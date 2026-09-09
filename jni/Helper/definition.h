enum EAimTrigger {
    None = 0,
    Shooting = 1,
    Scoping = 2,
    Both = 3,
    Any = 4
};

enum EAimTarget
{
    Head = 0,
    Chest = 1
};

namespace Cheat 
{
    uintptr_t libUE4Base;
    uintptr_t GName_Offest = 0x86CA71C;
    uintptr_t GUObject_Offset = 0xE6D36F0;
    uintptr_t GNativeAndroidApp_Offset = 0xE40B6A8;
    uintptr_t ActorArray_Offest = 0xA45A314;
    uintptr_t ProcessEvent;
    SDK::ASTExtraPlayerCharacter *localPlayer = nullptr;
    SDK::ASTExtraPlayerController *localController = nullptr;

    namespace Esp 
    {
        bool Line = false;
        bool Skeleton = false;
        bool Health = false;
        bool Distance = false;
        bool Name = false;
        bool Box = false;
        bool LootBox = false;
        bool Throwable = false;
        bool Counter = false;
        bool Target = false;
        bool FovCircle = false;
        bool ItemEsp = false;

        namespace Vehicle 
        {
            bool Name = true;
            bool Health = false;
            bool Fuel = false;
            float StatusRange = 75.0f;
        }
    }

    namespace Aimbot {
bool Enable;
bool VisCheck;
bool IgnoreKnock;
bool IgnoreBot;
bool AimPrediction;
bool StickyTarget = true;
bool Humanize = false;
EAimTrigger Trigger;
EAimTarget Target;
float RecoilControl;
float RecoilSet = 1.050f;
float Range = 250.0f;
float Radius = 240.0f;
float FireSpeed;
float ReactionDelay = 0.0f;
float AcquisitionTime = 0.0f;
float TrackingSpeed = 18.0f;
float MaxPitchSpeed = 540.0f;
float MaxYawSpeed = 720.0f;
float AimDeadzone = 0.02f;
float MicroJitter = 0.0f;
float PredictionLatency = 0.035f;
float PredictionGravity = 980.0f;
float MaxPredictionTime = 0.55f;
float BoneRefreshInterval = 0.08f;

}

    namespace BulletTrack 
    {
        bool Enable;
        bool VisCheck = true;
        bool IgnoreKnock = true;
		bool iGnoreBot;

        float Aimset;
        float Fov = 1000.0f;
        float Range = 600.0f;

        bool AutoFire = false;
    }

    namespace Memory 
    {
        bool Wide = false;
        bool Small = false;
        bool Magic = false;
        bool XHitEffect = false;
        
        float Size = 10000.0f;
    }
}

float Xpos;
float Ypos;
float UpScale;
float Xs=2.4, Ys=2.4;

#define IM_PI 3.14159265358979323846f
#define RAD2DEG(x) ((float)(x) * (float)(180.f / IM_PI))
#define DEG2RAD(x) ((float)(x) * (float)(IM_PI / 180.f))
#define DEG2RADD(x) ((float)(x) * (float)(IM_PI / 360.f))
#define W2S(w, s) UGameplayStatics::ProjectWorldToScreen(Cheat::localController, w, true, s)
#define COLOR_BLACK FLinearColor(0, 0, 0, 0.2f)
#define COLOR_WHITE FLinearColor(1.f, 1.f, 1.f, 1.f)
#define COLOR_RED FLinearColor(1.f, 0.f, 0.f, 1.f)
#define COLOR_GREEN FLinearColor(0.f, 1.f, 0.f, 1.f)
#define COLOR_BLUE FLinearColor(0.68f, 0.85f, 0.90f, 1.0f)
#define COLOR_YELLOW FLinearColor(1.f, 1.f, 0.f, 1.f)
#define COLOR_NONE FLinearColor(0.f, 0.f, 0.f, 0.f)

#define TSL_FONT_DEFAULT_SIZE 20

using namespace SDK;

bool BulletTrack = true;
using namespace SDK;

bool WriteAddr(void *addr, void *buffer, size_t length) 
{
    unsigned long page_size = sysconf(_SC_PAGESIZE);
    unsigned long size = page_size * sizeof(uintptr_t);
    return mprotect((void *) ((uintptr_t) addr - ((uintptr_t) addr % page_size) - page_size),
                    (size_t) size, PROT_EXEC | PROT_READ | PROT_WRITE) == 0 &&
           memcpy(addr, buffer, length) != 0;
}

template<typename T>
void Write(uintptr_t addr, T value) {
    WriteAddr((void *) addr, &value, sizeof(T));
}

int screenWidth = -1, glWidth, screenHeight = -1, glHeight;
float density = -1;

int Write_Float(long int addr, float value) {
    Tools::WriteAddr((void *) (addr), (void *) &value, 4);
    return 0;
}

FVector GetBoneLocationByName(ASTExtraPlayerCharacter *Actor, const char *BoneName) {
    return Actor->GetBonePos(BoneName, FVector());
}

AHUD *NewHUD = 0;

using json = nlohmann::json;
bool ExtremeExp = true;
static std::string EXP = " ";
static bool isCircle = true;
time_t rng = 0;
std::string ESP;
std::string Item;
std::string AIM;
std::string Memory;
std::string SilentAim;
std::string Floating;
std::string Setting;
pthread_t t;

uintptr_t ProcessEvent;

using namespace SDK;



FLinearColor RandomColor()
{
    // FLinearColor channels are normalized; keep the accent vivid without
    // generating out-of-range values that can produce inconsistent rendering.
    static float hue = 0.0f;
    constexpr float kTwoPi = 6.28318530718f;
    constexpr float kPhaseOffset = 2.09439510239f;

    hue = fmodf(hue + 0.025f, kTwoPi);
    return FLinearColor(
        0.5f + 0.5f * sinf(hue),
        0.5f + 0.5f * sinf(hue + kPhaseOffset),
        0.5f + 0.5f * sinf(hue + (2.0f * kPhaseOffset)),
        1.0f
    );
}


void NekoHook(FRotator &angles) 
{
    if (angles.Pitch > 180)
        angles.Pitch -= 360;
    if (angles.Pitch < -180)
        angles.Pitch += 360;

    if (angles.Pitch < -75.f)
        angles.Pitch = -75.f;
    else if (angles.Pitch > 75.f)
        angles.Pitch = 75.f;

    while (angles.Yaw < -180.0f)
        angles.Yaw += 360.0f;
    while (angles.Yaw > 180.0f)
        angles.Yaw -= 360.0f;
}

void NekoHook(float *angles) 
{
    if (angles[0] > 180)
        angles[0] -= 360;
    if (angles[0] < -180)
        angles[0] += 360;

    if (angles[0] < -75.f)
        angles[0] = -75.f;
    else if (angles[0] > 75.f)
        angles[0] = 75.f;

    while (angles[1] < -180.0f)
        angles[1] += 360.0f;
    while (angles[1] > 180.0f)
        angles[1] -= 360.0f;
}

void NekoHook(Vector3 angles) 
{
    if (angles.X > 180)
        angles.X -= 360;
    if (angles.X < -180)
        angles.X += 360;

    if (angles.X < -75.f)
        angles.X = -75.f;
    else if (angles.X > 75.f)
        angles.X = 75.f;

    while (angles.Y < -180.0f)
        angles.Y += 360.0f;
    while (angles.Y > 180.0f)
        angles.Y -= 360.0f;
}

FRotator Rotation = { };

struct sRegion {
    uintptr_t start, end;
};

std::vector<sRegion> trapRegions;

int GetIndex(int currentIndex, int arrayNum) {
    if (arrayNum <= 0) {
        return 0;
    }
    return (currentIndex + 1) % arrayNum;
}

float Random[11] = {0.9f, 1.0f, 1.1f, 1.2f, 1.3f, 1.4f, 1.5f, 1.6f, 1.7f, 1.9f, 2.0f};

float GetTimeInSeconds() 
{
    return std::chrono::duration<float>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}

static UEngine *GEngine = nullptr;
static UFont *tslFont = 0, *robotoTinyFont = 0;

bool EnsureFonts()
{
    // ESP only draws with tslFont. Treat the secondary distance-field font as
    // optional; requiring it made the entire overlay disappear on builds that
    // do not expose that asset even though the primary Roboto font was valid.
    if (tslFont)
        return true;

    // Object lookups are throttled and remain on the HUD/game thread instead
    // of continually polling from an unmanaged worker thread.
    static auto nextFontLookup = std::chrono::steady_clock::time_point::min();
    const auto now = std::chrono::steady_clock::now();
    if (now < nextFontLookup)
        return false;

    tslFont = UObject::FindObject<UFont>("Font Roboto.Roboto");
    if (!robotoTinyFont)
        robotoTinyFont = UObject::FindObject<UFont>("Font RobotoDistanceField.RobotoDistanceField");

    // Game builds can rename or strip the Roboto object path. The engine-owned
    // fonts are initialized with the HUD and are a reliable fallback, so a
    // missing optional asset cannot make every ESP primitive disappear.
    if (!tslFont && GEngine)
        tslFont = GEngine->SmallFont ? GEngine->SmallFont :
                  (GEngine->MediumFont ? GEngine->MediumFont : GEngine->TinyFont);
    if (!robotoTinyFont && GEngine)
        robotoTinyFont = GEngine->TinyFont ? GEngine->TinyFont : tslFont;

    nextFontLookup = now + std::chrono::seconds(1);
    return tslFont != nullptr;
}

float ScaleRand;
float TimeLift;

FVector TargetPos = { };

void DrawOutlinedText(AHUD *HUD, FString Text, FVector2D Pos, FLinearColor Color, FLinearColor OutlineColor, bool isCenter = false)
{
    if (!HUD || !HUD->Canvas || !tslFont)
        return;

    // Canvas text is rasterized by UE with font antialiasing. A solid dark
    // outline and a sub-pixel shadow keep it readable over any scene without
    // adding a coloured halo/glow.
    const FLinearColor outline(OutlineColor.R, OutlineColor.G, OutlineColor.B,
                               std::max(0.78f, OutlineColor.A));
    HUD->Canvas->K2_DrawText(tslFont, Text, Pos, Color, 0.0f,
                             FLinearColor(0.0f, 0.0f, 0.0f, 0.65f),
                             FVector2D(0.65f, 0.65f), isCenter, isCenter,
                             true, outline);
}

// Route all overlay strokes through the Canvas line path and keep a minimum
// sub-pixel-friendly width. It produces cleaner diagonals than the AHUD debug
// line wrapper, with one solid pass only (no glow layer).
void DrawCanvasLine(AHUD *HUD, float startX, float startY, float endX, float endY,
                    const FLinearColor &color, float thickness = 0.85f)
{
    if (!HUD || !HUD->Canvas)
        return;
    HUD->Canvas->K2_DrawLine(FVector2D(startX, startY), FVector2D(endX, endY),
                             std::max(0.85f, thickness), color);
}

struct D3DMatrix {
    float _11, _12, _13, _14;
    float _21, _22, _23, _24;
    float _31, _32, _33, _34;
    float _41, _42, _43, _44;
};

D3DMatrix QuatToMatrix(const FQuat &quat){
    D3DMatrix mat;
    float magnitude = std::sqrt(quat.X * quat.X + quat.Y * quat.Y + quat.Z * quat.Z + quat.W * quat.W);
    float qx = quat.X / magnitude;
    float qy = quat.Y / magnitude;
    float qz = quat.Z / magnitude;
    float qw = quat.W / magnitude;
    float xx = qx * qx;
    float xy = qx * qy;
    float xz = qx * qz;
    float xw = qx * qw;
    float yy = qy * qy;
    float yz = qy * qz;
    float yw = qy * qw;
    float zz = qz * qz;
    float zw = qz * qw;
    mat._11 = 1.0f - 2.0f * (yy + zz);
    mat._12 = 2.0f * (xy - zw);
    mat._13 = 2.0f * (xz + yw);
    mat._14 = 0.0f;
    mat._21 = 2.0f * (xy + zw);
    mat._22 = 1.0f - 2.0f * (xx + zz);
    mat._23 = 2.0f * (yz - xw);
    mat._24 = 0.0f;
    mat._31 = 2.0f * (xz - yw);
    mat._32 = 2.0f * (yz + xw);
    mat._33 = 1.0f - 2.0f * (xx + yy);
    mat._34 = 0.0f;
    mat._41 = 0.0f;
    mat._42 = 0.0f;
    mat._43 = 0.0f;
    mat._44 = 1.0f;
    return mat;
}

struct Matrix {float m[4][4];};
Matrix GetMatrix() {
    static UCanvas* Canvas = nullptr;
    if (Canvas == nullptr) {Canvas = UObject::FindObject<UCanvas>("Canvas Transient.DebugCanvasObject");}
    if (!Canvas) {return Matrix{};}
        uintptr_t lodalele;
    #if defined(__LP64__)
        lodalele = 0x270;
    #else
        lodalele = 0x200;
    #endif
    return *(Matrix*)((uintptr_t)Canvas + lodalele);
}

bool WorldToScreenPlayer(FVector pos, FVector &screen, int *distance) {
    Matrix ViewMatrix = GetMatrix();
    screen = {};
    *distance = 0;
    float screenW = (ViewMatrix.m[0][3] * pos.X) + (ViewMatrix.m[1][3] * pos.Y) + (ViewMatrix.m[2][3] * pos.Z + ViewMatrix.m[3][3]);
    if (screenW < 0.0001f)
        return false;
    *distance = (screenW / 100);
    float screenY = (ViewMatrix.m[0][1] * pos.X) + (ViewMatrix.m[1][1] * pos.Y) + (ViewMatrix.m[2][1] * (pos.Z + 85) + ViewMatrix.m[3][1]);
    float screenX = (ViewMatrix.m[0][0] * pos.X) + (ViewMatrix.m[1][0] * pos.Y) + (ViewMatrix.m[2][0] * pos.Z + ViewMatrix.m[3][0]);
    screen.Y = (glHeight / 2.f) - (glHeight / 2.f) * screenY / screenW;
    screen.X = (glWidth / 2.f) + (glWidth / 2.f) * screenX / screenW;
    float y1 = (glHeight / 2.f) - (ViewMatrix.m[0][1] * pos.X + ViewMatrix.m[1][1] * pos.Y + ViewMatrix.m[2][1] * (pos.Z - 95) + ViewMatrix.m[3][1]) * (glHeight / 2.f) / screenW;
    screen.Z = y1 - screen.Y;
    return !(screen.X == 0 && screen.Y == 0 && screen.Z == 0);
}

bool WorldToScreenBone(FVector Position, FVector2D *Screen) {
    Matrix ViewMatrix = GetMatrix();
    float ScreenW = (ViewMatrix.m[0][3] * Position.X) + (ViewMatrix.m[1][3] * Position.Y) + (ViewMatrix.m[2][3] * Position.Z + ViewMatrix.m[3][3]);
    if (ScreenW < 0.0001f)
        return false;
    ScreenW = 1 / ScreenW;
    float SightX = (glWidth / 2);
    float SightY = (glHeight / 2);
    Screen->X = SightX + (ViewMatrix.m[0][0] * Position.X + ViewMatrix.m[1][0] * Position.Y + ViewMatrix.m[2][0] * Position.Z + ViewMatrix.m[3][0]) * ScreenW * SightX;
    Screen->Y = SightY - (ViewMatrix.m[0][1] * Position.X + ViewMatrix.m[1][1] * Position.Y + ViewMatrix.m[2][1] * Position.Z + ViewMatrix.m[3][1]) * ScreenW * SightY;
    return true;
}

bool isObjectInvalid(UObject *obj) 
{
    if (!Tools::IsPtrValid(obj)) {
        return true;
    }

    if (!Tools::IsPtrValid(obj->ClassPrivate)) {
        return true;
    }

    if (obj->InternalIndex <= 0) {
        return true;
    }

    if (obj->NamePrivate.ComparisonIndex <= 0) {
        return true;
    }

    if ((uintptr_t) (obj) % sizeof(uintptr_t) != 0x0 &&
            (uintptr_t) (obj) % sizeof(uintptr_t) != 0x4) {
        return true;
    }

    if (std::any_of(trapRegions.begin(), trapRegions.end(), [obj](sRegion region) {
    return ((uintptr_t) obj) >= region.start && ((uintptr_t) obj) <= region.end;
    }) ||
    std::any_of(trapRegions.begin(), trapRegions.end(), [obj](sRegion region) {
        return ((uintptr_t) obj->ClassPrivate) >= region.start &&
               ((uintptr_t) obj->ClassPrivate) <= region.end;
    })) {
        return true;
    }

    return false;
}

struct FramePlayerData
{
    ASTExtraPlayerCharacter *player = nullptr;
    FVector2D headScreen{};
    FVector2D rootScreen{};
    float distance = 0.0f;
    float screenDistance = std::numeric_limits<float>::infinity();
    const char *exposedBone = nullptr;
    bool projected = false;
    bool visible = false;
};

struct VisibilitySample
{
    const char *exposedBone = nullptr;
    float sampledAt = -1000.0f;
};

static std::vector<AActor *> frameActors;
static std::vector<FramePlayerData> framePlayers;
static std::unordered_map<uintptr_t, VisibilitySample> visibilityCache;
static float frameDeltaSeconds = 1.0f / 60.0f;
static float frameElapsedSeconds = 0.0f;

void UpdateFrameTiming()
{
    static auto previousFrame = std::chrono::steady_clock::time_point{};
    const auto now = std::chrono::steady_clock::now();
    if (previousFrame == std::chrono::steady_clock::time_point{})
    {
        previousFrame = now;
        return;
    }

    const float measuredDelta = std::chrono::duration<float>(now - previousFrame).count();
    previousFrame = now;
    // A breakpoint, loading stall, or background resume should not make the
    // next aim adjustment jump across the screen.
    frameDeltaSeconds = std::max(1.0f / 240.0f, std::min(measuredDelta, 0.050f));
    frameElapsedSeconds += frameDeltaSeconds;
}

float GetFrameDeltaSeconds()
{
    return frameDeltaSeconds;
}

float GetFrameElapsedSeconds()
{
    return frameElapsedSeconds;
}

// Render callbacks run at display refresh rate. Emit diagnostics only when the
// pipeline state changes (and a compact heartbeat every few seconds), so
// logcat remains useful without becoming a source of frame hitches.
void LogEspRenderState(const char *state)
{
    static const char *previousState = nullptr;
    if (!previousState || strcmp(previousState, state) != 0)
    {
        LOGW("ESP state: %s", state);
        previousState = state;
    }
}

const char *DescribeLocalPawn(APawn *pawn)
{
    if (!pawn)
        return "null";
    if (isObjectInvalid(pawn))
        return "invalid";
    return pawn->IsA(ASTExtraPlayerCharacter::StaticClass())
        ? "player-character" : "not-player-character";
}

void LogEspFrameHeartbeat(AHUD *hud, UWorld *world,
                          ASTExtraPlayerController *controller,
                          ASTExtraPlayerCharacter *localPlayer,
                          const char *localPlayerSource)
{
    static float nextHeartbeatAt = 0.0f;
    if (frameElapsedSeconds < nextHeartbeatAt)
        return;

    size_t projectedPlayers = 0;
    size_t exposedPlayers = 0;
    for (const auto &player : framePlayers)
    {
        projectedPlayers += player.projected ? 1u : 0u;
        exposedPlayers += player.visible ? 1u : 0u;
    }

    APawn *acknowledgedPawn = controller ? controller->AcknowledgedPawn : nullptr;
    APawn *controllerPawn = controller ? controller->Pawn : nullptr;
    LOGI("ESP heartbeat: hud=%p canvas=%p world=%p controller=%p "
         "ackPawn=%p(%s) pawn=%p(%s) local=%p source=%s "
         "actors=%zu players=%zu projected=%zu exposed=%zu screen=%dx%d",
         static_cast<void *>(hud), hud ? static_cast<void *>(hud->Canvas) : nullptr,
         static_cast<void *>(world), static_cast<void *>(controller),
         static_cast<void *>(acknowledgedPawn), DescribeLocalPawn(acknowledgedPawn),
         static_cast<void *>(controllerPawn), DescribeLocalPawn(controllerPawn),
         static_cast<void *>(localPlayer), localPlayerSource ? localPlayerSource : "none",
         frameActors.size(), framePlayers.size(), projectedPlayers, exposedPlayers,
         glWidth, glHeight);
    nextHeartbeatAt = frameElapsedSeconds + 5.0f;
}

namespace
{
// Head-first preserves a head-only exposure. Body-first is used for chest
// preference, but still falls back to the head or limbs when that is all that
// is exposed from cover.
constexpr std::array<const char *, 20> kHeadPriorityBones = {
    "Head", "neck_01", "spine_03", "spine_02", "spine_01", "pelvis",
    "clavicle_r", "clavicle_l", "upperarm_r", "upperarm_l", "lowerarm_r",
    "lowerarm_l", "hand_r", "hand_l", "thigh_r", "thigh_l", "calf_r",
    "calf_l", "foot_r", "foot_l"
};
constexpr std::array<const char *, 20> kBodyPriorityBones = {
    "spine_03", "spine_02", "spine_01", "pelvis", "neck_01", "clavicle_r",
    "clavicle_l", "upperarm_r", "upperarm_l", "lowerarm_r", "lowerarm_l",
    "hand_r", "hand_l", "thigh_r", "thigh_l", "calf_r", "calf_l", "foot_r",
    "foot_l", "Head"
};

const char *FindExposedAimBone(ASTExtraPlayerCharacter *player,
                               ASTExtraPlayerController *controller)
{
    if (!player || !controller || !controller->PlayerCameraManager)
        return nullptr;

    const auto &priority = Cheat::Aimbot::Target == EAimTarget::Head
        ? kHeadPriorityBones
        : kBodyPriorityBones;
    for (const char *bone : priority)
    {
        if (controller->LineOfSightTo(controller->PlayerCameraManager,
                                      player->GetBonePos(bone, {}), false))
            return bone;
    }
    return nullptr;
}
} // namespace

UEngine *FindActiveGameEngine()
{
    // Keep the known object name as the fast path. The transient suffix varies
    // across launches (_0, _1, etc.), so do not let that one historical name
    // decide whether the complete overlay can render.
    if (auto *engine = UObject::FindObject<UEngine>("UAEGameEngine Transient.UAEGameEngine_1"))
        return engine;

    static UClass *engineClass = nullptr;
    if (!engineClass)
        engineClass = UObject::FindClass("Class Engine.Engine");
    if (!engineClass)
        return nullptr;

    auto &objects = UObject::GetGlobalObjects();
    const int objectCount = objects.Num();
    constexpr int kMaximumObjectCount = 2 * 1000 * 1000;
    if (objectCount <= 0 || objectCount > kMaximumObjectCount)
        return nullptr;

    for (int index = 0; index < objectCount; ++index)
    {
        auto *object = objects.GetByIndex(index);
        if (!object || isObjectInvalid(object) || !object->IsA(engineClass))
            continue;

        auto *engine = static_cast<UEngine *>(object);
        if (engine->GameViewport)
        {
            LOGI("ESP: using active engine instance %s", engine->GetFullName().c_str());
            return engine;
        }
    }
    return nullptr;
}

UWorld *GetWorld()
{
    // This function is reached from the HUD hook. Never sleep/retry in that
    // game-thread path: retry object discovery at a modest cadence instead.
    static auto nextEngineLookup = std::chrono::steady_clock::time_point::min();
    const auto now = std::chrono::steady_clock::now();

    // A level transition can replace the viewport. Reacquire its engine rather
    // than permanently retaining an instance which was valid only at startup.
    if (GEngine && (!GEngine->GameViewport || isObjectInvalid(GEngine)))
        GEngine = nullptr;
    if (!GEngine && now >= nextEngineLookup)
    {
        GEngine = FindActiveGameEngine();
        nextEngineLookup = now + std::chrono::seconds(1);
    }

    if (!GEngine || !GEngine->GameViewport)
        return nullptr;

    return GEngine->GameViewport->World;
}

TNameEntryArray *GetGNames()
{
    return ((TNameEntryArray *(*)()) (Cheat::libUE4Base + Cheat::GName_Offest))();
}

std::vector<AActor *> GetActors(UWorld *World = nullptr)
{
    if (!World)
        World = GetWorld();
    if (!World)
        return {};
    if (!World->PersistentLevel)
    {
        LogEspRenderState("persistent level is unavailable");
        return {};
    }

    struct ActorArray
    {
        uintptr_t base;
        int32_t count;
        int32_t max;
    };

    const auto actors = ((ActorArray *(*)(uintptr_t))
        (Cheat::libUE4Base + Cheat::ActorArray_Offest))(
        reinterpret_cast<uintptr_t>(World->PersistentLevel));

    // Treat game-owned array metadata as untrusted. A corrupt/stale count must
    // not turn a render callback into an unbounded read/allocation.
    constexpr int32_t kMaxActorsPerFrame = 4096;
    if (!actors || !actors->base || actors->count <= 0 ||
        actors->count > actors->max || actors->count > kMaxActorsPerFrame)
    {
        LogEspRenderState("actor-array metadata is invalid or empty");
        static float nextInvalidActorLogAt = 0.0f;
        if (frameElapsedSeconds >= nextInvalidActorLogAt)
        {
            LOGW("ESP actor array rejected: metadata=%p base=%p count=%d max=%d",
                 static_cast<void *>(actors),
                 actors ? reinterpret_cast<void *>(actors->base) : nullptr,
                 actors ? actors->count : 0, actors ? actors->max : 0);
            nextInvalidActorLogAt = frameElapsedSeconds + 5.0f;
        }
        return {};
    }

    std::vector<AActor *> actorsForFrame;
    actorsForFrame.reserve(static_cast<size_t>(actors->count));
    for (int32_t i = 0; i < actors->count; ++i)
    {
        auto actor = *reinterpret_cast<uintptr_t *>(
            actors->base + (static_cast<uintptr_t>(i) * sizeof(uintptr_t)));
        if (actor)
            actorsForFrame.push_back(reinterpret_cast<AActor *>(actor));
    }
    return actorsForFrame;
}

void RefreshFrameActors(UWorld *World)
{
    frameActors.clear();
    auto actors = GetActors(World);
    frameActors.reserve(actors.size());

    // Validate once per HUD frame. Draw and target-selection code can then use
    // the same snapshot rather than rescanning the game actor array.
    for (auto *actor : actors)
    {
        if (!isObjectInvalid(actor))
            frameActors.push_back(actor);
    }

    if (!actors.empty() && frameActors.empty())
    {
        LogEspRenderState("all actor pointers were rejected by validation");
        static float nextRejectedActorLogAt = 0.0f;
        if (frameElapsedSeconds >= nextRejectedActorLogAt)
        {
            LOGW("ESP actor validation rejected all %zu actor pointers", actors.size());
            nextRejectedActorLogAt = frameElapsedSeconds + 5.0f;
        }
    }
}

const std::vector<AActor *> &GetFrameActors()
{
    return frameActors;
}

const std::vector<FramePlayerData> &GetFramePlayers()
{
    return framePlayers;
}

const FramePlayerData *FindFramePlayer(ASTExtraPlayerCharacter *player)
{
    for (const auto &candidate : framePlayers)
    {
        if (candidate.player == player)
            return &candidate;
    }
    return nullptr;
}

void RefreshFramePlayers()
{
    framePlayers.clear();
    auto *localPlayer = Cheat::localPlayer;
    auto *localController = Cheat::localController;
    if (!localPlayer || !localController)
        return;

    framePlayers.reserve(frameActors.size());
    const float visibilityInterval = std::max(
        Cheat::Aimbot::BoneRefreshInterval, 1.0f / 30.0f);
    for (auto *actor : frameActors)
    {
        if (!actor->IsA(ASTExtraPlayerCharacter::StaticClass()))
            continue;

        auto *player = static_cast<ASTExtraPlayerCharacter *>(actor);
        if (player->PlayerKey == localPlayer->PlayerKey ||
            player->TeamID == localPlayer->TeamID || player->bDead || player->bHidden)
            continue;

        FramePlayerData candidate;
        candidate.player = player;
        candidate.distance = localPlayer->GetDistanceTo(player) / 100.0f;
        candidate.projected = W2S(player->GetBonePos("Head", {}), &candidate.headScreen) &&
            W2S(player->GetBonePos("Root", {}), &candidate.rootScreen);

        if (candidate.projected)
        {
            const float height = fabsf(candidate.rootScreen.Y - candidate.headScreen.Y);
            const float width = height * 0.20f;
            const FVector2D center(candidate.headScreen.X + (width * 0.5f),
                                   candidate.headScreen.Y + (height * 0.5f));
            candidate.screenDistance = FVector2D::Distance(
                FVector2D(glWidth * 0.5f, glHeight * 0.5f), center);
        }

        // Sample bone visibility below the HUD refresh rate. A candidate is
        // valid only when at least one trace reaches an exposed bone: a fully
        // covered player is not selected, head-only cover selects the head,
        // and any exposed limb/body point remains a valid fallback.
        auto &visibility = visibilityCache[reinterpret_cast<uintptr_t>(player)];
        if (frameElapsedSeconds - visibility.sampledAt >= visibilityInterval)
        {
            visibility.exposedBone = FindExposedAimBone(player, localController);
            visibility.sampledAt = frameElapsedSeconds;
        }
        candidate.exposedBone = visibility.exposedBone;
        candidate.visible = candidate.exposedBone != nullptr;
        framePlayers.push_back(candidate);
    }

    // Prevent the cache from retaining actor addresses after a long match or
    // map transition. Pruning is infrequent and outside the hot draw path.
    static float lastCachePrune = 0.0f;
    if (frameElapsedSeconds - lastCachePrune >= 10.0f)
    {
        const float expiration = frameElapsedSeconds - 15.0f;
        for (auto it = visibilityCache.begin(); it != visibilityCache.end();)
        {
            if (it->second.sampledAt < expiration)
                it = visibilityCache.erase(it);
            else
                ++it;
        }
        lastCachePrune = frameElapsedSeconds;
    }
}

template<class T>
void GetAllActors(std::vector<T *> &Actors)
{
    auto GWorld = GetWorld();
    if (!GWorld)
        return;

    TArray<AActor *> Actors2;
    UGameplayStatics::GetAllActorsOfClass(
        reinterpret_cast<UObject *>(GWorld), T::StaticClass(), &Actors2);
    for (int i = 0; i < Actors2.Num(); ++i)
        Actors.push_back(static_cast<T *>(Actors2[i]));
}

FVector operator*(const FVector &vector, float scalar)
{
    return FVector({vector.X * scalar, vector.Y * scalar, vector.Z * scalar});
}

FVector operator+(const FVector &lhs, const FVector &rhs) 
{
    return {lhs.X + rhs.X, lhs.Y + rhs.Y, lhs.Z + rhs.Z};
}

FVector operator-(const FVector &lhs, const FVector &rhs) 
{
    return {lhs.X - rhs.X, lhs.Y - rhs.Y, lhs.Z - rhs.Z};
}

FVector operator*(const FVector &lhs, const FVector &rhs) 
{
    return {lhs.X * rhs.X, lhs.Y * rhs.Y, lhs.Z * rhs.Z};
}

FVector operator/(const FVector &lhs, const FVector &rhs) 
{
    return {lhs.X / rhs.X, lhs.Y / rhs.Y, lhs.Z / rhs.Z};
}

SDK::FVector MultiplyVectorFloat(SDK::FVector a, float scalar) 
{
    return {a.X * scalar, a.Y * scalar, a.Z * scalar};
}

SDK::FVector SubtractVectors(SDK::FVector a, SDK::FVector b) {
    SDK::FVector result;
    result.X = a.X - b.X;
    result.Y = a.Y - b.Y;
    result.Z = a.Z - b.Z;
    return result;
}

SDK::FVector AddVectors(SDK::FVector a, SDK::FVector b) {
    SDK::FVector result;
    result.X = a.X + b.X;
    result.Y = a.Y + b.Y;
    result.Z = a.Z + b.Z;
    return result;
}

SDK::FVector MultiplyVectors(SDK::FVector a, SDK::FVector b) {
    SDK::FVector result;
    result.X = a.X * b.X;
    result.Y = a.Y * b.Y;
    result.Z = a.Z * b.Z;
    return result;
}

SDK::FVector DivideVectors(SDK::FVector a, SDK::FVector b) {
    SDK::FVector result;
    result.X = a.X / b.X;
    result.Y = a.Y / b.Y;
    result.Z = a.Z / b.Z;
    return result;
}

FVector Minus_VectorVector(const FVector& A, const FVector& B)
{
    return FVector{A.X - B.X, A.Y - B.Y, A.Z - B.Z};
}

FVector Add_VectorVector(const FVector& A, const FVector& B)
{
    return FVector{A.X + B.X, A.Y + B.Y, A.Z + B.Z};
}

FVector Multiply_VectorFloat(const FVector& A, float Scalar)
{
    return FVector{A.X * Scalar, A.Y * Scalar, A.Z * Scalar};
}

FVector CalculateWeaponMuzzlePosition(const FVector& weaponLocation, const FRotator& weaponRotation, float weaponBodyLength) {

    float radPitch = weaponRotation.Pitch * (3.14159265358979323846 / 180.0f);
    float radYaw = weaponRotation.Yaw * (3.14159265358979323846 / 180.0f);


    float forwardX = std::cos(radPitch) * std::cos(radYaw);
    float forwardY = std::cos(radPitch) * std::sin(radYaw);
    float forwardZ = std::sin(radPitch);


    FVector muzzlePosition = {
        weaponLocation.X + forwardX * weaponBodyLength,
        weaponLocation.Y + forwardY * weaponBodyLength,
        weaponLocation.Z + forwardZ * weaponBodyLength
    };
    return muzzlePosition;
}

FRotator ClampAngles(FRotator inRot) {
    FRotator outRot = inRot;
    if (outRot.Pitch > 180)
        outRot.Pitch -= 360;
    if (outRot.Pitch < -180)
        outRot.Pitch += 360;

    if (outRot.Pitch < -75.f)
        outRot.Pitch = -75.f;
    else if (outRot.Pitch > 75.f)
        outRot.Pitch = 75.f;

    while (outRot.Yaw < -180.0f)
        outRot.Yaw += 360.0f;
    while (outRot.Yaw > 180.0f)
        outRot.Yaw -= 360.0f;
    return outRot;
}

inline FLinearColor UIntToLinearColor(uint32_t color)
{
    // Assuming 0xAARRGGBB format
    float A = ((color >> 24) & 0xFF) / 255.f;
    float R = ((color >> 16) & 0xFF) / 255.f;
    float G = ((color >> 8) & 0xFF) / 255.f;
    float B = (color & 0xFF) / 255.f;
    return FLinearColor(R, G, B, A);
}

FRotator ToRotator(FVector local, FVector target) {
    FVector rotation = Minus_VectorVector(local, target);
    float hyp = sqrt(rotation.X * rotation.X + rotation.Y * rotation.Y);
    FRotator newViewAngle = {0};
    newViewAngle.Pitch = -atan(rotation.Z / hyp) * (180.f / (float) 3.14159265358979323846);
    newViewAngle.Yaw = atan(rotation.Y / rotation.X) * (180.f / (float) 3.14159265358979323846);
    newViewAngle.Roll = (float) 0.f;
    if (rotation.X >= 0.f)
        newViewAngle.Yaw += 180.0f;
    return newViewAngle;
}

void DrawRectangle(AHUD *HUD, FVector2D Pos, float Width, float Height, float Thickness, FLinearColor Color) 
{
    DrawCanvasLine(HUD, Pos.X, Pos.Y, Pos.X + Width, Pos.Y, Color, Thickness);
    DrawCanvasLine(HUD, Pos.X, Pos.Y, Pos.X, Pos.Y + Height, Color, Thickness);
    DrawCanvasLine(HUD, Pos.X + Width, Pos.Y, Pos.X + Width, Pos.Y + Height, Color, Thickness);
    DrawCanvasLine(HUD, Pos.X, Pos.Y + Height, Pos.X + Width, Pos.Y + Height, Color, Thickness);
}

void DrawFilledRectangle(AHUD *HUD, FVector2D Pos, float Width, float Height, FLinearColor Color) 
{
    HUD->DrawRect(Color, Pos.X, Pos.Y, Width, Height);
}

bool isInsideFOVs(int x, int y) {
    if (!Cheat::BulletTrack::Enable)
        return true;

    int circle_x = glWidth / 2;
    int circle_y = glHeight / 2;
    int rad = Cheat::BulletTrack::Fov * 400.0f;
    return (x - circle_x) * (x - circle_x) + (y - circle_y) * (y - circle_y) <= rad * rad;
}

namespace
{
struct AimTargetLock
{
    ASTExtraPlayerCharacter *player = nullptr;
    const char *bone = "Head";
    float acquiredAt = 0.0f;
    float activationDelay = 0.0f;
    float nextBoneRefreshAt = 0.0f;
};

AimTargetLock aimTargetLock;

float NormalizeAxis(float angle)
{
    while (angle > 180.0f)
        angle -= 360.0f;
    while (angle < -180.0f)
        angle += 360.0f;
    return angle;
}

float ClampMagnitude(float value, float maxMagnitude)
{
    if (maxMagnitude <= 0.0f)
        return value;
    return std::max(-maxMagnitude, std::min(value, maxMagnitude));
}

bool IsAimCandidate(const FramePlayerData &candidate, bool retainingLock)
{
    const auto *player = candidate.player;
    if (!player || !candidate.projected || player->bDead || player->bHidden)
        return false;
    if (Cheat::Aimbot::IgnoreKnock && player->Health <= 0.0f)
        return false;
    if (Cheat::Aimbot::IgnoreBot && (player->bIsAI || player->bEnsure))
        return false;
    // An aim lock always requires one cached exposed bone. This is kept
    // independent of the legacy visibility toggle so full cover can never
    // produce an automatic lock.
    if (!candidate.visible)
        return false;
    if (Cheat::Aimbot::Range > 0.0f && candidate.distance > Cheat::Aimbot::Range)
        return false;

    if (Cheat::Aimbot::Radius > 0.0f)
    {
        const float radius = Cheat::Aimbot::Radius * (retainingLock ? 1.20f : 1.0f);
        if (candidate.screenDistance > radius)
            return false;
    }
    return true;
}

void ArmAimTargetLock(ASTExtraPlayerCharacter *player)
{
    const float now = GetFrameElapsedSeconds();
    const uint32_t targetSeed = static_cast<uint32_t>(
        reinterpret_cast<uintptr_t>(player) >> 4);
    // Keep reaction timing deterministic for a target lock, but vary it a
    // little between enemies so the automatic motion does not start identically
    // after every acquisition.
    const float variation = Cheat::Aimbot::Humanize
        ? 0.035f + static_cast<float>(targetSeed % 70) / 1000.0f
        : 0.0f;
    aimTargetLock.player = player;
    aimTargetLock.bone = "Head";
    aimTargetLock.acquiredAt = now;
    aimTargetLock.activationDelay = std::max(0.0f,
        Cheat::Aimbot::ReactionDelay) + variation;
    aimTargetLock.nextBoneRefreshAt = now;
}

void ClearAimTargetLock()
{
    aimTargetLock = {};
}
} // namespace

const char *GetPreferredAimBone(ASTExtraPlayerCharacter *player,
                                ASTExtraPlayerController *)
{
    if (const auto *framePlayer = FindFramePlayer(player))
        return framePlayer->exposedBone;
    return nullptr;
}

const char *GetAimTargetBone(ASTExtraPlayerCharacter *target)
{
    // Head mode favors the head but falls back to the currently exposed bone;
    // this keeps tracking valid when cover hides the head but leaves a limb or
    // body point visible.
    if (Cheat::Aimbot::Target == EAimTarget::Head)
    {
        if (const auto *framePlayer = FindFramePlayer(target);
            framePlayer && framePlayer->exposedBone)
            return framePlayer->exposedBone;
        return "Head";
    }

    const float now = GetFrameElapsedSeconds();
    if (aimTargetLock.player != target)
        ArmAimTargetLock(target);

    if (now >= aimTargetLock.nextBoneRefreshAt)
    {
        if (const char *bone = GetPreferredAimBone(target, Cheat::localController))
            aimTargetLock.bone = bone;
        aimTargetLock.nextBoneRefreshAt = now + std::max(
            Cheat::Aimbot::BoneRefreshInterval, 1.0f / 60.0f);
    }
    return aimTargetLock.bone;
}

float GetAimTargetLockAge()
{
    return aimTargetLock.player
        ? std::max(0.0f, GetFrameElapsedSeconds() - aimTargetLock.acquiredAt)
        : 0.0f;
}

float GetHumanizedAimWarmup()
{
    if (!aimTargetLock.player || !Cheat::Aimbot::Humanize)
        return aimTargetLock.player ? 1.0f : 0.0f;

    const float elapsed = GetAimTargetLockAge() - aimTargetLock.activationDelay;
    if (elapsed <= 0.0f)
        return 0.0f;

    const float duration = std::max(Cheat::Aimbot::AcquisitionTime, 0.001f);
    const float progress = std::min(elapsed / duration, 1.0f);
    // Smoothstep avoids a sudden first correction when automatic tracking
    // begins, while still converging reliably on a moving target.
    return progress * progress * (3.0f - (2.0f * progress));
}

ASTExtraPlayerCharacter *GetTargetForAimBot()
{
    const auto &players = GetFramePlayers();
    if (!Cheat::localPlayer || !Cheat::localController)
    {
        ClearAimTargetLock();
        return nullptr;
    }

    // A small retention margin keeps the target stable as players cross the
    // centerline, preventing the camera from flickering between candidates.
    if (Cheat::Aimbot::StickyTarget)
    {
        if (const auto *locked = FindFramePlayer(aimTargetLock.player);
            locked && IsAimCandidate(*locked, true))
        {
            return locked->player;
        }
    }

    const FramePlayerData *best = nullptr;
    float bestScore = std::numeric_limits<float>::infinity();
    for (const auto &candidate : players)
    {
        if (!IsAimCandidate(candidate, false))
            continue;

        // Prioritize crosshair proximity. A slight distance term breaks ties
        // naturally without causing a target switch for small screen movement.
        const float score = candidate.screenDistance + (candidate.distance * 0.10f);
        if (score < bestScore)
        {
            bestScore = score;
            best = &candidate;
        }
    }

    if (!best)
    {
        ClearAimTargetLock();
        return nullptr;
    }

    if (aimTargetLock.player != best->player)
        ArmAimTargetLock(best->player);
    return best->player;
}

auto GetTargetByPussy() 
{
    ASTExtraPlayerCharacter *result = 0;
    float max = std::numeric_limits<float>::infinity();
    const auto &Actors = GetFrameActors();

    auto localPlayer = Cheat::localPlayer;
    auto localController = Cheat::localController;
    FVector PlayerPos = {};

    if (localPlayer) {
        for (int i = 0; i < Actors.size(); i++) {
            auto Actor = Actors[i];
            if (Actor->IsA(ASTExtraPlayerCharacter::StaticClass())) {

                auto Player = (ASTExtraPlayerCharacter *) Actor;
                float distx = localPlayer->GetDistanceTo(Player) / 100.0f;

                if (distx > Cheat::BulletTrack::Range)
                    continue;

                if (Player->PlayerKey == localPlayer->PlayerKey)
                    continue;

                if (Player->TeamID == localPlayer->TeamID)
                    continue;

                if (Player->bDead)
                    continue;

                if (Player->bHidden)
                    continue;

                if (Cheat::BulletTrack::IgnoreKnock) {
                    if (Player->Health == 0.0f)
                        continue;
                }

                if (Cheat::BulletTrack::VisCheck)
                {
                    if (!localController->LineOfSightTo(Player, {0, 0, 0}, true))
                        continue;
                }

                if (Cheat::BulletTrack::iGnoreBot) {
                    if (Player->bEnsure)
                        continue;
                }
                auto Root = Player->GetBonePos("Root", {});
                auto Head = Player->GetBonePos("Head", {});
                FVector2D RootSc, HeadSc;
                if (W2S(Root, &RootSc) && W2S(Head, &HeadSc)) {
                    float height = abs(HeadSc.Y - RootSc.Y);
                    float width = height * 0.20f;

                    FVector middlePoint = {HeadSc.X + (width / 2), HeadSc.Y + (height / 2), 0};
                    if ((middlePoint.X >= 0 && middlePoint.X <= glWidth) &&
                            (middlePoint.Y >= 0 && middlePoint.Y <= glHeight)) {
                        FVector2D v2Middle = FVector2D((float)(glWidth / 2), (float)(glHeight / 2));
                        FVector2D v2Loc = FVector2D(middlePoint.X, middlePoint.Y);

                    if (isInsideFOVs((int)middlePoint.X, (int)middlePoint.Y)) 
                    {
                        float dist = FVector2D::Distance(v2Middle, v2Loc);

                        if (dist < max) {
                            max = dist;
                            result = Player;
                        }
                    }
                }
            }
        }
    }
}
    return result;
}

const char *GetVehicleName(ASTExtraVehicleBase *Vehicle) 
{
    switch (Vehicle->VehicleShapeType) 
    {
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Motorbike:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Motorbike_SideCart:
            return "Motorbike";

        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Dacia:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_HeavyDacia:
            return "Dacia";

        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_MiniBus:
            return "Mini Bus";

        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_PickUp:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_PickUp01:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_HeavyPickup:
            return "Pick Up";

        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Buggy:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_HeavyBuggy:
            return "Buggy";

        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_UAZ:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_UAZ01:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_UAZ02:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_UAZ03:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_HeavyUAZ:
            return "UAZ";

        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_PG117:
            return "PG117";

        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Aquarail:
            return "Aquarail";

        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Mirado:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Mirado01:
            return "Mirado";

        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Rony:
            return "Rony";

        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Scooter:
            return "Scooter";

        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_SnowMobile:
            return "Snow Mobile";

        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_TukTukTuk:
            return "Tuk Tuk";

        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_SnowBike:
            return "Snow Bike";

        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Surfboard:
            return "Surf Board";

        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Snowboard:
            return "Snow Board";

        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Amphibious:
            return "Amphibious";

        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_LadaNiva:
            return "Lada Niva";

        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_UAV:
            return "UAV";

        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_MegaDrop:
            return "Mega Drop";

        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Lamborghini:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Lamborghini01:
            return "Lamborghini";

        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_GoldMirado:
            return "Gold Mirado";

        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_BigFoot:
            return "Big Foot";

        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_HeavyUH60:
            return "UH60";

        default:
            return "Vehicle";
    }
    return "Vehicle";
}

namespace Settings 
{
    static int Tab = 1;
}

void RenderESPPRIVATE(AHUD* HUD, int ScreenWidth, int ScreenHeight)
{
    glWidth = ScreenWidth;
    glHeight = ScreenHeight;
    UpdateFrameTiming();

    if (!HUD)
    {
        LogEspRenderState("HUD pointer is null");
        frameActors.clear();
        framePlayers.clear();
        Cheat::localPlayer = nullptr;
        Cheat::localController = nullptr;
        ClearAimTargetLock();
        return;
    }
    if (!HUD->Canvas)
    {
        // If this persists, the ProcessEvent handler is running before the
        // original HUD callback prepares Canvas. It deliberately dispatches
        // the original callback before attempting overlay rendering.
        LogEspRenderState("HUD Canvas is unavailable");
        frameActors.clear();
        framePlayers.clear();
        Cheat::localPlayer = nullptr;
        Cheat::localController = nullptr;
        ClearAimTargetLock();
        return;
    }

    auto *world = GetWorld();
    if (!world)
        LogEspRenderState("UWorld is unavailable");

    // ReceiveDrawHUD belongs to the local player's HUD, so PlayerOwner is the
    // most reliable controller route. In the current BGMI flow ServerConnection
    // can legitimately be null while the HUD is already drawing, which was
    // leaving the renderer without a controller despite a valid Canvas.
    ASTExtraPlayerController *localController = nullptr;
    const char *controllerSource = nullptr;
    if (HUD->PlayerOwner && !isObjectInvalid(HUD->PlayerOwner))
    {
        localController = static_cast<ASTExtraPlayerController *>(HUD->PlayerOwner);
        controllerSource = "HUD PlayerOwner";
    }
    else if (world && world->NetDriver && world->NetDriver->ServerConnection &&
             !isObjectInvalid(world->NetDriver->ServerConnection) &&
             world->NetDriver->ServerConnection->PlayerController &&
             !isObjectInvalid(world->NetDriver->ServerConnection->PlayerController))
    {
        localController = static_cast<ASTExtraPlayerController *>(
            world->NetDriver->ServerConnection->PlayerController);
        controllerSource = "NetDriver ServerConnection";
    }
    if (!localController)
        LogEspRenderState("local controller is unavailable");
    else
    {
        static ASTExtraPlayerController *lastLoggedController = nullptr;
        if (lastLoggedController != localController)
        {
            LOGI("ESP local controller resolved through %s: %p", controllerSource,
                 static_cast<void *>(localController));
            lastLoggedController = localController;
        }
    }

    RefreshFrameActors(world);

    ASTExtraPlayerCharacter *localPlayer = nullptr;
    const char *localPlayerSource = "none";
    if (localController)
    {
        // The acknowledged pawn is normally ready first, while Pawn is the
        // stable fallback on BGMI flows where acknowledgement is delayed.
        const auto asLocalPlayerCharacter = [](APawn *pawn) -> ASTExtraPlayerCharacter *
        {
            if (!pawn || isObjectInvalid(pawn) ||
                !pawn->IsA(ASTExtraPlayerCharacter::StaticClass()))
                return nullptr;
            return static_cast<ASTExtraPlayerCharacter *>(pawn);
        };
        localPlayer = asLocalPlayerCharacter(localController->AcknowledgedPawn);
        if (localPlayer)
            localPlayerSource = "acknowledged-pawn";
        if (!localPlayer)
        {
            localPlayer = asLocalPlayerCharacter(localController->Pawn);
            if (localPlayer)
                localPlayerSource = "controller-pawn";
        }

        // Retain the actor-snapshot fallback for flows where neither controller
        // pawn has replicated but PlayerKey is already available.
        if (!localPlayer)
        {
            for (auto *actor : GetFrameActors())
            {
                if (!actor->IsA(ASTExtraPlayerCharacter::StaticClass()))
                    continue;

                auto *player = static_cast<ASTExtraPlayerCharacter *>(actor);
                if (player->PlayerKey == localController->PlayerKey)
                {
                    localPlayer = player;
                    localPlayerSource = "actor-snapshot";
                    break;
                }
            }
        }
    }

    Cheat::localPlayer = localPlayer;
    Cheat::localController = localController;
    RefreshFramePlayers();

    const bool fontsReady = EnsureFonts();
    if (!localPlayer)
        LogEspRenderState("local player was not found in actor snapshot");
    else if (!fontsReady)
        LogEspRenderState("ESP font assets are unavailable");
    else
        LogEspRenderState("ready");

    LogEspFrameHeartbeat(HUD, world, localController, localPlayer, localPlayerSource);
}

void Box4LineHUD(
    AHUD* HUD,
    float X, 
    float Y, 
    float W, 
    float H, 
    float Thickness, 
    float CornerRatio, 
    FLinearColor Color
)
{
    float cornerW = W * CornerRatio;
    float cornerH = H * CornerRatio;

    // Top Left
    DrawCanvasLine(HUD, X, Y, X + cornerW, Y, Color, Thickness);
    DrawCanvasLine(HUD, X, Y, X, Y + cornerH, Color, Thickness);

    // Top Right
    DrawCanvasLine(HUD, X + W - cornerW, Y, X + W, Y, Color, Thickness);
    DrawCanvasLine(HUD, X + W, Y, X + W, Y + cornerH, Color, Thickness);

    // Bottom Left
    DrawCanvasLine(HUD, X, Y + H - cornerH, X, Y + H, Color, Thickness);
    DrawCanvasLine(HUD, X, Y + H, X + cornerW, Y + H, Color, Thickness);

    // Bottom Right
    DrawCanvasLine(HUD, X + W - cornerW, Y + H, X + W, Y + H, Color, Thickness);
    DrawCanvasLine(HUD, X + W, Y + H - cornerH, X + W, Y + H, Color, Thickness);
}

#include <cmath> // cosf, sinf

// Uses short Canvas line segments so rings are smooth, flat, and free of glow.
template<typename HUD_T, typename COLOR_T>
inline void DrawCircleHelper(HUD_T* HUD, float X, float Y, float Radius, COLOR_T Color,
                             int NumSegments = 36, float Thickness = 1.0f)
{
    if (!HUD || !HUD->Canvas) return;
    const float PI = 3.14159265358979323846f;
    float angleStep = 2.0f * PI / NumSegments;

    float prevX = X + Radius;
    float prevY = Y;
    for (int i = 1; i <= NumSegments; ++i)
    {
        float angle = i * angleStep;
        float newX = X + cosf(angle) * Radius;
        float newY = Y + sinf(angle) * Radius;

        DrawCanvasLine(HUD, prevX, prevY, newX, newY, Color, Thickness);

        prevX = newX;
        prevY = newY;
    }
}
