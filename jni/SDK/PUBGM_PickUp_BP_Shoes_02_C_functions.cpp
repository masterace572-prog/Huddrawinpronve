// PUBGm GL/KR/VN/TW - 64bit (4.5.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Functions
//---------------------By BangJO---------------------------

// Function PickUp_BP_Shoes_02_C.PickUp_BP_Shoes_02_C_C.UserConstructionScript
// (Event, Public, BlueprintCallable, BlueprintEvent)

void APickUp_BP_Shoes_02_C_C::UserConstructionScript()
{
	static UFunction *pFunc = nullptr;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function PickUp_BP_Shoes_02_C.PickUp_BP_Shoes_02_C_C.UserConstructionScript");

	APickUp_BP_Shoes_02_C_C_UserConstructionScript_Params params;

	auto flags = pFunc->FunctionFlags;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


}

