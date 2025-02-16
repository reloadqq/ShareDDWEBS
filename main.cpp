#include "Includes.h"
#include "Tools.h"
#include "fake_dlfcn.h"
#include "Vector3.hpp"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_android.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "StrEnc.h"
#include "plthook.h"


#include "Items.h"
#include "fontch.h"  
#include "obfuscate.h"
#include "KittyMemory/MemoryPatch.h"

#include "json.hpp"
#include "Rect.h"
#include "Iconcpp.h"
#include "ImguiPP.cpp"
#include "Menu.h"
#include "Font.h"
#include "Font.h"
#include "Icon.h"
using json = nlohmann::json;
#define SLEEP_TIME 1000LL / 60LL
#include "SDK.hpp"
using namespace SDK;
#include <curl/curl.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include "base64/base64.h"




float size_child = 0;
static float SliderFloat = 0;
char extras[32];
#define PATCH_LIB
#define COLOR_GREEN Color(0.f, 0.5f, 0.f, 1.f)
#define COLOR_BLACK Color(0, 0, 0, 1.f)
#define COLOR_WHITE Color(1.f, 1.f, 1.f, 1.f)
#define COLOR_RED   Color(1.f, 0, 0, 1.f)
#define COLOR_LIME  Color(0, 1.f, 0, 1.f)
#define COLOR_BLUE  Color(0, 0, 1.f, 1.f)
#define COLOR_ORANGE Color(1.f, 0.6f, 0.f, 1.f)
#define IM_PI 3.14159265358979323846f
#define RAD2DEG(x) ((float)(x) * (float)(180.f / IM_PI))
#define DEG2RAD(x) ((float)(x) * (float)(IM_PI / 180.f))

static float isRed = 0.0f, isGreen = 0.01f, isBlue = 0.0f;

uintptr_t AimBullet_Offset;
uintptr_t GWorld_Offset, GUObjectArray_Offset, SilentAim_Offset;

#define GNames_Offset 0x483167c
 #define GEngine_Offset 0x9e1cc1c //UEngine
 #define GEngine_Offset 0x9e01220 //UlocalPlayer
 #define GUObject_Offset 0x9bcac18
 #define GetActorArray_Offset 0x673c4e8
 #define ProccesEvent_Offset 0x62a4b5c //Child
 #define GNativeAndroidApp_Offset 0x9a02f38
 #define Actors_Offset 0x70



static int a = 0;
time_t rng = 0;
static std::string EXP = " ";
static std::string SLOT = " ";
static std::string modname = " ";
static std::string mod_status = " ";
static std::string credit = " ";
static std::string days = " ";
static std::string key = " ";
static std::string keys = " ";

std::string KeySlot = "";
std::string FlotingText = "";
std::string expiredDate = "";

//std::string expiredDate = "";
ImFont* Arabic;
json items_data;
std::string g_Token, g_Auth;
bool bValid = false;
bool show_another_window2 = false;
static bool HideWindow = true;
bool unlock;
bool shit = false;
bool LobbyBy = false;
bool ActiveESP = false;
bool ItemsMenu = true;

float RGB = 5;
float sliderint;
float FOVSize = 5;
float FOVSizea = 120;
uintptr_t anort;
uintptr_t UE4;
uintptr_t ANOGS;
uintptr_t Anogs;
uintptr_t g_UE4;
uintptr_t cloud;
uintptr_t anogs;
uintptr_t g_gcloud;
uintptr_t PandoraVideo;
uintptr_t GKPxStudio;
uintptr_t tgpa;
uintptr_t cubehawk;
uintptr_t shared;
uintptr_t INTLFoundation;
uintptr_t INTLCompliance;
uintptr_t CrashSight;
uintptr_t antiban;
uintptr_t GCloudVoice;
uintptr_t ijkffmpeg;
uintptr_t gcloudcore;
uintptr_t gnustl_shared;
uintptr_t igshare;
uintptr_t ITOP;
uintptr_t marsxlog;
uintptr_t swappy;
uintptr_t GvoiceNN;
uintptr_t TDataMaster;
uintptr_t TPRT;
uintptr_t TDMASTER;

android_app *g_App = 0;
//;time_t rng = 0;
ImFont* logo;
//ImFont* main_close;
ASTExtraPlayerCharacter *g_LocalPlayer = 0;
ASTExtraPlayerController *g_LocalController = 0;
///float FOVSizea = 100;
///float FOVSize = 5;
bool HIDEESP = true;
bool initImGui = false;
int screenWidth = -1, glWidth, screenHeight = -1, glHeight;
float density = -1;

std::map<int, bool> Items;
std::map<int, float *> ItemColors;

bool WriteAddr(void *addr, void *buffer, size_t length) {
    unsigned long page_size = sysconf(_SC_PAGESIZE);
    unsigned long size = page_size * sizeof(uintptr_t);
    return mprotect((void *) ((uintptr_t) addr - ((uintptr_t) addr % page_size) - page_size), (size_t) size, PROT_EXEC | PROT_READ | PROT_WRITE) == 0 && memcpy(addr, buffer, length) != 0;
}
template<typename T>
void Write(uintptr_t addr, T value) {
    WriteAddr((void *) addr, &value, sizeof(T));
}

static UEngine *GEngine = 0;
UWorld *GetWorld() {
    while (!GEngine) {
        GEngine = UObject::FindObject<UEngine>("UAEGameEngine Transient.UAEGameEngine_1"); // Auto 
        sleep(1);
    }
    if (GEngine) {
        auto ViewPort = GEngine->GameViewport;

        if (ViewPort) {
   //return {};
            return ViewPort->World;
        }
    }
    return 0;
}
TNameEntryArray *GetGNames() {
    return ((TNameEntryArray *(*)()) (UE4 + GNames_Offset))();
}

std::vector<AActor *> getActors() {
    auto World = GetWorld();
    if (!World)
        return std::vector<AActor *>();

    auto PersistentLevel = World->PersistentLevel;
    if (!PersistentLevel)
        return std::vector<AActor *>();

    auto Actors = *(TArray<AActor *> *)((uintptr_t) PersistentLevel + Actors_Offset);

    std::vector<AActor *> actors;
    for (int i = 0; i < Actors.Num(); i++) {
        auto Actor = Actors[i];
        if (Actor) {
            actors.push_back(Actor);
        }
    }
    return actors;
}


enum EAimBy {
    Distance = 0,
	FOV = 1
};

enum EAimB {
    Bt90 = 0,
	Bt360 = 1
};

enum EAimTarget {
    Head = 0,
    Chest = 1
};

enum EAimTrigger {
    None = 0,
    Shooting = 1,
    Scoping = 2,
    Both = 3,
    Any = 4
};
    struct sOTHER {
        bool FPS;
        bool EXPIRYTIME;
    };

//std::map<int, bool> Items;

struct sConfig {
	bool Nation;
	bool Bypass;
	float Cross;
	float Meter;
	bool FPS;
	float Skill;
	float Skill1;
	float Skill3;
	float Skill4;
	float FOVSizea;
	float FOVSize;
	float Skill2;
	float Line;
	float Recc;
	float Distance;
	float Box;
	float Skeleton;
	float Production;
	bool FightFps;
	bool IPadView;
	bool AutoUpdate = false;
    bool EnableAnimations = true;
    float AnimDuration = 1.0f;
	bool ESP;
	
    
	
	
	
	
    struct sPlayerESP {
		bool RGB;
		bool LineBelow;
		bool KERO;
		bool Island;
        bool LineMid;
        bool Recc;
        bool LootBoxItems;
        bool Box3D;
        bool Box4Line;
        bool Namee;
        bool keroz;
        bool LineTop;
        bool VehicleFuel;
        bool VehicleHP;
        bool WeaponId;
        bool BoxItems;
		bool ActiveEsp;
		bool MagicBullet;
		bool VehicleDist;
		bool Alert;
	//	bool VehicleFuel;
		bool Nation;
		//bool Box3D;
        bool Line;
		bool Radar;
		bool RadarDraw2;
		bool Radar1;
		bool Radar2;
		bool Radar3;
		bool Radar4;
		bool Warning;
        bool Box;
        bool Skeleton;
        bool Health;
        bool Grenade;
        bool ShowKnockedHealth;
        bool KEROO3;
        bool Name;
        bool Distance;
        bool TeamID;
        bool NoBot;
        bool LootBox;
        bool Vehicle;
    };
    sPlayerESP PlayerESP{0};

    struct sAimMenu {
        bool Enable;
        bool Less;
		bool Enable2;
        bool AimBot;
        bool SilentAim;
		float Cross;
        float RecZ;
		float RecX;
		float RecY;
		EAimBy AimBy;
	    EAimB  AimB;
        EAimTarget Target;
        EAimTrigger Trigger;
        bool Pred;
        bool ReCo;
        bool IgnoreKnocked;
        bool VisCheck;
		bool IgnoreBots;
		bool IgnoreBot;
		bool Recc;
		bool Predection;
    };
	sAimMenu SilentAim{0};
	sAimMenu AimBot{0};

	struct sMEM
	{
    bool Warning;
    bool Warning1;
	};
	sMEM MEM{0};
	struct sHighRisk
	{
		bool Shake;
		bool Recoil;
		bool Recoil1;
		bool RGB;
		bool Instant;
		bool HitEffect;
		bool Wall;
		bool FlashSdk;
		bool Wal;
		bool WideView;
        bool FPSUnlock = true;
        bool TSSBypass = true;
        bool TSSBypass2 = true;
        bool blockspect = true;
	};
	sHighRisk HighRisk{0};


struct sGOODVIEW {
    	bool ENABLE;
		bool UP;
		bool ON;
		bool DOWN;
		bool FRONT;
		bool BEHIND;
		bool RIGHT;
		bool LEFT;
		
		
	};
	sGOODVIEW GOODVIEW;


struct sESPMenu {
		bool Line;
		bool Box;
		bool fk;
		bool Skeleton;
		bool AUTOGOODZ;
		bool AUTOGOODY;
		bool AUTOGOODX;
		bool AUTOGOODXX;
		bool AUTOGOODYY;
		bool Skeletonn;
		bool Health;
		bool Name;
		bool Distance;
		bool TeamID;
		bool AutoFire;
	};
	sESPMenu ESPMenu;

struct sColorsESP
	{
		float *PVisibile;
        float *PNonVis;
        float *PVLine;
        float *PVILine;
        float *BVLine;
        float *BVILine;
        float *PVBox;
        float *PVIBox;
        float *BVBox;
        float *BVIBox;
        float *PVSkeleton;
        float *PVISkeleton;
        float *BVSkeleton;
        float *BVISkeleton;
		float *Fov;
		float *Text;
		float *Box3D;
		float *RGB;
		float *Count;
        float *TeamID;
        float *Name;
        float *WeaponId;
        float *Distance;
        float *Vehicle;
        float *Items;
    }; 
	sColorsESP ColorsESP{0};
	struct sOTHER {
        bool FPS;
        bool HIDEESP;
        bool EXPIRYTIME;
    };
    sOTHER OTHER{0};
};
sConfig Config{0};
static bool Feu;
#define CREATE_COLOR(r, g, b, a) new float[4] {(float)r, (float)g, (float)b, (float)a};

static float LineSize = 0.6f;
static float BoxSize = 1.7f;
static float SkeletonSize = 1.0f;
static float NameSize = 34.0f;
static float DistanceSize = 35.0f;
static float VehicleSize = 30.0f;

float RadarXW=320,RadarYW=255;


struct sRegion {
    uintptr_t start, end;
};

std::vector<sRegion> trapRegions;

bool isObjectInvalid(UObject *obj) {
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

    if ((uintptr_t)(obj) % sizeof(uintptr_t) != 0x0 && (uintptr_t)(obj) % sizeof(uintptr_t) != 0x4) {
        return true;
    }

    if (std::any_of(trapRegions.begin(), trapRegions.end(), [obj](sRegion region) { return ((uintptr_t) obj) >= region.start && ((uintptr_t) obj) <= region.end; }) ||
        std::any_of(trapRegions.begin(), trapRegions.end(), [obj](sRegion region) { return ((uintptr_t) obj->ClassPrivate) >= region.start && ((uintptr_t) obj->ClassPrivate) <= region.end; })) {
        return true;
    }

    return false;
}

std::string getObjectPath(UObject *Object) {
    std::string s;
    for (auto super = Object->ClassPrivate; super; super = (UClass *) super->SuperStruct) {
        if (!s.empty())
            s += ".";
        s += super->NamePrivate.GetName();
    }
    return s;
}

// ======================================================================== //

int32_t ToColor(float *col) {
    return ImGui::ColorConvertFloat4ToU32(*(ImVec4 *) (col));
}

FRotator ToRotator(FVector local, FVector target) {
    FVector rotation = UKismetMathLibrary::Subtract_VectorVector(local, target);

    float hyp = sqrt(rotation.X * rotation.X + rotation.Y * rotation.Y);

    FRotator newViewAngle = {0};
    newViewAngle.Pitch = -atan(rotation.Z / hyp) * (180.f / (float) 3.14159265358979323846);
    newViewAngle.Yaw = atan(rotation.Y / rotation.X) * (180.f / (float) 3.14159265358979323846);
    newViewAngle.Roll = (float) 0.f;

    if (rotation.X >= 0.f)
        newViewAngle.Yaw += 180.0f;

    return newViewAngle;
}


#define W2S(w, s) UGameplayStatics::ProjectWorldToScreen(localController, w, true, s)


bool isInsideFOVs(int x, int y) {
    if (!Config.AimBot.Cross)
        return true;

    int circle_x = glWidth / 2;
    int circle_y = glHeight / 2;
    int rad = Config.AimBot.Cross*0.5f;
    return (x - circle_x) * (x - circle_x) + (y - circle_y) * (y - circle_y) <= rad * rad;
}

auto GetTargetForAimBot() {
   ASTExtraPlayerCharacter *result = 0;
    float max = std::numeric_limits<float>::infinity();
    auto Actors = getActors();
    auto localPlayer = g_LocalPlayer;
    auto localController = g_LocalController;
    if (localPlayer)
    {
        for (int i = 0; i < Actors.size(); i++) {
                    auto Actor = Actors[i];
            if (isObjectInvalid(Actor))
                continue;
            if (Actor->IsA(ASTExtraPlayerCharacter::StaticClass()))
            {
                auto Player = (ASTExtraPlayerCharacter *)Actor;
                auto Target = (ASTExtraPlayerCharacter *) Actor;

                float dist = localPlayer->GetDistanceTo(Target) / 150.0f;    
                if (dist > 150.0f)
                    continue;
                        
                if (Player->PlayerKey == localPlayer->PlayerKey)
                    continue;
                if (Player->TeamID == localPlayer->TeamID)
                    continue;
                if (Player->bDead)
                    continue;
                    
                    
                if (Config.AimBot.IgnoreKnocked) {
                    if (Player->Health == 0.0f)
                        continue;
                }

                if (Config.AimBot.VisCheck) {
                    if (!localController->LineOfSightTo(Player, {0, 0, 0}, true))
                        continue;
                }
                if (Config.AimBot.IgnoreBot) {
                    if (Player->bIsAI)
                        continue;
                }

                        auto Root = Player->GetBonePos("Root", {});
                auto Head = Player->GetBonePos("Head", {});
                FVector2D RootSc, HeadSc;
                if (W2S(Root, &RootSc) && W2S(Head, &HeadSc))
                {
                    float height = abs(HeadSc.Y - RootSc.Y);
                    float width = height * 0.65f;

                    FVector middlePoint = {HeadSc.X + (width / 2), HeadSc.Y + (height / 2), 0};
                    if ((middlePoint.X >= 0 && middlePoint.X <= glWidth) && (middlePoint.Y >= 0 && middlePoint.Y <= glHeight))
                    {
                        FVector2D v2Middle = FVector2D((float)(glWidth / 2), (float)(glHeight / 2));
                        FVector2D v2Loc = FVector2D(middlePoint.X, middlePoint.Y);
                        

                        
                        
                                if(isInsideFOVs((int)middlePoint.X, (int)middlePoint.Y)) {
									
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



auto GetTargetByCrossDist() {
    ASTExtraPlayerCharacter *result = 0;
    float max = std::numeric_limits<float>::infinity();

    auto Actors = getActors();

    auto localPlayer = g_LocalPlayer;
    auto localController = g_LocalController;
                        FVector ViewPosY{0, 0, 0};
                        if (localPlayer) {                   
                        ViewPosY = localPlayer->GetBonePos("Head", {});
                        ViewPosY.Z += 10.f;
                         }  
    if (localPlayer) {
        for (int i = 0; i < Actors.size(); i++) {
            auto Actor = Actors[i];
            if (isObjectInvalid(Actor))
                continue;

            if (Actor->IsA(ASTExtraPlayerCharacter::StaticClass())) {
                auto Player = (ASTExtraPlayerCharacter *) Actor;

                if (Player->PlayerKey == localPlayer->PlayerKey)
                    continue;

                if (Player->TeamID == localPlayer->TeamID)
                    continue;

                if (Player->bDead)
                    continue;
//silentAim
                if (Config.SilentAim.IgnoreKnocked) {
                    if (Player->Health == 0.0f)
                        continue;
                }

                if (Config.SilentAim.VisCheck) {
                    if (!localController->LineOfSightTo(Player, ViewPosY, true))
                        continue;
                }
                if (Config.SilentAim.IgnoreBot) {
                    if (Player->bIsAI)
                        continue;
                }

                auto Root = Player->GetBonePos("Root", {});
                auto Head = Player->GetBonePos("Head", {});

                FVector2D RootSc, HeadSc;
                if (W2S(Root, &RootSc) && W2S(Head, &HeadSc)) {
                    float height = abs(HeadSc.Y - RootSc.Y);
                    float width = height * 0.65f;

                    FVector middlePoint = {HeadSc.X + (width / 2), HeadSc.Y + (height / 2), 0};
                    if ((middlePoint.X >= 0 && middlePoint.X <= glWidth) && (middlePoint.Y >= 0 && middlePoint.Y <= glHeight)) {
                        FVector2D v2Middle = FVector2D((float) (glWidth / 2), (float) (glHeight / 2));
                        FVector2D v2Loc = FVector2D(middlePoint.X, middlePoint.Y);
if(isInsideFOVs((int)middlePoint.X, (int)middlePoint.Y)) {
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

// ======================================================================== //
const char *GetVehicleName(ASTExtraVehicleBase *Vehicle) {
    switch (Vehicle->VehicleShapeType) {
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Motorbike:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Motorbike_SideCart:
            return "Motorbike";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Dacia:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_HeavyDacia:
            return "Dacia";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_MiniBus:
            return "Mini Bus";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_PickUp:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_PickUp01:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_HeavyPickup:
            return "Pick Up";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Buggy:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_HeavyBuggy:
            return "Buggy";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_UAZ:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_UAZ01:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_UAZ02:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_UAZ03:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_HeavyUAZ:
            return "UAZ";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_PG117:
            return "PG117";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Aquarail:
            return "Aquarail";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Mirado:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Mirado01:
            return "Mirado";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Rony:
            return "Rony";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Scooter:
            return "Scooter";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_SnowMobile:
            return "Snow Mobile";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_TukTukTuk:
            return "Tuk Tuk";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_SnowBike:
            return "Snow Bike";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Surfboard:
            return "Surf Board";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Snowboard:
            return "Snow Board";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Amphibious:
            return "Amphibious";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_LadaNiva:
            return "Lada Niva";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_UAV:
            return "UAV";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_MegaDrop:
            return "Mega Drop";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Lamborghini:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Lamborghini01:
            return "Lamborghini";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_GoldMirado:
            return "Gold Mirado";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_BigFoot:
            return "Big Foot";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_HeavyUH60:
            return "UH60";
            break;
        default:
            return "Vehicle";
            break;
    }
    return "Vehicle";
}

void (*orig_shoot_event)(USTExtraShootWeaponComponent *thiz, FVector start, FRotator rot, void *unk1, int unk2) = 0;

void shoot_event(USTExtraShootWeaponComponent *thiz, FVector start, FRotator rot, ASTExtraShootWeapon *weapon, int unk1) {
    if (Config.SilentAim.Enable) {
        ASTExtraPlayerCharacter *Target = GetTargetByCrossDist();
        if (Target) {
            bool triggerOk = false;
            if (Config.SilentAim.Trigger != EAimTrigger::None) {
                if (Config.SilentAim.Trigger == EAimTrigger::Shooting) {
                    triggerOk = g_LocalPlayer->bIsWeaponFiring;
                } else if (Config.SilentAim.Trigger == EAimTrigger::Scoping) {
                    triggerOk = g_LocalPlayer->bIsGunADS;
                } else if (Config.SilentAim.Trigger == EAimTrigger::Both) {
                    triggerOk = g_LocalPlayer->bIsWeaponFiring && g_LocalPlayer->bIsGunADS;
                } else if (Config.SilentAim.Trigger == EAimTrigger::Any) {
                    triggerOk = g_LocalPlayer->bIsWeaponFiring || g_LocalPlayer->bIsGunADS;
                }
            } else triggerOk = true;
            if (triggerOk) {
                FVector targetAimPos = Target->GetBonePos("Head", {});
                if (Config.SilentAim.Target == EAimTarget::Chest) {
                    targetAimPos.Z -= 25.0f;
                }
                UShootWeaponEntity *ShootWeaponEntityComponent = thiz->ShootWeaponEntityComponent;
                if (ShootWeaponEntityComponent) {
                    ASTExtraVehicleBase *CurrentVehicle = Target->CurrentVehicle;
                    if (CurrentVehicle) {
                        FVector LinearVelocity = CurrentVehicle->ReplicatedMovement.LinearVelocity;

                        float dist = g_LocalPlayer->GetDistanceTo(Target);
                        auto timeToTravel = dist / ShootWeaponEntityComponent->BulletRange;

                        targetAimPos = UKismetMathLibrary::Add_VectorVector(targetAimPos, UKismetMathLibrary::Multiply_VectorFloat(LinearVelocity, timeToTravel));
                    } else {
                        FVector Velocity = Target->GetVelocity();

                        float dist = g_LocalPlayer->GetDistanceTo(Target);
                        auto timeToTravel = dist / ShootWeaponEntityComponent->BulletRange;

                        targetAimPos = UKismetMathLibrary::Add_VectorVector(targetAimPos, UKismetMathLibrary::Multiply_VectorFloat(Velocity, timeToTravel));
                    }
                    FVector fDir = UKismetMathLibrary::Subtract_VectorVector(targetAimPos, g_LocalController->PlayerCameraManager->CameraCache.POV.Location);
                    rot = UKismetMathLibrary::Conv_VectorToRotator(fDir);
                }
            }
        }
    }
    return orig_shoot_event(thiz, start, rot, weapon, unk1);
}
// ================================================================================================================================ //


class FPSCounter {
protected:
    unsigned int m_fps;
    unsigned int m_fpscount;
    long m_fpsinterval;

public:
    FPSCounter() : m_fps(0), m_fpscount(0), m_fpsinterval(0) {
    }

    void update() {
        m_fpscount++;

        if (m_fpsinterval < time(0)) {
            m_fps = m_fpscount;

            m_fpscount = 0;
            m_fpsinterval = time(0) + 1;
        }
    }

    unsigned int get() const {
        return m_fps;
    }
};

FPSCounter fps;


void DrawBoxEnemy(ImDrawList *draw, ImVec2 X, ImVec2 Y, float thicc, float rounding, int color) {
    draw->AddLine({X.x, X.y}, {Y.x, Y.y}, color, thicc);
}

void VectorAnglesRadar(Vector3 & forward, FVector & angles) {
 if (forward.X == 0.f && forward.Y == 0.f) {
  angles.X = forward.Z > 0.f ? -90.f : 90.f;
  angles.Y = 0.f;
 } else {
  angles.X = RAD2DEG(atan2(-forward.Z, forward.Magnitude(forward)));
  angles.Y = RAD2DEG(atan2(forward.Y, forward.X));
 }
 angles.Z = 0.f;
}

void RotateTriangle(std::array<Vector3, 3> & points, float rotation) {
 const auto points_center = (points.at(0) + points.at(1) + points.at(2)) / 3;
 for (auto & point : points) {
  point = point - points_center;
  const auto temp_x = point.X;
  const auto temp_y = point.Y;
  const auto theta = DEG2RAD(rotation);
  const auto c = cosf(theta);
  const auto s = sinf(theta);
  point.X = temp_x * c - temp_y * s;
  point.Y = temp_x * s + temp_y * c;
  point = point + points_center;
 }
}

FVector2D pushToScreenBorder(FVector2D Pos, FVector2D screen, int borders, int offset) {
	int x = (int)Pos.X;
	int y = (int)Pos.Y;
	if ((borders & 1) == 1) {
		y = 0 - offset;
	}
	if ((borders & 2) == 2) {
		x = (int)screen.X + offset;
	}
	if ((borders & 4) == 4) {
		y = (int)screen.Y + offset;
	}
	if ((borders & 8) == 8) {
		x = 0 - offset;
	}
	return FVector2D(x, y);
}

int isOutsideSafezone(FVector2D pos, FVector2D screen) {
	FVector2D mSafezoneTopLeft(screen.X * 0.04f, screen.Y * 0.04f);
	FVector2D mSafezoneBottomRight(screen.X * 0.96f, screen.Y * 0.96f);
	int result = 0;
	if (pos.Y < mSafezoneTopLeft.Y) {
		result |= 1;
	}
	if (pos.X > mSafezoneBottomRight.X) {
		result |= 2;
	}
	if (pos.Y > mSafezoneBottomRight.Y) {
		result |= 4;
	}
	if (pos.X < mSafezoneTopLeft.X) {
		result |= 8;
	}
	return result;
}

void Box4Line(ImDrawList *draw, float thicc, int x, int y, int w, int h, int color) {
    int iw = w / 4;
    int ih = h / 4;
    // top
    draw->AddRect(ImVec2(x, y),ImVec2(x + iw, y), color, thicc);
    draw->AddRect(ImVec2(x + w - iw, y),ImVec2(x + w, y), color, thicc);
    draw->AddRect(ImVec2(x, y),ImVec2(x, y + ih), color, thicc);
    draw->AddRect(ImVec2(x + w - 1, y),ImVec2(x + w - 1, y + ih), color, thicc);;
    // bottom
    draw->AddRect(ImVec2(x, y + h),ImVec2(x + iw, y + h), color, thicc);
    draw->AddRect(ImVec2(x + w - iw, y + h),ImVec2(x + w, y + h), color, thicc);
    draw->AddRect(ImVec2(x, y + h - ih), ImVec2(x, y + h), color, thicc);
    draw->AddRect(ImVec2(x + w - 1, y + h - ih), ImVec2(x + w - 1, y + h), color, thicc);
}

void DrawBoxEnemy(ImDrawList *draw, ImVec2 X, ImVec2 Y, float thicc, int color) {
    draw->AddLine({X.x, X.y}, {Y.x, Y.y}, color, thicc);
}

void DrawFilledRectangle(int x, int y, int w, int h, ImU32 col, float rounding) {
    ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), col, rounding);
}

void DrawRectangle(int x, int y, int w, int h, ImU32 col, float rounding) {
    ImGui::GetBackgroundDrawList()->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), col, rounding);
}
bool W2S2(FVector worldPos, FVector2D *screenPos) {
    return g_LocalController->ProjectWorldLocationToScreen(worldPos, true, screenPos);
}

void Line(ImDrawList *draw,FVector2D origin, FVector2D dest, ImColor color)
{
   draw->AddLine({origin.X, origin.Y},{dest.X, dest.Y},color, 2.0f);
}


void Box3D1(ImDrawList *draw, FVector origin, FVector extends, ImColor col) {
    origin.X -= extends.X / 2.f;
    origin.Y -= extends.Y / 2.f;
    origin.Z -= extends.Z / 2.f;
    
    
 FVector one = origin;
 FVector two = origin; two.X += extends.X;
 FVector tree = origin; tree.X += extends.X; tree.Y += extends.Y;
 FVector four = origin; four.Y += extends.Y;

 FVector five = one; five.Z += extends.Z;
 FVector six = two; six.Z += extends.Z;
 FVector seven = tree; seven.Z += extends.Z;
 FVector eight = four; eight.Z += extends.Z;

    FVector2D s1, s2, s3, s4, s5, s6, s7, s8;
    if (W2S2(one, &s1) && W2S2(two, &s2) && W2S2(tree, &s3) && W2S2(four, &s4) &&
    W2S2(five, &s5) && W2S2(six, &s6) && W2S2(seven, &s7) && W2S2(eight, &s8))
    {
        
    Line(draw,s1, s2, col);
    Line(draw,s2, s3, col);
    Line(draw,s3, s4, col);
    Line(draw,s4, s1, col);
 
    Line(draw,s5, s6, col);
    Line(draw,s6, s7, col);
    Line(draw,s7, s8, col);
    Line(draw,s8, s5, col);
 
    Line(draw,s1, s5, col);
    Line(draw,s2, s6, col);
    Line(draw,s3, s7, col);
    Line(draw,s4, s8, col);

}
}

FVector WorldToRadar(float Yaw, FVector Origin, FVector LocalOrigin, float PosX, float PosY, Vector3 Size, bool &outbuff) {
 bool flag = false;
 double num = (double)Yaw;
 double num2 = num * 0.017453292519943295;
 float num3 = (float)std::cos(num2);
 float num4 = (float)std::sin(num2);
 float num5 = Origin.X - LocalOrigin.X;
 float num6 = Origin.Y - LocalOrigin.Y;
 struct FVector Xector;
 Xector.X = (num6 * num3 - num5 * num4) / 150.f;
 Xector.Y = (num5 * num3 + num6 * num4) / 150.f;
 struct FVector Xector2;
 Xector2.X = Xector.X + PosX + Size.X / 2.f;
 Xector2.Y = -Xector.Y + PosY + Size.Y / 2.f;
 bool flag2 = Xector2.X > PosX + Size.X;
 if (flag2) {
  Xector2.X = PosX + Size.X;
 }else{
  bool flag3 = Xector2.X < PosX;
  if (flag3) {
   Xector2.X = PosX;
  }
 }
 bool flag4 = Xector2.Y > PosY + Size.Y;
 if (flag4) {
  Xector2.Y = PosY + Size.Y;
 }else{
  bool flag5 = Xector2.Y < PosY;
  if (flag5){
   Xector2.Y = PosY;
  }
 }
 bool flag6 = Xector2.Y == PosY || Xector2.X == PosX;
 if (flag6){
  flag = true;
 }
 outbuff = flag;
 return Xector2;
}




void DrawESP(ImDrawList *draw) {
if (g_LocalController == 0){
   } else {
    }

	 if (LobbyBy) {
MemoryPatch::createWithHex("libanogs.so",0x4CE40, "00 20 70 47").Modify();
            	}   
		
    if (Config.OTHER.HIDEESP) {
        HIDEESP = false;
    } else {
        HIDEESP = true;
    }
    if (HIDEESP) {

            auto Actors = getActors();

    int totalEnemies = 0, totalBots = 0;

    ASTExtraPlayerCharacter *localPlayer = 0;
    ASTExtraPlayerController *localController = 0;
    
if (Config.AimBot.Enable) {
            draw->AddText({((float) density / 10.0f), 70}, IM_COL32(0, 255, 0, 255),
                          "AimSimukation 2.0 ~ Enable");
            }else{
            draw->AddText({((float) density / 10.0f), 70}, IM_COL32(255, 0, 0, 255),
                          "AimSimukation 2.0 ~ Disable");
        }


/*draw->AddText(NULL, ((float) density / 15.0f),{(float) glWidth / 150 + glWidth / 20,640},IM_COL32(0,255,255, 255),
                          "For FEEDBACK Hack Contact to @Owner_Admnn");*/
	
	
		
/* draw->AddText(NULL, ((float) density / 15.0f),{(float) glWidth / 2 + glWidth / 30,15},IM_COL32(0, 255, 0, 250),
                            " EXPIRY KEY :-  ");
    
draw->AddText(NULL, ((float) density / 15.0f),{(float) glWidth / 2 + glWidth / 6,15},IM_COL32(255, 0, 0, 250),EXP.c_str());*/
 

      

//draw->AddText(NULL, ((float) density / 20.0f),{(float) glWidth / 180 + glWidth / 40,200}, IM_COL32(255,255,0, 255),floating.c_str());

        if (Config.Bypass) {
            draw->AddText({((float) density / 10.0f), 40}, IM_COL32(0, 255, 0, 255),
                          "BYPASS ON");
						  
						  
						  
PATCH_LIB("libanogs.so", "0x2A0C1D  ", "00 00 A0 E3 1E FF 2F E1"); // offline ban
PATCH_LIB("libanogs.so", "0x2C3A7F  ", "00 00 A0 E3 1E FF 2F E1"); // offline ban
PATCH_LIB("libanogs.so", "0x2C674B  ", "00 00 A0 E3 1E FF 2F E1"); // offline ban
PATCH_LIB("libanogs.so", "0x2CAD59  ", "00 00 A0 E3 1E FF 2F E1"); // offline ban
PATCH_LIB("libanogs.so", "0x2CC06D  ", "00 00 A0 E3 1E FF 2F E1"); // online year
MemoryPatch::createWithHex("libUE4.so",0x41DF94,"h FF FF FF FF",131072).Modify();
MemoryPatch::createWithHex("libUE4.so",0x41DE70,"h FF FF FF FF",131072).Modify();
MemoryPatch::createWithHex("libUE4.so",0x41D650,"h FF FF FF FF",131072).Modify();
MemoryPatch::createWithHex("libUE4.so",0x41D640,"h FF FF FF FF",131072).Modify();
MemoryPatch::createWithHex("libUE4.so",0x41D61C,"h FF FF FF FF",131072).Modify();
MemoryPatch::createWithHex("libUE4.so",0x41D608,"h FF FF FF FF",131072).Modify();
MemoryPatch::createWithHex("libUE4.so",0x41D5C0,"h FF FF FF FF",131072).Modify();
MemoryPatch::createWithHex("libUE4.so",0x41D2D8,"h FF FF FF FF",131072).Modify();
MemoryPatch::createWithHex("libUE4.so",0x41D1A0,"h FF FF FF FF",131072).Modify();
MemoryPatch::createWithHex("libUE4.so",0x41D08C,"h FF FF FF FF",131072).Modify();
MemoryPatch::createWithHex("libUE4.so",0x41CFBC,"h FF FF FF FF",131072).Modify();
MemoryPatch::createWithHex("libUE4.so",0x41CFAC,"h FF FF FF FF",131072).Modify();
MemoryPatch::createWithHex("libanogs.so", 0x14dc4, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x14dc8, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fdc0, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fdc4, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fdc8, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fdcc, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fdd0, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fdd4, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fdd8, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fddc, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fde0, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fde4, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fde8, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fdec, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fdf0, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fdf4, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fdf8, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fdfc, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fe00, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fe04, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fe08, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fe0c, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fe10, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fe14, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fe18, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fe28, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fe2c, "00 00 A0 E3 1E FF 2F E1").Modify();
MemoryPatch::createWithHex("libanogs.so", 0x1fe30, "00 00 A0 E3 1E FF 2F E1").Modify();

MemoryPatch::createWithHex("libanogs.so", 0x1fe34, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fe38, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fe3c, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fe40, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fe44, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fe48, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fe4c, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fe50, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fe54, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fe58, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b04c, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b050, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b054, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b058, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b05c, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b060, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b064, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b068, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b06c, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b070, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b074, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b078, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b07c, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b080, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b084, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b088, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b08c, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b090, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b094, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b098, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b09c, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b0a0, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b0a4, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b0a8, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b0ac, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b0c0, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b0c4, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b0c8, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b0cc, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b0d0, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b0d4, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b0d8, "00 00 A0 E3 1E FF 2F E1").Modify();
MemoryPatch::createWithHex("libanogs.so", 0x2b0dc, "00 00 A0 E3 1E FF 2F E1").Modify();

MemoryPatch::createWithHex("libanogs.so", 0x2b0e0, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b0e4, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b0e8, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b0ec, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b0f0, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x4e7c8, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x4e7cc, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x4e7d0, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x4e7d4, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x4e7d8, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x4e7dc, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x4e7e0, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x4e7e4, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x4e7e8, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x4e7ec, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x4e7f0, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x4e7f4, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x4e7f8, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x4e7fc, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f30, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f34, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f38, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f3c, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f40, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f44, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f48, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f4c, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f50, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f54, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f58, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f5c, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f60, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f64, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f68, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f6c, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f70, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f74, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f78, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f7c, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f80, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cbd0, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cbd4, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cbd8, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cbdc, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cbe0, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cbe4, "2d 1e 00 01").Modify();
MemoryPatch::createWithHex("libanogs.so", 0x5cbe8, "2d 1e 00 01").Modify();

MemoryPatch::createWithHex("libanogs.so", 0x5cbec, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cbf0, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cbf4, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cbf8, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cbfc, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cc00, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cc04, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cc08, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cc0c, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cc10, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cc14, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cc18, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cc1c, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cc20, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41dbc, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41dc4, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41dc8, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41dcc, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41dd4, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41dd8, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41ddc, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41de0, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41de4, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41de8, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41df0, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41df4, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41dfc, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41e00, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41e04, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41e0c, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41e10, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41e14, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41e1c, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41e20, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41e28, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f30, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f34, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f38, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f3c, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f40, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f44, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f48, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f4c, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f50, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f54, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f58, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f5c, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f60, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f64, "2d 1e 00 01").Modify();
MemoryPatch::createWithHex("libanogs.so", 0x61f68, "2d 1e 00 01").Modify();

MemoryPatch::createWithHex("libanogs.so", 0x61f6c, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f70, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f74, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f78, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f7c, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f80, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cbd0, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cbd4, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cbd8, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cbdc, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cbe0, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cbe4, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cbe8, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cbec, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cbf0, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cbf4, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cbf8, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cbfc, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cc00, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cc04, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cc08, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cc0c, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cc10, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cc14, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cc18, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cc1c, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cc20, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41dbc, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41dc4, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41dc8, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41dcc, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41dd4, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41dd8, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41ddc, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41de0, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41de4, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41de8, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41df0, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41df4, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41dfc, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41e00, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41e04, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41e0c, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41e10, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41e14, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41e1c, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41e20, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41e28, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x95ef0, "00 20 70 47").Modify();
MemoryPatch::createWithHex("libanogs.so", 0xd218c, "00 20 70 47").Modify();

MemoryPatch::createWithHex("libanogs.so", 0xd2198, "00 20 70 47").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0xd219c, "00 20 70 47").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0xd21a0, "00 20 70 47").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0xd21a4, "00 20 70 47").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0xd21a8, "00 20 70 47").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0xd21ac, "00 20 70 47").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0xd21b0, "00 20 70 47").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0xd21b4, "00 20 70 47").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0xd21b8, "00 20 70 47").Modify(); 


 MemoryPatch::createWithHex("libanogs.so", 0x44AD1C, "00 00 00 00 06 C0 38 01").Modify();
			MemoryPatch::createWithHex("libanogs.so", 0x43F11C, "00 00 00 00 06 C0 38 01").Modify();
			MemoryPatch::createWithHex("libanogs.so", 0x43EFE0, "00 00 00 00 06 C0 38 01").Modify();
			MemoryPatch::createWithHex("libanogs.so", 0x608D6C, "00 00 00 00 06 C0 38 01").Modify();
			MemoryPatch::createWithHex("libanogs.so", 0x42C870, "00 00 00 00 06 C0 38 01").Modify();
			MemoryPatch::createWithHex("libanogs.so", 0xA8B48, "00 00 00 00 06 C0 38 01").Modify();
			MemoryPatch::createWithHex("libanogs.so", 0xA8B9C, "00 00 00 00 06 C0 38 01").Modify();
			MemoryPatch::createWithHex("libanogs.so", 0xB7638 , "00 02 1F D6").Modify();//fix 3rd party
	 

MemoryPatch::createWithHex("libUE4.so", 0x416B718, OBFUSCATE("AA 45 AB EB")); 
MemoryPatch::createWithHex("libUE4.so", 0x416B748, OBFUSCATE("22 45 AB EB"));
MemoryPatch::createWithHex("libUE4.so", 0x5759AF8, OBFUSCATE("0B FE 02 EB"));
MemoryPatch::createWithHex("libUE4.so", 0x4F66148, OBFUSCATE("83 2F E3 EB"));
MemoryPatch::createWithHex("libUE4.so", 0x569A6C4, OBFUSCATE("CA FF FF 0A"));
MemoryPatch::createWithHex("libUE4.so", 0x57599AC, OBFUSCATE("5C FC 02 EB"));
MemoryPatch::createWithHex("libUE4.so", 0x69C216C, OBFUSCATE("10 9E 4C EB"));
MemoryPatch::createWithHex("libUE4.so", 0x57585EC, OBFUSCATE("54 F9 01 EB"));
MemoryPatch::createWithHex("libUE4.so", 0x56DA37C, OBFUSCATE("0B 00 00 0A"));
MemoryPatch::createWithHex("libUE4.so", 0x577A38C, OBFUSCATE("CB 00 00 1A"));
MemoryPatch::createWithHex("libUE4.so", 0x416B81C, OBFUSCATE("FA 45 A7 EB"));
MemoryPatch::createWithHex("libUE4.so", 0x4756ADC, OBFUSCATE("7A 72 BA EB"));
MemoryPatch::createWithHex("libUE4.so", 0x46EAA9C, OBFUSCATE("62 C2 B8 EB"));
MemoryPatch::createWithHex("libUE4.so", 0x416B7B8, OBFUSCATE("84 C5 A2 EB"));
MemoryPatch::createWithHex("libUE4.so", 0x47F5CFC, OBFUSCATE("BD EE BC EB"));
MemoryPatch::createWithHex("libUE4.so", 0x47FB58C, OBFUSCATE("DC 04 BD EB"));
MemoryPatch::createWithHex("libUE4.so", 0x416B7E4, OBFUSCATE("58 C5 A2 EB"));
MemoryPatch::createWithHex("libUE4.so", 0x416BA44, OBFUSCATE("EE C4 A2 EB"));
MemoryPatch::createWithHex("libUE4.so", 0x416BA3C, OBFUSCATE("AA C3 A2 EB"));
MemoryPatch::createWithHex("libUE4.so", 0x416B7A8, OBFUSCATE("FB C2 A2 EB"));
MemoryPatch::createWithHex("libUE4.so", 0x416B738, OBFUSCATE("54 C2 A2 EB"));
MemoryPatch::createWithHex("libUE4.so", 0x416BA3C, OBFUSCATE("92 C2 A2 EB"));
MemoryPatch::createWithHex("libUE4.so", 0x6DF8AF4, OBFUSCATE("8E F5 54 EB"));
MemoryPatch::createWithHex("libUE4.so", 0x469152C, OBFUSCATE("C8 57 B7 EB"));
MemoryPatch::createWithHex("libUE4.so", 0x46EA964, OBFUSCATE("52 BC B8 EB"));
MemoryPatch::createWithHex("libUE4.so", 0x6972B34, OBFUSCATE("2F DC 42 EB"));
MemoryPatch::createWithHex("libUE4.so", 0x6BEC3B4, OBFUSCATE("10 C1 4C EB"));
MemoryPatch::createWithHex("libUE4.so", 0x732BFEC, OBFUSCATE("7C BF 69 DB"));
MemoryPatch::createWithHex("libUE4.so", 0x76F661C, OBFUSCATE("D8 E8 78 3B"));
MemoryPatch::createWithHex("libUE4.so", 0x76F6C1C, OBFUSCATE("D8 E8 78 3B"));
MemoryPatch::createWithHex("libUE4.so", 0x76F6C34, OBFUSCATE("D8 E8 78 3B"));
MemoryPatch::createWithHex("libUE4.so", 0x76F6C4C, OBFUSCATE("D8 E8 78 3B"));
MemoryPatch::createWithHex("libUE4.so", 0x76F6C64, OBFUSCATE("D8 E8 78 3B"));
MemoryPatch::createWithHex("libUE4.so", 0x76F6DA8, OBFUSCATE("D8 E8 78 3B"));
MemoryPatch::createWithHex("libUE4.so", 0x731E6EC, OBFUSCATE("14 87 69 DB"));
MemoryPatch::createWithHex("libUE4.so", 0x76F6E94, OBFUSCATE("D8 E8 78 3B"));
MemoryPatch::createWithHex("libUE4.so", 0x731E578, OBFUSCATE("7C 86 69 DB"));
MemoryPatch::createWithHex("libUE4.so", 0x731E164, OBFUSCATE("2C 85 69 DB"));
MemoryPatch::createWithHex("libUE4.so", 0x76F724C, OBFUSCATE("D8 E8 78 3B"));
MemoryPatch::createWithHex("libUE4.so", 0x76F7264, OBFUSCATE("D8 E8 78 3B"));
MemoryPatch::createWithHex("libUE4.so", 0x76F7294, OBFUSCATE("D8 E8 78 3B"));
MemoryPatch::createWithHex("libUE4.so", 0x76EF324, OBFUSCATE("D8 C8 78 3B"));
MemoryPatch::createWithHex("libUE4.so", 0x6FF319C, OBFUSCATE("4E D8 5C 3A"));
MemoryPatch::createWithHex("libUE4.so", 0x731DB6C, OBFUSCATE("B0 82 69 DB"));
MemoryPatch::createWithHex("libUE4.so", 0x76F74F4, OBFUSCATE("D8 E8 78 3B"));
MemoryPatch::createWithHex("libUE4.so", 0x76F7618, OBFUSCATE("D8 E8 78 3B"));
MemoryPatch::createWithHex("libUE4.so", 0x76F7724, OBFUSCATE("D8 E8 78 3B"));
MemoryPatch::createWithHex("libUE4.so", 0x76F776C, OBFUSCATE("D8 E8 78 3B"));
// Ban 10 yeay Не Юзать ! Бан на 10 лет !!! Глобал мамент бан 

MemoryPatch::createWithHex("libanogs.so", 0x6B810, OBFUSCATE("DC F4 BC E5"));
MemoryPatch::createWithHex("libanogs.so", 0x6B7C0, OBFUSCATE("03 C6 8F E2"));
MemoryPatch::createWithHex("libanogs.so", 0xA3454, OBFUSCATE("00 F0 62 F9")); 
MemoryPatch::createWithHex("libanogs.so", 0x32F844, OBFUSCATE("7C F2 D0 FF")); 
MemoryPatch::createWithHex("libanogs.so", 0x32F894, OBFUSCATE("7C F2 CB FF")); 
MemoryPatch::createWithHex("libanogs.so", 0x381F28, OBFUSCATE("CF F2 0A FB")); 
MemoryPatch::createWithHex("libanogs.so", 0xB2ED4, OBFUSCATE("00 F0 D5 FA")); 
MemoryPatch::createWithHex("libanogs.so", 0x32F894, OBFUSCATE("7C F2 9F FF")); 
MemoryPatch::createWithHex("libanogs.so", 0xB2ED4, OBFUSCATE("00 F0 BB FA")); 
MemoryPatch::createWithHex("libanogs.so", 0xB2934, OBFUSCATE("FF F7 CE FF")); 
MemoryPatch::createWithHex("libanogs.so", 0xFBBCC, OBFUSCATE("49 F0 0E F9")); 
MemoryPatch::createWithHex("libanogs.so", 0xFBE2C, OBFUSCATE("49 F0 38 FA")); 
MemoryPatch::createWithHex("libanogs.so", 0x334654, OBFUSCATE("81 F2 30 FE")); 
MemoryPatch::createWithHex("libanogs.so", 0xB2AAC, OBFUSCATE("00 F0 56 F8")); 
MemoryPatch::createWithHex("libanogs.so", 0x334654, OBFUSCATE("81 F2 23 FE")); 
MemoryPatch::createWithHex("libanogs.so", 0xAFE24, OBFUSCATE("FD F7 E0 F9")); 
MemoryPatch::createWithHex("libanogs.so", 0x334654, OBFUSCATE("81 F2 F5 FD")); 
MemoryPatch::createWithHex("libanogs.so", 0x334654, OBFUSCATE("81 F2 DC FD")); 
MemoryPatch::createWithHex("libanogs.so", 0x14BD88, OBFUSCATE("1D 03 00 EB")); 
MemoryPatch::createWithHex("libanogs.so", 0x14BB94, OBFUSCATE("A2 02 00 EB")); 
MemoryPatch::createWithHex("libanogs.so", 0x14B16C, OBFUSCATE("EC FF FF EB")); 
MemoryPatch::createWithHex("libanogs.so", 0x1AC7AC, OBFUSCATE("66 85 01 EB")); 
MemoryPatch::createWithHex("libanogs.so", 0x14ABB4, OBFUSCATE("59 FE FF EB")); 
MemoryPatch::createWithHex("libanogs.so", 0x1AC834, OBFUSCATE("69 85 01 EB")); 
MemoryPatch::createWithHex("libanogs.so", 0x1AC834, OBFUSCATE("66 85 01 EB")); 
MemoryPatch::createWithHex("libanogs.so", 0x381F28, OBFUSCATE("13 DB 08 FA")); 
MemoryPatch::createWithHex("libanogs.so", 0x14B42C, OBFUSCATE("3D 00 00 EB")); 
MemoryPatch::createWithHex("libanogs.so", 0x14B4A4, OBFUSCATE("54 00 00 EB")); 
MemoryPatch::createWithHex("libanogs.so", 0x14D2C8, OBFUSCATE("9A 07 00 EB")); 
MemoryPatch::createWithHex("libanogs.so", 0x14D3F8, OBFUSCATE("E2 07 00 EB")); 
MemoryPatch::createWithHex("libanogs.so", 0x14D4E8, OBFUSCATE("08 08 00 EB"));
MemoryPatch::createWithHex("libanogs.so", 0x17C214, OBFUSCATE("2A FC FF EB")); 
MemoryPatch::createWithHex("libanogs.so", 0x17BFDC, OBFUSCATE("97 FB FF EB")); 
MemoryPatch::createWithHex("libanogs.so", 0x17C3BC, OBFUSCATE("84 FC FF EB")); 
MemoryPatch::createWithHex("libanogs.so", 0x17D278, OBFUSCATE("10 00 00 EB")); 
MemoryPatch::createWithHex("libanogs.so", 0x382E3C, OBFUSCATE("F2 16 08 EB")); 
MemoryPatch::createWithHex("libanogs.so", 0x17CB84, OBFUSCATE("2A FE FF EB")); 
MemoryPatch::createWithHex("libanogs.so", 0x17D344, OBFUSCATE("01 00 00 EB")); 
MemoryPatch::createWithHex("libanogs.so", 0x176A84, OBFUSCATE("C9 E5 FF EB")); 
MemoryPatch::createWithHex("libanogs.so", 0x17A418, OBFUSCATE("04 F4 FF EB")); 
MemoryPatch::createWithHex("libanogs.so", 0x17D764, OBFUSCATE("7A 00 00 EB")); 
MemoryPatch::createWithHex("libanogs.so", 0x17D818, OBFUSCATE("91 00 00 EB")); 
MemoryPatch::createWithHex("libanogs.so", 0x381F28, OBFUSCATE("47 12 08 FA")); 
MemoryPatch::createWithHex("libanogs.so", 0x176C7C, OBFUSCATE("8D E5 FF EB")); 
MemoryPatch::createWithHex("libanogs.so", 0x176A98, OBFUSCATE("11 E5 FF EB")); 
MemoryPatch::createWithHex("libanogs.so", 0x17DA14, OBFUSCATE("E2 00 00 EB")); 
//UE4
MemoryPatch::createWithHex("libUE4.so", 0x4AD14D8, OBFUSCATE("04 5D 36 EB"));
MemoryPatch::createWithHex("libUE4.so", 0x3189E7C, OBFUSCATE("D6 3E D1 EB"));
MemoryPatch::createWithHex("libUE4.so", 0x21E21F8, OBFUSCATE("A7 9F 92 EB"));
MemoryPatch::createWithHex("libUE4.so", 0x46EAA9C, OBFUSCATE("0C C1 83 EB"));
MemoryPatch::createWithHex("libUE4.so", 0x513E118, OBFUSCATE("3E 0E AD EB"));
MemoryPatch::createWithHex("libUE4.so", 0x47B5FDC, OBFUSCATE("D5 6F 86 EB"));
MemoryPatch::createWithHex("libUE4.so", 0x513D7AC, OBFUSCATE("36 8D AC EB"));
MemoryPatch::createWithHex("libUE4.so", 0x46EA9FC, OBFUSCATE("5A 40 83 EB"));
MemoryPatch::createWithHex("libUE4.so", 0x513D9E4, OBFUSCATE("47 8C AC EB"));
MemoryPatch::createWithHex("libUE4.so", 0x469163C, OBFUSCATE("51 DA 81 EB"));
MemoryPatch::createWithHex("libUE4.so", 0x4696778, OBFUSCATE("C6 ED 81 EB"));
MemoryPatch::createWithHex("libUE4.so", 0x4756ADC, OBFUSCATE("E1 ED 84 EB"));
MemoryPatch::createWithHex("libUE4.so", 0x46EAC20, OBFUSCATE("96 3D 83 EB"));
MemoryPatch::createWithHex("libUE4.so", 0x513CC98, OBFUSCATE("7A 85 AC EB"));
MemoryPatch::createWithHex("libUE4.so", 0x4AF271C, OBFUSCATE("1B 5B 93 EA"));
MemoryPatch::createWithHex("libUE4.so", 0x513CC14, OBFUSCATE("FC 8A AB EB"));
MemoryPatch::createWithHex("libUE4.so", 0x513CAF8, OBFUSCATE("6B 8A AB EB"));
MemoryPatch::createWithHex("libUE4.so", 0x665ACE8, OBFUSCATE("7F 00 00 EB"));
MemoryPatch::createWithHex("libUE4.so", 0x665AE44, OBFUSCATE("BE 00 00 EB"));
MemoryPatch::createWithHex("libUE4.so", 0x513EE1C, OBFUSCATE("30 90 AB EB"));
MemoryPatch::createWithHex("libUE4.so", 0x665AF64, OBFUSCATE("02 00 00 EB"));
MemoryPatch::createWithHex("libUE4.so", 0x513E16C, OBFUSCATE("B1 8B AB EB"));
MemoryPatch::createWithHex("libUE4.so", 0x4F26154, OBFUSCATE("C8 2A A3 EB"));
MemoryPatch::createWithHex("libUE4.so", 0x46968B4, OBFUSCATE("6F EB 80 EB"));
MemoryPatch::createWithHex("libUE4.so", 0x513CCC8, OBFUSCATE("20 0B A5 EB"));
MemoryPatch::createWithHex("libUE4.so", 0x615E644, OBFUSCATE("ED 90 E5 EB"));
MemoryPatch::createWithHex("libUE4.so", 0x6C767A8, OBFUSCATE("EC F0 11 EB"));
MemoryPatch::createWithHex("libUE4.so", 0x6C2BD9C, OBFUSCATE("67 C6 10 EB"));
MemoryPatch::createWithHex("libUE4.so", 0x6DF2E58, OBFUSCATE("94 E2 17 EB"));
MemoryPatch::createWithHex("libUE4.so", 0x4B85BD4, OBFUSCATE("D8 D8 88 3B"));
MemoryPatch::createWithHex("libUE4.so", 0x4CC5B98, OBFUSCATE("D8 D8 8D 3B"));
MemoryPatch::createWithHex("libUE4.so", 0x4B85B58, OBFUSCATE("D8 D8 88 3B"));
MemoryPatch::createWithHex("libUE4.so", 0x4B85B44, OBFUSCATE("D8 D8 88 3B"));
MemoryPatch::createWithHex("libUE4.so", 0x4CC5B1C, OBFUSCATE("D8 D8 8D 3B"));
MemoryPatch::createWithHex("libUE4.so", 0x4B85AE4, OBFUSCATE("D8 D8 88 3B"));
MemoryPatch::createWithHex("libUE4.so", 0x8781A58, OBFUSCATE("C7 C8 78 3B"));
MemoryPatch::createWithHex("libUE4.so", 0x8785A88, OBFUSCATE("D8 D8 78 3B"));
MemoryPatch::createWithHex("libUE4.so", 0x73A51A8, OBFUSCATE("E5 68 00 EB"));
MemoryPatch::createWithHex("libUE4.so", 0x735E678, OBFUSCATE("9E 11 CE EB"));
MemoryPatch::createWithHex("libUE4.so", 0x733A474, OBFUSCATE("1A 81 CD EB"));
MemoryPatch::createWithHex("libUE4.so", 0x6112F8C, OBFUSCATE("CD E3 84 EB"));
MemoryPatch::createWithHex("libUE4.so", 0x7FD51C4, OBFUSCATE("57 EC FF EB"));
MemoryPatch::createWithHex("libUE4.so", 0x6112F88, OBFUSCATE("BA E3 84 EB"));
MemoryPatch::createWithHex("libUE4.so", 0x7FDA1D4, OBFUSCATE("48 00 00 EB"));
MemoryPatch::createWithHex("libUE4.so", 0x61116D4, OBFUSCATE("85 DD 84 EB"));
MemoryPatch::createWithHex("libUE4.so", 0x6111718, OBFUSCATE("19 DD 84 EB"));
MemoryPatch::createWithHex("libUE4.so", 0x7FDA51C, OBFUSCATE("14 00 00 0A"));
MemoryPatch::createWithHex("libUE4.so", 0x7339A8C, OBFUSCATE("68 7D CD EB"));
MemoryPatch::createWithHex("libUE4.so", 0x7FDA588, OBFUSCATE("16 00 00 EB"));
MemoryPatch::createWithHex("libUE4.so", 0x7339EBC, OBFUSCATE("46 7E CD EB"));
MemoryPatch::createWithHex("libUE4.so", 0x7339B08, OBFUSCATE("55 7D CD EB"));
MemoryPatch::createWithHex("libUE4.so", 0x733B334, OBFUSCATE("58 83 CD EB"));
MemoryPatch::createWithHex("libUE4.so", 0x7339EBC, OBFUSCATE("37 7E CD EB"));
MemoryPatch::createWithHex("libUE4.so", 0x733A6CC, OBFUSCATE("36 80 CD EB"));
MemoryPatch::createWithHex("libUE4.so", 0x7339EBC, OBFUSCATE("2B 7E CD EB"));
MemoryPatch::createWithHex("libUE4.so", 0x7339A8C, OBFUSCATE("1A 7D CD EB"));
MemoryPatch::createWithHex("libUE4.so", 0x7339B4C, OBFUSCATE("3F 7D CD EB"));
MemoryPatch::createWithHex("libUE4.so", 0x7FDA794, OBFUSCATE("26 00 00 EB"));
MemoryPatch::createWithHex("libUE4.so", 0x7FA2C5C, OBFUSCATE("21 21 FF EB"));
MemoryPatch::createWithHex("libUE4.so", 0x7FDAAC0, OBFUSCATE("7B 00 00 EB"));
MemoryPatch::createWithHex("libUE4.so", 0x611419C, OBFUSCATE("26 E6 84 EB"));
MemoryPatch::createWithHex("libUE4.so", 0x7FA2C5C, OBFUSCATE("45 20 FF EB"));
MemoryPatch::createWithHex("libUE4.so", 0x611173C, OBFUSCATE("35 D9 84 EB"));
MemoryPatch::createWithHex("libUE4.so", 0x6111CB4, OBFUSCATE("CC D9 84 EB"));
MemoryPatch::createWithHex("libUE4.so", 0x6112B1C, OBFUSCATE("47 DD 84 EB"));
MemoryPatch::createWithHex("libUE4.so", 0x61141CC, OBFUSCATE("E5 E2 84 EB"));
MemoryPatch::createWithHex("libUE4.so", 0x611419C, OBFUSCATE("26 E2 84 EB"));
MemoryPatch::createWithHex("libUE4.so", 0x6112DDC, OBFUSCATE("F6 DC 84 EB"));
MemoryPatch::createWithHex("libUE4.so", 0x6111A78, OBFUSCATE("F9 DD 81 EB"));
MemoryPatch::createWithHex("libUE4.so", 0x611268C, OBFUSCATE("2A E0 81 EB"));
MemoryPatch::createWithHex("libUE4.so", 0x6F2DF78, OBFUSCATE("DD 4D BA EB"));
MemoryPatch::createWithHex("libUE4.so", 0x6111EA8, OBFUSCATE("A7 DD 81 EB"));
MemoryPatch::createWithHex("libUE4.so", 0x6111A98, OBFUSCATE("9F DC 81 EB"));
MemoryPatch::createWithHex("libUE4.so", 0x611268C, OBFUSCATE("0F DF 81 EB"));
MemoryPatch::createWithHex("libUE4.so", 0x6B32584, OBFUSCATE("69 5E AA EB"));
MemoryPatch::createWithHex("libUE4.so", 0x61142B8, OBFUSCATE("A2 E5 81 EB"));
MemoryPatch::createWithHex("libUE4.so", 0x61116BC, OBFUSCATE("8C DA 81 EB"));
MemoryPatch::createWithHex("libUE4.so", 0x61142BC, OBFUSCATE("88 E5 81 EB"));
MemoryPatch::createWithHex("libUE4.so", 0x46EA9FC, OBFUSCATE("2C E5 53 EB")); 
MemoryPatch::createWithHex("libUE4.so", 0x4AF54FC, OBFUSCATE("3C C5 3D EB")); 
MemoryPatch::createWithHex("libUE4.so", 0x3189AD8, OBFUSCATE("AB 16 D8 EB")); 
MemoryPatch::createWithHex("libUE4.so", 0x4831DAC, OBFUSCATE("4D B7 32 EB")); 
MemoryPatch::createWithHex("libUE4.so", 0x3189AEC, OBFUSCATE("9A 16 D8 EB")); 
MemoryPatch::createWithHex("libUE4.so", 0x3189AD8, OBFUSCATE("91 16 D8 EB")); 
MemoryPatch::createWithHex("libUE4.so", 0x4831DAC, OBFUSCATE("33 B7 32 EB")); 
MemoryPatch::createWithHex("libUE4.so", 0x4A633B4, OBFUSCATE("2D 7C 3B EB")); 
MemoryPatch::createWithHex("libUE4.so", 0x4756ADC, OBFUSCATE("B6 49 2F EB")); 
MemoryPatch::createWithHex("libUE4.so", 0x3B9CBBC, OBFUSCATE("E0 61 00 EB")); 
MemoryPatch::createWithHex("libUE4.so", 0x318B5A4, OBFUSCATE("1E 1C D8 EB")); 
MemoryPatch::createWithHex("libUE4.so", 0x4ADDCB4, OBFUSCATE("B2 65 3D EB")); 
MemoryPatch::createWithHex("libUE4.so", 0x3B845F4, OBFUSCATE("10 D0 4B E2")); 
MemoryPatch::createWithHex("libUE4.so", 0x21E21F8, OBFUSCATE("AF 76 99 EB")); 
MemoryPatch::createWithHex("libUE4.so", 0x46EAA9C, OBFUSCATE("CC 98 2D EB")); 
MemoryPatch::createWithHex("libUE4.so", 0x21E21F8, OBFUSCATE("7D 76 99 EB")); 
MemoryPatch::createWithHex("libUE4.so", 0x3CE8F18, OBFUSCATE("B9 91 05 EB")); 
MemoryPatch::createWithHex("libUE4.so", 0x3189A24, OBFUSCATE("45 14 D8 EB")); 
MemoryPatch::createWithHex("libUE4.so", 0x3B84974, OBFUSCATE("03 00 00 EB")); 
MemoryPatch::createWithHex("libUE4.so", 0x3195D84, OBFUSCATE("05 45 D8 EA")); 
MemoryPatch::createWithHex("libUE4.so", 0x3BA87A8, OBFUSCATE("85 8F 00 EB")); 
MemoryPatch::createWithHex("libUE4.so", 0x46EA9FC, OBFUSCATE("05 98 2D EB")); 
MemoryPatch::createWithHex("libUE4.so", 0x21E2154, OBFUSCATE("CC 75 99 EB")); 
MemoryPatch::createWithHex("libUE4.so", 0x21E22E8, OBFUSCATE("ED 75 99 EB")); 
MemoryPatch::createWithHex("libUE4.so", 0x3189BF8, OBFUSCATE("2D 14 D8 EB")); 
MemoryPatch::createWithHex("libUE4.so", 0x3189BAC, OBFUSCATE("DB 13 D8 EB")); 
MemoryPatch::createWithHex("libUE4.so", 0x21E2154, OBFUSCATE("D2 74 99 EB")); 
MemoryPatch::createWithHex("libUE4.so", 0x3189A24, OBFUSCATE("E5 12 D8 EB")); 
MemoryPatch::createWithHex("libUE4.so", 0x46EA9FC, OBFUSCATE("D2 96 2D EB")); 
MemoryPatch::createWithHex("libUE4.so", 0x4698BAC, OBFUSCATE("9B 4E 2C EB")); 
MemoryPatch::createWithHex("libUE4.so", 0x21E22E8, OBFUSCATE("5D 74 99 EB")); 
MemoryPatch::createWithHex("libUE4.so", 0x3189BF8, OBFUSCATE("9D 12 D8 EB")); 
MemoryPatch::createWithHex("libUE4.so", 0x318BFCC, OBFUSCATE("79 1A D8 EB")); 
MemoryPatch::createWithHex("libUE4.so", 0x4756ADC, OBFUSCATE("BC 7E 2C EB")); 
MemoryPatch::createWithHex("libUE4.so", 0x22C44B4, OBFUSCATE("F0 D8 93 3A")); 
MemoryPatch::createWithHex("libUE4.so", 0x5343D7C, OBFUSCATE("EE D6 55 3A")); 
MemoryPatch::createWithHex("libUE4.so", 0x53439F8, OBFUSCATE("D5 D5 55 3A")); 
MemoryPatch::createWithHex("libUE4.so", 0x5BF8B44, OBFUSCATE("D8 A8 78 3B")); 
MemoryPatch::createWithHex("libUE4.so", 0x5BF4B48, OBFUSCATE("D8 98 78 3B")); 
MemoryPatch::createWithHex("libUE4.so", 0x21E5BCC, OBFUSCATE("F9 0A 90 EB")); 
MemoryPatch::createWithHex("libUE4.so", 0x21E2154, OBFUSCATE("59 C0 8E EB")); 
MemoryPatch::createWithHex("libUE4.so", 0x46EA9FC, OBFUSCATE("72 E2 22 EB")); 
MemoryPatch::createWithHex("libUE4.so", 0x476DE74, OBFUSCATE("48 93 20 EB")); 
MemoryPatch::createWithHex("libUE4.so", 0x318AA44, OBFUSCATE("8E 1A C1 EB")); 
//GCloydeVoice
MemoryPatch::createWithHex("libGCloudVoice.so", 0x4BEC8, OBFUSCATE("33 E1 FF EB"));
MemoryPatch::createWithHex("libGCloudVoice.so", 0x15E974, OBFUSCATE("D6 2B 04 EB"));
MemoryPatch::createWithHex("libGCloudVoice.so", 0xF5994, OBFUSCATE("CF 87 02 EB"));
MemoryPatch::createWithHex("libGCloudVoice.so", 0x519F4, OBFUSCATE("9E F7 FF EB"));
MemoryPatch::createWithHex("libGCloudVoice.so", 0x51AA4, OBFUSCATE("C5 F7 FF EB"));
MemoryPatch::createWithHex("libGCloudVoice.so", 0x228A88, OBFUSCATE("B9 53 07 FA"));
MemoryPatch::createWithHex("libGCloudVoice.so", 0x45D54, OBFUSCATE("06 C8 FF EB"));
MemoryPatch::createWithHex("libGCloudVoice.so", 0xF5994, OBFUSCATE("D5 86 02 EB"));
MemoryPatch::createWithHex("libGCloudVoice.so", 0xF5994, OBFUSCATE("B9 86 02 EB"));
MemoryPatch::createWithHex("libGCloudVoice.so", 0x21DFD4, OBFUSCATE("44 28 07 FA"));
MemoryPatch::createWithHex("libGCloudVoice.so", 0x4EA58, OBFUSCATE("32 EA FF EB"));
MemoryPatch::createWithHex("libGCloudVoice.so", 0x2293B8, OBFUSCATE("38 54 07 FA"));
MemoryPatch::createWithHex("libGCloudVoice.so", 0x258FC, OBFUSCATE("5C 45 FF EB"));
MemoryPatch::createWithHex("libGCloudeVoice.so", 0x1B791C, OBFUSCATE("E0 37 00 EB")); 
MemoryPatch::createWithHex("libGCloudeVoice.so", 0x1A22DC, OBFUSCATE("29 E2 FF EB")); 
MemoryPatch::createWithHex("libGCloudeVoice.so", 0x1AA394, OBFUSCATE("E1 01 00 EB")); 
MemoryPatch::createWithHex("libGCloudeVoice.so", 0x1AA818, OBFUSCATE("F7 02 00 EB")); 
MemoryPatch::createWithHex("libGCloudeVoice.so", 0x1AB11C, OBFUSCATE("20 05 00 EB")); 
MemoryPatch::createWithHex("libGCloudeVoice.so", 0x1AB424, OBFUSCATE("8F 05 00 EB")); 
MemoryPatch::createWithHex("libGCloudeVoice.so", 0x1AD514, OBFUSCATE("9C 0D 00 EB")); 
MemoryPatch::createWithHex("libRoosterNN.so", 0x9FDE8, "2D E9 F8 4F").Modify();
MemoryPatch::createWithHex("libRoosterNN.so", 0xA054E, "2D E9 F8 4F").Modify();
//Бан на 10 лет 

MemoryPatch::createWithHex("libanogs.so",0x133560, "  00 48 2D E9 ", 4).Modify();// 00 48 2D E9
MemoryPatch::createWithHex("libanogs.so",0x1DCB38, "  00 48 2D E9 ", 4).Modify();// 00 48 2D E9
MemoryPatch::createWithHex("libanogs.so",0x173C3C, "  04 D0 8D E2 ", 4).Modify();// 04 D0 8D E2
//الحمايه القويه 
MemoryPatch::createWithHex("libanogs.so",0x14EA48, "  1E FF 2F E1 ", 4).Modify();// 1E FF 2F E1
MemoryPatch::createWithHex("libanogs.so",0x1F7118, "  F0 4F 2D E9 ", 4).Modify();// F0 4F 2D E9

// Даты 

//CLASH
MemoryPatch::createWithHex("libUE4.so",0x41DF94,"h FF FF FF FF",131072).Modify();
MemoryPatch::createWithHex("libUE4.so",0x41DE70,"h FF FF FF FF",131072).Modify();
MemoryPatch::createWithHex("libUE4.so",0x41D650,"h FF FF FF FF",131072).Modify();
MemoryPatch::createWithHex("libUE4.so",0x41D640,"h FF FF FF FF",131072).Modify();
MemoryPatch::createWithHex("libUE4.so",0x41D61C,"h FF FF FF FF",131072).Modify();
MemoryPatch::createWithHex("libUE4.so",0x41D608,"h FF FF FF FF",131072).Modify();
MemoryPatch::createWithHex("libUE4.so",0x41D5C0,"h FF FF FF FF",131072).Modify();
MemoryPatch::createWithHex("libUE4.so",0x41D2D8,"h FF FF FF FF",131072).Modify();
MemoryPatch::createWithHex("libUE4.so",0x41D1A0,"h FF FF FF FF",131072).Modify();
MemoryPatch::createWithHex("libUE4.so",0x41D08C,"h FF FF FF FF",131072).Modify();
MemoryPatch::createWithHex("libUE4.so",0x41CFBC,"h FF FF FF FF",131072).Modify();
MemoryPatch::createWithHex("libUE4.so",0x41CFAC,"h FF FF FF FF",131072).Modify();
MemoryPatch::createWithHex("libanogs.so", 0x14dc4, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x14dc8, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fdc0, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fdc4, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fdc8, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fdcc, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fdd0, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fdd4, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fdd8, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fddc, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fde0, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fde4, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fde8, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fdec, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fdf0, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fdf4, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fdf8, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fdfc, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fe00, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fe04, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fe08, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fe0c, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fe10, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fe14, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fe18, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fe28, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fe2c, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fe30, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fe34, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fe38, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fe3c, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fe40, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fe44, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fe48, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fe4c, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fe50, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fe54, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1fe58, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b04c, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b050, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b054, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b058, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b05c, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b060, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b064, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b068, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b06c, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b070, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b074, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b078, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b07c, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b080, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b084, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b088, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b08c, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b090, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b094, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b098, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b09c, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b0a0, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b0a4, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b0a8, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b0ac, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b0c0, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b0c4, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b0c8, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b0cc, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b0d0, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b0d4, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b0d8, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b0dc, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b0e0, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b0e4, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b0e8, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b0ec, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2b0f0, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x4e7c8, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x4e7cc, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x4e7d0, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x4e7d4, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x4e7d8, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x4e7dc, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x4e7e0, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x4e7e4, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x4e7e8, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x4e7ec, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x4e7f0, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x4e7f4, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x4e7f8, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x4e7fc, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f30, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f34, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f38, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f3c, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f40, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f44, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f48, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f4c, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f50, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f54, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f58, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f5c, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f60, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f64, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f68, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f6c, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f70, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f74, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f78, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f7c, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f80, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cbd0, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cbd4, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cbd8, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cbdc, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cbe0, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cbe4, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cbe8, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cbec, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cbf0, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cbf4, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cbf8, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cbfc, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cc00, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cc04, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cc08, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cc0c, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cc10, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cc14, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cc18, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cc1c, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cc20, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41dbc, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41dc4, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41dc8, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41dcc, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41dd4, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41dd8, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41ddc, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41de0, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41de4, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41de8, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41df0, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41df4, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41dfc, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41e00, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41e04, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41e0c, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41e10, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41e14, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41e1c, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41e20, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41e28, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f30, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f34, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f38, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f3c, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f40, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f44, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f48, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f4c, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f50, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f54, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f58, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f5c, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f60, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f64, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f68, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f6c, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f70, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f74, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f78, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f7c, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x61f80, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cbd0, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cbd4, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cbd8, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cbdc, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cbe0, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cbe4, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cbe8, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cbec, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cbf0, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cbf4, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cbf8, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cbfc, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cc00, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cc04, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cc08, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cc0c, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cc10, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cc14, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cc18, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cc1c, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x5cc20, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41dbc, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41dc4, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41dc8, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41dcc, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41dd4, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41dd8, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41ddc, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41de0, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41de4, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41de8, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41df0, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41df4, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41dfc, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41e00, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41e04, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41e0c, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41e10, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41e14, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41e1c, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41e20, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x41e28, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x95ef0, "00 20 70 47").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0xd218c, "00 20 70 47").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0xd2198, "00 20 70 47").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0xd219c, "00 20 70 47").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0xd21a0, "00 20 70 47").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0xd21a4, "00 20 70 47").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0xd21a8, "00 20 70 47").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0xd21ac, "00 20 70 47").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0xd21b0, "00 20 70 47").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0xd21b4, "00 20 70 47").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0xd21b8, "00 20 70 47").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0xd21c0, "00 20 70 47").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0xd21c4, "00 20 70 47").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0xd21c8, "00 20 70 47").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0xd21cc, "00 20 70 47").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0xd21d0, "00 20 70 47").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x105d28, "00 20 70 47").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x105d2c, "00 20 70 47").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x105d34, "00 20 70 47").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x105d38, "00 20 70 47").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x105d3c, "00 20 70 47").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x105d40, "00 20 70 47").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x105d44, "00 20 70 47").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x105d48, "00 20 70 47").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x105d4c, "00 20 70 47").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x105d50, "00 20 70 47").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x105d54, "00 20 70 47").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x105d5c, "00 20 70 47").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x105d64, "00 20 70 47").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0xfa3e4, "00 20 70 47").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0xfa3e8, "00 20 70 47").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0xfa3ec, "00 20 70 47").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0xfa3f0, "00 20 70 47").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0xfa3f4, "00 20 70 47").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0xfa3f8, "00 20 70 47").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0xfa3fc, "00 20 70 47").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0xfa400, "00 20 70 47").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x138bb4, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x138bb8, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x138bc0, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x138bc8, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x138bd0, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x138bd8, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x138be0, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x138be8, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x138bf0, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x138bf8, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x138bfc, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x138c00, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x138c04, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x138c08, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x138c0c, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x15e030, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x15e034, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x15e038, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x15e03c, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x15e040, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x15e044, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x15e048, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x15e04c, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x15e050, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x15e054, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x15e058, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x15e05c, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x15e060, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x15e064, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x15e068, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x15e06c, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x15e070, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x15e074, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x15e078, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x15e07c, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x15e080, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x15e084, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x15e088, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x15e08c, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x17e090, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x17e094, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x17e098, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x17e09c, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x17e0a0, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x17e0a4, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x17e0a8, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x17e0ac, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x17e0b0, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x17e0b4, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x17e0b8, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x17e0bc, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x17e0c0, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x17e0c4, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x17e0c8, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1eabd0, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1eabd4, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1eabd8, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1eabdc, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1eabe0, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1eabe4, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1eabe8, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1eabec, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1eabf0, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1eabf4, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1eabf8, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1eabfc, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1eac00, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1eac04, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1eac08, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1eac0c, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1eac10, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1eac14, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1eac18, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1eac1c, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1eac20, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x1eac24, "00 00 A0 E3 1E FF 2F E1").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2886e4, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2886ec, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2886f4, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2886f8, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2886fc, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x288700, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x288704, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x288708, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x288710, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x288718, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x28871c, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x288720, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x288724, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x216460, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x216468, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x216470, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x216474, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x216478, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x21647c, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x216480, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x216488, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x216490, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x216494, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x216498, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x21649c, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2164a4, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2164a8, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2164ac, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x2164b0, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x340e84, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x340e8c, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x340e94, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x340e98, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x340e9c, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x340ea0, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x340ea8, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x340eac, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x340eb4, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x340ebc, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x340ec0, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x340ec4, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x340ec8, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x340ecc, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x340ed0, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x340ed8, "2d 1e 00 01").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x4be700, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x4be708, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x4be70c, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x4be710, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x4be714, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x4be71c, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x4be720, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x4be728, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x4be730, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x4be734, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x4be738, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x4be73c, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x4be740, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x4be744, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x4be74c, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x3e6ae0, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x3e6ae4, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x3e6ae8, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x3e6aec, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x3e6af0, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x3e6af4, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x3e6af8, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x3e6afc, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x3e6b00, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x3e6b04, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x3e6b08, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x3e6b14, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x3e6b18, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x3e6b1c, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x3e6b20, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x3e6b24, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x3e6b28, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x3e6b2c, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x3e6b30, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x3e6b34, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x3e6b38, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x494790, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x494794, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x494798, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x49479c, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x4947a0, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x4947a4, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x4947a8, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x4947ac, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x4947b0, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x4947b4, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x4947b8, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x4947bc, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x4947c0, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x4947c4, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x4947c8, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x4947cc, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x4947d0, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x4947d4, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x4947d8, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x4947dc, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x4947e0, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanogs.so", 0x4947e4, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x2de54, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x2de58, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x2de5c, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x2de60, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x2de64, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x2de68, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x2de6c, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x2de70, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x2de74, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x2de78, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x2de7c, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x2de80, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x6abec, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x6abf0, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x6abf8, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x6ac00, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x6ac08, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x6ac10, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x6ac18, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x6ac20, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x6ac28, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x6ac30, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x6ac38, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x6ac40, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x59994, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x5999c, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x599a4, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x599ac, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x599b4, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x599bc, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x599c4, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x599cc, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x70c48, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x70c4c, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x70c50, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x70c54, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x70c58, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x70c5c, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x70c60, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x70c64, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x70c68, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x71d58, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x71d5c, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x71d60, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x71d64, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x71d68, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x71d6c, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x71d70, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x71d74, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x71d78, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x71d7c, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x71d80, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x71d84, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x71d88, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x71d8c, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x71d90, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x71d94, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x71d98, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x71d9c, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x71da0, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x71da4, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x71da8, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x71dac, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x71db0, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x71db4, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x7fb9c, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x7fba0, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x7fba8, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x7fbac, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x7fbb0, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x7fbb4, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x7fbb8, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x7fbbc, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x7fbc4, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x7fbcc, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x7fbd0, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x7fbd4, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x7fbd8, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x7fbdc, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x7fbe0, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x7fbe8, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x7fbf0, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x7fbf4, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x7fbf8, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x7fbfc, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x7fc00, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x7fc04, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x1a1bac, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x1a1bb0, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x1a1bb4, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x1a1bb8, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x1a1bbc, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x1a1bc0, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x1a1bc4, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x1a1bc8, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x1a1bcc, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x1a1bd0, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x1a1bd4, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x1a1bd8, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x14aba8, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x14abb0, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x14abb4, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x14abb8, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x14abbc, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x14abc4, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x14abc8, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x14abcc, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x14abd0, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x14abd4, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x14abdc, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x14abe0, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x14abe4, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x14abe8, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libgcloud.so", 0x14abf0, "0e 06 00 d8").Modify(); 
MemoryPatch::createWithHex("libanort.so", 0x1ada0, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanort.so", 0x1adac, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanort.so", 0x1adb4, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanort.so", 0x1adbc, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanort.so", 0x1adc4, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanort.so", 0x1adcc, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanort.so", 0x1add4, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanort.so", 0x1addc, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanort.so", 0x1adec, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanort.so", 0x1adf4, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanort.so", 0x3c9d8, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanort.so", 0x3c9e4, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanort.so", 0x6aab0, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanort.so", 0x6ab00, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanort.so", 0xcc3e4, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanort.so", 0xcc3e8, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanort.so", 0xcc3ec, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libanort.so", 0x6ab04, "00 00 00 00").Modify(); 
MemoryPatch::createWithHex("libc++_shared.so", 0x30acc, "00 22 c0 06").Modify(); 
MemoryPatch::createWithHex("libc++_shared.so", 0x30ad0, "00 22 c0 06").Modify(); 
MemoryPatch::createWithHex("libc++_shared.so", 0x30ad8, "00 22 c0 06").Modify(); 
MemoryPatch::createWithHex("libc++_shared.so", 0x30ae0, "00 22 c0 06").Modify(); 
MemoryPatch::createWithHex("libc++_shared.so", 0x30ae4, "00 22 c0 06").Modify(); 
MemoryPatch::createWithHex("libc++_shared.so", 0x30ae8, "00 22 c0 06").Modify(); 
MemoryPatch::createWithHex("libc++_shared.so", 0x30aec, "00 22 c0 06").Modify(); 
MemoryPatch::createWithHex("libc++_shared.so", 0x30af4, "00 22 c0 06").Modify(); 
MemoryPatch::createWithHex("libc++_shared.so", 0x30af8, "00 22 c0 06").Modify(); 
MemoryPatch::createWithHex("libc++_shared.so", 0x30b00, "00 22 c0 06").Modify(); 
MemoryPatch::createWithHex("libc++_shared.so", 0x30b08, "00 22 c0 06").Modify(); 
MemoryPatch::createWithHex("libc++_shared.so", 0x30b10, "00 22 c0 06").Modify(); 
MemoryPatch::createWithHex("libc++_shared.so", 0x30b14, "00 22 c0 06").Modify(); 
MemoryPatch::createWithHex("libc++_shared.so", 0x565d4, "00 22 c0 06").Modify(); 
MemoryPatch::createWithHex("libc++_shared.so", 0x565d8, "00 22 c0 06").Modify(); 
MemoryPatch::createWithHex("libc++_shared.so", 0x565dc, "00 22 c0 06").Modify(); 
MemoryPatch::createWithHex("libc++_shared.so", 0x565e0, "00 22 c0 06").Modify(); 
MemoryPatch::createWithHex("libc++_shared.so", 0x565e4, "00 22 c0 06").Modify(); 
MemoryPatch::createWithHex("libc++_shared.so", 0x565e8, "00 22 c0 06").Modify(); 
MemoryPatch::createWithHex("libc++_shared.so", 0x82d5c, "00 22 c0 06").Modify(); 
MemoryPatch::createWithHex("libc++_shared.so", 0x82d64, "00 22 c0 06").Modify(); 
MemoryPatch::createWithHex("libc++_shared.so", 0x82d68, "00 22 c0 06").Modify(); 
MemoryPatch::createWithHex("libc++_shared.so", 0x82d70, "00 22 c0 06").Modify(); 
MemoryPatch::createWithHex("libc++_shared.so", 0x82d74, "00 22 c0 06").Modify(); 
MemoryPatch::createWithHex("libc++_shared.so", 0x82d7c, "00 22 c0 06").Modify(); 
MemoryPatch::createWithHex("libc++_shared.so", 0x82d80, "00 22 c0 06").Modify(); 
MemoryPatch::createWithHex("libc++_shared.so", 0x82d84, "00 22 c0 06").Modify(); 
MemoryPatch::createWithHex("libc++_shared.so", 0x82d8c, "00 22 c0 06").Modify(); 
MemoryPatch::createWithHex("libc++_shared.so", 0x82d90, "00 22 c0 06").Modify(); 
MemoryPatch::createWithHex("libc++_shared.so", 0x43e078, "00 22 c0 06").Modify(); 
MemoryPatch::createWithHex("libc++_shared.so", 0x43e07c, "00 22 c0 06").Modify(); 
MemoryPatch::createWithHex("libc++_shared.so", 0x43e080, "00 22 c0 06").Modify(); 
MemoryPatch::createWithHex("libc++_shared.so", 0x43e084, "00 22 c0 06").Modify(); 
MemoryPatch::createWithHex("libc++_shared.so", 0x43e088, "00 22 c0 06").Modify(); 
MemoryPatch::createWithHex("libc++_shared.so", 0x43e08c, "00 22 c0 06").Modify(); 
MemoryPatch::createWithHex("libc++_shared.so", 0x43e090, "00 22 c0 06").Modify(); 
MemoryPatch::createWithHex("libc++_shared.so", 0x43e094, "00 22 c0 06").Modify(); 
MemoryPatch::createWithHex("libc++_shared.so", 0x43e098, "00 22 c0 06").Modify(); 
MemoryPatch::createWithHex("libc++_shared.so", 0x43e09c, "00 22 c0 06").Modify(); 
MemoryPatch::createWithHex("libc++_shared.so", 0x43e0a4, "00 22 c0 06").Modify(); 
MemoryPatch::createWithHex("libc++_shared.so", 0x43e0ac, "00 22 c0 06").Modify(); 
MemoryPatch::createWithHex("libc++_shared.so", 0x43e0b0, "00 22 c0 06").Modify(); 
MemoryPatch::createWithHex("libc++_shared.so", 0x43e0b4, "00 22 c0 06").Modify(); 
MemoryPatch::createWithHex("libc++_shared.so", 0x43e0b8, "00 22 c0 06").Modify(); 
MemoryPatch::createWithHex("libc++_shared.so", 0x300e2c, "00 22 c0 06").Modify(); 
MemoryPatch::createWithHex("libc++_shared.so", 0x300e34, "00 22 c0 06").Modify(); 
MemoryPatch::createWithHex("libc++_shared.so", 0x300e38, "00 22 c0 06").Modify(); 
MemoryPatch::createWithHex("libc++_shared.so", 0x300e3c, "00 22 c0 06").Modify(); 
MemoryPatch::createWithHex("libc++_shared.so", 0x300e40, "00 22 c0 06").Modify(); 
MemoryPatch::createWithHex("libc++_shared.so", 0x300e44, "00 22 c0 06").Modify(); 
MemoryPatch::createWithHex("libc++_shared.so", 0x300e48, "00 22 c0 06").Modify(); 
MemoryPatch::createWithHex("libc++_shared.so", 0x300e4c, "00 22 c0 06").Modify(); 
MemoryPatch::createWithHex("libc++_shared.so", 0x300e50, "00 22 c0 06").Modify(); 
MemoryPatch::createWithHex("libc++_shared.so", 0x300e54, "00 22 c0 06").Modify(); 
MemoryPatch::createWithHex("libc++_shared.so", 0x300e5c, "00 22 c0 06").Modify(); 
MemoryPatch::createWithHex("libc++_shared.so", 0x300e64, "00 22 c0 06").Modify(); 
PATCH_LIB("libanogs.so","B7994","00 00 C0 E3 1E FF 2F E1");
PATCH_LIB("libanogs.so","EA3AC","00 00 C0 E3 1E FF 2F E1");
PATCH_LIB("libanogs.so","F0154","00 00 C0 E3 1E FF 2F E1");
PATCH_LIB("libanogs.so","FE9D0","00 00 C0 E3 1E FF 2F E1");
PATCH_LIB("libanogs.so","129A0","00 00 C0 E3 1E FF 2F E1");
PATCH_LIB("libanogs.so","154A10","00 00 C0 E3 1E FF 2F E1");
PATCH_LIB("libanogs.so","164174","00 00 C0 E3 1E FF 2F E1");
PATCH_LIB("libanogs.so","16067C","00 00 C0 E3 1E FF 2F E1");
PATCH_LIB("libanogs.so","190FC8","00 00 C0 E3 1E FF 2F E1");
PATCH_LIB("libanogs.so","1A0390","00 00 C0 E3 1E FF 2F E1");
PATCH_LIB("libanogs.so","1A1178","00 00 C0 E3 1E FF 2F E1");
PATCH_LIB("libanogs.so","1A216C","00 00 C0 E3 1E FF 2F E1");
PATCH_LIB("libanogs.so","1A8124","00 00 C0 E3 1E FF 2F E1");
PATCH_LIB("libanogs.so","1B1284","00 00 C0 E3 1E FF 2F E1");
PATCH_LIB("libanogs.so","1B697C","00 00 C0 E3 1E FF 2F E1");
PATCH_LIB("libanogs.so","1B7DC8","00 00 C0 E3 1E FF 2F E1");
PATCH_LIB("libanogs.so","1C7CB4","00 00 C0 E3 1E FF 2F E1");
PATCH_LIB("libanogs.so","1C8528","00 00 C0 E3 1E FF 2F E1");
PATCH_LIB("libanogs.so","1C89F0","00 00 C0 E3 1E FF 2F E1");
PATCH_LIB("libanogs.so","1CCDE4","00 00 C0 E3 1E FF 2F E1");
PATCH_LIB("libanogs.so","1D9CB0","00 00 C0 E3 1E FF 2F E1");
PATCH_LIB("libanogs.so","1E26E0","00 00 C0 E3 1E FF 2F E1");
PATCH_LIB("libanogs.so","212F1C","00 00 C0 E3 1E FF 2F E1");
PATCH_LIB("libanogs.so","21EC2C","00 00 C0 E3 1E FF 2F E1");
PATCH_LIB("libanogs.so","21FB78","00 00 C0 E3 1E FF 2F E1");
PATCH_LIB("libanogs.so","22CC38","00 00 C0 E3 1E FF 2F E1");
PATCH_LIB("libanogs.so","2396D4","00 00 C0 E3 1E FF 2F E1");
PATCH_LIB("libanogs.so","2E8EC8","00 00 C0 E3 1E FF 2F E1");
PATCH_LIB("libanogs.so","2F5290","00 00 C0 E3 1E FF 2F E1");
PATCH_LIB("libanogs.so","32E924","00 00 C0 E3 1E FF 2F E1");
PATCH_LIB("libanogs.so","32EB4C","00 00 C0 E3 1E FF 2F E1");
PATCH_LIB("libanogs.so","348E04","00 00 C0 E3 1E FF 2F E1");
PATCH_LIB("libanogs.so","351700","00 00 C0 E3 1E FF 2F E1");
PATCH_LIB("libanogs.so","35992C","00 00 C0 E3 1E FF 2F E1");
PATCH_LIB("libanogs.so","355C58","00 00 C0 E3 1E FF 2F E1");
PATCH_LIB("libanogs.so","3564A8","00 00 C0 E3 1E FF 2F E1");
PATCH_LIB("libanogs.so","35B9E4","00 00 C0 E3 1E FF 2F E1");
PATCH_LIB("libanort.so","3B5AP","00 00 C0 E3 1E FF 2F E1");
PATCH_LIB("libanort.so","44944","00 00 C0 E3 1E FF 2F E1");
PATCH_LIB("libanort.so","75150","00 00 C0 E3 1E FF 2F E1");
PATCH_LIB("libanort.so","76A70","00 00 C0 E3 1E FF 2F E1");
PATCH_LIB("libanort.so","94590","00 00 C0 E3 1E FF 2F E1");
PATCH_LIB("libanort.so","B2388","00 00 C0 E3 1E FF 2F E1");
PATCH_LIB("libanort.so","BD570","00 00 C0 E3 1E FF 2F E1");
PATCH_LIB("libanort.so","C1F30","00 00 C0 E3 1E FF 2F E1");
PATCH_LIB("libanort.so","CC78E","00 00 C0 E3 1E FF 2F E1");
PATCH_LIB("libanort.so","CEFE4","00 00 C0 E3 1E FF 2F E1");
PATCH_LIB("libanort.so","D36E4","00 00 C0 E3 1E FF 2F E1");
PATCH_LIB("libanort.so","D7D40","00 00 C0 E3 1E FF 2F E1");
PATCH_LIB("libanort.so","FCA78","00 00 C0 E3 1E FF 2F E1");
PATCH_LIB("libanort.so","11D5F0","00 00 C0 E3 1E FF 2F E1");
PATCH_LIB("libanort.so","1263A8","00 00 C0 E3 1E FF 2F E1");
PATCH_LIB("libanort.so","3B5A0","00 00 C0 E3 1E FF 2F E1");
PATCH_LIB("libanort.so","131C84","00 00 C0 E3 1E FF 2F E1");
PATCH_LIB("libanort.so","13695C","00 00 C0 E3 1E FF 2F E1");
PATCH_LIB("libanort.so","13BF80","00 00 C0 E3 1E FF 2F E1");
PATCH_LIB("libanort.so","13695C","00 00 C0 E3 1E FF 2F E1");
PATCH_LIB("libanort.so","131C84","00 00 C0 E3 1E FF 2F E1");
PATCH_LIB("libanort.so","12C98C","00 00 C0 E3 1E FF 2F E1");
MemoryPatch::createWithHex("libUE4.so", 0xEA70C9, "E0/42/70/E8");/*⟿✆♔♔〄*/
MemoryPatch::createWithHex("libUE4.so", 0xEE794F, "91/65/21/C5");/*⟿✆♔♔〄*/
MemoryPatch::createWithHex("libUE4.so", 0x580185, "E5/F9/E6/33");/*⟿✆♔♔〄*/
MemoryPatch::createWithHex("libUE4.so", 0xF8E099, "E0/55/C9/A4");/*⟿✆♔♔〄*/
MemoryPatch::createWithHex("libUE4.so", 0x692479, "AF/5B/94/50");/*⟿✆♔♔〄*/
MemoryPatch::createWithHex("libUE4.so", 0xF8DD03, "3D/B1/18/73");/*⟿✆♔♔〄*/
MemoryPatch::createWithHex("libUE4.so", 0x9C221D, "8D/15/B0/F5");/*⟿✆♔♔〄*/
MemoryPatch::createWithHex("libUE4.so", 0xA1B5C1, "AD/29/88/A8");/*⟿✆♔♔〄*/
MemoryPatch::createWithHex("libUE4.so", 0xFD784, "0F/F2/F7/56");/*⟿✆♔♔〄*/
MemoryPatch::createWithHex("libUE4.so", 0xCFBA60, "C6/59/B9/96");/*⟿✆♔♔〄*/
MemoryPatch::createWithHex("libTDataMaster.so", 0x57F141, "40/70/A0/A1");/*⟿✆♔♔〄*/
MemoryPatch::createWithHex("libTDataMaster.so", 0xC90DC4, "62/4B/4F/4F");/*⟿✆♔♔〄*/
MemoryPatch::createWithHex("libTDataMaster.so", 0xD7A1E, "01/44/5A/D0");/*⟿✆♔♔〄*/
MemoryPatch::createWithHex("libTDataMaster.so", 0x8734C3, "E6/C4/47/7E");/*⟿✆♔♔〄*/
MemoryPatch::createWithHex("libTDataMaster.so", 0x1110C, "96/B9/9C/2B");/*⟿✆♔♔〄*/
MemoryPatch::createWithHex("libTDataMaster.so", 0x9276DB, "21/14/BA/DF");/*⟿✆♔♔〄*/
MemoryPatch::createWithHex("libTDataMaster.so", 0x18F21D, "E1/89/9A/A1");/*⟿✆♔♔〄*/
MemoryPatch::createWithHex("libTDataMaster.so", 0xD18BDF, "1C/4D/68/AE");/*⟿✆♔♔〄*/
MemoryPatch::createWithHex("libTDataMaster.so", 0x412604, "28/25/10/1A");/*⟿✆♔♔〄*/
MemoryPatch::createWithHex("libTDataMaster.so", 0x795EFF, "2D/1F/EE/06");/*⟿✆♔♔〄*/
MemoryPatch::createWithHex("libanogs.so", 0xC31C6E, "B5/30/D1/16");/*⟿✆♔♔〄*/
MemoryPatch::createWithHex("libanogs.so", 0x663B19, "CA/8A/8B/0B");/*⟿✆♔♔〄*/
MemoryPatch::createWithHex("libanogs.so", 0x4FC9C5, "A9/DA/66/D7");/*⟿✆♔♔〄*/
MemoryPatch::createWithHex("libanogs.so", 0x399087, "CF/51/E2/79");/*⟿✆♔♔〄*/
MemoryPatch::createWithHex("libanogs.so", 0xB5FD2B, "C6/DA/8C/76");/*⟿✆♔♔〄*/
MemoryPatch::createWithHex("libanogs.so", 0xBABAAD, "C5/B4/C0/53");/*⟿✆♔♔〄*/
MemoryPatch::createWithHex("libanogs.so", 0x879075, "AA/C5/20/B6");/*⟿✆♔♔〄*/
MemoryPatch::createWithHex("libanogs.so", 0x9CC155, "E5/DF/F7/0E");/*⟿✆♔♔〄*/
MemoryPatch::createWithHex("libanogs.so", 0x2930A3, "B6/11/71/C5");/*⟿✆♔♔〄*/
MemoryPatch::createWithHex("libanogs.so", 0x1D5AFB, "5D/2B/94/DC");/*⟿✆♔♔〄*/
MemoryPatch::createWithHex("libgcloud.so", 0x97B115, "70/FC/18/92");/*⟿✆♔♔〄*/
MemoryPatch::createWithHex("libgcloud.so", 0xF1D847, "22/5C/9C/DB");/*⟿✆♔♔〄*/
MemoryPatch::createWithHex("libgcloud.so", 0x20A82E, "94/F4/64/B9");/*⟿✆♔♔〄*/
MemoryPatch::createWithHex("libgcloud.so", 0x915E92, "86/34/ED/46");/*⟿✆♔♔〄*/
MemoryPatch::createWithHex("libgcloud.so", 0x9FBFC2, "31/1F/CD/E8");/*⟿✆♔♔〄*/
MemoryPatch::createWithHex("libgcloud.so", 0x913036, "62/7D/01/CD");/*⟿✆♔♔〄*/
MemoryPatch::createWithHex("libgcloud.so", 0xD9B9C8, "22/B7/D5/1B");/*⟿✆♔♔〄*/
MemoryPatch::createWithHex("libgcloud.so", 0x51765D, "D3/BB/3C/2E");/*⟿✆♔♔〄*/
MemoryPatch::createWithHex("libgcloud.so", 0x76C78F, "07/3E/12/65");/*⟿✆♔♔〄*/
MemoryPatch::createWithHex("libgcloud.so", 0xDE1BA, "64/B8/79/02");/*⟿✆♔♔〄*/
MemoryPatch::createWithHex("libCrashSight.so", 0x92E7D0, "0B/52/5E/24");/*⟿✆♔♔〄*/
MemoryPatch::createWithHex("libCrashSight.so", 0x914168, "61/A4/99/2B");/*⟿✆♔♔〄*/
MemoryPatch::createWithHex("libCrashSight.so", 0xD96248, "07/9C/F5/9C");/*⟿✆♔♔〄*/
MemoryPatch::createWithHex("libCrashSight.so", 0xED25E, "A3/A7/66/52");/*⟿✆♔♔〄*/
MemoryPatch::createWithHex("libCrashSight.so", 0x1542FC, "0F/C1/FF/50");/*⟿✆♔♔〄*/
MemoryPatch::createWithHex("libCrashSight.so", 0xB9BA79, "AE/52/51/17");/*⟿✆♔♔〄*/
MemoryPatch::createWithHex("libCrashSight.so", 0xEE8B96, "30/35/4E/86");/*⟿✆♔♔〄*/
MemoryPatch::createWithHex("libCrashSight.so", 0x405FF1, "11/13/C1/AE");/*⟿✆♔♔〄*/
MemoryPatch::createWithHex("libCrashSight.so", 0xBD1835, "22/86/D4/8B");/*⟿✆♔♔〄*/
MemoryPatch::createWithHex("libCrashSight.so", 0x851528, "86/99/B9/6C");/*⟿✆♔♔〄*/
PATCH_LIB("libanogs.so","0xE2FBC","00 00 A0 E3 1E FF 2F E1");
PATCH_LIB("libanogs.so","0xEC39C","00 00 A0 E3 1E FF 2F E1");
PATCH_LIB("libanogs.so","0x137B4C","00 00 A0 E3 1E FF 2F E1");
PATCH_LIB("libanogs.so","0x1A0390","00 00 A0 E3 1E FF 2F E1");
PATCH_LIB("libanogs.so","0x1B697C","00 00 A0 E3 1E FF 2F E1");
PATCH_LIB("libanogs.so","0x35C0B8","00 00 A0 E3 1E FF 2F E1");
PATCH_LIB("libanogs.so","0xEDF42","00 00 A0 E3 1E FF 2F E1");
PATCH_LIB("libanogs.so","0x35BF6E","00 00 A0 E3 1E FF 2F E1");
PATCH_LIB("libanogs.so","0xEDF6E","00 00 A0 E3 1E FF 2F E1");
PATCH_LIB("libanogs.so","0x35B5FE","00 00 A0 E3 1E FF 2F E1");
PATCH_LIB("libanogs.so","0x1BB8FC","00 00 A0 E3 1E FF 2F E1");
MemoryPatch::createWithHex("libgcloud.so", 0xAA0FC, "00 00 A0 E3 1E FF 2F E1").Modify();
MemoryPatch::createWithHex("libgcloud.so", 0xAA110, "00 00 A0 E3 1E FF 2F E1").Modify();
MemoryPatch::createWithHex("libgcloud.so", 0xAA114, "00 00 A0 E3 1E FF 2F E1").Modify();
MemoryPatch::createWithHex("libgcloud.so", 0xAA118, "00 00 A0 E3 1E FF 2F E1").Modify();
MemoryPatch::createWithHex("libgcloud.so", 0xAA11C, "00 00 A0 E3 1E FF 2F E1").Modify();
MemoryPatch::createWithHex("libgcloud.so", 0xAA120, "00 00 A0 E3 1E FF 2F E1").Modify();
MemoryPatch::createWithHex("libanogs.so", 0x1F775C, "00 00 A0 E3 1E FF 2F E1").Modify();
MemoryPatch::createWithHex("libanogs.so", 0x1F77A8, "00 00 A0 E3 1E FF 2F E1").Modify();
MemoryPatch::createWithHex("libanogs.so", 0x1F780C, "00 00 A0 E3 1E FF 2F E1").Modify();
MemoryPatch::createWithHex("libanogs.so", 0x1F7858, "00 00 A0 E3 1E FF 2F E1").Modify();
MemoryPatch::createWithHex("libanogs.so", 0x1F78BC, "00 00 A0 E3 1E FF 2F E1").Modify();
MemoryPatch::createWithHex("libanogs.so", 0x1F7908, "00 00 A0 E3 1E FF 2F E1").Modify();
MemoryPatch::createWithHex("libanogs.so", 0x1F796C, "00 00 A0 E3 1E FF 2F E1").Modify();
MemoryPatch::createWithHex("libanogs.so", 0x1F79B8, "00 00 A0 E3 1E FF 2F E1").Modify();
MemoryPatch::createWithHex("libanogs.so", 0x1F7A1C, "00 00 A0 E3 1E FF 2F E1").Modify();
MemoryPatch::createWithHex("libanogs.so", 0x1F7A68, "00 00 A0 E3 1E FF 2F E1").Modify();

						  
			}

    for (int i = 0; i < Actors.size(); i++) {
        auto Actor = Actors[i];
        if (isObjectInvalid(Actor))
            continue;

        if (Actor->IsA(ASTExtraPlayerController::StaticClass())) {
            localController = (ASTExtraPlayerController *) Actor;
            break;
        }
    }

    if (localController) {
        for (int i = 0; i < Actors.size(); i++) {
            auto Actor = Actors[i];
            if (isObjectInvalid(Actor))
                continue;

            if (Actor->IsA(ASTExtraPlayerCharacter::StaticClass())) {
                if (((ASTExtraPlayerCharacter *) Actor)->PlayerKey == localController->PlayerKey) {
                    localPlayer = (ASTExtraPlayerCharacter *) Actor;
                    break;
                }
            }
        }


        if (localPlayer) {
            if (localPlayer->PartHitComponent) {
                auto ConfigCollisionDistSqAngles = localPlayer->PartHitComponent->ConfigCollisionDistSqAngles;
                for (int j = 0; j < ConfigCollisionDistSqAngles.Num(); j++) {
                    ConfigCollisionDistSqAngles[j].Angle = 90.0f;
                }
                localPlayer->PartHitComponent->ConfigCollisionDistSqAngles = ConfigCollisionDistSqAngles;
            }
                ///===================== Memory Function ====================//
                        if (Config.SilentAim.Enable) {
                         draw->AddCircle(ImVec2(glWidth / 2.0f, glHeight / 2.0f), Config.SilentAim.Cross*0.5f, ToColor(Config.ColorsESP.Fov), 100, 1.0f);
                    auto WeaponManagerComponent = localPlayer->WeaponManagerComponent;
                    if (WeaponManagerComponent) {
                        auto propSlot = WeaponManagerComponent->GetCurrentUsingPropSlot();
                        if ((int) propSlot.GetValue() >= 1 && (int) propSlot.GetValue() <= 3) {
                            auto CurrentWeaponReplicated = (ASTExtraShootWeapon *) WeaponManagerComponent->CurrentWeaponReplicated;
                            if (CurrentWeaponReplicated) {
                                auto ShootWeaponComponent = CurrentWeaponReplicated->ShootWeaponComponent;
                                if (ShootWeaponComponent) {
                                    int shoot_event_idx = 162;
                                    auto VTable = (void **) ShootWeaponComponent->VTable;
                                    if (VTable && (VTable[shoot_event_idx] != shoot_event)) {
                                        orig_shoot_event = decltype(orig_shoot_event)(
                                                VTable[shoot_event_idx]);
                                        VTable[shoot_event_idx] = (void *) shoot_event;
                                    }
                                }
                            }
                        }
                    }
                }

                //Aimbot//
                
                //ايم بوت
							 if (Config.AimBot.Less) {
                    auto WeaponManagerComponent = localPlayer->WeaponManagerComponent;
                    if (WeaponManagerComponent) {
                        auto CurrentWeaponReplicated = (ASTExtraShootWeapon *) WeaponManagerComponent->CurrentWeaponReplicated;
                        if (CurrentWeaponReplicated) {
                            auto ShootWeaponEntityComp = CurrentWeaponReplicated->ShootWeaponEntityComp;
                            auto ShootWeaponEffectComp = CurrentWeaponReplicated->ShootWeaponEffectComp;
                            if (ShootWeaponEntityComp && ShootWeaponEffectComp) {
                                if (Config.AimBot.Less) {
                                    ShootWeaponEntityComp->AccessoriesVRecoilFactor = 0.190f;
                                    ShootWeaponEntityComp->AccessoriesHRecoilFactor = 0.190f;
                                    ShootWeaponEntityComp->AccessoriesRecoveryFactor = 0.190f;

                                }
                            }
                        }
                    }
                }		
                
                
                if (Config.SilentAim.Enable) { //Config True
   auto WeaponManagerComponent = localPlayer->WeaponManagerComponent;
         if (WeaponManagerComponent) {
  auto propSlot = WeaponManagerComponent->GetCurrentUsingPropSlot();
  if ((int) propSlot.GetValue() >= 1 && (int) propSlot.GetValue() <= 3) {
   auto CurrentWeaponReplicated = (ASTExtraShootWeapon *) WeaponManagerComponent->CurrentWeaponReplicated;
              if (CurrentWeaponReplicated) {
   auto ShootWeaponComponent = CurrentWeaponReplicated->ShootWeaponComponent;
               if (ShootWeaponComponent) {
              int shoot_event_idx = 165;
        auto f_mprotect = [](uintptr_t addr, size_t len, int32_t prot) -> int32_t {
             static_assert(PAGE_SIZE == 4096);
     constexpr size_t page_size = static_cast<size_t>(PAGE_SIZE);
           void* start = // Reference Address of Start 
reinterpret_cast<void*>(addr & -page_size);
        uintptr_t end = (addr + len + page_size - 1) & -page_size;
        return mprotect(start, end - reinterpret_cast<uintptr_t>(start), prot);
                                    };
              auto VTable = (void **) ShootWeaponComponent->VTable;
               if (VTable && (VTable[shoot_event_idx] != shoot_event)) {
               orig_shoot_event = decltype(orig_shoot_event)(
                         VTable[shoot_event_idx]);
          f_mprotect((uintptr_t)(&VTable[shoot_event_idx]), sizeof(uintptr_t), PROT_READ | PROT_WRITE);
             VTable[shoot_event_idx] = (void *) shoot_event;
                                    }
                     }   
         }  
      } 
   }   
}
                
                
				
				if (Config.AimBot.Enable)
    {
    
    
     ASTExtraPlayerCharacter *Target = GetTargetForAimBot();
     if (Target)
     {
      bool triggerOk = false;
      if (Config.AimBot.Trigger != EAimTrigger::None)
      {
       if (Config.AimBot.Trigger == EAimTrigger::Shooting)
       {
        triggerOk = g_LocalPlayer->bIsWeaponFiring;
       }
       else if (Config.AimBot.Trigger == EAimTrigger::Scoping)
       {
        triggerOk = g_LocalPlayer->bIsGunADS;
       }
       else if (Config.AimBot.Trigger == EAimTrigger::Both)
       {
        triggerOk = g_LocalPlayer->bIsWeaponFiring && g_LocalPlayer->bIsGunADS;
       }
       else if (Config.AimBot.Trigger == EAimTrigger::Any)
       {
        triggerOk = g_LocalPlayer->bIsWeaponFiring || g_LocalPlayer->bIsGunADS;
       }
      }
      else
       triggerOk = true;
      if (triggerOk)
      {
      FVector targetAimPos = Target->GetBonePos("Head", {});
                        targetAimPos.Z += 9.f;
                       if (Config.SilentAim.Target == EAimTarget::Chest) {
                       
                       targetAimPos.Z -= 10.0f;
                    
                    }
                    
                       
          
         auto WeaponManagerComponent = localPlayer->WeaponManagerComponent;
       if (WeaponManagerComponent)
       {
        auto propSlot = WeaponManagerComponent->GetCurrentUsingPropSlot();
        if ((int)propSlot.GetValue() >= 1 && (int)propSlot.GetValue() <= 3)
        {
         auto CurrentWeaponReplicated = (ASTExtraShootWeapon *)WeaponManagerComponent->CurrentWeaponReplicated;
         if (CurrentWeaponReplicated)
         {
          auto ShootWeaponComponent = CurrentWeaponReplicated->ShootWeaponComponent;
          if (ShootWeaponComponent)
          {
           UShootWeaponEntity *ShootWeaponEntityComponent = ShootWeaponComponent->ShootWeaponEntityComponent;
           if (ShootWeaponEntityComponent)
           {
           
          
            ASTExtraVehicleBase *CurrentVehicle = Target->CurrentVehicle;
            if (CurrentVehicle)
            {
             FVector LinearVelocity = CurrentVehicle->ReplicatedMovement.LinearVelocity;
             float dist = localPlayer->GetDistanceTo(Target) ;
    //         auto timeToTravel = dist / ShootWeaponEntityComponent->BulletFireSpeed ;
           //  targetAimPos = UKismetMathLibrary::Add_VectorVector(targetAimPos, UKismetMathLibrary::Multiply_VectorFloat(LinearVelocity, timeToTravel));
             
             
            }
            else
            {
             FVector Velocity = Target->GetVelocity();
             float dist = localPlayer->GetDistanceTo(Target) ;
      //       auto timeToTravel = dist / ShootWeaponEntityComponent->BulletFireSpeed;
         //    targetAimPos = UKismetMathLibrary::Add_VectorVector(targetAimPos, UKismetMathLibrary::Multiply_VectorFloat(Velocity, timeToTravel));
             
             
            }
            
            if (Config.Recc) {
                            if (g_LocalPlayer->bIsGunADS) {
                               if (g_LocalPlayer->bIsWeaponFiring) {
                                float dist = g_LocalPlayer->GetDistanceTo(Target) / 100.f;                                                                                 
                                targetAimPos.Z -= dist * Config.Recc;        
                                
                                                   }
                                                   
                                                       }       
                                }  
                                
                              
            
            
            localController->SetControlRotation(ToRotator(localController->PlayerCameraManager->CameraCache.POV.Location, targetAimPos),"");
           }
          }
         }
        }
       }
      }
     }
    }
				
				
                  								
                  												
                  																				
                    for (int i = 0; i < Actors.size(); i++) {
                auto Actor = Actors[i];
                if (isObjectInvalid(Actor))
                    continue;

                         if (Actor->IsA(ASTExtraPlayerCharacter::StaticClass())) {
                            auto Player = (ASTExtraPlayerCharacter *) Actor;

                            float Distance = localPlayer->GetDistanceTo(Player) /100.0f;
                            if (Distance > 500.0f)
                                continue;

                            if (Player->PlayerKey == localController->PlayerKey)
                                continue;

                            if (Player->TeamID == localController->TeamID)
                                continue;

                            if (Player->bDead)
                                continue;

                            //if (!Player->Mesh)
                               // continue;
                                
                            bool IsVisible = localController->LineOfSightTo(Player, {0, 0, 0}, true);

                            int SCOLOR;
                            int SCOLOR2;
                            int SCOLO;

                            if (IsVisible)
                            {
                            SCOLOR = IM_COL32(0, 255, 0, 255);
                            SCOLOR2 = IM_COL32(0, 255, 0, 25);
                            SCOLO = IM_COL32(255, 100, 0, 100);
                            }else{
                            SCOLOR = IM_COL32(255, 0, 0, 255);
                            SCOLOR2 = IM_COL32(255, 0, 0, 25);
                            SCOLO = IM_COL32(0, 0, 0, 100);
                            }
                            
                            
                           int Colorhealth;
						int healthOutline;
                        if (Player->bIsAI)
						   {
                            totalBots++;
							Colorhealth = IM_COL32(0, 255, 0, 90);
							healthOutline = IM_COL32(0, 255, 174, 255);
						    }
                        else 
						    {
							totalEnemies++;
							Colorhealth = IM_COL32(255, 100, 0, 100);
							healthOutline = IM_COL32(255, 0, 0, 255);
							
							}
							///int SCOLOR3;

                                              if (Player->bIsAI)
                                              {
                                              SCOLO = IM_COL32(0, 255, 0, 90);
                                              }

											             if (Config.IPadView) {
   
        auto objs = UObject::GetGlobalObjects();
        for (int i = 0; i < objs.Num(); i++) {
        auto Object = objs.GetByIndex(i);
        if (isObjectInvalid(Object))
        continue;
        if (Object->IsA(ULocalPlayer::StaticClass())) {
        auto playerChar = (ULocalPlayer *) Object;      
        playerChar->AspectRatioAxisConstraint = EAspectRatioAxisConstraint::AspectRatio_MaintainYFOV;
        }     
        }
     }
											  
											  
											  
		           
											       if (Config.FightFps) {
auto objs = UObject::GetGlobalObjects();
for (int i = 0; i < objs.Num(); i++) {
auto Object = objs.GetByIndex(i);
if (isObjectInvalid(Object))
continue;
if (Object->IsA(USTExtraGameInstance::StaticClass())) {
                auto playerChar = (USTExtraGameInstance *) Object;      
          playerChar->UserDetailSetting.PUBGDeviceFPSDef = 90;   //90 Pfs Settings
                playerChar->UserDetailSetting.PUBGDeviceFPSLow = 90;
                playerChar->UserDetailSetting.PUBGDeviceFPSMid = 90;
                playerChar->UserDetailSetting.PUBGDeviceFPSHigh = 90;
                playerChar->UserDetailSetting.PUBGDeviceFPSHDR = 90;
                playerChar->UserDetailSetting.PUBGDeviceFPSUltralHigh = 90;
}
}
}
											  
											  if (Config.PlayerESP.Alert){
bool shit = false;
                            FVector MyPosition, EnemyPosition;
                            ASTExtraVehicleBase * CurrentVehiclea = Player->CurrentVehicle;
                            if (CurrentVehiclea) {
                                MyPosition = CurrentVehiclea->RootComponent->RelativeLocation;
                            } else {
                                MyPosition = Player->RootComponent->RelativeLocation;
                            }
                            ASTExtraVehicleBase * CurrentVehicle = localPlayer->CurrentVehicle;
                            if (CurrentVehicle) {
                                EnemyPosition = CurrentVehicle->RootComponent->RelativeLocation;
                            } else {
                                EnemyPosition = localPlayer->RootComponent->RelativeLocation;
                            }
                            FVector EntityPos = WorldToRadar(localController->PlayerCameraManager->CameraCache.POV.Rotation.Yaw, MyPosition, EnemyPosition, NULL, NULL, Vector3(glWidth, glHeight, 0), shit);
                            FVector angle = FVector();
                            Vector3 forward = Vector3((float)(glWidth / 2) - EntityPos.X, (float)(glHeight / 2) - EntityPos.Y, 0.0f);
                            VectorAnglesRadar(forward, angle);
                            const auto angle_yaw_rad = DEG2RAD(angle.Y + 180.f);
                            const auto new_point_x = (glWidth / 2) + (55/*alert dist from me*/) / 2 * 8 * cosf(angle_yaw_rad);
                            const auto new_point_y = (glHeight / 2) + (55/*alert dist from me*/) / 2 * 8 * sinf(angle_yaw_rad);
                            std::array<Vector3, 3> points { Vector3(new_point_x - ((90) / 4 + 3.5f) / 2, new_point_y - ((55) / 4 + 3.5f) / 2, 0.f), Vector3(new_point_x + ((90) / 4 + 3.5f) / 4, new_point_y, 0.f), Vector3(new_point_x - ((90) / 4 + 3.5f) / 2, new_point_y + ((55) / 4 + 3.5f) / 2, 0.f)};
                            RotateTriangle(points, angle.Y + 180.f);
                                                    draw->AddTriangle(ImVec2(points.at(0).X, points.at(0).Y), ImVec2(points.at(1).X, points.at(1).Y), ImVec2(points.at(2).X, points.at(2).Y), SCOLOR, 1.5f);
       draw->AddTriangleFilled(ImVec2(points.at(0).X, points.at(0).Y), ImVec2(points.at(1).X, points.at(1).Y), ImVec2(points.at(2).X, points.at(2).Y), SCOLOR);
       }
       
       
       
       if (Config.PlayerESP.WeaponId) {
        auto WeaponManagerComponent = Player->WeaponManagerComponent;
        if (WeaponManagerComponent) {
            {
          auto CurrentWeaponReplicated = (ASTExtraShootWeapon *)WeaponManagerComponent->CurrentWeaponReplicated;
          if (CurrentWeaponReplicated) {
           auto WeaponId = (int)CurrentWeaponReplicated->GetWeaponID();
           if (WeaponId) {
            std::string s;
            s += CurrentWeaponReplicated->GetWeaponName().ToString();
            auto textSize = ImGui::CalcTextSize2(s.c_str(), 0, ((float) density / 30.0f));
            //draw->AddText(NULL, ((float) density / 30.0f), {RootPosSC.x - (textSize.x / 2), RootPosSC.y}, IM_COL32(255, 255, 255, 255), s.c_str());
           }
          }
         }
        }
       }

	 	// if (Bypass) {Write<float>(UE4 + 0x6B29A38, 0);}
	   
			if (Config.PlayerESP.Radar) {          
bool out = false;                              
                     struct Vector3 Pos;
                     Pos.X = screenWidth / 4.395;
                     Pos.Y = screenHeight / 200;
                     struct Vector3 Size;
                     Size.X = 200; //Width of Radar Box.
                     Size.Y = 210; //Height of Radar Box.
                     float RadarCenterX = Pos.X + (Size.X / 2);
                     float RadarCenterY = Pos.Y + (Size.Y / 2);
                     ImColor CircleColor = ImColor(0, 0, 0, 20);
                     ImColor PointColor = ImColor(255, 255, 255, 150);
                     draw->AddLine(ImVec2(RadarCenterX, RadarCenterY), ImVec2(RadarCenterX, Pos.Y), IM_COL32(255, 000, 000, 0), 0.f);
                     draw->AddLine(ImVec2(RadarCenterX, RadarCenterY), ImVec2(Pos.X , RadarCenterY), IM_COL32(255, 000, 000, 0), 0.f);
                     draw->AddLine(ImVec2(Pos.X, RadarCenterY), ImVec2(Pos.X + Size.X, RadarCenterY), IM_COL32(255, 000, 000, 0), 0.f);
                     draw->AddLine(ImVec2(RadarCenterX, RadarCenterY), ImVec2(RadarCenterX, Pos.Y + Size.Y), IM_COL32(255, 000, 000, 0), 0.f);
                            
                     draw->AddCircleFilled(ImVec2(RadarCenterX, RadarCenterY), 100.f, CircleColor, 1000); //Background
                     draw->AddCircle(ImVec2(RadarCenterX, RadarCenterY), 100.f, PointColor, 1000);
                     draw->AddCircle(ImVec2(RadarCenterX, RadarCenterY), 80.f, PointColor, 1000);
                     draw->AddCircle(ImVec2(RadarCenterX, RadarCenterY), 60.f, PointColor, 1000);
                     draw->AddCircle(ImVec2(RadarCenterX, RadarCenterY), 25.f, PointColor, 1000);
                     draw->AddCircleFilled(ImVec2(RadarCenterX + 0.5f, RadarCenterY + 0.5f), 3.f, PointColor, 1000);
                 }
                 
                 
                 if (Config.PlayerESP.Radar) 
					 {
                      FVector MyPosition;
                      ASTExtraVehicleBase *CurrentVehiclea = Player->CurrentVehicle;
                 if (CurrentVehiclea) {
                      MyPosition = CurrentVehiclea->RootComponent->RelativeLocation;
                       } else {
                      MyPosition = Player->RootComponent->RelativeLocation;
                       }                                     
                      FVector EnemyPosition;
                      ASTExtraVehicleBase *CurrentVehicle = localPlayer->CurrentVehicle;
                 if (CurrentVehicle) {
                      EnemyPosition = CurrentVehicle->RootComponent->RelativeLocation;
                       }  else {
                      EnemyPosition = localPlayer->RootComponent->RelativeLocation;
                }
               bool out = false;                              
               struct Vector3 Pos;
               Pos.X = screenWidth / 4.395;
               Pos.Y = screenHeight / 200;
               struct Vector3 Size;
               Size.X = 200; //Width of Radar Box.
               Size.Y = 210; //Height of Radar Box.
               float RadarCenterX = Pos.X + (Size.X / 2);
               float RadarCenterY = Pos.Y + (Size.Y / 2);                                    
                                                   
               bool IsVisible = true;
               FVector RadarSketch = WorldToRadar(localController->PlayerCameraManager->CameraCache.POV.Rotation.Yaw, MyPosition, EnemyPosition, Pos.X, Pos.Y, Vector3(Size.X, Size.Y, 0), out);
                                if (Distance >= 0.f) {
                                
                                draw->AddCircleFilled(ImVec2(RadarSketch.X, RadarSketch.Y), 5, SCOLOR, 0.0f);
                 
             }
}
                    if (Config.PlayerESP.NoBot)
                        if (Player->bIsAI)
                            continue;

                    auto HeadPos = Player->GetBonePos("Head", {});
                            HeadPos.Z = HeadPos.Z + 12.5f; //head se line ooper
                            ImVec2 headPosSC;

                            auto RootPos = Player->GetBonePos("Root", {});
                            ImVec2 RootPosSC;
                            if (W2S(HeadPos, (FVector2D *) &headPosSC) && W2S(RootPos, (FVector2D *) &RootPosSC)) {
							
				    float magic_number = (Distance);
                    float mx = (glWidth / 4) / magic_number;

                    float healthLength = glWidth / 17;
                    if (healthLength < mx)
                        healthLength = mx;
						
						if (Config.PlayerESP.LineTop) {
						draw->AddLine({(float) glWidth / 2, 90}, headPosSC,
                                                  SCOLOR, 0.2f);
                    } 
										
							if (Config.PlayerESP.Skeleton) {
                                // ESP Head
                                static std::vector<std::string> right_arm{"neck_01",
                                                                              "clavicle_r",
                                                                              "upperarm_r",
                                                                              "lowerarm_r",
                                                                              "hand_r", "item_r"};
                                    static std::vector<std::string> left_arm{"neck_01",
                                                                             "clavicle_l",
                                                                             "upperarm_l",
                                                                             "lowerarm_l",
                                                                             "hand_l", "item_l"};
                                    static std::vector<std::string> spine{"Head", "neck_01",
                                                                          "spine_03",
                                                                          "spine_02", "spine_01",
                                                                          "pelvis"};
                                    static std::vector<std::string> lower_right{"pelvis", "thigh_r",
                                                                                "calf_r", "foot_r"};
                                    static std::vector<std::string> lower_left{"pelvis", "thigh_l",
                                                                               "calf_l", "foot_l"};
                                    static std::vector<std::vector<std::string>> skeleton{right_arm,
                                                                                          left_arm,
                                                                                          spine,
                                                                                          lower_right,
                                                                                          lower_left};

                                    for (auto &boneStructure: skeleton) {
                                        std::string lastBone;
                                        for (std::string &currentBone: boneStructure) {
                                            if (!lastBone.empty()) {
                                                ImVec2 boneFrom, boneTo;
                                                if (W2S(Player->GetBonePos(lastBone.c_str(), {}),
                                                        (FVector2D *) &boneFrom) &&
                                                    W2S(Player->GetBonePos(currentBone.c_str(), {}),
                                                        (FVector2D *) &boneTo)) {
                                                    draw->AddLine(boneFrom, boneTo,
                                                                SCOLOR, Config.Skeleton);
                                                }
                                            }
                                            lastBone = currentBone;
                                        }
                                    }              	 
								}
				    	
				                	if (Config.PlayerESP.Box3D) {
                            float boxHeight = abs(headPosSC.y - RootPosSC.y);
                                    float boxWidth = boxHeight * 0.65f;
                                    ImVec2 vStart = {headPosSC.x - (boxWidth / 2), headPosSC.y};
                                    ImVec2 vEnd = {vStart.x + boxWidth, vStart.y + boxHeight};

                                    draw->AddRect(vStart, vEnd, SCOLOR, 1.5f, 240, 1.7f);
                                    draw->AddRectFilled(vStart, vEnd, SCOLOR2, 1.5f, 240);
                                }
                                     
				                	if (Config.PlayerESP.Name || Config.PlayerESP.Distance) {
                                    DrawBoxEnemy(draw, ImVec2(headPosSC.x , headPosSC.y - 25), ImVec2(headPosSC.x , headPosSC.y - 25), 22, IM_COL32(0, 0, 0, 255));
                               }
						       /*if (Config.ESPMenu.Name) {
                                    std::string s;
                                    int NameColor;
                                    float a = 5;

                                    if (Player->bIsAI) {
                                        NameColor = IM_COL32(0, 255, 0, 255);
										s += std::to_string((int) Player->TeamID);
                                        s += "  [BOT] ";								    
                                    } else {
                                        NameColor = IM_COL32(255, 255, 100, 255);
                                        s += "[";
                                        s += std::to_string((int) Player->TeamID);
                                        s += "] ";
                                        s += Player->PlayerName.ToString();
                                    }
                                    draw->AddText(NULL, 15.f, ImVec2(headPosSC.x  + a, headPosSC.y - 35.0f), NameColor, s.c_str());
                                }*/
                                if (Config.PlayerESP.Health) {
                                                int CurHP = (int) std::max(0, std::min(
                                                        (int) Player->Health,
                                                        (int) Player->HealthMax));
                                                int MaxHP = (int) Player->HealthMax;

                                            
														
												  long HPColor;
                                                    if (Player->Health < 25)
                                                       HPColor = IM_COL32(0, 203, 255, 110);
                                                 else if (Player->Health < 50)
                                                       HPColor = IM_COL32(255, 0, 233, 120);
                                                 else if ( Player->Health < 75)
                                                       HPColor = IM_COL32(255, 0, 233, 120);
                                                  else
                                                       HPColor = SCOLO;

                                                //if (Config.PlayerESP.ShowKnockedHealth) {
                                                if (Player->Health == 0.0f && !Player->bDead) {
                                                   SCOLOR = IM_COL32(250, 0, 0, 80);
                                                   
                                                    HPColor = IM_COL32(255, 0, 0, 110);

                                                    CurHP = Player->NearDeathBreath;
                                                    if (Player->NearDeatchComponent) {
                                                        MaxHP = Player->NearDeatchComponent->BreathMax;
                                                    }
                                                }
                                                //}

                                                float boxWidth = density / 1.6f;
                                                boxWidth -= std::min(
                                                        ((boxWidth / 2) / 0.001f) * Distance,
                                                        boxWidth / 2);
                                                float boxHeight = boxWidth * 0.15f;


                                                ImVec2 vStart = {headPosSC.x - (boxWidth / 2),
                                                                 headPosSC.y -
                                                                 (boxHeight * 2.001f)};

                                                ImVec2 vEndFilled = {
                                                        vStart.x + (CurHP * boxWidth / MaxHP),
                                                        vStart.y + boxHeight};
                                                ImVec2 vEndRect = {vStart.x + boxWidth,
                                                                   vStart.y + boxHeight};

                                                draw->AddRectFilled(vStart, vEndFilled, HPColor,
                                                                    10.0f);
                                                draw->AddRect(vStart, vEndRect,
                                                              SCOLO, 10.0f);
                                            }
                              if (Config.PlayerESP.Name || Config.PlayerESP.Name || Config.PlayerESP.Distance) {
                                    float boxWidth = density / 1.6f; // width
                                boxWidth -= std::min(((boxWidth / 2) / 00.0f) * Distance,
                                                     boxWidth / 2);
                                float boxHeight = boxWidth * 0.15f;
                                    std::string s;
                                    
                                    

                                    if (Config.PlayerESP.TeamID) {
                                       
                                        s += std::to_string(Player->TeamID);
                                        s += " ";
                                   
                                    }

                                    if (Config.PlayerESP.Name) {
                                        if (Player->bIsAI) {                                       
                                        s += "  BOT ";
                                        
                                    } else {
                                    
                                  
                                       s += Player->PlayerName.ToString();
                                        }
                                    }

                                    if (Config.PlayerESP.Distance) {
                                        if (!s.empty()) {
                                            s += " ";
                                        }
                                        s += std::to_string((int)Distance);
                                        s += "m";
                                    }
                         
												  
							auto textSize = ImGui::CalcTextSize2(s.c_str(), 0, ((float) density / 30.0f));
                            draw->AddText(NULL, ((float) density / 30.0f), {headPosSC.x - (textSize.x / 2), headPosSC.y - (boxHeight * 1.83f)}, IM_COL32(255, 255, 255, 255), s.c_str());

                        }
                    }
                }
                

					//اوت

                if (Actors[i]->IsA(APickUpWrapperActor::StaticClass())) {
                            auto PickUp = (APickUpWrapperActor *) Actors[i];
                            if (Items[PickUp->DefineID.TypeSpecificID]) {
														
                                auto RootComponent = PickUp->RootComponent;
                                if (!RootComponent)
                                    continue;

                                float Distance = PickUp->GetDistanceTo(localPlayer) / 100.f;

                                FVector2D itemPos;
                                if (W2S(PickUp->K2_GetActorLocation(), &itemPos)) {
                                    std::string s;
                                    uint32_t tc = 0xFF000000;
									
                                    for (auto &category : items_data) {
                                         for (auto &item : category["Items"]) {
                                             if (item["itemId"] ==
                                                 PickUp->DefineID.TypeSpecificID) {
                                                 s = item["itemName"].get<std::string>();
                                                 tc = strtoul(
                                                 item["itemTextColor"].get<std::string>().c_str(),
                                                 0,
                                                 16);
                                                 break;
                                              }
                                         }
                                    }
                                    s += " - ";
                                    s += std::to_string((int) Distance);
                                    s += "m";
                                                        
									draw->AddText(NULL, ((float) density / 25.0f),
                                                              {itemPos.X, itemPos.Y},
                                                              tc, s.c_str());
                           }
                      }
                }
					                
						
				if (Config.PlayerESP.LootBox) 
     {
                            if (Actor->IsA(APickUpListWrapperActor::StaticClass())) {
                                auto LootBox = (APickUpListWrapperActor *) Actor;
                                auto RootComponent = Actor->RootComponent;
                                if (!RootComponent)
                                    continue;
                                float Distance = LootBox->GetDistanceTo(localPlayer) / 100.f;

                                FVector2D lootboxPos;
        if (Config.PlayerESP.LootBox) {
                                    FVector Hunt;
                            Hunt.X = 70.0f; 
                            Hunt.Y = 70.0f; // Front
                            Hunt.Z = 35.0f; // Height
                                Box3D1(draw, LootBox->K2_GetActorLocation(), Hunt, IM_COL32(0, 255, 0, 250));       
                                } 
                                if (W2S(LootBox->K2_GetActorLocation(), &lootboxPos)) {
                                    std::string s = ICON_FA_ARCHIVE"";
                                    s += " [";
                                    s += std::to_string((int) Distance);
                                    s += "M]";

                                    draw->AddText(NULL, ((float) density / 15.0f),
                                                  {lootboxPos.X, lootboxPos.Y},
                                                  IM_COL32(255, 0, 0, 255), s.c_str());
                                }
                            }
                        }
                        
                               	if (Config.PlayerESP.Grenade) {
						if (Actors[i]->IsA(ASTExtraGrenadeBase::StaticClass())) {
							auto Grenade = (ASTExtraGrenadeBase *) Actors[i];
							auto RootComponent = Grenade->RootComponent;
							if (!RootComponent)
								continue;
							float Distance = Grenade->GetDistanceTo(localPlayer) / 70.f;
							FVector2D grenadePos;
							if (W2S(Grenade->K2_GetActorLocation(), & grenadePos)) {
								std::string s = std::to_string((int) Distance);
								s += " m";
								std::string t;
								t += "!!!...MOVE  MOVE  MOVE...!!!";
								auto textSize = ImGui::CalcTextSize2(t.c_str(), 0, ((float) density / 17.0f));
								draw->AddText(NULL, ((float) density / 17.0f), ImVec2(glWidth / 2 - (textSize.x / 2), 110), IM_COL32(255, 0, 0, 220), t.c_str());
								draw->AddText(NULL, ((float) density / 25.0f), {grenadePos.X - 10, grenadePos.Y - 10}, IM_COL32(0, 0, 255, 255), s.c_str());
								draw->AddCircleFilled(ImVec2(grenadePos.X, grenadePos.Y), glHeight / (float) 1080 * 20, IM_COL32(255, 0, 0, 255), 0);
							}
						}
					}
					
					
                            if (Config.PlayerESP.Vehicle || Config.PlayerESP.VehicleFuel || Config.PlayerESP.VehicleHP)
					{
					if (Actors[i]->IsA(ASTExtraVehicleBase::StaticClass()))
                        {
                            auto Vehicle = (ASTExtraVehicleBase *)Actors[i];
                            if (!Vehicle->Mesh)
                                continue;
                            int CurHP = (int) std::max(0, std::min((int) Vehicle->VehicleCommon->HP, (int) Vehicle->VehicleCommon->HPMax));
                            int MaxHP = (int) Vehicle->VehicleCommon->HPMax;
                            long curHP_Color = IM_COL32(std::min(((510 * (MaxHP - CurHP)) / MaxHP), 255), std::min(((510 * CurHP) / MaxHP), 255), 0, 155);
                            float Distance = Vehicle->GetDistanceTo(localPlayer) / 100.f;
                            FVector2D vehiclePos;
                            if (W2S(Vehicle->K2_GetActorLocation(), &vehiclePos))
                            {
                                auto mWidthScale = std::min(0.10f * Distance, 50.f);
                                auto mWidth = 70.f - mWidthScale;
                                auto mHeight = mWidth * 0.15f;
                                if (Config.PlayerESP.Vehicle)
                                {
                                    std::string s = GetVehicleName(Vehicle);
                                    s += ICON_FA_CAR" [";
                                    s += std::to_string((int)Distance);
                                    s += "]";
                                    draw->AddText(NULL, ((float)density / 30.0f), {vehiclePos.X - (mWidth / 2), vehiclePos.Y}, ToColor(Config.ColorsESP.Vehicle), s.c_str());
                                }
                                if (Config.PlayerESP.Vehicle) {
                                    std::string sf;
                                    sf += "[Fuel:";
                                    sf += std::to_string((int)(100 * Vehicle->VehicleCommon->Fuel / Vehicle->VehicleCommon->FuelMax));
                                    sf += "]";
                                    draw->AddText(NULL, ((float)density / 30.0f), {vehiclePos.X - (mWidth / 2), vehiclePos.Y + 15.f}, IM_COL32(255, 255, 0, 255), sf.c_str());
                                }
                                if (Config.PlayerESP.Vehicle)
                                {
                                    ImVec2 vStart = {vehiclePos.X - (mWidth / 2), vehiclePos.Y - (mHeight * 1.5f)};
                                    ImVec2 vEndFilled = {vStart.x + (CurHP * mWidth / MaxHP), vStart.y + mHeight};
                                    ImVec2 vEndRect = {vStart.x + mWidth, vStart.y + mHeight};
                                    draw->AddRectFilled(vStart, vEndFilled, curHP_Color, 3.2f, 240);
                                    draw->AddRect(vStart, vEndRect, IM_COL32(000, 000, 000, 255), 3.2f, 240);
                                }
                             }
                             }
                             }
                            }}} 

         g_LocalController = localController;
    g_LocalPlayer = localPlayer;

    g_LocalController = localController;
    g_LocalPlayer = localPlayer;

       ImGui::GetForegroundDrawList()->AddRectFilled({glWidth /2-50,40},{glWidth /2,80},ImColor(255, 0, 0,110));
       ImGui::GetForegroundDrawList()->AddRectFilled({glWidth /2+50,40},{glWidth /2,80},ImColor(3, 255, 40,110)); 
       sprintf(extras, "%d", totalEnemies);
       ImGui::GetForegroundDrawList()->AddText({glWidth /2-35,45}, ImColor(255,255,255), extras);
       sprintf(extras, "%d", totalBots);
       ImGui::GetForegroundDrawList()->AddText({glWidth /2+15,45}, ImColor(255,255,255), extras);
                    

	               if (Config.AimBot.Enable) {
draw->AddCircle(ImVec2(glWidth / 2.0f, glHeight / 2.0f), Config.AimBot.Cross*0.5f, ToColor(Config.ColorsESP.Fov), 100, 1.0f);
}
        fps.update();
    }
}

// ======================================================================== //// ======================================================================== //

    std::string getClipboardText() {
    if (!g_App)
        return "";

    auto activity = g_App->activity;
    if (!activity)
        return "";

    auto vm = activity->vm;
    if (!vm)
        return "";

    auto object = activity->clazz;
    if (!object)
        return "";

    std::string result;

    JNIEnv *env;
    vm->AttachCurrentThread(&env, 0);
    {
        auto ContextClass = env->FindClass("android/content/Context");
        auto getSystemServiceMethod = env->GetMethodID(ContextClass, "getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;");

        auto str = env->NewStringUTF("clipboard");
        auto clipboardManager = env->CallObjectMethod(object, getSystemServiceMethod, str);
        env->DeleteLocalRef(str);

        auto ClipboardManagerClass = env->FindClass("android/content/ClipboardManager");
        auto getText = env->GetMethodID(ClipboardManagerClass, "getText", "()Ljava/lang/CharSequence;");

        auto CharSequenceClass = env->FindClass("java/lang/CharSequence");
        auto toStringMethod = env->GetMethodID(CharSequenceClass, "toString", "()Ljava/lang/String;");

        auto text = env->CallObjectMethod(clipboardManager, getText);
        if (text) {
            str = (jstring) env->CallObjectMethod(text, toStringMethod);
            result = env->GetStringUTFChars(str, 0);
            env->DeleteLocalRef(str);
            env->DeleteLocalRef(text);
        }

        env->DeleteLocalRef(CharSequenceClass);
        env->DeleteLocalRef(ClipboardManagerClass);
        env->DeleteLocalRef(clipboardManager);
        env->DeleteLocalRef(ContextClass);
    }
    vm->DetachCurrentThread();

    return result;
}

const char *GetAndroidID(JNIEnv *env, jobject context) {
    jclass contextClass = env->FindClass(/*android/content/Context*/ StrEnc("`L+&0^[S+-:J^$,r9q92(as", "\x01\x22\x4F\x54\x5F\x37\x3F\x7C\x48\x42\x54\x3E\x3B\x4A\x58\x5D\x7A\x1E\x57\x46\x4D\x19\x07", 23).c_str());
    jmethodID getContentResolverMethod = env->GetMethodID(contextClass, /*getContentResolver*/ StrEnc("E8X\\7r7ys_Q%JS+L+~", "\x22\x5D\x2C\x1F\x58\x1C\x43\x1C\x1D\x2B\x03\x40\x39\x3C\x47\x3A\x4E\x0C", 18).c_str(), /*()Landroid/content/ContentResolver;*/ StrEnc("8^QKmj< }5D:9q7f.BXkef]A*GYLNg}B!/L", "\x10\x77\x1D\x2A\x03\x0E\x4E\x4F\x14\x51\x6B\x59\x56\x1F\x43\x03\x40\x36\x77\x28\x0A\x08\x29\x24\x44\x33\x0B\x29\x3D\x08\x11\x34\x44\x5D\x77", 35).c_str());
    jclass settingSecureClass = env->FindClass(/*android/provider/Settings$Secure*/ StrEnc("T1yw^BCF^af&dB_@Raf}\\FS,zT~L(3Z\"", "\x35\x5F\x1D\x05\x31\x2B\x27\x69\x2E\x13\x09\x50\x0D\x26\x3A\x32\x7D\x32\x03\x09\x28\x2F\x3D\x4B\x09\x70\x2D\x29\x4B\x46\x28\x47", 32).c_str());
    jmethodID getStringMethod = env->GetStaticMethodID(settingSecureClass, /*getString*/ StrEnc("e<F*J5c0Y", "\x02\x59\x32\x79\x3E\x47\x0A\x5E\x3E", 9).c_str(), /*(Landroid/content/ContentResolver;Ljava/lang/String;)Ljava/lang/String;*/ StrEnc("$6*%R*!XO\"m18o,0S!*`uI$IW)l_/_knSdlRiO1T`2sH|Ouy__^}%Y)JsQ:-\"(2_^-$i{?H", "\x0C\x7A\x4B\x4B\x36\x58\x4E\x31\x2B\x0D\x0E\x5E\x56\x1B\x49\x5E\x27\x0E\x69\x0F\x1B\x3D\x41\x27\x23\x7B\x09\x2C\x40\x33\x1D\x0B\x21\x5F\x20\x38\x08\x39\x50\x7B\x0C\x53\x1D\x2F\x53\x1C\x01\x0B\x36\x31\x39\x46\x0C\x15\x43\x2B\x05\x30\x15\x41\x43\x46\x55\x70\x0D\x59\x56\x00\x15\x58\x73", 71).c_str());

    auto obj = env->CallObjectMethod(context, getContentResolverMethod);
    auto str = (jstring) env->CallStaticObjectMethod(settingSecureClass, getStringMethod, obj, env->NewStringUTF(/*android_id*/ StrEnc("ujHO)8OfOE", "\x14\x04\x2C\x3D\x46\x51\x2B\x39\x26\x21", 10).c_str()));
    return env->GetStringUTFChars(str, 0);
}

const char *GetDeviceModel(JNIEnv *env) {
    jclass buildClass = env->FindClass(/*android/os/Build*/ StrEnc("m5I{GKGWBP-VOxkA", "\x0C\x5B\x2D\x09\x28\x22\x23\x78\x2D\x23\x02\x14\x3A\x11\x07\x25", 16).c_str());
    jfieldID modelId = env->GetStaticFieldID(buildClass, /*MODEL*/ StrEnc("|}[q:", "\x31\x32\x1F\x34\x76", 5).c_str(), /*Ljava/lang/String;*/ StrEnc(".D:C:ETZ1O-Ib&^h.Y", "\x62\x2E\x5B\x35\x5B\x6A\x38\x3B\x5F\x28\x02\x1A\x16\x54\x37\x06\x49\x62", 18).c_str());

    auto str = (jstring) env->GetStaticObjectField(buildClass, modelId);
    return env->GetStringUTFChars(str, 0);
}

const char *GetDeviceBrand(JNIEnv *env) {
    jclass buildClass = env->FindClass(/*android/os/Build*/ StrEnc("0iW=2^>0zTRB!B90", "\x51\x07\x33\x4F\x5D\x37\x5A\x1F\x15\x27\x7D\x00\x54\x2B\x55\x54", 16).c_str());
    jfieldID modelId = env->GetStaticFieldID(buildClass, /*BRAND*/ StrEnc("@{[FP", "\x02\x29\x1A\x08\x14", 5).c_str(), /*Ljava/lang/String;*/ StrEnc(".D:C:ETZ1O-Ib&^h.Y", "\x62\x2E\x5B\x35\x5B\x6A\x38\x3B\x5F\x28\x02\x1A\x16\x54\x37\x06\x49\x62", 18).c_str());

    auto str = (jstring) env->GetStaticObjectField(buildClass, modelId);
    return env->GetStringUTFChars(str, 0);
}

const char *GetPackageName(JNIEnv *env, jobject context) {
    jclass contextClass = env->FindClass(/*android/content/Context*/ StrEnc("`L+&0^[S+-:J^$,r9q92(as", "\x01\x22\x4F\x54\x5F\x37\x3F\x7C\x48\x42\x54\x3E\x3B\x4A\x58\x5D\x7A\x1E\x57\x46\x4D\x19\x07", 23).c_str());
    jmethodID getPackageNameId = env->GetMethodID(contextClass, /*getPackageName*/ StrEnc("YN4DaP)!{wRGN}", "\x3E\x2B\x40\x14\x00\x33\x42\x40\x1C\x12\x1C\x26\x23\x18", 14).c_str(), /*()Ljava/lang/String;*/ StrEnc("VnpibEspM(b]<s#[9cQD", "\x7E\x47\x3C\x03\x03\x33\x12\x5F\x21\x49\x0C\x3A\x13\x20\x57\x29\x50\x0D\x36\x7F", 20).c_str());

    auto str = (jstring) env->CallObjectMethod(context, getPackageNameId);
    return env->GetStringUTFChars(str, 0);
}

const char *GetDeviceUniqueIdentifier(JNIEnv *env, const char *uuid) {
    jclass uuidClass = env->FindClass(/*java/util/UUID*/ StrEnc("B/TxJ=3BZ_]SFx", "\x28\x4E\x22\x19\x65\x48\x47\x2B\x36\x70\x08\x06\x0F\x3C", 14).c_str());

    auto len = strlen(uuid);

    jbyteArray myJByteArray = env->NewByteArray(len);
    env->SetByteArrayRegion(myJByteArray, 0, len, (jbyte *) uuid);

    jmethodID nameUUIDFromBytesMethod = env->GetStaticMethodID(uuidClass, /*nameUUIDFromBytes*/ StrEnc("P6LV|'0#A+zQmoat,", "\x3E\x57\x21\x33\x29\x72\x79\x67\x07\x59\x15\x3C\x2F\x16\x15\x11\x5F", 17).c_str(), /*([B)Ljava/util/UUID;*/ StrEnc("sW[\"Q[W3,7@H.vT0) xB", "\x5B\x0C\x19\x0B\x1D\x31\x36\x45\x4D\x18\x35\x3C\x47\x1A\x7B\x65\x7C\x69\x3C\x79", 20).c_str());
    jmethodID toStringMethod = env->GetMethodID(uuidClass, /*toString*/ StrEnc("2~5292eW", "\x46\x11\x66\x46\x4B\x5B\x0B\x30", 8).c_str(), /*()Ljava/lang/String;*/ StrEnc("P$BMc' #j?<:myTh_*h0", "\x78\x0D\x0E\x27\x02\x51\x41\x0C\x06\x5E\x52\x5D\x42\x2A\x20\x1A\x36\x44\x0F\x0B", 20).c_str());

    auto obj = env->CallStaticObjectMethod(uuidClass, nameUUIDFromBytesMethod, myJByteArray);
    auto str = (jstring) env->CallObjectMethod(obj, toStringMethod);
    return env->GetStringUTFChars(str, 0);
}

struct MemoryStruct {
    char *memory;
    size_t size;
};
static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *) userp;

    mem->memory = (char *) realloc(mem->memory, mem->size + realsize + 1);
    if (mem->memory == NULL) {
        return 0;
    }

    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

std::string Login(const char *user_key) {
    if (!g_App)
        return "Internal Error";

    auto activity = g_App->activity;
    if (!activity)
        return "Internal Error";

    auto vm = activity->vm;
    if (!vm)
        return "Internal Error";

    auto object = activity->clazz;
    if (!object)
        return "Internal Error";

    JNIEnv *env;
    vm->AttachCurrentThread(&env, 0);

    std::string hwid = user_key;
    hwid += GetAndroidID(env, object);
    hwid += GetDeviceModel(env);
    hwid += GetDeviceBrand(env);

    std::string UUID = GetDeviceUniqueIdentifier(env, hwid.c_str());

    vm->DetachCurrentThread();

    std::string errMsg;

    struct MemoryStruct chunk{};
    chunk.memory = (char *) malloc(1);
    chunk.size = 0;
//https://bantai.vipbombay.online/connect

//https://bantai.vipbombay.online/
    CURL *curl;
        CURLcode res;
        curl = curl_easy_init();
        if (curl) {
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, /*POST*/ StrEnc(",IL=", "\x7C\x06\x1F\x69", 4).c_str());
        std::string sRedLink = "https://freepanal.000webhostapp.com/connect";

        curl_easy_setopt(curl, CURLOPT_URL, sRedLink.c_str());

        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, /*https*/ StrEnc("!mLBO", "\x49\x19\x38\x32\x3C", 5).c_str());
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, /*Content-Type: application/x-www-form-urlencoded*/ StrEnc("@;Ls\\(KP4Qrop`b#d3094/r1cf<c<=H)AiiBG6i|Ta66s2[", "\x03\x54\x22\x07\x39\x46\x3F\x7D\x60\x28\x02\x0A\x4A\x40\x03\x53\x14\x5F\x59\x5A\x55\x5B\x1B\x5E\x0D\x49\x44\x4E\x4B\x4A\x3F\x04\x27\x06\x1B\x2F\x6A\x43\x1B\x10\x31\x0F\x55\x59\x17\x57\x3F", 47).c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        char data[4096];
        sprintf(data, /*game=PUBG&user_key=%s&serial=%s*/ StrEnc("qu2yXK,YkJyGD@ut0.u~Nb'5(:.:chK", "\x16\x14\x5F\x1C\x65\x1B\x79\x1B\x2C\x6C\x0C\x34\x21\x32\x2A\x1F\x55\x57\x48\x5B\x3D\x44\x54\x50\x5A\x53\x4F\x56\x5E\x4D\x38", 31).c_str(), user_key, UUID.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *) &chunk);

        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        res = curl_easy_perform(curl);
        if (res == CURLE_OK) {
            try {
                json result = json::parse(chunk.memory);
                                                if (result[/*status*/ StrEnc("(>_LBm", "\x5B\x4A\x3E\x38\x37\x1E", 6).c_str()] == true) {
                    rng = result[/*data*/ StrEnc("fAVA", "\x02\x20\x22\x20", 4).c_str()][/*rng*/ StrEnc("+n,", "\x59\x00\x4B", 3).c_str()].get<time_t>();
                      //expiredDate = result[/*data*/ StrEnc("fAVA", "\x02\x20\x22\x20", 4).c_str()][/*ts*/ StrEnc("4`", "\x40\x13", 2).c_str()].get<std::string>();
                    //  modStatus = result[/*data*/ StrEnc("fAVA", "\x02\x20\x22\x20", 4).c_str()][/*ms*/ StrEnc("#e", "\x4E\x16", 2).c_str()].get<std::string>();
                    std::string token = result[/*data*/ StrEnc("fAVA", "\x02\x20\x22\x20", 4).c_str()][/*token*/ StrEnc("{>3Lr", "\x0F\x51\x58\x29\x1C", 5).c_str()].get<std::string>();
                    time_t rng = result[/*data*/ StrEnc("fAVA", "\x02\x20\x22\x20", 4).c_str()][/*rng*/ StrEnc("+n,", "\x59\x00\x4B", 3).c_str()].get<time_t>();                  
                  
                    if (rng + 30 > time(0)) {
                        std::string auth = /*PUBG*/ StrEnc("Q*) ", "\x01\x7F\x6B\x67", 4).c_str();;
                        auth += "-";
                        auth += user_key;
                        auth += "-";
                        auth += UUID;
                        auth += "-";
                        auth += /*Vm8Lk7Uj2JmsjCPVPVjrLa7zgfx3uz9E*/ StrEnc("-2:uwZdV^%]?{{wHs2V,+(^NJU;kC*_{", "\x7B\x5F\x02\x39\x1C\x6D\x31\x3C\x6C\x6F\x30\x4C\x11\x38\x27\x1E\x23\x64\x3C\x5E\x67\x49\x69\x34\x2D\x33\x43\x58\x36\x50\x66\x3E", 32).c_str();
                        std::string outputAuth = Tools::CalcMD5(auth);
     
                        g_Token = token;
                        g_Auth = outputAuth;
				
                        bValid = g_Token == g_Auth;
                    }
                } else {
                    errMsg = result[/*reason*/ StrEnc("LW(3(c", "\x3E\x32\x49\x40\x47\x0D", 6).c_str()].get<std::string>();
                }
            } catch (json::exception &e) {
                errMsg = "{";
                errMsg += e.what();
                errMsg += "}\n{";
                errMsg += chunk.memory;
                errMsg += "}";
            }
        } else {
            errMsg = curl_easy_strerror(res);
        }
    }
    curl_easy_cleanup(curl);

    return bValid ? "OK" : errMsg;
}

	namespace Settings
{
    static int Tab = 1;
}

	EGLBoolean (*orig_eglSwapBuffers)(EGLDisplay dpy, EGLSurface surface);

EGLBoolean _eglSwapBuffers(EGLDisplay dpy, EGLSurface surface) {
    eglQuerySurface(dpy, surface, EGL_WIDTH, &glWidth);
    eglQuerySurface(dpy, surface, EGL_HEIGHT, &glHeight);
    if (glWidth <= 0 || glHeight <= 0)
        return orig_eglSwapBuffers(dpy, surface);

    if (!g_App)
        return orig_eglSwapBuffers(dpy, surface);

    screenWidth = ANativeWindow_getWidth(g_App->window);
    screenHeight = ANativeWindow_getHeight(g_App->window);
    density = AConfiguration_getDensity(g_App->config);

if (!initImGui) {
    ImGui::CreateContext();

    ImGuiStyle* style = &ImGui::GetStyle();
	Config.Bypass = true;

    // В начале программы (например, в инициализации)


    style->Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f); // Белый текст
    style->Colors[ImGuiCol_WindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f); // Чёрный фон окна
    style->Colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f); // Чёрная граница
    style->Colors[ImGuiCol_FrameBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f); // Чёрный фон элементов
    style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f); // Тёмно-серый при наведении
    style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.30f, 0.30f, 0.30f, 1.00f); // Серый при активации
    style->Colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f); // Чёрный заголовок окна
    style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f); // Чёрный заголовок активного окна
    style->Colors[ImGuiCol_Button] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f); // Чёрная кнопка
    style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f); // Тёмно-серый при наведении на кнопку
    style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.30f, 0.30f, 0.30f, 1.00f); // Серый при нажатии на кнопку
    style->Colors[ImGuiCol_Header] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f); // Чёрный заголовок
    style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f); // Тёмно-серый при наведении на заголовок
    style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.30f, 0.30f, 0.30f, 1.00f); // Серый при активации заголовка
// Настройка скругления для слайдеров
style->GrabRounding = 20.0f;
style->FrameRounding = 20.0f;

    style->ScrollbarSize = 6.0f;

	
	
    style->WindowRounding = 5.0f;
    
	
	
	
    // Menü Renkleri
    
    // Border ve üst kısmın renkleri
    
    ImGui_ImplAndroid_Init();
    ImGui_ImplOpenGL3_Init("#version 300 es");


        ImGuiIO &io = ImGui::GetIO();
        //ImGui::StyleColorsDark(style);
        io.ConfigWindowsMoveFromTitleBarOnly = true;
        io.IniFilename = NULL;

        static const ImWchar ranges[] =
{
    0x20, 0xFF,
    0x2010, 0x205E,
    0x0600, 0x06FF,
    0xFE00, 0xFEFF,   
    0,
};  


        

            io.ConfigWindowsMoveFromTitleBarOnly = false;
            io.IniFilename = NULL;


            //==//
            static const ImWchar icons_ranges[] = { 0xf000, 0xf3ff, 0 };
            ImFontConfig icons_config;

            ImFontConfig CustomFont;
            CustomFont.FontDataOwnedByAtlas = false;

            icons_config.MergeMode = true;
            icons_config.PixelSnapH = true;
            icons_config.OversampleH = 2.5;
            icons_config.OversampleV = 2.5;
            
          io.Fonts->AddFontFromMemoryTTF(const_cast<std::uint8_t*>(Custom), sizeof(Custom), 25.f, &CustomFont);
       io.Fonts->AddFontFromMemoryCompressedTTF(font_awesome_data, font_awesome_size, 30.0f, &icons_config, icons_ranges);

            ImFontConfig cfg;
            cfg.SizePixels = ((float) density / 20.0f);
            io.Fonts->AddFontDefault(&cfg);

            memset(&Config, 0, sizeof(sConfig));

// ===============================ESPCOLOR ================================== //

  
        Config.ColorsESP.PVisibile = CREATE_COLOR(28, 252, 3, 255);
        Config.ColorsESP.PNonVis = CREATE_COLOR(252, 3, 3, 255);
        Config.ColorsESP.PVLine = CREATE_COLOR(0, 255, 0, 255);
        Config.ColorsESP.PVILine = CREATE_COLOR(255, 0, 0, 255);
        Config.ColorsESP.BVLine = CREATE_COLOR(255, 255, 255, 255);
        Config.ColorsESP.BVILine = CREATE_COLOR(255, 0, 0, 255);
        Config.ColorsESP.PVBox = CREATE_COLOR(255, 0, 0, 255);
        Config.ColorsESP.PVIBox = CREATE_COLOR(255, 0, 0, 255);
        Config.ColorsESP.BVBox = CREATE_COLOR(255, 0, 0, 255);
        Config.ColorsESP.Box3D = CREATE_COLOR(255, 0, 0, 255);
        Config.ColorsESP.BVIBox = CREATE_COLOR(255, 0, 0, 255);
        Config.ColorsESP.PVSkeleton = CREATE_COLOR(255, 0, 0, 255);
        Config.ColorsESP.PVISkeleton = CREATE_COLOR(255, 0, 0, 255);
        Config.ColorsESP.BVSkeleton = CREATE_COLOR(255, 0, 0, 255);
        Config.ColorsESP.BVISkeleton = CREATE_COLOR(255, 0, 0, 255);
		Config.ColorsESP.Name = CREATE_COLOR(0, 0, 0, 200);
        Config.ColorsESP.Name = CREATE_COLOR(255, 255, 255, 255);
        Config.ColorsESP.RGB = CREATE_COLOR(255, 255, 255, 255);
		Config.ColorsESP.TeamID = CREATE_COLOR(0, 255, 0, 255);
        Config.ColorsESP.TeamID = CREATE_COLOR(255, 255, 255, 255);
		Config.ColorsESP.Fov = CREATE_COLOR(255, 255, 255, 255);
	    Config.ColorsESP.Text = CREATE_COLOR(255, 255, 255, 255);
	    Config.ColorsESP.Count = CREATE_COLOR(0, 255, 0, 255);
	    Config.ColorsESP.WeaponId = CREATE_COLOR(0, 255, 0, 255);
        Config.ColorsESP.Distance = CREATE_COLOR(255, 255, 255, 255);
        Config.ColorsESP.Vehicle = CREATE_COLOR(255, 0, 0, 255);
        Config.ColorsESP.Items = CREATE_COLOR(0, 255, 0, 255);   
		//Config.AimBot.Cross = 60.0f;
		//Config.SilentAim.Cross = 200.0f;
   //     FOVSizea = 180.0f;
   
   for (auto &i : items_data) {
            for (auto &item : i["Items"]) {
                int r, g, b;
                sscanf(item["itemTextColor"].get<std::string>().c_str(), "#%02X%02X%02X", &r, &g, &b);
              
            }
        }
        initImGui = true;
    }

    ImGuiIO &io = ImGui::GetIO();
 //MADE BY HOST OP
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplAndroid_NewFrame(glWidth, glHeight);
    ImGui::NewFrame();

    DrawESP(ImGui::GetBackgroundDrawList());
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //



    ImGui::SetNextWindowSize(ImVec2((float) glWidth * 0.45f, (float) glHeight * 0.65f), ImGuiCond_Once);
  
static bool menuOpen = false; // Переменная для отслеживания состояния меню
static bool 音量键 = false; 

for (int i = 0; i < IM_ARRAYSIZE(io.KeysDown); i++) {
    if (ImGui::IsKeyDown(i)) {
        if (!音量键) { // Если кнопка была отпущена, обрабатываем нажатие
            音量键 = true;       // Помечаем, что кнопка нажата
            menuOpen = !menuOpen; // Переключаем состояние меню
        }
    } else {
        音量键 = false; // Сбрасываем состояние кнопки, если она отпущена
    }
}




	
	
	/*if(menuOpen){
	ImGui::SetNextWindowSize(ImVec2((float)glWidth * 0.35f, (float)glHeight * 0.53f), ImGuiCond_Once);

    static bool p_open = true;
    ImGui::PushFont(Arabic);
    if (ImGui::Begin(OBFUSCATE("ElytraX "), &p_open, ImGuiWindowFlags_NoSavedSettings)) {
        static bool isLogin = true;

        if (!isLogin) {
            ImGui::Text("Please Login! (Copy Key to @FTSMOD)");

            ImGui::PushItemWidth(-1);
            static char s[64];
            ImGui::InputText("##key", s, sizeof s);
            ImGui::PopItemWidth();

            if (ImGui::Button("  Paste Your Key  ", ImVec2(ImGui::GetContentRegionAvailWidth(), 0))) {
                auto key = getClipboardText();
                strncpy(s, key.c_str(), sizeof s);
            }

            static std::string err;
            if (ImGui::Button("Login", ImVec2(ImGui::GetContentRegionAvailWidth(), 0))) {
                err = Login(s);
                if (err == "OK") {
                    isLogin = bValid && g_Auth == g_Token;
                }
            }

            if (!err.empty() && err != "OK") {
                ImGui::Text("Error: %s", err.c_str());
            }
        } else {
			
            // ESP MENÜ
            ImGui::PushFont(Arabic);
            if (ImGui::BeginTabBar("", ImGuiTabBarFlags_FittingPolicyScroll)) {
                if (ImGui::BeginTabItem(u8"ESP MENU")) {
                    // Tablo başlat
                    if (ImGui::BeginTable("split", 2, ImGuiTableFlags_SizingStretchSame)) {
                        ImGui::PushFont(Arabic);

                        // Menü genişliği ve yüksekliği
                        ImVec2 windowSize = ImGui::GetContentRegionAvail();
                        float buttonWidth = windowSize.x / 2.2f; // Buton genişliği
                        float buttonHeight = 40.0f; // Sabit buton yüksekliği
                        float spacing = 5.0f; // Butonlar arası boşluk

                        ImGui::Spacing();
						

                        // ESP Butonları düzenli yerleştirme
                        ImGui::TableNextColumn();
						ImGui::RadioButton("BYPASS ACTIVATED",&Config.Bypass);      
                        ImGui::Checkbox(u8"Esp", &Config.PlayerESP.Line);

                        ImGui::TableNextColumn();
                        ImGui::Checkbox(u8"Enable All Esp", &Feu);

                        ImGui::TableNextColumn();
                        ImGui::Checkbox(u8"ESP Alert", &Config.PlayerESP.Alert);

                        ImGui::TableNextColumn();
                        ImGui::Checkbox(u8"ESP Vehicle", &Config.PlayerESP.Vehicle);

                        ImGui::TableNextColumn();
                        ImGui::Checkbox(u8"ESP Box3D", &Config.PlayerESP.Box3D);

                        ImGui::TableNextColumn();
                        ImGui::Checkbox(u8"ESP Bone", &Config.PlayerESP.Skeleton);

                        ImGui::TableNextColumn();
                        ImGui::Checkbox(u8"ESP Line", &Config.PlayerESP.LineTop);

                        ImGui::TableNextColumn();
                        ImGui::Checkbox(u8"ESP V-Fuel", &Config.PlayerESP.VehicleFuel);

                        ImGui::TableNextColumn();
                        ImGui::Checkbox(u8"ESP V-Hp", &Config.PlayerESP.VehicleHP);

                        ImGui::TableNextColumn();
                        ImGui::Checkbox(u8"Granade Alert", &Config.PlayerESP.Grenade);

                        ImGui::TableNextColumn();
                        ImGui::Checkbox(u8"ESP LootBox", &Config.PlayerESP.LootBox);
						ImGui::TableNextColumn();
                        ImGui::Checkbox(u8"Ipad View ", &Config.IPadView);
						
						ImGui::TableNextColumn();
                        ImGui::Checkbox(u8"90 fps", &Config.FightFps);

                        
                        ImGui::EndTable();
                        ImGui::PopFont();
             
             
                    }
                    ImGui::EndTabItem();
                }
			   } 
			   ImGui::PushFont(Arabic);
           if (ImGui::BeginTabItem(u8" AIMBOT  ")) {
                    ImGui::Spacing();
                    if (ImGui::BeginTable("split", 1)) {
			            
			            
			            ImGui::Separator();  
                        ImGui::TableNextColumn();
                     //   ImGui::PushFont(Arabic);
                        
                        ImGui::Spacing();
			
                    ImGui::TableNextColumn();
                    ImGui::Separator();  
			            ImGui::Text(u8"(%.1f Fps Level)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			            ImGui::Separator(); 
			            ImGui::TableNextColumn();
			            ImGui::Spacing();
                     //   ImGui::Checkbox((u8"Silent Aim Enable"), &Config.SilentAim.Enable);
                        ImGui::Checkbox((u8"Aimbot 150M"), &Config.AimBot.Enable);
                        ImGui::Checkbox((u8"BT 370°"), &Config.SilentAim.Enable);
                        
		             	static int slider_test_0 = 50;
						ImGui::SliderFloat("FOV Size", &Config.AimBot.Cross, 0.0f, 400.0f);
						ImGui::SliderFloat("Anti-Recoil", &Config.Recc, 0.0f, 2.0f);
				 	//	ImGui::SliderFloat("Meter", &Config.Meter, 6.2f, 0.0f, 150.0f, "%.0f");
						
	         	static const char *triggers[] = {"Always", "Shooting"};
	     		ImGui::Combo("Trigger", (int *) &Config.AimBot.Trigger, triggers, 2, -1);

                    //    ImGui::Checkbox("Prediction ", &Config.AimBot.Predection);		
						
                        ImGui::Checkbox("Visibility Check", &Config.AimBot.VisCheck);
				        ImGui::Checkbox("Ignore Knock", &Config.AimBot.IgnoreKnocked);			
						
                        ImGui::Checkbox("Ignore Bot", &Config.AimBot.IgnoreBot);
						
				
	
			            ImGui::EndTable();
			            ImGui::PopFont();
                        
                    }
                    ImGui::EndTabItem();
            
					 

                
		 }
       } 
      } 
   

ImGui::End();
    ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    
}
*/
/*

// Перед отрисовкой интерфейса
if (menuOpen) {
    ImGui::GetBackgroundDrawList()->AddRectFilledMultiColor(
        ImVec2(0, 0), 
        ImVec2(glWidth, glHeight),
        IM_COL32(10, 10, 10, 180),
        IM_COL32(25, 25, 25, 180),
        IM_COL32(25, 25, 25, 180),
        IM_COL32(10, 10, 10, 180)
    );
}
if (menuOpen) {
    // Стили для блюр эффекта
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.08f, 0.08f, 0.08f, 0.92f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 15.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 8.0f);

    if (ImGui::Begin("Main Menu", nullptr, 
        ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoScrollWithMouse))
    {
        // Разделение на 2 колонки
        ImGui::Columns(2, "MainColumns", false);
        ImGui::SetColumnWidth(0, glWidth * 0.15f); // Ширина боковой панели

        // Секция 1 - Боковые кнопки (блюр)
        {
            ImGui::BeginChild("##LeftPanel", ImVec2(0, 0), true);
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.3f, 0.3f, 0.3f, 0.6f));
            
            if (ImGui::Button(ICON_FA_EYE " ESP", ImVec2(-FLT_MIN, 50))) 
                Settings::Tab = 1;
            
            if (ImGui::Button(ICON_FA_CROSSHAIRS " AIM", ImVec2(-FLT_MIN, 50))) 
                Settings::Tab = 2;
            
            if (ImGui::Button(ICON_FA_MAGIC " MISC", ImVec2(-FLT_MIN, 50))) 
                Settings::Tab = 3;
            
            ImGui::PopStyleColor();
            ImGui::EndChild();
        }

        ImGui::NextColumn();

        // Секция 2 - Чёрное меню
        {
            ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
            ImGui::BeginChild("##RightPanel", ImVec2(0, 0), true, ImGuiWindowFlags_AlwaysUseWindowPadding);
            
            // Контент для разных вкладок
            switch (Settings::Tab) {
                case 1:
                    ImGui::Checkbox("Player ESP", &Config.PlayerESP.Line);
                    ImGui::Checkbox("Item ESP", &Config.PlayerESP.Line);
                    break;
                    
                case 2:
                   // ImGui::SliderFloat("FOV", &Config.AimFOV, 1.0f, 360.0f);
                    ImGui::Checkbox("Aim Assist", &Config.PlayerESP.Line);
                    break;
                    
                case 3:
                    ImGui::Checkbox("Bypass", &Config.Bypass);
                    ImGui::Checkbox("Auto Update", &Config.PlayerESP.Box);
                    break;
            }
            
            ImGui::EndChild();
            ImGui::PopStyleColor();
        }

        ImGui::Columns(1);
        ImGui::End();
    }
    
    // Восстановление стилей
    ImGui::PopStyleColor();
    ImGui::PopStyleVar(2);
} 
*/










// Глобальные переменные
static float menuOpenTime = 0.0f;
static bool titleAnimFinished = false;
static ImVec4 titleColor = ImVec4(1.0f, 1.0f, 1.0f, 0.0f);
int currentTab = 1;


    if (menuOpen) {
        const float glWidth = ImGui::GetIO().DisplaySize.x;
        const float glHeight = ImGui::GetIO().DisplaySize.y;
        float timeSinceOpen = ImGui::GetTime() - menuOpenTime;

        // Анимация заголовка
        if (Config.EnableAnimations && timeSinceOpen < 2.0f) {
            const char* text = "ElytraX";
            ImVec2 textSize = ImGui::CalcTextSize(text);
            
            // Расчет позиции текста
            float textX = glWidth * 0.5f - textSize.x * 0.5f;
            float textY = glHeight * 0.4f - textSize.y * 0.5f;

            // Анимация прозрачности
            titleColor.w = ImClamp(timeSinceOpen * 2.0f, 0.0f, 1.0f);

            // Анимация цвета
            if (timeSinceOpen > 1.5f) {
                float redProgress = (timeSinceOpen - 1.5f) / 0.5f;
                titleColor.x = 1.0f - redProgress * 0.6f;
                titleColor.y = 1.0f - redProgress;
                titleColor.z = 1.0f - redProgress;
            }

            ImGui::GetBackgroundDrawList()->AddText(
                ImVec2(textX, textY), 
                ImColor(titleColor), 
                text
            );
        }
        else {
            titleAnimFinished = true;
        }

        // Основное меню
        if (!Config.EnableAnimations || titleAnimFinished) {
            // Фон
            float bgAlpha = Config.EnableAnimations ? 
                ImClamp((timeSinceOpen - 2.0f) * 2.0f, 0.0f, 0.92f) : 0.92f;

            // Расчет цветов фона
            ImU32 col1 = IM_COL32(10, 10, 10, (int)(180 * bgAlpha));
            ImU32 col2 = IM_COL32(25, 25, 25, (int)(180 * bgAlpha));
            
            ImGui::GetBackgroundDrawList()->AddRectFilledMultiColor(
                ImVec2(0, 0), 
                ImVec2(glWidth, glHeight),
                col1, col2, col2, col1
            );

            // Анимация движения
            float animProgress = Config.EnableAnimations ? 
                ImClamp((timeSinceOpen - 2.0f) / Config.AnimDuration, 0.0f, 1.0f) : 1.0f;
            
            float easedProgress = animProgress < 0.5f ? 
                2.0f * animProgress * animProgress : 
                1.0f - pow(-2.0f * animProgress + 2.0f, 2.0f) / 2.0f;

            // Стили окна
            ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.08f, 0.08f, 0.08f, 0.92f * bgAlpha));
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 15.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 8.0f);

            // Позиция окна
            float windowWidth = glWidth * 0.4f;
            float windowHeight = glHeight * 0.7f;
            float windowX = glWidth * 0.5f - windowWidth * 0.5f;
            float windowY = Config.EnableAnimations 
                ? -windowHeight + easedProgress * (windowHeight + glHeight * 0.1f)
                : glHeight * 0.1f;

            ImGui::SetNextWindowPos(ImVec2(windowX, windowY), ImGuiCond_Always);
            ImGui::SetNextWindowSize(ImVec2(windowWidth, windowHeight));

            if (ImGui::Begin("Main Menu", nullptr, 
                ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoScrollWithMouse |
                ImGuiWindowFlags_NoBringToFrontOnFocus))
            {
                // Боковая панель
                ImGui::Columns(2, "MainColumns", false);
                ImGui::SetColumnWidth(0, windowWidth * 0.375f);

                // Левая колонка
                if (ImGui::BeginChild("##LeftPanel", ImVec2(0, 0), true)) {
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.3f, 0.3f, 0.3f, 0.6f));
                    
                    float buttonHeight = 50.0f;
                    ImVec2 buttonSize = ImVec2(-FLT_MIN, buttonHeight);

                    if (ImGui::Button("ESP", buttonSize)) currentTab = 1;
                    if (ImGui::Button("AIM", buttonSize)) currentTab = 2;
                    if (ImGui::Button("MISC", buttonSize)) currentTab = 3;

                    ImGui::PopStyleColor();
                }
                ImGui::EndChild();

                ImGui::NextColumn();

                // Правая колонка
                if (ImGui::BeginChild("##RightPanel", ImVec2(0, 0), true)) {
                    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
                    
                    switch (currentTab) {
                        case 1:
                            ImGui::Checkbox("Player ESP", &Config.ESP);
                            ImGui::Checkbox("Item ESP", &Config.ESP);
                            break;
                            
                        case 2:
                       //     ImGui::SliderFloat("FOV", &Config.AimFOV, 1.0f, 360.0f, "%.0f");
                            ImGui::Checkbox("Aim Assist", &Config.ESP);
                            break;
                            
                        case 3:
                            ImGui::Checkbox("Bypass", &Config.Bypass);
                            ImGui::Checkbox("Auto Update", &Config.ESP);
                            ImGui::Separator();
                            ImGui::Checkbox("Enable Animations", &Config.ESP);
                           // ImGui::SliderFloat("Duration", &Config.AnimDuration, 0.5f, 3.0f, "%.1f s");
                            break;
                    }

                    ImGui::PopStyleColor();
                }
                ImGui::EndChild();

                ImGui::Columns(1);
            }
            ImGui::End();

            // Восстановление стилей
            ImGui::PopStyleColor();
            ImGui::PopStyleVar(2);
        }
    }
    else {
        // Сброс анимации при закрытии
        menuOpenTime = 0.0f;
        titleAnimFinished = false;
        titleColor = ImVec4(1.0f, 1.0f, 1.0f, 0.0f);
    }


// Пример использования в основном цикле

    
    // Рендер меню
    if (menuOpen) {
        if (menuOpenTime == 0.0f) menuOpenTime = ImGui::GetTime();
 
    }
    

    


    // Финальный рендеринг
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    


    //ImGui::End();
    //ImGui::Render();
  //      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());




// ================================================================================================================================ //
        return orig_eglSwapBuffers(dpy, surface);
        }

    int32_t (*orig_onInputEvent)(struct android_app *app, AInputEvent *inputEvent);

    int32_t onInputEvent(struct android_app *app, AInputEvent *inputEvent) {
        if (initImGui) {
            ImGui_ImplAndroid_HandleInputEvent(inputEvent, {(float) screenWidth / (float) glWidth, (float) screenHeight / (float) glHeight});
        }
        return orig_onInputEvent(app, inputEvent);
    }



#define SLEEP_TIME 1000LL / 60LL
[[noreturn]] void *maps_thread(void *) {
    while (true) {
        auto t1 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

        std::vector<sRegion> tmp;
        char line[512];
        FILE *f = fopen("/proc/self/maps", "r");
        if (f) {
            while (fgets(line, sizeof line, f)) {
                uintptr_t start, end;
                char tmpProt[16];
                if (sscanf(line, "%" PRIXPTR "-%" PRIXPTR " %16s %*s %*s %*s %*s", &start, &end, tmpProt) > 0) {
                    if (tmpProt[0] != 'r') {
                        tmp.push_back({start, end});
                    }
                }
            }
            fclose(f);
        }

        auto td = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - t1;
        std::this_thread::sleep_for(std::chrono::milliseconds(std::max(std::min(0LL, SLEEP_TIME - td), SLEEP_TIME)));
    }
}
void *main_thread(void *) {
       
        UE4 = Tools::GetBaseAddress("libUE4.so");
        while (!UE4){
        UE4 = Tools::GetBaseAddress("libUE4.so");
        sleep(1);}
        anort = Tools::GetBaseAddress("libanort.so");
        while (!anort){
        anort = Tools::GetBaseAddress("libanort.so");
        sleep(1);}
        anogs = Tools::GetBaseAddress("libanogs.so");
        while (!anogs){
        anogs = Tools::GetBaseAddress("libanogs.so");
        sleep(1);}
        CrashSight = Tools::GetBaseAddress("libCrashSight.so");
        while (!CrashSight){
        CrashSight = Tools::GetBaseAddress("libCrashSight.so");
        sleep(1);}
        while (!g_App){
        g_App = *(android_app **) (UE4 + GNativeAndroidApp_Offset);
        sleep(1);}
        while (!g_App->onInputEvent)
        sleep(1);
        orig_onInputEvent = decltype(orig_onInputEvent)(g_App->onInputEvent);
        g_App->onInputEvent = onInputEvent;
		
int (*sub_60A34)(int a1, unsigned char *a2, size_t a3);
	 
        FName::GNames = GetGNames();
        while (!FName::GNames) {
            FName::GNames = GetGNames();
            sleep(1);
        }
        UObject::GUObjectArray = (FUObjectArray *) (UE4 + GUObject_Offset);

        void *egl = dlopen_ex("libEGL.so", 4);
        while (!egl) {
            egl = dlopen_ex("libEGL.so", 4);
            sleep(1);
        }
        
        void *addr = dlsym_ex(egl, "eglSwapBuffers");
        HOOK(addr, _eglSwapBuffers, &orig_eglSwapBuffers);
        dlclose_ex(egl);
        Tools::Hook((void *) DobbySymbolResolver(OBFUSCATE("/system/lib/libEGL.so"), OBFUSCATE("eglSwapBuffers")), (void *) _eglSwapBuffers, (void **) &orig_eglSwapBuffers);

        pthread_t t;
        pthread_create(&t, 0, maps_thread, 0);
        items_data = json::parse(JSON_ITEMS);
        return 0;
    }

    __attribute__((constructor)) void _init() {
        pthread_t t;
        pthread_create(&t, 0, main_thread, 0);
    }
