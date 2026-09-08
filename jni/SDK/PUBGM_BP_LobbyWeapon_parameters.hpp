#pragma once

// PUBGm GL/KR/VN/TW - 64bit (4.5.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Parameters
//---------------------By BangJO---------------------------

// Function BP_LobbyWeapon.BP_LobbyWeapon_C.UnEquipWeaponPandent
struct ABP_LobbyWeapon_C_UnEquipWeaponPandent_Params
{
	EWeaponPendantSocketType PendantSocketType; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_LobbyWeapon.BP_LobbyWeapon_C.HandleIdleAnim
struct ABP_LobbyWeapon_C_HandleIdleAnim_Params
{
};

// Function BP_LobbyWeapon.BP_LobbyWeapon_C.OnDependentWeaponLoaded
struct ABP_LobbyWeapon_C_OnDependentWeaponLoaded_Params
{
};

// Function BP_LobbyWeapon.BP_LobbyWeapon_C.SetForceForbideIdleAnim
struct ABP_LobbyWeapon_C_SetForceForbideIdleAnim_Params
{
};

// Function BP_LobbyWeapon.BP_LobbyWeapon_C.RequestWeaponDIYData
struct ABP_LobbyWeapon_C_RequestWeaponDIYData_Params
{
	struct FString PlayerUID; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)
	int WeaponAvatarID; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int DIYPlanID; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_LobbyWeapon.BP_LobbyWeapon_C.OnAsyncLoadLobbyWeaponAnimDone
struct ABP_LobbyWeapon_C_OnAsyncLoadLobbyWeaponAnimDone_Params
{
};

// Function BP_LobbyWeapon.BP_LobbyWeapon_C.CheckWeaponAssetsAllLoaded
struct ABP_LobbyWeapon_C_CheckWeaponAssetsAllLoaded_Params
{
};

// Function BP_LobbyWeapon.BP_LobbyWeapon_C.ResetWeaponLoadedStatus
struct ABP_LobbyWeapon_C_ResetWeaponLoadedStatus_Params
{
};

// Function BP_LobbyWeapon.BP_LobbyWeapon_C.OnAsyncLoadLobbyWeaponMeshDone
struct ABP_LobbyWeapon_C_OnAsyncLoadLobbyWeaponMeshDone_Params
{
};

// Function BP_LobbyWeapon.BP_LobbyWeapon_C.GetWeaponAttachToBackRelativeTransformByBagLevel_Lobby
struct ABP_LobbyWeapon_C_GetWeaponAttachToBackRelativeTransformByBagLevel_Lobby_Params
{
	int* Level; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int* SideType; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FTransform ReturnValue; // (Parm, OutParm, ReturnParm, IsPlainOldData)
};

// Function BP_LobbyWeapon.BP_LobbyWeapon_C.InitMesh
struct ABP_LobbyWeapon_C_InitMesh_Params
{
	class UBattleItemHandleBase* Handle; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_LobbyWeapon.BP_LobbyWeapon_C.UserConstructionScript
struct ABP_LobbyWeapon_C_UserConstructionScript_Params
{
};

// Function BP_LobbyWeapon.BP_LobbyWeapon_C.ReceiveBeginPlay
struct ABP_LobbyWeapon_C_ReceiveBeginPlay_Params
{
};

// Function BP_LobbyWeapon.BP_LobbyWeapon_C.BPBeginPlay
struct ABP_LobbyWeapon_C_BPBeginPlay_Params
{
};

// Function BP_LobbyWeapon.BP_LobbyWeapon_C.AsyncLoadLobbyWeaponMeshDone
struct ABP_LobbyWeapon_C_AsyncLoadLobbyWeaponMeshDone_Params
{
};

// Function BP_LobbyWeapon.BP_LobbyWeapon_C.AsyncLoadLobbyWeaponAnimDone
struct ABP_LobbyWeapon_C_AsyncLoadLobbyWeaponAnimDone_Params
{
};

// Function BP_LobbyWeapon.BP_LobbyWeapon_C.ExecuteUbergraph_BP_LobbyWeapon
struct ABP_LobbyWeapon_C_ExecuteUbergraph_BP_LobbyWeapon_Params
{
	int EntryPoint; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

