#pragma once

// PUBGm GL/KR/VN/TW - 64bit (4.5.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Script Structs
//---------------------By BangJO---------------------------

// UserDefinedStruct BP_STRUCT_AvatarSlotTable_type.BP_STRUCT_AvatarSlotTable_type
// 0x00A8
struct FBP_STRUCT_AvatarSlotTable_type
{
	int SlotID_0_07B16B8074758AC65DD345920E3BDC84; // 0x0000(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	int TemplateID_1_2691320079AF0A7A6A1748830376BD24; // 0x0004(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	int SubSlotID_9_5DE936007C7E6AFA71E4CC580CE889E4; // 0x0008(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	int HideBoneType_12_394DA7C05E9425853B3A77F80B1DBD85; // 0x000C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	int HideBoneSlotID_13_7901AB002CDD9D2C1F43E7310DA083C4; // 0x0010(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char UnknownData00[0x4]; // 0x0014(0x0004) MISSED OFFSET
	TArray<int> ConflictConfig_a_14_4A2CF1C0416202311EA6EFBD0D3C6B21; // 0x0018(0x0010) (Edit, BlueprintVisible, ZeroConstructor)
	TArray<int> ConflictConfigWhenSelfReplaced_a_15_764E20C07104DE417E7A9EF100F1ABF1; // 0x0028(0x0010) (Edit, BlueprintVisible, ZeroConstructor)
	TArray<struct FName> HideBoneNames_an_16_39D4A7C079EDCBE52A2742700BD7AA2E; // 0x0038(0x0010) (Edit, BlueprintVisible, ZeroConstructor)
	TArray<int> HideFlags_a_17_091FE980116A8978158DCB690AD29A81; // 0x0048(0x0010) (Edit, BlueprintVisible, ZeroConstructor)
	TArray<int> RecoverHideFlagsWhenSelfHidden_a_18_030DF9003611DA621D1AA1B806165961; // 0x0058(0x0010) (Edit, BlueprintVisible, ZeroConstructor)
	TArray<int> RecoverHideFlagsWhenSelfReplaced_a_19_136E8E007DC0D0A81BF916070E83EDB1; // 0x0068(0x0010) (Edit, BlueprintVisible, ZeroConstructor)
	TArray<int> RecoverReplaceFlagsWhenSelfHidden_a_20_049729806E62479C2FFC41E800857461; // 0x0078(0x0010) (Edit, BlueprintVisible, ZeroConstructor)
	TArray<int> RecoverReplaceFlagsWhenSelfReplaced_a_21_33F73E804BB7815032938ACD0DA8EB01; // 0x0088(0x0010) (Edit, BlueprintVisible, ZeroConstructor)
	TArray<int> ReplaceFlags_a_22_7DB4DA005585940C434C0E4109C1D0F1; // 0x0098(0x0010) (Edit, BlueprintVisible, ZeroConstructor)
};

}

