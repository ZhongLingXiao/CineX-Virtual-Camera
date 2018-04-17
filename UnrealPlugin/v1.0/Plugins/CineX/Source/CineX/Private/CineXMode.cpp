#include "CineXMode.h"
#include "CineXEditor.h"
#include "Toolkits/ToolkitManager.h"
#include "EditorModeManager.h"

const FEditorModeID FCineXEdMode::EM_CineXEdModeId = TEXT("EM_CineXEdMode");

FCineXEdMode::FCineXEdMode()
{
    UISettings = NewObject<UCineXEditorTool>(GetTransientPackage(), TEXT("CineXUISettings"), RF_Transactional);
    UISettings->SetParent(this);
}

FCineXEdMode::~FCineXEdMode()
{

}

void FCineXEdMode::AddReferencedObjects(FReferenceCollector & Collector)
{
    // Call parent implementation
    FEdMode::AddReferencedObjects(Collector);

    Collector.AddReferencedObject(UISettings);
}

void FCineXEdMode::Enter()
{
    FEdMode::Enter();

    if (!Toolkit.IsValid() && UsesToolkits())
    {
        Toolkit = MakeShareable(new FCineXEdModeToolkit);
        Toolkit->Init(Owner->GetToolkitHost());
    }
}

void FCineXEdMode::Exit()
{
    if (Toolkit.IsValid())
    {
        FToolkitManager::Get().CloseToolkit(Toolkit.ToSharedRef());
        Toolkit.Reset();
    }

    // Call base Exit method to ensure proper cleanup
    FEdMode::Exit();
}

bool FCineXEdMode::UsesToolkits() const
{
    return true;
}