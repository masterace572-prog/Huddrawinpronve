#pragma once

// PUBGm GL/KR/VN/TW - 64bit (4.5.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// AnimBlueprintGeneratedClass CH_Base_AnimBP_MainCity_HoldingHands.CH_Base_AnimBP_MainCity_HoldingHands_C
// 0x0400 (0x0FD0 - 0x0BD0)
class UCH_Base_AnimBP_MainCity_HoldingHands_C : public UHoldingHandsMCAnimInstance
{
public:
	struct FPointerToUberGraphFrame UberGraphFrame; // 0x0BD0(0x0008) (Transient, DuplicateTransient)
	struct FAnimNode_ConvertLocalToComponentSpace AnimGraphNode_LocalToComponentSpace_AC530D3E43BD416C65007395C43067DC; // 0x0BD8(0x0050)
	struct FAnimNode_ConvertComponentToLocalSpace AnimGraphNode_ComponentToLocalSpace_AB689AA340B4180BD1F1F5AB502A1A15; // 0x0C28(0x0050)
	struct FAnimNode_Root AnimGraphNode_Root_5601083E47481550BED4139293A5AEB0; // 0x0C78(0x0050)
	unsigned char UnknownData00[0x8]; // 0x0CC8(0x0008) MISSED OFFSET
	struct FAnimNode_TwoBoneIK AnimGraphNode_TwoBoneIK_BD3817674F8A314036A554ADF2BE529F; // 0x0CD0(0x01C0)
	struct FAnimNode_BlendSpacePlayer AnimGraphNode_BlendSpacePlayer_1E1405814DC17EFAA7AD17BE9F0BCA31; // 0x0E90(0x0128)
	struct FAnimParamVector AnimVelocity; // 0x0FB8(0x0018) (Edit, BlueprintVisible, DisableEditOnInstance)

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("AnimBlueprintGeneratedClass CH_Base_AnimBP_MainCity_HoldingHands.CH_Base_AnimBP_MainCity_HoldingHands_C");
		return pStaticClass;
	}


	void EvaluateGraphExposedInputs_ExecuteUbergraph_CH_Base_AnimBP_MainCity_HoldingHands_AnimGraphNode_BlendSpacePlayer_1E1405814DC17EFAA7AD17BE9F0BCA31();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_CH_Base_AnimBP_MainCity_HoldingHands_AnimGraphNode_TwoBoneIK_BD3817674F8A314036A554ADF2BE529F();
	void ExecuteUbergraph_CH_Base_AnimBP_MainCity_HoldingHands(int EntryPoint);
};


}

