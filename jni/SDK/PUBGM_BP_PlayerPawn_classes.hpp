#pragma once

// PUBGm GL/KR/VN/TW - 64bit (4.5.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// BlueprintGeneratedClass BP_PlayerPawn.BP_PlayerPawn_C
// 0x02B8 (0x76A8 - 0x73F0)
class ABP_PlayerPawn_C : public ASTExtraPlayerCharacter
{
public:
	struct FPointerToUberGraphFrame UberGraphFrame; // 0x73F0(0x0008) (Transient, DuplicateTransient)
	class UBP_CharacterSearchOtherComp_C* BP_CharacterSearchOtherComp; // 0x73F8(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class UStaticMeshComponent* ScopeStaticMesh; // 0x7400(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class UScopeCameraComponent* ScopingCameraNew; // 0x7408(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class UCharacterFollowComponent_C* CharacterFollowComponent; // 0x7410(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class UCharacterAnimShareParamsComp* CharacterAnimShareParamsComp; // 0x7418(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class UBP_PlayEmoteComponent_C* BP_PlayEmoteComponent; // 0x7420(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class UCharacterBoundCapsuleComonent* MeshBoundCapsuleComonent; // 0x7428(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class UDynamicOptimizeCharacterComps_C* DynamicOptimizeCharacterComps; // 0x7430(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class UBP_CharacterCarryBackComp_C* BP_CharacterCarryBackComp; // 0x7438(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class UBP_SkillManagerComponent_C* BP_SkillManagerComponent; // 0x7440(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class UCustomCameraComponent* Camera; // 0x7448(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class UCapsuleComponent* ShareBounds; // 0x7450(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class UCharacterAnimList_Skill_C* CharacterAnimList_Skill; // 0x7458(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class UStaticMeshComponent* SCOPE; // 0x7460(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class UPostProcessComponent* PostProcess; // 0x7468(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class USpringArmComponent* ShoulderCameraSpringArm; // 0x7470(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class USceneComponent* ShoulderCameraOffset; // 0x7478(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class UCharacterAnimList_Base_C* CharacterAnimList_Base; // 0x7480(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class UPetComponent_BP_C* PetComponent_BP; // 0x7488(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class UCharacterAvatarComp2_BP_C* CharacterAvatarComp2_BP; // 0x7490(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class UObserverCameraComponent* ObserverCameraFPPMode; // 0x7498(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class UFPPSpringArmComponent* FPPSpringArm; // 0x74A0(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class UFPPComponent_C* FPPComponent; // 0x74A8(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class UParticleSystemComponent* ParticleSystem; // 0x74B0(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class USpringArmComponent* ScopingSpringArm; // 0x74B8(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class UCapsuleComponent* HitBox_Prone; // 0x74C0(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class UCapsuleComponent* HitBox_Stand; // 0x74C8(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class UVault_Controller_C* Vault_Controller; // 0x74D0(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class UBP_SwimController_C* BP_SwimController; // 0x74D8(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class UBP_AutoAimingComponent_C* BP_AutoAimingComponent; // 0x74E0(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class UCharacterWeaponManagerComponent* CharacterWeaponManager; // 0x74E8(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class UPickupManagerComponent* PickupManager; // 0x74F0(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class USceneComponent* CameraRoot; // 0x74F8(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class UCustomSpringArmComponent* CustomSpringArm; // 0x7500(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class UCameraSettingComponent_C* CameraSettingComponent; // 0x7508(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float ScopeTimeline_NewTrack_1_FBCE53A7433799FDD4E08AA77C9DCE27; // 0x7510(0x0004) (ZeroConstructor, IsPlainOldData)
	TEnumAsByte<enum ETimelineDirection> ScopeTimeline__Direction_FBCE53A7433799FDD4E08AA77C9DCE27; // 0x7514(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char UnknownData00[0x3]; // 0x7515(0x0003) MISSED OFFSET
	class UTimelineComponent* ScopeTimeline; // 0x7518(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool IsReloading; // 0x7520(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char UnknownData01[0x3]; // 0x7521(0x0003) MISSED OFFSET
	float ReloadingCDMax; // 0x7524(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool Jumped; // 0x7528(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	TEnumAsByte<enum EPlayerCameraMode> CurCameraMode; // 0x7529(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char UnknownData02[0x2]; // 0x752A(0x0002) MISSED OFFSET
	struct FSTR_CameraSetting StandCameraSetting; // 0x752C(0x0014) (Edit, BlueprintVisible, DisableEditOnInstance)
	struct FVector Normal; // 0x7540(0x000C) (Edit, BlueprintVisible, DisableEditOnInstance, IsPlainOldData)
	unsigned char UnknownData03[0x4]; // 0x754C(0x0004) MISSED OFFSET
	class APickUpWrapperActor* PickUpTarget_1; // 0x7550(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnTemplate, DisableEditOnInstance, IsPlainOldData)
	bool bIsPicking; // 0x7558(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char UnknownData04[0x3]; // 0x7559(0x0003) MISSED OFFSET
	float DefaultCapsuleRadius; // 0x755C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class USkeletalMeshComponent* ParachuteComponent_1; // 0x7560(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	TArray<class USpringArmComponent*> SpringArms; // 0x7568(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)
	TArray<class UCameraComponent*> Cameras; // 0x7578(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)
	class USpringArmComponent* CurActiveSpringArm; // 0x7588(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class USpringArmComponent* NewVar_1; // 0x7590(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	TEnumAsByte<enum ESTEPoseState> CurPoseState; // 0x7598(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char UnknownData05[0x7]; // 0x7599(0x0007) MISSED OFFSET
	TMap<int, class UBackpackEmoteHandle*> EmoteBPIDToAnimHandleMap; // 0x75A0(0x0050) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)
	class UParticleSystem* DecentBloodSpot; // 0x75F0(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UParticleSystem* BloodSpot_Red; // 0x75F8(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UParticleSystem* BloodSpot_Green; // 0x7600(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	TArray<EPawnState> DisallowedWateringStates; // 0x7608(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)
	class UChildActorComponent* PaintDecalDetectComp; // 0x7618(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class ASTExtraWeapon* CurUseingEmoteWeapon; // 0x7620(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnTemplate, DisableEditOnInstance, IsPlainOldData)
	class UMaterialBillboardComponent* FrameUIBillboard; // 0x7628(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool bIsAngledSightOnlyTurn_1; // 0x7630(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char UnknownData06[0x7]; // 0x7631(0x0007) MISSED OFFSET
	class UMeshComponent* OriginAttachComponent; // 0x7638(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UMeshComponent* TargetAttachComponent; // 0x7640(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FRotator OriginRotOffset; // 0x7648(0x000C) (Edit, BlueprintVisible, DisableEditOnInstance, IsPlainOldData)
	struct FDollyZoomParam OriginDollyZoomParam; // 0x7654(0x000C) (Edit, BlueprintVisible, DisableEditOnInstance)
	struct FDollyZoomParam TargetDollyZoomParam; // 0x7660(0x000C) (Edit, BlueprintVisible, DisableEditOnInstance)
	unsigned char UnknownData07[0x4]; // 0x766C(0x0004) MISSED OFFSET
	struct FName HurtSoundSwitchState; // 0x7670(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FVector BloodScale; // 0x7678(0x000C) (Edit, BlueprintVisible, DisableEditOnInstance, IsPlainOldData)
	unsigned char UnknownData08[0x4]; // 0x7684(0x0004) MISSED OFFSET
	struct FScriptMulticastDelegate OnCakePlacement; // 0x7688(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, BlueprintAssignable)
	class UPhysicsAsset* ShootPhysicsAssetOpt; // 0x7698(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class UPhysicsAsset* ShootPhysicsAsset; // 0x76A0(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("BlueprintGeneratedClass BP_PlayerPawn.BP_PlayerPawn_C");
		return pStaticClass;
	}


	void ShowScreenDamage(float Damage, TEnumAsByte<enum EDamageType> DamageEventType);
	void GetBattleItemHandlePath(int ItemId, struct FString* EmotePath);
	void RefreshWeaponSight();
	void HandleOnLandedSetAutoSprint();
	void ChangeParticleEffect(class UParticleSystemComponent* Particle, const struct FVector& _3DScale);
	void SpawnEmitterEffect(const struct FVector& RelativeLocation, class UParticleSystem* PSRef, class USceneComponent* AttachParent, const struct FVector& RelativeScale);
	struct FString GetEmoteHandlePath(int* ItemId);
	void Replay_IsEnemyFrameUIExisted(bool* bIsExisted);
	void HandleOnLanded(float ForceLandTime);
	void GetGameModeState(struct FName* CurModeState);
	void SetTpCameraFov(float FOV);
	void SetCapsuleParentBounds(bool UseParentBounds);
	void ClearDecalBakingRTCache();
	bool IsAngledSightAvailable();
	void RefreshAngledSightUI(bool HaveAngledSight, bool IsAngledSight);
	void ShowAngledSightState(bool IsAngled);
	void GetAngledSightRotator(class ASTExtraShootWeapon* NewParam, struct FRotator* NewParam1);
	void AngledSightAnimLogic(TEnumAsByte<enum EAngledSightType> Selection);
	void AngledSightAnimUpdate(float InputPin, bool bIsOnlyTurn);
	void Replay_CreateEnemyFrameUI(bool isPlayingCompletePlayback, bool is_enemy);
	void Replay_SetVisiableOfFrameUI(bool is_Visiable);
	void UpdateEmoteWeaponIdInfo(int ID, bool* Ret);
	void AllowWater(bool* bCanEnter);
	bool ShouldRedBlood();
	void CheckHasVehicleAvatar(class ASTExtraVehicleBase* InVehicle, class ASTExtraBaseCharacter* PlayerCharacter, int* InItemID);
	void ChangeCurVehicleAvatar(class ASTExtraVehicleBase* InVehicle);
	void HandleOnChangedVehicleSeat();
	void GetMasterBoneComponent(class UMeshComponent** MasterBoneComponent);
	void InitDefaultAvatarByResID(int AGender, int Head, int hair);
	void GetGrenadeCameraShakeByDir(const struct FVector& ImpulseDir, class UClass** RetVar);
	class UBackpackEmoteHandle* GetEmoteHandle(int* ItemId);
	struct FString GetShootWeaponNameByWeapon(int* ItemDefineID);
	class UCameraComponent* GetThirdPersonCamera();
	class USpringArmComponent* GetThirdPersonSpringArm();
	class UCameraComponent* GetFPPCamera();
	class USpringArmComponent* GetFPPSpringArm();
	class UCameraComponent* GetFirstPersonCamera();
	class USpringArmComponent* GetFirstPersonSpringArm();
	class UCameraComponent* GetScopeCamera();
	class USpringArmComponent* GetScopeSpringArm();
	bool ShouldAutoScopeWhenPeek();
	void GetControllerViewCamera(class UCameraComponent** Camera);
	void HandleOnDetachedVehicle(class ASTExtraVehicleBase* NewParam);
	void HandleOnAttachedVehicle(class ASTExtraVehicleBase* InVehicle);
	class USpringArmComponent* GetActiveSpringArm();
	void AimInterupted();
	void GetWeapon(struct FVector* NewParam, struct FRotator* NewParam1, bool* bHaveWeapon);
	void ResetBPCameraSetting();
	void ShowDebugArrow(class USceneComponent* self2, const struct FRotator& InRot, const struct FLinearColor& Color);
	void IsAutonomous(bool* NewParam);
	void PickUp(class APickUpWrapperActor* NewParam);
	void DoPickUpTarget();
	void RotateMesh(const struct FRotator& NewParam);
	void SetAllCollisionEnabled(bool bEnable);
	void MoveOutScope();
	void MoveInScope();
	void Reload();
	void SwitchCrouch(TEnumAsByte<enum ESTEPoseState> NewParam, TEnumAsByte<enum ESTEPoseState> preState);
	void UserConstructionScript();
	void ScopeTimeline__FinishedFunc();
	void ScopeTimeline__UpdateFunc();
	void OnPetOwnerPossessed();
	void ReceiveBeginPlay();
	void BPNotifyStartDying(class AController** Killer, class AActor** DamageCauser, struct FHitResult* KillingHitInfo, struct FVector* KillingHitImpulseDir, class UClass** KillingHitDamageType);
	void ReloadEvent();
	void OnEquipWeapon(TEnumAsByte<enum ESurviveWeaponPropSlot>* Slot);
	void OnNotifyHurt();
	void OnLanded(struct FHitResult* Hit);
	void OnPoseStateChange(TEnumAsByte<enum ESTEPoseState>* LastState, TEnumAsByte<enum ESTEPoseState>* CurState);
	void BPReceiveDamage(float* Damage, class UDamageType** DamageType, class AController** InstigatedBy, class AActor** DamageCauser, TEnumAsByte<enum EDamageType>* DamageEventType);
	void ParachuteOnWater();
	void OnUnEquipWeapon();
	void PawnVaultServerBluePrint(float* dis, float* Height, float* Length, struct FString* VaultKey, struct FVector* StartPos, class AActor** checkActor, float* crossblockMaxFall, float* crossblockMaxDis, struct FVector* HitPoint, class AActor** WindowActor, struct FRotator* movedir);
	void PawnVaultAllBluePrint(float* dis, float* Height, float* Length, struct FString* VaultKey, struct FVector* StartPos, class AActor** checkActor, float* crossblockMaxFall, float* crossblockMaxDis, struct FVector* HitPoint, struct FRotator* movedir);
	void ScopeInStop();
	void PlayScopeInTimeline(float Rate);
	void BPReceiveRadialDamage(float* DamageReceived, class UDamageType** DamageType, struct FVector* Origin, float* Radius, struct FHitResult* HitInfo, class AController** InstigatedBy, class AActor** DamageCauser, struct FVector* ImpulseDir);
	void ReceivePossessed(class AController** NewController);
	void ParachutePlaySound(class UAkAudioEvent** LocalAkEvent, class UAkAudioEvent** RemoteAkEvent);
	void OnWeaponEquipmentUpdate();
	void BindAndExecStateChanged();
	void StateEnterHandler_Event_1(EPawnState State);
	void OnHitByCake();
	void EnablePet(bool* Enable);
	void OnEnterStateForBp(EPawnState* State);
	void OnLeaveStateForBp(EPawnState* State);
	void ReceiveDestroyed();
	void PawnVaultServerStopCheckBluePrint();
	void PawnVaultStopBluePrint();
	void SwitchSightAngledLocal(TEnumAsByte<enum EAngledSightType>* Type, bool* IsOnlyTurn);
	void DoAngledSight(bool IsPush);
	void DoNormalSight(bool IsPush);
	void StopSwitchAngledSight();
	void CustomEvent_4(class ASTExtraShootWeapon* Weapon, EWeaponAttachmentSocketType Type, bool bEquip);
	void CustomEvent_1(bool bIsBegin);
	void OnVehicleStateChange();
	void OnBPStateCheckIn();
	void LuaReceiveBeginPlay();
	void SwitchRearSight(int PrevIndex, int NewIndex, const struct FRotator& AngleRotator);
	void BPOnRespawned();
	void RemoveRemainingCameraBlood(int SeatType);
	void DoWeaponSight();
	void SetWeaponSightStateLocal(bool* IsOpenWeaponSight);
	void RearSightTimeLineUpdate(float* Alpha);
	void RearSightTimeLineFinish(int* InRearSightNewIndex);
	void AngleSightTimeLineUpdate(float* Alpha);
	void AngleSightTimeLineFinish();
	void DoAutoReloadCurrentWeapon(class ASTExtraShootWeapon** ShootWeapon);
	void ExecuteUbergraph_BP_PlayerPawn(int EntryPoint);
	void OnCakePlacement__DelegateSignature(bool Success);
};


}

