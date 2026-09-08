#include "Helper/include.h"
#include "Helper/definition.h"
#include "Helper/Items.h"
#include "Helper/bypass.h"
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
        
if (Cheat::Aimbot::Enable) {
    // 获取瞄准目标
    ASTExtraPlayerCharacter *Target = GetTargetForAimBot();
    // 目标有效时的处理
    if (Target) {
    bool triggerOk = false;
   if (Cheat::Aimbot::Trigger == EAimTrigger::None) {
triggerOk = Cheat::localPlayer->bIsWeaponFiring;
}
if (Cheat::Aimbot::Trigger == EAimTrigger::Scoping) {
triggerOk = Cheat::localPlayer->bIsGunADS;
}
if (Cheat::Aimbot::Trigger == EAimTrigger::Both) {
triggerOk = Cheat::localPlayer->bIsWeaponFiring || Cheat::localPlayer->bIsGunADS;
}
if (triggerOk) {
FVector targetAimPos;
 if (Cheat::Aimbot::Target == EAimTarget::Head) {
 targetAimPos = Target->GetBonePos("Head", {0, 0, 0});
  }

 if (Cheat::Aimbot::Target == EAimTarget::Chest) {
 targetAimPos = Target->GetBonePos("upperarm_r", {0, 0, 0});
}
switch (Cheat::Aimbot::Target == EAimTarget::Head) {
                            case 1:
                                targetAimPos = Target->GetBonePos("Head", {});
                                break;
                            case 2:
                                targetAimPos = Target->GetBonePos("pelvis", {});
                                break;
                            case 3:
                                targetAimPos = Target->GetBonePos("calf_l", {});
                                break;
                            case 4:
                                targetAimPos = Target->GetBonePos("calf_r", {});
                                break;
                            case 5:
                                targetAimPos = Target->GetBonePos("lowerarm_l", {});
                                break;
                            case 6:
                                targetAimPos = Target->GetBonePos("lowerarm_r", {});
                                break;
                            case 7:
                                targetAimPos = Target->GetBonePos("upperarm_l", {});
                                break;
                            case 8:
                                targetAimPos = Target->GetBonePos("upperarm_r", {});
                                break;
                            case 9:
                                targetAimPos = Target->GetBonePos("thigh_l", {});
                                break;
                            case 10:
                                targetAimPos = Target->GetBonePos("thigh_r", {});
                                break;
                            case 11:
                                targetAimPos = Target->GetBonePos("foot_l", {});
                                break;
                            case 12:
                                targetAimPos = Target->GetBonePos("foot_r", {});
                                break;
                            default:
                                targetAimPos = Target->GetBonePos("Head", {});
                                break;
                        }
                        if(Cheat::Aimbot::Target == EAimTarget::Chest){
                        if(算法 == 0) {
                        targetAimPos = Target->GetBonePos("Head", {});//头
                        }else if(算法 == 1) {
                        targetAimPos = Target->GetBonePos("spine_03", {});//脖子
                        }else if(算法 == 2){
                        targetAimPos = Target->GetBonePos("pelvis", {});//屁股
                        }else if(算法 == 3){
                        targetAimPos = Target->GetBonePos("calf_l", {});//左小腿
                        }else if(算法 == 4){
                        targetAimPos = Target->GetBonePos("calf_r", {});//右小腿
                        }else if(算法 == 5){
                        targetAimPos = Target->GetBonePos("lowerarm_l", {});//左小臂
                        }else if(算法 == 6){
                        targetAimPos = Target->GetBonePos("lowerarm_r", {});//右小臂
                        }else if(算法 == 7){
                        targetAimPos = Target->GetBonePos("upperarm_l", {});//左上臂
                        }else if(算法 == 8){
                        targetAimPos = Target->GetBonePos("upperarm_r", {});//右上臂
                        }else if(算法 == 9) {
                        targetAimPos = Target->GetBonePos("thigh_l", {});//左大腿
                        }else if(算法 == 10) {
                        targetAimPos = Target->GetBonePos("thigh_r", {});//右大腿
                        }else if(算法 == 11) {
                        targetAimPos = Target->GetBonePos("foot_l", {});//左脚
                        }else if(算法 == 12){
                        targetAimPos = Target->GetBonePos("foot_r", {});//右脚
                        }
                        }        
            
            
            if (targetAimPos.X > 0 && targetAimPos.Y > 0 && targetAimPos.Z > 0) {
    auto WeaponManagerComponent = Cheat::localPlayer->WeaponManagerComponent;
    if (WeaponManagerComponent) {
        auto propSlot = WeaponManagerComponent->GetCurrentUsingPropSlot();
        if ((int) propSlot.GetValue() >= 1 && (int) propSlot.GetValue() <= 3) {
            auto CurrentWeaponReplicated = (ASTExtraShootWeapon *) WeaponManagerComponent->CurrentWeaponReplicated;
            if (CurrentWeaponReplicated) {
                auto ShootWeaponComponent = CurrentWeaponReplicated->ShootWeaponComponent;
                auto ShootWeaponEffectComp = CurrentWeaponReplicated->ShootWeaponEffectComp;
                if (ShootWeaponComponent) {
                    UShootWeaponEntity *ShootWeaponEntityComponent = ShootWeaponComponent->ShootWeaponEntityComponent;
                    if (ShootWeaponEntityComponent) {
                        // Get bullet fire speed using offset 0x408
                        float BulletFireSpeed = *(float*)((uintptr_t)ShootWeaponEntityComponent + 0x560);
                        
                        ASTExtraVehicleBase *CurrentVehicle = Target->CurrentVehicle;
                        if (CurrentVehicle) {
                            FVector LinearVelocity = CurrentVehicle->ReplicatedMovement.LinearVelocity;
                            float dist = Cheat::localPlayer->GetDistanceTo(Target);
                            auto timeToTravel = dist / BulletFireSpeed;  // Using BulletFireSpeed instead of BulletRange
                            targetAimPos = UKismetMathLibrary::Add_VectorVector(targetAimPos, UKismetMathLibrary::Multiply_VectorFloat(LinearVelocity, timeToTravel));
                            targetAimPos.Z += LinearVelocity.Z * timeToTravel + 0.5 * 573.f * timeToTravel * timeToTravel;
                        } else {
                            FVector Velocity = Target->GetVelocity();
                            float dist = Cheat::localPlayer->GetDistanceTo(Target);
                            auto timeToTravel = dist / BulletFireSpeed;  // Using BulletFireSpeed instead of BulletRange
                            targetAimPos = UKismetMathLibrary::Add_VectorVector(targetAimPos, UKismetMathLibrary::Multiply_VectorFloat(Velocity, timeToTravel));
                            targetAimPos.Z += Velocity.Z * timeToTravel + 0.5 * 573.f * timeToTravel * timeToTravel;
                        }
                        
                        if (Cheat::localPlayer->bIsWeaponFiring)
                        {
                            float dist = Cheat::localPlayer->GetDistanceTo(Target) / 100.f;
                            targetAimPos.Z -= dist * Cheat::Aimbot::RecoilSet;
                        }
                        
                        //开镜自瞄偏移修复(关键变量/AimControlRotationAdditive)
                        auto ControlRotator = Cheat::localController->ControlRotation;
                        auto aimRotation = ToRotator(Cheat::localController->PlayerCameraManager->CameraCache.POV.Location, targetAimPos);
                        ControlRotator.Pitch = aimRotation.Pitch - Cheat::localController->ControlRotation.Pitch - Cheat::localPlayer->AimControlRotationAdditive.Pitch / 1;
                        ControlRotator.Yaw = aimRotation.Yaw - Cheat::localController->ControlRotation.Yaw - Cheat::localPlayer->AimControlRotationAdditive.Yaw / 1;
                        
                        int 命中概率 = rand() % 101; //生成0到100的随机数
                        if (命中概率 <= 100) //设定概率
                        {
                            Cheat::localPlayer->AddControllerPitchInput(ControlRotator.Pitch);
                            Cheat::localPlayer->AddControllerYawInput(ControlRotator.Yaw);
                        }
                    }
                }
            }
        }
    }
}
        }
    }
}

       if (Cheat::Memory::XHitEffect)
        {
            if (Cheat::localController != nullptr)
{
 if (Cheat::localPlayer->bIsWeaponFiring || Cheat::localPlayer->bIsGunADS) 
 {
    auto MyHUD = (ASurviveHUD *)Cheat::localController->MyHUD;
    if (MyHUD == nullptr)
        return;
FLinearColor interpolatedColor = RandomColor();


    auto hitPerformPtr = &MyHUD->HitPerform;

    uintptr_t hitPerformAddress = *(uintptr_t *)(uintptr_t)hitPerformPtr;

    *(float *)((uintptr_t)hitPerformAddress + 0x10) = 99999.0f;
    *(float *)((uintptr_t)hitPerformAddress + 0x50) = 99999.0f;
    *(float *)((uintptr_t)hitPerformAddress + 0x90) = 99999.0f;
    *(float *)((uintptr_t)hitPerformAddress + 0xD0) = 99999.0f;

    MyHUD->SetHitPerformColor(EHitPerformColorType::EHitPerformColor_Head, interpolatedColor);
    MyHUD->SetHitPerformColor(EHitPerformColorType::EHitPerformColor_Body, interpolatedColor);
    Cheat::Memory::XHitEffect = true;
}
}
        }
        
        if (Cheat::localController != 0)
        {
        
           // Cheat::Memory::XHitEffect = true;
            
        }
        else
        {
           // Cheat::Memory::XHitEffect = false;

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
                                FLinearColor interpolatedColor = RandomColor();
                              //  ShootWeaponEntityComponent->GameDeviationFactor = 0.0f;
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
  //  Cheat::Esp::Target = true;
	Cheat::Esp::Counter = true;
    Cheat::Esp::Vehicle::Name = true;
    
  //  Cheat::BulletTrack::Enable = true;
    
    Cheat::Aimbot::Enable = true;
    Cheat::Aimbot::RecoilSet = 1.045f;
    Cheat::Aimbot::VisCheck = true;
    Cheat::Aimbot::IgnoreKnock = true;
    Cheat::Aimbot::Target = Chest;
	
	Cheat::Memory::Small = true;
	
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




void (*oReceiveDrawHUD)(AHUD *pHUD, int SizeX, int SizeY);
void hkReceiveDrawHUD(AHUD *pHUD, int SizeX, int SizeY)
{
    if (pHUD)
    {
        RenderESPPRIVATE(pHUD, SizeX, SizeY);
        DrawHUD(pHUD);
        DrawMemory();
    }
    oReceiveDrawHUD(pHUD, SizeX, SizeY);
}


void (*ShootBulletInner)(uintptr_t Weapon, FVector StartLoc, FRotator StartRot, int ShootID);
void xShootBulletInner(uintptr_t Weapon, FVector StartLoc, FRotator StartRot, int ShootID)
{
    if (Cheat::BulletTrack::Enable)
    {
        ASTExtraPlayerCharacter* Target = GetTargetForAimBot();
        if (Target)
        {
            FVector targetAimPos = Target->GetBonePos("Head", {});
            targetAimPos.Z -= -19.0f;   // same as targetAimPos.Z += 19.0f
            FRotator adjustedRot = ToRotator(StartLoc, targetAimPos);
            return ShootBulletInner(Weapon, StartLoc, adjustedRot, ShootID);
        }
    }
    return ShootBulletInner(Weapon, StartLoc, StartRot, ShootID);
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
    
    shadowhook_init(shadowhook_mode_t::SHADOWHOOK_MODE_UNIQUE, 0);
    
    shadowhook_hook_func_addr((void *)(Cheat::libUE4Base + 0x6BB0CFC), (void *)xShootBulletInner, (void **)&ShootBulletInner);
    
   shadowhook_hook_func_addr((void *)(Cheat::libUE4Base + 0xAA8E774), (void *)hkReceiveDrawHUD, (void **)&oReceiveDrawHUD);
   
    items_data = json::parse(JSON_ITEMS);
    AutoEspOn();

    return nullptr;
}

__attribute__ ((constructor))
void _init() 
{
    pthread_create(&t, NULL, RunGame, NULL);
}
