#pragma once

// PUBGm GL/KR/VN/TW - 64bit (4.5.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// BlueprintGeneratedClass PickUp_BP_Pants_06_B.PickUp_BP_Pants_06_B_C
// 0x0008 (0x0978 - 0x0970)
class APickUp_BP_Pants_06_B_C : public APickUpWrapperActor
{
public:
	class UStaticMeshComponent* Bag_03_icon; // 0x0970(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("BlueprintGeneratedClass PickUp_BP_Pants_06_B.PickUp_BP_Pants_06_B_C");
		return pStaticClass;
	}


	void UserConstructionScript();
};


}

