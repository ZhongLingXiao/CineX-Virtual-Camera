#include "CameraDriver.h"
#include "Camera/CameraActor.h"
#include <Runtime/Engine/Classes/Engine/Engine.h>
#include "Runtime/CinematicCamera/Public/CineCameraComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "EngineUtils.h"
#include "UdpSocketBuilder.h"
#include <EngineGlobals.h>

#define R2D 180/3.141592653
#define UNIT_SCALE 100.0 //ios -> unreal   m -> cm 
constexpr TCHAR*    CINE_CAMERA_CLASS   = TEXT("/CineX/CineXCameraDriver");
const static float  UNIT_MULTIPLIER     = 100; // meter to centimeter

UClass* ACameraDriver::UdriverClass = nullptr;

ACameraDriver::ACameraDriver() {
    // 1. Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick                   = true;
    PrimaryActorTick.bRunOnAnyThread                = false;
    PrimaryActorTick.bAllowTickOnDedicatedServer    = false;

    // 2. Build the static class
    if (UdriverClass == nullptr) {
        ConstructorHelpers::FClassFinder<ACameraDriver> UAsset(CINE_CAMERA_CLASS);
        UdriverClass = *UAsset.Class;
    }

    // 3. Init video manager
    video_manager_ = VideoManager::GetInstance();
}

ACameraDriver::~ACameraDriver() {
    video_manager_ = nullptr;
}


void ACameraDriver::BeginPlay() {
    // 1. Parent BeginPlay().
    Super::BeginPlay();

    // 2. Set CameraPawn's view as current view. 
    takeOverView();

    // 3. Start thread and set up callback function.
    clearCameraDataArray();
    StartUDPReceiver("CameraDataReceiver", IPAddress, Port);

    // 4. Set World for video manager
    video_manager_->SetWorld(GetWorld());
    video_manager_->Connect(IPAddress_IOS, Port_IOS);
}

void ACameraDriver::EndPlay(const EEndPlayReason::Type EndPlayReason) {
    Super::EndPlay(EndPlayReason);
    
    // 1. Clean up receiver
    if (udp_receiver_)
    {
        delete udp_receiver_;
        udp_receiver_ = nullptr;
    }

    if (listen_socket_)
    {
        listen_socket_->Close();
        ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(listen_socket_);
        listen_socket_ = nullptr;
    }

    // 2. Restore view target.
    restoreView();

    // 3. Clear world info
    video_manager_->Disconnect();
    video_manager_->SetWorld(nullptr);

}

void ACameraDriver::Tick(float DeltaSeconds) {

    // 1. Get latest camera data from array
    if (ResetCache) {
        clearCameraDataArray();
        ResetCache          = false;
        bWaitingCache       = true;
        last_frame_index_   = -1;
    }

    CacheCount = cameraDataArrayCount();

    if (bWaitingCache) {
        if (CacheCount < FrameDelay + 1) {
            return;
        } else {
            bWaitingCache = false;
        }
    }

    if (CacheCount <= 0) {
        if (GEngine) {
            GEngine->AddOnScreenDebugMessage(0x8876525, 5, FColor::Red, FString("Unreal render too fast, no new data in the queue"), true, FVector2D(2, 2));
        }
        return;
    }

    if (AutoResetCache) {
        while (CacheCount > FrameDelay + 1) {
            peekCameraDataArray();
            CacheCount = cameraDataArrayCount();
        }
    }

    CameraData camera_data = peekCameraDataArray();

    // 2. Get camera component.
    UCineCameraComponent* cineComponent = nullptr;
    if (CameraPawn) {
        cineComponent = dynamic_cast<UCineCameraComponent*>(CameraPawn->GetCameraComponent());
    }

    // 3. Set camera data to camera actor
    if (CameraPawn) {
        // Get position and rotation.
        FVector position;
        FRotator rotation;
        getCameraPose(camera_data, position, rotation);

        // Unreal Engine use cm as uint: this part need to unit translation from source.
        CameraPawn->SetActorLocation(GetActorLocation() + position, true);
        CameraPawn->SetActorRotation(FQuat(GetActorRotation()) * FQuat(rotation));

        // Set focus and focal length to camera component.
        if (cineComponent) {
            if (camera_data.Zoom > 0.0) {
                cineComponent->CurrentFocalLength = camera_data.Zoom;
            }
                
            if (camera_data.Focus > 0.0) {
                cineComponent->FocusSettings.ManualFocusDistance = camera_data.Focus;
            }
        }
    }
    
}


void ACameraDriver::takeOverView() {
    player_controller_ = UGameplayStatics::GetPlayerController(this, 0);
    
    if (!cache_view_target_) {
         cache_view_target_ = player_controller_->GetViewTarget();
    }

    if (CameraPawn) {
        //Cut instantly to camera pawn.
        player_controller_->SetViewTarget(CameraPawn);
    }
}


void ACameraDriver::restoreView() {
    
    if (cache_view_target_) {
        player_controller_->SetViewTarget(cache_view_target_);
    }
    cache_view_target_ = nullptr;
}

void ACameraDriver::getCameraPose(const CameraData& Data_, FVector& Position_, FRotator& Rotation_) {
    Position_.X = -Data_.Z * UNIT_SCALE;
    Position_.Y = Data_.X * UNIT_SCALE;
    Position_.Z = Data_.Y * UNIT_SCALE;

    Rotation_.Pitch  = Data_.Pitch * R2D;
    Rotation_.Roll   = -Data_.Roll * R2D;
    Rotation_.Yaw    = -Data_.Yaw * R2D;
}
    


CameraData ACameraDriver::peekCameraDataArray() {
    if (camera_data_array_.Num() > 0) {
        std::unique_lock<std::mutex> lock(mutex_);
        auto result = camera_data_array_[0];
        camera_data_array_.RemoveAt(0);

        return result;
    }
    return CameraData();
}


int32 ACameraDriver::cameraDataArrayCount() {
    std::unique_lock<std::mutex> lock(mutex_);
    return camera_data_array_.Num();
}


void ACameraDriver::clearCameraDataArray() {
    std::unique_lock<std::mutex> lock(mutex_);
    camera_data_array_.Empty();
}


void ACameraDriver::OnReceiveUDP(const FArrayReaderPtr& ArrayReaderPtr_, const FIPv4Endpoint& Endpoint_) {
    auto size = ArrayReaderPtr_->Num();
    FArrayReaderPtr& ar = const_cast<FArrayReaderPtr&>(ArrayReaderPtr_);
    
    if (size == 32) {
        CameraData packet;
        *ArrayReaderPtr_
        << packet.X << packet.Y << packet.Z 
        << packet.Pitch << packet.Yaw << packet.Roll
        << packet.Focus << packet.Zoom;

        if (true) {
            std::unique_lock<std::mutex> ulock(mutex_);
            camera_data_array_.Add(packet);
        } else {
            if (GEngine) {
                GEngine->AddOnScreenDebugMessage(0x8876525, 3, FColor::Red, FString("camera data packet checksum error and discarded"), true, FVector2D(1, 1));
            }
            GLog->Log("camera data packet checksum error and discarded");
        }
    } else {
        if (GEngine) {
            GEngine->AddOnScreenDebugMessage(0x8876525, 3, FColor::Red, FString("camera data packet with invalid size received and discarded"), true, FVector2D(1, 1));
        }
        GLog->Log("camera data packet with invalid size received and discarded");
    }
}


void ACameraDriver::StartUDPReceiver(const FString& SocketName_, const FString& IP_, const int32 Port_) {
    FIPv4Address Address;
    FIPv4Address::Parse(IP_, Address);

    // Build IP address
    FIPv4Endpoint Endpoint(Address, Port_);

    // BUFFER SIZE
    int32 BufferSize = 1024;

    // Create Socket
    listen_socket_ = FUdpSocketBuilder(*SocketName_)
                    .AsNonBlocking()
                    .AsReusable()
                    .BoundToEndpoint(Endpoint)
                    .WithReceiveBufferSize(BufferSize)
                    ;

    if (listen_socket_) {
        FTimespan ThreadWaitTime = FTimespan::FromMilliseconds(10);
        udp_receiver_ = new FUdpSocketReceiver(listen_socket_, ThreadWaitTime, TEXT("CINEX UDP RECEIVER"));
        if (udp_receiver_) {
            udp_receiver_->OnDataReceived().BindUObject(this, &ACameraDriver::OnReceiveUDP);
            udp_receiver_->Start();
        } else {
            if (GEngine) {
                GEngine->AddOnScreenDebugMessage(0x8876525, 3, FColor::Red, FString("Fail to create UDP receiver"), true, FVector2D(1, 1));
            }
            GLog->Log("Fail to create UDP receiver");
        }
    } else {
        if (GEngine) {
            GEngine->AddOnScreenDebugMessage(0x8876525, 3, FColor::Red, FString("Fail to create UDP socket"), true, FVector2D(1, 1));
        }
        GLog->Log("Fail to create UDP socket");
    }
}