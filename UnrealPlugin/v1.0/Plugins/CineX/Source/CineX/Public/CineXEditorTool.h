#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"
#include "CineXMode.h"
#include "CineXEditorTool.generated.h"

class FCineXEdMode;

UCLASS()
class UCineXEditorTool : public UObject
{
    GENERATED_UCLASS_BODY()

public:
    FCineXEdMode* ParentMode;

    UPROPERTY(EditAnywhere, Category = "Network")
        FString IPAddress = "192.168.0.1";
    UPROPERTY(EditAnywhere, Category = "Network")
        int32 Port = 62346;

    UPROPERTY(EditAnywhere, Category = "File Management")
        FString scene = "INT. SCHOOL - NIGHT";
    UPROPERTY(EditAnywhere, Category = "File Management")
        FString shot = "0001";
    UPROPERTY(EditAnywhere, Category = "File Management")
        FString take = "01";
    UPROPERTY(EditAnywhere, Category = "File Management")
        FString description = "PULL BACK TO WIDE ON";


    UFUNCTION(Exec)
        void Stop();

    UFUNCTION(Exec)
        void Start();

    void SetParent(FCineXEdMode* NewParent) {
        ParentMode = NewParent;
    }
};