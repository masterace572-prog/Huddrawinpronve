#include <list>
#include <vector>
#include <cstring>
#include <pthread.h>
#include <thread>
#include <jni.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/socket.h>
#include <malloc.h>
#include <math.h>
#include <sys/stat.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <locale>
#include <string>
#include <codecvt>
#include "SDK.hpp"
#include "KittyMemory/MemoryPatch.h"
#include "Substrate/SubstrateHook.h"
#include "Includes/Logger.h"
#include "Includes/Utils.h"
#include "Includes/Macros.h"
#include "Tools.h"
#include "Includes/json.hpp"
#include "Includes/android_include.h"
#include "Includes/Vector2.hpp"
#include "Includes/Vector3.hpp"

#include <cassert>
#include <fcntl.h>
#include <unistd.h>
#define _BYTE uint8_t
#define _WORD uint16_t
#define _DWORD uint32_t
#define _QWORD uint64_t
#define DefineHook(RET, NAME, ARGS) \
    RET(*Orig_##NAME)               \
    ARGS;                           \
    RET Hook_##NAME ARGS    
    
#include <fcntl.h>
#include <iostream>
#include <fstream>
#include <unistd.h> // for sleep
#include <string>

#include "oxorany.h"

size_t &_lxy_oxor_any_::X()
{
    static size_t x = 0;
    return x;
}

size_t &_lxy_oxor_any_::Y()
{
    static size_t y = 0;
    return y;
}
