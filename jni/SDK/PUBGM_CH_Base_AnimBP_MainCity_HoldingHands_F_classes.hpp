#pragma once

// PUBGm GL/KR/VN/TW - 64bit (4.5.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// AnimBlueprintGeneratedClass CH_Base_AnimBP_MainCity_HoldingHands_F.CH_Base_AnimBP_MainCity_HoldingHands_F_C
// 0x0C5C (0x182C - 0x0BD0)
class UCH_Base_AnimBP_MainCity_HoldingHands_F_C : public UHoldingHandsMCAnimInstance
{
public:
	struct FPointerToUberGraphFrame UberGraphFrame; // 0x0BD0(0x0008) (Transient, DuplicateTransient)
	struct FAnimNode_SimpleIKSolver AnimGraphNode_SimpleIKSolver_B3D0F9F94CC22A1FF16EACAF430D5378; // 0x0BD8(0x01A8)
	struct FAnimNode_ConvertLocalToComponentSpace AnimGraphNode_LocalToComponentSpace_7B96BCD1425E3F55AF5231813CBCEB21; // 0x0D80(0x0050)
	struct FAnimNode_ConvertComponentToLocalSpace AnimGraphNode_ComponentToLocalSpace_00DE825C4D43499FFA7D44A6F91C0003; // 0x0DD0(0x0050)
	struct FAnimNode_Fabrik AnimGraphNode_Fabrik_A46E136942B80F2789AD22A01DE63E68; // 0x0E20(0x01B0)
	struct FAnimNode_Root AnimGraphNode_Root_1BC1E6014FF40CCF23254F99A8E5A184; // 0x0FD0(0x0050)
	struct FAnimNode_TwoBoneIK AnimGraphNode_TwoBoneIK_6681A6DF4BEFD2E65514B48983986CE9; // 0x1020(0x01C0)
	struct FAnimNode_BlendListByEnumAdvance AnimGraphNode_BlendListByEnumAdvance_3A2038614D53C950AE7A438A48E15D1C; // 0x11E0(0x00F8)
	struct FAnimNode_ConvertComponentToLocalSpace AnimGraphNode_ComponentToLocalSpace_0B320EF4466E7335472614829F938830; // 0x12D8(0x0050)
	struct FAnimNode_ConvertLocalToComponentSpace AnimGraphNode_LocalToComponentSpace_CAC15D684EAF68F75498EE820EB523BF; // 0x1328(0x0050)
	struct FAnimNode_BlendListByBool AnimGraphNode_BlendListByBool_B2BE1E12445F893020F9FC852C1CBEFB; // 0x1378(0x00D0)
	struct FAnimNode_SaveCachedPose AnimGraphNode_SaveCachedPose_1349ABF64528B4035DB8E09D5F52535E; // 0x1448(0x00C0)
	struct FAnimNode_UseCachedPose AnimGraphNode_UseCachedPose_377B98B04BFF21DD8C7F53A4E7FE94B4; // 0x1508(0x0058)
	struct FAnimNode_UseCachedPose AnimGraphNode_UseCachedPose_BBDECA6346272751E365E386EF564268; // 0x1560(0x0058)
	struct FAnimNode_BlendSpacePlayer AnimGraphNode_BlendSpacePlayer_0B7D5B7F48E055EF1F9D0F9D519D10B7; // 0x15B8(0x0128)
	struct FAnimNode_BlendSpacePlayer AnimGraphNode_BlendSpacePlayer_36EFF0AD455D1087D005EE9679924173; // 0x16E0(0x0128)
	struct FAnimParamVector AnimVelocity; // 0x1808(0x0018) (Edit, BlueprintVisible, DisableEditOnInstance)
	struct FVector TargetEffectLoc; // 0x1820(0x000C) (Edit, BlueprintVisible, IsPlainOldData)

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("AnimBlueprintGeneratedClass CH_Base_AnimBP_MainCity_HoldingHands_F.CH_Base_AnimBP_MainCity_HoldingHands_F_C");
		return pStaticClass;
	}


	void EvaluateGraphExposedInputs_ExecuteUbergraph_CH_Base_AnimBP_MainCity_HoldingHands_F_AnimGraphNode_BlendListByBool_B2BE1E12445F893020F9FC852C1CBEFB();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_CH_Base_AnimBP_MainCity_HoldingHands_F_AnimGraphNode_BlendListByEnumAdvance_3A2038614D53C950AE7A438A48E15D1C();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_CH_Base_AnimBP_MainCity_HoldingHands_F_AnimGraphNode_BlendSpacePlayer_36EFF0AD455D1087D005EE9679924173();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_CH_Base_AnimBP_MainCity_HoldingHands_F_AnimGraphNode_TwoBoneIK_6681A6DF4BEFD2E65514B48983986CE9();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_CH_Base_AnimBP_MainCity_HoldingHands_F_AnimGraphNode_Fabrik_A46E136942B80F2789AD22A01DE63E68();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_CH_Base_AnimBP_MainCity_HoldingHands_F_AnimGraphNode_SimpleIKSolver_B3D0F9F94CC22A1FF16EACAF430D5378();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_CH_Base_AnimBP_MainCity_HoldingHands_F_AnimGraphNode_BlendSpacePlayer_0B7D5B7F48E055EF1F9D0F9D519D10B7();
	void ExecuteUbergraph_CH_Base_AnimBP_MainCity_HoldingHands_F(int EntryPoint);
};


}

