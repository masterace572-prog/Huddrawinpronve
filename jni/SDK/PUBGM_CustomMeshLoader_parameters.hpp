#pragma once

// PUBGm GL/KR/VN/TW - 64bit (4.5.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Parameters
//---------------------By BangJO---------------------------

// Function CustomMeshLoader.CustomMeshLoaderBPLibrary.LoadSModelFromMemory
struct UCustomMeshLoaderBPLibrary_LoadSModelFromMemory_Params
{
	TArray<unsigned char> Data; // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
	struct FString MeshName; // (Parm, ZeroConstructor)
	TArray<class UMaterialInstance*> Materials; // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
	class UStaticMesh* ReturnValue; // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function CustomMeshLoader.CustomMeshLoaderBPLibrary.LoadSModelFileAsync
struct UCustomMeshLoaderBPLibrary_LoadSModelFileAsync_Params
{
	struct FString FilePath; // (Parm, ZeroConstructor)
	struct FString MeshName; // (Parm, ZeroConstructor)
	struct FScriptDelegate OnComplete; // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
};

// Function CustomMeshLoader.CustomMeshLoaderBPLibrary.LoadSModelFile
struct UCustomMeshLoaderBPLibrary_LoadSModelFile_Params
{
	struct FString FilePath; // (Parm, ZeroConstructor)
	struct FString MeshName; // (Parm, ZeroConstructor)
	class UStaticMesh* ReturnValue; // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function CustomMeshLoader.CustomMeshLoaderBPLibrary.IsValidSModelFile
struct UCustomMeshLoaderBPLibrary_IsValidSModelFile_Params
{
	struct FString FilePath; // (Parm, ZeroConstructor)
	bool ReturnValue; // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function CustomMeshLoader.CustomMeshLoaderBPLibrary.GetSModelFileInfo
struct UCustomMeshLoaderBPLibrary_GetSModelFileInfo_Params
{
	struct FString FilePath; // (Parm, ZeroConstructor)
	int OutSectionCount; // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	int OutMaterialCount; // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	int OutVertexCount; // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	bool ReturnValue; // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function CustomMeshLoader.CustomMeshLoaderBPLibrary.DumpStaticMeshVertexDataByPath
struct UCustomMeshLoaderBPLibrary_DumpStaticMeshVertexDataByPath_Params
{
	struct FString MeshAssetPath; // (Parm, ZeroConstructor)
	struct FString OutputFilePath; // (Parm, ZeroConstructor)
	int LODIndex; // (Parm, ZeroConstructor, IsPlainOldData)
	int MaxVertices; // (Parm, ZeroConstructor, IsPlainOldData)
	struct FString ReturnValue; // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function CustomMeshLoader.CustomMeshLoaderBPLibrary.DumpStaticMeshVertexData
struct UCustomMeshLoaderBPLibrary_DumpStaticMeshVertexData_Params
{
	class UStaticMesh* Mesh; // (Parm, ZeroConstructor, IsPlainOldData)
	struct FString OutputFilePath; // (Parm, ZeroConstructor)
	int LODIndex; // (Parm, ZeroConstructor, IsPlainOldData)
	int MaxVertices; // (Parm, ZeroConstructor, IsPlainOldData)
	struct FString ReturnValue; // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

}

