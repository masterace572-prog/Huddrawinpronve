LOCAL_PATH := $(call my-dir)

# Official ByteDance ShadowHook v2.0.1 source integration.
# Build it as a shared library, exactly as upstream documents, so its required
# libshadowhook_nothing.so companion is available to linker initialization.
SHADOWHOOK_SOURCE := $(LOCAL_PATH)/shadowhook/src/main/cpp
SHADOWHOOK_COMMON_SRC := \
    shadowhook/src/main/cpp/common/bytesig.c \
    shadowhook/src/main/cpp/common/sh_errno.c \
    shadowhook/src/main/cpp/common/sh_log.c \
    shadowhook/src/main/cpp/common/sh_ref.c \
    shadowhook/src/main/cpp/common/sh_trampo.c \
    shadowhook/src/main/cpp/common/sh_util.c \
    shadowhook/src/main/cpp/sh_elf.c \
    shadowhook/src/main/cpp/sh_enter.c \
    shadowhook/src/main/cpp/sh_hub.c \
    shadowhook/src/main/cpp/sh_island.c \
    shadowhook/src/main/cpp/sh_jni.c \
    shadowhook/src/main/cpp/sh_linker.c \
    shadowhook/src/main/cpp/sh_recorder.c \
    shadowhook/src/main/cpp/sh_safe.c \
    shadowhook/src/main/cpp/sh_switch.c \
    shadowhook/src/main/cpp/sh_task.c \
    shadowhook/src/main/cpp/sh_xdl.c \
    shadowhook/src/main/cpp/shadowhook.c \
    shadowhook/src/main/cpp/third_party/xdl/xdl.c \
    shadowhook/src/main/cpp/third_party/xdl/xdl_iterate.c \
    shadowhook/src/main/cpp/third_party/xdl/xdl_linker.c \
    shadowhook/src/main/cpp/third_party/xdl/xdl_lzma.c \
    shadowhook/src/main/cpp/third_party/xdl/xdl_util.c

ifeq ($(TARGET_ARCH_ABI),arm64-v8a)
    SHADOWHOOK_ARCH_SRC := shadowhook/src/main/cpp/arch/arm64/sh_a64.c \
                           shadowhook/src/main/cpp/arch/arm64/sh_inst.c \
                           shadowhook/src/main/cpp/arch/arm64/sh_glue.S
    SHADOWHOOK_ARCH_LDFLAGS := -Wl,-z,max-page-size=16384
else ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
    SHADOWHOOK_ARCH_SRC := shadowhook/src/main/cpp/arch/arm/sh_a32.c \
                           shadowhook/src/main/cpp/arch/arm/sh_inst.c \
                           shadowhook/src/main/cpp/arch/arm/sh_t16.c \
                           shadowhook/src/main/cpp/arch/arm/sh_t32.c \
                           shadowhook/src/main/cpp/arch/arm/sh_txx.c \
                           shadowhook/src/main/cpp/arch/arm/sh_glue.S
    SHADOWHOOK_ARCH_LDFLAGS :=
else
    $(error ShadowHook v2.0.1 supports only armeabi-v7a and arm64-v8a)
endif

include $(CLEAR_VARS)
LOCAL_MODULE := shadowhook
LOCAL_SRC_FILES := $(SHADOWHOOK_COMMON_SRC) $(SHADOWHOOK_ARCH_SRC)
LOCAL_C_INCLUDES := $(SHADOWHOOK_SOURCE) \
                    $(SHADOWHOOK_SOURCE)/include \
                    $(SHADOWHOOK_SOURCE)/common \
                    $(SHADOWHOOK_SOURCE)/third_party/xdl \
                    $(SHADOWHOOK_SOURCE)/third_party/bsd \
                    $(SHADOWHOOK_SOURCE)/third_party/lss
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)
LOCAL_CFLAGS := -std=c11 -Os -fvisibility=hidden -ffunction-sections -fdata-sections
LOCAL_LDFLAGS := $(SHADOWHOOK_ARCH_LDFLAGS) -Wl,--exclude-libs,ALL -Wl,--gc-sections \
                 -Wl,--version-script=$(SHADOWHOOK_SOURCE)/shadowhook.map.txt
LOCAL_LDLIBS := -llog
include $(BUILD_SHARED_LIBRARY)

# ShadowHook dynamically loads this companion during linker initialization.
include $(CLEAR_VARS)
LOCAL_MODULE := shadowhook_nothing
LOCAL_SRC_FILES := shadowhook/src/main/cpp/nothing/sh_nothing.c
LOCAL_CFLAGS := -std=c11 -Oz -fvisibility=hidden -ffunction-sections -fdata-sections
LOCAL_LDFLAGS := $(SHADOWHOOK_ARCH_LDFLAGS) -Wl,--gc-sections
include $(BUILD_SHARED_LIBRARY)

PREBUILT_DIR := prebuilt/fuck

include $(CLEAR_VARS)
LOCAL_MODULE := KittyMemory
LOCAL_SRC_FILES := $(PREBUILT_DIR)/KittyMemory/KittyMemory.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := MemoryPatch
LOCAL_SRC_FILES := $(PREBUILT_DIR)/KittyMemory/MemoryPatch.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := MemoryBackup
LOCAL_SRC_FILES := $(PREBUILT_DIR)/KittyMemory/MemoryBackup.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := KittyUtils
LOCAL_SRC_FILES := $(PREBUILT_DIR)/KittyMemory/KittyUtils.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := hde64
LOCAL_SRC_FILES := $(PREBUILT_DIR)/Substrate/hde64.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := SubstrateHook
LOCAL_SRC_FILES := $(PREBUILT_DIR)/Substrate/SubstrateHook.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := SubstrateDebug
LOCAL_SRC_FILES := $(PREBUILT_DIR)/Substrate/SubstrateDebug.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := SubstratePosixMemory
LOCAL_SRC_FILES := $(PREBUILT_DIR)/Substrate/SubstratePosixMemory.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := base64
LOCAL_SRC_FILES := $(PREBUILT_DIR)/base64/base64.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := ElfImg
LOCAL_SRC_FILES := $(PREBUILT_DIR)/ElfImg.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := fake_dlfcn
LOCAL_SRC_FILES := $(PREBUILT_DIR)/fake_dlfcn.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := android_native_app_glue
LOCAL_SRC_FILES := $(PREBUILT_DIR)/android_native_app_glue.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := plthook_elf
LOCAL_SRC_FILES := $(PREBUILT_DIR)/plthook_elf.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := And64InlineHook
LOCAL_SRC_FILES := $(PREBUILT_DIR)/And64InlineHook/And64InlineHook.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := Anoy
                   
LOCAL_CFLAGS := -Wno-error=format-security -fvisibility=hidden -ffunction-sections -fdata-sections -w
LOCAL_CFLAGS += -fno-rtti -fno-exceptions -fpermissive
LOCAL_CPPFLAGS := -Wno-error=format-security -fvisibility=hidden -ffunction-sections -fdata-sections -w -Werror -s -std=c++17
LOCAL_CPPFLAGS += -Wno-error=c++11-narrowing -fms-extensions -fno-rtti -fno-exceptions -fpermissive
LOCAL_LDFLAGS += -Wl,--gc-sections,--strip-all, -llog
LOCAL_ARM_MODE := arm

LOCAL_SRC_FILES :=  main.cpp \
        ToolsRuntime.cpp \
        SDK/PUBGM_Basic.cpp \
        SDK/PUBGM_Basic_functions.cpp \
        SDK/PUBGM_CoreUObject_functions.cpp \
        SDK/PUBGM_Engine_functions.cpp \
        SDK/PUBGM_ShadowTrackerExtra_functions.cpp \
        SDK/PUBGM_Client_functions.cpp \

LOCAL_CPP_FEATURES := exceptions

LOCAL_LDLIBS := -llog -landroid -lEGL -lGLESv2 -lGLESv3 -lGLESv1_CM -lz

LOCAL_STATIC_LIBRARIES := And64InlineHook ElfImg fake_dlfcn android_native_app_glue plthook_elf base64 SubstrateDebug SubstrateHook hde64 SubstratePosixMemory KittyMemory MemoryPatch MemoryBackup KittyUtils
LOCAL_SHARED_LIBRARIES := shadowhook shadowhook_nothing

include $(BUILD_SHARED_LIBRARY)
