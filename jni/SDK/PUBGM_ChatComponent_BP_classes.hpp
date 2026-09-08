#pragma once

// PUBGm GL/KR/VN/TW - 64bit (4.5.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// BlueprintGeneratedClass ChatComponent_BP.ChatComponent_BP_C
// 0x0384 (0x087C - 0x04F8)
class UChatComponent_BP_C : public UChatComponent
{
public:
	struct FPointerToUberGraphFrame UberGraphFrame; // 0x04F8(0x0008) (Transient, DuplicateTransient)
	struct FString addToUIText; // 0x0500(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)
	TArray<struct FString> UITextArray; // 0x0510(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)
	int FirstIndex; // 0x0520(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char UnknownData00[0x4]; // 0x0524(0x0004) MISSED OFFSET
	struct FString currContentMsg; // 0x0528(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)
	bool bInitSetting; // 0x0538(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char UnknownData01[0x7]; // 0x0539(0x0007) MISSED OFFSET
	struct FString FriendChatStrGid; // 0x0540(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)
	struct FString FriendChatSenderName; // 0x0550(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)
	struct FString FriendChatContent; // 0x0560(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)
	bool FriendChatSelfMsg; // 0x0570(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char UnknownData02[0x7]; // 0x0571(0x0007) MISSED OFFSET
	struct FString FriendInviteStrGid; // 0x0578(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)
	struct FString FriendInviteSenderName; // 0x0588(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)
	struct FString FriendInviteBattleTextValue; // 0x0598(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)
	struct FString FriendReplyStrGid; // 0x05A8(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)
	struct FString FriendReplySenderName; // 0x05B8(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)
	bool FriendReplyReply; // 0x05C8(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool isMe; // 0x05C9(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char UnknownData03[0x2]; // 0x05CA(0x0002) MISSED OFFSET
	int UI_MsgID; // 0x05CC(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FString UI_ItemName; // 0x05D0(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)
	int UI_AlternateMsgID; // 0x05E0(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char UnknownData04[0x4]; // 0x05E4(0x0004) MISSED OFFSET
	class USettingConfig_C* SettingConfig; // 0x05E8(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	TArray<int> ChatFlagTypeList; // 0x05F0(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)
	TArray<int> TmpChatIDList; // 0x0600(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)
	bool bIsInfectMode; // 0x0610(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char UnknownData05[0x7]; // 0x0611(0x0007) MISSED OFFSET
	TArray<int> ChatQuikcTextIDList_HumanMenu; // 0x0618(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)
	TArray<int> ChatQuikcTextIDList_HumanTurnplate; // 0x0628(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)
	TArray<int> ChatQuikcTextIDList_ZombieMenu; // 0x0638(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)
	TArray<int> ChatQuikcTextIDList_ZombieTurnplate; // 0x0648(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)
	TArray<int> InfectModePlayerType; // 0x0658(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)
	ECharacterMainType CurInfectModePlayerType; // 0x0668(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char UnknownData06[0x3]; // 0x0669(0x0003) MISSED OFFSET
	struct FQuickChatIDAndAudio QuickChat; // 0x066C(0x000C) (Edit, BlueprintVisible, DisableEditOnInstance)
	unsigned char UnknownData07[0x50]; // 0x0678(0x0050) UNKNOWN PROPERTY: SetProperty ChatComponent_BP.ChatComponent_BP_C.GlobalActorIDList
	bool bIsVehicleWarMode; // 0x06C8(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char UnknownData08[0x7]; // 0x06C9(0x0007) MISSED OFFSET
	TArray<int> ChatQuikcTextIDList_VWMenu; // 0x06D0(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)
	TArray<int> ChatQuikcTextIDList_VWTurnplate; // 0x06E0(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)
	int TraceItemID; // 0x06F0(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char UnknownData09[0x4]; // 0x06F4(0x0004) MISSED OFFSET
	unsigned char UnknownData10[0x50]; // 0x06F4(0x0050) UNKNOWN PROPERTY: SetProperty ChatComponent_BP.ChatComponent_BP_C.MuteOnGlobal
	unsigned char UnknownData11[0x50]; // 0x0748(0x0050) UNKNOWN PROPERTY: SetProperty ChatComponent_BP.ChatComponent_BP_C.MuteMsgOnBluehole
	TArray<int> SpecialShowDistanceMsgID; // 0x0798(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)
	int MaxShowVoiceDistance; // 0x07A8(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool bIsMarkText; // 0x07AC(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char UnknownData12[0x3]; // 0x07AD(0x0003) MISSED OFFSET
	struct FString MarkText; // 0x07B0(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)
	TArray<struct FString> MarkTextArray; // 0x07C0(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)
	int addToUIMsgID; // 0x07D0(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char UnknownData13[0x4]; // 0x07D4(0x0004) MISSED OFFSET
	TMap<int, int> UIMsgIDMap; // 0x07D8(0x0050) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)
	unsigned char UnknownData14[0x50]; // 0x0828(0x0050) UNKNOWN PROPERTY: SetProperty ChatComponent_BP.ChatComponent_BP_C.CDMsgIDs
	float CDMsgDuration; // 0x0878(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass() {
        static UClass *pStaticClass = nullptr;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("BlueprintGeneratedClass ChatComponent_BP.ChatComponent_BP_C");
		return pStaticClass;
	}


	void GetIsForbidCustomChat(bool* bIsForbid);
	void PlayAutoLanguageMsg(int actorid, int MsgID);
	void CheckCDMsgs(int MsgID, bool* bIsShow);
	void AddMarkAndPlaySound(const struct FString& Name, const struct FString& Content, int MsgID, int ItemCount, int ItemId, const struct FString& PlayerKeyString, bool bIsMe, bool PlaySound, bool ShowChat, float Distance);
	void AddOneMarkToUIInner(bool bIsMe, const struct FString& TextMsg);
	void IsActorInGlobal(int actorid, bool* IsExist);
	void CheckIsAddReplyBtn(int MsgID, const struct FString& PlayerName);
	void GetSpecialDistanceString(const struct FString& SendPlayerName, struct FText* DistanceText);
	void DistanceToString(int Distance, int MsgID, const struct FString& PlayerName, struct FText* DistanceText);
	void GetActorNameByID(int actorid, struct FString* actorName);
	void GetLocalText(int MsgID, int ItemId, const struct FString& PlayerKeyString, int Distance, const struct FString& PlayerName, int ItemCount, struct FString* ContentMsg);
	void LoadVehicleModeQuickMsg();
	void IsVehicleWarMode(bool* IsVehicleWarMode);
	void InitActorIDList();
	void LoadInfectModeQuickMsg();
	void IsInfectMode(bool* IsInfectMode);
	void InitChatFlagList();
	void SetTurnplateQuickChatList();
	void GetActorBankByID(int actorid, struct FString* BankName);
	void SwitchActorAudio(int actorid);
	void LoadSingleAudio(int chatTextID);
	void LoadAllAudio();
	void CreateAudio(class UObject* audio, int resID);
	void SetQuickChatList();
	void InitFromSetting();
	void AddOneMsgToUIInner(bool isMe);
	void PlaySound(int MsgID, int actorid);
	void AddToArray();
	void AddOneMsgToUI1(struct FString* Name, struct FString* Content, int* MsgID, int* audioID, int* ItemId, struct FString* PlayerKeyString, bool* isMe, bool* PlaySound, bool* ShowChat, float* Distance);
	void NotifyFriendChat(struct FString* str_gid, struct FString* sender_name, struct FString* chat_content, bool* self_msg);
	void NotifyFriendInvite(struct FString* str_gid, struct FString* sender_name);
	void NotifyFriendReplyInvite(struct FString* str_gid, struct FString* sender_name, bool* bReply);
	void CloseChatHistoryList();
	void UpdateQuickItemText(int* MsgID, int* resID, int* alternateMsgID, int* ItemCount);
	void ReportBattleChat(int* MsgID, struct FString* Msg, int* msgExtraParam);
	void ReceiveBeginPlay();
	void AddOneMarkToUI(struct FString* Name, struct FString* Content, int* MsgID, int* audioID, int* ItemId, struct FString* PlayerKeyString, bool* isMe, bool* PlaySound, bool* ShowChat, float* Distance);
	void ExecuteUbergraph_ChatComponent_BP(int EntryPoint);
};


}

