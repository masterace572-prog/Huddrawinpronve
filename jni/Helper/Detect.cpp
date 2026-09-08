#include <string>
#include <vector>
#include <unistd.h>
#include <android/log.h>
#include <sys/system_properties.h>
#include <dirent.h>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "oxorany.h"

bool IsPackageInstalled(const char* packageName) {
    std::string cmd = oxorany("pm list packages | grep ");
    cmd += packageName;
    FILE* pipe = popen(cmd.c_str(), oxorany("r"));
    if (!pipe) return false;

    char buffer[128];
    std::string result = "";
    while (fgets(buffer, sizeof buffer, pipe) != NULL) {
        result += buffer;
    }
    pclose(pipe);
    return !result.empty();
}

bool IsRooted() {
    const char* paths[] = {
        oxorany("/system/app/Superuser.apk"),
        oxorany("/sbin/su"),
        oxorany("/system/bin/su"),
        oxorany("/system/xbin/su"),
        oxorany("/data/local/xbin/su"),
        oxorany("/data/local/bin/su"),
        oxorany("/system/sd/xbin/su"),
        oxorany("/system/bin/failsafe/su"),
        oxorany("/data/local/su"),
        oxorany("/su/bin/su")
    };
    for (const auto& path : paths) {
        if (access(path, F_OK) == 0)
            return true;
    }
    return false;
}

void RootAndToolCheck() 
{
    uintptr_t CMessageBoxExt_address = Cheat::libUE4Base + 0x79cdcec;
    auto CMessageBoxExt = reinterpret_cast<int(*)(int, const char16_t*, const char16_t*)>(CMessageBoxExt_address);

    std::vector<std::string> dangerousTools = {
        oxorany("com.topjohnwu.magisk"),
        oxorany("com.noshufou.android.su"),
        oxorany("eu.chainfire.supersu"),
        oxorany("com.koushikdutta.rommanager"),
        oxorany("com.dimonvideo.luckypatcher"),
        oxorany("com.chelpus.lackypatch"),
        oxorany("com.termux"),
        oxorany("org.kali.nethunter"),
        oxorany("com.guoshi.httpcanary"),
        oxorany("catch_.me_.if_.you_.can_"),
        oxorany("com.frida.server"),
        oxorany("re.frida.server"),
        oxorany("org.mozilla.fenix"),
        oxorany("com.jakting.rns"),
        oxorany("com.ghidra"),
        oxorany("com.jadx"),
        oxorany("com.bin.mt"),
        oxorany("com.mt.helper")
    };

    std::string detectedTool = "";

    for (const auto& pkg : dangerousTools) {
        if (IsPackageInstalled(pkg.c_str())) {
            detectedTool = pkg;
            break;
        }
    }

    if (IsRooted()) {
        detectedTool = oxorany("ROOT ACCESS");
    }

    if (!detectedTool.empty()) {
        std::u16string msg = u"RAT INJECTING BECAUSE YOU TRYING TO CRACK OR DUMP\nTool: ";
        msg += std::u16string(detectedTool.begin(), detectedTool.end());
        msg += u"\nPehle delete kar warna teri details leak";

        CMessageBoxExt(0, msg.c_str(), oxorany(u"warning !! mat panga le"));
        *(int*)0 = 0;
    }
}

std::vector<std::string> SuspiciousProcessNames = {
    oxorany("frida-server"), oxorany("frida"), oxorany("gg"), oxorany("gameguardian"),
    oxorany("termux"), oxorany("canary"), oxorany("httpcanary"), oxorany("su"), oxorany("magisk"), oxorany("sqlite"), oxorany("tcpdump")
};

bool IsProcessSuspicious() {
    DIR* proc = opendir(oxorany("/proc"));
    if (!proc) return false;

    struct dirent* ent;
    while ((ent = readdir(proc)) != NULL) {
        if (ent->d_type == DT_DIR) {
            std::string pid = ent->d_name;
            if (!std::all_of(pid.begin(), pid.end(), ::isdigit))
                continue;

            std::string cmdlinePath = oxorany("/proc/") + pid + oxorany("/cmdline");
            std::ifstream cmdFile(cmdlinePath);
            std::string line;
            if (std::getline(cmdFile, line)) {
                for (const auto& name : SuspiciousProcessNames) {
                    if (line.find(name) != std::string::npos) {
                        closedir(proc);
                        return true;
                    }
                }
            }
        }
    }
    closedir(proc);
    return false;
}

bool HasToolBinary() {
    std::vector<std::string> toolPaths = {
        oxorany("/data/local/tmp/frida-server"),
        oxorany("/data/data/com.termux/"),
        oxorany("/storage/emulated/0/Download/gg"),
        oxorany("/data/local/tmp/gg"),
        oxorany("/data/local/tmp/magisk"),
        oxorany("/system/bin/frida-server"),
        oxorany("/system/xbin/su"),
        oxorany("/data/local/tmp/su"),
    };

    for (const auto& path : toolPaths) {
        if (access(path.c_str(), F_OK) == 0)
            return true;
    }
    return false;
}

void ToolScanAndCrash() {
    uintptr_t CMessageBoxExt_address = Cheat::libUE4Base + 0x79cdcec;
    auto CMessageBoxExt = reinterpret_cast<int(*)(int, const char16_t*, const char16_t*)>(CMessageBoxExt_address);

    if (IsProcessSuspicious() || HasToolBinary()) {
        CMessageBoxExt(0, oxorany(u" RAT INJECTING IN YOUR DEVICE BECAUSE TRY TO CRACK OR DUMP!"), oxorany(u"RAT INJECTING IN YOUR DEVICE BECAUSE TRY TO CRACK OR DUMP"));
        *(int*)0 = 0;
    }
}

__attribute__((constructor))
void OnLoad() {
    RootAndToolCheck();
    ToolScanAndCrash();
}