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
