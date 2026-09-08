#pragma once

// PUBGm GL/KR/VN/TW - 64bit (4.5.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// Class CustomMeshLoader.CustomMeshLoaderBPLibrary
// 0x0000 (0x0028 - 0x0028)
class UCustomMeshLoaderBPLibrary : public UBlueprintFunctionLibrary
{
public:

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("Class CustomMeshLoader.CustomMeshLoaderBPLibrary");
		return pStaticClass;
	}


	static class UStaticMesh* LoadSModelFromMemory(TArray<unsigned char> Data, const struct FString& MeshName, TArray<class UMaterialInstance*> Materials);
	static void LoadSModelFileAsync(const struct FString& FilePath, const struct FString& MeshName, const struct FScriptDelegate& OnComplete);
	static class UStaticMesh* LoadSModelFile(const struct FString& FilePath, const struct FString& MeshName);
	static bool IsValidSModelFile(const struct FString& FilePath);
	static bool GetSModelFileInfo(const struct FString& FilePath, int* OutSectionCount, int* OutMaterialCount, int* OutVertexCount);
	static struct FString DumpStaticMeshVertexDataByPath(const struct FString& MeshAssetPath, const struct FString& OutputFilePath, int LODIndex, int MaxVertices);
	static struct FString DumpStaticMeshVertexData(class UStaticMesh* Mesh, const struct FString& OutputFilePath, int LODIndex, int MaxVertices);
};


}

