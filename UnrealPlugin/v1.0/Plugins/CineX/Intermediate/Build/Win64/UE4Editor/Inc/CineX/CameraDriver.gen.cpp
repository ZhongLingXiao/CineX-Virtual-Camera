// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "GeneratedCppIncludes.h"
#include "Private/CameraDriver.h"
PRAGMA_DISABLE_OPTIMIZATION
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCameraDriver() {}
// Cross Module References
	CINEX_API UClass* Z_Construct_UClass_ACameraDriver_NoRegister();
	CINEX_API UClass* Z_Construct_UClass_ACameraDriver();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_CineX();
	ENGINE_API UClass* Z_Construct_UClass_ACameraActor_NoRegister();
// End Cross Module References
	void ACameraDriver::StaticRegisterNativesACameraDriver()
	{
	}
	UClass* Z_Construct_UClass_ACameraDriver_NoRegister()
	{
		return ACameraDriver::StaticClass();
	}
	UClass* Z_Construct_UClass_ACameraDriver()
	{
		static UClass* OuterClass = NULL;
		if (!OuterClass)
		{
			Z_Construct_UClass_AActor();
			Z_Construct_UPackage__Script_CineX();
			OuterClass = ACameraDriver::StaticClass();
			if (!(OuterClass->ClassFlags & CLASS_Constructed))
			{
				UObjectForceRegistration(OuterClass);
				OuterClass->ClassFlags |= (EClassFlags)0x20800081u;


				UProperty* NewProp_CacheCount = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("CacheCount"), RF_Public|RF_Transient|RF_MarkAsNative) UIntProperty(CPP_PROPERTY_BASE(CacheCount, ACameraDriver), 0x0010000000000005);
				CPP_BOOL_PROPERTY_BITMASK_STRUCT(AutoResetCache, ACameraDriver);
				UProperty* NewProp_AutoResetCache = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("AutoResetCache"), RF_Public|RF_Transient|RF_MarkAsNative) UBoolProperty(FObjectInitializer(), EC_CppProperty, CPP_BOOL_PROPERTY_OFFSET(AutoResetCache, ACameraDriver), 0x0010000000000005, CPP_BOOL_PROPERTY_BITMASK(AutoResetCache, ACameraDriver), sizeof(bool), true);
				CPP_BOOL_PROPERTY_BITMASK_STRUCT(ResetCache, ACameraDriver);
				UProperty* NewProp_ResetCache = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("ResetCache"), RF_Public|RF_Transient|RF_MarkAsNative) UBoolProperty(FObjectInitializer(), EC_CppProperty, CPP_BOOL_PROPERTY_OFFSET(ResetCache, ACameraDriver), 0x0010000000000005, CPP_BOOL_PROPERTY_BITMASK(ResetCache, ACameraDriver), sizeof(bool), true);
				UProperty* NewProp_FrameDelay = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("FrameDelay"), RF_Public|RF_Transient|RF_MarkAsNative) UIntProperty(CPP_PROPERTY_BASE(FrameDelay, ACameraDriver), 0x0010000000000005);
				UProperty* NewProp_CameraPawn = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("CameraPawn"), RF_Public|RF_Transient|RF_MarkAsNative) UObjectProperty(CPP_PROPERTY_BASE(CameraPawn, ACameraDriver), 0x0010000000000005, Z_Construct_UClass_ACameraActor_NoRegister());
				UProperty* NewProp_Port_IOS = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("Port_IOS"), RF_Public|RF_Transient|RF_MarkAsNative) UIntProperty(CPP_PROPERTY_BASE(Port_IOS, ACameraDriver), 0x0010000000000005);
				UProperty* NewProp_IPAddress_IOS = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("IPAddress_IOS"), RF_Public|RF_Transient|RF_MarkAsNative) UStrProperty(CPP_PROPERTY_BASE(IPAddress_IOS, ACameraDriver), 0x0010000000000005);
				UProperty* NewProp_Port = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("Port"), RF_Public|RF_Transient|RF_MarkAsNative) UIntProperty(CPP_PROPERTY_BASE(Port, ACameraDriver), 0x0010000000000005);
				UProperty* NewProp_IPAddress = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("IPAddress"), RF_Public|RF_Transient|RF_MarkAsNative) UStrProperty(CPP_PROPERTY_BASE(IPAddress, ACameraDriver), 0x0010000000000005);
				static TCppClassTypeInfo<TCppClassTypeTraits<ACameraDriver> > StaticCppClassTypeInfo;
				OuterClass->SetCppTypeInfo(&StaticCppClassTypeInfo);
				OuterClass->StaticLink();
#if WITH_METADATA
				UMetaData* MetaData = OuterClass->GetOutermost()->GetMetaData();
				MetaData->SetValue(OuterClass, TEXT("IncludePath"), TEXT("CameraDriver.h"));
				MetaData->SetValue(OuterClass, TEXT("ModuleRelativePath"), TEXT("Private/CameraDriver.h"));
				MetaData->SetValue(OuterClass, TEXT("ToolTip"), TEXT("Camera Driver Class"));
				MetaData->SetValue(NewProp_CacheCount, TEXT("Category"), TEXT("Debug"));
				MetaData->SetValue(NewProp_CacheCount, TEXT("ModuleRelativePath"), TEXT("Private/CameraDriver.h"));
				MetaData->SetValue(NewProp_AutoResetCache, TEXT("Category"), TEXT("Debug"));
				MetaData->SetValue(NewProp_AutoResetCache, TEXT("ModuleRelativePath"), TEXT("Private/CameraDriver.h"));
				MetaData->SetValue(NewProp_ResetCache, TEXT("Category"), TEXT("Debug"));
				MetaData->SetValue(NewProp_ResetCache, TEXT("ModuleRelativePath"), TEXT("Private/CameraDriver.h"));
				MetaData->SetValue(NewProp_FrameDelay, TEXT("Category"), TEXT("Debug"));
				MetaData->SetValue(NewProp_FrameDelay, TEXT("ModuleRelativePath"), TEXT("Private/CameraDriver.h"));
				MetaData->SetValue(NewProp_CameraPawn, TEXT("Category"), TEXT("Cine Camera"));
				MetaData->SetValue(NewProp_CameraPawn, TEXT("ModuleRelativePath"), TEXT("Private/CameraDriver.h"));
				MetaData->SetValue(NewProp_Port_IOS, TEXT("Category"), TEXT("Network"));
				MetaData->SetValue(NewProp_Port_IOS, TEXT("ModuleRelativePath"), TEXT("Private/CameraDriver.h"));
				MetaData->SetValue(NewProp_IPAddress_IOS, TEXT("Category"), TEXT("Network"));
				MetaData->SetValue(NewProp_IPAddress_IOS, TEXT("ModuleRelativePath"), TEXT("Private/CameraDriver.h"));
				MetaData->SetValue(NewProp_Port, TEXT("Category"), TEXT("Network"));
				MetaData->SetValue(NewProp_Port, TEXT("ModuleRelativePath"), TEXT("Private/CameraDriver.h"));
				MetaData->SetValue(NewProp_IPAddress, TEXT("Category"), TEXT("Network"));
				MetaData->SetValue(NewProp_IPAddress, TEXT("ModuleRelativePath"), TEXT("Private/CameraDriver.h"));
#endif
			}
		}
		check(OuterClass->GetClass());
		return OuterClass;
	}
	IMPLEMENT_CLASS(ACameraDriver, 3913196809);
	static FCompiledInDefer Z_CompiledInDefer_UClass_ACameraDriver(Z_Construct_UClass_ACameraDriver, &ACameraDriver::StaticClass, TEXT("/Script/CineX"), TEXT("ACameraDriver"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ACameraDriver);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
PRAGMA_ENABLE_OPTIMIZATION
