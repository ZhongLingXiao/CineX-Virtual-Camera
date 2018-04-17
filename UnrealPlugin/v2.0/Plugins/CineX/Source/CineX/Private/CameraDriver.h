#pragma once
#include <mutex>
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Serialization/ArrayReader.h"
#include "Runtime/Networking/Public/Common/UdpSocketReceiver.h"
#include "CineXPrivatePCH.h"
#include "CameraDriver.generated.h"


class FLevelSequenceEditorToolkit;

/**
 * Camera Driver Class
 */
UCLASS(abstract)
class ACameraDriver : public AActor
{
    GENERATED_BODY()

// Property
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Network")
        FString IPAddress = FString(TEXT("localhost")); 
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Network")
        int32 Port = 62345;       

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cine Camera")
        class ACameraActor* CameraPawn = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
        int32 FrameDelay = 2;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
        bool ResetCache = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
        bool AutoResetCache = true;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
        int32 CacheCount = 0;


// Function
public:
    // Sets default values for this actor's properties 
    ACameraDriver();
    virtual ~ACameraDriver();

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

    // Called every frame
    virtual void Tick(float DeltaSeconds) override;


private:

    // Set view target to 'CameraPawn' when begin play
    void takeOverView();
    void restoreView();

    // Get camera pose info
    void getCameraPose(const CameraData& Data_, FVector& Position_, FRotator& Rotation_);

    // Camera data getter and setter
    CameraData  peekCameraDataArray();
    int32       cameraDataArrayCount();
    void        clearCameraDataArray();

    // UDP receiver
    void OnReceiveUDP(const FArrayReaderPtr& ArrayReaderPtr_, const FIPv4Endpoint& Endpoint_);
    void StartUDPReceiver(const FString& SocketName_, const FString& IP_, const int32 Port_);

private:
    // Network
    FSocket*                listen_socket_      = nullptr;
    FUdpSocketReceiver*     udp_receiver_       = nullptr;

    AActor*                 cache_view_target_  = nullptr;
    APlayerController*      player_controller_  = nullptr;

    std::mutex              mutex_;
    TArray<CameraData>      camera_data_array_;

    // Debug
    bool                    bWaitingCache       = true;
    int                     last_frame_index_   = -1;

    // Video manager
    VideoManager*           video_manager_      = nullptr;

	// TODO: CMD
	bool							sequencer_playback_stat_	= false;
	FLevelSequenceEditorToolkit*	level_sequence_editor_		= nullptr;

public:
    static UClass* UdriverClass;
};
