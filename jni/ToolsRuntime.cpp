#include "Tools.h"
#include "shadowhook/shadowhook.h"

#include <cerrno>
#include <cinttypes>
#include <cstdio>
#include <cstring>
#include <libgen.h>
#include <sys/mman.h>
#include <unistd.h>

namespace
{
uintptr_t PageStart(const void *address)
{
    const uintptr_t pageSize = static_cast<uintptr_t>(sysconf(_SC_PAGESIZE));
    return reinterpret_cast<uintptr_t>(address) & ~(pageSize - 1u);
}

bool MakeWritable(void *address, size_t length)
{
    if (!address || !length)
        return false;

    const uintptr_t pageSize = static_cast<uintptr_t>(sysconf(_SC_PAGESIZE));
    if (!pageSize)
        return false;

    const uintptr_t start = PageStart(address);
    const uintptr_t lastByte = reinterpret_cast<uintptr_t>(address) + length - 1u;
    const uintptr_t end = (lastByte & ~(pageSize - 1u)) + pageSize;
    return mprotect(reinterpret_cast<void *>(start), end - start,
                    PROT_READ | PROT_WRITE | PROT_EXEC) == 0;
}

bool IsMappedAddress(const void *address)
{
    if (!address)
        return false;

    FILE *maps = fopen("/proc/self/maps", "r");
    if (!maps)
        return false;

    const uintptr_t probe = reinterpret_cast<uintptr_t>(address);
    uintptr_t start = 0;
    uintptr_t end = 0;
    char permissions[5]{};
    char line[512]{};
    bool mapped = false;
    while (fgets(line, sizeof(line), maps))
    {
        if (sscanf(line, "%" SCNxPTR "-%" SCNxPTR " %4s", &start, &end,
                   permissions) == 3 && probe >= start && probe < end)
        {
            mapped = true;
            break;
        }
    }

    fclose(maps);
    return mapped;
}
} // namespace

namespace Tools
{
// Legacy callers are routed to ShadowHook as well. Hook installation is
// initialized by the bootstrap before any game hooks are registered.
void Hook(void *target, void *replace, void **backup)
{
    if (!target || !replace || !backup)
        return;
    shadowhook_hook_func_addr(target, replace, backup);
}

bool Read(void *addr, void *buffer, size_t length)
{
    if (!addr || !buffer || !length || !IsMappedAddress(addr))
        return false;
    memcpy(buffer, addr, length);
    return true;
}

bool Write(void *addr, void *buffer, size_t length)
{
    if (!addr || !buffer || !length)
        return false;
    memcpy(addr, buffer, length);
    return true;
}

bool ReadAddr(void *addr, void *buffer, size_t length)
{
    return Read(addr, buffer, length);
}

bool WriteAddr(void *addr, void *buffer, size_t length)
{
    if (!MakeWritable(addr, length))
        return false;
    memcpy(addr, buffer, length);
    return true;
}

bool SetWriteable(void *addr)
{
    return MakeWritable(addr, 1u);
}

bool PVM_ReadAddr(void *addr, void *buffer, size_t length)
{
    return Read(addr, buffer, length);
}

bool PVM_WriteAddr(void *addr, void *buffer, size_t length)
{
    return WriteAddr(addr, buffer, length);
}

bool IsPtrValid(void *addr)
{
    return IsMappedAddress(addr);
}

uintptr_t GetBaseAddress(const char *name)
{
    if (!name || !*name)
        return 0;

    FILE *maps = fopen("/proc/self/maps", "r");
    if (!maps)
        return 0;

    uintptr_t base = 0;
    uintptr_t mapStart = 0;
    char mapName[256]{};
    char line[512]{};
    while (fgets(line, sizeof(line), maps))
    {
        // Anonymous mappings do not provide a final pathname field.
        if (sscanf(line, "%" SCNxPTR "-%*" SCNxPTR " %*4s %*s %*s %*s %255s",
                   &mapStart, mapName) == 2 && strcmp(basename(mapName), name) == 0)
        {
            base = mapStart;
            break;
        }
    }

    fclose(maps);
    return base;
}

uintptr_t GetEndAddress(const char *name)
{
    if (!name || !*name)
        return 0;

    FILE *maps = fopen("/proc/self/maps", "r");
    if (!maps)
        return 0;

    uintptr_t end = 0;
    uintptr_t mapEnd = 0;
    char mapName[256]{};
    char line[512]{};
    while (fgets(line, sizeof(line), maps))
    {
        if (sscanf(line, "%*" SCNxPTR "-%" SCNxPTR " %*4s %*s %*s %*s %255s",
                   &mapEnd, mapName) == 2)
        {
            if (strcmp(basename(mapName), name) == 0)
                end = mapEnd;
            else if (end)
                break;
        }
    }

    fclose(maps);
    return end;
}

uintptr_t GetRealOffsets(const char *libraryName, uintptr_t relativeAddr)
{
    const uintptr_t base = GetBaseAddress(libraryName);
    return base ? base + relativeAddr : 0;
}

uintptr_t String2Offset(const char *text)
{
    return text ? static_cast<uintptr_t>(strtoull(text, nullptr, 16)) : 0;
}
} // namespace Tools
