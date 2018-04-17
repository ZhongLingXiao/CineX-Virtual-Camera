#include "VideoManager.h"
#include "Runtime/Engine/Public/EngineGlobals.h" // TODO: GEngine only use for testing
#include "jpeglib.h"
#include <vector>


constexpr int MAX_WIDTH = 1920;
constexpr int MAX_HEIGHT = 1080;
constexpr int COMPONENTS_NUM = 4;
constexpr unsigned int MAGIC_NUM = 0x5643414d;


VideoManager::VideoManager() {
	// 1. Thread init with callback method
	thread_ = new std::thread(std::bind(&VideoManager::SendFrame, this));
    
    // 2. ZMQ init
    context_ = new zmq::context_t();

    // 3. Alloc 10mb memory for frame grab
	frame_buffer_ = (uint8*)malloc(10 * 1024 * 1024);

	// 4. Init NV capture library
	DWORD maxDisplayWidth = -1, maxDisplayHeight = -1;
	if (!nvfbc_library_.load()) {
		fprintf(stderr, "Unable to load the NvFBC library\n");
	}

	nvfbc_library_.enable(NVFBC_STATE_ENABLE);
	nvfbc_to_sys_ = (NvFBCToSys *)nvfbc_library_.create(NVFBC_TO_SYS, &maxDisplayWidth, &maxDisplayHeight);

	NVFBCRESULT status = NVFBC_SUCCESS;
	if (!nvfbc_to_sys_) {
		fprintf(stderr, "Unable to create an instance of NvFBC\n");
	}

	// Setup the frame grab
	fbc_sys_setup_params_.dwVersion = NVFBC_TOSYS_SETUP_PARAMS_VER;
	fbc_sys_setup_params_.eMode = NVFBC_TOSYS_ARGB;
	fbc_sys_setup_params_.bWithHWCursor = false;
	fbc_sys_setup_params_.bDiffMap = FALSE;
	fbc_sys_setup_params_.ppBuffer = (void **)&frame_buffer_;
	fbc_sys_setup_params_.ppDiffMap = NULL;

}


VideoManager::~VideoManager() {

	if (thread_) {
		thread_->join();
		delete thread_;
		thread_ = nullptr;
	}

    if (context_) {
        delete context_;
        context_ = nullptr;
    }

	if (nvfbc_to_sys_) {
		nvfbc_to_sys_->NvFBCToSysRelease();
		delete nvfbc_to_sys_;
		nvfbc_to_sys_ = nullptr;
	}

	if (frame_buffer_) {
		free(frame_buffer_);
		frame_buffer_ = nullptr;
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
	
	// 1. Set up NV capture
	fbc_setup_status_ = nvfbc_to_sys_->NvFBCToSysSetUp(&fbc_sys_setup_params_);
	if (fbc_setup_status_ != NVFBC_SUCCESS) {
		GEngine->AddOnScreenDebugMessage(0x8876525, 5, FColor::Red, FString("Fail to execute NvFBCToSysSetUp()"), true, FVector2D(1, 1));
	}

    // 2. ZMQ server bind
    assert(context_);
    socket_ = new zmq::socket_t(*context_, ZMQ_PUB);
    socket_->setsockopt(ZMQ_RCVTIMEO, 100);
    socket_->setsockopt(ZMQ_SNDTIMEO, 100);
    socket_->setsockopt(ZMQ_LINGER, 0);
	try {
		address_ = "tcp://" + IP_ + ":" + FString::FromInt(Port_);
		socket_->bind(TCHAR_TO_ANSI(*address_));
	} catch (...) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Fail to bind socket!"));
	}

	// 3. Set running state
	running_ = true;

}


void VideoManager::Disconnect() {
	
	running_ = false;

	try {
		socket_->unbind(TCHAR_TO_ANSI(*address_));
	} catch (...) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Fail to unbind socket!"));
	}

    if (socket_) {
        delete socket_;
        socket_ = nullptr;
    }

}


bool VideoManager::IsConnected() {

    return socket_->connected();

}


void VideoManager::SendFrame() {
	while (true)
	{
		// over 50fps
		if (running_ && nvfbc_to_sys_ && (fbc_setup_status_ == NVFBC_SUCCESS)) {

			// 1. Grab frame
			NvFBCFrameGrabInfo grabInfo;
			NVFBC_TOSYS_GRAB_FRAME_PARAMS fbcSysGrabParams = { 0 };
			fbcSysGrabParams.dwVersion = NVFBC_TOSYS_GRAB_FRAME_PARAMS_VER;
			fbcSysGrabParams.dwFlags = NVFBC_TOSYS_NOFLAGS;
			fbcSysGrabParams.dwTargetWidth = 1280;
			fbcSysGrabParams.dwTargetHeight = 720;
			fbcSysGrabParams.dwStartX = 0;
			fbcSysGrabParams.dwStartY = 0;
			fbcSysGrabParams.eGMode = NVFBC_TOSYS_SOURCEMODE_CROP;
			fbcSysGrabParams.pNvFBCFrameGrabInfo = &grabInfo;
			
			if (!nvfbc_to_sys_)
				continue;

			NVFBCRESULT status;
			status = nvfbc_to_sys_->NvFBCToSysGrabFrame(&fbcSysGrabParams);

			// 2. Compress data
			unsigned char *pOutJpegBuffer = nullptr;
			unsigned long size = 0;
			if (status == NVFBC_SUCCESS) {		
				size = JpegCompress(frame_buffer_, 1280, 720, 75, pOutJpegBuffer);
			}

			// 3. Send data
			if (socket_) {
				bool success = (size == socket_->send(pOutJpegBuffer, size, ZMQ_DONTWAIT));
				if (!success) {
					GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Send Pixels fail ..."));
				}
			}

			free(pOutJpegBuffer);

		} else {
			
			// idle wait 0.1 second
			::Sleep(100);
			continue;
		}

	}

}


unsigned long VideoManager::JpegCompress(void* lpBmpBuffer, int nWidth, int nHeight, int quality, unsigned char*& ppJpegBuffer) {

    jpeg_compress_struct cinfo;
    jpeg_error_mgr errorMgr;
    unsigned long compressSize;

    cinfo.err = jpeg_std_error(&errorMgr);

    jpeg_create_compress(&cinfo);

    cinfo.image_width = nWidth;
    cinfo.image_height = nHeight;
    cinfo.input_components = 4;				//how many bit per dot
    cinfo.in_color_space = JCS_EXT_BGRX;	//seq of bit, red blue green alpha(x)

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

