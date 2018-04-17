#include "CineXEditor.h"
#include "CineXMode.h"
#include "CineXEditorTool.h"
#include "CineXDetailCustomization.h"
#include "Engine/Selection.h"

#include "PropertyEditorModule.h"
#include "SlateOptMacros.h"

#include "IDetailsView.h"
#include "IIntroTutorials.h"

#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Notifications/SErrorText.h"
#include "EditorModeManager.h"

#define LOCTEXT_NAMESPACE "FNewEditorTool"


void FCineXEdModeToolkit::Init(const TSharedPtr<IToolkitHost>& InitToolkitHost)
{
    FCineXEdMode* NewEdMode = GetEditorMode();

    NewEditorWidgets = SNew(SCineXEditor, SharedThis(this));

    FModeToolkit::Init(InitToolkitHost);
}

FName FCineXEdModeToolkit::GetToolkitFName() const
{
    return FName("CineXEditor");
}

FText FCineXEdModeToolkit::GetBaseToolkitName() const
{
    return LOCTEXT("Toolkitname", "CineX Editor");
}

FCineXEdMode* FCineXEdModeToolkit::GetEditorMode() const
{
    return (FCineXEdMode*)GLevelEditorModeTools().GetActiveMode(FCineXEdMode::EM_CineXEdModeId);
}

TSharedPtr<SWidget> FCineXEdModeToolkit::GetInlineContent() const
{
    return NewEditorWidgets;
}

//////////////////////////////////////////////////////////////////////////

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SCineXEditor::Construct(const FArguments& InArgs, TSharedRef<FCineXEdModeToolkit> InParentToolkit)
{
    FPropertyEditorModule& PropertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
    PropertyEditorModule.RegisterCustomClassLayout("CineXEditorTool", FOnGetDetailCustomizationInstance::CreateStatic(&FCineXDetailCustomization::MakeInstance));
    PropertyEditorModule.NotifyCustomizationModuleChanged();

    FDetailsViewArgs DetailsViewArgs(false, false, false, FDetailsViewArgs::HideNameArea);

    DetailsPanel = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
    DetailsPanel->SetIsPropertyVisibleDelegate(FIsPropertyVisible::CreateSP(this, &SCineXEditor::GetIsPropertyVisible));

    FCineXEdMode* NewEdMode = GetEditorMode();

    ChildSlot
    [
        SNew(SVerticalBox)
        + SVerticalBox::Slot()
        .Padding(0)
        [
            SNew(SVerticalBox)
            .IsEnabled(this, &SCineXEditor::GetNewEditorIsEnabled)
            + SVerticalBox::Slot()
            .Padding(0)
            [
                DetailsPanel.ToSharedRef()
            ]
        ]
    ];

    RefreshDetailPanel();
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

FCineXEdMode* SCineXEditor::GetEditorMode() const
{
    return (FCineXEdMode*)GLevelEditorModeTools().GetActiveMode(FCineXEdMode::EM_CineXEdModeId);
}

FText SCineXEditor::GetErrorText() const
{
    FCineXEdMode* NewEdMode = GetEditorMode();

    return FText::GetEmpty();
}

bool SCineXEditor::GetNewEditorIsEnabled() const
{
    FCineXEdMode* NewEdMode = GetEditorMode();
    if (NewEdMode)
    {
        return true;
    }
    return false;
}

bool SCineXEditor::GetIsPropertyVisible(const FPropertyAndParent & PropertyAndParent) const
{
    return true;
}

void SCineXEditor::RefreshDetailPanel()
{
    FCineXEdMode* NewEdMode = GetEditorMode();
    if (NewEdMode)
    {
        // Refresh details panel
        DetailsPanel->SetObject(NewEdMode->UISettings, true);
    }
}
#undef LOCTEXT_NAMESPACE