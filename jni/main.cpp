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
#include <atomic>

json items_data;

namespace
{
struct ItemVisual
{
    std::string name;
    FLinearColor color;
};

std::unordered_map<int, ItemVisual> itemVisuals;

bool IsFiniteVector(const FVector &value)
{
    return std::isfinite(value.X) && std::isfinite(value.Y) && std::isfinite(value.Z);
}

float VectorDistance(const FVector &from, const FVector &to)
{
    const float x = to.X - from.X;
    const float y = to.Y - from.Y;
    const float z = to.Z - from.Z;
    return sqrtf((x * x) + (y * y) + (z * z));
}

FVector GetTargetVelocity(ASTExtraPlayerCharacter *target)
{
    const FVector playerVelocity = target->GetVelocity();
    if (!target->CurrentVehicle)
        return playerVelocity;

    const FVector vehicleVelocity = target->CurrentVehicle->ReplicatedMovement.LinearVelocity;
    const float vehicleSpeedSquared = (vehicleVelocity.X * vehicleVelocity.X) +
        (vehicleVelocity.Y * vehicleVelocity.Y) + (vehicleVelocity.Z * vehicleVelocity.Z);
    return vehicleSpeedSquared > 25.0f ? vehicleVelocity : playerVelocity;
}

FVector PredictAimPosition(ASTExtraPlayerCharacter *target, const FVector &aimPoint,
                           const FVector &shotOrigin, float bulletSpeed)
{
    if (!target || !IsFiniteVector(aimPoint) || !IsFiniteVector(shotOrigin) ||
        !std::isfinite(bulletSpeed) || bulletSpeed < 1000.0f)
        return aimPoint;

    const FVector velocity = GetTargetVelocity(target);
    if (!IsFiniteVector(velocity))
        return aimPoint;

    const float maxFlightTime = std::max(0.10f, Cheat::Aimbot::MaxPredictionTime);
    const float latency = std::max(0.0f, Cheat::Aimbot::PredictionLatency);
    float flightTime = std::min(VectorDistance(shotOrigin, aimPoint) / bulletSpeed,
                                maxFlightTime);

    // Recompute time of flight against the leading point. Two bounded passes
    // handle side-running targets substantially better than a single distance /
    // speed approximation while remaining stable with intermittent snapshots.
    for (int iteration = 0; iteration < 2; ++iteration)
    {
        const float leadTime = flightTime + latency;
        const FVector leadingPoint{
            aimPoint.X + (velocity.X * leadTime),
            aimPoint.Y + (velocity.Y * leadTime),
            aimPoint.Z + (velocity.Z * leadTime)
        };
        flightTime = std::min(VectorDistance(shotOrigin, leadingPoint) / bulletSpeed,
                              maxFlightTime);
    }

    const float leadTime = flightTime + latency;
    FVector predicted{
        aimPoint.X + (velocity.X * leadTime),
        aimPoint.Y + (velocity.Y * leadTime),
        aimPoint.Z + (velocity.Z * leadTime)
    };
    // Compensate only for projectile flight time; latency shifts the target but
    // does not increase the amount of gravitational projectile drop.
    predicted.Z += 0.5f * std::max(0.0f, Cheat::Aimbot::PredictionGravity) *
        flightTime * flightTime;
    return IsFiniteVector(predicted) ? predicted : aimPoint;
}

namespace OverlayUI
{
const FLinearColor kPanelBackground(0.018f, 0.031f, 0.064f, 0.91f);
const FLinearColor kPanelBorder(0.22f, 0.43f, 0.68f, 0.74f);
const FLinearColor kTextPrimary(0.95f, 0.98f, 1.0f, 1.0f);
const FLinearColor kTextMuted(0.58f, 0.69f, 0.82f, 1.0f);
const FLinearColor kVisible(0.18f, 0.92f, 0.72f, 1.0f);
const FLinearColor kHidden(1.0f, 0.32f, 0.47f, 1.0f);
const FLinearColor kWarning(1.0f, 0.69f, 0.23f, 1.0f);
const FLinearColor kAccent(0.27f, 0.62f, 1.0f, 1.0f);
const FLinearColor kFovBlue(0.16f, 0.53f, 1.0f, 1.0f);

// One Canvas-rendered stroke per line: sharp, anti-aliased, and no glow.
void DrawCleanLine(AHUD *hud, float x1, float y1, float x2, float y2,
                   const FLinearColor &color, float thickness = 0.70f)
{
    DrawCanvasLine(hud, x1, y1, x2, y2, color, thickness);
}

void DrawPanel(AHUD *hud, float x, float y, float width, float height,
               FLinearColor accent)
{
    DrawFilledRectangle(hud, {x, y}, width, height, kPanelBackground);
    DrawCleanLine(hud, x, y, x + width, y, kPanelBorder, 0.70f);
    DrawCleanLine(hud, x, y, x, y + height, kPanelBorder, 0.70f);
    DrawCleanLine(hud, x + width, y, x + width, y + height, kPanelBorder, 0.70f);
    DrawCleanLine(hud, x, y + height, x + width, y + height, kPanelBorder, 0.70f);
    DrawFilledRectangle(hud, {x, y}, width, 2.0f, accent);
    DrawFilledRectangle(hud, {x, y}, 3.0f, height, accent);
}

void DrawHeader(AHUD *hud, int enemies, int bots)
{
    if (!Cheat::Esp::Counter || !tslFont)
        return;

    constexpr float width = 270.0f;
    constexpr float height = 44.0f;
    const float x = (glWidth - width) * 0.5f;
    constexpr float y = 18.0f;
    DrawPanel(hud, x, y, width, height, enemies > 0 ? kHidden : kVisible);

    const int previousSize = tslFont->LegacyFontSize;
    tslFont->LegacyFontSize = 10;
    DrawOutlinedText(hud, FString("HUDDRAW  /  LIVE MATCH"), {x + 13.0f, y + 7.0f},
                     kTextMuted, COLOR_BLACK, false);

    const std::string enemyText = "ENEMIES " + std::to_string(enemies);
    const std::string botText = "BOTS " + std::to_string(bots);
    const float delta = GetFrameDeltaSeconds();
    const int fps = delta > 0.0f ? static_cast<int>(std::round(1.0f / delta)) : 0;
    const std::string fpsText = std::to_string(fps) + " FPS";
    constexpr float rowTop = y + 22.0f;
    DrawFilledRectangle(hud, {x + 90.0f, rowTop}, 1.0f, 14.0f,
                        FLinearColor(kPanelBorder.R, kPanelBorder.G, kPanelBorder.B, 0.58f));
    DrawFilledRectangle(hud, {x + 180.0f, rowTop}, 1.0f, 14.0f,
                        FLinearColor(kPanelBorder.R, kPanelBorder.G, kPanelBorder.B, 0.58f));

    tslFont->LegacyFontSize = 11;
    DrawOutlinedText(hud, FString(enemyText.c_str()), {x + 45.0f, y + 23.0f},
                     kTextPrimary, COLOR_BLACK, true);
    DrawOutlinedText(hud, FString(botText.c_str()), {x + 135.0f, y + 23.0f},
                     kWarning, COLOR_BLACK, true);
    DrawOutlinedText(hud, FString(fpsText.c_str()), {x + 225.0f, y + 23.0f},
                     kVisible, COLOR_BLACK, true);
    tslFont->LegacyFontSize = previousSize;
}

FLinearColor HealthColor(float percentage)
{
    percentage = std::max(0.0f, std::min(percentage, 1.0f));
    const FLinearColor low(1.0f, 0.24f, 0.34f, 1.0f);
    const FLinearColor middle(1.0f, 0.76f, 0.17f, 1.0f);
    const FLinearColor full(0.14f, 0.94f, 0.54f, 1.0f);
    const FLinearColor &from = percentage < 0.50f ? low : middle;
    const FLinearColor &to = percentage < 0.50f ? middle : full;
    const float blend = percentage < 0.50f ? percentage * 2.0f :
        (percentage - 0.50f) * 2.0f;
    return FLinearColor(
        from.R + ((to.R - from.R) * blend),
        from.G + ((to.G - from.G) * blend),
        from.B + ((to.B - from.B) * blend), 1.0f);
}

void DrawAimbotFov(AHUD *hud)
{
    if (!Cheat::Esp::FovCircle || !Cheat::Aimbot::Enable ||
        Cheat::Aimbot::Radius <= 0.0f)
        return;

    // The visual radius deliberately matches target selection. The default is
    // tightened to 240 px below so it stays useful on mobile screens instead
    // of covering most of the display.
    const int segments = GetFrameDeltaSeconds() <= (1.0f / 90.0f) ? 96 : 80;
    const float radius = Cheat::Aimbot::Radius;
    const FLinearColor ring(kFovBlue.R, kFovBlue.G, kFovBlue.B, 0.90f);
    DrawCircleHelper(hud, glWidth * 0.5f, glHeight * 0.5f, radius, ring,
                     segments, 0.70f);
}

void DrawSelectedTargetMarker(AHUD *hud, float x, float y, float width,
                              float height)
{
    if (!Cheat::Esp::Target)
        return;

    const float corner = std::max(6.0f, width * 0.22f);
    const float left = x - 3.0f;
    const float right = x + width + 3.0f;
    const float top = y - 3.0f;
    const float bottom = y + height + 3.0f;
    const FLinearColor marker(1.0f, 0.65f, 0.20f, 0.98f);

    DrawCleanLine(hud, left, top, left + corner, top, marker, 0.85f);
    DrawCleanLine(hud, left, top, left, top + corner, marker, 0.85f);
    DrawCleanLine(hud, right - corner, top, right, top, marker, 0.85f);
    DrawCleanLine(hud, right, top, right, top + corner, marker, 0.85f);
    DrawCleanLine(hud, left, bottom - corner, left, bottom, marker, 0.85f);
    DrawCleanLine(hud, left, bottom, left + corner, bottom, marker, 0.85f);
    DrawCleanLine(hud, right - corner, bottom, right, bottom, marker, 0.85f);
    DrawCleanLine(hud, right, bottom - corner, right, bottom, marker, 0.85f);

    const int previousSize = tslFont->LegacyFontSize;
    tslFont->LegacyFontSize = 9;
    DrawOutlinedText(hud, FString("LOCK"), {x + width * 0.5f, top - 12.0f},
                     marker, COLOR_BLACK, true);
    tslFont->LegacyFontSize = previousSize;
}

void DrawPlayerText(AHUD *hud, ASTExtraPlayerCharacter *player, float x,
                    float y, float distance, bool visible, bool knocked)
{
    if (!hud || !hud->Canvas || !tslFont ||
        (!Cheat::Esp::Name && !Cheat::Esp::Distance && !knocked))
        return;

    const int previousSize = tslFont->LegacyFontSize;
    const FLinearColor visibilityColor = visible ? kVisible : kHidden;
    const FLinearColor accent = knocked ? kHidden : visibilityColor;
    float tagBottom = y - 5.0f;

    if (Cheat::Esp::Distance || knocked)
    {
        const std::string statusText = knocked ? "KNOCKED" : std::to_string(
            static_cast<int>(std::round(distance))) + " m";
        const FString statusLabel(statusText.c_str());
        tslFont->LegacyFontSize = 10;
        const float tagWidth = knocked ? 76.0f : 54.0f;
        tagBottom -= 13.0f;
        DrawFilledRectangle(hud, {x - tagWidth * 0.5f, tagBottom}, tagWidth, 13.0f,
                            FLinearColor(0.015f, 0.028f, 0.055f, 0.84f));
        DrawFilledRectangle(hud, {x - tagWidth * 0.5f, tagBottom}, 2.0f, 13.0f, accent);
        DrawOutlinedText(hud, statusLabel, {x, tagBottom + 1.0f}, accent,
                         COLOR_BLACK, true);
        tagBottom -= 3.0f;
    }

    if (Cheat::Esp::Name)
    {
        const FString label = player->bEnsure ? FString("BOT") : player->PlayerName;
        tslFont->LegacyFontSize = 12;
        // Fixed tag widths avoid an additional Blueprint/ProcessEvent call for
        // every player every frame while keeping normal player names readable.
        const float tagWidth = player->bEnsure ? 58.0f : 126.0f;
        tagBottom -= 16.0f;
        DrawFilledRectangle(hud, {x - tagWidth * 0.5f, tagBottom}, tagWidth, 16.0f,
                            FLinearColor(0.018f, 0.035f, 0.070f, 0.92f));
        DrawFilledRectangle(hud, {x - tagWidth * 0.5f, tagBottom}, tagWidth, 1.5f, accent);
        DrawOutlinedText(hud, label, {x, tagBottom + 2.0f}, kTextPrimary,
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

    const bool aimTriggerActive = Cheat::localPlayer->bIsWeaponFiring ||
        Cheat::localPlayer->bIsGunADS;
    if (!aimTriggerActive)
        ClearAimTargetLock();
    ASTExtraPlayerCharacter *selectedTarget = aimTriggerActive && Cheat::Aimbot::Enable
        ? GetTargetForAimBot()
        : nullptr;

    OverlayUI::DrawAimbotFov(HUD);

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

        // entry.visible is the cached exposed-bone result used by the aimbot,
        // keeping tracer/skeleton colours and target eligibility in sync.
        const bool isVisible = entry.visible;
        const bool isKnocked = !player->bDead && player->Health <= 0.0f;
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
                    OverlayUI::DrawCleanLine(HUD, boneScreen[from].X, boneScreen[from].Y,
                                              boneScreen[to].X, boneScreen[to].Y,
                                              accent, 0.60f);
                }
            }

            FVector headTop = player->GetBonePos("Head", {});
            headTop.Z += 15.0f;
            FVector2D topScreen;
            if (W2S(headTop, &topScreen))
            {
                const float radius = FVector2D::Distance(headScreen, topScreen);
                DrawCircleHelper(HUD, headScreen.X, headScreen.Y, radius,
                                 accent, 48, 0.60f);
            }
        }

        if (Cheat::Esp::Box)
            Box4LineHUD(HUD, x, y, width, boxHeight, 1.25f, 0.16f, accent);
        if (entry.player == selectedTarget)
            OverlayUI::DrawSelectedTargetMarker(HUD, x, y, width, boxHeight);

        // A knocked player is represented by the KNOCKED status tag only;
        // do not render their bleed-out value as if it were normal HP.
        if (Cheat::Esp::Health && !isKnocked)
        {
            const float maxHealth = player->HealthMax;
            if (maxHealth > 0.0f)
            {
                const float healthPercentage = std::max(0.0f, std::min(
                    player->Health / maxHealth, 1.0f));
                const float healthWidth = std::max(30.0f, std::min(width * 1.22f, 72.0f));
                constexpr float healthHeight = 3.0f;
                const float healthX = headScreen.X - (healthWidth * 0.5f);
                const float healthY = rootScreen.Y + 6.0f;
                DrawFilledRectangle(HUD, {healthX - 1.0f, healthY - 1.0f},
                                    healthWidth + 2.0f, healthHeight + 2.0f,
                                    FLinearColor(0.0f, 0.0f, 0.0f, 0.72f));
                DrawFilledRectangle(HUD, {healthX, healthY}, healthWidth, healthHeight,
                                    FLinearColor(0.05f, 0.08f, 0.13f, 0.95f));
                DrawFilledRectangle(HUD, {healthX, healthY}, healthWidth * healthPercentage,
                                    healthHeight, OverlayUI::HealthColor(healthPercentage));
            }
        }

        if (Cheat::Esp::Line)
        {
            OverlayUI::DrawCleanLine(HUD, glWidth * 0.5f, 72.0f, headScreen.X, y - 4.0f,
                                      FLinearColor(accent.R, accent.G, accent.B, 0.72f), 0.65f);
        }

        OverlayUI::DrawPlayerText(HUD, player, headScreen.X, y, distance, isVisible, isKnocked);
    }

    // Player actors are consumed above from the precomputed snapshot. The
    // remaining actor types only require one projection at their own ranges.
    for (auto *actor : GetFrameActors())
    {
        if (actor->IsA(ASTExtraPlayerCharacter::StaticClass()))
            continue;

        if ((Cheat::Esp::Vehicle::Name || Cheat::Esp::Vehicle::Health ||
             Cheat::Esp::Vehicle::Fuel) && actor->IsA(ASTExtraVehicleBase::StaticClass()))
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
            if (Cheat::Esp::Vehicle::Name)
                DrawOutlinedText(HUD, FString(GetVehicleName(vehicle)), screen,
                                 OverlayUI::kWarning, COLOR_BLACK, true);

            std::string status = std::to_string(static_cast<int>(distance)) + " m";
            const bool closeEnough = Cheat::Esp::Vehicle::StatusRange <= 0.0f ||
                distance <= Cheat::Esp::Vehicle::StatusRange;
            const auto *vehicleCommon = closeEnough ? vehicle->VehicleCommon : nullptr;
            if (vehicleCommon && Cheat::Esp::Vehicle::Health && vehicleCommon->HPMax > 0.0f)
            {
                const float percentage = std::max(0.0f, std::min(
                    vehicleCommon->HP * 100.0f / vehicleCommon->HPMax, 100.0f));
                status += "  HP " + std::to_string(static_cast<int>(std::round(percentage))) + "%";
            }
            if (vehicleCommon && Cheat::Esp::Vehicle::Fuel && vehicleCommon->FuelMax > 0.0f)
            {
                const float percentage = std::max(0.0f, std::min(
                    vehicleCommon->Fuel * 100.0f / vehicleCommon->FuelMax, 100.0f));
                status += "  FUEL " + std::to_string(static_cast<int>(std::round(percentage))) + "%";
            }
            DrawOutlinedText(HUD, FString(status.c_str()), {screen.X, screen.Y + 12.0f},
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
        // Automatic tracking follows only deliberate combat input: ADS or
        // firing. Do not even acquire a target lock while the player is idle.
        const bool triggerActive = Cheat::localPlayer->bIsWeaponFiring ||
            Cheat::localPlayer->bIsGunADS;
        if (!triggerActive)
            ClearAimTargetLock();

        auto *target = triggerActive ? GetTargetForAimBot() : nullptr;
        if (target)
        {
            const float warmup = GetHumanizedAimWarmup();
            if (warmup > 0.0f)
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

                        auto *cameraManager = Cheat::localController->PlayerCameraManager;
                        if (Cheat::Aimbot::AimPrediction && entity && cameraManager)
                        {
                            const float bulletSpeed = *reinterpret_cast<float *>(
                                reinterpret_cast<uintptr_t>(entity) + 0x560);
                            targetAimPos = PredictAimPosition(target, targetAimPos,
                                cameraManager->CameraCache.POV.Location, bulletSpeed);
                        }

                        if (Cheat::localPlayer->bIsWeaponFiring)
                        {
                            const float distance = Cheat::localPlayer->GetDistanceTo(target) / 100.0f;
                            targetAimPos.Z -= distance * Cheat::Aimbot::RecoilSet;
                        }

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
                            float response = Cheat::Aimbot::Humanize
                                ? 1.0f - expf(-std::max(1.0f,
                                    Cheat::Aimbot::TrackingSpeed) * dt)
                                : 1.0f;
                            response *= warmup;
                            float pitchInput = ClampMagnitude(pitchError * response,
                                Cheat::Aimbot::MaxPitchSpeed * dt);
                            float yawInput = ClampMagnitude(yawError * response,
                                Cheat::Aimbot::MaxYawSpeed * dt);
                            const float remainingError = fabsf(pitchError) + fabsf(yawError);

                            if (Cheat::Aimbot::Humanize)
                            {
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

                            // Leave a tiny deadzone around the target rather
                            // than issuing a mathematically perfect correction
                            // every render callback.
                            if (remainingError > Cheat::Aimbot::AimDeadzone)
                            {
                                Cheat::localPlayer->AddControllerPitchInput(pitchInput);
                                Cheat::localPlayer->AddControllerYawInput(yawInput);
                            }
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
    Cheat::Esp::Box = false;
    Cheat::Esp::LootBox = true;
    Cheat::Esp::Throwable = true;
    Cheat::Esp::ItemEsp = true;
    Cheat::Esp::Counter = true;
    Cheat::Esp::Target = true;
    Cheat::Esp::FovCircle = true;
    Cheat::Esp::Vehicle::Name = true;
    Cheat::Esp::Vehicle::Health = true;
    Cheat::Esp::Vehicle::Fuel = true;
    Cheat::Esp::Vehicle::StatusRange = 75.0f;

    Cheat::Aimbot::Enable = true;
    Cheat::Aimbot::StickyTarget = true;
    Cheat::Aimbot::Humanize = false;
    Cheat::Aimbot::AimPrediction = true;
    Cheat::Aimbot::Trigger = EAimTrigger::Both;
    Cheat::Aimbot::RecoilSet = 1.045f;
    Cheat::Aimbot::VisCheck = true;
    Cheat::Aimbot::IgnoreKnock = true;
    Cheat::Aimbot::Range = 250.0f;
    Cheat::Aimbot::Radius = 240.0f;
    Cheat::Aimbot::ReactionDelay = 0.0f;
    Cheat::Aimbot::AcquisitionTime = 0.0f;
    Cheat::Aimbot::TrackingSpeed = 18.0f;
    Cheat::Aimbot::MaxPitchSpeed = 540.0f;
    Cheat::Aimbot::MaxYawSpeed = 720.0f;
    Cheat::Aimbot::AimDeadzone = 0.02f;
    Cheat::Aimbot::MicroJitter = 0.0f;
    Cheat::Aimbot::PredictionLatency = 0.035f;
    Cheat::Aimbot::PredictionGravity = 980.0f;
    Cheat::Aimbot::MaxPredictionTime = 0.55f;
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



// The direct AHUD hook is kept only as a reference. Rendering is now
// dispatched through ProcessEvent below, matching Engine.HUD.ReceiveDrawHUD.
#if 0
void (*oReceiveDrawHUD)(AHUD *pHUD, int SizeX, int SizeY);
void hkReceiveDrawHUD(AHUD *pHUD, int SizeX, int SizeY)
{
    oReceiveDrawHUD(pHUD, SizeX, SizeY);
    RenderESPPRIVATE(pHUD, SizeX, SizeY);
    DrawHUD(pHUD);
    DrawMemory();
}
#endif

void (*oProcessEvent)(UObject *pObj, UFunction *pFunc, void *pArgs) = nullptr;
static std::atomic<uint32_t> receiveDrawHUDDispatches{0};

void LogShadowHookRecords(const char *operation)
{
    // v2.0.1 adds operation traces. Capture only installation-time records so
    // diagnostics can identify a bad target/stub without adding frame cost.
    char *records = shadowhook_get_records(SHADOWHOOK_RECORD_ITEM_ALL);
    if (!records || !*records)
    {
        LOGW("ShadowHook %s: no operation record is available", operation);
        free(records);
        return;
    }

    constexpr size_t kMaximumLogCharacters = 3072;
    const size_t length = strnlen(records, kMaximumLogCharacters);
    LOGI("ShadowHook %s records (%zu%s): %.*s", operation, length,
         records[length] == '\0' ? "" : "+", static_cast<int>(length), records);
    free(records);
}

void hkProcessEvent(UObject *pObj, UFunction *pFunc, void *pArgs)
{
    static UFunction *receiveDrawHUD = nullptr;
    bool isReceiveDrawHUD = pFunc == receiveDrawHUD;

    // Avoid building a full UObject name for every ProcessEvent call. Resolve
    // and cache the function once, then use the UFunction pointer on the hot
    // path. The simple-name guard makes startup lookup inexpensive as well.
    if (!isReceiveDrawHUD && pFunc &&
        strcmp(pFunc->NamePrivate.GetName(), "ReceiveDrawHUD") == 0 &&
        pFunc->GetFullName() == "Function Engine.HUD.ReceiveDrawHUD")
    {
        receiveDrawHUD = pFunc;
        isReceiveDrawHUD = true;
        LOGI("ProcessEvent: ReceiveDrawHUD resolved at %p", static_cast<void *>(pFunc));
    }

    AHUD *hud = nullptr;
    int sizeX = 0;
    int sizeY = 0;
    if (isReceiveDrawHUD && pObj && pArgs)
    {
        const auto *params = static_cast<AHUD_ReceiveDrawHUD_Params *>(pArgs);
        if (params->SizeX > 0 && params->SizeY > 0 &&
            params->SizeX <= 10000 && params->SizeY <= 10000)
        {
            hud = static_cast<AHUD *>(pObj);
            sizeX = params->SizeX;
            sizeY = params->SizeY;
        }
        else
        {
            LOGW("ProcessEvent: invalid ReceiveDrawHUD size %dx%d",
                 params->SizeX, params->SizeY);
        }
    }

    if (oProcessEvent)
        oProcessEvent(pObj, pFunc, pArgs);
    else
    {
        LOGE("ProcessEvent hook has no original trampoline");
        return;
    }

    // Draw only after UE has processed ReceiveDrawHUD and prepared Canvas.
    if (hud)
    {
        const uint32_t dispatchIndex = receiveDrawHUDDispatches.fetch_add(1,
            std::memory_order_relaxed);
        if (dispatchIndex == 0)
        {
            LOGI("ProcessEvent HUD dispatch is active: HUD=%p Canvas=%p size=%dx%d",
                 static_cast<void *>(hud), static_cast<void *>(hud->Canvas), sizeX, sizeY);
        }

        RenderESPPRIVATE(hud, sizeX, sizeY);
        DrawHUD(hud);
        DrawMemory();
    }
}

void (*ShootBulletInner)(uintptr_t Weapon, FVector StartLoc, FRotator StartRot, int ShootID);
void xShootBulletInner(uintptr_t Weapon, FVector StartLoc, FRotator StartRot, int ShootID)
{
    if (Cheat::BulletTrack::Enable)
    {
        ASTExtraPlayerCharacter* Target = GetTargetForAimBot();
        if (Target)
        {
            FVector targetAimPos = Target->GetBonePos(GetAimTargetBone(Target), {});
            targetAimPos.Z -= -19.0f;   // same as targetAimPos.Z += 19.0f
            FRotator adjustedRot = ToRotator(StartLoc, targetAimPos);
            return ShootBulletInner(Weapon, StartLoc, adjustedRot, ShootID);
        }
    }
    return ShootBulletInner(Weapon, StartLoc, StartRot, ShootID);
}


void initOffset()
{
    constexpr uintptr_t kProcessEventOffset = 0x9FA1C34;
    Cheat::ProcessEvent = Cheat::libUE4Base + kProcessEventOffset;
    if (!Cheat::ProcessEvent)
    {
        LOGE("ProcessEvent address is null");
        return;
    }

    const char *runtimeVersion = shadowhook_get_version();
    LOGI("ShadowHook runtime=%s header=%s mode=UNIQUE target=%p",
         runtimeVersion ? runtimeVersion : "unknown", SHADOWHOOK_VERSION,
         reinterpret_cast<void *>(Cheat::ProcessEvent));

    const int initResult = shadowhook_init(SHADOWHOOK_MODE_UNIQUE, false);
    if (initResult != SHADOWHOOK_ERRNO_OK)
    {
        const int initError = shadowhook_get_init_errno();
        const char *message = shadowhook_to_errmsg(initResult);
        const char *initMessage = shadowhook_to_errmsg(initError);
        LOGE("ShadowHook init failed: result=%d (%s), init_errno=%d (%s)",
             initResult, message ? message : "unknown error", initError,
             initMessage ? initMessage : "unknown error");
        return;
    }

    // Operation recording is a v2.0.1 feature used only during bootstrap.
    // It has no per-frame overhead and makes failed target/stub installation
    // directly visible through the existing logcat logger.
    shadowhook_set_recordable(true);
    LOGI("ShadowHook initialized: mode=%d recordable=%d", shadowhook_get_mode(),
         shadowhook_get_recordable() ? 1 : 0);

    void *processEventStub = shadowhook_hook_func_addr(
        reinterpret_cast<void *>(Cheat::ProcessEvent),
        reinterpret_cast<void *>(hkProcessEvent),
        reinterpret_cast<void **>(&oProcessEvent));
    if (!processEventStub || !oProcessEvent)
    {
        const int error = shadowhook_get_errno();
        const char *message = shadowhook_to_errmsg(error);
        LOGE("ShadowHook ProcessEvent hook failed: target=%p stub=%p error=%d (%s)",
             reinterpret_cast<void *>(Cheat::ProcessEvent), processEventStub, error,
             message ? message : "unknown error");
        return;
    }

    LOGI("ShadowHook ProcessEvent installed: target=%p trampoline=%p",
         reinterpret_cast<void *>(Cheat::ProcessEvent),
         reinterpret_cast<void *>(oProcessEvent));
    LogShadowHookRecords("ProcessEvent installation");
}


void *RunGame(void *)
{
    LOGI("ESP bootstrap started; waiting for libUE4.so");
    Cheat::libUE4Base = Tools::GetBaseAddress("libUE4.so");

    while (!Cheat::libUE4Base)
    {
        Cheat::libUE4Base = Tools::GetBaseAddress("libUE4.so");
        sleep(1);
    }
    LOGI("libUE4.so loaded at %p", reinterpret_cast<void *>(Cheat::libUE4Base));

    FName::GNames = GetGNames();
    while (!FName::GNames)
    {
        FName::GNames = GetGNames();
        sleep(1);
    }
    LOGI("GNames resolved at %p", static_cast<void *>(FName::GNames));

    UObject::GUObjectArray = reinterpret_cast<FUObjectArray *>(
        Cheat::libUE4Base + Cheat::GUObject_Offset);
    LOGI("GUObjectArray configured at %p", static_cast<void *>(UObject::GUObjectArray));

    initOffset();
    if (!oProcessEvent)
    {
        LOGE("ESP hooks are disabled because ProcessEvent was not installed");
        return nullptr;
    }

    const uintptr_t bulletAddress = Cheat::libUE4Base + 0x6BB0CFC;
    void *bulletStub = shadowhook_hook_func_addr(
        reinterpret_cast<void *>(bulletAddress),
        reinterpret_cast<void *>(xShootBulletInner),
        reinterpret_cast<void **>(&ShootBulletInner));
    if (!bulletStub || !ShootBulletInner)
    {
        const int error = shadowhook_get_errno();
        const char *message = shadowhook_to_errmsg(error);
        LOGE("ShadowHook bullet hook failed: target=%p stub=%p error=%d (%s)",
             reinterpret_cast<void *>(bulletAddress), bulletStub, error,
             message ? message : "unknown error");
    }
    else
    {
        LOGI("ShadowHook bullet hook installed: target=%p trampoline=%p",
             reinterpret_cast<void *>(bulletAddress),
             reinterpret_cast<void *>(ShootBulletInner));
        LogShadowHookRecords("bullet-hook installation");
    }

    items_data = json::parse(JSON_ITEMS);
    AutoEspOn();
    LOGI("ESP defaults enabled");
    return nullptr;
}

__attribute__ ((constructor))
void _init() 
{
    pthread_create(&t, NULL, RunGame, NULL);
}
