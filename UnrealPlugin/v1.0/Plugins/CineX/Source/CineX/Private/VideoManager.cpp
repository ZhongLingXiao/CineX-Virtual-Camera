#include "VideoManager.h"
#include "Runtime/Engine/Public/EngineGlobals.h" // TODO: GEngine only use for testing
#include "jpeglib.h"
#include <vector>


constexpr int MAX_WIDTH = 1920;
constexpr int MAX_HEIGHT = 1080;
constexpr int COMPONENTS_NUM = 4;
constexpr unsigned int MAGIC_NUM = 0x5643414d;

static IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(TEXT("ImageWrapper"));

VideoManager::VideoManager() {

    // Producer & consumer queue
    cache_ = new BoundedBuffer(CACHE_CAPACITY);
    
    // ZMQ init
    context_ = new zmq::context_t();

    // Thread init with callback method
    thread_ = new std::thread(std::bind(&VideoManager::SendPixels, this));

    // Alloc 1mb memory
    image_data_.Init(0, 4*1024*1024);

    /*
    NvFBCLibrary nvfbcLibrary;
    NvFBCToSys *nvfbcToSys = NULL;

    DWORD maxDisplayWidth = -1, maxDisplayHeight = -1;
    BOOL bRecoveryDone = FALSE;

    NvFBCFrameGrabInfo grabInfo;
    unsigned char *frameBuffer = NULL;
    unsigned char *diffMap = NULL;

    if (!nvfbcLibrary.load())
    {
        fprintf(stderr, "Unable to load the NvFBC library\n");
    }

    NVFBC_STATE state = NVFBC_STATE_ENABLE;
    nvfbcLibrary.enable(state);

    //! Create an instance of NvFBCToSys
    nvfbcToSys = (NvFBCToSys *)nvfbcLibrary.create(NVFBC_TO_SYS, &maxDisplayWidth, &maxDisplayHeight);

    NVFBCRESULT status = NVFBC_SUCCESS;
    if (!nvfbcToSys)
    {
        fprintf(stderr, "Unable to create an instance of NvFBC\n");
    }

    //! Setup the frame grab
    NVFBC_TOSYS_SETUP_PARAMS fbcSysSetupParams = { 0 };
    fbcSysSetupParams.dwVersion = NVFBC_TOSYS_SETUP_PARAMS_VER;
    fbcSysSetupParams.eMode = NVFBC_TOSYS_ARGB;
    fbcSysSetupParams.bWithHWCursor = false;
    fbcSysSetupParams.bDiffMap = FALSE;
    fbcSysSetupParams.ppBuffer = (void **)&frameBuffer;
    fbcSysSetupParams.ppDiffMap = NULL;

    status = nvfbcToSys->NvFBCToSysSetUp(&fbcSysSetupParams);
    if (status == NVFBC_SUCCESS)
    {
        NVFBC_TOSYS_GRAB_FRAME_PARAMS fbcSysGrabParams = { 0 };
        //! Grab the frame.  
        // If scaling or cropping is enabled the width and height returned in the
        // NvFBCFrameGrabInfo structure reflect the current desktop resolution, not the actual grabbed size.
        fbcSysGrabParams.dwVersion = NVFBC_TOSYS_GRAB_FRAME_PARAMS_VER;
        fbcSysGrabParams.dwFlags = NVFBC_TOSYS_NOWAIT;
        fbcSysGrabParams.dwTargetWidth = 1280;
        fbcSysGrabParams.dwTargetHeight = 720;
        fbcSysGrabParams.dwStartX = 0;
        fbcSysGrabParams.dwStartY = 0;
        fbcSysGrabParams.eGMode = NVFBC_TOSYS_SOURCEMODE_SCALE;
        fbcSysGrabParams.pNvFBCFrameGrabInfo = &grabInfo;
    
        status = nvfbcToSys->NvFBCToSysGrabFrame(&fbcSysGrabParams);
        if (status == NVFBC_SUCCESS)
        {
            fprintf(stderr, "NVFBC_SUCCESS\n");
        }
        else
        {
            fprintf(stderr, "NVFBC_Failed\n");
        }
    
        if (nvfbcToSys)
        {
            //! Release the NvFBCToSys object
            nvfbcToSys->NvFBCToSysRelease();
        }
    }
	*/

}


VideoManager::~VideoManager() {

    world_ = nullptr;
    if (cache_) {
        delete cache_;
        cache_ = nullptr;
    }

    cancel_ = true;

    if (thread_) {
        thread_->join();
        delete thread_;
        thread_ = nullptr;
    }

    if (context_) {
        delete context_;
        context_ = nullptr;
    }

}


static VideoManager* sInst = nullptr;
VideoManager* VideoManager::GetInstance() {

    if (!sInst) {
        sInst = new VideoManager();
    }
    return sInst;

}


void VideoManager::ReleaseInstance() {

    if (sInst) {
        delete sInst;
        sInst = nullptr;
    }

}


void VideoManager::Connect(const FString& IP_, const int32 Port_) {

    // zmq server bind
    assert(context_);
    socket_ = new zmq::socket_t(*context_, ZMQ_PUB);
    socket_->setsockopt(ZMQ_RCVTIMEO, 100);
    socket_->setsockopt(ZMQ_SNDTIMEO, 100);
    socket_->setsockopt(ZMQ_LINGER, 0);
	try {
		address_ = "tcp://" + IP_ + ":" + FString::FromInt(Port_);
		socket_->bind(TCHAR_TO_ANSI(*address_));
	} catch (...) {
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Fail to bind socket!"));
	}

}


void VideoManager::Disconnect() {

	try {
		socket_->unbind(TCHAR_TO_ANSI(*address_));
	} catch (...) {
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Fail to unbind socket!"));
	}

    if (socket_) {
        delete socket_;
        socket_ = nullptr;
    }

}


bool VideoManager::IsConnected() {

    return socket_->connected();

}


void VideoManager::ReadPixels() {

    if (world_) {

        bool bScreenshotSuccessful = false;
        UGameViewportClient* client = world_->GetGameViewport();
        if (!client)
            return;

        FViewport* InViewport = client->Viewport;

        TArray<FColor> Bitmap;
        bScreenshotSuccessful = GetViewportScreenShot(InViewport, Bitmap);

        cache_->Deposit(Bitmap);

    }

}


void VideoManager::SendPixels() {

    while (true) {
        // 1. Get data
        TArray<FColor> data = cache_->Fetch();

        // 2. Send data
        if (world_) {
            UGameViewportClient* client = world_->GetGameViewport();
            if (!client)
                continue;

            FViewport* viewport = client->Viewport;;
            if (!viewport)
                continue;

            unsigned char *pOutJpegBuffer = nullptr;
            unsigned long size = JpegCompress(data.GetData(), viewport->GetSizeXY().X, viewport->GetSizeXY().Y, 75, pOutJpegBuffer);

            image_data_.Reserve(size);
            image_data_.SetNum(size);
            image_data_.SetNumUnsafeInternal(size);

            for (unsigned long i = 0; i < size; i++) {
                image_data_[i] = pOutJpegBuffer[i];
            }

            if (socket_) {
                bool success = (image_data_.Num() == socket_->send(image_data_.GetData(), image_data_.Num(), ZMQ_DONTWAIT));
                if (!success) {
					GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Send Pixels fail ..."));
                }
            }

            free(pOutJpegBuffer);
        }
    }

}


unsigned long VideoManager::JpegCompress(void* lpBmpBuffer, int nWidth, int nHeight, int quality, unsigned char*& ppJpegBuffer) {

    jpeg_compress_struct cinfo;
    jpeg_error_mgr errorMgr;
    unsigned long compressSize;

    cinfo.err = jpeg_std_error(&errorMgr);
    //cinfo.err->error_exit = error_exit;
    jpeg_create_compress(&cinfo);

    cinfo.image_width = nWidth;
    cinfo.image_height = nHeight;
    cinfo.input_components = 4; //how many bit per dot
    cinfo.in_color_space = JCS_EXT_BGRX; //seq of bit, red blue green alpha(x)

    jpeg_mem_dest(&cinfo, &ppJpegBuffer, &compressSize);

    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, quality, true);

    jpeg_start_compress(&cinfo, true);

    int nRowStride = nWidth * 4;
    std::vector<JSAMPROW> row_pointer(cinfo.image_height);

    auto ptr = (unsigned char*)lpBmpBuffer;
    for (JDIMENSION i = 0; i < cinfo.image_height; i++, ptr += nRowStride) {
        row_pointer[i] = ptr;
    }

    jpeg_write_scanlines(&cinfo, row_pointer.data(), row_pointer.size());
    jpeg_finish_compress(&cinfo);
    jpeg_destroy_compress(&cinfo);
    return compressSize;

}

