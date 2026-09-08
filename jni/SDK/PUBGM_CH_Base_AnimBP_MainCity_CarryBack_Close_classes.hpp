#pragma once

// PUBGm GL/KR/VN/TW - 64bit (4.5.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// AnimBlueprintGeneratedClass CH_Base_AnimBP_MainCity_CarryBack_Close.CH_Base_AnimBP_MainCity_CarryBack_Close_C
// 0x0758 (0x1298 - 0x0B40)
class UCH_Base_AnimBP_MainCity_CarryBack_Close_C : public UCarryBackMCAnimInstance
{
public:
	struct FPointerToUberGraphFrame UberGraphFrame; // 0x0B40(0x0008) (Transient, DuplicateTransient)
	struct FAnimNode_LayeredBoneBlend AnimGraphNode_LayeredBoneBlend_3E7EDFAA4BBE8AD34B3FB5AF7FE2AFC7; // 0x0B48(0x00E8)
	struct FAnimNode_Root AnimGraphNode_Root_707BFE064957FE9BAF45D7A08ED68B69; // 0x0C30(0x0050)
	struct FAnimNode_BlendListByEnumAdvance AnimGraphNode_BlendListByEnumAdvance_328EB8B6403AA8F5F59E35A268C38C94; // 0x0C80(0x00F8)
	struct FAnimNode_BlendSpaceEvaluator AnimGraphNode_BlendSpaceEvaluator_758B5B104911D34782C46DACD33A10B8; // 0x0D78(0x0130)
	struct FAnimNode_BlendSpaceEvaluator AnimGraphNode_BlendSpaceEvaluator_4786E5964EF0BA870C8A40A5A0A738E4; // 0x0EA8(0x0130)
	struct FAnimNode_BlendSpaceEvaluator AnimGraphNode_BlendSpaceEvaluator_6F97B27C4867FA6D491617A1EF887AA3; // 0x0FD8(0x0130)
	struct FAnimNode_SaveCachedPose AnimGraphNode_SaveCachedPose_B42D479A44B9CBD115D2898990A932C7; // 0x1108(0x00C0)
	struct FAnimNode_UseCachedPose AnimGraphNode_UseCachedPose_9B339396400C12D5BA556AA6652BA86A; // 0x11C8(0x0058)
	struct FAnimNode_UseCachedPose AnimGraphNode_UseCachedPose_C3AF58334844F4438929909C3019744A; // 0x1220(0x0058)
	struct FAnimParamVector Velocity; // 0x1278(0x0018) (Edit, BlueprintVisible, DisableEditOnInstance)
	class ASTExtraBaseCharacter* EmptyChar; // 0x1290(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnTemplate, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("AnimBlueprintGeneratedClass CH_Base_AnimBP_MainCity_CarryBack_Close.CH_Base_AnimBP_MainCity_CarryBack_Close_C");
		return pStaticClass;
	}


	void EvaluateGraphExposedInputs_ExecuteUbergraph_CH_Base_AnimBP_MainCity_CarryBack_Close_AnimGraphNode_BlendSpaceEvaluator_6F97B27C4867FA6D491617A1EF887AA3();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_CH_Base_AnimBP_MainCity_CarryBack_Close_AnimGraphNode_BlendSpaceEvaluator_4786E5964EF0BA870C8A40A5A0A738E4();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_CH_Base_AnimBP_MainCity_CarryBack_Close_AnimGraphNode_BlendSpaceEvaluator_758B5B104911D34782C46DACD33A10B8();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_CH_Base_AnimBP_MainCity_CarryBack_Close_AnimGraphNode_BlendListByEnumAdvance_328EB8B6403AA8F5F59E35A268C38C94();
	void BpOnDeactived();
	void BpOnActived();
	void ExecuteUbergraph_CH_Base_AnimBP_MainCity_CarryBack_Close(int EntryPoint);
};


}

