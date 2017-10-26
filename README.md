# CChromaEditor - C++ Native MFC Library for playing and editing Chroma animations

**Table of Contents**

* [Related](#related)
* [Frameworks supported](#frameworks-supported)
* [Prerequisites](#prerequisites)
* [Assets](#assets)
* [API](#api)
* [Edit API](#edit-api)
* [File Format](#file-format)

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

**Running the editor application**

1 Run the [Chroma Editor Installer](https://github.com/razerofficial/CChromaEditor/releases/tag/1.0) to associate `.chroma` animations with the editor.

2 Double-click a `.chroma` animation file to open in the editor

**Building the editor**

1 Open `CChromaEditor.sln` in Visual Studio

2 The `CChromaEditorLibrary` project builds the native C++ DLL for `x64` and `x86` platforms

3 The `CConsoleEditor` project is a console project that uses the `DLL` and provides a command-line interface. The only parameter is the file path to a `Chroma` animation file. When no parameter is provided, the editor opens `temp.chroma` on the desktop.


<a name="assets"></a>
## Assets

This library supports the `Chroma` animation exports from [UE4](https://github.com/razerofficial/UE4ChromaSDK), [Unity](https://github.com/razerofficial/UnityNativeChromaSDK/), and [GameMaker](https://github.com/razerofficial/GameMakerChromaExtension).

![image_1](images/image_1.png)


<a name="api"></a>
## API

The API has various methods with the `D` suffix where `double` return-type/parameters were used. This is to support engines like `GameMaker` which have a limited number of data-types.

Methods:

* [PluginAddFrame](#PluginAddFrame)
* [PluginCloseAnimation](#PluginCloseAnimation)
* [PluginCloseAnimationName](#PluginCloseAnimationName)
* [PluginCopyKeyColor](#PluginCopyKeyColor)
* [PluginCopyKeyColorName](#PluginCopyKeyColorName)
* [PluginCreateAnimation](#PluginCreateAnimation)
* [PluginCreateAnimationInMemory](#PluginCreateAnimationInMemory)
* [PluginGetAnimation](#PluginGetAnimation)
* [PluginGetCurrentFrame](#PluginGetCurrentFrame)
* [PluginGetCurrentFrameName](#PluginGetCurrentFrameName)
* [PluginGetDevice](#PluginGetDevice)
* [PluginGetDeviceType](#PluginGetDeviceType)
* [PluginGetFrame](#PluginGetFrame)
* [PluginGetFrameCount](#PluginGetFrameCount)
* [PluginGetFrameCountName](#PluginGetFrameCountName)
* [PluginGetMaxColumn](#PluginGetMaxColumn)
* [PluginGetMaxLeds](#PluginGetMaxLeds)
* [PluginGetMaxRow](#PluginGetMaxRow)
* [PluginHasAnimationLoop](#PluginHasAnimationLoop)
* [PluginHasAnimationLoopName](#PluginHasAnimationLoopName)
* [PluginIsAnimationPaused](#PluginIsAnimationPaused)
* [PluginIsAnimationPausedName](#PluginIsAnimationPausedName)
* [PluginIsDialogOpen](#PluginIsDialogOpen)
* [PluginIsInitialized](#PluginIsInitialized)
* [PluginIsPlatformSupported](#PluginIsPlatformSupported)
* [PluginIsPlaying](#PluginIsPlaying)
* [PluginIsPlayingName](#PluginIsPlayingName)
* [PluginIsPlayingType](#PluginIsPlayingType)
* [PluginLoadAnimation](#PluginLoadAnimation)
* [PluginMirrorHorizontally](#PluginMirrorHorizontally)
* [PluginMirrorVertically](#PluginMirrorVertically)
* [PluginOpenAnimation](#PluginOpenAnimation)
* [PluginOpenEditorDialog](#PluginOpenEditorDialog)
* [PluginOpenEditorDialogAndPlay](#PluginOpenEditorDialogAndPlay)
* [PluginOverrideFrameDuration](#PluginOverrideFrameDuration)
* [PluginPauseAnimation](#PluginPauseAnimation)
* [PluginPauseAnimationName](#PluginPauseAnimationName)
* [PluginPlayAnimation](#PluginPlayAnimation)
* [PluginPlayAnimationLoop](#PluginPlayAnimationLoop)
* [PluginPlayAnimationName](#PluginPlayAnimationName)
* [PluginPlayComposite](#PluginPlayComposite)
* [PluginPreviewFrame](#PluginPreviewFrame)
* [PluginResetAnimation](#PluginResetAnimation)
* [PluginResumeAnimation](#PluginResumeAnimation)
* [PluginReverse](#PluginReverse)
* [PluginSaveAnimation](#PluginSaveAnimation)
* [PluginSetCurrentFrame](#PluginSetCurrentFrame)
* [PluginSetCurrentFrameName](#PluginSetCurrentFrameName)
* [PluginSetDevice](#PluginSetDevice)
* [PluginSetKeyColor](#PluginSetKeyColor)
* [PluginSetKeyColorName](#PluginSetKeyColorName)
* [PluginSetLogDelegate](#PluginSetLogDelegate)
* [PluginStopAnimation](#PluginStopAnimation)
* [PluginStopAnimationName](#PluginStopAnimationName)
* [PluginStopAnimationType](#PluginStopAnimationType)
* [PluginStopComposite](#PluginStopComposite)
* [PluginUninit](#PluginUninit)
* [PluginUnloadAnimation](#PluginUnloadAnimation)
* [PluginUpdateFrame](#PluginUpdateFrame)


<a name="PluginGetAnimation"></a>
**PluginGetAnimation**

`PluginGetAnimation` automatically handles initializing the `ChromaSDK`. The named `.chroma` animation file will be automatically opened. This method returns the `animationId` of the opened animation.

```C++
EXPORT_API int PluginGetAnimation(const char* name);
```


<a name="PluginPlayAnimationLoop"></a>
**PluginPlayAnimationLoop**

`PluginPlayAnimationLoop` automatically handles initializing the `ChromaSDK`. The method will play the animation given the `animationId` with looping `on` or `off`.

```C++
EXPORT_API void PluginPlayAnimationLoop(int animationId, bool loop);
```


<a name="PluginPlayAnimationName"></a>
**PluginPlayAnimationName**

`PluginPlayAnimationName` automatically handles initializing the `ChromaSDK`. The named `.chroma` animation file will be automatically opened. The animation will play with looping `on` or `off`.

```C++
EXPORT_API void PluginPlayAnimationName(const char* path, bool loop);
```


<a name="PluginStopAnimationName"></a>
**PluginStopAnimationName**

`PluginStopAnimationName` automatically handles initializing the `ChromaSDK`. The named `.chroma` animation file will be automatically opened. The animation will stop if playing.

```C++
EXPORT_API void PluginStopAnimationName(const char* path);
```


<a name="PluginStopAnimationType"></a>
**PluginStopAnimationType**

`PluginStopAnimationType` automatically handles initializing the `ChromaSDK`. If any animation is playing for the `deviceType` and `device` combination, it will be stopped.

```C++
EXPORT_API void PluginStopAnimationType(int deviceType, int device);
```


<a name="PluginIsPlayingName"></a>
**PluginIsPlayingName**

`PluginIsPlayingName` automatically handles initializing the `ChromaSDK`. The named `.chroma` animation file will be automatically opened. The method will return whether the animation is playing or not.

```C++
EXPORT_API bool PluginIsPlayingName(const char* path);
```


<a name="PluginIsPlayingType"></a>
**PluginIsPlayingType**

`PluginIsPlayingType` automatically handles initializing the `ChromaSDK`. If any animation is playing for the `deviceType` and `device` combination, the method will return true, otherwise false.

```C++
EXPORT_API bool PluginIsPlayingType(int deviceType, int device);
```


<a name="PluginPlayComposite"></a>
**PluginPlayComposite**

`PluginPlayComposite` automatically handles initializing the `ChromaSDK`. The named animation files for the `.chroma` set will be automatically opened. The set of animations will play with looping `on` or `off`.

```C++
EXPORT_API void PluginPlayComposite(const char* name, bool loop);

// Given "Random" this will invoke:
// PluginPlayAnimationName("Random_ChromaLink.chroma", loop);
// PluginPlayAnimationName("Random_Headset.chroma", loop);
// PluginPlayAnimationName("Random_Keyboard.chroma", loop);
// PluginPlayAnimationName("Random_Keypad.chroma", loop);
// PluginPlayAnimationName("Random_Mouse.chroma", loop);
// PluginPlayAnimationName("Random_Mousepad.chroma", loop);
```


<a name="PluginStopComposite"></a>
**PluginStopComposite**

`PluginStopComposite` automatically handles initializing the `ChromaSDK`. The named animation files for the `.chroma` set will be automatically opened. The set of animations will be stopped if playing.

```C++
EXPORT_API void PluginStopComposite(const char* name);

// Given "Random" this will invoke:
// PluginStopAnimationName("Random_ChromaLink.chroma");
// PluginStopAnimationName("Random_Headset.chroma");
// PluginStopAnimationName("Random_Keyboard.chroma");
// PluginStopAnimationName("Random_Keypad.chroma");
// PluginStopAnimationName("Random_Mouse.chroma");
// PluginStopAnimationName("Random_Mousepad.chroma");
```


<a name="PluginSetLogDelegate"></a>
**PluginSetLogDelegate**

Invokes the setup for a debug logging callback so that `stdout` is redirected to the callback. This is used by `Unity` so that debug messages can appear in the console window.

```C++
extern "C" EXPORT_API void PluginSetLogDelegate(DebugLogPtr fp);
```


<a name="PluginIsInitialized"></a>
**PluginIsInitialized**

Returns true if the plugin has been initialized. Returns false if the plugin is uninitialized.

```C++
extern "C" EXPORT_API bool PluginIsInitialized();
extern "C" EXPORT_API double PluginIsInitializedD();
```


<a name="PluginIsDialogOpen"></a>
**PluginIsDialogOpen**

The editor dialog is a non-blocking modal window, this method returns true if the modal window is open, otherwise false.

```C++
extern "C" EXPORT_API bool PluginIsDialogOpen();
extern "C" EXPORT_API double PluginIsDialogOpenD();
```


<a name="PluginOpenEditorDialog"></a>
**PluginOpenEditorDialog**

Opens a `Chroma` animation file with the `.chroma` extension. Returns zero upon success. Returns -1 if there was a failure.

```C++
extern "C" EXPORT_API int PluginOpenEditorDialog(const char* path);
extern "C" EXPORT_API double PluginOpenEditorDialogD(const char* path);
```


<a name="PluginOpenAnimation"></a>
**PluginOpenAnimation**

Opens a `Chroma` animation file so that it can be played. Returns an animation id >= 0 upon success. Returns -1 if there was a failure. The animation id is used in most of the API methods.

```C++
extern "C" EXPORT_API int PluginOpenAnimation(const char* path);
extern "C" EXPORT_API double PluginOpenAnimationD(const char* path);
```


<a name="PluginLoadAnimation"></a>
**PluginLoadAnimation**

Loads `Chroma` effects so that the animation can be played immediately. Returns the animation id upon success. Returns -1 upon failure.

```C++
extern "C" EXPORT_API int PluginLoadAnimation(int animationId);
extern "C" EXPORT_API double PluginLoadAnimationD(double animationId);
```


<a name="PluginUnloadAnimation"></a>
**PluginUnloadAnimation**

Unloads `Chroma` effects to free up resources. Returns the animation id upon success. Returns -1 upon failure.

```C++
extern "C" EXPORT_API int PluginUnloadAnimation(int animationId);
extern "C" EXPORT_API double PluginUnloadAnimationD(double animationId);
```


<a name="PluginPlayAnimation"></a>
**PluginPlayAnimation**

Plays the `Chroma` animation. This will load the animation, if not loaded previously. Returns the animation id upon success. Returns -1 upon failure.

```C++
extern "C" EXPORT_API int PluginPlayAnimation(int animationId);
extern "C" EXPORT_API double PluginPlayAnimationD(double animationId);
```


<a name="PluginStopAnimation"></a>
**PluginStopAnimation**

Stops animation playback if in progress. Returns the animation id upon success. Returns -1 upon failure.

```C++
extern "C" EXPORT_API int PluginStopAnimation(int animationId);
extern "C" EXPORT_API double PluginStopAnimationD(double animationId);
```


<a name="PluginCloseAnimation"></a>
**PluginCloseAnimation**

Closes the `Chroma` animation to free up resources. Returns the animation id upon success. Returns -1 upon failure. This might be used while authoring effects if there was a change necessitating re-opening the animation. The animation id can no longer be used once closed.

```C++
extern "C" EXPORT_API int PluginCloseAnimation(int animationId);
extern "C" EXPORT_API double PluginCloseAnimationD(double animationId);
```


<a name="PluginUninit"></a>
**PluginUninit**

Uninitializes the `ChromaSDK`. Returns 0 upon success. Returns -1 upon failure.

```C++
extern "C" EXPORT_API int PluginUninit();
extern "C" EXPORT_API double PluginUninitD();
```


<a name="EChromaSDKDeviceTypeEnum"></a>
**EChromaSDKDeviceTypeEnum**

The supported device types are `1D` and `2D`.

```C++
enum EChromaSDKDeviceTypeEnum
{
    DE_1D = 0,
    DE_2D,
};
```


<a name="EChromaSDKDevice1DEnum"></a>
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


<a name="EChromaSDKDevice2DEnum"></a>
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


<a name="PluginGetDeviceType"></a>
**PluginGetDeviceType**

Returns the `EChromaSDKDeviceTypeEnum` of a `Chroma` animation as an integer upon success. Returns -1 upon failure.

```C++
EXPORT_API int PluginGetDeviceType(int animationId);
```


<a name="PluginGetDevice"></a>
**PluginGetDevice**

Returns the `EChromaSDKDevice1DEnum` or `EChromaSDKDevice2DEnum` of a `Chroma` animation respective to the `deviceType`, as an integer upon success. Returns -1 upon failure.

```C++
EXPORT_API int PluginGetDevice(int animationId);
```


<a name="PluginGetMaxLeds"></a>
**PluginGetMaxLeds**

Returns the MAX LEDS given the `EChromaSDKDevice1DEnum` device as an integer upon success. Returns -1 upon failure. 

```C++
EXPORT_API int PluginGetMaxLeds(int device);
```


<a name="PluginGetMaxRow"></a>
**PluginGetMaxRow**

Returns the `MAX ROW` given the `EChromaSDKDevice2DEnum` device as an integer upon success. Returns -1 upon failure.

```C++
EXPORT_API int PluginGetMaxRow(int device);
```


<a name="PluginGetMaxColumn"></a>
**PluginGetMaxColumn**

Returns the `MAX COLUMN` given the `EChromaSDKDevice2DEnum` device as an integer upon success. Returns -1 upon failure.

```C++
EXPORT_API int PluginGetMaxColumn(int device);
```


<a name="PluginGetFrameCount"></a>
**PluginGetFrameCount**

Returns the frame count of a `Chroma` animation upon success. Returns -1 upon failure.

```C++
EXPORT_API int PluginGetFrameCount(int animationId);
```


<a name="PluginGetFrameCountName"></a>
**PluginGetFrameCountName**

Returns the frame count of a `Chroma` animation upon success. Returns -1 upon failure.

```C++
EXPORT_API int PluginGetFrameCountName(const char* path);
```


<a name="PluginGetCurrentFrame"></a>
**PluginGetCurrentFrame**

Get the current frame of the animation referenced by id.

```C++
EXPORT_API int PluginGetCurrentFrame(int animationId);
```


<a name="PluginGetCurrentFrameName"></a>
**PluginGetCurrentFrameName**

Get the current frame of the animation referenced by name.

```C++
EXPORT_API int PluginGetCurrentFrameName(const char* path);
```


<a name="PluginSetCurrentFrame"></a>
**PluginSetCurrentFrame**

Set the current frame of the animation referenced by id.

```C++
EXPORT_API void PluginSetCurrentFrame(int animationId, int frameId);
```


<a name="PluginSetCurrentFrameName"></a>
**PluginSetCurrentFrameName**

Set the current frame of the animation referenced by name.

```C++
EXPORT_API void PluginSetCurrentFrameName(const char* path, int frameId);
```


<a name="PluginPauseAnimation"></a>
**PluginPauseAnimation**

Pause the current animation referenced by id.

```C++
EXPORT_API void PluginPauseAnimation(int animationId);
```


<a name="PluginPauseAnimationName"></a>
**PluginPauseAnimationName**

Pause the current animation referenced by name.

```C++
EXPORT_API void PluginPauseAnimationName(const char* path);
```


<a name="PluginIsAnimationPaused"></a>
**PluginIsAnimationPaused**

Check if the animation is paused referenced by id.

```C++
EXPORT_API bool PluginIsAnimationPaused(int animationId);
```


<a name="PluginIsAnimationPausedName"></a>
**PluginIsAnimationPausedName**

Check if the animation is paused referenced by name.

```C++
EXPORT_API bool PluginIsAnimationPausedName(const char* path);
```


<a name="PluginHasAnimationLoop"></a>
**PluginHasAnimationLoop**

Check if the animation has loop enabled referenced by id.

```C++
EXPORT_API bool PluginHasAnimationLoop(int animationId);
```


<a name="PluginHasAnimationLoopName"></a>
**PluginHasAnimationLoopName**

Check if the animation has loop enabled referenced by name.

```C++
EXPORT_API bool PluginHasAnimationLoopName(const char* path);
```


<a name="PluginResumeAnimation"></a>
**PluginResumeAnimation**

Resume the animation with loop `ON` or `OFF` referenced by id.

```C++
EXPORT_API void PluginResumeAnimation(int animationId, bool loop);
```


<a name="PluginResumeAnimationName"></a>
**PluginResumeAnimationName**

Resume the animation with loop `ON` or `OFF` referenced by name.

```C++
EXPORT_API void PluginResumeAnimationName(const char* path, bool loop);
```


<a name="edit-api"></a>
## Edit API

The following edit methods will modify the provided `Chroma` animation. `Edit` methods will automatically `stop` the animation when used.


<a name="PluginCreateAnimation"></a>
**PluginCreateAnimation**

Creates a `Chroma` animation at the given path. The `deviceType` parameter uses `EChromaSDKDeviceTypeEnum` as an integer. The `device` parameter uses `EChromaSDKDevice1DEnum` or `EChromaSDKDevice2DEnum` as an integer, respective to the `deviceType`. Returns the animation id upon success. Returns -1 upon failure.

```C++
EXPORT_API int PluginCreateAnimation(const char* path, int deviceType, int device);
```

Saves a `Chroma` animation file with the `.chroma` extension at the given path. Returns the animation id upon success. Returns -1 upon failure.


<a name="PluginCreateAnimationInMemory"></a>
**PluginCreateAnimationInMemory**

Creates a `Chroma` animation in memory without creating a file. The `deviceType` parameter uses `EChromaSDKDeviceTypeEnum` as an integer. The `device` parameter uses `EChromaSDKDevice1DEnum` or `EChromaSDKDevice2DEnum` as an integer, respective to the `deviceType`. Returns the animation id upon success. Returns -1 upon failure.

```C++
EXPORT_API int PluginCreateAnimationInMemory(int deviceType, int device);
```

Returns the animation id upon success. Returns -1 upon failure.


<a name="PluginSaveAnimation"></a>
**PluginSaveAnimation**

```C++
EXPORT_API int PluginSaveAnimation(int animationId, const char* path);
```


<a name="PluginResetAnimation"></a>
**PluginResetAnimation**

Resets the `Chroma` animation to 1 blank frame. Returns the animation id upon success. Returns -1 upon failure.

```C++
EXPORT_API int PluginResetAnimation(int animationId);
```


<a name="PluginSetDevice"></a>
**PluginSetDevice**

Changes the `deviceType` and `device` of a `Chroma` animation. If the device is changed, the `Chroma` animation will be reset with 1 blank frame. Returns the animation id upon success. Returns -1 upon failure.

```C++
EXPORT_API int PluginSetDevice(int animationId, int deviceType, int device);
```


<a name="PluginAddFrame"></a>
**PluginAddFrame**

Adds a frame to the `Chroma` animation and sets the `duration` (in seconds). The `color` is expected to be an array of the dimensions for the `deviceType/device`. The `length` parameter is the size of the `color` array. For `EChromaSDKDevice1DEnum` the array size should be `MAX LEDS`. For `EChromaSDKDevice2DEnum` the array size should be `MAX ROW` * `MAX COLUMN`. Returns the animation id upon success. Returns -1 upon failure.

```C++
EXPORT_API int PluginAddFrame(int animationId, float duration, int* colors, int length);
```


<a name="PluginUpdateFrame"></a>
**PluginUpdateFrame**

Updates the `frameIndex` of the `Chroma` animation and sets the `duration` (in seconds). The `color` is expected to be an array of the dimensions for the `deviceType/device`. The `length` parameter is the size of the `color` array. For `EChromaSDKDevice1DEnum` the array size should be `MAX LEDS`. For `EChromaSDKDevice2DEnum` the array size should be `MAX ROW` * `MAX COLUMN`. Returns the animation id upon success. Returns -1 upon failure.

```C++
EXPORT_API int PluginUpdateFrame(int animationId, int frameIndex,
    float duration, int* colors, int length);
```


<a name="PluginGetFrame"></a>
**PluginGetFrame**

Gets the frame colors and duration (in seconds) for a `Chroma` animation. The `color` is expected to be an array of the expected dimensions for the `deviceType/device`. The `length` parameter is the size of the `color` array. For `EChromaSDKDevice1DEnum` the array size should be `MAX LEDS`. For `EChromaSDKDevice2DEnum` the array size should be `MAX ROW` * `MAX COLUMN`. Returns the animation id upon success. Returns -1 upon failure. 

```C++
EXPORT_API int PluginGetFrame(int animationId, int frameIndex, float* duration, int* colors, int length)
```


<a name="PluginPreviewFrame"></a>
**PluginPreviewFrame**

Displays the `Chroma` animation frame on `Chroma` hardware given the `frameIndex`. Returns the animation id upon success. Returns -1 upon failure.

```C++
EXPORT_API int PluginPreviewFrame(int animationId, int frameIndex);
```


<a name="PluginOverrideFrameDuration"></a>
**PluginOverrideFrameDuration**

Sets the `duration` for all grames in the `Chroma` animation to the `duration` parameter. Returns the animation id upon success. Returns -1 upon failure.

```C++
EXPORT_API int PluginOverrideFrameDuration(int animationId, float duration);
```


<a name="PluginReverse"></a>
**PluginReverse**

Reverses the animation frame order of the `Chroma` animation. Returns the animation id upon success. Returns -1 upon failure.

```C++
EXPORT_API int PluginReverse(int animationId);
```


<a name="PluginMirrorHorizontally"></a>
**PluginMirrorHorizontally**

Flips the color grid horizontally for all `Chroma` animation frames. Returns the animation id upon success. Returns -1 upon failure.

```C++
EXPORT_API int PluginMirrorHorizontally(int animationId);
```


<a name="PluginMirrorVertically"></a>
**PluginMirrorVertically**

Flips the color grid vertically for all `Chroma` animation frames. This method has no effect for `EChromaSDKDevice1DEnum` devices. Returns the animation id upon success. Returns -1 upon failure.

```C++
EXPORT_API int PluginMirrorVertically(int animationId);
```


<a name="file-format"></a>
## File Format

**Version: (int)**

**EChromaSDKDeviceTypeEnum: (byte)**

```c++
enum EChromaSDKDeviceTypeEnum
{
    DE_1D = 0,
    DE_2D,
};
```

* Depending on the `EChromaSDKDeviceTypeEnum`, the file will use either the `1D` or `2D` file format.

**1D File Format**

**EChromaSDKDevice1DEnum: (byte)**

```c++
enum EChromaSDKDevice1DEnum
{
    DE_ChromaLink = 0,
    DE_Headset,
    DE_Mousepad,
};
```

**Frame Count: (unsigned int)**

**Frames: (FChromaSDKColorFrame1D[])**

```c++
struct FChromaSDKColorFrame1D
{
    float Duration;
    std::vector<COLORREF> Colors;
};
```

**Duration: (float)**

**Color Array: (int[])**


**2D File Format**

**EChromaSDKDevice2DEnum: (byte)**

```c++
enum EChromaSDKDevice2DEnum
{
    DE_Keyboard = 0,
    DE_Keypad,
    DE_Mouse,
};
```

**Frame Count: (unsigned int)**

**Frames: (FChromaSDKColorFrame2D[])**

```c++
struct FChromaSDKColors
{
    std::vector<COLORREF> Colors;
};
```

```c++
struct FChromaSDKColorFrame2D
{
    float Duration;
    std::vector<FChromaSDKColors> Colors;
};
```

**Duration: (float)**

**Color Array: (int[][])**
