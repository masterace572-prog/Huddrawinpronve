# ShadowHook source provenance

This directory vendors **ShadowHook v2.0.1** from the official ByteDance
[`android-inline-hook`](https://github.com/bytedance/android-inline-hook)
repository.

- Upstream tag: `v2.0.1`
- Upstream commit: `854c775c2c3676e57a0f383597ebf420b5204161`
- Imported source: `shadowhook/src/main/cpp`

`jni/Android.mk` builds `libshadowhook.so` and its required runtime companion
`libshadowhook_nothing.so` from these sources. The companion is required by
ShadowHook's linker initialization path and must be packaged with the app.

## Project compatibility patch

`shadowhook.c` contains one narrowly scoped build-time compatibility guard:
`SH_CONFIG_ALLOW_LINKER_INIT_FAILURE`. It applies only when an Android linker
hides the private `soinfo` symbols used by ShadowHook's **optional** dynamic
library monitoring feature, which otherwise causes initialization error `12`.
This project hooks only already-loaded, explicit function addresses in
`libUE4.so`; with the guard enabled, those direct-address hooks can initialize
without automatic hooks for libraries loaded later. The default upstream
behaviour is retained unless that build flag is supplied by `Android.mk`.

The v2.0.1 source also has two build-only compatibility adaptations for the
project's older AIDE NDK headers: it omits the optional `PR_SET_VMA_ANON_NAME`
page label when that constant is unavailable, and obtains the runtime Android
API level through the long-supported system property API when
`android_get_device_api_level()` is unavailable. Neither alters hook logic.

The same optional VMA-label guard is applied to ShadowHook's hub-stack
allocation. Its bundled xDL utility uses the same system-property API-level
fallback so it also builds with those headers.
