#include "Helper/include.h"
#include "Helper/definition.h"
#include "Helper/Items.h"
#include "Helper/bypass.h"
#include "Helper/Hit.h"
#include "Helper/KillMsg.h"
#include "Helper/Noob.h"
#include "Helper/Skin.h"

#include <fcntl.h>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <string>

json items_data;
std::map<int, bool> Items;

void DrawHUD(AHUD* HUD)
{
    if (Cheat::localPlayer && Cheat::localController)
    {
        int totalEnemies = 0;
        int totalBots = 0;
        auto AllActors = GetActors();

        for (auto& i : AllActors)
        {
            auto Actor = i;

            if (isObjectInvalid(Actor))
                continue;

            if (Actor->IsA(ASTExtraPlayerCharacter::StaticClass()))
            {
                auto Player = (ASTExtraPlayerCharacter*)Actor;
                bool IsVisible = Cheat::localController->LineOfSightTo(Player, { 0, 0, 0 }, true);

                FLinearColor White;
                FLinearColor boxColor;

                if (IsVisible)
                {
                    White = FLinearColor(0.0f, 1.0f, 0.0f, 1.0f);
                    boxColor = FLinearColor(1.0f, 1.0f, 1.0f, 0.7f);
                }
                else
                {
                    White = FLinearColor(1.0f, 0.0f, 0.0f, 1.0f);
                    boxColor = FLinearColor(1.0f, 0.0f, 0.0f, 0.7f);
                }

                float Distance = Cheat::localPlayer->GetDistanceTo(Player) / 100.0f;

                if (Player->PlayerKey == Cheat::localController->PlayerKey ||
                    Player->TeamID == Cheat::localController->TeamID ||
                    Player->bDead ||
                    Player->bHidden)
                    continue;

                if (Player->bEnsure)
                    totalBots++;
                else
                    totalEnemies++;

                auto HeadPos = Player->GetBonePos("Head", {});
                FVector2D headPosSC;
                auto RootPos = Player->GetBonePos("Root", {});
                FVector2D RootPosSC;

                if (W2S(HeadPos, &headPosSC) && W2S(RootPos, &RootPosSC))
                {
                    if (Cheat::Esp::Skeleton)
					{
    					static std::vector<std::vector<std::string>> skeleton =
    					{
        					{ "Head", "neck_01", "spine_03", "spine_02", "spine_01", "pelvis" },
        					{ "neck_01", "clavicle_r", "upperarm_r", "lowerarm_r", "hand_r", "item_r" },
        					{ "neck_01", "clavicle_l", "upperarm_l", "lowerarm_l", "hand_l", "item_l" },
        					{ "pelvis", "thigh_r", "calf_r", "foot_r" },
        					{ "pelvis", "thigh_l", "calf_l", "foot_l" }
    					};

    					for (auto& boneStructure : skeleton)
    					{
        					std::string lastBone;
        for (std::string& currentBone : boneStructure)
        {
            if (!lastBone.empty())
            {
                FVector2D boneFrom, boneTo;
                if (W2S(Player->GetBonePos(lastBone.c_str(), {}), &boneFrom) &&
                    W2S(Player->GetBonePos(currentBone.c_str(), {}), &boneTo))
                {
                    HUD->DrawLine(boneFrom.X, boneFrom.Y, boneTo.X, boneTo.Y, White, 1.5f);
                }
            }
            lastBone = currentBone;
        }
    }

    // Draw circle on head as before
    FVector head3D = Player->GetBonePos("Head", {});
    FVector2D headPos2D;
    if (W2S(head3D, &headPos2D))
    {
        FVector top3D = head3D;
        top3D.Z += 15.0f;
        FVector2D top2D;
        if (W2S(top3D, &top2D))
        {
            float radius = FVector2D::Distance(headPos2D, top2D);
            DrawCircleHelper(HUD, headPos2D.X, headPos2D.Y, radius, White, 36, 1.5f);
        }
    }
}

                    float height = fabs(RootPosSC.Y - headPosSC.Y);
                    float extraTop = height * 0.10f;
                    float totalHeight = height + extraTop;
                    float width = totalHeight / 2.0f;
                    float x = headPosSC.X - width / 2.0f;
                    float y = headPosSC.Y - extraTop;

                    if (Cheat::Esp::Box)
                    {
                        Box4LineHUD(HUD, x, y, width, totalHeight, 1.2f, 0.25f / 2.0f, boxColor);
                    }

                    if (Cheat::Esp::Health)
                    {
                        float CurHP = std::max(0.f, std::min(Player->Health, Player->HealthMax));
                        float MaxHP = Player->HealthMax;
                        float KnockHealth = Player->NearDeathBreath;
                        float HealthPercentage = CurHP / MaxHP;

                        FLinearColor HPColor;
                        if (CurHP > 70.0f)
                            HPColor = FLinearColor(0.0f, 0.7f, 0.8f, 1.0f);
                        else if (CurHP > 30.0f)
                            HPColor = FLinearColor(1.0f, 1.0f, 0.0f, 1.0f);
                        else if (CurHP > 0.0f)
                            HPColor = FLinearColor(1.0f, 0.0f, 0.0f, 1.0f);
                        else
                        {
                            HPColor = FLinearColor(0.5f, 0.0f, 0.0f, 1.0f);
                            HealthPercentage = KnockHealth / MaxHP;
                        }

                        float BarHeight = totalHeight;
                        float BarWidth = 3.0f;
                        float spacing = width * 0.1f;

                        float BarX = x - BarWidth - spacing;
                        float BarY = y;

                        DrawFilledRectangle(HUD, FVector2D(BarX, BarY), BarWidth, BarHeight, FLinearColor(0.f, 0.f, 0.f, 0.5f));

                        float FilledHeight = BarHeight * HealthPercentage;
                        float FilledY = BarY + (BarHeight - FilledHeight);
                        DrawFilledRectangle(HUD, FVector2D(BarX, FilledY), BarWidth, FilledHeight, HPColor);
                    }

                    if (Cheat::Esp::Line)
                    {
                        float lineStartX = (float)glWidth / 2;
                        float lineStartY = 0.0f;
                        float lineEndX = headPosSC.X;
                        float lineEndY = y - 5.0f;
                        HUD->DrawLine(lineStartX, lineStartY, lineEndX, lineEndY, White, 1.5f);
                    }

                    if (Cheat::Esp::Name || Cheat::Esp::Distance)
                    {
                        tslFont->LegacyFontSize = 10;

                        float textX = x + (width / 2.0f);
                        float textY = y + totalHeight + 4.0f;

                        if (Cheat::Esp::Name)
                        {
                            if (!Player->bEnsure)
                                DrawOutlinedText(HUD, Player->PlayerName, FVector2D(textX, textY), COLOR_WHITE, COLOR_BLACK, true);
                            else
                                DrawOutlinedText(HUD, FString("Bot"), FVector2D(textX, textY), COLOR_WHITE, COLOR_BLACK, true);

                            textY += 14.0f;
                        }

                        if (Cheat::Esp::Distance)
                        {
                            std::string distanceStr = std::to_string((int)Distance) + " M";
                            DrawOutlinedText(HUD, FString(distanceStr.c_str()), FVector2D(textX, textY), COLOR_YELLOW, COLOR_BLACK, true);
                        }

                        tslFont->LegacyFontSize = TSL_FONT_DEFAULT_SIZE;
                    }
                }
            }

            if (Cheat::Esp::Vehicle::Name && i->IsA(ASTExtraVehicleBase::StaticClass()))
            {
                auto Vehicle = (ASTExtraVehicleBase*)i;
                if (!Vehicle->Mesh)
                    continue;

                float Distance = Vehicle->GetDistanceTo(Cheat::localPlayer) / 100.f;

                FVector2D vehiclePos;
                if (W2S(Vehicle->K2_GetActorLocation(), &vehiclePos))
                {
                    float mWidthScale = std::min(0.10f * Distance, 50.f);
                    float mWidth = 70.f - mWidthScale;

                    std::string nameStr = GetVehicleName(Vehicle);
                    std::string distStr = std::to_string((int)Distance) + "M";

                    FLinearColor WhiteColor(1.0f, 1.0f, 0.0f, 1.0f);
                    tslFont->LegacyFontSize = 10;

                    DrawOutlinedText(HUD, FString(nameStr.c_str()), { vehiclePos.X - (mWidth / 2), vehiclePos.Y }, WhiteColor, COLOR_BLACK, true);
                    DrawOutlinedText(HUD, FString(distStr.c_str()), { vehiclePos.X - (mWidth / 2), vehiclePos.Y + 14 }, WhiteColor, COLOR_BLACK, true);

                    tslFont->LegacyFontSize = TSL_FONT_DEFAULT_SIZE;
                }
            }
			
			if (Cheat::Esp::Throwable)
            {
                if (Actor->IsA(ASTExtraGrenadeBase::StaticClass()))
                {
                    auto Grenade = (ASTExtraGrenadeBase*)Actor;
                    if (!Grenade->RootComponent)
                        continue;

                    float Distance = Grenade->GetDistanceTo(Cheat::localPlayer) / 100.f;
                    if (Distance > 50.f)
                        continue;

                    FVector2D grenadePos;
                    if (W2S(Grenade->K2_GetActorLocation(), &grenadePos))
                    {
                        tslFont->LegacyFontSize = 10;

                        DrawOutlinedText(HUD, FString("Nade"), FVector2D(grenadePos.X, grenadePos.Y),
                                         FLinearColor(1.0f, 0.0f, 0.0f, 1.0f), COLOR_BLACK, true);

                        std::string distStr = " " + std::to_string((int)Distance) + "M";
                        DrawOutlinedText(HUD, FString(distStr.c_str()), FVector2D(grenadePos.X, grenadePos.Y + 14),
                                         FLinearColor(1.0f, 0.0f, 0.0f, 1.0f), COLOR_BLACK, true);

                        tslFont->LegacyFontSize = TSL_FONT_DEFAULT_SIZE;
                    }
                }
            }

            if (Cheat::Esp::LootBox)
            {
                if (Actor->IsA(APickUpListWrapperActor::StaticClass()))
                {
                    auto Pick = (APickUpListWrapperActor*)Actor;
                    if (!Pick->RootComponent)
                        continue;

                    float Distance = Pick->GetDistanceTo(Cheat::localPlayer) / 100.f;
                    if (Distance > 50.f)
                        continue;

                    FVector2D boxPos;
                    if (W2S(Pick->K2_GetActorLocation(), &boxPos))
                    {
                        tslFont->LegacyFontSize = 10;

                        DrawOutlinedText(HUD, FString("Death Box"), FVector2D(boxPos.X, boxPos.Y),
                                         FLinearColor(0.0f, 1.0f, 0.0f, 1.0f), COLOR_BLACK, true);

                        std::string distStr = " " + std::to_string((int)Distance) + "M";
                        DrawOutlinedText(HUD, FString(distStr.c_str()), FVector2D(boxPos.X, boxPos.Y + 14),
                                         FLinearColor(0.0f, 1.0f, 0.0f, 1.0f), COLOR_BLACK, true);

                        tslFont->LegacyFontSize = TSL_FONT_DEFAULT_SIZE;
                    }
                }
            }

            if (Actor->IsA(APickUpWrapperActor::StaticClass()))
            {
                auto PickUp = (APickUpWrapperActor*)Actor;

                if (Items[PickUp->DefineID.TypeSpecificID])
                {
                    auto RootComponent = PickUp->RootComponent;
                    if (!RootComponent)
                        continue;

                    float Distance = PickUp->GetDistanceTo(Cheat::localPlayer) / 100.f;
                    if (Distance > 30.0f)
                        continue;

                    FVector2D itemPos;
                    if (W2S(PickUp->K2_GetActorLocation(), &itemPos))
                    {
                        std::string itemName;
                        uint32_t textColor = 0xFFFFFFFF;

                        for (auto& category : items_data)
                        {
                            for (auto& item : category["Items"])
                            {
                                if (item["itemId"] == PickUp->DefineID.TypeSpecificID)
                                {
                                    itemName = item["itemName"].get<std::string>();
                                    textColor = strtoul(item["itemTextColor"].get<std::string>().c_str(), 0, 16);
                                    break;
                                }
                            }
                        }

                        tslFont->LegacyFontSize = 10;

                        DrawOutlinedText(HUD, FString(itemName.c_str()), FVector2D(itemPos.X, itemPos.Y),
                                         UIntToLinearColor(textColor), COLOR_BLACK, true);

                        std::string distText = " " + std::to_string((int)Distance) + " M";
                        uint32_t distanceColor = 0xFFAAAAAA;
                        DrawOutlinedText(HUD, FString(distText.c_str()), FVector2D(itemPos.X, itemPos.Y + 12.0f),
                                         UIntToLinearColor(distanceColor), COLOR_BLACK, true);

                        tslFont->LegacyFontSize = TSL_FONT_DEFAULT_SIZE;
                    }
                }
            }
        }

        if (Cheat::Esp::Counter)
        {
            int totalEntities = totalEnemies + totalBots;
            if (totalEntities > 0)
            {
                std::string s = "  " + std::to_string(totalEntities);
                tslFont->LegacyFontSize = 20;
                DrawOutlinedText(HUD, FString(s), FVector2D((float)glWidth / 2.0f - 1, 110),
                                 COLOR_RED, COLOR_BLACK, true);
                tslFont->LegacyFontSize = TSL_FONT_DEFAULT_SIZE;
            }
        }
    }
}

void DrawMemory()
{
    if (Cheat::localPlayer && Cheat::localController)
    {
        if (Cheat::Aimbot::Enable)
        {
            ASTExtraPlayerCharacter* Target = GetTargetForAimBot();

            if (Target)
            {
                bool triggerOk = true;
                triggerOk = Cheat::localPlayer->bIsWeaponFiring;

                if (triggerOk)
                {
                    FVector targetAimPos = Target->GetBonePos("Head", {});
                    targetAimPos.Z -= 22.0f;

                    auto WeaponManagerComponent = Cheat::localPlayer->WeaponManagerComponent;

                    if (WeaponManagerComponent)
                    {
                        auto propSlot = WeaponManagerComponent->GetCurrentUsingPropSlot();

                        if ((int)propSlot.GetValue() >= 1 && (int)propSlot.GetValue() <= 3)
                        {
                            auto CurrentWeaponReplicated = (ASTExtraShootWeapon*)WeaponManagerComponent->CurrentWeaponReplicated;

                            if (CurrentWeaponReplicated)
                            {
                                auto ShootWeaponComponent = CurrentWeaponReplicated->ShootWeaponComponent;

                                if (ShootWeaponComponent)
                                {
                                    UShootWeaponEntity* ShootWeaponEntityComponent = ShootWeaponComponent->ShootWeaponEntityComponent;

                                    if (ShootWeaponEntityComponent)
                                    {
                                        ASTExtraVehicleBase* CurrentVehicle = Target->CurrentVehicle;

                                        if (CurrentVehicle)
                                        {
                                            FVector LinearVelocity = CurrentVehicle->ReplicatedMovement.LinearVelocity;
                                            float dist = Cheat::localPlayer->GetDistanceTo(Target);
                                            auto timeToTravel = dist / ShootWeaponEntityComponent->BulletFireSpeed;
                                            targetAimPos = UKismetMathLibrary::Add_VectorVector(
                                                targetAimPos,
                                                UKismetMathLibrary::Multiply_VectorFloat(LinearVelocity, timeToTravel)
                                            );
                                        }
                                        else
                                        {
                                            FVector Velocity = Target->GetVelocity();
                                            float dist = Cheat::localPlayer->GetDistanceTo(Target);
                                            auto timeToTravel = dist / ShootWeaponEntityComponent->BulletFireSpeed;
                                            targetAimPos = UKismetMathLibrary::Add_VectorVector(
                                                targetAimPos,
                                                UKismetMathLibrary::Multiply_VectorFloat(Velocity, timeToTravel)
                                            );
                                        }

                                        if (Cheat::localPlayer->bIsWeaponFiring)
                                        {
                                            float dist = Cheat::localPlayer->GetDistanceTo(Target) / 100.f;
                                            targetAimPos.Z -= dist * Cheat::Aimbot::Recoil;
                                        }

                                        FVector fDir = UKismetMathLibrary::Subtract_VectorVector(
                                            targetAimPos,
                                            Cheat::localController->PlayerCameraManager->CameraCache.POV.Location
                                        );

                                        FRotator Yaptr = UKismetMathLibrary::Conv_VectorToRotator(fDir);
                                        FRotator CpYaT = Cheat::localController->PlayerCameraManager->CameraCache.POV.Rotation;

                                        Yaptr.Pitch -= CpYaT.Pitch;
                                        Yaptr.Yaw -= CpYaT.Yaw;
                                        Yaptr.Roll = 0.f;

                                        NekoHook(Yaptr);

                                        CpYaT.Pitch += Yaptr.Pitch / Xs;
                                        CpYaT.Yaw += Yaptr.Yaw / Ys;
                                        CpYaT.Roll = 0.f;

                                        Cheat::localController->SetControlRotation(CpYaT, "");
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        static USTExtraGameInstance* Instance = nullptr;
        if (!Instance)
        {
            Instance = UObject::FindObject<USTExtraGameInstance>("STExtraGameInstance Transient.UAEGameEngine_1.STExtraGameInstance_1");
            if (Instance != nullptr)
            {
                auto& UserSettings = Instance->UserDetailSetting;
                UserSettings.PUBGDeviceFPSDef = 120;
                UserSettings.PUBGDeviceFPSLow = 120;
                UserSettings.PUBGDeviceFPSMid = 120;
                UserSettings.PUBGDeviceFPSHigh = 120;
                UserSettings.PUBGDeviceFPSHDR = 120;
                UserSettings.PUBGDeviceFPSUltralHigh = 120;
                UserSettings.DeviceMaxQualityLevel = 3;
            }
        }

static ULocalPlayer *UlocalPlayer = nullptr;
    if (!UlocalPlayer)
    {
        UlocalPlayer = UObject::FindObject<ULocalPlayer>("LocalPlayer Transient.UAEGameEngine_1.LocalPlayer_1");
    }

    if (UlocalPlayer == nullptr)
        return;



    static auto OrigView = UlocalPlayer->AspectRatioAxisConstraint;
    if (Cheat::Memory::Wide)
    {
        UlocalPlayer->AspectRatioAxisConstraint = EAspectRatioAxisConstraint::AspectRatio_MaintainYFOV;
    }
    else
    {
        if (UlocalPlayer->AspectRatioAxisConstraint != OrigView)
        {
            UlocalPlayer->AspectRatioAxisConstraint = OrigView;
        }
    }
	
        if (Cheat::Memory::Hit)
        {
            TriggerHitEffect();
        }

        if (Cheat::Memory::Wide)
        {
            uintptr_t localPlayer = (uintptr_t)Cheat::localPlayer;

            if (localPlayer)
            {
                uintptr_t cameraComponent = *(uintptr_t*)(localPlayer + 0x1C08);

                if (cameraComponent)
                {
                    *(float*)(cameraComponent + 0x33C) = 140.0f;
                }
            }
        }

        if (Cheat::Memory::Small)
        {
            auto WeaponManagerComponent = Cheat::localPlayer->WeaponManagerComponent;

            if (WeaponManagerComponent)
            {
                auto propSlot = WeaponManagerComponent->GetCurrentUsingPropSlot();

                if ((int)propSlot.GetValue() >= 1 && (int)propSlot.GetValue() <= 3)
                {
                    auto CurrentWeaponReplicated = (ASTExtraShootWeapon*)WeaponManagerComponent->CurrentWeaponReplicated;

                    if (CurrentWeaponReplicated)
                    {
                        auto ShootWeaponComponent = CurrentWeaponReplicated->ShootWeaponComponent;

                        if (ShootWeaponComponent)
                        {
                            UShootWeaponEntity* ShootWeaponEntityComponent = ShootWeaponComponent->ShootWeaponEntityComponent;

                            if (ShootWeaponEntityComponent && Cheat::Memory::Small)
                            {
                                ShootWeaponEntityComponent->GameDeviationFactor = 0.0f;
                            }
                        }
                    }
                }
            }
        }
    }
}

void AutoEspOn() 
{
    Cheat::Esp::Line = true;
    Cheat::Esp::Name = true;
    Cheat::Esp::Distance = true;
    Cheat::Esp::Health = true;
    Cheat::Esp::Skeleton = true;
    Cheat::Esp::Box = true;
	Cheat::Esp::LootBox = true;
	Cheat::Esp::Throwable = true;
    Cheat::Esp::Target = true;
	Cheat::Esp::Counter = true;
    Cheat::Esp::Vehicle::Name = true;
	
  //   Cheat::Aimbot::Enable = true;
 //   Cheat::Memory::Hit = true;
 //   Cheat::Memory::Wide = true;
    Cheat::Memory::Skin = true;
	
	Cheat::Memory::Small = true;
	//Cheat::Memory::Magic = true;
	//Cheat::Aimbot::Enable = true;
	Cheat::BulletTrack::Enable = true;
	Cheat::BulletTrack::Range = 600.0f;
	
    for (auto &i : items_data) 
    {
        int itemCount = 0;
        for (auto &item : i[("Items")]) 
        {
            item[("itemName")].get<std::string>().c_str();
            Items[item[("itemId")].get<int>()] = true;
            itemCount++;

            if (itemCount % 4 != 0 && &item != &i[("Items")].back()){}
        }
    }
}

// ============================================================
// ReceiveDrawHUD — direct offset hook (no ProcessEvent)
// Replace 0x0 with the actual ReceiveDrawHUD offset in libUE4.so
// ============================================================
#define RECEIVE_DRAW_HUD_OFFSET 0x0  // TODO: set real offset

void (*oReceiveDrawHUD)(AHUD *pHUD, int SizeX, int SizeY);
void hkReceiveDrawHUD(AHUD *pHUD, int SizeX, int SizeY)
{
    if (pHUD)
    {
        RenderESPPRIVATE(pHUD, SizeX, SizeY);
        DrawHUD(pHUD);
        DrawMemory();
        SkinHack();
    }
    oReceiveDrawHUD(pHUD, SizeX, SizeY);
}

void initOffset()
{
    // Hook ReceiveDrawHUD directly at its offset
    A64HookFunction((void *)(Cheat::libUE4Base + RECEIVE_DRAW_HUD_OFFSET),
                    (void *)hkReceiveDrawHUD, (void **)&oReceiveDrawHUD);
}

void *RunGame(void *) 
{
    Cheat::libUE4Base = Tools::GetBaseAddress("libUE4.so");

    while (!Cheat::libUE4Base) 
    {
        Cheat::libUE4Base = Tools::GetBaseAddress("libUE4.so");
        sleep(1);
    }

    FName::GNames = GetGNames();

    while (!FName::GNames) 
    {
        FName::GNames = GetGNames();
        sleep(1);
    }

    UObject::GUObjectArray = (FUObjectArray *)(Cheat::libUE4Base + Cheat::GUObject_Offset);
    
    initOffset();
    	A64HookFunction((void *)(Cheat::libUE4Base + 0x66B1FFC), (void *)shoot_event, (void **)&orig_shoot_event);
	A64HookFunction((void *)(Cheat::libUE4Base + 0x5E6A910), (void *)hook__kill_message, (void **)&orig_kill_message);
	
	//DobbyHook((void *)(Cheat::libUE4Base + 0x62F9640), (void *)shoot_event, (void **)&orig_shoot_event);
	
    items_data = json::parse(JSON_ITEMS);
    AutoEspOn();

    return nullptr;
}

__attribute__ ((constructor))
void _init() 
{
    pthread_create(&t, NULL, RunGame, NULL);
}
