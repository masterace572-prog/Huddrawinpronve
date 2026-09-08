// PUBGm GL/KR/VN/TW - 64bit (4.5.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Functions
//---------------------By BangJO---------------------------

// Function Common_Collect_Level_UIBP.Common_Collect_Level_UIBP_C.PreConstruct
// (BlueprintCosmetic, Event, Public, BlueprintEvent)
// Parameters:
// bool* IsDesignTime (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UCommon_Collect_Level_UIBP_C::PreConstruct(bool* IsDesignTime)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Common_Collect_Level_UIBP.Common_Collect_Level_UIBP_C.PreConstruct");

	UCommon_Collect_Level_UIBP_C_PreConstruct_Params params;
	params.IsDesignTime = IsDesignTime;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function Common_Collect_Level_UIBP.Common_Collect_Level_UIBP_C.ExecuteUbergraph_Common_Collect_Level_UIBP
// ()
// Parameters:
// int EntryPoint (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UCommon_Collect_Level_UIBP_C::ExecuteUbergraph_Common_Collect_Level_UIBP(int EntryPoint)
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function Common_Collect_Level_UIBP.Common_Collect_Level_UIBP_C.ExecuteUbergraph_Common_Collect_Level_UIBP");

	UCommon_Collect_Level_UIBP_C_ExecuteUbergraph_Common_Collect_Level_UIBP_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


}

