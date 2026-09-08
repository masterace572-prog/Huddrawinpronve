#pragma once

// PUBGm GL/KR/VN/TW - 64bit (4.5.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// BlueprintGeneratedClass BattleItemHandle_HeadBP.BattleItemHandle_HeadBP_C
// 0x0016 (0x0BA8 - 0x0B92)
class UBattleItemHandle_HeadBP_C : public UBattleItemHandle_AvatarBP_C
{
public:
	unsigned char UnknownData00[0x6]; // 0x0B92(0x0006) MISSED OFFSET
	TArray<int> BodyResIDList; // 0x0B98(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("BlueprintGeneratedClass BattleItemHandle_HeadBP.BattleItemHandle_HeadBP_C");
		return pStaticClass;
	}

};


}

