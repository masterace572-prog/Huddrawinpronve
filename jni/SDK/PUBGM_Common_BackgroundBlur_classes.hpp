#pragma once

// PUBGm GL/KR/VN/TW - 64bit (4.5.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// WidgetBlueprintGeneratedClass Common_BackgroundBlur.Common_BackgroundBlur_C
// 0x0014 (0x042C - 0x0418)
class UCommon_BackgroundBlur_C : public UUAEUserWidget
{
public:
	struct FPointerToUberGraphFrame UberGraphFrame; // 0x0418(0x0008) (Transient, DuplicateTransient)
	class UBackgroundBlur* BlurComponent; // 0x0420(0x0008) (BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, RepNotify, Interp, NonTransactional, EditorOnly, NoDestructor, AutoWeak, ContainsInstancedReference, AssetRegistrySearchable, SimpleDisplay, AdvancedDisplay, Protected, BlueprintCallable, BlueprintAuthorityOnly, TextExportTransient, NonPIEDuplicateTransient, ExposeOnSpawn, PersistentInstance, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic, NativeAccessSpecifierProtected, NativeAccessSpecifierPrivate)
	float Component; // 0x0428(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("WidgetBlueprintGeneratedClass Common_BackgroundBlur.Common_BackgroundBlur_C");
		return pStaticClass;
	}


	void PreConstruct(bool* IsDesignTime);
	void Construct();
	void ExecuteUbergraph_Common_BackgroundBlur(int EntryPoint);
};


}

