#include "Helper/include.h"
#include "Helper/definition.h"
#include "Helper/Items.h"
#include "Helper/bypass.h"
#include <fcntl.h>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <string>
#include <utility>

json items_data;

namespace
{
struct ItemVisual
{
    std::string name;
    FLinearColor color;
};

std::unordered_map<int, ItemVisual> itemVisuals;

namespace OverlayUI
{
const FLinearColor kPanelBackground(0.035f, 0.055f, 0.085f, 0.86f);
const FLinearColor kPanelBorder(0.24f, 0.32f, 0.42f, 0.85f);
const FLinearColor kTextPrimary(0.94f, 0.97f, 1.0f, 1.0f);
const FLinearColor kTextMuted(0.62f, 0.71f, 0.82f, 1.0f);
const FLinearColor kVisible(0.20f, 0.91f, 0.73f, 1.0f);
const FLinearColor kHidden(1.0f, 0.34f, 0.45f, 1.0f);
const FLinearColor kWarning(1.0f, 0.68f, 0.24f, 1.0f);

void DrawPanel(AHUD *hud, float x, float y, float width, float height,
               FLinearColor accent)
{
    DrawFilledRectangle(hud, {x + 2.0f, y + 2.0f}, width, height,
                        FLinearColor(0.0f, 0.0f, 0.0f, 0.22f));
    DrawFilledRectangle(hud, {x, y}, width, height, kPanelBackground);
    hud->DrawLine(x, y, x + width, y, kPanelBorder, 1.0f);
    hud->DrawLine(x, y, x, y + height, kPanelBorder, 1.0f);
    hud->DrawLine(x + width, y, x + width, y + height, kPanelBorder, 1.0f);
    hud->DrawLine(x, y + height, x + width, y + height, kPanelBorder, 1.0f);
    DrawFilledRectangle(hud, {x, y}, 4.0f, height, accent);
}

void DrawHeader(AHUD *hud, int enemies, int bots)
{
    if (!Cheat::Esp::Counter || !tslFont)
        return;

    constexpr float width = 170.0f;
    constexpr float height = 42.0f;
    const float x = (glWidth - width) * 0.5f;
    constexpr float y = 26.0f;
    DrawPanel(hud, x, y, width, height, enemies > 0 ? kHidden : kVisible);

    const int previousSize = tslFont->LegacyFontSize;
    tslFont->LegacyFontSize = 9;
    DrawOutlinedText(hud, FString("HUDDRAW // LIVE"), {x + 13.0f, y + 7.0f},
                     kTextMuted, COLOR_BLACK, false);

    const std::string enemyText = "ENEMIES " + std::to_string(enemies);
    const std::string botText = "BOTS " + std::to_string(bots);
    tslFont->LegacyFontSize = 12;
    DrawOutlinedText(hud, FString(enemyText.c_str()), {x + 13.0f, y + 21.0f},
                     kTextPrimary, COLOR_BLACK, false);
    DrawOutlinedText(hud, FString(botText.c_str()), {x + 105.0f, y + 21.0f},
                     kTextMuted, COLOR_BLACK, false);
    tslFont->LegacyFontSize = previousSize;
}

FLinearColor HealthColor(float percentage)
{
    if (percentage > 0.70f)
        return kVisible;
    if (percentage > 0.30f)
        return kWarning;
    return kHidden;
}

void DrawPlayerText(AHUD *hud, ASTExtraPlayerCharacter *player, float x,
                    float y, float distance, bool visible)
{
    if (!tslFont || (!Cheat::Esp::Name && !Cheat::Esp::Distance))
        return;

    const int previousSize = tslFont->LegacyFontSize;
    tslFont->LegacyFontSize = 10;
    const FLinearColor accent = visible ? kVisible : kHidden;
    float textY = y - 19.0f;

    if (Cheat::Esp::Name)
    {
        const FString label = player->bEnsure ? FString("BOT") : player->PlayerName;
        DrawOutlinedText(hud, label, {x, textY}, kTextPrimary, COLOR_BLACK, true);
        textY += 12.0f;
    }

    if (Cheat::Esp::Distance)
    {
        const std::string distanceText = std::to_string(static_cast<int>(distance)) + " m";
        DrawOutlinedText(hud, FString(distanceText.c_str()), {x, textY}, accent,
                         COLOR_BLACK, true);
    }
    tslFont->LegacyFontSize = previousSize;
}
} // namespace OverlayUI
} // namespace

void DrawHUD(AHUD *HUD)
{
    if (!HUD || !tslFont || !Cheat::localPlayer || !Cheat::localController)
        return;

    int totalEnemies = 0;
    int totalBots = 0;
    for (const auto &entry : GetFramePlayers())
    {
        auto *player = entry.player;
        if (!player)
            continue;

        if (player->bEnsure)
            ++totalBots;
        else
            ++totalEnemies;

        if (!entry.projected)
            continue;

        const FVector2D &headScreen = entry.headScreen;
        const FVector2D &rootScreen = entry.rootScreen;
        const float height = fabsf(rootScreen.Y - headScreen.Y);
        if (height < 4.0f)
            continue;

        const bool isVisible = entry.visible;
        const FLinearColor accent = isVisible ? OverlayUI::kVisible : OverlayUI::kHidden;
        const float distance = entry.distance;
        const float extraTop = height * 0.10f;
        const float boxHeight = height + extraTop;
        const float width = boxHeight * 0.50f;
        const float x = headScreen.X - (width * 0.5f);
        const float y = headScreen.Y - extraTop;

        // Keep distant entities readable with their compact box/tag while
        // avoiding 22 bone projections for sprites that are only a few pixels
        // high on screen.
        const bool drawDetailedSkeleton = Cheat::Esp::Skeleton &&
            height >= 18.0f && distance <= 350.0f;
        if (drawDetailedSkeleton)
        {
            constexpr std::array<const char *, 22> kBoneNames = {
                "Head", "neck_01", "spine_03", "spine_02", "spine_01", "pelvis",
                "clavicle_r", "upperarm_r", "lowerarm_r", "hand_r", "item_r",
                "clavicle_l", "upperarm_l", "lowerarm_l", "hand_l", "item_l",
                "thigh_r", "calf_r", "foot_r", "thigh_l", "calf_l", "foot_l"
            };
            constexpr std::array<std::pair<size_t, size_t>, 21> kSkeletonLinks = {{
                {0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5},
                {1, 6}, {6, 7}, {7, 8}, {8, 9}, {9, 10},
                {1, 11}, {11, 12}, {12, 13}, {13, 14}, {14, 15},
                {5, 16}, {16, 17}, {17, 18}, {5, 19}, {19, 20}, {20, 21}
            }};

            std::array<FVector2D, kBoneNames.size()> boneScreen{};
            std::array<bool, kBoneNames.size()> projected{};
            for (size_t boneIndex = 0; boneIndex < kBoneNames.size(); ++boneIndex)
            {
                projected[boneIndex] = W2S(
                    player->GetBonePos(kBoneNames[boneIndex], {}),
                    &boneScreen[boneIndex]);
            }

            for (const auto &[from, to] : kSkeletonLinks)
            {
                if (projected[from] && projected[to])
                {
                    HUD->DrawLine(boneScreen[from].X, boneScreen[from].Y,
                                  boneScreen[to].X, boneScreen[to].Y,
                                  accent, 1.25f);
                }
            }

            FVector headTop = player->GetBonePos("Head", {});
            headTop.Z += 15.0f;
            FVector2D topScreen;
            if (W2S(headTop, &topScreen))
            {
                const float radius = FVector2D::Distance(headScreen, topScreen);
                DrawCircleHelper(HUD, headScreen.X, headScreen.Y, radius,
                                 accent, 28, 1.25f);
            }
        }

        if (Cheat::Esp::Box)
            Box4LineHUD(HUD, x, y, width, boxHeight, 1.25f, 0.16f, accent);

        if (Cheat::Esp::Health)
        {
            const float maxHealth = player->HealthMax;
            if (maxHealth > 0.0f)
            {
                const float currentHealth = std::max(0.0f,
                    std::min(player->Health, maxHealth));
                float healthPercentage = currentHealth / maxHealth;
                if (currentHealth <= 0.0f)
                    healthPercentage = std::max(0.0f,
                        std::min(player->NearDeathBreath / maxHealth, 1.0f));

                constexpr float barWidth = 3.0f;
                const float barX = x - barWidth - (width * 0.10f);
                DrawFilledRectangle(HUD, {barX - 1.0f, y - 1.0f}, barWidth + 2.0f,
                                    boxHeight + 2.0f, OverlayUI::kPanelBorder);
                DrawFilledRectangle(HUD, {barX, y}, barWidth, boxHeight,
                                    FLinearColor(0.0f, 0.0f, 0.0f, 0.58f));
                const float filledHeight = boxHeight * healthPercentage;
                DrawFilledRectangle(HUD, {barX, y + boxHeight - filledHeight},
                                    barWidth, filledHeight,
                                    OverlayUI::HealthColor(healthPercentage));
            }
        }

        if (Cheat::Esp::Line)
        {
            HUD->DrawLine(glWidth * 0.5f, glHeight - 34.0f, headScreen.X, y - 4.0f,
                          FLinearColor(accent.R, accent.G, accent.B, 0.62f), 1.0f);
        }

        OverlayUI::DrawPlayerText(HUD, player, headScreen.X, y, distance, isVisible);
    }

    // Player actors are consumed above from the precomputed snapshot. The
    // remaining actor types only require one projection at their own ranges.
    for (auto *actor : GetFrameActors())
    {
        if (actor->IsA(ASTExtraPlayerCharacter::StaticClass()))
            continue;

        if (Cheat::Esp::Vehicle::Name && actor->IsA(ASTExtraVehicleBase::StaticClass()))
        {
            auto *vehicle = static_cast<ASTExtraVehicleBase *>(actor);
            if (!vehicle->Mesh)
                continue;

            FVector2D screen;
            if (!W2S(vehicle->K2_GetActorLocation(), &screen))
                continue;

            const float distance = vehicle->GetDistanceTo(Cheat::localPlayer) / 100.0f;
            const int previousSize = tslFont->LegacyFontSize;
            tslFont->LegacyFontSize = 10;
            DrawOutlinedText(HUD, FString(GetVehicleName(vehicle)), screen,
                             OverlayUI::kWarning, COLOR_BLACK, true);
            const std::string distanceText = std::to_string(static_cast<int>(distance)) + " m";
            DrawOutlinedText(HUD, FString(distanceText.c_str()), {screen.X, screen.Y + 12.0f},
                             OverlayUI::kTextMuted, COLOR_BLACK, true);
            tslFont->LegacyFontSize = previousSize;
            continue;
        }

        if (Cheat::Esp::Throwable && actor->IsA(ASTExtraGrenadeBase::StaticClass()))
        {
            auto *grenade = static_cast<ASTExtraGrenadeBase *>(actor);
            if (!grenade->RootComponent)
                continue;

            const float distance = grenade->GetDistanceTo(Cheat::localPlayer) / 100.0f;
            FVector2D screen;
            if (distance > 50.0f || !W2S(grenade->K2_GetActorLocation(), &screen))
                continue;

            const int previousSize = tslFont->LegacyFontSize;
            tslFont->LegacyFontSize = 10;
            DrawOutlinedText(HUD, FString("GRENADE"), screen, OverlayUI::kHidden,
                             COLOR_BLACK, true);
            const std::string distanceText = std::to_string(static_cast<int>(distance)) + " m";
            DrawOutlinedText(HUD, FString(distanceText.c_str()), {screen.X, screen.Y + 12.0f},
                             OverlayUI::kTextMuted, COLOR_BLACK, true);
            tslFont->LegacyFontSize = previousSize;
            continue;
        }

        if (Cheat::Esp::LootBox && actor->IsA(APickUpListWrapperActor::StaticClass()))
        {
            auto *pickupList = static_cast<APickUpListWrapperActor *>(actor);
            if (!pickupList->RootComponent)
                continue;

            const float distance = pickupList->GetDistanceTo(Cheat::localPlayer) / 100.0f;
            FVector2D screen;
            if (distance > 50.0f || !W2S(pickupList->K2_GetActorLocation(), &screen))
                continue;

            const int previousSize = tslFont->LegacyFontSize;
            tslFont->LegacyFontSize = 10;
            DrawOutlinedText(HUD, FString("LOOT CRATE"), screen, OverlayUI::kVisible,
                             COLOR_BLACK, true);
            const std::string distanceText = std::to_string(static_cast<int>(distance)) + " m";
            DrawOutlinedText(HUD, FString(distanceText.c_str()), {screen.X, screen.Y + 12.0f},
                             OverlayUI::kTextMuted, COLOR_BLACK, true);
            tslFont->LegacyFontSize = previousSize;
            continue;
        }

        if (Cheat::Esp::ItemEsp && actor->IsA(APickUpWrapperActor::StaticClass()))
        {
            auto *pickup = static_cast<APickUpWrapperActor *>(actor);
            if (!pickup->RootComponent)
                continue;

            const auto item = itemVisuals.find(pickup->DefineID.TypeSpecificID);
            if (item == itemVisuals.end())
                continue;

            const float distance = pickup->GetDistanceTo(Cheat::localPlayer) / 100.0f;
            FVector2D screen;
            if (distance > 30.0f || !W2S(pickup->K2_GetActorLocation(), &screen))
                continue;

            const int previousSize = tslFont->LegacyFontSize;
            tslFont->LegacyFontSize = 10;
            DrawOutlinedText(HUD, FString(item->second.name.c_str()), screen,
                             item->second.color, COLOR_BLACK, true);
            const std::string distanceText = std::to_string(static_cast<int>(distance)) + " m";
            DrawOutlinedText(HUD, FString(distanceText.c_str()), {screen.X, screen.Y + 12.0f},
                             OverlayUI::kTextMuted, COLOR_BLACK, true);
            tslFont->LegacyFontSize = previousSize;
        }
    }

    OverlayUI::DrawHeader(HUD, totalEnemies, totalBots);
}


void DrawMemory()
{
    if (!Cheat::localPlayer || !Cheat::localController)
        return;

    if (Cheat::Aimbot::Enable)
    {
        auto *target = GetTargetForAimBot();
        if (target)
        {
            bool triggerActive = false;
            switch (Cheat::Aimbot::Trigger)
            {
                case EAimTrigger::None:
                case EAimTrigger::Shooting:
                    triggerActive = Cheat::localPlayer->bIsWeaponFiring;
                    break;
                case EAimTrigger::Scoping:
                    triggerActive = Cheat::localPlayer->bIsGunADS;
                    break;
                case EAimTrigger::Both:
                case EAimTrigger::Any:
                    triggerActive = Cheat::localPlayer->bIsWeaponFiring ||
                        Cheat::localPlayer->bIsGunADS;
                    break;
            }

            // Automatic mode tracks a valid locked enemy without requiring a
            // firing/ADS state. Disable AutoAim to retain trigger-only use.
            const bool shouldTrack = Cheat::Aimbot::AutoAim || triggerActive;
            const bool reactionElapsed = GetAimTargetLockAge() >=
                std::max(0.0f, Cheat::Aimbot::ReactionDelay);
            if (shouldTrack && reactionElapsed)
            {
                FVector targetAimPos = target->GetBonePos(GetAimTargetBone(target), {});
                const bool validTargetPosition = std::isfinite(targetAimPos.X) &&
                    std::isfinite(targetAimPos.Y) && std::isfinite(targetAimPos.Z);
                auto *weaponManager = Cheat::localPlayer->WeaponManagerComponent;
                if (validTargetPosition && weaponManager)
                {
                    const auto propSlot = weaponManager->GetCurrentUsingPropSlot();
                    if (static_cast<int>(propSlot.GetValue()) >= 1 &&
                        static_cast<int>(propSlot.GetValue()) <= 3)
                    {
                        auto *weapon = static_cast<ASTExtraShootWeapon *>(
                            weaponManager->CurrentWeaponReplicated);
                        auto *shootWeapon = weapon ? weapon->ShootWeaponComponent : nullptr;
                        auto *entity = shootWeapon
                            ? shootWeapon->ShootWeaponEntityComponent
                            : nullptr;

                        if (Cheat::Aimbot::AimPrediction && entity)
                        {
                            const float bulletSpeed = *reinterpret_cast<float *>(
                                reinterpret_cast<uintptr_t>(entity) + 0x560);
                            if (std::isfinite(bulletSpeed) && bulletSpeed > 1.0f)
                            {
                                const auto *vehicle = target->CurrentVehicle;
                                const FVector velocity = vehicle
                                    ? vehicle->ReplicatedMovement.LinearVelocity
                                    : target->GetVelocity();
                                const float distance = Cheat::localPlayer->GetDistanceTo(target);
                                const float travelTime = distance / bulletSpeed;

                                targetAimPos = UKismetMathLibrary::Add_VectorVector(
                                    targetAimPos,
                                    UKismetMathLibrary::Multiply_VectorFloat(
                                        velocity, travelTime));
                                targetAimPos.Z += velocity.Z * travelTime +
                                    0.5f * 573.0f * travelTime * travelTime;
                            }
                        }

                        if (Cheat::localPlayer->bIsWeaponFiring)
                        {
                            const float distance = Cheat::localPlayer->GetDistanceTo(target) / 100.0f;
                            targetAimPos.Z -= distance * Cheat::Aimbot::RecoilSet;
                        }

                        auto *cameraManager = Cheat::localController->PlayerCameraManager;
                        if (cameraManager)
                        {
                            const FRotator aimRotation = ToRotator(
                                cameraManager->CameraCache.POV.Location, targetAimPos);
                            const FRotator currentRotation = Cheat::localController->ControlRotation;
                            const float pitchError = NormalizeAxis(aimRotation.Pitch -
                                currentRotation.Pitch -
                                Cheat::localPlayer->AimControlRotationAdditive.Pitch);
                            const float yawError = NormalizeAxis(aimRotation.Yaw -
                                currentRotation.Yaw -
                                Cheat::localPlayer->AimControlRotationAdditive.Yaw);

                            const float dt = GetFrameDeltaSeconds();
                            const float response = Cheat::Aimbot::Humanize
                                ? 1.0f - expf(-std::max(1.0f,
                                    Cheat::Aimbot::TrackingSpeed) * dt)
                                : 1.0f;
                            float pitchInput = ClampMagnitude(pitchError * response,
                                Cheat::Aimbot::MaxPitchSpeed * dt);
                            float yawInput = ClampMagnitude(yawError * response,
                                Cheat::Aimbot::MaxYawSpeed * dt);

                            if (Cheat::Aimbot::Humanize)
                            {
                                const float remainingError = fabsf(pitchError) + fabsf(yawError);
                                const float settleFactor = std::max(0.0f,
                                    1.0f - (remainingError / 12.0f));
                                const float phase = GetFrameElapsedSeconds() * 7.0f +
                                    static_cast<float>(reinterpret_cast<uintptr_t>(target) & 0xFF);
                                const float jitter = sinf(phase) *
                                    Cheat::Aimbot::MicroJitter * settleFactor;
                                pitchInput = ClampMagnitude(pitchInput + jitter,
                                    Cheat::Aimbot::MaxPitchSpeed * dt);
                                yawInput = ClampMagnitude(yawInput + (jitter * 0.65f),
                                    Cheat::Aimbot::MaxYawSpeed * dt);
                            }

                            Cheat::localPlayer->AddControllerPitchInput(pitchInput);
                            Cheat::localPlayer->AddControllerYawInput(yawInput);
                        }
                    }
                }
            }
        }
    }

    if (Cheat::Memory::XHitEffect &&
        (Cheat::localPlayer->bIsWeaponFiring || Cheat::localPlayer->bIsGunADS))
    {
        auto *hud = static_cast<ASurviveHUD *>(Cheat::localController->MyHUD);
        if (!hud)
            return;

        const auto hitPerformAddress = *reinterpret_cast<uintptr_t *>(&hud->HitPerform);
        if (!hitPerformAddress)
            return;

        const FLinearColor color = RandomColor();
        *reinterpret_cast<float *>(hitPerformAddress + 0x10) = 99999.0f;
        *reinterpret_cast<float *>(hitPerformAddress + 0x50) = 99999.0f;
        *reinterpret_cast<float *>(hitPerformAddress + 0x90) = 99999.0f;
        *reinterpret_cast<float *>(hitPerformAddress + 0xD0) = 99999.0f;
        hud->SetHitPerformColor(EHitPerformColorType::EHitPerformColor_Head, color);
        hud->SetHitPerformColor(EHitPerformColorType::EHitPerformColor_Body, color);
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
    Cheat::Esp::ItemEsp = true;
    Cheat::Esp::Counter = true;
    Cheat::Esp::Vehicle::Name = true;

    Cheat::Aimbot::Enable = true;
    Cheat::Aimbot::AutoAim = true;
    Cheat::Aimbot::StickyTarget = true;
    Cheat::Aimbot::Humanize = true;
    Cheat::Aimbot::AimPrediction = true;
    Cheat::Aimbot::Trigger = EAimTrigger::Shooting;
    Cheat::Aimbot::RecoilSet = 1.045f;
    Cheat::Aimbot::VisCheck = true;
    Cheat::Aimbot::IgnoreKnock = true;
    Cheat::Aimbot::Range = 250.0f;
    Cheat::Aimbot::Radius = 300.0f;
    Cheat::Aimbot::ReactionDelay = 0.075f;
    Cheat::Aimbot::TrackingSpeed = 12.0f;
    Cheat::Aimbot::MaxPitchSpeed = 180.0f;
    Cheat::Aimbot::MaxYawSpeed = 240.0f;
    Cheat::Aimbot::MicroJitter = 0.08f;
    Cheat::Aimbot::BoneRefreshInterval = 0.08f;
    Cheat::Aimbot::Target = Chest;

    // Convert the static JSON once during startup. The draw path performs one
    // hash lookup instead of repeatedly scanning every JSON category/item.
    itemVisuals.clear();
    itemVisuals.reserve(items_data.size() * 4);
    for (const auto &category : items_data)
    {
        for (const auto &item : category["Items"])
        {
            const int id = item["itemId"].get<int>();
            const uint32_t color = static_cast<uint32_t>(std::strtoul(
                item["itemTextColor"].get<std::string>().c_str(), nullptr, 0));
            itemVisuals.emplace(id, ItemVisual{
                item["itemName"].get<std::string>(), UIntToLinearColor(color)});
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
