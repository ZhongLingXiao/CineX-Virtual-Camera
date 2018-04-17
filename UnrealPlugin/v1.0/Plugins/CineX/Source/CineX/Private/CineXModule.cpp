#include "CineXPrivatePCH.h"

#include "CineXMode.h"
#include "CineXProfiler.h"
#include "CineXEditorTool.h"
#include "CineXDetailCustomization.h"

#include "PropertyEditorModule.h"
#include "Interfaces/IPluginManager.h"

#include "Styling/SlateStyleRegistry.h"
#include "Styling/SlateTypes.h"
#include "EditorStyleSet.h"
#include "SlateOptMacros.h"
#include "Features/IModularFeatures.h"

#define LOCTEXT_NAMESPACE "FCineXEditorModeModule"
#define IMAGE_PLUGIN_BRUSH( RelativePath, ... ) FSlateImageBrush( FCineX::InContent( RelativePath, ".png" ), __VA_ARGS__ )

FString FCineX::InContent(const FString & RelativePath, const ANSICHAR * Extension)
{
    static FString ContentDir = FPaths::GamePluginsDir() / TEXT("CineX/Content/Slate");
    return (ContentDir / RelativePath) + Extension;
}

TSharedPtr< FSlateStyleSet > FCineX::StyleSet = nullptr;
TSharedPtr< class ISlateStyle > FCineX::Get() { return StyleSet; }

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void FCineX::Initialize()
{
    // Const icon sizes
    const FVector2D Icon8x8(8.0f, 8.0f);
    const FVector2D Icon16x16(16.0f, 16.0f);
    const FVector2D Icon20x20(20.0f, 20.0f);
    const FVector2D Icon40x40(40.0f, 40.0f);

    // Only register once
    if (StyleSet.IsValid())
    {
        return;
    }

    StyleSet = MakeShareable(new FSlateStyleSet(GetStyleSetName()));
    StyleSet->SetContentRoot(FPaths::GamePluginsDir() / TEXT("CineX/Content/Slate"));
    StyleSet->SetCoreContentRoot(FPaths::EngineContentDir() / TEXT("Slate"));

    StyleSet->Set("LevelEditor.CineXEditorMode", new IMAGE_PLUGIN_BRUSH("Icons/TNT_sqr", Icon40x40));
    StyleSet->Set("LevelEditor.CineXEditorMode.Small", new IMAGE_PLUGIN_BRUSH("Icons/TNT_sqr", Icon20x20));
    StyleSet->Set("LevelEditor.CineXEditorMode.Selected", new IMAGE_PLUGIN_BRUSH("Icons/TNT_sqr", Icon40x40));
    StyleSet->Set("LevelEditor.CineXEditorMode.Selected.Small", new IMAGE_PLUGIN_BRUSH("Icons/TNT_sqr", Icon20x20));

    FSlateStyleRegistry::RegisterSlateStyle(*StyleSet.Get());
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

#undef IMAGE_PLUGIN_BRUSH

FName FCineX::GetStyleSetName()
{
    static FName StyleName(TEXT("CineXEditorMode"));
    return StyleName;
}

void FCineX::StartupModule()
{
    // Initialize style set
    Initialize();

    // Global profiler for async rendering
    profiler_ = new CineXProfiler();  
    IModularFeatures::Get().RegisterModularFeature(FExternalProfiler::GetFeatureName(), profiler_);

    // Register mode
    FEditorModeRegistry::Get().RegisterMode<FCineXEdMode>(
        FCineXEdMode::EM_CineXEdModeId,
        LOCTEXT("CineXEditorModeEdModeName", "CineXEditorModeEdMode"),
        FSlateIcon(GetStyleSetName(), "LevelEditor.CineXEditorMode", "LevelEditor.CineXEditorMode.Small"),
        true
        );
}

void FCineX::ShutdownModule()
{
    IModularFeatures::Get().UnregisterModularFeature(FExternalProfiler::GetFeatureName(), profiler_);
    delete profiler_;
    profiler_ = nullptr;

    // This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
    // we call this function before unloading the module.
    FEditorModeRegistry::Get().UnregisterMode(FCineXEdMode::EM_CineXEdModeId);

}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FCineX, CineX)



//class FCineX : public ICineX
//{
//	/** IModuleInterface implementation */
//	virtual void StartupModule() override
//	{
//		//ZMQContext::Singleton();
//		UE_LOG(LogCineX, Log, TEXT(" CineX plug-in Loaded"));
//	}
//
//	virtual void ShutdownModule() override
//	{
//		//ZMQContext::Release();
//		UE_LOG(LogCineX, Log, TEXT(" CineX plug-in Shutdown"));
//	}
//
//};
//
//
//IMPLEMENT_MODULE( FCineX, CineX )
//DEFINE_LOG_CATEGORY(LogCineX);