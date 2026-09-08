// PUBGm GL/KR/VN/TW - 64bit (4.5.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Functions
//---------------------By BangJO---------------------------

// Function Common_UIPopupBG.Common_UIPopupBG_C.Construct
// (BlueprintCosmetic, Event, Public, BlueprintEvent)

void UCommon_UIPopupBG_C::Construct()
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Common_UIPopupBG.Common_UIPopupBG_C.Construct");

	UCommon_UIPopupBG_C_Construct_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function Common_UIPopupBG.Common_UIPopupBG_C.ExecuteUbergraph_Common_UIPopupBG
// ()
// Parameters:
// int EntryPoint (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UCommon_UIPopupBG_C::ExecuteUbergraph_Common_UIPopupBG(int EntryPoint)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Common_UIPopupBG.Common_UIPopupBG_C.ExecuteUbergraph_Common_UIPopupBG");

	UCommon_UIPopupBG_C_ExecuteUbergraph_Common_UIPopupBG_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


}

