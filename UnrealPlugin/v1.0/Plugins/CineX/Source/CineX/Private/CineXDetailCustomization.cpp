#include "CineXDetailCustomization.h"
#include "PropertyEditing.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SComboButton.h"

TSharedRef<IDetailCustomization> FCineXDetailCustomization::MakeInstance()
{
	return MakeShareable(new FCineXDetailCustomization);
}


void FCineXDetailCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	TSet<UClass*> Classes;

	TArray<TWeakObjectPtr<UObject>> ObjectsBeingCustomized;
	DetailBuilder.GetObjectsBeingCustomized(/*out*/ ObjectsBeingCustomized);

	for (auto WeakObject : ObjectsBeingCustomized) 
	{
		if (UObject* Instance = WeakObject.Get())
		{
			Classes.Add(Instance->GetClass());
		}
	}

	//Create commands category
	IDetailCategoryBuilder& Category = DetailBuilder.EditCategory("Connection");

	//Create button for each element
	for (UClass* Class : Classes)
	{
		for (TFieldIterator<UFunction> FuncIt(Class); FuncIt; ++FuncIt) 
		{
			UFunction* Function = *FuncIt;
			if (Function->HasAnyFunctionFlags(FUNC_Exec) && (Function->NumParms == 0))
			{
				const FString FunctionName = Function->GetName();
				const FText ButtonCaption = FText::FromString(FunctionName);
				Category.AddCustomRow(ButtonCaption)
				.ValueContent()
				[
					SNew(SButton)
					.Text(ButtonCaption)
					.OnClicked(FOnClicked::CreateStatic(&FCineXDetailCustomization::ExecuteCommand, &DetailBuilder, Function))
				];
			}
		}
	}
}

FReply FCineXDetailCustomization::ExecuteCommand(IDetailLayoutBuilder * DetailBuilder, UFunction * MethodToExecute)
{
	TArray<TWeakObjectPtr<UObject>> ObjectsBeingCustomized;
	DetailBuilder->GetObjectsBeingCustomized(/*out*/ ObjectsBeingCustomized);

	for (auto WeakObject : ObjectsBeingCustomized)
	{
		if (UObject* Instance = WeakObject.Get())
		{
			Instance->CallFunctionByNameWithArguments(*MethodToExecute->GetName(), *GLog, nullptr, true);
		}
	}
	
	return FReply::Handled();
}