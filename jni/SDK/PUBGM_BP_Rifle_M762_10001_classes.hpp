#pragma once

// PUBGm GL/KR/VN/TW - 64bit (4.5.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// BlueprintGeneratedClass BP_Rifle_M762_10001.BP_Rifle_M762_10000_C
// 0x0008 (0x0CB8 - 0x0CB0)
class ABP_Rifle_M762_10000_C : public ABP_LobbyWeapon_C
{
public:
	class ULobbyWeaponAnimList_Rifle_C* LobbyWeaponAnimList_Rifle; // 0x0CB0(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("BlueprintGeneratedClass BP_Rifle_M762_10001.BP_Rifle_M762_10000_C");
		return pStaticClass;
	}


	void UserConstructionScript();
};


}

