#pragma once

// PUBGm GL/KR/VN/TW - 64bit (4.5.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// AnimBlueprintGeneratedClass SK_WEP_M762_AnimBP.SK_WEP_M762_AnimBP_C
// 0x0500 (0x0A20 - 0x0520)
class USK_WEP_M762_AnimBP_C : public UWeaponAnimInstanceBase
{
public:
	struct FPointerToUberGraphFrame UberGraphFrame; // 0x0520(0x0008) (Transient, DuplicateTransient)
	struct FAnimNode_Root AnimGraphNode_Root_54EC97EA440A95CD7FB04B95D0E78C37; // 0x0528(0x0050)
	struct FAnimNode_TransitionResult AnimGraphNode_TransitionResult_EA5A53814DB29AE7CBF197A05D1B10C9; // 0x0578(0x0048)
	struct FAnimNode_TransitionResult AnimGraphNode_TransitionResult_8CEAF91845C5DA83474AAD9EDD224CEE; // 0x05C0(0x0048)
	struct FAnimNode_TransitionResult AnimGraphNode_TransitionResult_FDF0D0B741F2ABEFBE76B2B64898E3D4; // 0x0608(0x0048)
	struct FAnimNode_TransitionResult AnimGraphNode_TransitionResult_C941CB0543E0E653AFE6EE9C8186D23B; // 0x0650(0x0048)
	struct FAnimNode_SequencePlayer AnimGraphNode_SequencePlayer_98496C2A4706E279E92B8385A64172C2; // 0x0698(0x0070)
	struct FAnimNode_Root AnimGraphNode_StateResult_A2D081EE46FE96C2EA4EE4B7D2D30C4C; // 0x0708(0x0050)
	struct FAnimNode_SequencePlayer AnimGraphNode_SequencePlayer_2CF5336F44DD851C7B7E95BF5B1CA4C2; // 0x0758(0x0070)
	struct FAnimNode_Root AnimGraphNode_StateResult_D66961454722BB1CA8A0ABB7E2256273; // 0x07C8(0x0050)
	struct FAnimNode_SequencePlayer AnimGraphNode_SequencePlayer_D8CC7BB94EE8463A1FA91A8392F649A4; // 0x0818(0x0070)
	struct FAnimNode_Root AnimGraphNode_StateResult_03C2FAFF4E8EA39BB4EFD0B07DB120E4; // 0x0888(0x0050)
	struct FAnimNode_StateMachine AnimGraphNode_StateMachine_D171C9F5453652C69971B4B33BB064EC; // 0x08D8(0x00D8)
	struct FAnimNode_Slot AnimGraphNode_Slot_88072B4D4A3EE5484FA509A5D8EAF5B0; // 0x09B0(0x0070)

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("AnimBlueprintGeneratedClass SK_WEP_M762_AnimBP.SK_WEP_M762_AnimBP_C");
		return pStaticClass;
	}


	void HandleWeaponStateChanged(TEnumAsByte<enum EFreshWeaponStateType> Selection);
	void PlayFireAnim();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_SK_WEP_M762_AnimBP_AnimGraphNode_TransitionResult_FDF0D0B741F2ABEFBE76B2B64898E3D4();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_SK_WEP_M762_AnimBP_AnimGraphNode_TransitionResult_C941CB0543E0E653AFE6EE9C8186D23B();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_SK_WEP_M762_AnimBP_AnimGraphNode_SequencePlayer_98496C2A4706E279E92B8385A64172C2();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_SK_WEP_M762_AnimBP_AnimGraphNode_SequencePlayer_2CF5336F44DD851C7B7E95BF5B1CA4C2();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_SK_WEP_M762_AnimBP_AnimGraphNode_TransitionResult_EA5A53814DB29AE7CBF197A05D1B10C9();
	void OnWeaponChangeState(TEnumAsByte<enum EFreshWeaponStateType> CurState);
	void BlueprintInitializeAnimation();
	void EvaluateGraphExposedInputs_ExecuteUbergraph_SK_WEP_M762_AnimBP_AnimGraphNode_TransitionResult_8CEAF91845C5DA83474AAD9EDD224CEE();
	void ExecuteUbergraph_SK_WEP_M762_AnimBP(int EntryPoint);
};


}

