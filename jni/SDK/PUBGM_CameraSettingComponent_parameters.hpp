#pragma once

// PUBGm GL/KR/VN/TW - 64bit (4.5.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "PUBGM_BangJO.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Parameters
//---------------------By BangJO---------------------------

// Function CameraSettingComponent.CameraSettingComponent_C.SaveCurCameraSetting
struct UCameraSettingComponent_C_SaveCurCameraSetting_Params
{
	class USpringArmComponent* SprintArm; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function CameraSettingComponent.CameraSettingComponent_C.LerpCameraSettings
struct UCameraSettingComponent_C_LerpCameraSettings_Params
{
	float LerpAlpha; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FSTR_CameraSetting CameraSettings; // (BlueprintVisible, BlueprintReadOnly, Parm)
	class USpringArmComponent* SpringArm; // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

