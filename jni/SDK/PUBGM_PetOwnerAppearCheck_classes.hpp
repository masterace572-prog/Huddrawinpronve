#pragma once

// PUBGm GL/KR/VN/TW - 64bit (4.5.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// BlueprintGeneratedClass PetOwnerAppearCheck.PetOwnerAppearCheck_C
// 0x0000 (0x0098 - 0x0098)
class UPetOwnerAppearCheck_C : public UBTDecorator_BlueprintBase
{
public:

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("BlueprintGeneratedClass PetOwnerAppearCheck.PetOwnerAppearCheck_C");
		return pStaticClass;
	}


	bool PerformConditionCheckAI(class AAIController** OwnerController, class APawn** ControlledPawn);
};


}

