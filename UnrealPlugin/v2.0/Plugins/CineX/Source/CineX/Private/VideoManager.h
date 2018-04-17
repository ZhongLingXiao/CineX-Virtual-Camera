#pragma once
#include "CoreMinimal.h"
#include "RHI.h"

#include <thread>
#include <mutex>

#include "zmq.hpp"
#include "NvFBCLibrary.h"
#include "NvFBC/nvFBCToSys.h"

#include "CineXPrivatePCH.h"

namespace std {
    class thread;
};


class VideoManager
{
public:

	static VideoManager* GetInstance();
	static void ReleaseInstance();

	void Connect(const FString& IP_, const int32 Port_);
	void Disconnect();
	bool IsConnected();

	void SendFrame();

protected:

	VideoManager();
	~VideoManager();


private:

	unsigned long JpegCompress(void* lpBmpBuffer, int nWidth, int nHeight, int quality, unsigned char*& ppJpegBuffer);

private:

	// Thread
	std::thread*				thread_ = nullptr;
	std::mutex					mutex_;
	bool						running_ = false;
	// ZMQ
	zmq::context_t*				context_ = nullptr;
	zmq::socket_t*				socket_ = nullptr;
	FString						address_;

	// NV Capture
	uint8*						frame_buffer_ = nullptr;
	NvFBCLibrary				nvfbc_library_;
	NvFBCToSys*					nvfbc_to_sys_ = nullptr;
	NVFBC_TOSYS_SETUP_PARAMS	fbc_sys_setup_params_ = { 0 };
	NVFBCRESULT					fbc_setup_status_ = NVFBC_SUCCESS;
};

