#pragma once

// PUBGm GL/KR/VN/TW - 64bit (4.5.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// AnimBlueprintGeneratedClass CH_Base_AnimBP_MainCity_CarryBack.CH_Base_AnimBP_MainCity_CarryBack_C
// 0x0758 (0x1298 - 0x0B40)
class UCH_Base_AnimBP_MainCity_CarryBack_C : public UCarryBackMCAnimInstance
{
public:
	struct FPointerToUberGraphFrame UberGraphFrame; // 0x0B40(0x0008) (Transient, DuplicateTransient)
	struct FAnimNode_LayeredBoneBlend AnimGraphNode_LayeredBoneBlend_D48CA3E34AAC530EC658CD8C3D7FB7AD; // 0x0B48(0x00E8)
	struct FAnimNode_Root AnimGraphNode_Root_0C0797F94EFEE5686EE6A9B7FD923252; // 0x0C30(0x0050)
	struct FAnimNode_BlendListByEnumAdvance AnimGraphNode_BlendListByEnumAdvance_ADD0A28246FA744CA7F17E94E86223DB; // 0x0C80(0x00F8)
	struct FAnimNode_BlendSpaceEvaluator AnimGraphNode_BlendSpaceEvaluator_CF1EE7E447A497FFE7CB6F9DE41E46B3; // 0x0D78(0x0130)
	struct FAnimNode_BlendSpaceEvaluator AnimGraphNode_BlendSpaceEvaluator_C935DFF943F5F27C29BF5F943B5D627A; // 0x0EA8(0x0130)
	struct FAnimNode_BlendSpaceEvaluator AnimGraphNode_BlendSpaceEvaluator_27CB39084A88BBCD0AA8E9AA97530339; // 0x0FD8(0x0130)
	struct FAnimNode_SaveCachedPose AnimGraphNode_SaveCachedPose_345718504A4E4C1779CE0AB05271E770; // 0x1108(0x00C0)
	struct FAnimNode_UseCachedPose AnimGraphNode_UseCachedPose_0976371B4E4973C20D2ECA8A237D4E77; // 0x11C8(0x0058)
	struct FAnimNode_UseCachedPose AnimGraphNode_UseCachedPose_260539DC447CFB39BA1BC2B3864DCCF7; // 0x1220(0x0058)
	struct FAnimParamVector Velocity; // 0x1278(0x0018) (Edit, BlueprintVisible, DisableEditOnInstance)
	class ASTExtraBaseCharacter* ClearEmpty; // 0x1290(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnTemplate, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("AnimBlueprintGeneratedClass CH_Base_AnimBP_MainCity_CarryBack.CH_Base_AnimBP_MainCity_CarryBack_C");
		return pStaticClass;
	}


	void EvaluateGraphExposedInputs_ExecuteUbergraph_CH_Base_AnimBP_MainCity_CarryBack_AnimGraphNode_BlendSpaceEvaluator_C935DFF943F5F27C29BF5F943B5D627A();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_CH_Base_AnimBP_MainCity_CarryBack_AnimGraphNode_BlendSpaceEvaluator_27CB39084A88BBCD0AA8E9AA97530339();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_CH_Base_AnimBP_MainCity_CarryBack_AnimGraphNode_BlendSpaceEvaluator_CF1EE7E447A497FFE7CB6F9DE41E46B3();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_CH_Base_AnimBP_MainCity_CarryBack_AnimGraphNode_BlendListByEnumAdvance_ADD0A28246FA744CA7F17E94E86223DB();
	void BpOnDeactived();
	void BpOnActived();
	void ExecuteUbergraph_CH_Base_AnimBP_MainCity_CarryBack(int EntryPoint);
};


}

