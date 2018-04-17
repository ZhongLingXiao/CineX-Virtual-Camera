// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "ObjectMacros.h"
#include "ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef CINEX_CineXEditorTool_generated_h
#error "CineXEditorTool.generated.h already included, missing '#pragma once' in CineXEditorTool.h"
#endif
#define CINEX_CineXEditorTool_generated_h

#define NetworkXPlugin_Plugins_CineX_Source_CineX_Public_CineXEditorTool_h_14_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execStart) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->Start(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execStop) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->Stop(); \
		P_NATIVE_END; \
	}


#define NetworkXPlugin_Plugins_CineX_Source_CineX_Public_CineXEditorTool_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execStart) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->Start(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execStop) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->Stop(); \
		P_NATIVE_END; \
	}


#define NetworkXPlugin_Plugins_CineX_Source_CineX_Public_CineXEditorTool_h_14_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUCineXEditorTool(); \
	friend CINEX_API class UClass* Z_Construct_UClass_UCineXEditorTool(); \
public: \
	DECLARE_CLASS(UCineXEditorTool, UObject, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/CineX"), NO_API) \
	DECLARE_SERIALIZER(UCineXEditorTool) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define NetworkXPlugin_Plugins_CineX_Source_CineX_Public_CineXEditorTool_h_14_INCLASS \
private: \
	static void StaticRegisterNativesUCineXEditorTool(); \
	friend CINEX_API class UClass* Z_Construct_UClass_UCineXEditorTool(); \
public: \
	DECLARE_CLASS(UCineXEditorTool, UObject, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/CineX"), NO_API) \
	DECLARE_SERIALIZER(UCineXEditorTool) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define NetworkXPlugin_Plugins_CineX_Source_CineX_Public_CineXEditorTool_h_14_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UCineXEditorTool(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UCineXEditorTool) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UCineXEditorTool); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UCineXEditorTool); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UCineXEditorTool(UCineXEditorTool&&); \
	NO_API UCineXEditorTool(const UCineXEditorTool&); \
public:


#define NetworkXPlugin_Plugins_CineX_Source_CineX_Public_CineXEditorTool_h_14_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UCineXEditorTool(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UCineXEditorTool(UCineXEditorTool&&); \
	NO_API UCineXEditorTool(const UCineXEditorTool&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UCineXEditorTool); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UCineXEditorTool); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UCineXEditorTool)


#define NetworkXPlugin_Plugins_CineX_Source_CineX_Public_CineXEditorTool_h_14_PRIVATE_PROPERTY_OFFSET
#define NetworkXPlugin_Plugins_CineX_Source_CineX_Public_CineXEditorTool_h_11_PROLOG
#define NetworkXPlugin_Plugins_CineX_Source_CineX_Public_CineXEditorTool_h_14_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	NetworkXPlugin_Plugins_CineX_Source_CineX_Public_CineXEditorTool_h_14_PRIVATE_PROPERTY_OFFSET \
	NetworkXPlugin_Plugins_CineX_Source_CineX_Public_CineXEditorTool_h_14_RPC_WRAPPERS \
	NetworkXPlugin_Plugins_CineX_Source_CineX_Public_CineXEditorTool_h_14_INCLASS \
	NetworkXPlugin_Plugins_CineX_Source_CineX_Public_CineXEditorTool_h_14_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define NetworkXPlugin_Plugins_CineX_Source_CineX_Public_CineXEditorTool_h_14_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	NetworkXPlugin_Plugins_CineX_Source_CineX_Public_CineXEditorTool_h_14_PRIVATE_PROPERTY_OFFSET \
	NetworkXPlugin_Plugins_CineX_Source_CineX_Public_CineXEditorTool_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	NetworkXPlugin_Plugins_CineX_Source_CineX_Public_CineXEditorTool_h_14_INCLASS_NO_PURE_DECLS \
	NetworkXPlugin_Plugins_CineX_Source_CineX_Public_CineXEditorTool_h_14_ENHANCED_CONSTRUCTORS \
static_assert(false, "Unknown access specifier for GENERATED_BODY() macro in class CineXEditorTool."); \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID NetworkXPlugin_Plugins_CineX_Source_CineX_Public_CineXEditorTool_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
