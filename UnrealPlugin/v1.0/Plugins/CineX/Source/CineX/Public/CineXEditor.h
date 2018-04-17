#pragma once

#include "CoreMinimal.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SCompoundWidget.h"
#include "CineXMode.h"
#include "Toolkits/IToolkitHost.h"
#include "AssetThumbnail.h"
#include "Toolkits/BaseToolkit.h"
#include "Editor.h"

class IDetailsView;
class SCineXEditor;
class SErrorText;
struct FPropertyAndParent;

class FCineXEdModeToolkit : public FModeToolkit
{
public:
    /** FModeToolkit interface */
    virtual void Init(const TSharedPtr<IToolkitHost>& InitToolkitHost) override;

    /** IToolkit interface */
    virtual FName GetToolkitFName() const override;
    virtual FText GetBaseToolkitName() const override;
    virtual FCineXEdMode* GetEditorMode() const override;
    virtual TSharedPtr<class SWidget> GetInlineContent() const override;


private:
    /** Geometry tools widget */
    TSharedPtr<SCineXEditor> NewEditorWidgets;
};

/**
* Slate widgets for the New Editor Mode
*/
class SCineXEditor : public SCompoundWidget
{
public:
    SLATE_BEGIN_ARGS(SCineXEditor) {}
    SLATE_END_ARGS()

    void Construct(const FArguments& InArgs, TSharedRef<FCineXEdModeToolkit> InParentToolkit);

    void RefreshDetailPanel();

protected:

    class FCineXEdMode* GetEditorMode() const;

    FText GetErrorText() const;

    bool GetNewEditorIsEnabled() const;

    bool GetIsPropertyVisible(const FPropertyAndParent& PropertyAndParent) const;

    TSharedPtr<SErrorText> Error;

    TSharedPtr<IDetailsView> DetailsPanel;
};