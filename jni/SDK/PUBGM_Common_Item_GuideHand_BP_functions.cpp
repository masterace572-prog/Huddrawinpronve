// PUBGm GL/KR/VN/TW - 64bit (4.5.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Functions
//---------------------By BangJO---------------------------

// Function Common_Item_GuideHand_BP.Common_Item_GuideHand_BP_C.OnReleaseItemCallback__DelegateSignature
// (Public, Delegate, BlueprintCallable, BlueprintEvent)

void UCommon_Item_GuideHand_BP_C::OnReleaseItemCallback__DelegateSignature()
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Common_Item_GuideHand_BP.Common_Item_GuideHand_BP_C.OnReleaseItemCallback__DelegateSignature");

	UCommon_Item_GuideHand_BP_C_OnReleaseItemCallback__DelegateSignature_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function Common_Item_GuideHand_BP.Common_Item_GuideHand_BP_C.OnPressItemCallback__DelegateSignature
// (Public, Delegate, BlueprintCallable, BlueprintEvent)

void UCommon_Item_GuideHand_BP_C::OnPressItemCallback__DelegateSignature()
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Common_Item_GuideHand_BP.Common_Item_GuideHand_BP_C.OnPressItemCallback__DelegateSignature");

	UCommon_Item_GuideHand_BP_C_OnPressItemCallback__DelegateSignature_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function Common_Item_GuideHand_BP.Common_Item_GuideHand_BP_C.OnClickItemCallback__DelegateSignature
// (Public, Delegate, BlueprintCallable, BlueprintEvent)
// Parameters:
// int resID (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UCommon_Item_GuideHand_BP_C::OnClickItemCallback__DelegateSignature(int resID)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Common_Item_GuideHand_BP.Common_Item_GuideHand_BP_C.OnClickItemCallback__DelegateSignature");

	UCommon_Item_GuideHand_BP_C_OnClickItemCallback__DelegateSignature_Params params;
	params.resID = resID;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


}

