# ShadowHook source provenance

This directory vendors **ShadowHook v2.0.1** from the official ByteDance
[`android-inline-hook`](https://github.com/bytedance/android-inline-hook)
repository.

- Upstream tag: `v2.0.1`
- Upstream commit: `854c775c2c3676e57a0f383597ebf420b5204161`
- Imported source: `shadowhook/src/main/cpp`

`jni/Android.mk` compiles the v2.0.1 hook API directly into `libAnoy.so`.
The injection payload is self-contained: it does not build, link, package, or
load `libshadowhook.so` or `libshadowhook_nothing.so`. Direct static linking is
intentional because the older AIDE ndk-build used by this project does not
place shared-module dependencies on the final C++ linker command.

## Project compatibility patch

`shadowhook.c` contains a narrowly scoped build-time compatibility mode:
`SH_CONFIG_DIRECT_ADDRESS_ONLY`. The project hooks only explicit, already-loaded
function addresses in `libUE4.so`, so it skips ShadowHook's optional linker
load/unload monitor and task monitor. This prevents initialization error `12`
on devices that hide private linker symbols and avoids the companion
`libshadowhook_nothing.so` dependency. Symbol-name hooks and automatic hooks
for libraries loaded after initialization are intentionally unavailable in this
self-contained injection build. The default upstream behaviour is retained
unless this build flag is supplied by `Android.mk`.

The v2.0.1 source also has two build-only compatibility adaptations for the
project's older AIDE NDK headers: it omits the optional `PR_SET_VMA_ANON_NAME`
page label when that constant is unavailable, and obtains the runtime Android
API level through the long-supported system property API when
`android_get_device_api_level()` is unavailable. Neither alters hook logic.

The same optional VMA-label guard is applied to ShadowHook's hub-stack
allocation. Its bundled xDL utility uses the same system-property API-level
fallback so it also builds with those headers. The xDL header additionally
provides the numeric Android Q/R API-level constants (29/30) when an older
AIDE NDK predates those symbolic definitions.
