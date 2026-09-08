#pragma once

// PUBGm GL/KR/VN/TW - 64bit (4.5.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// BlueprintGeneratedClass BP_Rifle_M762_BattleItemHandle.BP_Rifle_M762_BattleItemHandle_C
// 0x0000 (0x0A41 - 0x0A41)
class UBP_Rifle_M762_BattleItemHandle_C : public UBattleItemHandle_MainWeapon_C
{
public:

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("BlueprintGeneratedClass BP_Rifle_M762_BattleItemHandle.BP_Rifle_M762_BattleItemHandle_C");
		return pStaticClass;
	}

};


}

