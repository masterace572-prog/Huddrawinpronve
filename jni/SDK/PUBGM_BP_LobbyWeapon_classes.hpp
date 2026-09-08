#pragma once

// PUBGm GL/KR/VN/TW - 64bit (4.5.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// BlueprintGeneratedClass BP_LobbyWeapon.BP_LobbyWeapon_C
// 0x0070 (0x0CB0 - 0x0C40)
class ABP_LobbyWeapon_C : public ASTExtraLobbyWeapon
{
public:
	struct FPointerToUberGraphFrame UberGraphFrame; // 0x0C40(0x0008) (Transient, DuplicateTransient)
	class UWeaponAvatarComp_BP_C* WeaponAvatarComp_BP; // 0x0C48(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool bHoldBack; // 0x0C50(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char UnknownData00[0x7]; // 0x0C51(0x0007) MISSED OFFSET
	TMap<struct FString, struct FTransform> WeaponAttachRelativeTransformMap; // 0x0C58(0x0050) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)
	bool WeaponMeshAndMatLoaded; // 0x0CA8(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool WeaponAnimLoaded; // 0x0CA9(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool ForbiddenWeaponIdleAnim; // 0x0CAA(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char UnknownData01[0x1]; // 0x0CAB(0x0001) MISSED OFFSET
	int ShowType; // 0x0CAC(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("BlueprintGeneratedClass BP_LobbyWeapon.BP_LobbyWeapon_C");
		return pStaticClass;
	}


	void UnEquipWeaponPandent(EWeaponPendantSocketType PendantSocketType);
	void HandleIdleAnim();
	void OnDependentWeaponLoaded();
	void SetForceForbideIdleAnim();
	void RequestWeaponDIYData(const struct FString& PlayerUID, int WeaponAvatarID, int DIYPlanID);
	void OnAsyncLoadLobbyWeaponAnimDone();
	void CheckWeaponAssetsAllLoaded();
	void ResetWeaponLoadedStatus();
	void OnAsyncLoadLobbyWeaponMeshDone();
	struct FTransform GetWeaponAttachToBackRelativeTransformByBagLevel_Lobby(int* Level, int* SideType);
	void InitMesh(class UBattleItemHandleBase* Handle);
	void UserConstructionScript();
	void ReceiveBeginPlay();
	void BPBeginPlay();
	void AsyncLoadLobbyWeaponMeshDone();
	void AsyncLoadLobbyWeaponAnimDone();
	void ExecuteUbergraph_BP_LobbyWeapon(int EntryPoint);
};


}

