# CChromaEditor - C++ Native MFC Library for playing and editing Chroma animations

**Table of Contents**

* [Related](#related)
* [Frameworks supported](#frameworks-supported)
* [Prerequisites](#prerequisites)
* [Assets](#assets)
* [API](#api)
* [Edit API](#edit-api)

<a name="related"></a>
## Related

- [CChromaEditor](https://github.com/RazerOfficial/CChromaEditor) - C++ Native MFC Library for playing and editing Chroma animations

- [GameMakerChromaExtension](https://github.com/RazerOfficial/GameMakerChromaExtension) - GameMaker Extension to control lighting for Razer Chroma

- [UE4ChromaSDK](https://github.com/RazerOfficial/UE4ChromaSDK) - Unreal Engine 4 (UE4) Blueprint library to control lighting for Razer Chroma

- [UnityNativeChromaSDK](https://github.com/RazerOfficial/UnityNativeChromaSDK) - Unity native library for the ChromaSDK

- [UnityChromaSDK](https://github.com/RazerOfficial/UnityChromaSDK) - Unity C# library for the Chroma Rest API

<a name="frameworks-supported"></a>
## Frameworks supported
- Windows ChromaSDK (32-bit)

- Windows ChromaSDK (64-bit)

<a name="prerequisites"></a>
## Prerequisites

- Install [Synapse](http://developer.razerzone.com/works-with-chroma/download/)

- Install [Chroma SDK 2.5.3](http://developer.razerzone.com/works-with-chroma/download/)

- Install [Microsoft Visual C++ Redistributable for Visual Studio 2017](https://www.visualstudio.com/downloads/)

- To compile: Install [Visual Studio](https://www.visualstudio.com/)

- To compile: Install [Windows 10 SDK](https://developer.microsoft.com/en-us/windows/downloads/windows-10-sdk)

- To compile: Install `Templates->Other Languages->Visual C++->Visual C++ 2015 Tools for Windows Desktop` which can be installed through the `Visual Studio New Project Dialog`

![image_42](images/image_2.png)


<a name="getting-started"></a>
## Getting Started

1 Open `CChromaEditor.sln` in Visual Studio

2 The `CChromaEditorLibrary` project builds the native C++ DLL for `x64` and `x86` platforms

3 The `CConsoleEditor` project is a console project that uses the `DLL` and provides a command-line interface. The only parameter is the file path to a `Chroma` animation file. When no parameter is provided, the editor cycles through a series of unit tests.

<a name="assets"></a>
## Assets

This library supports the `Chroma` animation exports from [UE4](https://github.com/razerofficial/UE4ChromaSDK), [Unity](https://github.com/razerofficial/UnityNativeChromaSDK/), and [GameMaker](https://github.com/razerofficial/GameMakerChromaExtension).

<a name="api"></a>
## API

The API has various methods with the `D` suffix where `double` return-type/parameters were used. This is to support engines like `GameMaker` which have a limited number of data-types.

**PluginSetLogDelegate**

Invokes the setup for a debug logging callback so that `stdout` is redirected to the callback. This is used by `Unity` so that debug messages can appear in the console window.

```C++
extern "C" EXPORT_API void PluginSetLogDelegate(DebugLogPtr fp);
```

**PluginIsInitialized**

Returns true if the plugin has been initialized. Returns false if the plugin is uninitialized.

```C++
extern "C" EXPORT_API bool PluginIsInitialized();
extern "C" EXPORT_API double PluginIsInitializedD();
```

**PluginIsDialogOpen**

The editor dialog is a non-blocking modal window, this method returns true if the modal window is open, otherwise false.

```C++
extern "C" EXPORT_API bool PluginIsDialogOpen();
extern "C" EXPORT_API double PluginIsDialogOpenD();
```

**PluginOpenEditorDialog**

Opens a `Chroma` animation file with the `.chroma` extension. Returns zero upon success. Returns -1 if there was a failure.

```C++
extern "C" EXPORT_API int PluginOpenEditorDialog(char* path);
extern "C" EXPORT_API double PluginOpenEditorDialogD(char* path);
```

![image_1](images/image_1.png)

**PluginOpenAnimation**

Opens a `Chroma` animation file so that it can be played. Returns an animation id >= 0 upon success. Returns -1 if there was a failure. The animation id is used in most of the API methods.

```C++
extern "C" EXPORT_API int PluginOpenAnimation(char* path);
extern "C" EXPORT_API double PluginOpenAnimationD(char* path);
```

**PluginLoadAnimation**

Loads `Chroma` effects so that the animation can be played immediately. Returns the animation id upon success. Returns -1 upon failure.

```C++
extern "C" EXPORT_API int PluginLoadAnimation(int animationId);
extern "C" EXPORT_API double PluginLoadAnimationD(double animationId);
```

**PluginUnloadAnimation**

Unloads `Chroma` effects to free up resources. Returns the animation id upon success. Returns -1 upon failure.

```C++
extern "C" EXPORT_API int PluginUnloadAnimation(int animationId);
extern "C" EXPORT_API double PluginUnloadAnimationD(double animationId);
```

**PluginPlayAnimation**

Plays the `Chroma` animation. This will load the animation, if not loaded previously. Returns the animation id upon success. Returns -1 upon failure.

```C++
extern "C" EXPORT_API int PluginPlayAnimation(int animationId);
extern "C" EXPORT_API double PluginPlayAnimationD(double animationId);
```

**PluginStopAnimation**

Stops animation playback if in progress. Returns the animation id upon success. Returns -1 upon failure.

```C++
extern "C" EXPORT_API int PluginStopAnimation(int animationId);
extern "C" EXPORT_API double PluginStopAnimationD(double animationId);
```

**PluginCloseAnimation**

Closes the `Chroma` animation to free up resources. Returns the animation id upon success. Returns -1 upon failure. This might be used while authoring effects if there was a change necessitating re-opening the animation. The animation id can no longer be used once closed.

```C++
extern "C" EXPORT_API int PluginCloseAnimation(int animationId);
extern "C" EXPORT_API double PluginCloseAnimationD(double animationId);
```

**PluginUninit**

Uninitializes the `ChromaSDK`. Returns 0 upon success. Returns -1 upon failure.

```C++
extern "C" EXPORT_API int PluginUninit();
extern "C" EXPORT_API double PluginUninitD();
```

**EChromaSDKDeviceTypeEnum**

The supported device types are `1D` and `2D`.

```C++
enum EChromaSDKDeviceTypeEnum
{
    DE_1D = 0,
    DE_2D,
};
```

**EChromaSDKDevice1DEnum**

`1D` devices are `ChromaLink`, `Headset`, and `Mousepad`.

```C++
enum EChromaSDKDevice1DEnum
{
    DE_ChromaLink = 0,
    DE_Headset,
    DE_Mousepad,
};
```

**EChromaSDKDevice2DEnum**

`2D` devices are `Keyboard`, `Keypad`, and `Mouse`.

```C++
enum EChromaSDKDevice2DEnum
{
    DE_Keyboard = 0,
    DE_Keypad,
    DE_Mouse,
};
```

**PluginGetDeviceType**

Returns the `EChromaSDKDeviceTypeEnum` of a `Chroma` animation as an integer upon success. Returns -1 upon failure.

```C++
EXPORT_API int PluginGetDeviceType(int animationId);
```

**PluginGetDevice**

Returns the `EChromaSDKDevice1DEnum` or `EChromaSDKDevice2DEnum` of a `Chroma` animation respective to the `deviceType`, as an integer upon success. Returns -1 upon failure.

```C++
EXPORT_API int PluginGetDevice(int animationId);
```

**PluginGetMaxLeds**

Returns the MAX LEDS given the `EChromaSDKDevice1DEnum` device as an integer upon success. Returns -1 upon failure. 

```C++
EXPORT_API int PluginGetMaxLeds(int device);
```

**PluginGetMaxRow**

Returns the `MAX ROW` given the `EChromaSDKDevice2DEnum` device as an integer upon success. Returns -1 upon failure.

```C++
EXPORT_API int PluginGetMaxRow(int device);
```

**PluginGetMaxColumn**

Returns the `MAX COLUMN` given the `EChromaSDKDevice2DEnum` device as an integer upon success. Returns -1 upon failure.

```C++
EXPORT_API int PluginGetMaxColumn(int device);
```

**PluginGetFrameCount**

Returns the frame count of a `Chroma` animation upon success. Returns -1 upon failure.

```C++
EXPORT_API int PluginGetFrameCount(int animationId);
```

<a name="edit-api"></a>
## Edit API

The following edit methods will modify the provided `Chroma` animation. `Edit` methods will automatically `stop` the animation when used.

**PluginCreateAnimation**

Creates a `Chroma` animation at the given path. The `deviceType` parameter uses `EChromaSDKDeviceTypeEnum` as an integer. The `device` parameter uses `EChromaSDKDevice1DEnum` or `EChromaSDKDevice2DEnum` as an integer, respective to the `deviceType`. Returns the animation id upon success. Returns -1 upon failure.

```C++
EXPORT_API int PluginCreateAnimation(char* path, int deviceType, int device);
```

Saves a `Chroma` animation file with the `.chroma` extension at the given path. Returns the animation id upon success. Returns -1 upon failure.

**PluginCreateAnimationInMemory**

Creates a `Chroma` animation in memory without creating a file. The `deviceType` parameter uses `EChromaSDKDeviceTypeEnum` as an integer. The `device` parameter uses `EChromaSDKDevice1DEnum` or `EChromaSDKDevice2DEnum` as an integer, respective to the `deviceType`. Returns the animation id upon success. Returns -1 upon failure.

```C++
EXPORT_API int PluginCreateAnimationInMemory(int deviceType, int device);
```

Returns the animation id upon success. Returns -1 upon failure.

**PluginSaveAnimation**

```C++
EXPORT_API int PluginSaveAnimation(int animationId, char* path);
```

**PluginResetAnimation**

Resets the `Chroma` animation to 1 blank frame. Returns the animation id upon success. Returns -1 upon failure.

```C++
EXPORT_API int PluginResetAnimation(int animationId);
```

**PluginSetDevice**

Changes the `deviceType` and `device` of a `Chroma` animation. If the device is changed, the `Chroma` animation will be reset with 1 blank frame. Returns the animation id upon success. Returns -1 upon failure.

```C++
EXPORT_API int PluginSetDevice(int animationId, int deviceType, int device);
```

**PluginAddFrame**

Adds a frame to the `Chroma` animation and sets the `duration` (in seconds). The `color` is expected to be an array of the dimensions for the `deviceType/device`. The `length` parameter is the size of the `color` array. For `EChromaSDKDevice1DEnum` the array size should be `MAX LEDS`. For `EChromaSDKDevice2DEnum` the array size should be `MAX ROW` * `MAX COLUMN`. Returns the animation id upon success. Returns -1 upon failure.

```C++
EXPORT_API int PluginAddFrame(int animationId, float duration, int* colors, int length);
```

**PluginUpdateFrame**

Updates the `frameIndex` of the `Chroma` animation and sets the `duration` (in seconds). The `color` is expected to be an array of the dimensions for the `deviceType/device`. The `length` parameter is the size of the `color` array. For `EChromaSDKDevice1DEnum` the array size should be `MAX LEDS`. For `EChromaSDKDevice2DEnum` the array size should be `MAX ROW` * `MAX COLUMN`. Returns the animation id upon success. Returns -1 upon failure.

```C++
EXPORT_API int PluginUpdateFrame(int animationId, int frameIndex,
    float duration, int* colors, int length);
```

**PluginGetFrame**

Gets the frame colors and duration (in seconds) for a `Chroma` animation. The `color` is expected to be an array of the expected dimensions for the `deviceType/device`. The `length` parameter is the size of the `color` array. For `EChromaSDKDevice1DEnum` the array size should be `MAX LEDS`. For `EChromaSDKDevice2DEnum` the array size should be `MAX ROW` * `MAX COLUMN`. Returns the animation id upon success. Returns -1 upon failure. 

```C++
EXPORT_API int PluginGetFrame(int animationId, int frameIndex, float* duration, int* colors, int length)
```

**PluginPreviewFrame**

Displays the `Chroma` animation frame on `Chroma` hardware given the `frameIndex`. Returns the animation id upon success. Returns -1 upon failure.

```C++
EXPORT_API int PluginPreviewFrame(int animationId, int frameIndex);
```

**PluginOverrideFrameDuration**

Sets the `duration` for all grames in the `Chroma` animation to the `duration` parameter. Returns the animation id upon success. Returns -1 upon failure.

```C++
EXPORT_API int PluginOverrideFrameDuration(int animationId, float duration);
```

**PluginReverse**

Reverses the animation frame order of the `Chroma` animation. Returns the animation id upon success. Returns -1 upon failure.

```C++
EXPORT_API int PluginReverse(int animationId);
```

**PluginMirrorHorizontally**

Flips the color grid horizontally for all `Chroma` animation frames. Returns the animation id upon success. Returns -1 upon failure.

```C++
EXPORT_API int PluginMirrorHorizontally(int animationId);
```

**PluginMirrorVertically**

Flips the color grid vertically for all `Chroma` animation frames. This method has no effect for `EChromaSDKDevice1DEnum` devices. Returns the animation id upon success. Returns -1 upon failure.

```C++
EXPORT_API int PluginMirrorVertically(int animationId);
```
