#pragma once

// PUBGm GL/KR/VN/TW - 64bit (4.5.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// BlueprintGeneratedClass MinitvAvatarComponent_BP.MinitvAvatarComponent_BP_C
// 0x0000 (0x0C10 - 0x0C10)
class UMinitvAvatarComponent_BP_C : public UPetAvatarComponent
{
public:

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("BlueprintGeneratedClass MinitvAvatarComponent_BP.MinitvAvatarComponent_BP_C");
		return pStaticClass;
	}


	void RayEquipItemById(int ID);
};


}

