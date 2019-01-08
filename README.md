# CChromaEditor - C++ Native MFC Library for playing and editing Chroma animations

**Table of Contents**

* [See Also](#see-also)
* [Frameworks supported](#frameworks-supported)
* [Prerequisites](#prerequisites)
* [Assets](#assets)
* [Dialog](dialog)
* [API](#api)
* [File Format](#file-format)

<a name="see-also"></a>
## See Also

**Apps:**

- [ChromaClientForDiscord](https://github.com/tgraupmann/ChromaDiscordApp) - Add Chroma lighting to the Discord App events

- [ChromaClientForMixer](https://github.com/tgraupmann/ChromaClientForMixer) - Add Chroma lighting to the Mixer streaming experience

- [ChromaClientForTwitch](https://github.com/tgraupmann/ChromaTwitchExtension) - Add Chroma lighting to the Twitch streaming experience

**Plugins:**

- [CChromaEditor](https://github.com/RazerOfficial/CChromaEditor) - C++ native MFC library for playing and editing Chroma animations

- [GameMakerChromaExtension](https://github.com/RazerOfficial/GameMakerChromaExtension) - GameMaker extension to control lighting for Razer Chroma

- [HTML5ChromaSDK](https://github.com/RazerOfficial/HTML5ChromaSDK) - JavaScript library for playing Chroma animations

- [UE4ChromaSDKRT](https://github.com/RazerOfficial/UE4ChromaSDKRT) - UE4 runtime module with Blueprint library for the ChromaSDK

- [UnityNativeChromaSDK](https://github.com/RazerOfficial/UnityNativeChromaSDK) - Unity native library for the ChromaSDK

<a name="frameworks-supported"></a>
## Frameworks supported
- Windows ChromaSDK (32-bit)

- Windows ChromaSDK (64-bit)

<a name="prerequisites"></a>
## Prerequisites

- Install [Synapse](http://developer.razerzone.com/works-with-chroma/download/)

- Synapse will install the Chroma SDK when a Chroma enabled device is connected

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

<a name="dialog"></a>
## Dialog

![image_1](images/image_1.png)

**File Menu**

![image_3](images/image_3.png)

**New**

Start with a new animationName

**Open**

Open a file dialog and open a `Chroma` animation

**Save**

Save the open animation

**Save As**

Open a file dialog and save the open animation

**Import Menu**

![image_4](images/image_4.png)

**Import Image**

Import a BMP, JPG, or PNG texture into the grid layout. The images will be stretched to fit the grid.

**Import Animation**

Import a GIF animation into the grid layout. Multiple frames will be added if they exist in the GIF. The image will be stretched to fit the grid.
<br/>

<a name="api"></a>
## API

The API has various methods with the `D` suffix where `double` return-type/parameters were used. This is to support engines like `GameMaker` which have a limited number of data-types.

Methods:

* [PluginAddFrame](#PluginAddFrame)
* [PluginAddNonZeroAllKeysAllFrames](#PluginAddNonZeroAllKeysAllFrames)
* [PluginAddNonZeroAllKeysAllFramesName](#PluginAddNonZeroAllKeysAllFramesName)
* [PluginAddNonZeroAllKeysAllFramesNameD](#PluginAddNonZeroAllKeysAllFramesNameD)
* [PluginAddNonZeroAllKeysAllFramesOffset](#PluginAddNonZeroAllKeysAllFramesOffset)
* [PluginAddNonZeroAllKeysAllFramesOffsetName](#PluginAddNonZeroAllKeysAllFramesOffsetName)
* [PluginAddNonZeroAllKeysAllFramesOffsetNameD](#PluginAddNonZeroAllKeysAllFramesOffsetNameD)
* [PluginAddNonZeroAllKeysOffset](#PluginAddNonZeroAllKeysOffset)
* [PluginAddNonZeroAllKeysOffsetName](#PluginAddNonZeroAllKeysOffsetName)
* [PluginAddNonZeroAllKeysOffsetNameD](#PluginAddNonZeroAllKeysOffsetNameD)
* [PluginAddNonZeroTargetAllKeysAllFrames](#PluginAddNonZeroTargetAllKeysAllFrames)
* [PluginAddNonZeroTargetAllKeysAllFramesName](#PluginAddNonZeroTargetAllKeysAllFramesName)
* [PluginAddNonZeroTargetAllKeysAllFramesNameD](#PluginAddNonZeroTargetAllKeysAllFramesNameD)
* [PluginAddNonZeroTargetAllKeysAllFramesOffset](#PluginAddNonZeroTargetAllKeysAllFramesOffset)
* [PluginAddNonZeroTargetAllKeysAllFramesOffsetName](#PluginAddNonZeroTargetAllKeysAllFramesOffsetName)
* [PluginAddNonZeroTargetAllKeysAllFramesOffsetNameD](#PluginAddNonZeroTargetAllKeysAllFramesOffsetNameD)
* [PluginAddNonZeroTargetAllKeysOffset](#PluginAddNonZeroTargetAllKeysOffset)
* [PluginAddNonZeroTargetAllKeysOffsetName](#PluginAddNonZeroTargetAllKeysOffsetName)
* [PluginAddNonZeroTargetAllKeysOffsetNameD](#PluginAddNonZeroTargetAllKeysOffsetNameD)
* [PluginAppendAllFrames](#PluginAppendAllFrames)
* [PluginAppendAllFramesName](#PluginAppendAllFramesName)
* [PluginAppendAllFramesNameD](#PluginAppendAllFramesNameD)
* [PluginClearAll](#PluginClearAll)
* [PluginClearAnimationType](#PluginClearAnimationType)
* [PluginCloseAll](#PluginCloseAll)
* [PluginCloseAnimation](#PluginCloseAnimation)
* [PluginCloseAnimationD](#PluginCloseAnimationD)
* [PluginCloseAnimationName](#PluginCloseAnimationName)
* [PluginCloseAnimationNameD](#PluginCloseAnimationNameD)
* [PluginCloseComposite](#PluginCloseComposite)
* [PluginCloseCompositeD](#PluginCloseCompositeD)
* [PluginCopyAnimation](#PluginCopyAnimation)
* [PluginCopyAnimationName](#PluginCopyAnimationName)
* [PluginCopyAnimationNameD](#PluginCopyAnimationNameD)
* [PluginCopyBlueChannelAllFrames](#PluginCopyBlueChannelAllFrames)
* [PluginCopyBlueChannelAllFramesName](#PluginCopyBlueChannelAllFramesName)
* [PluginCopyBlueChannelAllFramesNameD](#PluginCopyBlueChannelAllFramesNameD)
* [PluginCopyGreenChannelAllFrames](#PluginCopyGreenChannelAllFrames)
* [PluginCopyGreenChannelAllFramesName](#PluginCopyGreenChannelAllFramesName)
* [PluginCopyGreenChannelAllFramesNameD](#PluginCopyGreenChannelAllFramesNameD)
* [PluginCopyKeyColor](#PluginCopyKeyColor)
* [PluginCopyKeyColorAllFrames](#PluginCopyKeyColorAllFrames)
* [PluginCopyKeyColorAllFramesName](#PluginCopyKeyColorAllFramesName)
* [PluginCopyKeyColorAllFramesNameD](#PluginCopyKeyColorAllFramesNameD)
* [PluginCopyKeyColorAllFramesOffset](#PluginCopyKeyColorAllFramesOffset)
* [PluginCopyKeyColorAllFramesOffsetName](#PluginCopyKeyColorAllFramesOffsetName)
* [PluginCopyKeyColorAllFramesOffsetNameD](#PluginCopyKeyColorAllFramesOffsetNameD)
* [PluginCopyKeyColorName](#PluginCopyKeyColorName)
* [PluginCopyKeyColorNameD](#PluginCopyKeyColorNameD)
* [PluginCopyNonZeroAllKeys](#PluginCopyNonZeroAllKeys)
* [PluginCopyNonZeroAllKeysAllFrames](#PluginCopyNonZeroAllKeysAllFrames)
* [PluginCopyNonZeroAllKeysAllFramesName](#PluginCopyNonZeroAllKeysAllFramesName)
* [PluginCopyNonZeroAllKeysAllFramesNameD](#PluginCopyNonZeroAllKeysAllFramesNameD)
* [PluginCopyNonZeroAllKeysAllFramesOffset](#PluginCopyNonZeroAllKeysAllFramesOffset)
* [PluginCopyNonZeroAllKeysAllFramesOffsetName](#PluginCopyNonZeroAllKeysAllFramesOffsetName)
* [PluginCopyNonZeroAllKeysAllFramesOffsetNameD](#PluginCopyNonZeroAllKeysAllFramesOffsetNameD)
* [PluginCopyNonZeroAllKeysName](#PluginCopyNonZeroAllKeysName)
* [PluginCopyNonZeroAllKeysNameD](#PluginCopyNonZeroAllKeysNameD)
* [PluginCopyNonZeroAllKeysOffset](#PluginCopyNonZeroAllKeysOffset)
* [PluginCopyNonZeroAllKeysOffsetName](#PluginCopyNonZeroAllKeysOffsetName)
* [PluginCopyNonZeroAllKeysOffsetNameD](#PluginCopyNonZeroAllKeysOffsetNameD)
* [PluginCopyNonZeroKeyColor](#PluginCopyNonZeroKeyColor)
* [PluginCopyNonZeroKeyColorName](#PluginCopyNonZeroKeyColorName)
* [PluginCopyNonZeroKeyColorNameD](#PluginCopyNonZeroKeyColorNameD)
* [PluginCopyNonZeroTargetAllKeys](#PluginCopyNonZeroTargetAllKeys)
* [PluginCopyNonZeroTargetAllKeysAllFrames](#PluginCopyNonZeroTargetAllKeysAllFrames)
* [PluginCopyNonZeroTargetAllKeysAllFramesName](#PluginCopyNonZeroTargetAllKeysAllFramesName)
* [PluginCopyNonZeroTargetAllKeysAllFramesNameD](#PluginCopyNonZeroTargetAllKeysAllFramesNameD)
* [PluginCopyNonZeroTargetAllKeysAllFramesOffset](#PluginCopyNonZeroTargetAllKeysAllFramesOffset)
* [PluginCopyNonZeroTargetAllKeysAllFramesOffsetName](#PluginCopyNonZeroTargetAllKeysAllFramesOffsetName)
* [PluginCopyNonZeroTargetAllKeysAllFramesOffsetNameD](#PluginCopyNonZeroTargetAllKeysAllFramesOffsetNameD)
* [PluginCopyNonZeroTargetAllKeysName](#PluginCopyNonZeroTargetAllKeysName)
* [PluginCopyNonZeroTargetAllKeysNameD](#PluginCopyNonZeroTargetAllKeysNameD)
* [PluginCopyNonZeroTargetAllKeysOffset](#PluginCopyNonZeroTargetAllKeysOffset)
* [PluginCopyNonZeroTargetAllKeysOffsetName](#PluginCopyNonZeroTargetAllKeysOffsetName)
* [PluginCopyNonZeroTargetAllKeysOffsetNameD](#PluginCopyNonZeroTargetAllKeysOffsetNameD)
* [PluginCopyRedChannelAllFrames](#PluginCopyRedChannelAllFrames)
* [PluginCopyRedChannelAllFramesName](#PluginCopyRedChannelAllFramesName)
* [PluginCopyRedChannelAllFramesNameD](#PluginCopyRedChannelAllFramesNameD)
* [PluginCopyZeroAllKeysAllFrames](#PluginCopyZeroAllKeysAllFrames)
* [PluginCopyZeroAllKeysAllFramesName](#PluginCopyZeroAllKeysAllFramesName)
* [PluginCopyZeroAllKeysAllFramesNameD](#PluginCopyZeroAllKeysAllFramesNameD)
* [PluginCopyZeroAllKeysAllFramesOffset](#PluginCopyZeroAllKeysAllFramesOffset)
* [PluginCopyZeroAllKeysAllFramesOffsetName](#PluginCopyZeroAllKeysAllFramesOffsetName)
* [PluginCopyZeroAllKeysAllFramesOffsetNameD](#PluginCopyZeroAllKeysAllFramesOffsetNameD)
* [PluginCopyZeroKeyColor](#PluginCopyZeroKeyColor)
* [PluginCopyZeroKeyColorName](#PluginCopyZeroKeyColorName)
* [PluginCopyZeroKeyColorNameD](#PluginCopyZeroKeyColorNameD)
* [PluginCopyZeroTargetAllKeysAllFrames](#PluginCopyZeroTargetAllKeysAllFrames)
* [PluginCopyZeroTargetAllKeysAllFramesName](#PluginCopyZeroTargetAllKeysAllFramesName)
* [PluginCopyZeroTargetAllKeysAllFramesNameD](#PluginCopyZeroTargetAllKeysAllFramesNameD)
* [PluginCoreCreateChromaLinkEffect](#PluginCoreCreateChromaLinkEffect)
* [PluginCoreCreateEffect](#PluginCoreCreateEffect)
* [PluginCoreCreateHeadsetEffect](#PluginCoreCreateHeadsetEffect)
* [PluginCoreCreateKeyboardEffect](#PluginCoreCreateKeyboardEffect)
* [PluginCoreCreateKeypadEffect](#PluginCoreCreateKeypadEffect)
* [PluginCoreCreateMouseEffect](#PluginCoreCreateMouseEffect)
* [PluginCoreCreateMousepadEffect](#PluginCoreCreateMousepadEffect)
* [PluginCoreDeleteEffect](#PluginCoreDeleteEffect)
* [PluginCoreInit](#PluginCoreInit)
* [PluginCoreQueryDevice](#PluginCoreQueryDevice)
* [PluginCoreSetEffect](#PluginCoreSetEffect)
* [PluginCoreUnInit](#PluginCoreUnInit)
* [PluginCreateAnimation](#PluginCreateAnimation)
* [PluginCreateAnimationInMemory](#PluginCreateAnimationInMemory)
* [PluginCreateEffect](#PluginCreateEffect)
* [PluginDeleteEffect](#PluginDeleteEffect)
* [PluginDuplicateFirstFrame](#PluginDuplicateFirstFrame)
* [PluginDuplicateFirstFrameName](#PluginDuplicateFirstFrameName)
* [PluginDuplicateFirstFrameNameD](#PluginDuplicateFirstFrameNameD)
* [PluginDuplicateFrames](#PluginDuplicateFrames)
* [PluginDuplicateFramesName](#PluginDuplicateFramesName)
* [PluginDuplicateFramesNameD](#PluginDuplicateFramesNameD)
* [PluginDuplicateMirrorFrames](#PluginDuplicateMirrorFrames)
* [PluginDuplicateMirrorFramesName](#PluginDuplicateMirrorFramesName)
* [PluginDuplicateMirrorFramesNameD](#PluginDuplicateMirrorFramesNameD)
* [PluginFadeEndFrames](#PluginFadeEndFrames)
* [PluginFadeEndFramesName](#PluginFadeEndFramesName)
* [PluginFadeEndFramesNameD](#PluginFadeEndFramesNameD)
* [PluginFadeStartFrames](#PluginFadeStartFrames)
* [PluginFadeStartFramesName](#PluginFadeStartFramesName)
* [PluginFadeStartFramesNameD](#PluginFadeStartFramesNameD)
* [PluginFillColor](#PluginFillColor)
* [PluginFillColorAllFrames](#PluginFillColorAllFrames)
* [PluginFillColorAllFramesName](#PluginFillColorAllFramesName)
* [PluginFillColorAllFramesNameD](#PluginFillColorAllFramesNameD)
* [PluginFillColorAllFramesRGB](#PluginFillColorAllFramesRGB)
* [PluginFillColorAllFramesRGBName](#PluginFillColorAllFramesRGBName)
* [PluginFillColorAllFramesRGBNameD](#PluginFillColorAllFramesRGBNameD)
* [PluginFillColorName](#PluginFillColorName)
* [PluginFillColorNameD](#PluginFillColorNameD)
* [PluginFillColorRGB](#PluginFillColorRGB)
* [PluginFillColorRGBName](#PluginFillColorRGBName)
* [PluginFillColorRGBNameD](#PluginFillColorRGBNameD)
* [PluginFillNonZeroColor](#PluginFillNonZeroColor)
* [PluginFillNonZeroColorAllFrames](#PluginFillNonZeroColorAllFrames)
* [PluginFillNonZeroColorAllFramesName](#PluginFillNonZeroColorAllFramesName)
* [PluginFillNonZeroColorAllFramesNameD](#PluginFillNonZeroColorAllFramesNameD)
* [PluginFillNonZeroColorAllFramesRGB](#PluginFillNonZeroColorAllFramesRGB)
* [PluginFillNonZeroColorAllFramesRGBName](#PluginFillNonZeroColorAllFramesRGBName)
* [PluginFillNonZeroColorAllFramesRGBNameD](#PluginFillNonZeroColorAllFramesRGBNameD)
* [PluginFillNonZeroColorName](#PluginFillNonZeroColorName)
* [PluginFillNonZeroColorNameD](#PluginFillNonZeroColorNameD)
* [PluginFillNonZeroColorRGB](#PluginFillNonZeroColorRGB)
* [PluginFillNonZeroColorRGBName](#PluginFillNonZeroColorRGBName)
* [PluginFillNonZeroColorRGBNameD](#PluginFillNonZeroColorRGBNameD)
* [PluginFillRandomColors](#PluginFillRandomColors)
* [PluginFillRandomColorsAllFrames](#PluginFillRandomColorsAllFrames)
* [PluginFillRandomColorsAllFramesName](#PluginFillRandomColorsAllFramesName)
* [PluginFillRandomColorsAllFramesNameD](#PluginFillRandomColorsAllFramesNameD)
* [PluginFillRandomColorsBlackAndWhite](#PluginFillRandomColorsBlackAndWhite)
* [PluginFillRandomColorsBlackAndWhiteAllFrames](#PluginFillRandomColorsBlackAndWhiteAllFrames)
* [PluginFillRandomColorsBlackAndWhiteAllFramesName](#PluginFillRandomColorsBlackAndWhiteAllFramesName)
* [PluginFillRandomColorsBlackAndWhiteAllFramesNameD](#PluginFillRandomColorsBlackAndWhiteAllFramesNameD)
* [PluginFillRandomColorsBlackAndWhiteName](#PluginFillRandomColorsBlackAndWhiteName)
* [PluginFillRandomColorsBlackAndWhiteNameD](#PluginFillRandomColorsBlackAndWhiteNameD)
* [PluginFillRandomColorsName](#PluginFillRandomColorsName)
* [PluginFillRandomColorsNameD](#PluginFillRandomColorsNameD)
* [PluginFillThresholdColors](#PluginFillThresholdColors)
* [PluginFillThresholdColorsAllFrames](#PluginFillThresholdColorsAllFrames)
* [PluginFillThresholdColorsAllFramesName](#PluginFillThresholdColorsAllFramesName)
* [PluginFillThresholdColorsAllFramesNameD](#PluginFillThresholdColorsAllFramesNameD)
* [PluginFillThresholdColorsAllFramesRGB](#PluginFillThresholdColorsAllFramesRGB)
* [PluginFillThresholdColorsAllFramesRGBName](#PluginFillThresholdColorsAllFramesRGBName)
* [PluginFillThresholdColorsAllFramesRGBNameD](#PluginFillThresholdColorsAllFramesRGBNameD)
* [PluginFillThresholdColorsMinMaxAllFramesRGB](#PluginFillThresholdColorsMinMaxAllFramesRGB)
* [PluginFillThresholdColorsMinMaxAllFramesRGBName](#PluginFillThresholdColorsMinMaxAllFramesRGBName)
* [PluginFillThresholdColorsMinMaxAllFramesRGBNameD](#PluginFillThresholdColorsMinMaxAllFramesRGBNameD)
* [PluginFillThresholdColorsMinMaxRGB](#PluginFillThresholdColorsMinMaxRGB)
* [PluginFillThresholdColorsMinMaxRGBName](#PluginFillThresholdColorsMinMaxRGBName)
* [PluginFillThresholdColorsMinMaxRGBNameD](#PluginFillThresholdColorsMinMaxRGBNameD)
* [PluginFillThresholdColorsName](#PluginFillThresholdColorsName)
* [PluginFillThresholdColorsNameD](#PluginFillThresholdColorsNameD)
* [PluginFillThresholdColorsRGB](#PluginFillThresholdColorsRGB)
* [PluginFillThresholdColorsRGBName](#PluginFillThresholdColorsRGBName)
* [PluginFillThresholdColorsRGBNameD](#PluginFillThresholdColorsRGBNameD)
* [PluginFillThresholdRGBColorsAllFramesRGB](#PluginFillThresholdRGBColorsAllFramesRGB)
* [PluginFillThresholdRGBColorsAllFramesRGBName](#PluginFillThresholdRGBColorsAllFramesRGBName)
* [PluginFillThresholdRGBColorsAllFramesRGBNameD](#PluginFillThresholdRGBColorsAllFramesRGBNameD)
* [PluginFillThresholdRGBColorsRGB](#PluginFillThresholdRGBColorsRGB)
* [PluginFillThresholdRGBColorsRGBName](#PluginFillThresholdRGBColorsRGBName)
* [PluginFillThresholdRGBColorsRGBNameD](#PluginFillThresholdRGBColorsRGBNameD)
* [PluginFillZeroColor](#PluginFillZeroColor)
* [PluginFillZeroColorAllFrames](#PluginFillZeroColorAllFrames)
* [PluginFillZeroColorAllFramesName](#PluginFillZeroColorAllFramesName)
* [PluginFillZeroColorAllFramesNameD](#PluginFillZeroColorAllFramesNameD)
* [PluginFillZeroColorAllFramesRGB](#PluginFillZeroColorAllFramesRGB)
* [PluginFillZeroColorAllFramesRGBName](#PluginFillZeroColorAllFramesRGBName)
* [PluginFillZeroColorAllFramesRGBNameD](#PluginFillZeroColorAllFramesRGBNameD)
* [PluginFillZeroColorName](#PluginFillZeroColorName)
* [PluginFillZeroColorNameD](#PluginFillZeroColorNameD)
* [PluginFillZeroColorRGB](#PluginFillZeroColorRGB)
* [PluginFillZeroColorRGBName](#PluginFillZeroColorRGBName)
* [PluginFillZeroColorRGBNameD](#PluginFillZeroColorRGBNameD)
* [PluginGet1DColor](#PluginGet1DColor)
* [PluginGet1DColorName](#PluginGet1DColorName)
* [PluginGet1DColorNameD](#PluginGet1DColorNameD)
* [PluginGet2DColor](#PluginGet2DColor)
* [PluginGet2DColorName](#PluginGet2DColorName)
* [PluginGet2DColorNameD](#PluginGet2DColorNameD)
* [PluginGetAnimation](#PluginGetAnimation)
* [PluginGetAnimationCount](#PluginGetAnimationCount)
* [PluginGetAnimationD](#PluginGetAnimationD)
* [PluginGetAnimationId](#PluginGetAnimationId)
* [PluginGetAnimationName](#PluginGetAnimationName)
* [PluginGetCurrentFrame](#PluginGetCurrentFrame)
* [PluginGetCurrentFrameName](#PluginGetCurrentFrameName)
* [PluginGetCurrentFrameNameD](#PluginGetCurrentFrameNameD)
* [PluginGetDevice](#PluginGetDevice)
* [PluginGetDeviceName](#PluginGetDeviceName)
* [PluginGetDeviceNameD](#PluginGetDeviceNameD)
* [PluginGetDeviceType](#PluginGetDeviceType)
* [PluginGetDeviceTypeName](#PluginGetDeviceTypeName)
* [PluginGetDeviceTypeNameD](#PluginGetDeviceTypeNameD)
* [PluginGetFrame](#PluginGetFrame)
* [PluginGetFrameCount](#PluginGetFrameCount)
* [PluginGetFrameCountName](#PluginGetFrameCountName)
* [PluginGetFrameCountNameD](#PluginGetFrameCountNameD)
* [PluginGetKeyColor](#PluginGetKeyColor)
* [PluginGetKeyColorD](#PluginGetKeyColorD)
* [PluginGetKeyColorName](#PluginGetKeyColorName)
* [PluginGetMaxColumn](#PluginGetMaxColumn)
* [PluginGetMaxColumnD](#PluginGetMaxColumnD)
* [PluginGetMaxLeds](#PluginGetMaxLeds)
* [PluginGetMaxLedsD](#PluginGetMaxLedsD)
* [PluginGetMaxRow](#PluginGetMaxRow)
* [PluginGetMaxRowD](#PluginGetMaxRowD)
* [PluginGetPlayingAnimationCount](#PluginGetPlayingAnimationCount)
* [PluginGetPlayingAnimationId](#PluginGetPlayingAnimationId)
* [PluginGetRGB](#PluginGetRGB)
* [PluginGetRGBD](#PluginGetRGBD)
* [PluginHasAnimationLoop](#PluginHasAnimationLoop)
* [PluginHasAnimationLoopName](#PluginHasAnimationLoopName)
* [PluginHasAnimationLoopNameD](#PluginHasAnimationLoopNameD)
* [PluginInit](#PluginInit)
* [PluginInitD](#PluginInitD)
* [PluginInsertDelay](#PluginInsertDelay)
* [PluginInsertDelayName](#PluginInsertDelayName)
* [PluginInsertDelayNameD](#PluginInsertDelayNameD)
* [PluginInsertFrame](#PluginInsertFrame)
* [PluginInsertFrameName](#PluginInsertFrameName)
* [PluginInsertFrameNameD](#PluginInsertFrameNameD)
* [PluginInvertColors](#PluginInvertColors)
* [PluginInvertColorsAllFrames](#PluginInvertColorsAllFrames)
* [PluginInvertColorsAllFramesName](#PluginInvertColorsAllFramesName)
* [PluginInvertColorsAllFramesNameD](#PluginInvertColorsAllFramesNameD)
* [PluginInvertColorsName](#PluginInvertColorsName)
* [PluginInvertColorsNameD](#PluginInvertColorsNameD)
* [PluginIsAnimationPaused](#PluginIsAnimationPaused)
* [PluginIsAnimationPausedName](#PluginIsAnimationPausedName)
* [PluginIsAnimationPausedNameD](#PluginIsAnimationPausedNameD)
* [PluginIsDialogOpen](#PluginIsDialogOpen)
* [PluginIsDialogOpenD](#PluginIsDialogOpenD)
* [PluginIsInitialized](#PluginIsInitialized)
* [PluginIsInitializedD](#PluginIsInitializedD)
* [PluginIsPlatformSupported](#PluginIsPlatformSupported)
* [PluginIsPlatformSupportedD](#PluginIsPlatformSupportedD)
* [PluginIsPlaying](#PluginIsPlaying)
* [PluginIsPlayingD](#PluginIsPlayingD)
* [PluginIsPlayingName](#PluginIsPlayingName)
* [PluginIsPlayingNameD](#PluginIsPlayingNameD)
* [PluginIsPlayingType](#PluginIsPlayingType)
* [PluginIsPlayingTypeD](#PluginIsPlayingTypeD)
* [PluginLerp](#PluginLerp)
* [PluginLerpColor](#PluginLerpColor)
* [PluginLoadAnimation](#PluginLoadAnimation)
* [PluginLoadAnimationD](#PluginLoadAnimationD)
* [PluginLoadAnimationName](#PluginLoadAnimationName)
* [PluginLoadComposite](#PluginLoadComposite)
* [PluginMakeBlankFrames](#PluginMakeBlankFrames)
* [PluginMakeBlankFramesName](#PluginMakeBlankFramesName)
* [PluginMakeBlankFramesNameD](#PluginMakeBlankFramesNameD)
* [PluginMakeBlankFramesRandom](#PluginMakeBlankFramesRandom)
* [PluginMakeBlankFramesRandomBlackAndWhite](#PluginMakeBlankFramesRandomBlackAndWhite)
* [PluginMakeBlankFramesRandomBlackAndWhiteName](#PluginMakeBlankFramesRandomBlackAndWhiteName)
* [PluginMakeBlankFramesRandomBlackAndWhiteNameD](#PluginMakeBlankFramesRandomBlackAndWhiteNameD)
* [PluginMakeBlankFramesRandomName](#PluginMakeBlankFramesRandomName)
* [PluginMakeBlankFramesRandomNameD](#PluginMakeBlankFramesRandomNameD)
* [PluginMakeBlankFramesRGB](#PluginMakeBlankFramesRGB)
* [PluginMakeBlankFramesRGBName](#PluginMakeBlankFramesRGBName)
* [PluginMakeBlankFramesRGBNameD](#PluginMakeBlankFramesRGBNameD)
* [PluginMirrorHorizontally](#PluginMirrorHorizontally)
* [PluginMirrorVertically](#PluginMirrorVertically)
* [PluginMultiplyColorLerpAllFrames](#PluginMultiplyColorLerpAllFrames)
* [PluginMultiplyColorLerpAllFramesName](#PluginMultiplyColorLerpAllFramesName)
* [PluginMultiplyColorLerpAllFramesNameD](#PluginMultiplyColorLerpAllFramesNameD)
* [PluginMultiplyIntensity](#PluginMultiplyIntensity)
* [PluginMultiplyIntensityAllFrames](#PluginMultiplyIntensityAllFrames)
* [PluginMultiplyIntensityAllFramesName](#PluginMultiplyIntensityAllFramesName)
* [PluginMultiplyIntensityAllFramesNameD](#PluginMultiplyIntensityAllFramesNameD)
* [PluginMultiplyIntensityAllFramesRGB](#PluginMultiplyIntensityAllFramesRGB)
* [PluginMultiplyIntensityAllFramesRGBName](#PluginMultiplyIntensityAllFramesRGBName)
* [PluginMultiplyIntensityAllFramesRGBNameD](#PluginMultiplyIntensityAllFramesRGBNameD)
* [PluginMultiplyIntensityColor](#PluginMultiplyIntensityColor)
* [PluginMultiplyIntensityColorAllFrames](#PluginMultiplyIntensityColorAllFrames)
* [PluginMultiplyIntensityColorAllFramesName](#PluginMultiplyIntensityColorAllFramesName)
* [PluginMultiplyIntensityColorAllFramesNameD](#PluginMultiplyIntensityColorAllFramesNameD)
* [PluginMultiplyIntensityColorName](#PluginMultiplyIntensityColorName)
* [PluginMultiplyIntensityColorNameD](#PluginMultiplyIntensityColorNameD)
* [PluginMultiplyIntensityName](#PluginMultiplyIntensityName)
* [PluginMultiplyIntensityNameD](#PluginMultiplyIntensityNameD)
* [PluginMultiplyIntensityRGB](#PluginMultiplyIntensityRGB)
* [PluginMultiplyIntensityRGBName](#PluginMultiplyIntensityRGBName)
* [PluginMultiplyIntensityRGBNameD](#PluginMultiplyIntensityRGBNameD)
* [PluginMultiplyNonZeroTargetColorLerp](#PluginMultiplyNonZeroTargetColorLerp)
* [PluginMultiplyNonZeroTargetColorLerpAllFrames](#PluginMultiplyNonZeroTargetColorLerpAllFrames)
* [PluginMultiplyNonZeroTargetColorLerpAllFramesName](#PluginMultiplyNonZeroTargetColorLerpAllFramesName)
* [PluginMultiplyNonZeroTargetColorLerpAllFramesNameD](#PluginMultiplyNonZeroTargetColorLerpAllFramesNameD)
* [PluginMultiplyNonZeroTargetColorLerpAllFramesRGB](#PluginMultiplyNonZeroTargetColorLerpAllFramesRGB)
* [PluginMultiplyNonZeroTargetColorLerpAllFramesRGBName](#PluginMultiplyNonZeroTargetColorLerpAllFramesRGBName)
* [PluginMultiplyNonZeroTargetColorLerpAllFramesRGBNameD](#PluginMultiplyNonZeroTargetColorLerpAllFramesRGBNameD)
* [PluginMultiplyTargetColorLerp](#PluginMultiplyTargetColorLerp)
* [PluginMultiplyTargetColorLerpAllFrames](#PluginMultiplyTargetColorLerpAllFrames)
* [PluginMultiplyTargetColorLerpAllFramesName](#PluginMultiplyTargetColorLerpAllFramesName)
* [PluginMultiplyTargetColorLerpAllFramesNameD](#PluginMultiplyTargetColorLerpAllFramesNameD)
* [PluginMultiplyTargetColorLerpAllFramesRGB](#PluginMultiplyTargetColorLerpAllFramesRGB)
* [PluginMultiplyTargetColorLerpAllFramesRGBName](#PluginMultiplyTargetColorLerpAllFramesRGBName)
* [PluginMultiplyTargetColorLerpAllFramesRGBNameD](#PluginMultiplyTargetColorLerpAllFramesRGBNameD)
* [PluginOffsetColors](#PluginOffsetColors)
* [PluginOffsetColorsAllFrames](#PluginOffsetColorsAllFrames)
* [PluginOffsetColorsAllFramesName](#PluginOffsetColorsAllFramesName)
* [PluginOffsetColorsAllFramesNameD](#PluginOffsetColorsAllFramesNameD)
* [PluginOffsetColorsName](#PluginOffsetColorsName)
* [PluginOffsetColorsNameD](#PluginOffsetColorsNameD)
* [PluginOffsetNonZeroColors](#PluginOffsetNonZeroColors)
* [PluginOffsetNonZeroColorsAllFrames](#PluginOffsetNonZeroColorsAllFrames)
* [PluginOffsetNonZeroColorsAllFramesName](#PluginOffsetNonZeroColorsAllFramesName)
* [PluginOffsetNonZeroColorsAllFramesNameD](#PluginOffsetNonZeroColorsAllFramesNameD)
* [PluginOffsetNonZeroColorsName](#PluginOffsetNonZeroColorsName)
* [PluginOffsetNonZeroColorsNameD](#PluginOffsetNonZeroColorsNameD)
* [PluginOpenAnimation](#PluginOpenAnimation)
* [PluginOpenAnimationD](#PluginOpenAnimationD)
* [PluginOpenEditorDialog](#PluginOpenEditorDialog)
* [PluginOpenEditorDialogAndPlay](#PluginOpenEditorDialogAndPlay)
* [PluginOpenEditorDialogAndPlayD](#PluginOpenEditorDialogAndPlayD)
* [PluginOpenEditorDialogD](#PluginOpenEditorDialogD)
* [PluginOverrideFrameDuration](#PluginOverrideFrameDuration)
* [PluginOverrideFrameDurationD](#PluginOverrideFrameDurationD)
* [PluginOverrideFrameDurationName](#PluginOverrideFrameDurationName)
* [PluginPauseAnimation](#PluginPauseAnimation)
* [PluginPauseAnimationName](#PluginPauseAnimationName)
* [PluginPauseAnimationNameD](#PluginPauseAnimationNameD)
* [PluginPlayAnimation](#PluginPlayAnimation)
* [PluginPlayAnimationD](#PluginPlayAnimationD)
* [PluginPlayAnimationFrame](#PluginPlayAnimationFrame)
* [PluginPlayAnimationFrameName](#PluginPlayAnimationFrameName)
* [PluginPlayAnimationFrameNameD](#PluginPlayAnimationFrameNameD)
* [PluginPlayAnimationLoop](#PluginPlayAnimationLoop)
* [PluginPlayAnimationName](#PluginPlayAnimationName)
* [PluginPlayAnimationNameD](#PluginPlayAnimationNameD)
* [PluginPlayComposite](#PluginPlayComposite)
* [PluginPlayCompositeD](#PluginPlayCompositeD)
* [PluginPreviewFrame](#PluginPreviewFrame)
* [PluginPreviewFrameD](#PluginPreviewFrameD)
* [PluginPreviewFrameName](#PluginPreviewFrameName)
* [PluginReduceFrames](#PluginReduceFrames)
* [PluginReduceFramesName](#PluginReduceFramesName)
* [PluginReduceFramesNameD](#PluginReduceFramesNameD)
* [PluginResetAnimation](#PluginResetAnimation)
* [PluginResumeAnimation](#PluginResumeAnimation)
* [PluginResumeAnimationName](#PluginResumeAnimationName)
* [PluginResumeAnimationNameD](#PluginResumeAnimationNameD)
* [PluginReverse](#PluginReverse)
* [PluginReverseAllFrames](#PluginReverseAllFrames)
* [PluginReverseAllFramesName](#PluginReverseAllFramesName)
* [PluginReverseAllFramesNameD](#PluginReverseAllFramesNameD)
* [PluginSaveAnimation](#PluginSaveAnimation)
* [PluginSaveAnimationName](#PluginSaveAnimationName)
* [PluginSet1DColor](#PluginSet1DColor)
* [PluginSet1DColorName](#PluginSet1DColorName)
* [PluginSet1DColorNameD](#PluginSet1DColorNameD)
* [PluginSet2DColor](#PluginSet2DColor)
* [PluginSet2DColorName](#PluginSet2DColorName)
* [PluginSet2DColorNameD](#PluginSet2DColorNameD)
* [PluginSetChromaCustomColorAllFrames](#PluginSetChromaCustomColorAllFrames)
* [PluginSetChromaCustomColorAllFramesName](#PluginSetChromaCustomColorAllFramesName)
* [PluginSetChromaCustomColorAllFramesNameD](#PluginSetChromaCustomColorAllFramesNameD)
* [PluginSetChromaCustomFlag](#PluginSetChromaCustomFlag)
* [PluginSetChromaCustomFlagName](#PluginSetChromaCustomFlagName)
* [PluginSetChromaCustomFlagNameD](#PluginSetChromaCustomFlagNameD)
* [PluginSetCurrentFrame](#PluginSetCurrentFrame)
* [PluginSetCurrentFrameName](#PluginSetCurrentFrameName)
* [PluginSetCurrentFrameNameD](#PluginSetCurrentFrameNameD)
* [PluginSetDevice](#PluginSetDevice)
* [PluginSetEffect](#PluginSetEffect)
* [PluginSetKeyColor](#PluginSetKeyColor)
* [PluginSetKeyColorAllFrames](#PluginSetKeyColorAllFrames)
* [PluginSetKeyColorAllFramesName](#PluginSetKeyColorAllFramesName)
* [PluginSetKeyColorAllFramesNameD](#PluginSetKeyColorAllFramesNameD)
* [PluginSetKeyColorAllFramesRGB](#PluginSetKeyColorAllFramesRGB)
* [PluginSetKeyColorAllFramesRGBName](#PluginSetKeyColorAllFramesRGBName)
* [PluginSetKeyColorAllFramesRGBNameD](#PluginSetKeyColorAllFramesRGBNameD)
* [PluginSetKeyColorName](#PluginSetKeyColorName)
* [PluginSetKeyColorNameD](#PluginSetKeyColorNameD)
* [PluginSetKeyColorRGB](#PluginSetKeyColorRGB)
* [PluginSetKeyColorRGBName](#PluginSetKeyColorRGBName)
* [PluginSetKeyColorRGBNameD](#PluginSetKeyColorRGBNameD)
* [PluginSetKeyNonZeroColor](#PluginSetKeyNonZeroColor)
* [PluginSetKeyNonZeroColorName](#PluginSetKeyNonZeroColorName)
* [PluginSetKeyNonZeroColorNameD](#PluginSetKeyNonZeroColorNameD)
* [PluginSetKeyNonZeroColorRGB](#PluginSetKeyNonZeroColorRGB)
* [PluginSetKeyNonZeroColorRGBName](#PluginSetKeyNonZeroColorRGBName)
* [PluginSetKeyNonZeroColorRGBNameD](#PluginSetKeyNonZeroColorRGBNameD)
* [PluginSetKeysColor](#PluginSetKeysColor)
* [PluginSetKeysColorAllFrames](#PluginSetKeysColorAllFrames)
* [PluginSetKeysColorAllFramesName](#PluginSetKeysColorAllFramesName)
* [PluginSetKeysColorAllFramesRGB](#PluginSetKeysColorAllFramesRGB)
* [PluginSetKeysColorAllFramesRGBName](#PluginSetKeysColorAllFramesRGBName)
* [PluginSetKeysColorName](#PluginSetKeysColorName)
* [PluginSetKeysColorRGB](#PluginSetKeysColorRGB)
* [PluginSetKeysColorRGBName](#PluginSetKeysColorRGBName)
* [PluginSetKeysNonZeroColor](#PluginSetKeysNonZeroColor)
* [PluginSetKeysNonZeroColorAllFrames](#PluginSetKeysNonZeroColorAllFrames)
* [PluginSetKeysNonZeroColorAllFramesName](#PluginSetKeysNonZeroColorAllFramesName)
* [PluginSetKeysNonZeroColorName](#PluginSetKeysNonZeroColorName)
* [PluginSetKeysNonZeroColorRGB](#PluginSetKeysNonZeroColorRGB)
* [PluginSetKeysNonZeroColorRGBName](#PluginSetKeysNonZeroColorRGBName)
* [PluginSetKeysZeroColor](#PluginSetKeysZeroColor)
* [PluginSetKeysZeroColorAllFrames](#PluginSetKeysZeroColorAllFrames)
* [PluginSetKeysZeroColorAllFramesName](#PluginSetKeysZeroColorAllFramesName)
* [PluginSetKeysZeroColorAllFramesRGB](#PluginSetKeysZeroColorAllFramesRGB)
* [PluginSetKeysZeroColorAllFramesRGBName](#PluginSetKeysZeroColorAllFramesRGBName)
* [PluginSetKeysZeroColorName](#PluginSetKeysZeroColorName)
* [PluginSetKeysZeroColorRGB](#PluginSetKeysZeroColorRGB)
* [PluginSetKeysZeroColorRGBName](#PluginSetKeysZeroColorRGBName)
* [PluginSetKeyZeroColor](#PluginSetKeyZeroColor)
* [PluginSetKeyZeroColorName](#PluginSetKeyZeroColorName)
* [PluginSetKeyZeroColorNameD](#PluginSetKeyZeroColorNameD)
* [PluginSetKeyZeroColorRGB](#PluginSetKeyZeroColorRGB)
* [PluginSetKeyZeroColorRGBName](#PluginSetKeyZeroColorRGBName)
* [PluginSetKeyZeroColorRGBNameD](#PluginSetKeyZeroColorRGBNameD)
* [PluginSetLogDelegate](#PluginSetLogDelegate)
* [PluginStopAll](#PluginStopAll)
* [PluginStopAnimation](#PluginStopAnimation)
* [PluginStopAnimationD](#PluginStopAnimationD)
* [PluginStopAnimationName](#PluginStopAnimationName)
* [PluginStopAnimationNameD](#PluginStopAnimationNameD)
* [PluginStopAnimationType](#PluginStopAnimationType)
* [PluginStopAnimationTypeD](#PluginStopAnimationTypeD)
* [PluginStopComposite](#PluginStopComposite)
* [PluginStopCompositeD](#PluginStopCompositeD)
* [PluginSubtractNonZeroAllKeysAllFrames](#PluginSubtractNonZeroAllKeysAllFrames)
* [PluginSubtractNonZeroAllKeysAllFramesName](#PluginSubtractNonZeroAllKeysAllFramesName)
* [PluginSubtractNonZeroAllKeysAllFramesNameD](#PluginSubtractNonZeroAllKeysAllFramesNameD)
* [PluginSubtractNonZeroAllKeysAllFramesOffset](#PluginSubtractNonZeroAllKeysAllFramesOffset)
* [PluginSubtractNonZeroAllKeysAllFramesOffsetName](#PluginSubtractNonZeroAllKeysAllFramesOffsetName)
* [PluginSubtractNonZeroAllKeysAllFramesOffsetNameD](#PluginSubtractNonZeroAllKeysAllFramesOffsetNameD)
* [PluginSubtractNonZeroAllKeysOffset](#PluginSubtractNonZeroAllKeysOffset)
* [PluginSubtractNonZeroAllKeysOffsetName](#PluginSubtractNonZeroAllKeysOffsetName)
* [PluginSubtractNonZeroAllKeysOffsetNameD](#PluginSubtractNonZeroAllKeysOffsetNameD)
* [PluginSubtractNonZeroTargetAllKeysAllFrames](#PluginSubtractNonZeroTargetAllKeysAllFrames)
* [PluginSubtractNonZeroTargetAllKeysAllFramesName](#PluginSubtractNonZeroTargetAllKeysAllFramesName)
* [PluginSubtractNonZeroTargetAllKeysAllFramesNameD](#PluginSubtractNonZeroTargetAllKeysAllFramesNameD)
* [PluginSubtractNonZeroTargetAllKeysAllFramesOffset](#PluginSubtractNonZeroTargetAllKeysAllFramesOffset)
* [PluginSubtractNonZeroTargetAllKeysAllFramesOffsetName](#PluginSubtractNonZeroTargetAllKeysAllFramesOffsetName)
* [PluginSubtractNonZeroTargetAllKeysAllFramesOffsetNameD](#PluginSubtractNonZeroTargetAllKeysAllFramesOffsetNameD)
* [PluginSubtractNonZeroTargetAllKeysOffset](#PluginSubtractNonZeroTargetAllKeysOffset)
* [PluginSubtractNonZeroTargetAllKeysOffsetName](#PluginSubtractNonZeroTargetAllKeysOffsetName)
* [PluginSubtractNonZeroTargetAllKeysOffsetNameD](#PluginSubtractNonZeroTargetAllKeysOffsetNameD)
* [PluginTrimEndFrames](#PluginTrimEndFrames)
* [PluginTrimEndFramesName](#PluginTrimEndFramesName)
* [PluginTrimEndFramesNameD](#PluginTrimEndFramesNameD)
* [PluginTrimFrame](#PluginTrimFrame)
* [PluginTrimFrameName](#PluginTrimFrameName)
* [PluginTrimFrameNameD](#PluginTrimFrameNameD)
* [PluginTrimStartFrames](#PluginTrimStartFrames)
* [PluginTrimStartFramesName](#PluginTrimStartFramesName)
* [PluginTrimStartFramesNameD](#PluginTrimStartFramesNameD)
* [PluginUninit](#PluginUninit)
* [PluginUninitD](#PluginUninitD)
* [PluginUnloadAnimation](#PluginUnloadAnimation)
* [PluginUnloadAnimationD](#PluginUnloadAnimationD)
* [PluginUnloadAnimationName](#PluginUnloadAnimationName)
* [PluginUnloadComposite](#PluginUnloadComposite)
* [PluginUpdateFrame](#PluginUpdateFrame)

---
<a name="PluginAddFrame"></a>
**PluginAddFrame**

Adds a frame to the `Chroma` animation and sets the `duration` (in seconds).
The `color` is expected to be an array of the dimensions for the `deviceType/device`.
The `length` parameter is the size of the `color` array. For `EChromaSDKDevice1DEnum`
the array size should be `MAX LEDS`. For `EChromaSDKDevice2DEnum` the array
size should be `MAX ROW` * `MAX COLUMN`. Returns the animation id upon
success. Returns -1 upon failure.

```C++
// DLL Interface
EXPORT_API int PluginAddFrame(
	int animationId, float duration, int* colors, int length);

// Class Plugin
int result = ChromaAnimationAPI::AddFrame(
	int animationId, float duration, int* colors, int length);
```

---
<a name="PluginAddNonZeroAllKeysAllFrames"></a>
**PluginAddNonZeroAllKeysAllFrames**

```C++
// DLL Interface
EXPORT_API void PluginAddNonZeroAllKeysAllFrames(
	int sourceAnimationId, int targetAnimationId);

// Class Plugin
ChromaAnimationAPI::AddNonZeroAllKeysAllFrames(
	int sourceAnimationId, int targetAnimationId);
```

---
<a name="PluginAddNonZeroAllKeysAllFramesName"></a>
**PluginAddNonZeroAllKeysAllFramesName**

```C++
// DLL Interface
EXPORT_API void PluginAddNonZeroAllKeysAllFramesName(
	const char* sourceAnimation, const char* targetAnimation);

// Class Plugin
ChromaAnimationAPI::AddNonZeroAllKeysAllFramesName(
	const char* sourceAnimation, const char* targetAnimation);
```

---
<a name="PluginAddNonZeroAllKeysAllFramesNameD"></a>
**PluginAddNonZeroAllKeysAllFramesNameD**

```C++
// DLL Interface
EXPORT_API double PluginAddNonZeroAllKeysAllFramesNameD(
	const char* sourceAnimation, const char* targetAnimation);

// Class Plugin
double result = ChromaAnimationAPI::AddNonZeroAllKeysAllFramesNameD(
	const char* sourceAnimation, const char* targetAnimation);
```

---
<a name="PluginAddNonZeroAllKeysAllFramesOffset"></a>
**PluginAddNonZeroAllKeysAllFramesOffset**

```C++
// DLL Interface
EXPORT_API void PluginAddNonZeroAllKeysAllFramesOffset(
	int sourceAnimationId, int targetAnimationId, int offset);

// Class Plugin
ChromaAnimationAPI::AddNonZeroAllKeysAllFramesOffset(
	int sourceAnimationId, int targetAnimationId, int offset);
```

---
<a name="PluginAddNonZeroAllKeysAllFramesOffsetName"></a>
**PluginAddNonZeroAllKeysAllFramesOffsetName**

```C++
// DLL Interface
EXPORT_API void PluginAddNonZeroAllKeysAllFramesOffsetName(
	const char* sourceAnimation, const char* targetAnimation, int offset);

// Class Plugin
ChromaAnimationAPI::AddNonZeroAllKeysAllFramesOffsetName(
	const char* sourceAnimation, const char* targetAnimation, int offset);
```

---
<a name="PluginAddNonZeroAllKeysAllFramesOffsetNameD"></a>
**PluginAddNonZeroAllKeysAllFramesOffsetNameD**

```C++
// DLL Interface
EXPORT_API double PluginAddNonZeroAllKeysAllFramesOffsetNameD(
	const char* sourceAnimation, const char* targetAnimation, double offset);

// Class Plugin
double result = ChromaAnimationAPI::AddNonZeroAllKeysAllFramesOffsetNameD(
	const char* sourceAnimation, const char* targetAnimation, double offset);
```

---
<a name="PluginAddNonZeroAllKeysOffset"></a>
**PluginAddNonZeroAllKeysOffset**

```C++
// DLL Interface
EXPORT_API void PluginAddNonZeroAllKeysOffset(
	int sourceAnimationId, int targetAnimationId, int frameId, int offset);

// Class Plugin
ChromaAnimationAPI::AddNonZeroAllKeysOffset(
	int sourceAnimationId, int targetAnimationId, int frameId, int offset);
```

---
<a name="PluginAddNonZeroAllKeysOffsetName"></a>
**PluginAddNonZeroAllKeysOffsetName**

```C++
// DLL Interface
EXPORT_API void PluginAddNonZeroAllKeysOffsetName(
	const char* sourceAnimation, const char* targetAnimation, int frameId, int offset);

// Class Plugin
ChromaAnimationAPI::AddNonZeroAllKeysOffsetName(
	const char* sourceAnimation, const char* targetAnimation, int frameId, int offset);
```

---
<a name="PluginAddNonZeroAllKeysOffsetNameD"></a>
**PluginAddNonZeroAllKeysOffsetNameD**

```C++
// DLL Interface
EXPORT_API double PluginAddNonZeroAllKeysOffsetNameD(
	const char* sourceAnimation, const char* targetAnimation, double frameId,
	double offset);

// Class Plugin
double result = ChromaAnimationAPI::AddNonZeroAllKeysOffsetNameD(
	const char* sourceAnimation, const char* targetAnimation, double frameId,
	double offset);
```

---
<a name="PluginAddNonZeroTargetAllKeysAllFrames"></a>
**PluginAddNonZeroTargetAllKeysAllFrames**

```C++
// DLL Interface
EXPORT_API void PluginAddNonZeroTargetAllKeysAllFrames(
	int sourceAnimationId, int targetAnimationId);

// Class Plugin
ChromaAnimationAPI::AddNonZeroTargetAllKeysAllFrames(
	int sourceAnimationId, int targetAnimationId);
```

---
<a name="PluginAddNonZeroTargetAllKeysAllFramesName"></a>
**PluginAddNonZeroTargetAllKeysAllFramesName**

```C++
// DLL Interface
EXPORT_API void PluginAddNonZeroTargetAllKeysAllFramesName(
	const char* sourceAnimation, const char* targetAnimation);

// Class Plugin
ChromaAnimationAPI::AddNonZeroTargetAllKeysAllFramesName(
	const char* sourceAnimation, const char* targetAnimation);
```

---
<a name="PluginAddNonZeroTargetAllKeysAllFramesNameD"></a>
**PluginAddNonZeroTargetAllKeysAllFramesNameD**

```C++
// DLL Interface
EXPORT_API double PluginAddNonZeroTargetAllKeysAllFramesNameD(
	const char* sourceAnimation, const char* targetAnimation);

// Class Plugin
double result = ChromaAnimationAPI::AddNonZeroTargetAllKeysAllFramesNameD(
	const char* sourceAnimation, const char* targetAnimation);
```

---
<a name="PluginAddNonZeroTargetAllKeysAllFramesOffset"></a>
**PluginAddNonZeroTargetAllKeysAllFramesOffset**

```C++
// DLL Interface
EXPORT_API void PluginAddNonZeroTargetAllKeysAllFramesOffset(
	int sourceAnimationId, int targetAnimationId, int offset);

// Class Plugin
ChromaAnimationAPI::AddNonZeroTargetAllKeysAllFramesOffset(
	int sourceAnimationId, int targetAnimationId, int offset);
```

---
<a name="PluginAddNonZeroTargetAllKeysAllFramesOffsetName"></a>
**PluginAddNonZeroTargetAllKeysAllFramesOffsetName**

```C++
// DLL Interface
EXPORT_API void PluginAddNonZeroTargetAllKeysAllFramesOffsetName(
	const char* sourceAnimation, const char* targetAnimation, int offset);

// Class Plugin
ChromaAnimationAPI::AddNonZeroTargetAllKeysAllFramesOffsetName(
	const char* sourceAnimation, const char* targetAnimation, int offset);
```

---
<a name="PluginAddNonZeroTargetAllKeysAllFramesOffsetNameD"></a>
**PluginAddNonZeroTargetAllKeysAllFramesOffsetNameD**

```C++
// DLL Interface
EXPORT_API double PluginAddNonZeroTargetAllKeysAllFramesOffsetNameD(
	const char* sourceAnimation, const char* targetAnimation, double offset);

// Class Plugin
double result = ChromaAnimationAPI::AddNonZeroTargetAllKeysAllFramesOffsetNameD(
	const char* sourceAnimation, const char* targetAnimation, double offset);
```

---
<a name="PluginAddNonZeroTargetAllKeysOffset"></a>
**PluginAddNonZeroTargetAllKeysOffset**

```C++
// DLL Interface
EXPORT_API void PluginAddNonZeroTargetAllKeysOffset(
	int sourceAnimationId, int targetAnimationId, int frameId, int offset);

// Class Plugin
ChromaAnimationAPI::AddNonZeroTargetAllKeysOffset(
	int sourceAnimationId, int targetAnimationId, int frameId, int offset);
```

---
<a name="PluginAddNonZeroTargetAllKeysOffsetName"></a>
**PluginAddNonZeroTargetAllKeysOffsetName**

```C++
// DLL Interface
EXPORT_API void PluginAddNonZeroTargetAllKeysOffsetName(
	const char* sourceAnimation, const char* targetAnimation, int frameId, int offset);

// Class Plugin
ChromaAnimationAPI::AddNonZeroTargetAllKeysOffsetName(
	const char* sourceAnimation, const char* targetAnimation, int frameId, int offset);
```

---
<a name="PluginAddNonZeroTargetAllKeysOffsetNameD"></a>
**PluginAddNonZeroTargetAllKeysOffsetNameD**

```C++
// DLL Interface
EXPORT_API double PluginAddNonZeroTargetAllKeysOffsetNameD(
	const char* sourceAnimation, const char* targetAnimation, double frameId,
	double offset);

// Class Plugin
double result = ChromaAnimationAPI::AddNonZeroTargetAllKeysOffsetNameD(
	const char* sourceAnimation, const char* targetAnimation, double frameId,
	double offset);
```

---
<a name="PluginAppendAllFrames"></a>
**PluginAppendAllFrames**

```C++
// DLL Interface
EXPORT_API void PluginAppendAllFrames(
	int sourceAnimationId, int targetAnimationId);

// Class Plugin
ChromaAnimationAPI::AppendAllFrames(
	int sourceAnimationId, int targetAnimationId);
```

---
<a name="PluginAppendAllFramesName"></a>
**PluginAppendAllFramesName**

```C++
// DLL Interface
EXPORT_API void PluginAppendAllFramesName(
	const char* sourceAnimation, const char* targetAnimation);

// Class Plugin
ChromaAnimationAPI::AppendAllFramesName(
	const char* sourceAnimation, const char* targetAnimation);
```

---
<a name="PluginAppendAllFramesNameD"></a>
**PluginAppendAllFramesNameD**

```C++
// DLL Interface
EXPORT_API double PluginAppendAllFramesNameD(
	const char* sourceAnimation, const char* targetAnimation);

// Class Plugin
double result = ChromaAnimationAPI::AppendAllFramesNameD(
	const char* sourceAnimation, const char* targetAnimation);
```

---
<a name="PluginClearAll"></a>
**PluginClearAll**

`PluginClearAll` will issue a `CLEAR` effect for all devices.

```C++
// DLL Interface
EXPORT_API void PluginClearAll();

// Class Plugin
ChromaAnimationAPI::ClearAll();
```

---
<a name="PluginClearAnimationType"></a>
**PluginClearAnimationType**

`PluginClearAnimationType` will issue a `CLEAR` effect for the given device.

```C++
// DLL Interface
EXPORT_API void PluginClearAnimationType(
	int deviceType, int device);

// Class Plugin
ChromaAnimationAPI::ClearAnimationType(
	int deviceType, int device);
```

---
<a name="PluginCloseAll"></a>
**PluginCloseAll**

`PluginCloseAll` closes all open animations so they can be reloaded from
disk. The set of animations will be stopped if playing.

```C++
// DLL Interface
EXPORT_API void PluginCloseAll();

// Class Plugin
ChromaAnimationAPI::CloseAll();
```

---
<a name="PluginCloseAnimation"></a>
**PluginCloseAnimation**

Closes the `Chroma` animation to free up resources referenced by id. Returns
the animation id upon success. Returns -1 upon failure. This might be used
while authoring effects if there was a change necessitating re-opening
the animation. The animation id can no longer be used once closed.

```C++
// DLL Interface
EXPORT_API int PluginCloseAnimation(int animationId);

// Class Plugin
int result = ChromaAnimationAPI::CloseAnimation(int animationId);
```

---
<a name="PluginCloseAnimationD"></a>
**PluginCloseAnimationD**

```C++
// DLL Interface
EXPORT_API double PluginCloseAnimationD(double animationId);

// Class Plugin
double result = ChromaAnimationAPI::CloseAnimationD(double animationId);
```

---
<a name="PluginCloseAnimationName"></a>
**PluginCloseAnimationName**

Closes the `Chroma` animation referenced by name so that the animation can
be reloaded from disk.

```C++
// DLL Interface
EXPORT_API void PluginCloseAnimationName(const char* path);

// Class Plugin
ChromaAnimationAPI::CloseAnimationName(const char* path);
```

---
<a name="PluginCloseAnimationNameD"></a>
**PluginCloseAnimationNameD**

```C++
// DLL Interface
EXPORT_API double PluginCloseAnimationNameD(const char* path);

// Class Plugin
double result = ChromaAnimationAPI::CloseAnimationNameD(const char* path);
```

---
<a name="PluginCloseComposite"></a>
**PluginCloseComposite**

`PluginCloseComposite` closes a set of animations so they can be reloaded
from disk. The set of animations will be stopped if playing.

```C++
// DLL Interface
EXPORT_API void PluginCloseComposite(const char* name);

// Class Plugin
ChromaAnimationAPI::CloseComposite(const char* name);
```

---
<a name="PluginCloseCompositeD"></a>
**PluginCloseCompositeD**

```C++
// DLL Interface
EXPORT_API double PluginCloseCompositeD(const char* name);

// Class Plugin
double result = ChromaAnimationAPI::CloseCompositeD(const char* name);
```

---
<a name="PluginCopyAnimation"></a>
**PluginCopyAnimation**

```C++
// DLL Interface
EXPORT_API int PluginCopyAnimation(
	int sourceAnimationId, const char* targetAnimation);

// Class Plugin
int result = ChromaAnimationAPI::CopyAnimation(
	int sourceAnimationId, const char* targetAnimation);
```

---
<a name="PluginCopyAnimationName"></a>
**PluginCopyAnimationName**

```C++
// DLL Interface
EXPORT_API void PluginCopyAnimationName(
	const char* sourceAnimation, const char* targetAnimation);

// Class Plugin
ChromaAnimationAPI::CopyAnimationName(
	const char* sourceAnimation, const char* targetAnimation);
```

---
<a name="PluginCopyAnimationNameD"></a>
**PluginCopyAnimationNameD**

```C++
// DLL Interface
EXPORT_API double PluginCopyAnimationNameD(
	const char* sourceAnimation, const char* targetAnimation);

// Class Plugin
double result = ChromaAnimationAPI::CopyAnimationNameD(
	const char* sourceAnimation, const char* targetAnimation);
```

---
<a name="PluginCopyBlueChannelAllFrames"></a>
**PluginCopyBlueChannelAllFrames**

```C++
// DLL Interface
EXPORT_API void PluginCopyBlueChannelAllFrames(
	int animationId, float redIntensity, float greenIntensity);

// Class Plugin
ChromaAnimationAPI::CopyBlueChannelAllFrames(
	int animationId, float redIntensity, float greenIntensity);
```

---
<a name="PluginCopyBlueChannelAllFramesName"></a>
**PluginCopyBlueChannelAllFramesName**

```C++
// DLL Interface
EXPORT_API void PluginCopyBlueChannelAllFramesName(
	const char* path, float redIntensity, float greenIntensity);

// Class Plugin
ChromaAnimationAPI::CopyBlueChannelAllFramesName(
	const char* path, float redIntensity, float greenIntensity);
```

---
<a name="PluginCopyBlueChannelAllFramesNameD"></a>
**PluginCopyBlueChannelAllFramesNameD**

```C++
// DLL Interface
EXPORT_API double PluginCopyBlueChannelAllFramesNameD(
	const char* path, double redIntensity, double greenIntensity);

// Class Plugin
double result = ChromaAnimationAPI::CopyBlueChannelAllFramesNameD(
	const char* path, double redIntensity, double greenIntensity);
```

---
<a name="PluginCopyGreenChannelAllFrames"></a>
**PluginCopyGreenChannelAllFrames**

```C++
// DLL Interface
EXPORT_API void PluginCopyGreenChannelAllFrames(
	int animationId, float redIntensity, float blueIntensity);

// Class Plugin
ChromaAnimationAPI::CopyGreenChannelAllFrames(
	int animationId, float redIntensity, float blueIntensity);
```

---
<a name="PluginCopyGreenChannelAllFramesName"></a>
**PluginCopyGreenChannelAllFramesName**

```C++
// DLL Interface
EXPORT_API void PluginCopyGreenChannelAllFramesName(
	const char* path, float redIntensity, float blueIntensity);

// Class Plugin
ChromaAnimationAPI::CopyGreenChannelAllFramesName(
	const char* path, float redIntensity, float blueIntensity);
```

---
<a name="PluginCopyGreenChannelAllFramesNameD"></a>
**PluginCopyGreenChannelAllFramesNameD**

```C++
// DLL Interface
EXPORT_API double PluginCopyGreenChannelAllFramesNameD(
	const char* path, double redIntensity, double blueIntensity);

// Class Plugin
double result = ChromaAnimationAPI::CopyGreenChannelAllFramesNameD(
	const char* path, double redIntensity, double blueIntensity);
```

---
<a name="PluginCopyKeyColor"></a>
**PluginCopyKeyColor**

Copy animation key color from the source animation to the target animation
for the given frame.

```C++
// DLL Interface
EXPORT_API void PluginCopyKeyColor(
	int sourceAnimationId, int targetAnimationId, int frameId, int rzkey);

// Class Plugin
ChromaAnimationAPI::CopyKeyColor(
	int sourceAnimationId, int targetAnimationId, int frameId, int rzkey);
```

---
<a name="PluginCopyKeyColorAllFrames"></a>
**PluginCopyKeyColorAllFrames**

```C++
// DLL Interface
EXPORT_API void PluginCopyKeyColorAllFrames(
	int sourceAnimationId, int targetAnimationId, int rzkey);

// Class Plugin
ChromaAnimationAPI::CopyKeyColorAllFrames(
	int sourceAnimationId, int targetAnimationId, int rzkey);
```

---
<a name="PluginCopyKeyColorAllFramesName"></a>
**PluginCopyKeyColorAllFramesName**

```C++
// DLL Interface
EXPORT_API void PluginCopyKeyColorAllFramesName(
	const char* sourceAnimation, const char* targetAnimation, int rzkey);

// Class Plugin
ChromaAnimationAPI::CopyKeyColorAllFramesName(
	const char* sourceAnimation, const char* targetAnimation, int rzkey);
```

---
<a name="PluginCopyKeyColorAllFramesNameD"></a>
**PluginCopyKeyColorAllFramesNameD**

```C++
// DLL Interface
EXPORT_API double PluginCopyKeyColorAllFramesNameD(
	const char* sourceAnimation, const char* targetAnimation, double rzkey);

// Class Plugin
double result = ChromaAnimationAPI::CopyKeyColorAllFramesNameD(
	const char* sourceAnimation, const char* targetAnimation, double rzkey);
```

---
<a name="PluginCopyKeyColorAllFramesOffset"></a>
**PluginCopyKeyColorAllFramesOffset**

```C++
// DLL Interface
EXPORT_API void PluginCopyKeyColorAllFramesOffset(
	int sourceAnimationId, int targetAnimationId, int rzkey, int offset);

// Class Plugin
ChromaAnimationAPI::CopyKeyColorAllFramesOffset(
	int sourceAnimationId, int targetAnimationId, int rzkey, int offset);
```

---
<a name="PluginCopyKeyColorAllFramesOffsetName"></a>
**PluginCopyKeyColorAllFramesOffsetName**

```C++
// DLL Interface
EXPORT_API void PluginCopyKeyColorAllFramesOffsetName(
	const char* sourceAnimation, const char* targetAnimation, int rzkey, int offset);

// Class Plugin
ChromaAnimationAPI::CopyKeyColorAllFramesOffsetName(
	const char* sourceAnimation, const char* targetAnimation, int rzkey, int offset);
```

---
<a name="PluginCopyKeyColorAllFramesOffsetNameD"></a>
**PluginCopyKeyColorAllFramesOffsetNameD**

```C++
// DLL Interface
EXPORT_API double PluginCopyKeyColorAllFramesOffsetNameD(
	const char* sourceAnimation, const char* targetAnimation, double rzkey, double offset);

// Class Plugin
double result = ChromaAnimationAPI::CopyKeyColorAllFramesOffsetNameD(
	const char* sourceAnimation, const char* targetAnimation, double rzkey, double offset);
```

---
<a name="PluginCopyKeyColorName"></a>
**PluginCopyKeyColorName**

Copy animation key color from the source animation to the target animation
for the given frame.

```C++
// DLL Interface
EXPORT_API void PluginCopyKeyColorName(
	const char* sourceAnimation, const char* targetAnimation, int frameId, int rzkey);

// Class Plugin
ChromaAnimationAPI::CopyKeyColorName(
	const char* sourceAnimation, const char* targetAnimation, int frameId, int rzkey);
```

---
<a name="PluginCopyKeyColorNameD"></a>
**PluginCopyKeyColorNameD**

```C++
// DLL Interface
EXPORT_API double PluginCopyKeyColorNameD(
	const char* sourceAnimation, const char* targetAnimation, double frameId,
	double rzkey);

// Class Plugin
double result = ChromaAnimationAPI::CopyKeyColorNameD(
	const char* sourceAnimation, const char* targetAnimation, double frameId,
	double rzkey);
```

---
<a name="PluginCopyNonZeroAllKeys"></a>
**PluginCopyNonZeroAllKeys**

```C++
// DLL Interface
EXPORT_API void PluginCopyNonZeroAllKeys(
	int sourceAnimationId, int targetAnimationId, int frameId);

// Class Plugin
ChromaAnimationAPI::CopyNonZeroAllKeys(
	int sourceAnimationId, int targetAnimationId, int frameId);
```

---
<a name="PluginCopyNonZeroAllKeysAllFrames"></a>
**PluginCopyNonZeroAllKeysAllFrames**

Copy nonzero colors from a source animation to a target animation for all
keys.

```C++
// DLL Interface
EXPORT_API void PluginCopyNonZeroAllKeysAllFrames(
	int sourceAnimationId, int targetAnimationId);

// Class Plugin
ChromaAnimationAPI::CopyNonZeroAllKeysAllFrames(
	int sourceAnimationId, int targetAnimationId);
```

---
<a name="PluginCopyNonZeroAllKeysAllFramesName"></a>
**PluginCopyNonZeroAllKeysAllFramesName**

Copy nonzero colors from a source animation to a target animation for all
keys.

```C++
// DLL Interface
EXPORT_API void PluginCopyNonZeroAllKeysAllFramesName(
	const char* sourceAnimation, const char* targetAnimation);

// Class Plugin
ChromaAnimationAPI::CopyNonZeroAllKeysAllFramesName(
	const char* sourceAnimation, const char* targetAnimation);
```

---
<a name="PluginCopyNonZeroAllKeysAllFramesNameD"></a>
**PluginCopyNonZeroAllKeysAllFramesNameD**

```C++
// DLL Interface
EXPORT_API double PluginCopyNonZeroAllKeysAllFramesNameD(
	const char* sourceAnimation, const char* targetAnimation);

// Class Plugin
double result = ChromaAnimationAPI::CopyNonZeroAllKeysAllFramesNameD(
	const char* sourceAnimation, const char* targetAnimation);
```

---
<a name="PluginCopyNonZeroAllKeysAllFramesOffset"></a>
**PluginCopyNonZeroAllKeysAllFramesOffset**

```C++
// DLL Interface
EXPORT_API void PluginCopyNonZeroAllKeysAllFramesOffset(
	int sourceAnimationId, int targetAnimationId, int offset);

// Class Plugin
ChromaAnimationAPI::CopyNonZeroAllKeysAllFramesOffset(
	int sourceAnimationId, int targetAnimationId, int offset);
```

---
<a name="PluginCopyNonZeroAllKeysAllFramesOffsetName"></a>
**PluginCopyNonZeroAllKeysAllFramesOffsetName**

```C++
// DLL Interface
EXPORT_API void PluginCopyNonZeroAllKeysAllFramesOffsetName(
	const char* sourceAnimation, const char* targetAnimation, int offset);

// Class Plugin
ChromaAnimationAPI::CopyNonZeroAllKeysAllFramesOffsetName(
	const char* sourceAnimation, const char* targetAnimation, int offset);
```

---
<a name="PluginCopyNonZeroAllKeysAllFramesOffsetNameD"></a>
**PluginCopyNonZeroAllKeysAllFramesOffsetNameD**

```C++
// DLL Interface
EXPORT_API double PluginCopyNonZeroAllKeysAllFramesOffsetNameD(
	const char* sourceAnimation, const char* targetAnimation, double offset);

// Class Plugin
double result = ChromaAnimationAPI::CopyNonZeroAllKeysAllFramesOffsetNameD(
	const char* sourceAnimation, const char* targetAnimation, double offset);
```

---
<a name="PluginCopyNonZeroAllKeysName"></a>
**PluginCopyNonZeroAllKeysName**

```C++
// DLL Interface
EXPORT_API void PluginCopyNonZeroAllKeysName(
	const char* sourceAnimation, const char* targetAnimation, int frameId);

// Class Plugin
ChromaAnimationAPI::CopyNonZeroAllKeysName(
	const char* sourceAnimation, const char* targetAnimation, int frameId);
```

---
<a name="PluginCopyNonZeroAllKeysNameD"></a>
**PluginCopyNonZeroAllKeysNameD**

```C++
// DLL Interface
EXPORT_API double PluginCopyNonZeroAllKeysNameD(
	const char* sourceAnimation, const char* targetAnimation, double frameId);

// Class Plugin
double result = ChromaAnimationAPI::CopyNonZeroAllKeysNameD(
	const char* sourceAnimation, const char* targetAnimation, double frameId);
```

---
<a name="PluginCopyNonZeroAllKeysOffset"></a>
**PluginCopyNonZeroAllKeysOffset**

```C++
// DLL Interface
EXPORT_API void PluginCopyNonZeroAllKeysOffset(
	int sourceAnimationId, int targetAnimationId, int frameId, int offset);

// Class Plugin
ChromaAnimationAPI::CopyNonZeroAllKeysOffset(
	int sourceAnimationId, int targetAnimationId, int frameId, int offset);
```

---
<a name="PluginCopyNonZeroAllKeysOffsetName"></a>
**PluginCopyNonZeroAllKeysOffsetName**

```C++
// DLL Interface
EXPORT_API void PluginCopyNonZeroAllKeysOffsetName(
	const char* sourceAnimation, const char* targetAnimation, int frameId, int offset);

// Class Plugin
ChromaAnimationAPI::CopyNonZeroAllKeysOffsetName(
	const char* sourceAnimation, const char* targetAnimation, int frameId, int offset);
```

---
<a name="PluginCopyNonZeroAllKeysOffsetNameD"></a>
**PluginCopyNonZeroAllKeysOffsetNameD**

```C++
// DLL Interface
EXPORT_API double PluginCopyNonZeroAllKeysOffsetNameD(
	const char* sourceAnimation, const char* targetAnimation, double frameId,
	double offset);

// Class Plugin
double result = ChromaAnimationAPI::CopyNonZeroAllKeysOffsetNameD(
	const char* sourceAnimation, const char* targetAnimation, double frameId,
	double offset);
```

---
<a name="PluginCopyNonZeroKeyColor"></a>
**PluginCopyNonZeroKeyColor**

Copy animation key color from the source animation to the target animation
for the given frame where color is not zero.

```C++
// DLL Interface
EXPORT_API void PluginCopyNonZeroKeyColor(
	int sourceAnimationId, int targetAnimationId, int frameId, int rzkey);

// Class Plugin
ChromaAnimationAPI::CopyNonZeroKeyColor(
	int sourceAnimationId, int targetAnimationId, int frameId, int rzkey);
```

---
<a name="PluginCopyNonZeroKeyColorName"></a>
**PluginCopyNonZeroKeyColorName**

Copy animation key color from the source animation to the target animation
for the given frame where color is not zero.

```C++
// DLL Interface
EXPORT_API void PluginCopyNonZeroKeyColorName(
	const char* sourceAnimation, const char* targetAnimation, int frameId, int rzkey);

// Class Plugin
ChromaAnimationAPI::CopyNonZeroKeyColorName(
	const char* sourceAnimation, const char* targetAnimation, int frameId, int rzkey);
```

---
<a name="PluginCopyNonZeroKeyColorNameD"></a>
**PluginCopyNonZeroKeyColorNameD**

```C++
// DLL Interface
EXPORT_API double PluginCopyNonZeroKeyColorNameD(
	const char* sourceAnimation, const char* targetAnimation, double frameId,
	double rzkey);

// Class Plugin
double result = ChromaAnimationAPI::CopyNonZeroKeyColorNameD(
	const char* sourceAnimation, const char* targetAnimation, double frameId,
	double rzkey);
```

---
<a name="PluginCopyNonZeroTargetAllKeys"></a>
**PluginCopyNonZeroTargetAllKeys**

```C++
// DLL Interface
EXPORT_API void PluginCopyNonZeroTargetAllKeys(
	int sourceAnimationId, int targetAnimationId, int frameId);

// Class Plugin
ChromaAnimationAPI::CopyNonZeroTargetAllKeys(
	int sourceAnimationId, int targetAnimationId, int frameId);
```

---
<a name="PluginCopyNonZeroTargetAllKeysAllFrames"></a>
**PluginCopyNonZeroTargetAllKeysAllFrames**

```C++
// DLL Interface
EXPORT_API void PluginCopyNonZeroTargetAllKeysAllFrames(
	int sourceAnimationId, int targetAnimationId);

// Class Plugin
ChromaAnimationAPI::CopyNonZeroTargetAllKeysAllFrames(
	int sourceAnimationId, int targetAnimationId);
```

---
<a name="PluginCopyNonZeroTargetAllKeysAllFramesName"></a>
**PluginCopyNonZeroTargetAllKeysAllFramesName**

```C++
// DLL Interface
EXPORT_API void PluginCopyNonZeroTargetAllKeysAllFramesName(
	const char* sourceAnimation, const char* targetAnimation);

// Class Plugin
ChromaAnimationAPI::CopyNonZeroTargetAllKeysAllFramesName(
	const char* sourceAnimation, const char* targetAnimation);
```

---
<a name="PluginCopyNonZeroTargetAllKeysAllFramesNameD"></a>
**PluginCopyNonZeroTargetAllKeysAllFramesNameD**

```C++
// DLL Interface
EXPORT_API double PluginCopyNonZeroTargetAllKeysAllFramesNameD(
	const char* sourceAnimation, const char* targetAnimation);

// Class Plugin
double result = ChromaAnimationAPI::CopyNonZeroTargetAllKeysAllFramesNameD(
	const char* sourceAnimation, const char* targetAnimation);
```

---
<a name="PluginCopyNonZeroTargetAllKeysAllFramesOffset"></a>
**PluginCopyNonZeroTargetAllKeysAllFramesOffset**

```C++
// DLL Interface
EXPORT_API void PluginCopyNonZeroTargetAllKeysAllFramesOffset(
	int sourceAnimationId, int targetAnimationId, int offset);

// Class Plugin
ChromaAnimationAPI::CopyNonZeroTargetAllKeysAllFramesOffset(
	int sourceAnimationId, int targetAnimationId, int offset);
```

---
<a name="PluginCopyNonZeroTargetAllKeysAllFramesOffsetName"></a>
**PluginCopyNonZeroTargetAllKeysAllFramesOffsetName**

```C++
// DLL Interface
EXPORT_API void PluginCopyNonZeroTargetAllKeysAllFramesOffsetName(
	const char* sourceAnimation, const char* targetAnimation, int offset);

// Class Plugin
ChromaAnimationAPI::CopyNonZeroTargetAllKeysAllFramesOffsetName(
	const char* sourceAnimation, const char* targetAnimation, int offset);
```

---
<a name="PluginCopyNonZeroTargetAllKeysAllFramesOffsetNameD"></a>
**PluginCopyNonZeroTargetAllKeysAllFramesOffsetNameD**

```C++
// DLL Interface
EXPORT_API double PluginCopyNonZeroTargetAllKeysAllFramesOffsetNameD(
	const char* sourceAnimation, const char* targetAnimation, double offset);

// Class Plugin
double result = ChromaAnimationAPI::CopyNonZeroTargetAllKeysAllFramesOffsetNameD(
	const char* sourceAnimation, const char* targetAnimation, double offset);
```

---
<a name="PluginCopyNonZeroTargetAllKeysName"></a>
**PluginCopyNonZeroTargetAllKeysName**

```C++
// DLL Interface
EXPORT_API void PluginCopyNonZeroTargetAllKeysName(
	const char* sourceAnimation, const char* targetAnimation, int frameId);

// Class Plugin
ChromaAnimationAPI::CopyNonZeroTargetAllKeysName(
	const char* sourceAnimation, const char* targetAnimation, int frameId);
```

---
<a name="PluginCopyNonZeroTargetAllKeysNameD"></a>
**PluginCopyNonZeroTargetAllKeysNameD**

```C++
// DLL Interface
EXPORT_API double PluginCopyNonZeroTargetAllKeysNameD(
	const char* sourceAnimation, const char* targetAnimation, double frameId);

// Class Plugin
double result = ChromaAnimationAPI::CopyNonZeroTargetAllKeysNameD(
	const char* sourceAnimation, const char* targetAnimation, double frameId);
```

---
<a name="PluginCopyNonZeroTargetAllKeysOffset"></a>
**PluginCopyNonZeroTargetAllKeysOffset**

```C++
// DLL Interface
EXPORT_API void PluginCopyNonZeroTargetAllKeysOffset(
	int sourceAnimationId, int targetAnimationId, int frameId, int offset);

// Class Plugin
ChromaAnimationAPI::CopyNonZeroTargetAllKeysOffset(
	int sourceAnimationId, int targetAnimationId, int frameId, int offset);
```

---
<a name="PluginCopyNonZeroTargetAllKeysOffsetName"></a>
**PluginCopyNonZeroTargetAllKeysOffsetName**

```C++
// DLL Interface
EXPORT_API void PluginCopyNonZeroTargetAllKeysOffsetName(
	const char* sourceAnimation, const char* targetAnimation, int frameId, int offset);

// Class Plugin
ChromaAnimationAPI::CopyNonZeroTargetAllKeysOffsetName(
	const char* sourceAnimation, const char* targetAnimation, int frameId, int offset);
```

---
<a name="PluginCopyNonZeroTargetAllKeysOffsetNameD"></a>
**PluginCopyNonZeroTargetAllKeysOffsetNameD**

```C++
// DLL Interface
EXPORT_API double PluginCopyNonZeroTargetAllKeysOffsetNameD(
	const char* sourceAnimation, const char* targetAnimation, double frameId,
	double offset);

// Class Plugin
double result = ChromaAnimationAPI::CopyNonZeroTargetAllKeysOffsetNameD(
	const char* sourceAnimation, const char* targetAnimation, double frameId,
	double offset);
```

---
<a name="PluginCopyRedChannelAllFrames"></a>
**PluginCopyRedChannelAllFrames**

```C++
// DLL Interface
EXPORT_API void PluginCopyRedChannelAllFrames(
	int animationId, float greenIntensity, float blueIntensity);

// Class Plugin
ChromaAnimationAPI::CopyRedChannelAllFrames(
	int animationId, float greenIntensity, float blueIntensity);
```

---
<a name="PluginCopyRedChannelAllFramesName"></a>
**PluginCopyRedChannelAllFramesName**

```C++
// DLL Interface
EXPORT_API void PluginCopyRedChannelAllFramesName(
	const char* path, float greenIntensity, float blueIntensity);

// Class Plugin
ChromaAnimationAPI::CopyRedChannelAllFramesName(
	const char* path, float greenIntensity, float blueIntensity);
```

---
<a name="PluginCopyRedChannelAllFramesNameD"></a>
**PluginCopyRedChannelAllFramesNameD**

```C++
// DLL Interface
EXPORT_API double PluginCopyRedChannelAllFramesNameD(
	const char* path, double greenIntensity, double blueIntensity);

// Class Plugin
double result = ChromaAnimationAPI::CopyRedChannelAllFramesNameD(
	const char* path, double greenIntensity, double blueIntensity);
```

---
<a name="PluginCopyZeroAllKeysAllFrames"></a>
**PluginCopyZeroAllKeysAllFrames**

```C++
// DLL Interface
EXPORT_API void PluginCopyZeroAllKeysAllFrames(
	int sourceAnimationId, int targetAnimationId);

// Class Plugin
ChromaAnimationAPI::CopyZeroAllKeysAllFrames(
	int sourceAnimationId, int targetAnimationId);
```

---
<a name="PluginCopyZeroAllKeysAllFramesName"></a>
**PluginCopyZeroAllKeysAllFramesName**

```C++
// DLL Interface
EXPORT_API void PluginCopyZeroAllKeysAllFramesName(
	const char* sourceAnimation, const char* targetAnimation);

// Class Plugin
ChromaAnimationAPI::CopyZeroAllKeysAllFramesName(
	const char* sourceAnimation, const char* targetAnimation);
```

---
<a name="PluginCopyZeroAllKeysAllFramesNameD"></a>
**PluginCopyZeroAllKeysAllFramesNameD**

```C++
// DLL Interface
EXPORT_API double PluginCopyZeroAllKeysAllFramesNameD(
	const char* sourceAnimation, const char* targetAnimation);

// Class Plugin
double result = ChromaAnimationAPI::CopyZeroAllKeysAllFramesNameD(
	const char* sourceAnimation, const char* targetAnimation);
```

---
<a name="PluginCopyZeroAllKeysAllFramesOffset"></a>
**PluginCopyZeroAllKeysAllFramesOffset**

```C++
// DLL Interface
EXPORT_API void PluginCopyZeroAllKeysAllFramesOffset(
	int sourceAnimationId, int targetAnimationId, int offset);

// Class Plugin
ChromaAnimationAPI::CopyZeroAllKeysAllFramesOffset(
	int sourceAnimationId, int targetAnimationId, int offset);
```

---
<a name="PluginCopyZeroAllKeysAllFramesOffsetName"></a>
**PluginCopyZeroAllKeysAllFramesOffsetName**

```C++
// DLL Interface
EXPORT_API void PluginCopyZeroAllKeysAllFramesOffsetName(
	const char* sourceAnimation, const char* targetAnimation, int offset);

// Class Plugin
ChromaAnimationAPI::CopyZeroAllKeysAllFramesOffsetName(
	const char* sourceAnimation, const char* targetAnimation, int offset);
```

---
<a name="PluginCopyZeroAllKeysAllFramesOffsetNameD"></a>
**PluginCopyZeroAllKeysAllFramesOffsetNameD**

```C++
// DLL Interface
EXPORT_API double PluginCopyZeroAllKeysAllFramesOffsetNameD(
	const char* sourceAnimation, const char* targetAnimation, double offset);

// Class Plugin
double result = ChromaAnimationAPI::CopyZeroAllKeysAllFramesOffsetNameD(
	const char* sourceAnimation, const char* targetAnimation, double offset);
```

---
<a name="PluginCopyZeroKeyColor"></a>
**PluginCopyZeroKeyColor**

```C++
// DLL Interface
EXPORT_API void PluginCopyZeroKeyColor(
	int sourceAnimationId, int targetAnimationId, int frameId, int rzkey);

// Class Plugin
ChromaAnimationAPI::CopyZeroKeyColor(
	int sourceAnimationId, int targetAnimationId, int frameId, int rzkey);
```

---
<a name="PluginCopyZeroKeyColorName"></a>
**PluginCopyZeroKeyColorName**

```C++
// DLL Interface
EXPORT_API void PluginCopyZeroKeyColorName(
	const char* sourceAnimation, const char* targetAnimation, int frameId, int rzkey);

// Class Plugin
ChromaAnimationAPI::CopyZeroKeyColorName(
	const char* sourceAnimation, const char* targetAnimation, int frameId, int rzkey);
```

---
<a name="PluginCopyZeroKeyColorNameD"></a>
**PluginCopyZeroKeyColorNameD**

```C++
// DLL Interface
EXPORT_API double PluginCopyZeroKeyColorNameD(
	const char* sourceAnimation, const char* targetAnimation, double frameId,
	double rzkey);

// Class Plugin
double result = ChromaAnimationAPI::CopyZeroKeyColorNameD(
	const char* sourceAnimation, const char* targetAnimation, double frameId,
	double rzkey);
```

---
<a name="PluginCopyZeroTargetAllKeysAllFrames"></a>
**PluginCopyZeroTargetAllKeysAllFrames**

```C++
// DLL Interface
EXPORT_API void PluginCopyZeroTargetAllKeysAllFrames(
	int sourceAnimationId, int targetAnimationId);

// Class Plugin
ChromaAnimationAPI::CopyZeroTargetAllKeysAllFrames(
	int sourceAnimationId, int targetAnimationId);
```

---
<a name="PluginCopyZeroTargetAllKeysAllFramesName"></a>
**PluginCopyZeroTargetAllKeysAllFramesName**

```C++
// DLL Interface
EXPORT_API void PluginCopyZeroTargetAllKeysAllFramesName(
	const char* sourceAnimation, const char* targetAnimation);

// Class Plugin
ChromaAnimationAPI::CopyZeroTargetAllKeysAllFramesName(
	const char* sourceAnimation, const char* targetAnimation);
```

---
<a name="PluginCopyZeroTargetAllKeysAllFramesNameD"></a>
**PluginCopyZeroTargetAllKeysAllFramesNameD**

```C++
// DLL Interface
EXPORT_API double PluginCopyZeroTargetAllKeysAllFramesNameD(
	const char* sourceAnimation, const char* targetAnimation);

// Class Plugin
double result = ChromaAnimationAPI::CopyZeroTargetAllKeysAllFramesNameD(
	const char* sourceAnimation, const char* targetAnimation);
```

---
<a name="PluginCoreCreateChromaLinkEffect"></a>
**PluginCoreCreateChromaLinkEffect**

```C++
// DLL Interface
EXPORT_API RZRESULT PluginCoreCreateChromaLinkEffect(
	ChromaSDK::ChromaLink::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);

// Class Plugin
RZRESULT result = ChromaAnimationAPI::CoreCreateChromaLinkEffect(
	ChromaSDK::ChromaLink::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
```

---
<a name="PluginCoreCreateEffect"></a>
**PluginCoreCreateEffect**

```C++
// DLL Interface
EXPORT_API RZRESULT PluginCoreCreateEffect(
	RZDEVICEID DeviceId, ChromaSDK::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);

// Class Plugin
RZRESULT result = ChromaAnimationAPI::CoreCreateEffect(
	RZDEVICEID DeviceId, ChromaSDK::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
```

---
<a name="PluginCoreCreateHeadsetEffect"></a>
**PluginCoreCreateHeadsetEffect**

```C++
// DLL Interface
EXPORT_API RZRESULT PluginCoreCreateHeadsetEffect(
	ChromaSDK::Headset::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);

// Class Plugin
RZRESULT result = ChromaAnimationAPI::CoreCreateHeadsetEffect(
	ChromaSDK::Headset::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
```

---
<a name="PluginCoreCreateKeyboardEffect"></a>
**PluginCoreCreateKeyboardEffect**

```C++
// DLL Interface
EXPORT_API RZRESULT PluginCoreCreateKeyboardEffect(
	ChromaSDK::Keyboard::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);

// Class Plugin
RZRESULT result = ChromaAnimationAPI::CoreCreateKeyboardEffect(
	ChromaSDK::Keyboard::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
```

---
<a name="PluginCoreCreateKeypadEffect"></a>
**PluginCoreCreateKeypadEffect**

```C++
// DLL Interface
EXPORT_API RZRESULT PluginCoreCreateKeypadEffect(
	ChromaSDK::Keypad::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);

// Class Plugin
RZRESULT result = ChromaAnimationAPI::CoreCreateKeypadEffect(
	ChromaSDK::Keypad::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
```

---
<a name="PluginCoreCreateMouseEffect"></a>
**PluginCoreCreateMouseEffect**

```C++
// DLL Interface
EXPORT_API RZRESULT PluginCoreCreateMouseEffect(
	ChromaSDK::Mouse::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);

// Class Plugin
RZRESULT result = ChromaAnimationAPI::CoreCreateMouseEffect(
	ChromaSDK::Mouse::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
```

---
<a name="PluginCoreCreateMousepadEffect"></a>
**PluginCoreCreateMousepadEffect**

```C++
// DLL Interface
EXPORT_API RZRESULT PluginCoreCreateMousepadEffect(
	ChromaSDK::Mousepad::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);

// Class Plugin
RZRESULT result = ChromaAnimationAPI::CoreCreateMousepadEffect(
	ChromaSDK::Mousepad::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
```

---
<a name="PluginCoreDeleteEffect"></a>
**PluginCoreDeleteEffect**

```C++
// DLL Interface
EXPORT_API RZRESULT PluginCoreDeleteEffect(RZEFFECTID EffectId);

// Class Plugin
RZRESULT result = ChromaAnimationAPI::CoreDeleteEffect(RZEFFECTID EffectId);
```

---
<a name="PluginCoreInit"></a>
**PluginCoreInit**

```C++
// DLL Interface
EXPORT_API RZRESULT PluginCoreInit();

// Class Plugin
RZRESULT result = ChromaAnimationAPI::CoreInit();
```

---
<a name="PluginCoreQueryDevice"></a>
**PluginCoreQueryDevice**

```C++
// DLL Interface
EXPORT_API RZRESULT PluginCoreQueryDevice(
	RZDEVICEID DeviceId, ChromaSDK::DEVICE_INFO_TYPE &DeviceInfo);

// Class Plugin
RZRESULT result = ChromaAnimationAPI::CoreQueryDevice(
	RZDEVICEID DeviceId, ChromaSDK::DEVICE_INFO_TYPE &DeviceInfo);
```

---
<a name="PluginCoreSetEffect"></a>
**PluginCoreSetEffect**

```C++
// DLL Interface
EXPORT_API RZRESULT PluginCoreSetEffect(RZEFFECTID EffectId);

// Class Plugin
RZRESULT result = ChromaAnimationAPI::CoreSetEffect(RZEFFECTID EffectId);
```

---
<a name="PluginCoreUnInit"></a>
**PluginCoreUnInit**

```C++
// DLL Interface
EXPORT_API RZRESULT PluginCoreUnInit();

// Class Plugin
RZRESULT result = ChromaAnimationAPI::CoreUnInit();
```

---
<a name="PluginCreateAnimation"></a>
**PluginCreateAnimation**

Creates a `Chroma` animation at the given path. The `deviceType` parameter
uses `EChromaSDKDeviceTypeEnum` as an integer. The `device` parameter uses
`EChromaSDKDevice1DEnum` or `EChromaSDKDevice2DEnum` as an integer, respective
to the `deviceType`. Returns the animation id upon success. Returns -1
upon failure. Saves a `Chroma` animation file with the `.chroma` extension
at the given path. Returns the animation id upon success. Returns -1 upon
failure.

```C++
// DLL Interface
EXPORT_API int PluginCreateAnimation(
	const char* path, int deviceType, int device);

// Class Plugin
int result = ChromaAnimationAPI::CreateAnimation(
	const char* path, int deviceType, int device);
```

---
<a name="PluginCreateAnimationInMemory"></a>
**PluginCreateAnimationInMemory**

Creates a `Chroma` animation in memory without creating a file. The `deviceType`
parameter uses `EChromaSDKDeviceTypeEnum` as an integer. The `device` parameter
uses `EChromaSDKDevice1DEnum` or `EChromaSDKDevice2DEnum` as an integer,
respective to the `deviceType`. Returns the animation id upon success.
Returns -1 upon failure. Returns the animation id upon success. Returns
-1 upon failure.

```C++
// DLL Interface
EXPORT_API int PluginCreateAnimationInMemory(
	int deviceType, int device);

// Class Plugin
int result = ChromaAnimationAPI::CreateAnimationInMemory(
	int deviceType, int device);
```

---
<a name="PluginCreateEffect"></a>
**PluginCreateEffect**

```C++
// DLL Interface
EXPORT_API RZRESULT PluginCreateEffect(
	RZDEVICEID deviceId, ChromaSDK::EFFECT_TYPE effect, int* colors, int size,
	ChromaSDK::FChromaSDKGuid* effectId);

// Class Plugin
RZRESULT result = ChromaAnimationAPI::CreateEffect(
	RZDEVICEID deviceId, ChromaSDK::EFFECT_TYPE effect, int* colors, int size,
	ChromaSDK::FChromaSDKGuid* effectId);
```

---
<a name="PluginDeleteEffect"></a>
**PluginDeleteEffect**

```C++
// DLL Interface
EXPORT_API RZRESULT PluginDeleteEffect(
	const ChromaSDK::FChromaSDKGuid& effectId);

// Class Plugin
RZRESULT result = ChromaAnimationAPI::DeleteEffect(
	const ChromaSDK::FChromaSDKGuid& effectId);
```

---
<a name="PluginDuplicateFirstFrame"></a>
**PluginDuplicateFirstFrame**

```C++
// DLL Interface
EXPORT_API void PluginDuplicateFirstFrame(
	int animationId, int frameCount);

// Class Plugin
ChromaAnimationAPI::DuplicateFirstFrame(
	int animationId, int frameCount);
```

---
<a name="PluginDuplicateFirstFrameName"></a>
**PluginDuplicateFirstFrameName**

```C++
// DLL Interface
EXPORT_API void PluginDuplicateFirstFrameName(
	const char* path, int frameCount);

// Class Plugin
ChromaAnimationAPI::DuplicateFirstFrameName(
	const char* path, int frameCount);
```

---
<a name="PluginDuplicateFirstFrameNameD"></a>
**PluginDuplicateFirstFrameNameD**

```C++
// DLL Interface
EXPORT_API double PluginDuplicateFirstFrameNameD(
	const char* path, double frameCount);

// Class Plugin
double result = ChromaAnimationAPI::DuplicateFirstFrameNameD(
	const char* path, double frameCount);
```

---
<a name="PluginDuplicateFrames"></a>
**PluginDuplicateFrames**

```C++
// DLL Interface
EXPORT_API void PluginDuplicateFrames(int animationId);

// Class Plugin
ChromaAnimationAPI::DuplicateFrames(int animationId);
```

---
<a name="PluginDuplicateFramesName"></a>
**PluginDuplicateFramesName**

```C++
// DLL Interface
EXPORT_API void PluginDuplicateFramesName(const char* path);

// Class Plugin
ChromaAnimationAPI::DuplicateFramesName(const char* path);
```

---
<a name="PluginDuplicateFramesNameD"></a>
**PluginDuplicateFramesNameD**

```C++
// DLL Interface
EXPORT_API double PluginDuplicateFramesNameD(const char* path);

// Class Plugin
double result = ChromaAnimationAPI::DuplicateFramesNameD(const char* path);
```

---
<a name="PluginDuplicateMirrorFrames"></a>
**PluginDuplicateMirrorFrames**

```C++
// DLL Interface
EXPORT_API void PluginDuplicateMirrorFrames(int animationId);

// Class Plugin
ChromaAnimationAPI::DuplicateMirrorFrames(int animationId);
```

---
<a name="PluginDuplicateMirrorFramesName"></a>
**PluginDuplicateMirrorFramesName**

```C++
// DLL Interface
EXPORT_API void PluginDuplicateMirrorFramesName(const char* path);

// Class Plugin
ChromaAnimationAPI::DuplicateMirrorFramesName(const char* path);
```

---
<a name="PluginDuplicateMirrorFramesNameD"></a>
**PluginDuplicateMirrorFramesNameD**

```C++
// DLL Interface
EXPORT_API double PluginDuplicateMirrorFramesNameD(const char* path);

// Class Plugin
double result = ChromaAnimationAPI::DuplicateMirrorFramesNameD(const char* path);
```

---
<a name="PluginFadeEndFrames"></a>
**PluginFadeEndFrames**

```C++
// DLL Interface
EXPORT_API void PluginFadeEndFrames(
	int animationId, int fade);

// Class Plugin
ChromaAnimationAPI::FadeEndFrames(
	int animationId, int fade);
```

---
<a name="PluginFadeEndFramesName"></a>
**PluginFadeEndFramesName**

```C++
// DLL Interface
EXPORT_API void PluginFadeEndFramesName(
	const char* path, int fade);

// Class Plugin
ChromaAnimationAPI::FadeEndFramesName(
	const char* path, int fade);
```

---
<a name="PluginFadeEndFramesNameD"></a>
**PluginFadeEndFramesNameD**

```C++
// DLL Interface
EXPORT_API double PluginFadeEndFramesNameD(
	const char* path, double fade);

// Class Plugin
double result = ChromaAnimationAPI::FadeEndFramesNameD(
	const char* path, double fade);
```

---
<a name="PluginFadeStartFrames"></a>
**PluginFadeStartFrames**

```C++
// DLL Interface
EXPORT_API void PluginFadeStartFrames(
	int animationId, int fade);

// Class Plugin
ChromaAnimationAPI::FadeStartFrames(
	int animationId, int fade);
```

---
<a name="PluginFadeStartFramesName"></a>
**PluginFadeStartFramesName**

```C++
// DLL Interface
EXPORT_API void PluginFadeStartFramesName(
	const char* path, int fade);

// Class Plugin
ChromaAnimationAPI::FadeStartFramesName(
	const char* path, int fade);
```

---
<a name="PluginFadeStartFramesNameD"></a>
**PluginFadeStartFramesNameD**

```C++
// DLL Interface
EXPORT_API double PluginFadeStartFramesNameD(
	const char* path, double fade);

// Class Plugin
double result = ChromaAnimationAPI::FadeStartFramesNameD(
	const char* path, double fade);
```

---
<a name="PluginFillColor"></a>
**PluginFillColor**

Set the RGB value for all colors in the specified frame. Use the range of
0 to 255 for red, green, and blue parameters.

```C++
// DLL Interface
EXPORT_API void PluginFillColor(
	int animationId, int frameId, int color);

// Class Plugin
ChromaAnimationAPI::FillColor(
	int animationId, int frameId, int color);
```

---
<a name="PluginFillColorAllFrames"></a>
**PluginFillColorAllFrames**

```C++
// DLL Interface
EXPORT_API void PluginFillColorAllFrames(
	int animationId, int color);

// Class Plugin
ChromaAnimationAPI::FillColorAllFrames(
	int animationId, int color);
```

---
<a name="PluginFillColorAllFramesName"></a>
**PluginFillColorAllFramesName**

Set the RGB value for all colors for all frames.

```C++
// DLL Interface
EXPORT_API void PluginFillColorAllFramesName(
	const char* path, int color);

// Class Plugin
ChromaAnimationAPI::FillColorAllFramesName(
	const char* path, int color);
```

---
<a name="PluginFillColorAllFramesNameD"></a>
**PluginFillColorAllFramesNameD**

```C++
// DLL Interface
EXPORT_API double PluginFillColorAllFramesNameD(
	const char* path, double color);

// Class Plugin
double result = ChromaAnimationAPI::FillColorAllFramesNameD(
	const char* path, double color);
```

---
<a name="PluginFillColorAllFramesRGB"></a>
**PluginFillColorAllFramesRGB**

Set the RGB value for all colors for all frames. Use the range of 0 to 255
for red, green, and blue parameters.

```C++
// DLL Interface
EXPORT_API void PluginFillColorAllFramesRGB(
	int animationId, int red, int green, int blue);

// Class Plugin
ChromaAnimationAPI::FillColorAllFramesRGB(
	int animationId, int red, int green, int blue);
```

---
<a name="PluginFillColorAllFramesRGBName"></a>
**PluginFillColorAllFramesRGBName**

```C++
// DLL Interface
EXPORT_API void PluginFillColorAllFramesRGBName(
	const char* path, int red, int green, int blue);

// Class Plugin
ChromaAnimationAPI::FillColorAllFramesRGBName(
	const char* path, int red, int green, int blue);
```

---
<a name="PluginFillColorAllFramesRGBNameD"></a>
**PluginFillColorAllFramesRGBNameD**

```C++
// DLL Interface
EXPORT_API double PluginFillColorAllFramesRGBNameD(
	const char* path, double red, double green, double blue);

// Class Plugin
double result = ChromaAnimationAPI::FillColorAllFramesRGBNameD(
	const char* path, double red, double green, double blue);
```

---
<a name="PluginFillColorName"></a>
**PluginFillColorName**

Set the RGB value for all colors in the specified frame. Use a BGR integer
for the color parameter. 0xFF0000 (blue) 0x00FF00 (green) 0x0000FF (red)

```C++
// DLL Interface
EXPORT_API void PluginFillColorName(
	const char* path, int frameId, int color);

// Class Plugin
ChromaAnimationAPI::FillColorName(
	const char* path, int frameId, int color);
```

---
<a name="PluginFillColorNameD"></a>
**PluginFillColorNameD**

```C++
// DLL Interface
EXPORT_API double PluginFillColorNameD(
	const char* path, double frameId, double color);

// Class Plugin
double result = ChromaAnimationAPI::FillColorNameD(
	const char* path, double frameId, double color);
```

---
<a name="PluginFillColorRGB"></a>
**PluginFillColorRGB**

Set the RGB value for all colors in the specified frame. Use the range of
0 to 255 for red, green, and blue parameters.

```C++
// DLL Interface
EXPORT_API void PluginFillColorRGB(
	int animationId, int frameId, int red, int green, int blue);

// Class Plugin
ChromaAnimationAPI::FillColorRGB(
	int animationId, int frameId, int red, int green, int blue);
```

---
<a name="PluginFillColorRGBName"></a>
**PluginFillColorRGBName**

```C++
// DLL Interface
EXPORT_API void PluginFillColorRGBName(
	const char* path, int frameId, int red, int green, int blue);

// Class Plugin
ChromaAnimationAPI::FillColorRGBName(
	const char* path, int frameId, int red, int green, int blue);
```

---
<a name="PluginFillColorRGBNameD"></a>
**PluginFillColorRGBNameD**

```C++
// DLL Interface
EXPORT_API double PluginFillColorRGBNameD(
	const char* path, double frameId, double red, double green, double blue);

// Class Plugin
double result = ChromaAnimationAPI::FillColorRGBNameD(
	const char* path, double frameId, double red, double green, double blue);
```

---
<a name="PluginFillNonZeroColor"></a>
**PluginFillNonZeroColor**

This method will only update colors in the animation that are not already
set to black. Set the RGB value for a subset of colors in the specified
frame.

```C++
// DLL Interface
EXPORT_API void PluginFillNonZeroColor(
	int animationId, int frameId, int color);

// Class Plugin
ChromaAnimationAPI::FillNonZeroColor(
	int animationId, int frameId, int color);
```

---
<a name="PluginFillNonZeroColorAllFrames"></a>
**PluginFillNonZeroColorAllFrames**

This method will only update colors in the animation that are not already
set to black. Set the RGB value for a subset of colors for all frames.

```C++
// DLL Interface
EXPORT_API void PluginFillNonZeroColorAllFrames(
	int animationId, int color);

// Class Plugin
ChromaAnimationAPI::FillNonZeroColorAllFrames(
	int animationId, int color);
```

---
<a name="PluginFillNonZeroColorAllFramesName"></a>
**PluginFillNonZeroColorAllFramesName**

This method will only update colors in the animation that are not already
set to black. Set the RGB value for a subset of colors for all frames.

```C++
// DLL Interface
EXPORT_API void PluginFillNonZeroColorAllFramesName(
	const char* path, int color);

// Class Plugin
ChromaAnimationAPI::FillNonZeroColorAllFramesName(
	const char* path, int color);
```

---
<a name="PluginFillNonZeroColorAllFramesNameD"></a>
**PluginFillNonZeroColorAllFramesNameD**

```C++
// DLL Interface
EXPORT_API double PluginFillNonZeroColorAllFramesNameD(
	const char* path, double color);

// Class Plugin
double result = ChromaAnimationAPI::FillNonZeroColorAllFramesNameD(
	const char* path, double color);
```

---
<a name="PluginFillNonZeroColorAllFramesRGB"></a>
**PluginFillNonZeroColorAllFramesRGB**

This method will only update colors in the animation that are not already
set to black. Set the RGB value for a subset of colors for all frames.
Use the range of 0 to 255 for red, green, and blue parameters.

```C++
// DLL Interface
EXPORT_API void PluginFillNonZeroColorAllFramesRGB(
	int animationId, int red, int green, int blue);

// Class Plugin
ChromaAnimationAPI::FillNonZeroColorAllFramesRGB(
	int animationId, int red, int green, int blue);
```

---
<a name="PluginFillNonZeroColorAllFramesRGBName"></a>
**PluginFillNonZeroColorAllFramesRGBName**

```C++
// DLL Interface
EXPORT_API void PluginFillNonZeroColorAllFramesRGBName(
	const char* path, int red, int green, int blue);

// Class Plugin
ChromaAnimationAPI::FillNonZeroColorAllFramesRGBName(
	const char* path, int red, int green, int blue);
```

---
<a name="PluginFillNonZeroColorAllFramesRGBNameD"></a>
**PluginFillNonZeroColorAllFramesRGBNameD**

```C++
// DLL Interface
EXPORT_API double PluginFillNonZeroColorAllFramesRGBNameD(
	const char* path, double red, double green, double blue);

// Class Plugin
double result = ChromaAnimationAPI::FillNonZeroColorAllFramesRGBNameD(
	const char* path, double red, double green, double blue);
```

---
<a name="PluginFillNonZeroColorName"></a>
**PluginFillNonZeroColorName**

This method will only update colors in the animation that are not already
set to black. Set the RGB value for a subset of colors in the specified
frame.

```C++
// DLL Interface
EXPORT_API void PluginFillNonZeroColorName(
	const char* path, int frameId, int color);

// Class Plugin
ChromaAnimationAPI::FillNonZeroColorName(
	const char* path, int frameId, int color);
```

---
<a name="PluginFillNonZeroColorNameD"></a>
**PluginFillNonZeroColorNameD**

```C++
// DLL Interface
EXPORT_API double PluginFillNonZeroColorNameD(
	const char* path, double frameId, double color);

// Class Plugin
double result = ChromaAnimationAPI::FillNonZeroColorNameD(
	const char* path, double frameId, double color);
```

---
<a name="PluginFillNonZeroColorRGB"></a>
**PluginFillNonZeroColorRGB**

This method will only update colors in the animation that are not already
set to black. Set the RGB value for a subset of colors in the specified
frame. Use the range of 0 to 255 for red, green, and blue parameters.

```C++
// DLL Interface
EXPORT_API void PluginFillNonZeroColorRGB(
	int animationId, int frameId, int red, int green, int blue);

// Class Plugin
ChromaAnimationAPI::FillNonZeroColorRGB(
	int animationId, int frameId, int red, int green, int blue);
```

---
<a name="PluginFillNonZeroColorRGBName"></a>
**PluginFillNonZeroColorRGBName**

```C++
// DLL Interface
EXPORT_API void PluginFillNonZeroColorRGBName(
	const char* path, int frameId, int red, int green, int blue);

// Class Plugin
ChromaAnimationAPI::FillNonZeroColorRGBName(
	const char* path, int frameId, int red, int green, int blue);
```

---
<a name="PluginFillNonZeroColorRGBNameD"></a>
**PluginFillNonZeroColorRGBNameD**

```C++
// DLL Interface
EXPORT_API double PluginFillNonZeroColorRGBNameD(
	const char* path, double frameId, double red, double green, double blue);

// Class Plugin
double result = ChromaAnimationAPI::FillNonZeroColorRGBNameD(
	const char* path, double frameId, double red, double green, double blue);
```

---
<a name="PluginFillRandomColors"></a>
**PluginFillRandomColors**

```C++
// DLL Interface
EXPORT_API void PluginFillRandomColors(
	int animationId, int frameId);

// Class Plugin
ChromaAnimationAPI::FillRandomColors(
	int animationId, int frameId);
```

---
<a name="PluginFillRandomColorsAllFrames"></a>
**PluginFillRandomColorsAllFrames**

```C++
// DLL Interface
EXPORT_API void PluginFillRandomColorsAllFrames(int animationId);

// Class Plugin
ChromaAnimationAPI::FillRandomColorsAllFrames(int animationId);
```

---
<a name="PluginFillRandomColorsAllFramesName"></a>
**PluginFillRandomColorsAllFramesName**

```C++
// DLL Interface
EXPORT_API void PluginFillRandomColorsAllFramesName(const char* path);

// Class Plugin
ChromaAnimationAPI::FillRandomColorsAllFramesName(const char* path);
```

---
<a name="PluginFillRandomColorsAllFramesNameD"></a>
**PluginFillRandomColorsAllFramesNameD**

```C++
// DLL Interface
EXPORT_API double PluginFillRandomColorsAllFramesNameD(const char* path);

// Class Plugin
double result = ChromaAnimationAPI::FillRandomColorsAllFramesNameD(const char* path);
```

---
<a name="PluginFillRandomColorsBlackAndWhite"></a>
**PluginFillRandomColorsBlackAndWhite**

```C++
// DLL Interface
EXPORT_API void PluginFillRandomColorsBlackAndWhite(
	int animationId, int frameId);

// Class Plugin
ChromaAnimationAPI::FillRandomColorsBlackAndWhite(
	int animationId, int frameId);
```

---
<a name="PluginFillRandomColorsBlackAndWhiteAllFrames"></a>
**PluginFillRandomColorsBlackAndWhiteAllFrames**

```C++
// DLL Interface
EXPORT_API void PluginFillRandomColorsBlackAndWhiteAllFrames(int animationId);

// Class Plugin
ChromaAnimationAPI::FillRandomColorsBlackAndWhiteAllFrames(int animationId);
```

---
<a name="PluginFillRandomColorsBlackAndWhiteAllFramesName"></a>
**PluginFillRandomColorsBlackAndWhiteAllFramesName**

```C++
// DLL Interface
EXPORT_API void PluginFillRandomColorsBlackAndWhiteAllFramesName(const char* path);

// Class Plugin
ChromaAnimationAPI::FillRandomColorsBlackAndWhiteAllFramesName(const char* path);
```

---
<a name="PluginFillRandomColorsBlackAndWhiteAllFramesNameD"></a>
**PluginFillRandomColorsBlackAndWhiteAllFramesNameD**

```C++
// DLL Interface
EXPORT_API double PluginFillRandomColorsBlackAndWhiteAllFramesNameD(const char* path);

// Class Plugin
double result = ChromaAnimationAPI::FillRandomColorsBlackAndWhiteAllFramesNameD(const char* path);
```

---
<a name="PluginFillRandomColorsBlackAndWhiteName"></a>
**PluginFillRandomColorsBlackAndWhiteName**

```C++
// DLL Interface
EXPORT_API void PluginFillRandomColorsBlackAndWhiteName(
	const char* path, int frameId);

// Class Plugin
ChromaAnimationAPI::FillRandomColorsBlackAndWhiteName(
	const char* path, int frameId);
```

---
<a name="PluginFillRandomColorsBlackAndWhiteNameD"></a>
**PluginFillRandomColorsBlackAndWhiteNameD**

```C++
// DLL Interface
EXPORT_API double PluginFillRandomColorsBlackAndWhiteNameD(
	const char* path, double frameId);

// Class Plugin
double result = ChromaAnimationAPI::FillRandomColorsBlackAndWhiteNameD(
	const char* path, double frameId);
```

---
<a name="PluginFillRandomColorsName"></a>
**PluginFillRandomColorsName**

```C++
// DLL Interface
EXPORT_API void PluginFillRandomColorsName(
	const char* path, int frameId);

// Class Plugin
ChromaAnimationAPI::FillRandomColorsName(
	const char* path, int frameId);
```

---
<a name="PluginFillRandomColorsNameD"></a>
**PluginFillRandomColorsNameD**

```C++
// DLL Interface
EXPORT_API double PluginFillRandomColorsNameD(
	const char* path, double frameId);

// Class Plugin
double result = ChromaAnimationAPI::FillRandomColorsNameD(
	const char* path, double frameId);
```

---
<a name="PluginFillThresholdColors"></a>
**PluginFillThresholdColors**

```C++
// DLL Interface
EXPORT_API void PluginFillThresholdColors(
	int animationId, int frameId, int threshold, int color);

// Class Plugin
ChromaAnimationAPI::FillThresholdColors(
	int animationId, int frameId, int threshold, int color);
```

---
<a name="PluginFillThresholdColorsAllFrames"></a>
**PluginFillThresholdColorsAllFrames**

```C++
// DLL Interface
EXPORT_API void PluginFillThresholdColorsAllFrames(
	int animationId, int threshold, int color);

// Class Plugin
ChromaAnimationAPI::FillThresholdColorsAllFrames(
	int animationId, int threshold, int color);
```

---
<a name="PluginFillThresholdColorsAllFramesName"></a>
**PluginFillThresholdColorsAllFramesName**

```C++
// DLL Interface
EXPORT_API void PluginFillThresholdColorsAllFramesName(
	const char* path, int threshold, int color);

// Class Plugin
ChromaAnimationAPI::FillThresholdColorsAllFramesName(
	const char* path, int threshold, int color);
```

---
<a name="PluginFillThresholdColorsAllFramesNameD"></a>
**PluginFillThresholdColorsAllFramesNameD**

```C++
// DLL Interface
EXPORT_API double PluginFillThresholdColorsAllFramesNameD(
	const char* path, double threshold, double color);

// Class Plugin
double result = ChromaAnimationAPI::FillThresholdColorsAllFramesNameD(
	const char* path, double threshold, double color);
```

---
<a name="PluginFillThresholdColorsAllFramesRGB"></a>
**PluginFillThresholdColorsAllFramesRGB**

```C++
// DLL Interface
EXPORT_API void PluginFillThresholdColorsAllFramesRGB(
	int animationId, int threshold, int red, int green, int blue);

// Class Plugin
ChromaAnimationAPI::FillThresholdColorsAllFramesRGB(
	int animationId, int threshold, int red, int green, int blue);
```

---
<a name="PluginFillThresholdColorsAllFramesRGBName"></a>
**PluginFillThresholdColorsAllFramesRGBName**

```C++
// DLL Interface
EXPORT_API void PluginFillThresholdColorsAllFramesRGBName(
	const char* path, int threshold, int red, int green, int blue);

// Class Plugin
ChromaAnimationAPI::FillThresholdColorsAllFramesRGBName(
	const char* path, int threshold, int red, int green, int blue);
```

---
<a name="PluginFillThresholdColorsAllFramesRGBNameD"></a>
**PluginFillThresholdColorsAllFramesRGBNameD**

```C++
// DLL Interface
EXPORT_API double PluginFillThresholdColorsAllFramesRGBNameD(
	const char* path, double threshold, double red, double green, double blue);

// Class Plugin
double result = ChromaAnimationAPI::FillThresholdColorsAllFramesRGBNameD(
	const char* path, double threshold, double red, double green, double blue);
```

---
<a name="PluginFillThresholdColorsMinMaxAllFramesRGB"></a>
**PluginFillThresholdColorsMinMaxAllFramesRGB**

```C++
// DLL Interface
EXPORT_API void PluginFillThresholdColorsMinMaxAllFramesRGB(
	int animationId, int minThreshold, int minRed, int minGreen, int minBlue,
	int maxThreshold, int maxRed, int maxGreen, int maxBlue);

// Class Plugin
ChromaAnimationAPI::FillThresholdColorsMinMaxAllFramesRGB(
	int animationId, int minThreshold, int minRed, int minGreen, int minBlue,
	int maxThreshold, int maxRed, int maxGreen, int maxBlue);
```

---
<a name="PluginFillThresholdColorsMinMaxAllFramesRGBName"></a>
**PluginFillThresholdColorsMinMaxAllFramesRGBName**

```C++
// DLL Interface
EXPORT_API void PluginFillThresholdColorsMinMaxAllFramesRGBName(
	const char* path, int minThreshold, int minRed, int minGreen, int minBlue,
	int maxThreshold, int maxRed, int maxGreen, int maxBlue);

// Class Plugin
ChromaAnimationAPI::FillThresholdColorsMinMaxAllFramesRGBName(
	const char* path, int minThreshold, int minRed, int minGreen, int minBlue,
	int maxThreshold, int maxRed, int maxGreen, int maxBlue);
```

---
<a name="PluginFillThresholdColorsMinMaxAllFramesRGBNameD"></a>
**PluginFillThresholdColorsMinMaxAllFramesRGBNameD**

```C++
// DLL Interface
EXPORT_API double PluginFillThresholdColorsMinMaxAllFramesRGBNameD(
	const char* path, double minThreshold, double minRed, double minGreen, double minBlue,
	double maxThreshold, double maxRed, double maxGreen, double maxBlue);

// Class Plugin
double result = ChromaAnimationAPI::FillThresholdColorsMinMaxAllFramesRGBNameD(
	const char* path, double minThreshold, double minRed, double minGreen, double minBlue,
	double maxThreshold, double maxRed, double maxGreen, double maxBlue);
```

---
<a name="PluginFillThresholdColorsMinMaxRGB"></a>
**PluginFillThresholdColorsMinMaxRGB**

```C++
// DLL Interface
EXPORT_API void PluginFillThresholdColorsMinMaxRGB(
	int animationId, int frameId, int minThreshold, int minRed, int minGreen,
	int minBlue, int maxThreshold, int maxRed, int maxGreen, int maxBlue);

// Class Plugin
ChromaAnimationAPI::FillThresholdColorsMinMaxRGB(
	int animationId, int frameId, int minThreshold, int minRed, int minGreen,
	int minBlue, int maxThreshold, int maxRed, int maxGreen, int maxBlue);
```

---
<a name="PluginFillThresholdColorsMinMaxRGBName"></a>
**PluginFillThresholdColorsMinMaxRGBName**

```C++
// DLL Interface
EXPORT_API void PluginFillThresholdColorsMinMaxRGBName(
	const char* path, int frameId, int minThreshold, int minRed, int minGreen,
	int minBlue, int maxThreshold, int maxRed, int maxGreen, int maxBlue);

// Class Plugin
ChromaAnimationAPI::FillThresholdColorsMinMaxRGBName(
	const char* path, int frameId, int minThreshold, int minRed, int minGreen,
	int minBlue, int maxThreshold, int maxRed, int maxGreen, int maxBlue);
```

---
<a name="PluginFillThresholdColorsMinMaxRGBNameD"></a>
**PluginFillThresholdColorsMinMaxRGBNameD**

```C++
// DLL Interface
EXPORT_API double PluginFillThresholdColorsMinMaxRGBNameD(
	const char* path, double frameId, double minThreshold, double minRed, double minGreen,
	double minBlue, double maxThreshold, double maxRed, double maxGreen, double maxBlue);

// Class Plugin
double result = ChromaAnimationAPI::FillThresholdColorsMinMaxRGBNameD(
	const char* path, double frameId, double minThreshold, double minRed, double minGreen,
	double minBlue, double maxThreshold, double maxRed, double maxGreen, double maxBlue);
```

---
<a name="PluginFillThresholdColorsName"></a>
**PluginFillThresholdColorsName**

```C++
// DLL Interface
EXPORT_API void PluginFillThresholdColorsName(
	const char* path, int frameId, int threshold, int color);

// Class Plugin
ChromaAnimationAPI::FillThresholdColorsName(
	const char* path, int frameId, int threshold, int color);
```

---
<a name="PluginFillThresholdColorsNameD"></a>
**PluginFillThresholdColorsNameD**

```C++
// DLL Interface
EXPORT_API double PluginFillThresholdColorsNameD(
	const char* path, double frameId, double threshold, double color);

// Class Plugin
double result = ChromaAnimationAPI::FillThresholdColorsNameD(
	const char* path, double frameId, double threshold, double color);
```

---
<a name="PluginFillThresholdColorsRGB"></a>
**PluginFillThresholdColorsRGB**

```C++
// DLL Interface
EXPORT_API void PluginFillThresholdColorsRGB(
	int animationId, int frameId, int threshold, int red, int green, int blue);

// Class Plugin
ChromaAnimationAPI::FillThresholdColorsRGB(
	int animationId, int frameId, int threshold, int red, int green, int blue);
```

---
<a name="PluginFillThresholdColorsRGBName"></a>
**PluginFillThresholdColorsRGBName**

```C++
// DLL Interface
EXPORT_API void PluginFillThresholdColorsRGBName(
	const char* path, int frameId, int threshold, int red, int green, int blue);

// Class Plugin
ChromaAnimationAPI::FillThresholdColorsRGBName(
	const char* path, int frameId, int threshold, int red, int green, int blue);
```

---
<a name="PluginFillThresholdColorsRGBNameD"></a>
**PluginFillThresholdColorsRGBNameD**

```C++
// DLL Interface
EXPORT_API double PluginFillThresholdColorsRGBNameD(
	const char* path, double frameId, double threshold, double red, double green,
	double blue);

// Class Plugin
double result = ChromaAnimationAPI::FillThresholdColorsRGBNameD(
	const char* path, double frameId, double threshold, double red, double green,
	double blue);
```

---
<a name="PluginFillThresholdRGBColorsAllFramesRGB"></a>
**PluginFillThresholdRGBColorsAllFramesRGB**

```C++
// DLL Interface
EXPORT_API void PluginFillThresholdRGBColorsAllFramesRGB(
	int animationId, int redThreshold, int greenThreshold, int blueThreshold,
	int red, int green, int blue);

// Class Plugin
ChromaAnimationAPI::FillThresholdRGBColorsAllFramesRGB(
	int animationId, int redThreshold, int greenThreshold, int blueThreshold,
	int red, int green, int blue);
```

---
<a name="PluginFillThresholdRGBColorsAllFramesRGBName"></a>
**PluginFillThresholdRGBColorsAllFramesRGBName**

```C++
// DLL Interface
EXPORT_API void PluginFillThresholdRGBColorsAllFramesRGBName(
	const char* path, int redThreshold, int greenThreshold, int blueThreshold,
	int red, int green, int blue);

// Class Plugin
ChromaAnimationAPI::FillThresholdRGBColorsAllFramesRGBName(
	const char* path, int redThreshold, int greenThreshold, int blueThreshold,
	int red, int green, int blue);
```

---
<a name="PluginFillThresholdRGBColorsAllFramesRGBNameD"></a>
**PluginFillThresholdRGBColorsAllFramesRGBNameD**

```C++
// DLL Interface
EXPORT_API double PluginFillThresholdRGBColorsAllFramesRGBNameD(
	const char* path, double redThreshold, double greenThreshold, double blueThreshold,
	double red, double green, double blue);

// Class Plugin
double result = ChromaAnimationAPI::FillThresholdRGBColorsAllFramesRGBNameD(
	const char* path, double redThreshold, double greenThreshold, double blueThreshold,
	double red, double green, double blue);
```

---
<a name="PluginFillThresholdRGBColorsRGB"></a>
**PluginFillThresholdRGBColorsRGB**

```C++
// DLL Interface
EXPORT_API void PluginFillThresholdRGBColorsRGB(
	int animationId, int frameId, int redThreshold, int greenThreshold, int blueThreshold,
	int red, int green, int blue);

// Class Plugin
ChromaAnimationAPI::FillThresholdRGBColorsRGB(
	int animationId, int frameId, int redThreshold, int greenThreshold, int blueThreshold,
	int red, int green, int blue);
```

---
<a name="PluginFillThresholdRGBColorsRGBName"></a>
**PluginFillThresholdRGBColorsRGBName**

```C++
// DLL Interface
EXPORT_API void PluginFillThresholdRGBColorsRGBName(
	const char* path, int frameId, int redThreshold, int greenThreshold, int blueThreshold,
	int red, int green, int blue);

// Class Plugin
ChromaAnimationAPI::FillThresholdRGBColorsRGBName(
	const char* path, int frameId, int redThreshold, int greenThreshold, int blueThreshold,
	int red, int green, int blue);
```

---
<a name="PluginFillThresholdRGBColorsRGBNameD"></a>
**PluginFillThresholdRGBColorsRGBNameD**

```C++
// DLL Interface
EXPORT_API double PluginFillThresholdRGBColorsRGBNameD(
	const char* path, double frameId, double redThreshold, double greenThreshold,
	double blueThreshold, double red, double green, double blue);

// Class Plugin
double result = ChromaAnimationAPI::FillThresholdRGBColorsRGBNameD(
	const char* path, double frameId, double redThreshold, double greenThreshold,
	double blueThreshold, double red, double green, double blue);
```

---
<a name="PluginFillZeroColor"></a>
**PluginFillZeroColor**

```C++
// DLL Interface
EXPORT_API void PluginFillZeroColor(
	int animationId, int frameId, int color);

// Class Plugin
ChromaAnimationAPI::FillZeroColor(
	int animationId, int frameId, int color);
```

---
<a name="PluginFillZeroColorAllFrames"></a>
**PluginFillZeroColorAllFrames**

```C++
// DLL Interface
EXPORT_API void PluginFillZeroColorAllFrames(
	int animationId, int color);

// Class Plugin
ChromaAnimationAPI::FillZeroColorAllFrames(
	int animationId, int color);
```

---
<a name="PluginFillZeroColorAllFramesName"></a>
**PluginFillZeroColorAllFramesName**

```C++
// DLL Interface
EXPORT_API void PluginFillZeroColorAllFramesName(
	const char* path, int color);

// Class Plugin
ChromaAnimationAPI::FillZeroColorAllFramesName(
	const char* path, int color);
```

---
<a name="PluginFillZeroColorAllFramesNameD"></a>
**PluginFillZeroColorAllFramesNameD**

```C++
// DLL Interface
EXPORT_API double PluginFillZeroColorAllFramesNameD(
	const char* path, double color);

// Class Plugin
double result = ChromaAnimationAPI::FillZeroColorAllFramesNameD(
	const char* path, double color);
```

---
<a name="PluginFillZeroColorAllFramesRGB"></a>
**PluginFillZeroColorAllFramesRGB**

```C++
// DLL Interface
EXPORT_API void PluginFillZeroColorAllFramesRGB(
	int animationId, int red, int green, int blue);

// Class Plugin
ChromaAnimationAPI::FillZeroColorAllFramesRGB(
	int animationId, int red, int green, int blue);
```

---
<a name="PluginFillZeroColorAllFramesRGBName"></a>
**PluginFillZeroColorAllFramesRGBName**

```C++
// DLL Interface
EXPORT_API void PluginFillZeroColorAllFramesRGBName(
	const char* path, int red, int green, int blue);

// Class Plugin
ChromaAnimationAPI::FillZeroColorAllFramesRGBName(
	const char* path, int red, int green, int blue);
```

---
<a name="PluginFillZeroColorAllFramesRGBNameD"></a>
**PluginFillZeroColorAllFramesRGBNameD**

```C++
// DLL Interface
EXPORT_API double PluginFillZeroColorAllFramesRGBNameD(
	const char* path, double red, double green, double blue);

// Class Plugin
double result = ChromaAnimationAPI::FillZeroColorAllFramesRGBNameD(
	const char* path, double red, double green, double blue);
```

---
<a name="PluginFillZeroColorName"></a>
**PluginFillZeroColorName**

```C++
// DLL Interface
EXPORT_API void PluginFillZeroColorName(
	const char* path, int frameId, int color);

// Class Plugin
ChromaAnimationAPI::FillZeroColorName(
	const char* path, int frameId, int color);
```

---
<a name="PluginFillZeroColorNameD"></a>
**PluginFillZeroColorNameD**

```C++
// DLL Interface
EXPORT_API double PluginFillZeroColorNameD(
	const char* path, double frameId, double color);

// Class Plugin
double result = ChromaAnimationAPI::FillZeroColorNameD(
	const char* path, double frameId, double color);
```

---
<a name="PluginFillZeroColorRGB"></a>
**PluginFillZeroColorRGB**

```C++
// DLL Interface
EXPORT_API void PluginFillZeroColorRGB(
	int animationId, int frameId, int red, int green, int blue);

// Class Plugin
ChromaAnimationAPI::FillZeroColorRGB(
	int animationId, int frameId, int red, int green, int blue);
```

---
<a name="PluginFillZeroColorRGBName"></a>
**PluginFillZeroColorRGBName**

```C++
// DLL Interface
EXPORT_API void PluginFillZeroColorRGBName(
	const char* path, int frameId, int red, int green, int blue);

// Class Plugin
ChromaAnimationAPI::FillZeroColorRGBName(
	const char* path, int frameId, int red, int green, int blue);
```

---
<a name="PluginFillZeroColorRGBNameD"></a>
**PluginFillZeroColorRGBNameD**

```C++
// DLL Interface
EXPORT_API double PluginFillZeroColorRGBNameD(
	const char* path, double frameId, double red, double green, double blue);

// Class Plugin
double result = ChromaAnimationAPI::FillZeroColorRGBNameD(
	const char* path, double frameId, double red, double green, double blue);
```

---
<a name="PluginGet1DColor"></a>
**PluginGet1DColor**

```C++
// DLL Interface
EXPORT_API int PluginGet1DColor(
	int animationId, int frameId, int led);

// Class Plugin
int result = ChromaAnimationAPI::Get1DColor(
	int animationId, int frameId, int led);
```

---
<a name="PluginGet1DColorName"></a>
**PluginGet1DColorName**

Get the animation color for a frame given the `1D` `led`. The `led` should
be greater than or equal to 0 and less than the `MaxLeds`.

```C++
// DLL Interface
EXPORT_API int PluginGet1DColorName(
	const char* path, int frameId, int led);

// Class Plugin
int result = ChromaAnimationAPI::Get1DColorName(
	const char* path, int frameId, int led);
```

---
<a name="PluginGet1DColorNameD"></a>
**PluginGet1DColorNameD**

```C++
// DLL Interface
EXPORT_API double PluginGet1DColorNameD(
	const char* path, double frameId, double led);

// Class Plugin
double result = ChromaAnimationAPI::Get1DColorNameD(
	const char* path, double frameId, double led);
```

---
<a name="PluginGet2DColor"></a>
**PluginGet2DColor**

```C++
// DLL Interface
EXPORT_API int PluginGet2DColor(
	int animationId, int frameId, int row, int column);

// Class Plugin
int result = ChromaAnimationAPI::Get2DColor(
	int animationId, int frameId, int row, int column);
```

---
<a name="PluginGet2DColorName"></a>
**PluginGet2DColorName**

Get the animation color for a frame given the `2D` `row` and `column`. The
`row` should be greater than or equal to 0 and less than the `MaxRow`.
The `column` should be greater than or equal to 0 and less than the `MaxColumn`.

```C++
// DLL Interface
EXPORT_API int PluginGet2DColorName(
	const char* path, int frameId, int row, int column);

// Class Plugin
int result = ChromaAnimationAPI::Get2DColorName(
	const char* path, int frameId, int row, int column);
```

---
<a name="PluginGet2DColorNameD"></a>
**PluginGet2DColorNameD**

```C++
// DLL Interface
EXPORT_API double PluginGet2DColorNameD(
	const char* path, double frameId, double row, double column);

// Class Plugin
double result = ChromaAnimationAPI::Get2DColorNameD(
	const char* path, double frameId, double row, double column);
```

---
<a name="PluginGetAnimation"></a>
**PluginGetAnimation**

```C++
// DLL Interface
EXPORT_API int PluginGetAnimation(const char* name);

// Class Plugin
int result = ChromaAnimationAPI::GetAnimation(const char* name);
```

---
<a name="PluginGetAnimationCount"></a>
**PluginGetAnimationCount**

`PluginGetAnimationCount` will return the number of loaded animations.

```C++
// DLL Interface
EXPORT_API int PluginGetAnimationCount();

// Class Plugin
int result = ChromaAnimationAPI::GetAnimationCount();
```

---
<a name="PluginGetAnimationD"></a>
**PluginGetAnimationD**

```C++
// DLL Interface
EXPORT_API double PluginGetAnimationD(const char* name);

// Class Plugin
double result = ChromaAnimationAPI::GetAnimationD(const char* name);
```

---
<a name="PluginGetAnimationId"></a>
**PluginGetAnimationId**

`PluginGetAnimationId` will return the `animationId` given the `index` of
the loaded animation. The `index` is zero-based and less than the number
returned by `PluginGetAnimationCount`. Use `PluginGetAnimationName` to
get the name of the animation.

```C++
// DLL Interface
EXPORT_API int PluginGetAnimationId(int index);

// Class Plugin
int result = ChromaAnimationAPI::GetAnimationId(int index);
```

---
<a name="PluginGetAnimationName"></a>
**PluginGetAnimationName**

`PluginGetAnimationName` takes an `animationId` and returns the name of
the animation of the `.chroma` animation file. If a name is not available
then an empty string will be returned.

```C++
// DLL Interface
EXPORT_API const char* PluginGetAnimationName(int animationId);

// Class Plugin
const char* result = ChromaAnimationAPI::GetAnimationName(int animationId);
```

---
<a name="PluginGetCurrentFrame"></a>
**PluginGetCurrentFrame**

Get the current frame of the animation referenced by id.

```C++
// DLL Interface
EXPORT_API int PluginGetCurrentFrame(int animationId);

// Class Plugin
int result = ChromaAnimationAPI::GetCurrentFrame(int animationId);
```

---
<a name="PluginGetCurrentFrameName"></a>
**PluginGetCurrentFrameName**

Get the current frame of the animation referenced by name.

```C++
// DLL Interface
EXPORT_API int PluginGetCurrentFrameName(const char* path);

// Class Plugin
int result = ChromaAnimationAPI::GetCurrentFrameName(const char* path);
```

---
<a name="PluginGetCurrentFrameNameD"></a>
**PluginGetCurrentFrameNameD**

```C++
// DLL Interface
EXPORT_API double PluginGetCurrentFrameNameD(const char* path);

// Class Plugin
double result = ChromaAnimationAPI::GetCurrentFrameNameD(const char* path);
```

---
<a name="PluginGetDevice"></a>
**PluginGetDevice**

Returns the `EChromaSDKDevice1DEnum` or `EChromaSDKDevice2DEnum` of a `Chroma`
animation respective to the `deviceType`, as an integer upon success. Returns
-1 upon failure.

```C++
// DLL Interface
EXPORT_API int PluginGetDevice(int animationId);

// Class Plugin
int result = ChromaAnimationAPI::GetDevice(int animationId);
```

---
<a name="PluginGetDeviceName"></a>
**PluginGetDeviceName**

Returns the `EChromaSDKDevice1DEnum` or `EChromaSDKDevice2DEnum` of a `Chroma`
animation respective to the `deviceType`, as an integer upon success. Returns
-1 upon failure.

```C++
// DLL Interface
EXPORT_API int PluginGetDeviceName(const char* path);

// Class Plugin
int result = ChromaAnimationAPI::GetDeviceName(const char* path);
```

---
<a name="PluginGetDeviceNameD"></a>
**PluginGetDeviceNameD**

```C++
// DLL Interface
EXPORT_API double PluginGetDeviceNameD(const char* path);

// Class Plugin
double result = ChromaAnimationAPI::GetDeviceNameD(const char* path);
```

---
<a name="PluginGetDeviceType"></a>
**PluginGetDeviceType**

Returns the `EChromaSDKDeviceTypeEnum` of a `Chroma` animation as an integer
upon success. Returns -1 upon failure.

```C++
// DLL Interface
EXPORT_API int PluginGetDeviceType(int animationId);

// Class Plugin
int result = ChromaAnimationAPI::GetDeviceType(int animationId);
```

---
<a name="PluginGetDeviceTypeName"></a>
**PluginGetDeviceTypeName**

Returns the `EChromaSDKDeviceTypeEnum` of a `Chroma` animation as an integer
upon success. Returns -1 upon failure.

```C++
// DLL Interface
EXPORT_API int PluginGetDeviceTypeName(const char* path);

// Class Plugin
int result = ChromaAnimationAPI::GetDeviceTypeName(const char* path);
```

---
<a name="PluginGetDeviceTypeNameD"></a>
**PluginGetDeviceTypeNameD**

```C++
// DLL Interface
EXPORT_API double PluginGetDeviceTypeNameD(const char* path);

// Class Plugin
double result = ChromaAnimationAPI::GetDeviceTypeNameD(const char* path);
```

---
<a name="PluginGetFrame"></a>
**PluginGetFrame**

Gets the frame colors and duration (in seconds) for a `Chroma` animation.
The `color` is expected to be an array of the expected dimensions for the
`deviceType/device`. The `length` parameter is the size of the `color`
array. For `EChromaSDKDevice1DEnum` the array size should be `MAX LEDS`.
For `EChromaSDKDevice2DEnum` the array size should be `MAX ROW` * `MAX
COLUMN`. Returns the animation id upon success. Returns -1 upon failure.

```C++
// DLL Interface
EXPORT_API int PluginGetFrame(
	int animationId, int frameIndex, float* duration, int* colors, int length);

// Class Plugin
int result = ChromaAnimationAPI::GetFrame(
	int animationId, int frameIndex, float* duration, int* colors, int length);
```

---
<a name="PluginGetFrameCount"></a>
**PluginGetFrameCount**

Returns the frame count of a `Chroma` animation upon success. Returns -1
upon failure.

```C++
// DLL Interface
EXPORT_API int PluginGetFrameCount(int animationId);

// Class Plugin
int result = ChromaAnimationAPI::GetFrameCount(int animationId);
```

---
<a name="PluginGetFrameCountName"></a>
**PluginGetFrameCountName**

Returns the frame count of a `Chroma` animation upon success. Returns -1
upon failure.

```C++
// DLL Interface
EXPORT_API int PluginGetFrameCountName(const char* path);

// Class Plugin
int result = ChromaAnimationAPI::GetFrameCountName(const char* path);
```

---
<a name="PluginGetFrameCountNameD"></a>
**PluginGetFrameCountNameD**

```C++
// DLL Interface
EXPORT_API double PluginGetFrameCountNameD(const char* path);

// Class Plugin
double result = ChromaAnimationAPI::GetFrameCountNameD(const char* path);
```

---
<a name="PluginGetKeyColor"></a>
**PluginGetKeyColor**

Get the color of an animation key for the given frame referenced by id.

```C++
// DLL Interface
EXPORT_API int PluginGetKeyColor(
	int animationId, int frameId, int rzkey);

// Class Plugin
int result = ChromaAnimationAPI::GetKeyColor(
	int animationId, int frameId, int rzkey);
```

---
<a name="PluginGetKeyColorD"></a>
**PluginGetKeyColorD**

```C++
// DLL Interface
EXPORT_API double PluginGetKeyColorD(
	const char* path, double frameId, double rzkey);

// Class Plugin
double result = ChromaAnimationAPI::GetKeyColorD(
	const char* path, double frameId, double rzkey);
```

---
<a name="PluginGetKeyColorName"></a>
**PluginGetKeyColorName**

Get the color of an animation key for the given frame referenced by name.

```C++
// DLL Interface
EXPORT_API int PluginGetKeyColorName(
	const char* path, int frameId, int rzkey);

// Class Plugin
int result = ChromaAnimationAPI::GetKeyColorName(
	const char* path, int frameId, int rzkey);
```

---
<a name="PluginGetMaxColumn"></a>
**PluginGetMaxColumn**

Returns the `MAX COLUMN` given the `EChromaSDKDevice2DEnum` device as an
integer upon success. Returns -1 upon failure.

```C++
// DLL Interface
EXPORT_API int PluginGetMaxColumn(int device);

// Class Plugin
int result = ChromaAnimationAPI::GetMaxColumn(int device);
```

---
<a name="PluginGetMaxColumnD"></a>
**PluginGetMaxColumnD**

```C++
// DLL Interface
EXPORT_API double PluginGetMaxColumnD(double device);

// Class Plugin
double result = ChromaAnimationAPI::GetMaxColumnD(double device);
```

---
<a name="PluginGetMaxLeds"></a>
**PluginGetMaxLeds**

Returns the MAX LEDS given the `EChromaSDKDevice1DEnum` device as an integer
upon success. Returns -1 upon failure.

```C++
// DLL Interface
EXPORT_API int PluginGetMaxLeds(int device);

// Class Plugin
int result = ChromaAnimationAPI::GetMaxLeds(int device);
```

---
<a name="PluginGetMaxLedsD"></a>
**PluginGetMaxLedsD**

```C++
// DLL Interface
EXPORT_API double PluginGetMaxLedsD(double device);

// Class Plugin
double result = ChromaAnimationAPI::GetMaxLedsD(double device);
```

---
<a name="PluginGetMaxRow"></a>
**PluginGetMaxRow**

Returns the `MAX ROW` given the `EChromaSDKDevice2DEnum` device as an integer
upon success. Returns -1 upon failure.

```C++
// DLL Interface
EXPORT_API int PluginGetMaxRow(int device);

// Class Plugin
int result = ChromaAnimationAPI::GetMaxRow(int device);
```

---
<a name="PluginGetMaxRowD"></a>
**PluginGetMaxRowD**

```C++
// DLL Interface
EXPORT_API double PluginGetMaxRowD(double device);

// Class Plugin
double result = ChromaAnimationAPI::GetMaxRowD(double device);
```

---
<a name="PluginGetPlayingAnimationCount"></a>
**PluginGetPlayingAnimationCount**

`PluginGetPlayingAnimationCount` will return the number of playing animations.

```C++
// DLL Interface
EXPORT_API int PluginGetPlayingAnimationCount();

// Class Plugin
int result = ChromaAnimationAPI::GetPlayingAnimationCount();
```

---
<a name="PluginGetPlayingAnimationId"></a>
**PluginGetPlayingAnimationId**

```C++
// DLL Interface
EXPORT_API int PluginGetPlayingAnimationId(int index);

// Class Plugin
int result = ChromaAnimationAPI::GetPlayingAnimationId(int index);
```

---
<a name="PluginGetRGB"></a>
**PluginGetRGB**

`PluginGetPlayingAnimationId` will return the `animationId` given the `index`
of the playing animation. The `index` is zero-based and less than the number
returned by `PluginGetPlayingAnimationCount`. Use `PluginGetAnimationName`
to get the name of the animation.

```C++
// DLL Interface
EXPORT_API int PluginGetRGB(
	int red, int green, int blue);

// Class Plugin
int result = ChromaAnimationAPI::GetRGB(
	int red, int green, int blue);
```

---
<a name="PluginGetRGBD"></a>
**PluginGetRGBD**

```C++
// DLL Interface
EXPORT_API double PluginGetRGBD(
	double red, double green, double blue);

// Class Plugin
double result = ChromaAnimationAPI::GetRGBD(
	double red, double green, double blue);
```

---
<a name="PluginHasAnimationLoop"></a>
**PluginHasAnimationLoop**

Check if the animation has loop enabled referenced by id.

```C++
// DLL Interface
EXPORT_API bool PluginHasAnimationLoop(int animationId);

// Class Plugin
bool result = ChromaAnimationAPI::HasAnimationLoop(int animationId);
```

---
<a name="PluginHasAnimationLoopName"></a>
**PluginHasAnimationLoopName**

Check if the animation has loop enabled referenced by name.

```C++
// DLL Interface
EXPORT_API bool PluginHasAnimationLoopName(const char* path);

// Class Plugin
bool result = ChromaAnimationAPI::HasAnimationLoopName(const char* path);
```

---
<a name="PluginHasAnimationLoopNameD"></a>
**PluginHasAnimationLoopNameD**

```C++
// DLL Interface
EXPORT_API double PluginHasAnimationLoopNameD(const char* path);

// Class Plugin
double result = ChromaAnimationAPI::HasAnimationLoopNameD(const char* path);
```

---
<a name="PluginInit"></a>
**PluginInit**

Initialize the ChromaSDK. Zero indicates  success, otherwise failure. Many
API methods auto initialize the ChromaSDK if not already initialized.

```C++
// DLL Interface
EXPORT_API int PluginInit();

// Class Plugin
int result = ChromaAnimationAPI::Init();
```

---
<a name="PluginInitD"></a>
**PluginInitD**

```C++
// DLL Interface
EXPORT_API double PluginInitD();

// Class Plugin
double result = ChromaAnimationAPI::InitD();
```

---
<a name="PluginInsertDelay"></a>
**PluginInsertDelay**

```C++
// DLL Interface
EXPORT_API void PluginInsertDelay(
	int animationId, int frameId, int delay);

// Class Plugin
ChromaAnimationAPI::InsertDelay(
	int animationId, int frameId, int delay);
```

---
<a name="PluginInsertDelayName"></a>
**PluginInsertDelayName**

```C++
// DLL Interface
EXPORT_API void PluginInsertDelayName(
	const char* path, int frameId, int delay);

// Class Plugin
ChromaAnimationAPI::InsertDelayName(
	const char* path, int frameId, int delay);
```

---
<a name="PluginInsertDelayNameD"></a>
**PluginInsertDelayNameD**

```C++
// DLL Interface
EXPORT_API double PluginInsertDelayNameD(
	const char* path, double frameId, double delay);

// Class Plugin
double result = ChromaAnimationAPI::InsertDelayNameD(
	const char* path, double frameId, double delay);
```

---
<a name="PluginInsertFrame"></a>
**PluginInsertFrame**

```C++
// DLL Interface
EXPORT_API void PluginInsertFrame(
	int animationId, int sourceFrame, int targetFrame);

// Class Plugin
ChromaAnimationAPI::InsertFrame(
	int animationId, int sourceFrame, int targetFrame);
```

---
<a name="PluginInsertFrameName"></a>
**PluginInsertFrameName**

```C++
// DLL Interface
EXPORT_API void PluginInsertFrameName(
	const char* path, int sourceFrame, int targetFrame);

// Class Plugin
ChromaAnimationAPI::InsertFrameName(
	const char* path, int sourceFrame, int targetFrame);
```

---
<a name="PluginInsertFrameNameD"></a>
**PluginInsertFrameNameD**

```C++
// DLL Interface
EXPORT_API double PluginInsertFrameNameD(
	const char* path, double sourceFrame, double targetFrame);

// Class Plugin
double result = ChromaAnimationAPI::InsertFrameNameD(
	const char* path, double sourceFrame, double targetFrame);
```

---
<a name="PluginInvertColors"></a>
**PluginInvertColors**

```C++
// DLL Interface
EXPORT_API void PluginInvertColors(
	int animationId, int frameId);

// Class Plugin
ChromaAnimationAPI::InvertColors(
	int animationId, int frameId);
```

---
<a name="PluginInvertColorsAllFrames"></a>
**PluginInvertColorsAllFrames**

```C++
// DLL Interface
EXPORT_API void PluginInvertColorsAllFrames(int animationId);

// Class Plugin
ChromaAnimationAPI::InvertColorsAllFrames(int animationId);
```

---
<a name="PluginInvertColorsAllFramesName"></a>
**PluginInvertColorsAllFramesName**

```C++
// DLL Interface
EXPORT_API void PluginInvertColorsAllFramesName(const char* path);

// Class Plugin
ChromaAnimationAPI::InvertColorsAllFramesName(const char* path);
```

---
<a name="PluginInvertColorsAllFramesNameD"></a>
**PluginInvertColorsAllFramesNameD**

```C++
// DLL Interface
EXPORT_API double PluginInvertColorsAllFramesNameD(const char* path);

// Class Plugin
double result = ChromaAnimationAPI::InvertColorsAllFramesNameD(const char* path);
```

---
<a name="PluginInvertColorsName"></a>
**PluginInvertColorsName**

```C++
// DLL Interface
EXPORT_API void PluginInvertColorsName(
	const char* path, int frameId);

// Class Plugin
ChromaAnimationAPI::InvertColorsName(
	const char* path, int frameId);
```

---
<a name="PluginInvertColorsNameD"></a>
**PluginInvertColorsNameD**

```C++
// DLL Interface
EXPORT_API double PluginInvertColorsNameD(
	const char* path, double frameId);

// Class Plugin
double result = ChromaAnimationAPI::InvertColorsNameD(
	const char* path, double frameId);
```

---
<a name="PluginIsAnimationPaused"></a>
**PluginIsAnimationPaused**

Check if the animation is paused referenced by id.

```C++
// DLL Interface
EXPORT_API bool PluginIsAnimationPaused(int animationId);

// Class Plugin
bool result = ChromaAnimationAPI::IsAnimationPaused(int animationId);
```

---
<a name="PluginIsAnimationPausedName"></a>
**PluginIsAnimationPausedName**

Check if the animation is paused referenced by name.

```C++
// DLL Interface
EXPORT_API bool PluginIsAnimationPausedName(const char* path);

// Class Plugin
bool result = ChromaAnimationAPI::IsAnimationPausedName(const char* path);
```

---
<a name="PluginIsAnimationPausedNameD"></a>
**PluginIsAnimationPausedNameD**

```C++
// DLL Interface
EXPORT_API double PluginIsAnimationPausedNameD(const char* path);

// Class Plugin
double result = ChromaAnimationAPI::IsAnimationPausedNameD(const char* path);
```

---
<a name="PluginIsDialogOpen"></a>
**PluginIsDialogOpen**

The editor dialog is a non-blocking modal window, this method returns true
if the modal window is open, otherwise false.

```C++
// DLL Interface
EXPORT_API bool PluginIsDialogOpen();

// Class Plugin
bool result = ChromaAnimationAPI::IsDialogOpen();
```

---
<a name="PluginIsDialogOpenD"></a>
**PluginIsDialogOpenD**

```C++
// DLL Interface
EXPORT_API double PluginIsDialogOpenD();

// Class Plugin
double result = ChromaAnimationAPI::IsDialogOpenD();
```

---
<a name="PluginIsInitialized"></a>
**PluginIsInitialized**

Returns true if the plugin has been initialized. Returns false if the plugin
is uninitialized.

```C++
// DLL Interface
EXPORT_API bool PluginIsInitialized();

// Class Plugin
bool result = ChromaAnimationAPI::IsInitialized();
```

---
<a name="PluginIsInitializedD"></a>
**PluginIsInitializedD**

```C++
// DLL Interface
EXPORT_API double PluginIsInitializedD();

// Class Plugin
double result = ChromaAnimationAPI::IsInitializedD();
```

---
<a name="PluginIsPlatformSupported"></a>
**PluginIsPlatformSupported**

If the method can be invoked the method returns true.

```C++
// DLL Interface
EXPORT_API bool PluginIsPlatformSupported();

// Class Plugin
bool result = ChromaAnimationAPI::IsPlatformSupported();
```

---
<a name="PluginIsPlatformSupportedD"></a>
**PluginIsPlatformSupportedD**

```C++
// DLL Interface
EXPORT_API double PluginIsPlatformSupportedD();

// Class Plugin
double result = ChromaAnimationAPI::IsPlatformSupportedD();
```

---
<a name="PluginIsPlaying"></a>
**PluginIsPlaying**

```C++
// DLL Interface
EXPORT_API bool PluginIsPlaying(int animationId);

// Class Plugin
bool result = ChromaAnimationAPI::IsPlaying(int animationId);
```

---
<a name="PluginIsPlayingD"></a>
**PluginIsPlayingD**

```C++
// DLL Interface
EXPORT_API double PluginIsPlayingD(double animationId);

// Class Plugin
double result = ChromaAnimationAPI::IsPlayingD(double animationId);
```

---
<a name="PluginIsPlayingName"></a>
**PluginIsPlayingName**

`PluginIsPlayingName` automatically handles initializing the `ChromaSDK`.
The named `.chroma` animation file will be automatically opened. The method
will return whether the animation is playing or not.

```C++
// DLL Interface
EXPORT_API bool PluginIsPlayingName(const char* path);

// Class Plugin
bool result = ChromaAnimationAPI::IsPlayingName(const char* path);
```

---
<a name="PluginIsPlayingNameD"></a>
**PluginIsPlayingNameD**

```C++
// DLL Interface
EXPORT_API double PluginIsPlayingNameD(const char* path);

// Class Plugin
double result = ChromaAnimationAPI::IsPlayingNameD(const char* path);
```

---
<a name="PluginIsPlayingType"></a>
**PluginIsPlayingType**

`PluginIsPlayingType` automatically handles initializing the `ChromaSDK`.
If any animation is playing for the `deviceType` and `device` combination,
the method will return true, otherwise false.

```C++
// DLL Interface
EXPORT_API bool PluginIsPlayingType(
	int deviceType, int device);

// Class Plugin
bool result = ChromaAnimationAPI::IsPlayingType(
	int deviceType, int device);
```

---
<a name="PluginIsPlayingTypeD"></a>
**PluginIsPlayingTypeD**

```C++
// DLL Interface
EXPORT_API double PluginIsPlayingTypeD(
	double deviceType, double device);

// Class Plugin
double result = ChromaAnimationAPI::IsPlayingTypeD(
	double deviceType, double device);
```

---
<a name="PluginLerp"></a>
**PluginLerp**

```C++
// DLL Interface
EXPORT_API float PluginLerp(
	float start, float end, float amt);

// Class Plugin
float result = ChromaAnimationAPI::Lerp(
	float start, float end, float amt);
```

---
<a name="PluginLerpColor"></a>
**PluginLerpColor**

```C++
// DLL Interface
EXPORT_API int PluginLerpColor(
	int from, int to, float t);

// Class Plugin
int result = ChromaAnimationAPI::LerpColor(
	int from, int to, float t);
```

---
<a name="PluginLoadAnimation"></a>
**PluginLoadAnimation**

Loads `Chroma` effects so that the animation can be played immediately.
Returns the animation id upon success. Returns -1 upon failure.

```C++
// DLL Interface
EXPORT_API int PluginLoadAnimation(int animationId);

// Class Plugin
int result = ChromaAnimationAPI::LoadAnimation(int animationId);
```

---
<a name="PluginLoadAnimationD"></a>
**PluginLoadAnimationD**

```C++
// DLL Interface
EXPORT_API double PluginLoadAnimationD(double animationId);

// Class Plugin
double result = ChromaAnimationAPI::LoadAnimationD(double animationId);
```

---
<a name="PluginLoadAnimationName"></a>
**PluginLoadAnimationName**

```C++
// DLL Interface
EXPORT_API void PluginLoadAnimationName(const char* path);

// Class Plugin
ChromaAnimationAPI::LoadAnimationName(const char* path);
```

---
<a name="PluginLoadComposite"></a>
**PluginLoadComposite**

```C++
// DLL Interface
EXPORT_API void PluginLoadComposite(const char* name);

// Class Plugin
ChromaAnimationAPI::LoadComposite(const char* name);
```

---
<a name="PluginMakeBlankFrames"></a>
**PluginMakeBlankFrames**

```C++
// DLL Interface
EXPORT_API void PluginMakeBlankFrames(
	int animationId, int frameCount, float duration, int color);

// Class Plugin
ChromaAnimationAPI::MakeBlankFrames(
	int animationId, int frameCount, float duration, int color);
```

---
<a name="PluginMakeBlankFramesName"></a>
**PluginMakeBlankFramesName**

```C++
// DLL Interface
EXPORT_API void PluginMakeBlankFramesName(
	const char* path, int frameCount, float duration, int color);

// Class Plugin
ChromaAnimationAPI::MakeBlankFramesName(
	const char* path, int frameCount, float duration, int color);
```

---
<a name="PluginMakeBlankFramesNameD"></a>
**PluginMakeBlankFramesNameD**

```C++
// DLL Interface
EXPORT_API double PluginMakeBlankFramesNameD(
	const char* path, double frameCount, double duration, double color);

// Class Plugin
double result = ChromaAnimationAPI::MakeBlankFramesNameD(
	const char* path, double frameCount, double duration, double color);
```

---
<a name="PluginMakeBlankFramesRandom"></a>
**PluginMakeBlankFramesRandom**

```C++
// DLL Interface
EXPORT_API void PluginMakeBlankFramesRandom(
	int animationId, int frameCount, float duration);

// Class Plugin
ChromaAnimationAPI::MakeBlankFramesRandom(
	int animationId, int frameCount, float duration);
```

---
<a name="PluginMakeBlankFramesRandomBlackAndWhite"></a>
**PluginMakeBlankFramesRandomBlackAndWhite**

```C++
// DLL Interface
EXPORT_API void PluginMakeBlankFramesRandomBlackAndWhite(
	int animationId, int frameCount, float duration);

// Class Plugin
ChromaAnimationAPI::MakeBlankFramesRandomBlackAndWhite(
	int animationId, int frameCount, float duration);
```

---
<a name="PluginMakeBlankFramesRandomBlackAndWhiteName"></a>
**PluginMakeBlankFramesRandomBlackAndWhiteName**

```C++
// DLL Interface
EXPORT_API void PluginMakeBlankFramesRandomBlackAndWhiteName(
	const char* path, int frameCount, float duration);

// Class Plugin
ChromaAnimationAPI::MakeBlankFramesRandomBlackAndWhiteName(
	const char* path, int frameCount, float duration);
```

---
<a name="PluginMakeBlankFramesRandomBlackAndWhiteNameD"></a>
**PluginMakeBlankFramesRandomBlackAndWhiteNameD**

```C++
// DLL Interface
EXPORT_API double PluginMakeBlankFramesRandomBlackAndWhiteNameD(
	const char* path, double frameCount, double duration);

// Class Plugin
double result = ChromaAnimationAPI::MakeBlankFramesRandomBlackAndWhiteNameD(
	const char* path, double frameCount, double duration);
```

---
<a name="PluginMakeBlankFramesRandomName"></a>
**PluginMakeBlankFramesRandomName**

```C++
// DLL Interface
EXPORT_API void PluginMakeBlankFramesRandomName(
	const char* path, int frameCount, float duration);

// Class Plugin
ChromaAnimationAPI::MakeBlankFramesRandomName(
	const char* path, int frameCount, float duration);
```

---
<a name="PluginMakeBlankFramesRandomNameD"></a>
**PluginMakeBlankFramesRandomNameD**

```C++
// DLL Interface
EXPORT_API double PluginMakeBlankFramesRandomNameD(
	const char* path, double frameCount, double duration);

// Class Plugin
double result = ChromaAnimationAPI::MakeBlankFramesRandomNameD(
	const char* path, double frameCount, double duration);
```

---
<a name="PluginMakeBlankFramesRGB"></a>
**PluginMakeBlankFramesRGB**

```C++
// DLL Interface
EXPORT_API void PluginMakeBlankFramesRGB(
	int animationId, int frameCount, float duration, int red, int green, int blue);

// Class Plugin
ChromaAnimationAPI::MakeBlankFramesRGB(
	int animationId, int frameCount, float duration, int red, int green, int blue);
```

---
<a name="PluginMakeBlankFramesRGBName"></a>
**PluginMakeBlankFramesRGBName**

```C++
// DLL Interface
EXPORT_API void PluginMakeBlankFramesRGBName(
	const char* path, int frameCount, float duration, int red, int green, int blue);

// Class Plugin
ChromaAnimationAPI::MakeBlankFramesRGBName(
	const char* path, int frameCount, float duration, int red, int green, int blue);
```

---
<a name="PluginMakeBlankFramesRGBNameD"></a>
**PluginMakeBlankFramesRGBNameD**

```C++
// DLL Interface
EXPORT_API double PluginMakeBlankFramesRGBNameD(
	const char* path, double frameCount, double duration, double red, double green,
	double blue);

// Class Plugin
double result = ChromaAnimationAPI::MakeBlankFramesRGBNameD(
	const char* path, double frameCount, double duration, double red, double green,
	double blue);
```

---
<a name="PluginMirrorHorizontally"></a>
**PluginMirrorHorizontally**

Flips the color grid horizontally for all `Chroma` animation frames. Returns
the animation id upon success. Returns -1 upon failure.

```C++
// DLL Interface
EXPORT_API int PluginMirrorHorizontally(int animationId);

// Class Plugin
int result = ChromaAnimationAPI::MirrorHorizontally(int animationId);
```

---
<a name="PluginMirrorVertically"></a>
**PluginMirrorVertically**

Flips the color grid vertically for all `Chroma` animation frames. This
method has no effect for `EChromaSDKDevice1DEnum` devices. Returns the
animation id upon success. Returns -1 upon failure.

```C++
// DLL Interface
EXPORT_API int PluginMirrorVertically(int animationId);

// Class Plugin
int result = ChromaAnimationAPI::MirrorVertically(int animationId);
```

---
<a name="PluginMultiplyColorLerpAllFrames"></a>
**PluginMultiplyColorLerpAllFrames**

```C++
// DLL Interface
EXPORT_API void PluginMultiplyColorLerpAllFrames(
	int animationId, int color1, int color2);

// Class Plugin
ChromaAnimationAPI::MultiplyColorLerpAllFrames(
	int animationId, int color1, int color2);
```

---
<a name="PluginMultiplyColorLerpAllFramesName"></a>
**PluginMultiplyColorLerpAllFramesName**

```C++
// DLL Interface
EXPORT_API void PluginMultiplyColorLerpAllFramesName(
	const char* path, int color1, int color2);

// Class Plugin
ChromaAnimationAPI::MultiplyColorLerpAllFramesName(
	const char* path, int color1, int color2);
```

---
<a name="PluginMultiplyColorLerpAllFramesNameD"></a>
**PluginMultiplyColorLerpAllFramesNameD**

```C++
// DLL Interface
EXPORT_API double PluginMultiplyColorLerpAllFramesNameD(
	const char* path, double color1, double color2);

// Class Plugin
double result = ChromaAnimationAPI::MultiplyColorLerpAllFramesNameD(
	const char* path, double color1, double color2);
```

---
<a name="PluginMultiplyIntensity"></a>
**PluginMultiplyIntensity**

Multiply all the colors in the frame by the intensity value. The valid the
intensity range is from 0.0 to 255.0. RGB components are multiplied equally.
An intensity of 0.5 would half the color value. Black colors in the frame
will not be affected by this method.

```C++
// DLL Interface
EXPORT_API void PluginMultiplyIntensity(
	int animationId, int frameId, float intensity);

// Class Plugin
ChromaAnimationAPI::MultiplyIntensity(
	int animationId, int frameId, float intensity);
```

---
<a name="PluginMultiplyIntensityAllFrames"></a>
**PluginMultiplyIntensityAllFrames**

Multiply all the colors for all frames by the intensity value. The valid
the intensity range is from 0.0 to 255.0. RGB components are multiplied
equally. An intensity of 0.5 would half the color value. Black colors in
the frame will not be affected by this method.

```C++
// DLL Interface
EXPORT_API void PluginMultiplyIntensityAllFrames(
	int animationId, float intensity);

// Class Plugin
ChromaAnimationAPI::MultiplyIntensityAllFrames(
	int animationId, float intensity);
```

---
<a name="PluginMultiplyIntensityAllFramesName"></a>
**PluginMultiplyIntensityAllFramesName**

Multiply all the colors for all frames by the intensity value. The valid
the intensity range is from 0.0 to 255.0. RGB components are multiplied
equally. An intensity of 0.5 would half the color value. Black colors in
the frame will not be affected by this method.

```C++
// DLL Interface
EXPORT_API void PluginMultiplyIntensityAllFramesName(
	const char* path, float intensity);

// Class Plugin
ChromaAnimationAPI::MultiplyIntensityAllFramesName(
	const char* path, float intensity);
```

---
<a name="PluginMultiplyIntensityAllFramesNameD"></a>
**PluginMultiplyIntensityAllFramesNameD**

```C++
// DLL Interface
EXPORT_API double PluginMultiplyIntensityAllFramesNameD(
	const char* path, double intensity);

// Class Plugin
double result = ChromaAnimationAPI::MultiplyIntensityAllFramesNameD(
	const char* path, double intensity);
```

---
<a name="PluginMultiplyIntensityAllFramesRGB"></a>
**PluginMultiplyIntensityAllFramesRGB**

```C++
// DLL Interface
EXPORT_API void PluginMultiplyIntensityAllFramesRGB(
	int animationId, int red, int green, int blue);

// Class Plugin
ChromaAnimationAPI::MultiplyIntensityAllFramesRGB(
	int animationId, int red, int green, int blue);
```

---
<a name="PluginMultiplyIntensityAllFramesRGBName"></a>
**PluginMultiplyIntensityAllFramesRGBName**

```C++
// DLL Interface
EXPORT_API void PluginMultiplyIntensityAllFramesRGBName(
	const char* path, int red, int green, int blue);

// Class Plugin
ChromaAnimationAPI::MultiplyIntensityAllFramesRGBName(
	const char* path, int red, int green, int blue);
```

---
<a name="PluginMultiplyIntensityAllFramesRGBNameD"></a>
**PluginMultiplyIntensityAllFramesRGBNameD**

```C++
// DLL Interface
EXPORT_API double PluginMultiplyIntensityAllFramesRGBNameD(
	const char* path, double red, double green, double blue);

// Class Plugin
double result = ChromaAnimationAPI::MultiplyIntensityAllFramesRGBNameD(
	const char* path, double red, double green, double blue);
```

---
<a name="PluginMultiplyIntensityColor"></a>
**PluginMultiplyIntensityColor**

```C++
// DLL Interface
EXPORT_API void PluginMultiplyIntensityColor(
	int animationId, int frameId, int color);

// Class Plugin
ChromaAnimationAPI::MultiplyIntensityColor(
	int animationId, int frameId, int color);
```

---
<a name="PluginMultiplyIntensityColorAllFrames"></a>
**PluginMultiplyIntensityColorAllFrames**

```C++
// DLL Interface
EXPORT_API void PluginMultiplyIntensityColorAllFrames(
	int animationId, int color);

// Class Plugin
ChromaAnimationAPI::MultiplyIntensityColorAllFrames(
	int animationId, int color);
```

---
<a name="PluginMultiplyIntensityColorAllFramesName"></a>
**PluginMultiplyIntensityColorAllFramesName**

```C++
// DLL Interface
EXPORT_API void PluginMultiplyIntensityColorAllFramesName(
	const char* path, int color);

// Class Plugin
ChromaAnimationAPI::MultiplyIntensityColorAllFramesName(
	const char* path, int color);
```

---
<a name="PluginMultiplyIntensityColorAllFramesNameD"></a>
**PluginMultiplyIntensityColorAllFramesNameD**

```C++
// DLL Interface
EXPORT_API double PluginMultiplyIntensityColorAllFramesNameD(
	const char* path, double color);

// Class Plugin
double result = ChromaAnimationAPI::MultiplyIntensityColorAllFramesNameD(
	const char* path, double color);
```

---
<a name="PluginMultiplyIntensityColorName"></a>
**PluginMultiplyIntensityColorName**

```C++
// DLL Interface
EXPORT_API void PluginMultiplyIntensityColorName(
	const char* path, int frameId, int color);

// Class Plugin
ChromaAnimationAPI::MultiplyIntensityColorName(
	const char* path, int frameId, int color);
```

---
<a name="PluginMultiplyIntensityColorNameD"></a>
**PluginMultiplyIntensityColorNameD**

```C++
// DLL Interface
EXPORT_API double PluginMultiplyIntensityColorNameD(
	const char* path, double frameId, double color);

// Class Plugin
double result = ChromaAnimationAPI::MultiplyIntensityColorNameD(
	const char* path, double frameId, double color);
```

---
<a name="PluginMultiplyIntensityName"></a>
**PluginMultiplyIntensityName**

Multiply all the colors in the frame by the intensity value. The valid the
intensity range is from 0.0 to 255.0. RGB components are multiplied equally.
An intensity of 0.5 would half the color value. Black colors in the frame
will not be affected by this method.

```C++
// DLL Interface
EXPORT_API void PluginMultiplyIntensityName(
	const char* path, int frameId, float intensity);

// Class Plugin
ChromaAnimationAPI::MultiplyIntensityName(
	const char* path, int frameId, float intensity);
```

---
<a name="PluginMultiplyIntensityNameD"></a>
**PluginMultiplyIntensityNameD**

```C++
// DLL Interface
EXPORT_API double PluginMultiplyIntensityNameD(
	const char* path, double frameId, double intensity);

// Class Plugin
double result = ChromaAnimationAPI::MultiplyIntensityNameD(
	const char* path, double frameId, double intensity);
```

---
<a name="PluginMultiplyIntensityRGB"></a>
**PluginMultiplyIntensityRGB**

```C++
// DLL Interface
EXPORT_API void PluginMultiplyIntensityRGB(
	int animationId, int frameId, int red, int green, int blue);

// Class Plugin
ChromaAnimationAPI::MultiplyIntensityRGB(
	int animationId, int frameId, int red, int green, int blue);
```

---
<a name="PluginMultiplyIntensityRGBName"></a>
**PluginMultiplyIntensityRGBName**

```C++
// DLL Interface
EXPORT_API void PluginMultiplyIntensityRGBName(
	const char* path, int frameId, int red, int green, int blue);

// Class Plugin
ChromaAnimationAPI::MultiplyIntensityRGBName(
	const char* path, int frameId, int red, int green, int blue);
```

---
<a name="PluginMultiplyIntensityRGBNameD"></a>
**PluginMultiplyIntensityRGBNameD**

```C++
// DLL Interface
EXPORT_API double PluginMultiplyIntensityRGBNameD(
	const char* path, double frameId, double red, double green, double blue);

// Class Plugin
double result = ChromaAnimationAPI::MultiplyIntensityRGBNameD(
	const char* path, double frameId, double red, double green, double blue);
```

---
<a name="PluginMultiplyNonZeroTargetColorLerp"></a>
**PluginMultiplyNonZeroTargetColorLerp**

```C++
// DLL Interface
EXPORT_API void PluginMultiplyNonZeroTargetColorLerp(
	int animationId, int frameId, int color1, int color2);

// Class Plugin
ChromaAnimationAPI::MultiplyNonZeroTargetColorLerp(
	int animationId, int frameId, int color1, int color2);
```

---
<a name="PluginMultiplyNonZeroTargetColorLerpAllFrames"></a>
**PluginMultiplyNonZeroTargetColorLerpAllFrames**

```C++
// DLL Interface
EXPORT_API void PluginMultiplyNonZeroTargetColorLerpAllFrames(
	int animationId, int color1, int color2);

// Class Plugin
ChromaAnimationAPI::MultiplyNonZeroTargetColorLerpAllFrames(
	int animationId, int color1, int color2);
```

---
<a name="PluginMultiplyNonZeroTargetColorLerpAllFramesName"></a>
**PluginMultiplyNonZeroTargetColorLerpAllFramesName**

```C++
// DLL Interface
EXPORT_API void PluginMultiplyNonZeroTargetColorLerpAllFramesName(
	const char* path, int color1, int color2);

// Class Plugin
ChromaAnimationAPI::MultiplyNonZeroTargetColorLerpAllFramesName(
	const char* path, int color1, int color2);
```

---
<a name="PluginMultiplyNonZeroTargetColorLerpAllFramesNameD"></a>
**PluginMultiplyNonZeroTargetColorLerpAllFramesNameD**

```C++
// DLL Interface
EXPORT_API double PluginMultiplyNonZeroTargetColorLerpAllFramesNameD(
	const char* path, double color1, double color2);

// Class Plugin
double result = ChromaAnimationAPI::MultiplyNonZeroTargetColorLerpAllFramesNameD(
	const char* path, double color1, double color2);
```

---
<a name="PluginMultiplyNonZeroTargetColorLerpAllFramesRGB"></a>
**PluginMultiplyNonZeroTargetColorLerpAllFramesRGB**

```C++
// DLL Interface
EXPORT_API void PluginMultiplyNonZeroTargetColorLerpAllFramesRGB(
	int animationId, int red1, int green1, int blue1, int red2, int green2, int blue2);

// Class Plugin
ChromaAnimationAPI::MultiplyNonZeroTargetColorLerpAllFramesRGB(
	int animationId, int red1, int green1, int blue1, int red2, int green2, int blue2);
```

---
<a name="PluginMultiplyNonZeroTargetColorLerpAllFramesRGBName"></a>
**PluginMultiplyNonZeroTargetColorLerpAllFramesRGBName**

```C++
// DLL Interface
EXPORT_API void PluginMultiplyNonZeroTargetColorLerpAllFramesRGBName(
	const char* path, int red1, int green1, int blue1, int red2, int green2,
	int blue2);

// Class Plugin
ChromaAnimationAPI::MultiplyNonZeroTargetColorLerpAllFramesRGBName(
	const char* path, int red1, int green1, int blue1, int red2, int green2,
	int blue2);
```

---
<a name="PluginMultiplyNonZeroTargetColorLerpAllFramesRGBNameD"></a>
**PluginMultiplyNonZeroTargetColorLerpAllFramesRGBNameD**

```C++
// DLL Interface
EXPORT_API double PluginMultiplyNonZeroTargetColorLerpAllFramesRGBNameD(
	const char* path, double red1, double green1, double blue1, double red2,
	double green2, double blue2);

// Class Plugin
double result = ChromaAnimationAPI::MultiplyNonZeroTargetColorLerpAllFramesRGBNameD(
	const char* path, double red1, double green1, double blue1, double red2,
	double green2, double blue2);
```

---
<a name="PluginMultiplyTargetColorLerp"></a>
**PluginMultiplyTargetColorLerp**

```C++
// DLL Interface
EXPORT_API void PluginMultiplyTargetColorLerp(
	int animationId, int frameId, int color1, int color2);

// Class Plugin
ChromaAnimationAPI::MultiplyTargetColorLerp(
	int animationId, int frameId, int color1, int color2);
```

---
<a name="PluginMultiplyTargetColorLerpAllFrames"></a>
**PluginMultiplyTargetColorLerpAllFrames**

```C++
// DLL Interface
EXPORT_API void PluginMultiplyTargetColorLerpAllFrames(
	int animationId, int color1, int color2);

// Class Plugin
ChromaAnimationAPI::MultiplyTargetColorLerpAllFrames(
	int animationId, int color1, int color2);
```

---
<a name="PluginMultiplyTargetColorLerpAllFramesName"></a>
**PluginMultiplyTargetColorLerpAllFramesName**

```C++
// DLL Interface
EXPORT_API void PluginMultiplyTargetColorLerpAllFramesName(
	const char* path, int color1, int color2);

// Class Plugin
ChromaAnimationAPI::MultiplyTargetColorLerpAllFramesName(
	const char* path, int color1, int color2);
```

---
<a name="PluginMultiplyTargetColorLerpAllFramesNameD"></a>
**PluginMultiplyTargetColorLerpAllFramesNameD**

```C++
// DLL Interface
EXPORT_API double PluginMultiplyTargetColorLerpAllFramesNameD(
	const char* path, double color1, double color2);

// Class Plugin
double result = ChromaAnimationAPI::MultiplyTargetColorLerpAllFramesNameD(
	const char* path, double color1, double color2);
```

---
<a name="PluginMultiplyTargetColorLerpAllFramesRGB"></a>
**PluginMultiplyTargetColorLerpAllFramesRGB**

```C++
// DLL Interface
EXPORT_API void PluginMultiplyTargetColorLerpAllFramesRGB(
	int animationId, int red1, int green1, int blue1, int red2, int green2, int blue2);

// Class Plugin
ChromaAnimationAPI::MultiplyTargetColorLerpAllFramesRGB(
	int animationId, int red1, int green1, int blue1, int red2, int green2, int blue2);
```

---
<a name="PluginMultiplyTargetColorLerpAllFramesRGBName"></a>
**PluginMultiplyTargetColorLerpAllFramesRGBName**

```C++
// DLL Interface
EXPORT_API void PluginMultiplyTargetColorLerpAllFramesRGBName(
	const char* path, int red1, int green1, int blue1, int red2, int green2,
	int blue2);

// Class Plugin
ChromaAnimationAPI::MultiplyTargetColorLerpAllFramesRGBName(
	const char* path, int red1, int green1, int blue1, int red2, int green2,
	int blue2);
```

---
<a name="PluginMultiplyTargetColorLerpAllFramesRGBNameD"></a>
**PluginMultiplyTargetColorLerpAllFramesRGBNameD**

```C++
// DLL Interface
EXPORT_API double PluginMultiplyTargetColorLerpAllFramesRGBNameD(
	const char* path, double red1, double green1, double blue1, double red2,
	double green2, double blue2);

// Class Plugin
double result = ChromaAnimationAPI::MultiplyTargetColorLerpAllFramesRGBNameD(
	const char* path, double red1, double green1, double blue1, double red2,
	double green2, double blue2);
```

---
<a name="PluginOffsetColors"></a>
**PluginOffsetColors**

Offset all colors in the frame using the RGB offset. Use the range of -255
to 255 for red, green, and blue parameters. Negative values remove color.
Positive values add color.

```C++
// DLL Interface
EXPORT_API void PluginOffsetColors(
	int animationId, int frameId, int red, int green, int blue);

// Class Plugin
ChromaAnimationAPI::OffsetColors(
	int animationId, int frameId, int red, int green, int blue);
```

---
<a name="PluginOffsetColorsAllFrames"></a>
**PluginOffsetColorsAllFrames**

Offset all colors for all frames using the RGB offset. Use the range of
-255 to 255 for red, green, and blue parameters. Negative values remove
color. Positive values add color.

```C++
// DLL Interface
EXPORT_API void PluginOffsetColorsAllFrames(
	int animationId, int red, int green, int blue);

// Class Plugin
ChromaAnimationAPI::OffsetColorsAllFrames(
	int animationId, int red, int green, int blue);
```

---
<a name="PluginOffsetColorsAllFramesName"></a>
**PluginOffsetColorsAllFramesName**

Offset all colors for all frames using the RGB offset. Use the range of
-255 to 255 for red, green, and blue parameters. Negative values remove
color. Positive values add color.

```C++
// DLL Interface
EXPORT_API void PluginOffsetColorsAllFramesName(
	const char* path, int red, int green, int blue);

// Class Plugin
ChromaAnimationAPI::OffsetColorsAllFramesName(
	const char* path, int red, int green, int blue);
```

---
<a name="PluginOffsetColorsAllFramesNameD"></a>
**PluginOffsetColorsAllFramesNameD**

```C++
// DLL Interface
EXPORT_API double PluginOffsetColorsAllFramesNameD(
	const char* path, double red, double green, double blue);

// Class Plugin
double result = ChromaAnimationAPI::OffsetColorsAllFramesNameD(
	const char* path, double red, double green, double blue);
```

---
<a name="PluginOffsetColorsName"></a>
**PluginOffsetColorsName**

Offset all colors in the frame using the RGB offset. Use the range of -255
to 255 for red, green, and blue parameters. Negative values remove color.
Positive values add color.

```C++
// DLL Interface
EXPORT_API void PluginOffsetColorsName(
	const char* path, int frameId, int red, int green, int blue);

// Class Plugin
ChromaAnimationAPI::OffsetColorsName(
	const char* path, int frameId, int red, int green, int blue);
```

---
<a name="PluginOffsetColorsNameD"></a>
**PluginOffsetColorsNameD**

```C++
// DLL Interface
EXPORT_API double PluginOffsetColorsNameD(
	const char* path, double frameId, double red, double green, double blue);

// Class Plugin
double result = ChromaAnimationAPI::OffsetColorsNameD(
	const char* path, double frameId, double red, double green, double blue);
```

---
<a name="PluginOffsetNonZeroColors"></a>
**PluginOffsetNonZeroColors**

This method will only update colors in the animation that are not already
set to black. Offset a subset of colors in the frame using the RGB offset.
Use the range of -255 to 255 for red, green, and blue parameters. Negative
values remove color. Positive values add color.

```C++
// DLL Interface
EXPORT_API void PluginOffsetNonZeroColors(
	int animationId, int frameId, int red, int green, int blue);

// Class Plugin
ChromaAnimationAPI::OffsetNonZeroColors(
	int animationId, int frameId, int red, int green, int blue);
```

---
<a name="PluginOffsetNonZeroColorsAllFrames"></a>
**PluginOffsetNonZeroColorsAllFrames**

This method will only update colors in the animation that are not already
set to black. Offset a subset of colors for all frames using the RGB offset.
Use the range of -255 to 255 for red, green, and blue parameters. Negative
values remove color. Positive values add color.

```C++
// DLL Interface
EXPORT_API void PluginOffsetNonZeroColorsAllFrames(
	int animationId, int red, int green, int blue);

// Class Plugin
ChromaAnimationAPI::OffsetNonZeroColorsAllFrames(
	int animationId, int red, int green, int blue);
```

---
<a name="PluginOffsetNonZeroColorsAllFramesName"></a>
**PluginOffsetNonZeroColorsAllFramesName**

This method will only update colors in the animation that are not already
set to black. Offset a subset of colors for all frames using the RGB offset.
Use the range of -255 to 255 for red, green, and blue parameters. Negative
values remove color. Positive values add color.

```C++
// DLL Interface
EXPORT_API void PluginOffsetNonZeroColorsAllFramesName(
	const char* path, int red, int green, int blue);

// Class Plugin
ChromaAnimationAPI::OffsetNonZeroColorsAllFramesName(
	const char* path, int red, int green, int blue);
```

---
<a name="PluginOffsetNonZeroColorsAllFramesNameD"></a>
**PluginOffsetNonZeroColorsAllFramesNameD**

```C++
// DLL Interface
EXPORT_API double PluginOffsetNonZeroColorsAllFramesNameD(
	const char* path, double red, double green, double blue);

// Class Plugin
double result = ChromaAnimationAPI::OffsetNonZeroColorsAllFramesNameD(
	const char* path, double red, double green, double blue);
```

---
<a name="PluginOffsetNonZeroColorsName"></a>
**PluginOffsetNonZeroColorsName**

This method will only update colors in the animation that are not already
set to black. Offset a subset of colors in the frame using the RGB offset.
Use the range of -255 to 255 for red, green, and blue parameters. Negative
values remove color. Positive values add color.

```C++
// DLL Interface
EXPORT_API void PluginOffsetNonZeroColorsName(
	const char* path, int frameId, int red, int green, int blue);

// Class Plugin
ChromaAnimationAPI::OffsetNonZeroColorsName(
	const char* path, int frameId, int red, int green, int blue);
```

---
<a name="PluginOffsetNonZeroColorsNameD"></a>
**PluginOffsetNonZeroColorsNameD**

```C++
// DLL Interface
EXPORT_API double PluginOffsetNonZeroColorsNameD(
	const char* path, double frameId, double red, double green, double blue);

// Class Plugin
double result = ChromaAnimationAPI::OffsetNonZeroColorsNameD(
	const char* path, double frameId, double red, double green, double blue);
```

---
<a name="PluginOpenAnimation"></a>
**PluginOpenAnimation**

Opens a `Chroma` animation file so that it can be played. Returns an animation
id >= 0 upon success. Returns -1 if there was a failure. The animation
id is used in most of the API methods.

```C++
// DLL Interface
EXPORT_API int PluginOpenAnimation(const char* path);

// Class Plugin
int result = ChromaAnimationAPI::OpenAnimation(const char* path);
```

---
<a name="PluginOpenAnimationD"></a>
**PluginOpenAnimationD**

```C++
// DLL Interface
EXPORT_API double PluginOpenAnimationD(const char* path);

// Class Plugin
double result = ChromaAnimationAPI::OpenAnimationD(const char* path);
```

---
<a name="PluginOpenEditorDialog"></a>
**PluginOpenEditorDialog**

Opens a `Chroma` animation file with the `.chroma` extension. Returns zero
upon success. Returns -1 if there was a failure.

```C++
// DLL Interface
EXPORT_API int PluginOpenEditorDialog(const char* path);

// Class Plugin
int result = ChromaAnimationAPI::OpenEditorDialog(const char* path);
```

---
<a name="PluginOpenEditorDialogAndPlay"></a>
**PluginOpenEditorDialogAndPlay**

```C++
// DLL Interface
EXPORT_API int PluginOpenEditorDialogAndPlay(const char* path);

// Class Plugin
int result = ChromaAnimationAPI::OpenEditorDialogAndPlay(const char* path);
```

---
<a name="PluginOpenEditorDialogAndPlayD"></a>
**PluginOpenEditorDialogAndPlayD**

```C++
// DLL Interface
EXPORT_API double PluginOpenEditorDialogAndPlayD(const char* path);

// Class Plugin
double result = ChromaAnimationAPI::OpenEditorDialogAndPlayD(const char* path);
```

---
<a name="PluginOpenEditorDialogD"></a>
**PluginOpenEditorDialogD**

```C++
// DLL Interface
EXPORT_API double PluginOpenEditorDialogD(const char* path);

// Class Plugin
double result = ChromaAnimationAPI::OpenEditorDialogD(const char* path);
```

---
<a name="PluginOverrideFrameDuration"></a>
**PluginOverrideFrameDuration**

Sets the `duration` for all grames in the `Chroma` animation to the `duration`
parameter. Returns the animation id upon success. Returns -1 upon failure.

```C++
// DLL Interface
EXPORT_API int PluginOverrideFrameDuration(
	int animationId, float duration);

// Class Plugin
int result = ChromaAnimationAPI::OverrideFrameDuration(
	int animationId, float duration);
```

---
<a name="PluginOverrideFrameDurationD"></a>
**PluginOverrideFrameDurationD**

```C++
// DLL Interface
EXPORT_API double PluginOverrideFrameDurationD(
	double animationId, double duration);

// Class Plugin
double result = ChromaAnimationAPI::OverrideFrameDurationD(
	double animationId, double duration);
```

---
<a name="PluginOverrideFrameDurationName"></a>
**PluginOverrideFrameDurationName**

```C++
// DLL Interface
EXPORT_API void PluginOverrideFrameDurationName(
	const char* path, float duration);

// Class Plugin
ChromaAnimationAPI::OverrideFrameDurationName(
	const char* path, float duration);
```

---
<a name="PluginPauseAnimation"></a>
**PluginPauseAnimation**

Pause the current animation referenced by id.

```C++
// DLL Interface
EXPORT_API void PluginPauseAnimation(int animationId);

// Class Plugin
ChromaAnimationAPI::PauseAnimation(int animationId);
```

---
<a name="PluginPauseAnimationName"></a>
**PluginPauseAnimationName**

Pause the current animation referenced by name.

```C++
// DLL Interface
EXPORT_API void PluginPauseAnimationName(const char* path);

// Class Plugin
ChromaAnimationAPI::PauseAnimationName(const char* path);
```

---
<a name="PluginPauseAnimationNameD"></a>
**PluginPauseAnimationNameD**

```C++
// DLL Interface
EXPORT_API double PluginPauseAnimationNameD(const char* path);

// Class Plugin
double result = ChromaAnimationAPI::PauseAnimationNameD(const char* path);
```

---
<a name="PluginPlayAnimation"></a>
**PluginPlayAnimation**

Plays the `Chroma` animation. This will load the animation, if not loaded
previously. Returns the animation id upon success. Returns -1 upon failure.

```C++
// DLL Interface
EXPORT_API int PluginPlayAnimation(int animationId);

// Class Plugin
int result = ChromaAnimationAPI::PlayAnimation(int animationId);
```

---
<a name="PluginPlayAnimationD"></a>
**PluginPlayAnimationD**

```C++
// DLL Interface
EXPORT_API double PluginPlayAnimationD(double animationId);

// Class Plugin
double result = ChromaAnimationAPI::PlayAnimationD(double animationId);
```

---
<a name="PluginPlayAnimationFrame"></a>
**PluginPlayAnimationFrame**

`PluginPlayAnimationFrame` automatically handles initializing the `ChromaSDK`.
The method will play the animation given the `animationId` with looping
`on` or `off` starting at the `frameId`.

```C++
// DLL Interface
EXPORT_API void PluginPlayAnimationFrame(
	int animationId, int frameId, bool loop);

// Class Plugin
ChromaAnimationAPI::PlayAnimationFrame(
	int animationId, int frameId, bool loop);
```

---
<a name="PluginPlayAnimationFrameName"></a>
**PluginPlayAnimationFrameName**

`PluginPlayAnimationFrameName` automatically handles initializing the `ChromaSDK`.
The named `.chroma` animation file will be automatically opened. The animation
will play with looping `on` or `off` starting at the `frameId`.

```C++
// DLL Interface
EXPORT_API void PluginPlayAnimationFrameName(
	const char* path, int frameId, bool loop);

// Class Plugin
ChromaAnimationAPI::PlayAnimationFrameName(
	const char* path, int frameId, bool loop);
```

---
<a name="PluginPlayAnimationFrameNameD"></a>
**PluginPlayAnimationFrameNameD**

```C++
// DLL Interface
EXPORT_API double PluginPlayAnimationFrameNameD(
	const char* path, double frameId, double loop);

// Class Plugin
double result = ChromaAnimationAPI::PlayAnimationFrameNameD(
	const char* path, double frameId, double loop);
```

---
<a name="PluginPlayAnimationLoop"></a>
**PluginPlayAnimationLoop**

`PluginPlayAnimationLoop` automatically handles initializing the `ChromaSDK`.
The method will play the animation given the `animationId` with looping
`on` or `off`.

```C++
// DLL Interface
EXPORT_API void PluginPlayAnimationLoop(
	int animationId, bool loop);

// Class Plugin
ChromaAnimationAPI::PlayAnimationLoop(
	int animationId, bool loop);
```

---
<a name="PluginPlayAnimationName"></a>
**PluginPlayAnimationName**

`PluginPlayAnimationName` automatically handles initializing the `ChromaSDK`.
The named `.chroma` animation file will be automatically opened. The animation
will play with looping `on` or `off`.

```C++
// DLL Interface
EXPORT_API void PluginPlayAnimationName(
	const char* path, bool loop);

// Class Plugin
ChromaAnimationAPI::PlayAnimationName(
	const char* path, bool loop);
```

---
<a name="PluginPlayAnimationNameD"></a>
**PluginPlayAnimationNameD**

```C++
// DLL Interface
EXPORT_API double PluginPlayAnimationNameD(
	const char* path, double loop);

// Class Plugin
double result = ChromaAnimationAPI::PlayAnimationNameD(
	const char* path, double loop);
```

---
<a name="PluginPlayComposite"></a>
**PluginPlayComposite**

`PluginPlayComposite` automatically handles initializing the `ChromaSDK`.
The named animation files for the `.chroma` set will be automatically opened.
The set of animations will play with looping `on` or `off`.

```C++
// DLL Interface
EXPORT_API void PluginPlayComposite(
	const char* name, bool loop);

// Class Plugin
ChromaAnimationAPI::PlayComposite(
	const char* name, bool loop);
```

---
<a name="PluginPlayCompositeD"></a>
**PluginPlayCompositeD**

```C++
// DLL Interface
EXPORT_API double PluginPlayCompositeD(
	const char* name, double loop);

// Class Plugin
double result = ChromaAnimationAPI::PlayCompositeD(
	const char* name, double loop);
```

---
<a name="PluginPreviewFrame"></a>
**PluginPreviewFrame**

Displays the `Chroma` animation frame on `Chroma` hardware given the `frameIndex`.
Returns the animation id upon success. Returns -1 upon failure.

```C++
// DLL Interface
EXPORT_API int PluginPreviewFrame(
	int animationId, int frameIndex);

// Class Plugin
int result = ChromaAnimationAPI::PreviewFrame(
	int animationId, int frameIndex);
```

---
<a name="PluginPreviewFrameD"></a>
**PluginPreviewFrameD**

```C++
// DLL Interface
EXPORT_API double PluginPreviewFrameD(
	double animationId, double frameIndex);

// Class Plugin
double result = ChromaAnimationAPI::PreviewFrameD(
	double animationId, double frameIndex);
```

---
<a name="PluginPreviewFrameName"></a>
**PluginPreviewFrameName**

```C++
// DLL Interface
EXPORT_API void PluginPreviewFrameName(
	const char* path, int frameIndex);

// Class Plugin
ChromaAnimationAPI::PreviewFrameName(
	const char* path, int frameIndex);
```

---
<a name="PluginReduceFrames"></a>
**PluginReduceFrames**

```C++
// DLL Interface
EXPORT_API void PluginReduceFrames(
	int animationId, int n);

// Class Plugin
ChromaAnimationAPI::ReduceFrames(
	int animationId, int n);
```

---
<a name="PluginReduceFramesName"></a>
**PluginReduceFramesName**

```C++
// DLL Interface
EXPORT_API void PluginReduceFramesName(
	const char* path, int n);

// Class Plugin
ChromaAnimationAPI::ReduceFramesName(
	const char* path, int n);
```

---
<a name="PluginReduceFramesNameD"></a>
**PluginReduceFramesNameD**

```C++
// DLL Interface
EXPORT_API double PluginReduceFramesNameD(
	const char* path, double n);

// Class Plugin
double result = ChromaAnimationAPI::ReduceFramesNameD(
	const char* path, double n);
```

---
<a name="PluginResetAnimation"></a>
**PluginResetAnimation**

Resets the `Chroma` animation to 1 blank frame. Returns the animation id
upon success. Returns -1 upon failure.

```C++
// DLL Interface
EXPORT_API int PluginResetAnimation(int animationId);

// Class Plugin
int result = ChromaAnimationAPI::ResetAnimation(int animationId);
```

---
<a name="PluginResumeAnimation"></a>
**PluginResumeAnimation**

Resume the animation with loop `ON` or `OFF` referenced by id.

```C++
// DLL Interface
EXPORT_API void PluginResumeAnimation(
	int animationId, bool loop);

// Class Plugin
ChromaAnimationAPI::ResumeAnimation(
	int animationId, bool loop);
```

---
<a name="PluginResumeAnimationName"></a>
**PluginResumeAnimationName**

Resume the animation with loop `ON` or `OFF` referenced by name.

```C++
// DLL Interface
EXPORT_API void PluginResumeAnimationName(
	const char* path, bool loop);

// Class Plugin
ChromaAnimationAPI::ResumeAnimationName(
	const char* path, bool loop);
```

---
<a name="PluginResumeAnimationNameD"></a>
**PluginResumeAnimationNameD**

```C++
// DLL Interface
EXPORT_API double PluginResumeAnimationNameD(
	const char* path, double loop);

// Class Plugin
double result = ChromaAnimationAPI::ResumeAnimationNameD(
	const char* path, double loop);
```

---
<a name="PluginReverse"></a>
**PluginReverse**

Reverse the animation frame order of the `Chroma` animation. Returns the
animation id upon success. Returns -1 upon failure.

```C++
// DLL Interface
EXPORT_API int PluginReverse(int animationId);

// Class Plugin
int result = ChromaAnimationAPI::Reverse(int animationId);
```

---
<a name="PluginReverseAllFrames"></a>
**PluginReverseAllFrames**

```C++
// DLL Interface
EXPORT_API void PluginReverseAllFrames(int animationId);

// Class Plugin
ChromaAnimationAPI::ReverseAllFrames(int animationId);
```

---
<a name="PluginReverseAllFramesName"></a>
**PluginReverseAllFramesName**

```C++
// DLL Interface
EXPORT_API void PluginReverseAllFramesName(const char* path);

// Class Plugin
ChromaAnimationAPI::ReverseAllFramesName(const char* path);
```

---
<a name="PluginReverseAllFramesNameD"></a>
**PluginReverseAllFramesNameD**

```C++
// DLL Interface
EXPORT_API double PluginReverseAllFramesNameD(const char* path);

// Class Plugin
double result = ChromaAnimationAPI::ReverseAllFramesNameD(const char* path);
```

---
<a name="PluginSaveAnimation"></a>
**PluginSaveAnimation**

```C++
// DLL Interface
EXPORT_API int PluginSaveAnimation(
	int animationId, const char* path);

// Class Plugin
int result = ChromaAnimationAPI::SaveAnimation(
	int animationId, const char* path);
```

---
<a name="PluginSaveAnimationName"></a>
**PluginSaveAnimationName**

```C++
// DLL Interface
EXPORT_API int PluginSaveAnimationName(
	const char* sourceAnimation, const char* targetAnimation);

// Class Plugin
int result = ChromaAnimationAPI::SaveAnimationName(
	const char* sourceAnimation, const char* targetAnimation);
```

---
<a name="PluginSet1DColor"></a>
**PluginSet1DColor**

```C++
// DLL Interface
EXPORT_API void PluginSet1DColor(
	int animationId, int frameId, int led, int color);

// Class Plugin
ChromaAnimationAPI::Set1DColor(
	int animationId, int frameId, int led, int color);
```

---
<a name="PluginSet1DColorName"></a>
**PluginSet1DColorName**

Set the animation color for a frame given the `1D` `led`. The `led` should
be greater than or equal to 0 and less than the `MaxLeds`.

```C++
// DLL Interface
EXPORT_API void PluginSet1DColorName(
	const char* path, int frameId, int led, int color);

// Class Plugin
ChromaAnimationAPI::Set1DColorName(
	const char* path, int frameId, int led, int color);
```

---
<a name="PluginSet1DColorNameD"></a>
**PluginSet1DColorNameD**

```C++
// DLL Interface
EXPORT_API double PluginSet1DColorNameD(
	const char* path, double frameId, double led, double color);

// Class Plugin
double result = ChromaAnimationAPI::Set1DColorNameD(
	const char* path, double frameId, double led, double color);
```

---
<a name="PluginSet2DColor"></a>
**PluginSet2DColor**

```C++
// DLL Interface
EXPORT_API void PluginSet2DColor(
	int animationId, int frameId, int row, int column, int color);

// Class Plugin
ChromaAnimationAPI::Set2DColor(
	int animationId, int frameId, int row, int column, int color);
```

---
<a name="PluginSet2DColorName"></a>
**PluginSet2DColorName**

Set the animation color for a frame given the `2D` `row` and `column`. The
`row` should be greater than or equal to 0 and less than the `MaxRow`.
The `column` should be greater than or equal to 0 and less than the `MaxColumn`.

```C++
// DLL Interface
EXPORT_API void PluginSet2DColorName(
	const char* path, int frameId, int row, int column, int color);

// Class Plugin
ChromaAnimationAPI::Set2DColorName(
	const char* path, int frameId, int row, int column, int color);
```

---
<a name="PluginSet2DColorNameD"></a>
**PluginSet2DColorNameD**

```C++
// DLL Interface
EXPORT_API double PluginSet2DColorNameD(
	const char* path, double frameId, double rowColumnIndex, double color);

// Class Plugin
double result = ChromaAnimationAPI::Set2DColorNameD(
	const char* path, double frameId, double rowColumnIndex, double color);
```

---
<a name="PluginSetChromaCustomColorAllFrames"></a>
**PluginSetChromaCustomColorAllFrames**

```C++
// DLL Interface
EXPORT_API void PluginSetChromaCustomColorAllFrames(int animationId);

// Class Plugin
ChromaAnimationAPI::SetChromaCustomColorAllFrames(int animationId);
```

---
<a name="PluginSetChromaCustomColorAllFramesName"></a>
**PluginSetChromaCustomColorAllFramesName**

```C++
// DLL Interface
EXPORT_API void PluginSetChromaCustomColorAllFramesName(const char* path);

// Class Plugin
ChromaAnimationAPI::SetChromaCustomColorAllFramesName(const char* path);
```

---
<a name="PluginSetChromaCustomColorAllFramesNameD"></a>
**PluginSetChromaCustomColorAllFramesNameD**

```C++
// DLL Interface
EXPORT_API double PluginSetChromaCustomColorAllFramesNameD(const char* path);

// Class Plugin
double result = ChromaAnimationAPI::SetChromaCustomColorAllFramesNameD(const char* path);
```

---
<a name="PluginSetChromaCustomFlag"></a>
**PluginSetChromaCustomFlag**

```C++
// DLL Interface
EXPORT_API void PluginSetChromaCustomFlag(
	int animationId, bool flag);

// Class Plugin
ChromaAnimationAPI::SetChromaCustomFlag(
	int animationId, bool flag);
```

---
<a name="PluginSetChromaCustomFlagName"></a>
**PluginSetChromaCustomFlagName**

```C++
// DLL Interface
EXPORT_API void PluginSetChromaCustomFlagName(
	const char* path, bool flag);

// Class Plugin
ChromaAnimationAPI::SetChromaCustomFlagName(
	const char* path, bool flag);
```

---
<a name="PluginSetChromaCustomFlagNameD"></a>
**PluginSetChromaCustomFlagNameD**

```C++
// DLL Interface
EXPORT_API double PluginSetChromaCustomFlagNameD(
	const char* path, double flag);

// Class Plugin
double result = ChromaAnimationAPI::SetChromaCustomFlagNameD(
	const char* path, double flag);
```

---
<a name="PluginSetCurrentFrame"></a>
**PluginSetCurrentFrame**

Set the current frame of the animation referenced by id.

```C++
// DLL Interface
EXPORT_API void PluginSetCurrentFrame(
	int animationId, int frameId);

// Class Plugin
ChromaAnimationAPI::SetCurrentFrame(
	int animationId, int frameId);
```

---
<a name="PluginSetCurrentFrameName"></a>
**PluginSetCurrentFrameName**

Set the current frame of the animation referenced by name.

```C++
// DLL Interface
EXPORT_API void PluginSetCurrentFrameName(
	const char* path, int frameId);

// Class Plugin
ChromaAnimationAPI::SetCurrentFrameName(
	const char* path, int frameId);
```

---
<a name="PluginSetCurrentFrameNameD"></a>
**PluginSetCurrentFrameNameD**

```C++
// DLL Interface
EXPORT_API double PluginSetCurrentFrameNameD(
	const char* path, double frameId);

// Class Plugin
double result = ChromaAnimationAPI::SetCurrentFrameNameD(
	const char* path, double frameId);
```

---
<a name="PluginSetDevice"></a>
**PluginSetDevice**

Changes the `deviceType` and `device` of a `Chroma` animation. If the device
is changed, the `Chroma` animation will be reset with 1 blank frame. Returns
the animation id upon success. Returns -1 upon failure.

```C++
// DLL Interface
EXPORT_API int PluginSetDevice(
	int animationId, int deviceType, int device);

// Class Plugin
int result = ChromaAnimationAPI::SetDevice(
	int animationId, int deviceType, int device);
```

---
<a name="PluginSetEffect"></a>
**PluginSetEffect**

```C++
// DLL Interface
EXPORT_API RZRESULT PluginSetEffect(
	const ChromaSDK::FChromaSDKGuid& effectId);

// Class Plugin
RZRESULT result = ChromaAnimationAPI::SetEffect(
	const ChromaSDK::FChromaSDKGuid& effectId);
```

---
<a name="PluginSetKeyColor"></a>
**PluginSetKeyColor**

Set animation key to a static color for the given frame.

```C++
// DLL Interface
EXPORT_API void PluginSetKeyColor(
	int animationId, int frameId, int rzkey, int color);

// Class Plugin
ChromaAnimationAPI::SetKeyColor(
	int animationId, int frameId, int rzkey, int color);
```

---
<a name="PluginSetKeyColorAllFrames"></a>
**PluginSetKeyColorAllFrames**

```C++
// DLL Interface
EXPORT_API void PluginSetKeyColorAllFrames(
	int animationId, int rzkey, int color);

// Class Plugin
ChromaAnimationAPI::SetKeyColorAllFrames(
	int animationId, int rzkey, int color);
```

---
<a name="PluginSetKeyColorAllFramesName"></a>
**PluginSetKeyColorAllFramesName**

```C++
// DLL Interface
EXPORT_API void PluginSetKeyColorAllFramesName(
	const char* path, int rzkey, int color);

// Class Plugin
ChromaAnimationAPI::SetKeyColorAllFramesName(
	const char* path, int rzkey, int color);
```

---
<a name="PluginSetKeyColorAllFramesNameD"></a>
**PluginSetKeyColorAllFramesNameD**

```C++
// DLL Interface
EXPORT_API double PluginSetKeyColorAllFramesNameD(
	const char* path, double rzkey, double color);

// Class Plugin
double result = ChromaAnimationAPI::SetKeyColorAllFramesNameD(
	const char* path, double rzkey, double color);
```

---
<a name="PluginSetKeyColorAllFramesRGB"></a>
**PluginSetKeyColorAllFramesRGB**

```C++
// DLL Interface
EXPORT_API void PluginSetKeyColorAllFramesRGB(
	int animationId, int rzkey, int red, int green, int blue);

// Class Plugin
ChromaAnimationAPI::SetKeyColorAllFramesRGB(
	int animationId, int rzkey, int red, int green, int blue);
```

---
<a name="PluginSetKeyColorAllFramesRGBName"></a>
**PluginSetKeyColorAllFramesRGBName**

```C++
// DLL Interface
EXPORT_API void PluginSetKeyColorAllFramesRGBName(
	const char* path, int rzkey, int red, int green, int blue);

// Class Plugin
ChromaAnimationAPI::SetKeyColorAllFramesRGBName(
	const char* path, int rzkey, int red, int green, int blue);
```

---
<a name="PluginSetKeyColorAllFramesRGBNameD"></a>
**PluginSetKeyColorAllFramesRGBNameD**

```C++
// DLL Interface
EXPORT_API double PluginSetKeyColorAllFramesRGBNameD(
	const char* path, double rzkey, double red, double green, double blue);

// Class Plugin
double result = ChromaAnimationAPI::SetKeyColorAllFramesRGBNameD(
	const char* path, double rzkey, double red, double green, double blue);
```

---
<a name="PluginSetKeyColorName"></a>
**PluginSetKeyColorName**

Set animation key to a static color for the given frame.

```C++
// DLL Interface
EXPORT_API void PluginSetKeyColorName(
	const char* path, int frameId, int rzkey, int color);

// Class Plugin
ChromaAnimationAPI::SetKeyColorName(
	const char* path, int frameId, int rzkey, int color);
```

---
<a name="PluginSetKeyColorNameD"></a>
**PluginSetKeyColorNameD**

```C++
// DLL Interface
EXPORT_API double PluginSetKeyColorNameD(
	const char* path, double frameId, double rzkey, double color);

// Class Plugin
double result = ChromaAnimationAPI::SetKeyColorNameD(
	const char* path, double frameId, double rzkey, double color);
```

---
<a name="PluginSetKeyColorRGB"></a>
**PluginSetKeyColorRGB**

```C++
// DLL Interface
EXPORT_API void PluginSetKeyColorRGB(
	int animationId, int frameId, int rzkey, int red, int green, int blue);

// Class Plugin
ChromaAnimationAPI::SetKeyColorRGB(
	int animationId, int frameId, int rzkey, int red, int green, int blue);
```

---
<a name="PluginSetKeyColorRGBName"></a>
**PluginSetKeyColorRGBName**

```C++
// DLL Interface
EXPORT_API void PluginSetKeyColorRGBName(
	const char* path, int frameId, int rzkey, int red, int green, int blue);

// Class Plugin
ChromaAnimationAPI::SetKeyColorRGBName(
	const char* path, int frameId, int rzkey, int red, int green, int blue);
```

---
<a name="PluginSetKeyColorRGBNameD"></a>
**PluginSetKeyColorRGBNameD**

```C++
// DLL Interface
EXPORT_API double PluginSetKeyColorRGBNameD(
	const char* path, double frameId, double rzkey, double red, double green,
	double blue);

// Class Plugin
double result = ChromaAnimationAPI::SetKeyColorRGBNameD(
	const char* path, double frameId, double rzkey, double red, double green,
	double blue);
```

---
<a name="PluginSetKeyNonZeroColor"></a>
**PluginSetKeyNonZeroColor**

Set animation key to a static color for the given frame if the existing
color is not already black.

```C++
// DLL Interface
EXPORT_API void PluginSetKeyNonZeroColor(
	int animationId, int frameId, int rzkey, int color);

// Class Plugin
ChromaAnimationAPI::SetKeyNonZeroColor(
	int animationId, int frameId, int rzkey, int color);
```

---
<a name="PluginSetKeyNonZeroColorName"></a>
**PluginSetKeyNonZeroColorName**

Set animation key to a static color for the given frame if the existing
color is not already black.

```C++
// DLL Interface
EXPORT_API void PluginSetKeyNonZeroColorName(
	const char* path, int frameId, int rzkey, int color);

// Class Plugin
ChromaAnimationAPI::SetKeyNonZeroColorName(
	const char* path, int frameId, int rzkey, int color);
```

---
<a name="PluginSetKeyNonZeroColorNameD"></a>
**PluginSetKeyNonZeroColorNameD**

```C++
// DLL Interface
EXPORT_API double PluginSetKeyNonZeroColorNameD(
	const char* path, double frameId, double rzkey, double color);

// Class Plugin
double result = ChromaAnimationAPI::SetKeyNonZeroColorNameD(
	const char* path, double frameId, double rzkey, double color);
```

---
<a name="PluginSetKeyNonZeroColorRGB"></a>
**PluginSetKeyNonZeroColorRGB**

```C++
// DLL Interface
EXPORT_API void PluginSetKeyNonZeroColorRGB(
	int animationId, int frameId, int rzkey, int red, int green, int blue);

// Class Plugin
ChromaAnimationAPI::SetKeyNonZeroColorRGB(
	int animationId, int frameId, int rzkey, int red, int green, int blue);
```

---
<a name="PluginSetKeyNonZeroColorRGBName"></a>
**PluginSetKeyNonZeroColorRGBName**

```C++
// DLL Interface
EXPORT_API void PluginSetKeyNonZeroColorRGBName(
	const char* path, int frameId, int rzkey, int red, int green, int blue);

// Class Plugin
ChromaAnimationAPI::SetKeyNonZeroColorRGBName(
	const char* path, int frameId, int rzkey, int red, int green, int blue);
```

---
<a name="PluginSetKeyNonZeroColorRGBNameD"></a>
**PluginSetKeyNonZeroColorRGBNameD**

```C++
// DLL Interface
EXPORT_API double PluginSetKeyNonZeroColorRGBNameD(
	const char* path, double frameId, double rzkey, double red, double green,
	double blue);

// Class Plugin
double result = ChromaAnimationAPI::SetKeyNonZeroColorRGBNameD(
	const char* path, double frameId, double rzkey, double red, double green,
	double blue);
```

---
<a name="PluginSetKeysColor"></a>
**PluginSetKeysColor**

Set an array of animation keys to a static color for the given frame.

```C++
// DLL Interface
EXPORT_API void PluginSetKeysColor(
	int animationId, int frameId, const int* rzkeys, int keyCount, int color);

// Class Plugin
ChromaAnimationAPI::SetKeysColor(
	int animationId, int frameId, const int* rzkeys, int keyCount, int color);
```

---
<a name="PluginSetKeysColorAllFrames"></a>
**PluginSetKeysColorAllFrames**

```C++
// DLL Interface
EXPORT_API void PluginSetKeysColorAllFrames(
	int animationId, const int* rzkeys, int keyCount, int color);

// Class Plugin
ChromaAnimationAPI::SetKeysColorAllFrames(
	int animationId, const int* rzkeys, int keyCount, int color);
```

---
<a name="PluginSetKeysColorAllFramesName"></a>
**PluginSetKeysColorAllFramesName**

```C++
// DLL Interface
EXPORT_API void PluginSetKeysColorAllFramesName(
	const char* path, const int* rzkeys, int keyCount, int color);

// Class Plugin
ChromaAnimationAPI::SetKeysColorAllFramesName(
	const char* path, const int* rzkeys, int keyCount, int color);
```

---
<a name="PluginSetKeysColorAllFramesRGB"></a>
**PluginSetKeysColorAllFramesRGB**

```C++
// DLL Interface
EXPORT_API void PluginSetKeysColorAllFramesRGB(
	int animationId, const int* rzkeys, int keyCount, int red, int green, int blue);

// Class Plugin
ChromaAnimationAPI::SetKeysColorAllFramesRGB(
	int animationId, const int* rzkeys, int keyCount, int red, int green, int blue);
```

---
<a name="PluginSetKeysColorAllFramesRGBName"></a>
**PluginSetKeysColorAllFramesRGBName**

```C++
// DLL Interface
EXPORT_API void PluginSetKeysColorAllFramesRGBName(
	const char* path, const int* rzkeys, int keyCount, int red, int green, int blue);

// Class Plugin
ChromaAnimationAPI::SetKeysColorAllFramesRGBName(
	const char* path, const int* rzkeys, int keyCount, int red, int green, int blue);
```

---
<a name="PluginSetKeysColorName"></a>
**PluginSetKeysColorName**

Set an array of animation keys to a static color for the given frame.

```C++
// DLL Interface
EXPORT_API void PluginSetKeysColorName(
	const char* path, int frameId, const int* rzkeys, int keyCount, int color);

// Class Plugin
ChromaAnimationAPI::SetKeysColorName(
	const char* path, int frameId, const int* rzkeys, int keyCount, int color);
```

---
<a name="PluginSetKeysColorRGB"></a>
**PluginSetKeysColorRGB**

```C++
// DLL Interface
EXPORT_API void PluginSetKeysColorRGB(
	int animationId, int frameId, const int* rzkeys, int keyCount, int red, int green,
	int blue);

// Class Plugin
ChromaAnimationAPI::SetKeysColorRGB(
	int animationId, int frameId, const int* rzkeys, int keyCount, int red, int green,
	int blue);
```

---
<a name="PluginSetKeysColorRGBName"></a>
**PluginSetKeysColorRGBName**

```C++
// DLL Interface
EXPORT_API void PluginSetKeysColorRGBName(
	const char* path, int frameId, const int* rzkeys, int keyCount, int red,
	int green, int blue);

// Class Plugin
ChromaAnimationAPI::SetKeysColorRGBName(
	const char* path, int frameId, const int* rzkeys, int keyCount, int red,
	int green, int blue);
```

---
<a name="PluginSetKeysNonZeroColor"></a>
**PluginSetKeysNonZeroColor**

Set an array of animation keys to a static color for the given frame if
the existing color is not already black.

```C++
// DLL Interface
EXPORT_API void PluginSetKeysNonZeroColor(
	int animationId, int frameId, const int* rzkeys, int keyCount, int color);

// Class Plugin
ChromaAnimationAPI::SetKeysNonZeroColor(
	int animationId, int frameId, const int* rzkeys, int keyCount, int color);
```

---
<a name="PluginSetKeysNonZeroColorAllFrames"></a>
**PluginSetKeysNonZeroColorAllFrames**

```C++
// DLL Interface
EXPORT_API void PluginSetKeysNonZeroColorAllFrames(
	int animationId, const int* rzkeys, int keyCount, int color);

// Class Plugin
ChromaAnimationAPI::SetKeysNonZeroColorAllFrames(
	int animationId, const int* rzkeys, int keyCount, int color);
```

---
<a name="PluginSetKeysNonZeroColorAllFramesName"></a>
**PluginSetKeysNonZeroColorAllFramesName**

```C++
// DLL Interface
EXPORT_API void PluginSetKeysNonZeroColorAllFramesName(
	const char* path, const int* rzkeys, int keyCount, int color);

// Class Plugin
ChromaAnimationAPI::SetKeysNonZeroColorAllFramesName(
	const char* path, const int* rzkeys, int keyCount, int color);
```

---
<a name="PluginSetKeysNonZeroColorName"></a>
**PluginSetKeysNonZeroColorName**

Set an array of animation keys to a static color for the given frame if
the existing color is not already black.

```C++
// DLL Interface
EXPORT_API void PluginSetKeysNonZeroColorName(
	const char* path, int frameId, const int* rzkeys, int keyCount, int color);

// Class Plugin
ChromaAnimationAPI::SetKeysNonZeroColorName(
	const char* path, int frameId, const int* rzkeys, int keyCount, int color);
```

---
<a name="PluginSetKeysNonZeroColorRGB"></a>
**PluginSetKeysNonZeroColorRGB**

```C++
// DLL Interface
EXPORT_API void PluginSetKeysNonZeroColorRGB(
	int animationId, int frameId, const int* rzkeys, int keyCount, int red, int green,
	int blue);

// Class Plugin
ChromaAnimationAPI::SetKeysNonZeroColorRGB(
	int animationId, int frameId, const int* rzkeys, int keyCount, int red, int green,
	int blue);
```

---
<a name="PluginSetKeysNonZeroColorRGBName"></a>
**PluginSetKeysNonZeroColorRGBName**

```C++
// DLL Interface
EXPORT_API void PluginSetKeysNonZeroColorRGBName(
	const char* path, int frameId, const int* rzkeys, int keyCount, int red,
	int green, int blue);

// Class Plugin
ChromaAnimationAPI::SetKeysNonZeroColorRGBName(
	const char* path, int frameId, const int* rzkeys, int keyCount, int red,
	int green, int blue);
```

---
<a name="PluginSetKeysZeroColor"></a>
**PluginSetKeysZeroColor**

```C++
// DLL Interface
EXPORT_API void PluginSetKeysZeroColor(
	int animationId, int frameId, const int* rzkeys, int keyCount, int color);

// Class Plugin
ChromaAnimationAPI::SetKeysZeroColor(
	int animationId, int frameId, const int* rzkeys, int keyCount, int color);
```

---
<a name="PluginSetKeysZeroColorAllFrames"></a>
**PluginSetKeysZeroColorAllFrames**

```C++
// DLL Interface
EXPORT_API void PluginSetKeysZeroColorAllFrames(
	int animationId, const int* rzkeys, int keyCount, int color);

// Class Plugin
ChromaAnimationAPI::SetKeysZeroColorAllFrames(
	int animationId, const int* rzkeys, int keyCount, int color);
```

---
<a name="PluginSetKeysZeroColorAllFramesName"></a>
**PluginSetKeysZeroColorAllFramesName**

```C++
// DLL Interface
EXPORT_API void PluginSetKeysZeroColorAllFramesName(
	const char* path, const int* rzkeys, int keyCount, int color);

// Class Plugin
ChromaAnimationAPI::SetKeysZeroColorAllFramesName(
	const char* path, const int* rzkeys, int keyCount, int color);
```

---
<a name="PluginSetKeysZeroColorAllFramesRGB"></a>
**PluginSetKeysZeroColorAllFramesRGB**

```C++
// DLL Interface
EXPORT_API void PluginSetKeysZeroColorAllFramesRGB(
	int animationId, const int* rzkeys, int keyCount, int red, int green, int blue);

// Class Plugin
ChromaAnimationAPI::SetKeysZeroColorAllFramesRGB(
	int animationId, const int* rzkeys, int keyCount, int red, int green, int blue);
```

---
<a name="PluginSetKeysZeroColorAllFramesRGBName"></a>
**PluginSetKeysZeroColorAllFramesRGBName**

```C++
// DLL Interface
EXPORT_API void PluginSetKeysZeroColorAllFramesRGBName(
	const char* path, const int* rzkeys, int keyCount, int red, int green, int blue);

// Class Plugin
ChromaAnimationAPI::SetKeysZeroColorAllFramesRGBName(
	const char* path, const int* rzkeys, int keyCount, int red, int green, int blue);
```

---
<a name="PluginSetKeysZeroColorName"></a>
**PluginSetKeysZeroColorName**

```C++
// DLL Interface
EXPORT_API void PluginSetKeysZeroColorName(
	const char* path, int frameId, const int* rzkeys, int keyCount, int color);

// Class Plugin
ChromaAnimationAPI::SetKeysZeroColorName(
	const char* path, int frameId, const int* rzkeys, int keyCount, int color);
```

---
<a name="PluginSetKeysZeroColorRGB"></a>
**PluginSetKeysZeroColorRGB**

```C++
// DLL Interface
EXPORT_API void PluginSetKeysZeroColorRGB(
	int animationId, int frameId, const int* rzkeys, int keyCount, int red, int green,
	int blue);

// Class Plugin
ChromaAnimationAPI::SetKeysZeroColorRGB(
	int animationId, int frameId, const int* rzkeys, int keyCount, int red, int green,
	int blue);
```

---
<a name="PluginSetKeysZeroColorRGBName"></a>
**PluginSetKeysZeroColorRGBName**

```C++
// DLL Interface
EXPORT_API void PluginSetKeysZeroColorRGBName(
	const char* path, int frameId, const int* rzkeys, int keyCount, int red,
	int green, int blue);

// Class Plugin
ChromaAnimationAPI::SetKeysZeroColorRGBName(
	const char* path, int frameId, const int* rzkeys, int keyCount, int red,
	int green, int blue);
```

---
<a name="PluginSetKeyZeroColor"></a>
**PluginSetKeyZeroColor**

```C++
// DLL Interface
EXPORT_API void PluginSetKeyZeroColor(
	int animationId, int frameId, int rzkey, int color);

// Class Plugin
ChromaAnimationAPI::SetKeyZeroColor(
	int animationId, int frameId, int rzkey, int color);
```

---
<a name="PluginSetKeyZeroColorName"></a>
**PluginSetKeyZeroColorName**

```C++
// DLL Interface
EXPORT_API void PluginSetKeyZeroColorName(
	const char* path, int frameId, int rzkey, int color);

// Class Plugin
ChromaAnimationAPI::SetKeyZeroColorName(
	const char* path, int frameId, int rzkey, int color);
```

---
<a name="PluginSetKeyZeroColorNameD"></a>
**PluginSetKeyZeroColorNameD**

```C++
// DLL Interface
EXPORT_API double PluginSetKeyZeroColorNameD(
	const char* path, double frameId, double rzkey, double color);

// Class Plugin
double result = ChromaAnimationAPI::SetKeyZeroColorNameD(
	const char* path, double frameId, double rzkey, double color);
```

---
<a name="PluginSetKeyZeroColorRGB"></a>
**PluginSetKeyZeroColorRGB**

```C++
// DLL Interface
EXPORT_API void PluginSetKeyZeroColorRGB(
	int animationId, int frameId, int rzkey, int red, int green, int blue);

// Class Plugin
ChromaAnimationAPI::SetKeyZeroColorRGB(
	int animationId, int frameId, int rzkey, int red, int green, int blue);
```

---
<a name="PluginSetKeyZeroColorRGBName"></a>
**PluginSetKeyZeroColorRGBName**

```C++
// DLL Interface
EXPORT_API void PluginSetKeyZeroColorRGBName(
	const char* path, int frameId, int rzkey, int red, int green, int blue);

// Class Plugin
ChromaAnimationAPI::SetKeyZeroColorRGBName(
	const char* path, int frameId, int rzkey, int red, int green, int blue);
```

---
<a name="PluginSetKeyZeroColorRGBNameD"></a>
**PluginSetKeyZeroColorRGBNameD**

```C++
// DLL Interface
EXPORT_API double PluginSetKeyZeroColorRGBNameD(
	const char* path, double frameId, double rzkey, double red, double green,
	double blue);

// Class Plugin
double result = ChromaAnimationAPI::SetKeyZeroColorRGBNameD(
	const char* path, double frameId, double rzkey, double red, double green,
	double blue);
```

---
<a name="PluginSetLogDelegate"></a>
**PluginSetLogDelegate**

Invokes the setup for a debug logging callback so that `stdout` is redirected
to the callback. This is used by `Unity` so that debug messages can appear
in the console window.

```C++
// DLL Interface
EXPORT_API void PluginSetLogDelegate(DebugLogPtr fp);

// Class Plugin
ChromaAnimationAPI::SetLogDelegate(DebugLogPtr fp);
```

---
<a name="PluginStopAll"></a>
**PluginStopAll**

`PluginStopAll` will automatically stop all animations that are playing.

```C++
// DLL Interface
EXPORT_API void PluginStopAll();

// Class Plugin
ChromaAnimationAPI::StopAll();
```

---
<a name="PluginStopAnimation"></a>
**PluginStopAnimation**

Stops animation playback if in progress. Returns the animation id upon success.
Returns -1 upon failure.

```C++
// DLL Interface
EXPORT_API int PluginStopAnimation(int animationId);

// Class Plugin
int result = ChromaAnimationAPI::StopAnimation(int animationId);
```

---
<a name="PluginStopAnimationD"></a>
**PluginStopAnimationD**

```C++
// DLL Interface
EXPORT_API double PluginStopAnimationD(double animationId);

// Class Plugin
double result = ChromaAnimationAPI::StopAnimationD(double animationId);
```

---
<a name="PluginStopAnimationName"></a>
**PluginStopAnimationName**

`PluginStopAnimationName` automatically handles initializing the `ChromaSDK`.
The named `.chroma` animation file will be automatically opened. The animation
will stop if playing.

```C++
// DLL Interface
EXPORT_API void PluginStopAnimationName(const char* path);

// Class Plugin
ChromaAnimationAPI::StopAnimationName(const char* path);
```

---
<a name="PluginStopAnimationNameD"></a>
**PluginStopAnimationNameD**

```C++
// DLL Interface
EXPORT_API double PluginStopAnimationNameD(const char* path);

// Class Plugin
double result = ChromaAnimationAPI::StopAnimationNameD(const char* path);
```

---
<a name="PluginStopAnimationType"></a>
**PluginStopAnimationType**

`PluginStopAnimationType` automatically handles initializing the `ChromaSDK`.
If any animation is playing for the `deviceType` and `device` combination,
it will be stopped.

```C++
// DLL Interface
EXPORT_API void PluginStopAnimationType(
	int deviceType, int device);

// Class Plugin
ChromaAnimationAPI::StopAnimationType(
	int deviceType, int device);
```

---
<a name="PluginStopAnimationTypeD"></a>
**PluginStopAnimationTypeD**

```C++
// DLL Interface
EXPORT_API double PluginStopAnimationTypeD(
	double deviceType, double device);

// Class Plugin
double result = ChromaAnimationAPI::StopAnimationTypeD(
	double deviceType, double device);
```

---
<a name="PluginStopComposite"></a>
**PluginStopComposite**

`PluginStopComposite` automatically handles initializing the `ChromaSDK`.
The named animation files for the `.chroma` set will be automatically opened.
The set of animations will be stopped if playing.

```C++
// DLL Interface
EXPORT_API void PluginStopComposite(const char* name);

// Class Plugin
ChromaAnimationAPI::StopComposite(const char* name);
```

---
<a name="PluginStopCompositeD"></a>
**PluginStopCompositeD**

```C++
// DLL Interface
EXPORT_API double PluginStopCompositeD(const char* name);

// Class Plugin
double result = ChromaAnimationAPI::StopCompositeD(const char* name);
```

---
<a name="PluginSubtractNonZeroAllKeysAllFrames"></a>
**PluginSubtractNonZeroAllKeysAllFrames**

```C++
// DLL Interface
EXPORT_API void PluginSubtractNonZeroAllKeysAllFrames(
	int sourceAnimationId, int targetAnimationId);

// Class Plugin
ChromaAnimationAPI::SubtractNonZeroAllKeysAllFrames(
	int sourceAnimationId, int targetAnimationId);
```

---
<a name="PluginSubtractNonZeroAllKeysAllFramesName"></a>
**PluginSubtractNonZeroAllKeysAllFramesName**

```C++
// DLL Interface
EXPORT_API void PluginSubtractNonZeroAllKeysAllFramesName(
	const char* sourceAnimation, const char* targetAnimation);

// Class Plugin
ChromaAnimationAPI::SubtractNonZeroAllKeysAllFramesName(
	const char* sourceAnimation, const char* targetAnimation);
```

---
<a name="PluginSubtractNonZeroAllKeysAllFramesNameD"></a>
**PluginSubtractNonZeroAllKeysAllFramesNameD**

```C++
// DLL Interface
EXPORT_API double PluginSubtractNonZeroAllKeysAllFramesNameD(
	const char* sourceAnimation, const char* targetAnimation);

// Class Plugin
double result = ChromaAnimationAPI::SubtractNonZeroAllKeysAllFramesNameD(
	const char* sourceAnimation, const char* targetAnimation);
```

---
<a name="PluginSubtractNonZeroAllKeysAllFramesOffset"></a>
**PluginSubtractNonZeroAllKeysAllFramesOffset**

```C++
// DLL Interface
EXPORT_API void PluginSubtractNonZeroAllKeysAllFramesOffset(
	int sourceAnimationId, int targetAnimationId, int offset);

// Class Plugin
ChromaAnimationAPI::SubtractNonZeroAllKeysAllFramesOffset(
	int sourceAnimationId, int targetAnimationId, int offset);
```

---
<a name="PluginSubtractNonZeroAllKeysAllFramesOffsetName"></a>
**PluginSubtractNonZeroAllKeysAllFramesOffsetName**

```C++
// DLL Interface
EXPORT_API void PluginSubtractNonZeroAllKeysAllFramesOffsetName(
	const char* sourceAnimation, const char* targetAnimation, int offset);

// Class Plugin
ChromaAnimationAPI::SubtractNonZeroAllKeysAllFramesOffsetName(
	const char* sourceAnimation, const char* targetAnimation, int offset);
```

---
<a name="PluginSubtractNonZeroAllKeysAllFramesOffsetNameD"></a>
**PluginSubtractNonZeroAllKeysAllFramesOffsetNameD**

```C++
// DLL Interface
EXPORT_API double PluginSubtractNonZeroAllKeysAllFramesOffsetNameD(
	const char* sourceAnimation, const char* targetAnimation, double offset);

// Class Plugin
double result = ChromaAnimationAPI::SubtractNonZeroAllKeysAllFramesOffsetNameD(
	const char* sourceAnimation, const char* targetAnimation, double offset);
```

---
<a name="PluginSubtractNonZeroAllKeysOffset"></a>
**PluginSubtractNonZeroAllKeysOffset**

```C++
// DLL Interface
EXPORT_API void PluginSubtractNonZeroAllKeysOffset(
	int sourceAnimationId, int targetAnimationId, int frameId, int offset);

// Class Plugin
ChromaAnimationAPI::SubtractNonZeroAllKeysOffset(
	int sourceAnimationId, int targetAnimationId, int frameId, int offset);
```

---
<a name="PluginSubtractNonZeroAllKeysOffsetName"></a>
**PluginSubtractNonZeroAllKeysOffsetName**

```C++
// DLL Interface
EXPORT_API void PluginSubtractNonZeroAllKeysOffsetName(
	const char* sourceAnimation, const char* targetAnimation, int frameId, int offset);

// Class Plugin
ChromaAnimationAPI::SubtractNonZeroAllKeysOffsetName(
	const char* sourceAnimation, const char* targetAnimation, int frameId, int offset);
```

---
<a name="PluginSubtractNonZeroAllKeysOffsetNameD"></a>
**PluginSubtractNonZeroAllKeysOffsetNameD**

```C++
// DLL Interface
EXPORT_API double PluginSubtractNonZeroAllKeysOffsetNameD(
	const char* sourceAnimation, const char* targetAnimation, double frameId,
	double offset);

// Class Plugin
double result = ChromaAnimationAPI::SubtractNonZeroAllKeysOffsetNameD(
	const char* sourceAnimation, const char* targetAnimation, double frameId,
	double offset);
```

---
<a name="PluginSubtractNonZeroTargetAllKeysAllFrames"></a>
**PluginSubtractNonZeroTargetAllKeysAllFrames**

```C++
// DLL Interface
EXPORT_API void PluginSubtractNonZeroTargetAllKeysAllFrames(
	int sourceAnimationId, int targetAnimationId);

// Class Plugin
ChromaAnimationAPI::SubtractNonZeroTargetAllKeysAllFrames(
	int sourceAnimationId, int targetAnimationId);
```

---
<a name="PluginSubtractNonZeroTargetAllKeysAllFramesName"></a>
**PluginSubtractNonZeroTargetAllKeysAllFramesName**

```C++
// DLL Interface
EXPORT_API void PluginSubtractNonZeroTargetAllKeysAllFramesName(
	const char* sourceAnimation, const char* targetAnimation);

// Class Plugin
ChromaAnimationAPI::SubtractNonZeroTargetAllKeysAllFramesName(
	const char* sourceAnimation, const char* targetAnimation);
```

---
<a name="PluginSubtractNonZeroTargetAllKeysAllFramesNameD"></a>
**PluginSubtractNonZeroTargetAllKeysAllFramesNameD**

```C++
// DLL Interface
EXPORT_API double PluginSubtractNonZeroTargetAllKeysAllFramesNameD(
	const char* sourceAnimation, const char* targetAnimation);

// Class Plugin
double result = ChromaAnimationAPI::SubtractNonZeroTargetAllKeysAllFramesNameD(
	const char* sourceAnimation, const char* targetAnimation);
```

---
<a name="PluginSubtractNonZeroTargetAllKeysAllFramesOffset"></a>
**PluginSubtractNonZeroTargetAllKeysAllFramesOffset**

```C++
// DLL Interface
EXPORT_API void PluginSubtractNonZeroTargetAllKeysAllFramesOffset(
	int sourceAnimationId, int targetAnimationId, int offset);

// Class Plugin
ChromaAnimationAPI::SubtractNonZeroTargetAllKeysAllFramesOffset(
	int sourceAnimationId, int targetAnimationId, int offset);
```

---
<a name="PluginSubtractNonZeroTargetAllKeysAllFramesOffsetName"></a>
**PluginSubtractNonZeroTargetAllKeysAllFramesOffsetName**

```C++
// DLL Interface
EXPORT_API void PluginSubtractNonZeroTargetAllKeysAllFramesOffsetName(
	const char* sourceAnimation, const char* targetAnimation, int offset);

// Class Plugin
ChromaAnimationAPI::SubtractNonZeroTargetAllKeysAllFramesOffsetName(
	const char* sourceAnimation, const char* targetAnimation, int offset);
```

---
<a name="PluginSubtractNonZeroTargetAllKeysAllFramesOffsetNameD"></a>
**PluginSubtractNonZeroTargetAllKeysAllFramesOffsetNameD**

```C++
// DLL Interface
EXPORT_API double PluginSubtractNonZeroTargetAllKeysAllFramesOffsetNameD(
	const char* sourceAnimation, const char* targetAnimation, double offset);

// Class Plugin
double result = ChromaAnimationAPI::SubtractNonZeroTargetAllKeysAllFramesOffsetNameD(
	const char* sourceAnimation, const char* targetAnimation, double offset);
```

---
<a name="PluginSubtractNonZeroTargetAllKeysOffset"></a>
**PluginSubtractNonZeroTargetAllKeysOffset**

```C++
// DLL Interface
EXPORT_API void PluginSubtractNonZeroTargetAllKeysOffset(
	int sourceAnimationId, int targetAnimationId, int frameId, int offset);

// Class Plugin
ChromaAnimationAPI::SubtractNonZeroTargetAllKeysOffset(
	int sourceAnimationId, int targetAnimationId, int frameId, int offset);
```

---
<a name="PluginSubtractNonZeroTargetAllKeysOffsetName"></a>
**PluginSubtractNonZeroTargetAllKeysOffsetName**

```C++
// DLL Interface
EXPORT_API void PluginSubtractNonZeroTargetAllKeysOffsetName(
	const char* sourceAnimation, const char* targetAnimation, int frameId, int offset);

// Class Plugin
ChromaAnimationAPI::SubtractNonZeroTargetAllKeysOffsetName(
	const char* sourceAnimation, const char* targetAnimation, int frameId, int offset);
```

---
<a name="PluginSubtractNonZeroTargetAllKeysOffsetNameD"></a>
**PluginSubtractNonZeroTargetAllKeysOffsetNameD**

```C++
// DLL Interface
EXPORT_API double PluginSubtractNonZeroTargetAllKeysOffsetNameD(
	const char* sourceAnimation, const char* targetAnimation, double frameId,
	double offset);

// Class Plugin
double result = ChromaAnimationAPI::SubtractNonZeroTargetAllKeysOffsetNameD(
	const char* sourceAnimation, const char* targetAnimation, double frameId,
	double offset);
```

---
<a name="PluginTrimEndFrames"></a>
**PluginTrimEndFrames**

```C++
// DLL Interface
EXPORT_API void PluginTrimEndFrames(
	int animationId, int lastFrameId);

// Class Plugin
ChromaAnimationAPI::TrimEndFrames(
	int animationId, int lastFrameId);
```

---
<a name="PluginTrimEndFramesName"></a>
**PluginTrimEndFramesName**

```C++
// DLL Interface
EXPORT_API void PluginTrimEndFramesName(
	const char* path, int lastFrameId);

// Class Plugin
ChromaAnimationAPI::TrimEndFramesName(
	const char* path, int lastFrameId);
```

---
<a name="PluginTrimEndFramesNameD"></a>
**PluginTrimEndFramesNameD**

```C++
// DLL Interface
EXPORT_API double PluginTrimEndFramesNameD(
	const char* path, double lastFrameId);

// Class Plugin
double result = ChromaAnimationAPI::TrimEndFramesNameD(
	const char* path, double lastFrameId);
```

---
<a name="PluginTrimFrame"></a>
**PluginTrimFrame**

```C++
// DLL Interface
EXPORT_API void PluginTrimFrame(
	int animationId, int frameId);

// Class Plugin
ChromaAnimationAPI::TrimFrame(
	int animationId, int frameId);
```

---
<a name="PluginTrimFrameName"></a>
**PluginTrimFrameName**

```C++
// DLL Interface
EXPORT_API void PluginTrimFrameName(
	const char* path, int frameId);

// Class Plugin
ChromaAnimationAPI::TrimFrameName(
	const char* path, int frameId);
```

---
<a name="PluginTrimFrameNameD"></a>
**PluginTrimFrameNameD**

```C++
// DLL Interface
EXPORT_API double PluginTrimFrameNameD(
	const char* path, double frameId);

// Class Plugin
double result = ChromaAnimationAPI::TrimFrameNameD(
	const char* path, double frameId);
```

---
<a name="PluginTrimStartFrames"></a>
**PluginTrimStartFrames**

```C++
// DLL Interface
EXPORT_API void PluginTrimStartFrames(
	int animationId, int numberOfFrames);

// Class Plugin
ChromaAnimationAPI::TrimStartFrames(
	int animationId, int numberOfFrames);
```

---
<a name="PluginTrimStartFramesName"></a>
**PluginTrimStartFramesName**

```C++
// DLL Interface
EXPORT_API void PluginTrimStartFramesName(
	const char* path, int numberOfFrames);

// Class Plugin
ChromaAnimationAPI::TrimStartFramesName(
	const char* path, int numberOfFrames);
```

---
<a name="PluginTrimStartFramesNameD"></a>
**PluginTrimStartFramesNameD**

```C++
// DLL Interface
EXPORT_API double PluginTrimStartFramesNameD(
	const char* path, double numberOfFrames);

// Class Plugin
double result = ChromaAnimationAPI::TrimStartFramesNameD(
	const char* path, double numberOfFrames);
```

---
<a name="PluginUninit"></a>
**PluginUninit**

Uninitializes the `ChromaSDK`. Returns 0 upon success. Returns -1 upon failure.

```C++
// DLL Interface
EXPORT_API int PluginUninit();

// Class Plugin
int result = ChromaAnimationAPI::Uninit();
```

---
<a name="PluginUninitD"></a>
**PluginUninitD**

```C++
// DLL Interface
EXPORT_API double PluginUninitD();

// Class Plugin
double result = ChromaAnimationAPI::UninitD();
```

---
<a name="PluginUnloadAnimation"></a>
**PluginUnloadAnimation**

Unloads `Chroma` effects to free up resources. Returns the animation id
upon success. Returns -1 upon failure.

```C++
// DLL Interface
EXPORT_API int PluginUnloadAnimation(int animationId);

// Class Plugin
int result = ChromaAnimationAPI::UnloadAnimation(int animationId);
```

---
<a name="PluginUnloadAnimationD"></a>
**PluginUnloadAnimationD**

```C++
// DLL Interface
EXPORT_API double PluginUnloadAnimationD(double animationId);

// Class Plugin
double result = ChromaAnimationAPI::UnloadAnimationD(double animationId);
```

---
<a name="PluginUnloadAnimationName"></a>
**PluginUnloadAnimationName**

```C++
// DLL Interface
EXPORT_API void PluginUnloadAnimationName(const char* path);

// Class Plugin
ChromaAnimationAPI::UnloadAnimationName(const char* path);
```

---
<a name="PluginUnloadComposite"></a>
**PluginUnloadComposite**

```C++
// DLL Interface
EXPORT_API void PluginUnloadComposite(const char* name);

// Class Plugin
ChromaAnimationAPI::UnloadComposite(const char* name);
```

---
<a name="PluginUpdateFrame"></a>
**PluginUpdateFrame**

Updates the `frameIndex` of the `Chroma` animation and sets the `duration`
(in seconds). The `color` is expected to be an array of the dimensions
for the `deviceType/device`. The `length` parameter is the size of the
`color` array. For `EChromaSDKDevice1DEnum` the array size should be `MAX
LEDS`. For `EChromaSDKDevice2DEnum` the array size should be `MAX ROW`
* `MAX COLUMN`. Returns the animation id upon success. Returns -1 upon
failure.

```C++
// DLL Interface
EXPORT_API int PluginUpdateFrame(
	int animationId, int frameIndex, float duration, int* colors, int length);

// Class Plugin
int result = ChromaAnimationAPI::UpdateFrame(
	int animationId, int frameIndex, float duration, int* colors, int length);
```




<br/><br/>

<hr/>

* (End of automation)

<br/><br/>





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


<a name="PluginCloseComposite"></a>
**PluginCloseComposite**

`PluginCloseComposite` closes a set of animations so they can be reloaded from disk. The set of animations will be stopped if playing.

```C++
EXPORT_API void PluginCloseComposite(const char* name);

// Given "Random" this will invoke:
// PluginCloseAnimationName("Random_ChromaLink.chroma");
// PluginCloseAnimationName("Random_Headset.chroma");
// PluginCloseAnimationName("Random_Keyboard.chroma");
// PluginCloseAnimationName("Random_Keypad.chroma");
// PluginCloseAnimationName("Random_Mouse.chroma");
// PluginCloseAnimationName("Random_Mousepad.chroma");
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

(Auto-documentation needs sample snippet section)


<a name="PluginSetKeysColorName"></a>
**PluginSetKeysColorName**

Set an array of animation keys to a static color for the given frame.

```C++
EXPORT_API void PluginSetKeysColorName(const char* path, int frameId, const int* rzkeys, int keyCount, int color);
```

Usage:

```C++
const char* animationName = "Blank_Keyboard.chroma";
int frameCount = _gMethodGetFrameCountName(animationName);

int wasdKeys[4] =
{
  (int)Keyboard::RZKEY::RZKEY_W,
  (int)Keyboard::RZKEY::RZKEY_A,
  (int)Keyboard::RZKEY::RZKEY_S,
  (int)Keyboard::RZKEY::RZKEY_D,
};
for (int i = 0; i < frameCount; ++i)
{
  _gMethodSetKeysColorName(animationName, i, wasdKeys, size(wasdKeys), 0xFF);
}
_gMethodPlayAnimationName(animationName, false);
```


<a name="PluginSetKeysNonZeroColorName"></a>
**PluginSetKeysNonZeroColorName**

Set an array of animation keys to a static color for the given frame if the existing color is not already black.

```C++
EXPORT_API void PluginSetKeysNonZeroColorName(const char* path, int frameId,
  const int* rzkeys, int keyCount, int color);
```

Usage:

```C++
const char* animationName = "Blank_Keyboard.chroma";
int frameCount = _gMethodGetFrameCountName(animationName);

int wasdKeys[4] =
{
  (int)Keyboard::RZKEY::RZKEY_W,
  (int)Keyboard::RZKEY::RZKEY_A,
  (int)Keyboard::RZKEY::RZKEY_S,
  (int)Keyboard::RZKEY::RZKEY_D,
};
for (int i = 0; i < frameCount; ++i)
{
  _gMethodSetKeysNonZeroColorName(animationName, i, wasdKeys, size(wasdKeys), 0xFF);
}
_gMethodPlayAnimationName(animationName, false);
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
