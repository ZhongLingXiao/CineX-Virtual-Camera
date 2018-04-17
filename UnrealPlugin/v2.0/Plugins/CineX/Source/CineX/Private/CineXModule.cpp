#include "CineXPrivatePCH.h"

class FCineX : public ICineX
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override
	{
		UE_LOG(LogCineX, Log, TEXT(" Loaded"));
	}

	virtual void ShutdownModule() override
	{
		UE_LOG(LogCineX, Log, TEXT(" Shutdown"));
	}

};


IMPLEMENT_MODULE(FCineX, CineX)
DEFINE_LOG_CATEGORY(LogCineX);
