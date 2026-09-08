#define targetLibName OBFUSCATE("libUE4.so")
#define targetLibName OBFUSCATE("libanogs.so")
#define targetLibName OBFUSCATE("libanort.so")
#define targetLibName OBFUSCATE("libhdmpve.so")
#define targetLibName OBFUSCATE("libTDataMaster.so")
#define targetLibName ("libRoosterNN.so")
#define targetLibName ("libhdmpve.so")
#define targetLibName ("libCrashKit.so")
#define targetLibName ("libITOP.so")
#define targetLibName ("libAntsVoice.so")
DWORD roosterBase = 0;
DWORD libUE4Base = 0;
DWORD libanogsBase = 0;
DWORD libTBlueDataBase = 0;
DWORD chut = 0;
DWORD libanortBase = 0;
DWORD libanogsAlloc = 0;
DWORD libUE4Alloc = 0;
char *Offset;
DWORD NewBase = 0;
#define BYTE1
#define BYTE5
#define BYTE4
#define BYTE3
#define BYTE2
#define BYTE6
#define BYTE2
#define HIBYTE
#define _BYTE  uint8_t
#define _WORD  uint16_t
#define _DWORD uint32_t
#define _QWORD uint64_t
#define _OWORD uint64_t
#define j_j__free
#define __OFSUB__
uintptr_t ANOGS;
#define AnoSDKIoctlOld_0
#define pkgName "com.pubg.imobile"
#pragma pack(1)
struct patch_t
{
    _BYTE nPatchType;
    DWORD dwAddress;
};

unsigned int libanogsSize  = 0;
unsigned int libUE4Size  = 0;

#define DefineHook(RET, NAME, ARGS) \
    RET(*Orig_##NAME)               \
    ARGS;                           \
    RET Hook_##NAME ARGS
    
uintptr_t get_module_base(pid_t pid, const char* module_name) {
    char filename[32], line[512];
    uintptr_t addr = 0;
    snprintf(filename, sizeof(filename), "/proc/%d/maps", pid);
    FILE* fp = fopen(filename, "r");

    if (fp) {
        while (fgets(line, sizeof(line), fp)) {
            if (strstr(line, module_name)) {
                sscanf(line, "%lx-%*lx", &addr);
                break;
            }
        }
        fclose(fp);
    }
    return addr;
}



size_t StrlenSkinsByRik(char *s)
{
	static const std::unordered_map<std::string, std::string> replacements = 
	{
        {"403006", "1405870"},
        {"1405385", "1407625"}, // Sandsylph
        {"1405269", "1407625"}, // Winter Highness Set
        {"404151", "1407625"},  // BAPE Sta Mid
        {"1405884", "1406327"}, // BAPE Sta Mid
        {"1405113", "1407387"}, // The Reaper's End Set
        {"1405548", "1407366"}, // Wind Spirit Jia'er
        {"403003", "1405628"},  // Devious Cybercat Set
        {"403020", "1405628"},  // Golden Pharaoh Divine Set
        {"403032", "1407470"},  // Carefree Exiled Immortal
        {"403224", "1406891"},  // Soul-Eater Underworld King
        {"403160", "1406386"},  // Zero Combat Suit
        {"403002", "1407387"},  // Phantom Night Shinigami Set
        {"403198", "1400687"},  // Halloween Mummy
        {"403124", "1406387"},  // Asuka
        {"1404008", "1405623"}, // Underworld Traveler Set
        {"403193", "1407103"},  // Dawn Flora Divine Set
        {"403192", "1407219"},  // Holy Flame Igni Divine Set
        {"403153", "1407453"},  // Arabian Traveler
        {"1400043", "1405163"}, // Ruins Hunter
        {"403162", "1407277"},  // Flame Ancient God
        {"404056", "1404191"},  // Trendy Walker Pants
        {"403177", "1407079"},  // Blissful Fool
        {"1400100", "1400782"}, // Ice Crystal Core
        {"403195", "1400569"},  // BAPE MIX CAMO HOODIE
        {"403163", "1404049"},  // BAPE X PUBGM Camouflage Shark Jacket
        {"404001", "1404050"},  // BAPE X PUBGM Camouflage Pants
        {"404049", "1404002"},  // BAPE City Camo Pants
        {"404026", "1400650"},  // BAPE MIX CAMO SHORTS
        {"405053", "1404051"},  // BAPE X PUBGM Camouflage Shoes
        {"405022", "1404003"},  // BAPE Sta Mid
        {"402046", "474031"},   // BAPE Sta Mid

        // Assault Rifles
        {"10100100", "1101001265"}, // AKM
        {"10100300", "1101003195"}, // SCAR-L
        {"10100400", "1101004046"}, // M416 Glacier
        {"10100600", "1101006075"}, // AUG
        {"10501000", "1105010019"}, // MG3
        {"10300700", "1103007028"}, // MK14
        {"10100500", "1101005098"}, // Groza
        {"10100800", "1101008104"}, // M762
        {"10110200", "1101102017"}, // ACE32
        {"10110000", "1101100012"}, // FAMAS

        // Submachine Guns
        {"10200100", "1102001120"}, // UZI
        {"10210500", "1102105012"}, // P90
        {"10200200", "1102002136"}, // UMP45
        {"10200300", "1102003080"}, // Vector

        // Backpacks
        {"501001", "1501001174"},  // Backpack (Lv. 1)
        {"501002", "1501002174"},  // Backpack (Lv. 2)
        {"501003", "1501003174"},  // Backpack (Lv. 3)
		
		//Helmet
		{"502101", "0"},  // Helmet (Lv. 1)
        {"502102", "0"},  // Helmet (Lv. 2)
        {"502103", "0"},  // Helmet (Lv. 3)
		
        // Vehicles
        {"1961001", "1903193"},    // Coupe RB
        {"1953001", "1953008"},    // Monster Truck
        {"1908001", "1908094"},    // UAZ
        {"1903001", "1903075"},    // Dacia
        {"1903002", "1903075"},    // Dacia (Orange)
        {"1903003", "1903075"},    // Dacia (White)
        {"1915004", "1915008"},    // Mirado
        {"1916001", "1916006"},    // Rony
        {"1532907", "1901089"},    // Motorcycle

        // Buggies
        {"1907001", "1907059"},
        {"1907002", "1907059"},
        {"1907003", "1907059"},
        {"1907004", "1907059"},
        {"1907005", "1907059"},
        {"1907006", "1907059"},
        {"2001001","2002942"}, // Frame  C6S18 Conqueror 
        {"202408052", "202408061"} // Auto Showroom  Lobby Theme 
    };
    auto it = replacements.find(s);
    if (it != replacements.end()) 
	{
        strcpy(s, it->second.c_str()); // Make sure 's' has enough space
        return strlen(s);
    }
    return strlen(s); // If no replacement, return original length
}


	
void *AntiSemx(void *)
{
    LOGI("SankeXd");
    do 
    { 
        sleep(1); 
    } 
    while (!isLibraryLoaded(targetLibName));

HOOK_LIB_NO_ORIG("libUE4.so","0xC23FA50", StrlenSkinsByRik);
return NULL;
}


__attribute__((constructor))
void lib_main() 
{
    pthread_t ptid;
    pthread_create(&ptid, NULL, AntiSemx, NULL);
}
