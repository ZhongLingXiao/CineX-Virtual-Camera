// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "GeneratedCppIncludes.h"
#include "Public/CineXEditorTool.h"
PRAGMA_DISABLE_OPTIMIZATION
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCineXEditorTool() {}
// Cross Module References
	CINEX_API UFunction* Z_Construct_UFunction_UCineXEditorTool_Start();
	CINEX_API UClass* Z_Construct_UClass_UCineXEditorTool();
	CINEX_API UFunction* Z_Construct_UFunction_UCineXEditorTool_Stop();
	CINEX_API UClass* Z_Construct_UClass_UCineXEditorTool_NoRegister();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	UPackage* Z_Construct_UPackage__Script_CineX();
// End Cross Module References
	void UCineXEditorTool::StaticRegisterNativesUCineXEditorTool()
	{
		UClass* Class = UCineXEditorTool::StaticClass();
		static const TNameNativePtrPair<ANSICHAR> AnsiFuncs[] = {
			{ "Start", (Native)&UCineXEditorTool::execStart },
			{ "Stop", (Native)&UCineXEditorTool::execStop },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, AnsiFuncs, ARRAY_COUNT(AnsiFuncs));
	}
	UFunction* Z_Construct_UFunction_UCineXEditorTool_Start()
	{
		UObject* Outer = Z_Construct_UClass_UCineXEditorTool();
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("Start"), RF_Public|RF_Transient|RF_MarkAsNative) UFunction(FObjectInitializer(), nullptr, (EFunctionFlags)0x00020601, 65535);
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("Public/CineXEditorTool.h"));
#endif
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_UCineXEditorTool_Stop()
	{
		UObject* Outer = Z_Construct_UClass_UCineXEditorTool();
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("Stop"), RF_Public|RF_Transient|RF_MarkAsNative) UFunction(FObjectInitializer(), nullptr, (EFunctionFlags)0x00020601, 65535);
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("Public/CineXEditorTool.h"));
#endif
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UCineXEditorTool_NoRegister()
	{
		return UCineXEditorTool::StaticClass();
	}
	UClass* Z_Construct_UClass_UCineXEditorTool()
	{
		static UClass* OuterClass = NULL;
		if (!OuterClass)
		{
			Z_Construct_UClass_UObject();
			Z_Construct_UPackage__Script_CineX();
			OuterClass = UCineXEditorTool::StaticClass();
			if (!(OuterClass->ClassFlags & CLASS_Constructed))
			{
				UObjectForceRegistration(OuterClass);
				OuterClass->ClassFlags |= (EClassFlags)0x20000080u;

				OuterClass->LinkChild(Z_Construct_UFunction_UCineXEditorTool_Start());
				OuterClass->LinkChild(Z_Construct_UFunction_UCineXEditorTool_Stop());

				UProperty* NewProp_description = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("description"), RF_Public|RF_Transient|RF_MarkAsNative) UStrProperty(CPP_PROPERTY_BASE(description, UCineXEditorTool), 0x0010000000000001);
				UProperty* NewProp_take = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("take"), RF_Public|RF_Transient|RF_MarkAsNative) UStrProperty(CPP_PROPERTY_BASE(take, UCineXEditorTool), 0x0010000000000001);
				UProperty* NewProp_shot = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("shot"), RF_Public|RF_Transient|RF_MarkAsNative) UStrProperty(CPP_PROPERTY_BASE(shot, UCineXEditorTool), 0x0010000000000001);
				UProperty* NewProp_scene = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("scene"), RF_Public|RF_Transient|RF_MarkAsNative) UStrProperty(CPP_PROPERTY_BASE(scene, UCineXEditorTool), 0x0010000000000001);
				UProperty* NewProp_Port = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("Port"), RF_Public|RF_Transient|RF_MarkAsNative) UIntProperty(CPP_PROPERTY_BASE(Port, UCineXEditorTool), 0x0010000000000001);
				UProperty* NewProp_IPAddress = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("IPAddress"), RF_Public|RF_Transient|RF_MarkAsNative) UStrProperty(CPP_PROPERTY_BASE(IPAddress, UCineXEditorTool), 0x0010000000000001);
				OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UFunction_UCineXEditorTool_Start(), "Start"); // 1201752904
				OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UFunction_UCineXEditorTool_Stop(), "Stop"); // 1343692270
				static TCppClassTypeInfo<TCppClassTypeTraits<UCineXEditorTool> > StaticCppClassTypeInfo;
				OuterClass->SetCppTypeInfo(&StaticCppClassTypeInfo);
				OuterClass->StaticLink();
#if WITH_METADATA
				UMetaData* MetaData = OuterClass->GetOutermost()->GetMetaData();
				MetaData->SetValue(OuterClass, TEXT("IncludePath"), TEXT("CineXEditorTool.h"));
				MetaData->SetValue(OuterClass, TEXT("ModuleRelativePath"), TEXT("Public/CineXEditorTool.h"));
				MetaData->SetValue(NewProp_description, TEXT("Category"), TEXT("File Management"));
				MetaData->SetValue(NewProp_description, TEXT("ModuleRelativePath"), TEXT("Public/CineXEditorTool.h"));
				MetaData->SetValue(NewProp_take, TEXT("Category"), TEXT("File Management"));
				MetaData->SetValue(NewProp_take, TEXT("ModuleRelativePath"), TEXT("Public/CineXEditorTool.h"));
				MetaData->SetValue(NewProp_shot, TEXT("Category"), TEXT("File Management"));
				MetaData->SetValue(NewProp_shot, TEXT("ModuleRelativePath"), TEXT("Public/CineXEditorTool.h"));
				MetaData->SetValue(NewProp_scene, TEXT("Category"), TEXT("File Management"));
				MetaData->SetValue(NewProp_scene, TEXT("ModuleRelativePath"), TEXT("Public/CineXEditorTool.h"));
				MetaData->SetValue(NewProp_Port, TEXT("Category"), TEXT("Network"));
				MetaData->SetValue(NewProp_Port, TEXT("ModuleRelativePath"), TEXT("Public/CineXEditorTool.h"));
				MetaData->SetValue(NewProp_IPAddress, TEXT("Category"), TEXT("Network"));
				MetaData->SetValue(NewProp_IPAddress, TEXT("ModuleRelativePath"), TEXT("Public/CineXEditorTool.h"));
#endif
			}
		}
		check(OuterClass->GetClass());
		return OuterClass;
	}
	IMPLEMENT_CLASS(UCineXEditorTool, 3282854080);
	static FCompiledInDefer Z_CompiledInDefer_UClass_UCineXEditorTool(Z_Construct_UClass_UCineXEditorTool, &UCineXEditorTool::StaticClass, TEXT("/Script/CineX"), TEXT("UCineXEditorTool"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UCineXEditorTool);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
PRAGMA_ENABLE_OPTIMIZATION
