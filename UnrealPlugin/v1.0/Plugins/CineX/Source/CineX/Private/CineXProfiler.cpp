#include "CineXProfiler.h"
#include "VideoManager.h"

CineXProfiler::CineXProfiler() {
    video_manager_ = VideoManager::GetInstance();
}

CineXProfiler::~CineXProfiler() {
    video_manager_ = nullptr;
    VideoManager::ReleaseInstance();
}

void CineXProfiler::FrameSync() {
    // TODO async rendering here
    //GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("ASync Rendering ..."));
    video_manager_->ReadPixels();
}

void CineXProfiler::ProfilerPauseFunction() {
}

void CineXProfiler::ProfilerResumeFunction() {
}