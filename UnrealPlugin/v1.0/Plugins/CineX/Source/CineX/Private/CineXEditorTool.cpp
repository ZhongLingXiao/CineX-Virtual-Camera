#include "CineXEditorTool.h"
#include "UObject/ConstructorHelpers.h"
#include "Editor/SequenceRecorder/Public/ISequenceRecorder.h"

UCineXEditorTool::UCineXEditorTool(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{

}

void UCineXEditorTool::Start()
{
    UE_LOG(LogTemp, Warning, TEXT("Start function is executed"));
}

void UCineXEditorTool::Stop()
{
    UE_LOG(LogTemp, Warning, TEXT("Stop function is executed"));
}