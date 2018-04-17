#pragma once
#include "CoreMinimal.h"
#include "ModuleManager.h"
#include "Styling/ISlateStyle.h"
#include "Styling/SlateStyle.h"

class CineXProfiler;

class FCineX : public IModuleInterface
{
public:

	/** 
	 * IModuleInterface implementation 
	 */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	static void Initialize();

	static TSharedPtr< class ISlateStyle > Get();

	static FName GetStyleSetName();

private:

	static FString InContent(const FString& RelativePath, const ANSICHAR* Extension);

private:
	static TSharedPtr< class FSlateStyleSet > StyleSet;

	CineXProfiler* profiler_ = nullptr;
};
