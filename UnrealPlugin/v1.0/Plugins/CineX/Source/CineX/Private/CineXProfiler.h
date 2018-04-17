#pragma once
#include "CoreMinimal.h"
#include "ProfilingDebugging/ExternalProfiler.h"

class CineXProfiler : public FExternalProfiler
{
public:
    CineXProfiler();
    ~CineXProfiler();

    /** Mark where the profiler should consider the frame boundary to be. */
    void FrameSync() override;

    /** Pauses profiling. */
    void ProfilerPauseFunction() override;

    /** Resumes profiling. */
    void ProfilerResumeFunction() override;

    /** Gets the name of this profiler as a string.  This is used to allow the user to select this profiler in a system configuration file or on the command-line */
    const TCHAR* GetProfilerName() const  override {
        return TEXT("CineXProfiler");
    }
private:
    //
    VideoManager* video_manager_ = nullptr;
};