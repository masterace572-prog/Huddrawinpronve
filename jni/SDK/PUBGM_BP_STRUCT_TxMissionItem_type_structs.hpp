#pragma once

// PUBGm GL/KR/VN/TW - 64bit (4.5.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Script Structs
//---------------------By BangJO---------------------------

// UserDefinedStruct BP_STRUCT_TxMissionItem_type.BP_STRUCT_TxMissionItem_type
// 0x0108
struct FBP_STRUCT_TxMissionItem_type
{
	int CanIntoBag_22_4CB022404DD2516D09C4D91507CFA9B7; // 0x0000(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	int ItemID_1_49D5BBC036F518BF132AF653050D6844; // 0x0004(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	int ItemSubType_2_15150B807AF16BF04C3005AA03E776D5; // 0x0008(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	int ItemType_3_5EC3E1003A3CA896478837AE0D6B3565; // 0x000C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FString PrepareSlot_4_698B91003CDC5D227A5C466801DD7194; // 0x0010(0x0010) (Edit, BlueprintVisible, ZeroConstructor)
	int SellPrice_5_621695804D11035272FF41330D8ED645; // 0x0020(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char UnknownData00[0x4]; // 0x0024(0x0004) MISSED OFFSET
	struct FString Slot1_6_746CA9806AFCAACC23F44A07095A68E1; // 0x0028(0x0010) (Edit, BlueprintVisible, ZeroConstructor)
	struct FString Slot2_7_746DA9C06AFCAACD23F44A04095A68E2; // 0x0038(0x0010) (Edit, BlueprintVisible, ZeroConstructor)
	struct FString Slot3_8_746EAA006AFCAACE23F44A05095A68E3; // 0x0048(0x0010) (Edit, BlueprintVisible, ZeroConstructor)
	struct FString Slot4_9_746FAA406AFCAACF23F44A0A095A68E4; // 0x0058(0x0010) (Edit, BlueprintVisible, ZeroConstructor)
	struct FString Slot5_10_7470AA806AFCAAD023F44A0B095A68E5; // 0x0068(0x0010) (Edit, BlueprintVisible, ZeroConstructor)
	struct FString Slot6_11_7471AAC06AFCAAD123F44A08095A68E6; // 0x0078(0x0010) (Edit, BlueprintVisible, ZeroConstructor)
	int WardrobeTab_12_38B7080075734EE21C3835B902055C52; // 0x0088(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	int BagCapacity_14_468DE2C025B9F7E751AD7D4A012FA5B9; // 0x008C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	int repairCost_15_6610BBC03F3023E569DB8D610F912D24; // 0x0090(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	int repairMoneyId_16_0E88A2C0056A94F16EEE93850CFC34D4; // 0x0094(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	int totalDurability_17_39D98400075A715045B5AB1F0377F729; // 0x0098(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float weight_f_18_6FD34800316B3CBE1A7790E80C146F86; // 0x009C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	int QuickBuyTabID_19_7B1B89005D48F5BE18AA52A7042B7014; // 0x00A0(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool IsPrecious_20_2CF9964006DAB2D121665C31012D0953; // 0x00A4(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool CannotTakeOut_21_3A9EBCC02ADED9154DC85630037A8914; // 0x00A5(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char UnknownData01[0x2]; // 0x00A6(0x0002) MISSED OFFSET
	int EquipType_23_7ED5DE4074147FC76016CB60069D0C95; // 0x00A8(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char UnknownData02[0x4]; // 0x00AC(0x0004) MISSED OFFSET
	struct FString Slot7_24_7472AB006AFCAAD223F44A09095A68E7; // 0x00B0(0x0010) (Edit, BlueprintVisible, ZeroConstructor)
	struct FString Slot8_25_7473AB406AFCAAD323F44A0E095A68E8; // 0x00C0(0x0010) (Edit, BlueprintVisible, ZeroConstructor)
	struct FString SpecialDesc_26_6D5064C0495420574A8DA476063AB993; // 0x00D0(0x0010) (Edit, BlueprintVisible, ZeroConstructor)
	struct FString Slot9_27_7474AB806AFCAAD423F44A0F095A68E9; // 0x00E0(0x0010) (Edit, BlueprintVisible, ZeroConstructor)
	struct FString TacticalAccessoryIcon_28_205D6B406EF3DB432FE284610532FEFE; // 0x00F0(0x0010) (Edit, BlueprintVisible, ZeroConstructor)
	bool OBReport_29_278BB8003EFBC7AE2309AF94006603A4; // 0x0100(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool IsReturnTeammate_30_37F00F400278E3B33D9410770E6BA465; // 0x0101(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool CannotPutIntoSafetyBox_31_562C27802A3450601BE0A2C20E637D28; // 0x0102(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char UnknownData03[0x1]; // 0x0103(0x0001) MISSED OFFSET
	int RedpacketItemId_32_5665A8800D1F9E54799B8CD90EF478F4; // 0x0104(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
};

}

