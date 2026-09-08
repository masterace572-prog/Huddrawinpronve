#pragma once

// PUBGm GL/KR/VN/TW - 64bit (4.5.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// BlueprintGeneratedClass BP_PlayerLobbyPawn.BP_PlayerLobbyPawn_C
// 0x0231 (0x0DC1 - 0x0B90)
class ABP_PlayerLobbyPawn_C : public ASTExtraLobbyCharacter
{
public:
	struct FPointerToUberGraphFrame UberGraphFrame; // 0x0B90(0x0008) (Transient, DuplicateTransient)
	class UCameraComponent* Camera; // 0x0B98(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class UBP_LobbyWeaponManager_C* BP_LobbyWeaponManager; // 0x0BA0(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class ULobbyPlayEmoteComponent_BP_C* LobbyPlayEmoteComponent_BP; // 0x0BA8(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class ULobbyWeaponAnimationComponent_C* LobbyWeaponAnimationComponent; // 0x0BB0(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class USkeletalMeshComponent* WeaponSkeletalMesh; // 0x0BB8(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class UCharacterAvatarComp2_BP_C* CharacterAvatarComp2_BP; // 0x0BC0(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class UAELobbyCharAnimListComp* AELobbyCharAnimListComp; // 0x0BC8(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float Timeline_0_Time_DFD4E0A94A64AF2CC7AD9DB7F31CA12E; // 0x0BD0(0x0004) (ZeroConstructor, IsPlainOldData)
	TEnumAsByte<enum ETimelineDirection> Timeline_0__Direction_DFD4E0A94A64AF2CC7AD9DB7F31CA12E; // 0x0BD4(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char UnknownData00[0x3]; // 0x0BD5(0x0003) MISSED OFFSET
	class UTimelineComponent* Timeline_1; // 0x0BD8(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	int headid; // 0x0BE0(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	int resID; // 0x0BE4(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool press; // 0x0BE8(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char UnknownData01[0x3]; // 0x0BE9(0x0003) MISSED OFFSET
	float LocationX; // 0x0BEC(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	TEnumAsByte<enum ETouchIndex> FingerIndex; // 0x0BF0(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char UnknownData02[0x3]; // 0x0BF1(0x0003) MISSED OFFSET
	int LobbyPosition; // 0x0BF4(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class ASTExtraWeapon* curEquipingWeapon; // 0x0BF8(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnTemplate, DisableEditOnInstance, IsPlainOldData)
	TMap<int, class UBackpackEmoteHandle*> EmoteItemIDToHandleMap; // 0x0C00(0x0050) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)
	struct FString PlayerKey; // 0x0C50(0x0010) (Edit, BlueprintVisible, ZeroConstructor)
	bool HeadIsVisible; // 0x0C60(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool canRotate; // 0x0C61(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char UnknownData03[0x2]; // 0x0C62(0x0002) MISSED OFFSET
	int LuaID; // 0x0C64(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FScriptMulticastDelegate OnPlayAction; // 0x0C68(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, BlueprintAssignable)
	struct FScriptMulticastDelegate OnStopAction; // 0x0C78(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, BlueprintAssignable)
	struct FScriptMulticastDelegate OnChangeEquipment; // 0x0C88(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, BlueprintAssignable)
	class UBackpackEmoteHandle* CurEmoteHandle; // 0x0C98(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool bIsEmoteLooping; // 0x0CA0(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char UnknownData04[0x3]; // 0x0CA1(0x0003) MISSED OFFSET
	int CurrentActionID; // 0x0CA4(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool IsChangingHead; // 0x0CA8(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char UnknownData05[0x3]; // 0x0CA9(0x0003) MISSED OFFSET
	int PlayOnChangingHeadAcionID; // 0x0CAC(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	int CurPlayEmoteId; // 0x0CB0(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool IsPlayingAction; // 0x0CB4(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char UnknownData06[0x3]; // 0x0CB5(0x0003) MISSED OFFSET
	float RotateTime; // 0x0CB8(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float TargetRotation; // 0x0CBC(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool StartRotateFlag; // 0x0CC0(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char UnknownData07[0x3]; // 0x0CC1(0x0003) MISSED OFFSET
	float ClothAnimDyAlpha; // 0x0CC4(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float CurClothAnimDyAlpha; // 0x0CC8(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float ClothAnimDyAlphaDiff; // 0x0CCC(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool isMVPMotion; // 0x0CD0(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char UnknownData08[0x7]; // 0x0CD1(0x0007) MISSED OFFSET
	struct FScriptMulticastDelegate OnchangeGender; // 0x0CD8(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, BlueprintAssignable)
	bool bEquipingSkateAircraft; // 0x0CE8(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool isAutoTest; // 0x0CE9(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char UnknownData09[0x2]; // 0x0CEA(0x0002) MISSED OFFSET
	struct FVector LocationBeforeEmote; // 0x0CEC(0x000C) (Edit, BlueprintVisible, DisableEditOnInstance, IsPlainOldData)
	float Inten; // 0x0CF8(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char UnknownData10[0x4]; // 0x0CFC(0x0004) MISSED OFFSET
	TMap<int, int> DynamicMatClothMap; // 0x0D00(0x0050) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)
	float WindSpeed_Editor; // 0x0D50(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float WindStrength_Editor; // 0x0D54(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float WindRadius_Editor; // 0x0D58(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char UnknownData11[0x4]; // 0x0D5C(0x0004) MISSED OFFSET
	class UCurveFloat* WindSpeed; // 0x0D60(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float AccumelateWindTime; // 0x0D68(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char UnknownData12[0x4]; // 0x0D6C(0x0004) MISSED OFFSET
	struct FScriptMulticastDelegate OnSceneType2Change; // 0x0D70(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, BlueprintAssignable)
	int SceneType2; // 0x0D80(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool NeedLookAtCam; // 0x0D84(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char UnknownData13[0x3]; // 0x0D85(0x0003) MISSED OFFSET
	struct FScriptMulticastDelegate OnPreChangeEquip; // 0x0D88(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, BlueprintAssignable)
	unsigned char UnknownData14[0x28]; // 0x0D98(0x0028) UNKNOWN PROPERTY: SoftObjectProperty BP_PlayerLobbyPawn.BP_PlayerLobbyPawn_C.FootLockAnimPath
	bool bIgnoreDragRotation; // 0x0DC0(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("BlueprintGeneratedClass BP_PlayerLobbyPawn.BP_PlayerLobbyPawn_C");
		return pStaticClass;
	}


	void UpdateCameraLocation();
	void SetCompRotate(class USceneComponent* RotateComp, float Rotate);
	void SetAddCharacterWeaponAnimListHandle(TArray<struct FLobbyCharacterWeaponAnimData>* addAnimData);
	void CharEquipWeaponPendant(int WeaponId, EWeaponPendantSocketType PendantSocketType);
	void WeaponAllAssetLoadFinish();
	void CharUnEquipWeaponByResId(int resID, const struct FName& SocketName);
	void CharUnEquipExtraWeapon();
	void SetForceUseDefaultIdle(bool Force);
	void UpdateClothInten(float leten);
	void UpdateClothMatParam(float RotateSpeed);
	void StopActionCamera();
	void RotateOnTickInternal();
	void GetCurrentActionID(int* ActionID);
	void OnAvatarAllMeshLoaded();
	void TryRotateAvatar();
	void SetAvatarVisibleForEmote(bool Visible);
	void RequestWeaponDIYData(const struct FString& InPlayerUID, int WeaponAvatarID, int InDIYPlanID);
	void SetIsMVPMotion(bool isMVPMotion);
	void InitDefaultAvatarByResID(int AGender, int Head, int hair);
	void SetClothAnimDyAlphaInst(float Alpha);
	void SetClothAnimDyAlphaGrad(float Alpha);
	void SetClothAnimDyAlpha(float Alpha);
	void RotateOnTick(float RotateTime, float TargetRotation);
	void OnEndActionHandle(int ActionID);
	void OnPlayActionHandle(int ActionID);
	void SetConflictRuleEnable(bool bEnableConflictRule);
	void PutOffEquipmentBySlot(EAvatarSlotType SlotType, bool* Result);
	void PlayEmoteLoop();
	void ShouldCurEmoteShowWeapon(bool* Result);
	void HandleWeaponDisplayWhenPlayEmote();
	void GetAllEquipmentList(TArray<int>* Result);
	void SetCanRotate(bool canRotate);
	void PutOffEquipmentByResID(int resID, bool* Result);
	void HideWeapon(bool isHide);
	void CharPlayEmoteByResId(int EmoteId, const struct FString& ExtraInfo);
	void CharUnEquipWeapon();
	void CharEquipWeaponByResId(int resID, bool bUse, bool bAsync, const struct FName& SocketName, class ASTExtraWeapon** Weapon);
	class UBackpackEmoteHandle* GetEmoteHandle(int* ItemId);
	void GetBPID(int RowName, int* BPID);
	void UserConstructionScript();
	void Timeline_0__FinishedFunc();
	void Timeline_0__UpdateFunc();
	void ReceiveTick(float* DeltaSeconds);
	void TickClothLeten(float From);
	void ExecuteUbergraph_BP_PlayerLobbyPawn(int EntryPoint);
	void OnPreChangeEquip__DelegateSignature();
	void OnSceneType2Change__DelegateSignature(int sceneType);
	void OnchangeGender__DelegateSignature();
	void OnChangeEquipment__DelegateSignature();
	void OnStopAction__DelegateSignature(int ActionID);
	void OnPlayAction__DelegateSignature(int ActionID);
};


}

