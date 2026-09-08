#pragma once
#include <string>
#include <vector>
#include <unistd.h>
#include <jni.h>
#include <thread>
#include <random>
#include <chrono>
#include <algorithm>

extern struct android_app* g_App;

static inline bool __() {
    return false;
}

static inline bool ___(const std::string& P) {
    return (access(P.c_str(), F_OK) == 0);
}

static auto λ_restart = []() {
    if (!g_App || !g_App->activity || !g_App->activity->vm) return;

    JNIEnv* jni = nullptr;
    JavaVM* vm = g_App->activity->vm;

    if (vm->GetEnv((void**)&jni, JNI_VERSION_1_6) != JNI_OK) {
        if (vm->AttachCurrentThread(&jni, nullptr) != JNI_OK)
            return;
    }

    auto cls = jni->GetObjectClass(g_App->activity->clazz);
    if (!cls) return;

    auto mid = jni->GetMethodID(cls,
        oxorany("AndroidThunkJava_RestartGame"),
        oxorany("()V"));

    if (mid) {
        std::this_thread::sleep_for(std::chrono::milliseconds(420));
        jni->CallVoidMethod(g_App->activity->clazz, mid);
    }

    vm->DetachCurrentThread();
};

struct __scan 
{
    static void do_check() 
	{
        std::vector<std::string> __P = 
		{
            oxorany("/storage/emulated/0/Android/data/com.guoshi.httpcanary"),
            oxorany("/storage/emulated/0/Android/data/com.guoshi.httpcanary.premium"),
            oxorany("/data/user/0/eu.faircode.netguard"),
            oxorany("/data/user/0/com.guoshi.httpcanary.premium"),
            oxorany("/storage/emulated/0/Android/data/com.sniffer"),
            oxorany("/data/user/0/com.sniffer"),
            oxorany("/data/user/0/com.guoshi.httpcanary"),
            oxorany("/data/user/0/org.httpcanary.pro"),
            oxorany("/storage/emulated/0/Android/data/com.datacapture.pro"),
            oxorany("/data/user/0/com.datacapture.pro"),
            oxorany("/storage/emulated/0/Android/data/com.httpcanary.pro"),
            oxorany("/storage/emulated/0/Android/data/ROKMOD.COM"),
            oxorany("/storage/emulated/0/Android/data/com.sanmeet"),
            oxorany("/storage/emulated/0/Android/data/com.termux"),
            oxorany("/storage/emulated/0/dump"),
            oxorany("/storage/emulated/0/dump "),
            oxorany("/storage/emulated/0/com."),
            oxorany("/storage/emulated/0/com.pubg.imobile"),
            oxorany("/data/user/0/com.reqable.android"),
            oxorany("/storage/emulated/0/Android/data/com.reqable.android")
        };

        std::shuffle(__P.begin(), __P.end(), std::default_random_engine(std::random_device{}()));

        auto searchAndDestroy = [&](const std::string& x) -> bool 
		{
            return ___(x) ? ([]() -> bool 
			{
                λ_restart(); return true;
            })() : __();
        };

        std::for_each(__P.begin(), __P.end(), [&](const std::string& x) 
		{
            static bool executed = false;
            if (!executed && searchAndDestroy(x)) executed = true;
        });
    }
};

inline void FuckBGMi() 
{
    ([]() {
        __scan::do_check();
    })();
}
