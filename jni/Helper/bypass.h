#define targetLibName OBFUSCATE("libUE4.so")
#define targetLibName OBFUSCATE("libanogs.so")
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

	
void *AntiSemx(void *)
{
    LOGI("Everything ok bp done");
    do 
    { 
        sleep(1); 
    } 
    while (!isLibraryLoaded(targetLibName));
    /*
 PATCH_LIB("libanogs.so", "0x228560", "00 00 80 D2 C0 03 5F D6");
 PATCH_LIB("libanogs.so", "0x2ECE70", "00 00 80 D2 C0 03 5F D6");
 PATCH_LIB("libanogs.so", "0x213000", "00 00 80 D2 C0 03 5F D6");
 */
return NULL;
}


__attribute__((constructor))
void lib_main() 
{
    pthread_t ptid;
    pthread_create(&ptid, NULL, AntiSemx, NULL);
}
