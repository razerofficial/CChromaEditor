// CConsoleEditor.cpp : Defines the entry point for the console application.
//

#define CHROMA_EDITOR_DLL _T("CChromaEditorLibrary.dll")

#include "stdafx.h"
#include <chrono>
#include <thread>
#include <Windows.h>
#include "..\CChromaEditorLibrary\ChromaSDKPluginTypes.h"

typedef void(*PLUGIN_INIT)();
typedef bool(*PLUGIN_IS_INITIALIZED)();
typedef void(*PLUGIN_UNINIT)();
typedef bool(*PLUGIN_IS_DIALOG_OPEN)();
typedef int(*PLUGIN_OPEN_EDITOR_DIALOG)(const char* path);
typedef int(*PLUGIN_OPEN_EDITOR_DIALOG_AND_PLAY)(const char* path);
typedef int(*PLUGIN_OPEN_ANIMATION)(const char* path);
typedef int(*PLUGIN_CLOSE_ANIMATION)(int animationId);
typedef void(*PLUGIN_CLOSE_ANIMATION_NAME)(const char* path);
typedef void(*PLUGIN_CLOSE_COMPOSITE)(const char* name);
typedef void(*PLUGIN_CLOSE_ALL)();
typedef int(*PLUGIN_CREATE_ANIMATION)(const char* path, int deviceType, int device);
typedef int(*PLUGIN_CREATE_ANIMATION_IN_MEMORY)(int deviceType, int device);
typedef int(*PLUGIN_PREVIEW_FRAME)(int animationId, int frameIndex);
typedef int(*PLUGIN_PLAY_ANIMATION)(int animationId);
typedef void(*PLUGIN_PLAY_ANIMATION_NAME)(const char* path, bool loop);
typedef void(*PLUGIN_STOP_ANIMATION_NAME)(const char* path);
typedef void(*PLUGIN_STOP_ANIMATION_TYPE)(int deviceType, int device);
typedef void(*PLUGIN_STOP_COMPOSITE)(const char* name);
typedef void(*PLUGIN_STOP_ALL)();
typedef bool(*PLUGIN_IS_PLAYING_NAME)(const char* name);
typedef bool(*PLUGIN_IS_PLAYING_TYPE)(int deviceType, int device);
typedef void(*PLUGIN_LOAD_COMPOSITE)(const char* name);
typedef void(*PLUGIN_UNLOAD_COMPOSITE)(const char* name);
typedef void(*PLUGIN_PLAY_COMPOSITE)(const char* name, bool loop);
typedef void(*PLUGIN_LOAD_ANIMATION_NAME)(const char* path);
typedef void(*PLUGIN_UNLOAD_ANIMATION_NAME)(const char* path);
typedef int(*PLUGIN_GET_MAX_ROW)(int device);
typedef int(*PLUGIN_GET_MAX_COLUMN)(int device);
typedef int(*PLUGIN_ADD_FRAME)(int animationId, float duration, int* colors, int length);
typedef int(*PLUGIN_GET_FRAME)(int animationId, int frameIndex, float* duration, int* colors, int length);
typedef int(*PLUGIN_GET_FRAME_COUNT_NAME)(const char* path);
typedef void(*PLUGIN_SET_KEY_COLOR)(int animationId, int frameId, int rzkey, int color);
typedef void(*PLUGIN_SET_KEY_COLOR_NAME)(const char* path, int frameId, int rzkey, int color);
typedef void(*PLUGIN_SET_KEYS_COLOR_NAME)(const char* path, int frameId, const int* rzkeys, int keyCount, int color);
typedef void(*PLUGIN_SET_KEY_NONZERO_COLOR_NAME)(const char* path, int frameId, int rzkey, int color);
typedef void(*PLUGIN_SET_KEYS_NONZERO_COLOR_NAME)(const char* path, int frameId, const int* rzkeys, int keyCount, int color);
typedef void(*PLUGIN_COPY_NONZERO_ALL_KEYS_ALL_FRAMES_NAME)(const char* sourceAnimation, const char* targetAnimation);
typedef void(*PLUGIN_COPY_KEY_COLOR_NAME)(const char* sourceAnimation, const char* targetAnimation, int frameId, int rzkey);
typedef void(*PLUGIN_FILL_COLOR_NAME)(const char* path, int frameId, int red, int green, int blue);
typedef void(*PLUGIN_FILL_COLOR_ALL_FRAMES_NAME)(const char* path, int red, int green, int blue);
typedef void(*PLUGIN_FILL_NONZERO_COLOR_NAME)(const char* path, int frameId, int red, int green, int blue);
typedef void(*PLUGIN_FILL_NONZERO_COLOR_ALL_FRAMES_NAME)(const char* path, int red, int green, int blue);
typedef void(*PLUGIN_OFFSET_COLORS_NAME)(const char* path, int frameId, int red, int green, int blue);
typedef void(*PLUGIN_OFFSET_COLORS_ALL_FRAMES_NAME)(const char* path, int red, int green, int blue);
typedef void(*PLUGIN_OFFSET_NONZERO_COLORS_NAME)(const char* path, int frameId, int red, int green, int blue);
typedef void(*PLUGIN_OFFSET_NONZERO_COLORS_ALL_FRAMES_NAME)(const char* path, int red, int green, int blue);
typedef void(*PLUGIN_MULTIPLY_INTENSITY_NAME)(const char* path, int frameId, float intensity);
typedef void(*PLUGIN_MULTIPLY_INTENSITY_ALL_FRAMES_NAME)(const char* path, float intensity);
typedef bool(*PLUGIN_KEYBOARD_USE_CHROMA_CUSTOM)(int animationId, bool flag);
typedef bool(*PLUGIN_KEYBOARD_USE_CHROMA_CUSTOM_NAME)(const char* path, bool flag);
typedef const char*(*PLUGIN_GET_ANIMATION_NAME)(int animationId);
typedef void(*PLUGIN_CLEAR_ANIMATION_TYPE)(int deviceType, int device);
typedef void(*PLUGIN_CLEAR_ALL)();
typedef int(*PLUGIN_GET_ANIMATION_COUNT)();
typedef int(*PLUGIN_GET_ANIMATION_ID)(int index);
typedef int(*PLUGIN_GET_PLAYING_ANIMATION_COUNT)();
typedef int(*PLUGIN_GET_PLAYING_ANIMATION_ID)(int index);
typedef long(*PLUGIN_CREATE_EFFECT)(RZDEVICEID deviceId, ChromaSDK::EFFECT_TYPE effect, int* colors, int size, ChromaSDK::FChromaSDKGuid* effectGUID);
typedef long(*PLUGIN_SET_EFFECT)(const ChromaSDK::FChromaSDKGuid& effectGUID);
typedef long(*PLUGIN_DELETE_EFFECT)(const ChromaSDK::FChromaSDKGuid& effectGUID);

#if RUN_UNIT_TESTS
void DebugUnitTests();
#endif

using namespace std;
using namespace std::chrono;
using namespace ChromaSDK;

#define CHROMASDK_DECLARE_METHOD(Signature, FieldName) Signature _gMethod ## FieldName = nullptr;

CHROMASDK_DECLARE_METHOD(PLUGIN_IS_INITIALIZED, IsInitialized)
CHROMASDK_DECLARE_METHOD(PLUGIN_IS_INITIALIZED, IsInitialized2)
CHROMASDK_DECLARE_METHOD(PLUGIN_IS_DIALOG_OPEN, IsDialogOpen)
CHROMASDK_DECLARE_METHOD(PLUGIN_OPEN_EDITOR_DIALOG, OpenEditorDialog)
CHROMASDK_DECLARE_METHOD(PLUGIN_OPEN_EDITOR_DIALOG_AND_PLAY, OpenEditorDialogAndPlay)
CHROMASDK_DECLARE_METHOD(PLUGIN_OPEN_ANIMATION, OpenAnimation)
CHROMASDK_DECLARE_METHOD(PLUGIN_CLOSE_ANIMATION, CloseAnimation)
CHROMASDK_DECLARE_METHOD(PLUGIN_PREVIEW_FRAME, PreviewFrame)
CHROMASDK_DECLARE_METHOD(PLUGIN_PLAY_ANIMATION, PlayAnimation)
CHROMASDK_DECLARE_METHOD(PLUGIN_PLAY_ANIMATION_NAME, PlayAnimationName)
CHROMASDK_DECLARE_METHOD(PLUGIN_STOP_ANIMATION_NAME, StopAnimationName)
CHROMASDK_DECLARE_METHOD(PLUGIN_STOP_ANIMATION_TYPE, StopAnimationType)
CHROMASDK_DECLARE_METHOD(PLUGIN_IS_PLAYING_NAME, IsPlayingName)
CHROMASDK_DECLARE_METHOD(PLUGIN_IS_PLAYING_TYPE, IsPlayingType)
CHROMASDK_DECLARE_METHOD(PLUGIN_LOAD_COMPOSITE, LoadComposite)
CHROMASDK_DECLARE_METHOD(PLUGIN_UNLOAD_COMPOSITE, UnloadComposite)
CHROMASDK_DECLARE_METHOD(PLUGIN_PLAY_COMPOSITE, PlayComposite)
CHROMASDK_DECLARE_METHOD(PLUGIN_STOP_COMPOSITE, StopComposite)
CHROMASDK_DECLARE_METHOD(PLUGIN_CLOSE_COMPOSITE, CloseComposite)
CHROMASDK_DECLARE_METHOD(PLUGIN_CLOSE_ALL, CloseAll)
CHROMASDK_DECLARE_METHOD(PLUGIN_CREATE_ANIMATION, CreateAnimation)
CHROMASDK_DECLARE_METHOD(PLUGIN_CREATE_ANIMATION_IN_MEMORY, CreateAnimationInMemory)
CHROMASDK_DECLARE_METHOD(PLUGIN_INIT, Init)
CHROMASDK_DECLARE_METHOD(PLUGIN_UNINIT, Uninit)
CHROMASDK_DECLARE_METHOD(PLUGIN_CLOSE_ANIMATION_NAME, CloseAnimationName)
CHROMASDK_DECLARE_METHOD(PLUGIN_LOAD_ANIMATION_NAME, LoadAnimationName)
CHROMASDK_DECLARE_METHOD(PLUGIN_UNLOAD_ANIMATION_NAME, UnloadAnimationName)
CHROMASDK_DECLARE_METHOD(PLUGIN_GET_MAX_ROW, GetMaxRow)
CHROMASDK_DECLARE_METHOD(PLUGIN_GET_MAX_COLUMN, GetMaxColumn)
CHROMASDK_DECLARE_METHOD(PLUGIN_ADD_FRAME, AddFrame)
CHROMASDK_DECLARE_METHOD(PLUGIN_GET_FRAME, GetFrame)
CHROMASDK_DECLARE_METHOD(PLUGIN_GET_FRAME_COUNT_NAME, GetFrameCountName)
CHROMASDK_DECLARE_METHOD(PLUGIN_SET_KEY_COLOR, SetKeyColor)
CHROMASDK_DECLARE_METHOD(PLUGIN_SET_KEY_COLOR_NAME, SetKeyColorName)
CHROMASDK_DECLARE_METHOD(PLUGIN_SET_KEYS_COLOR_NAME, SetKeysColorName)
CHROMASDK_DECLARE_METHOD(PLUGIN_SET_KEY_NONZERO_COLOR_NAME, SetKeyNonZeroColorName)
CHROMASDK_DECLARE_METHOD(PLUGIN_SET_KEYS_NONZERO_COLOR_NAME, SetKeysNonZeroColorName)
CHROMASDK_DECLARE_METHOD(PLUGIN_COPY_NONZERO_ALL_KEYS_ALL_FRAMES_NAME, CopyNonZeroAllKeysAllFramesName)
CHROMASDK_DECLARE_METHOD(PLUGIN_COPY_KEY_COLOR_NAME, CopyKeyColorName)
CHROMASDK_DECLARE_METHOD(PLUGIN_FILL_COLOR_NAME, FillColorName)
CHROMASDK_DECLARE_METHOD(PLUGIN_FILL_COLOR_ALL_FRAMES_NAME, FillColorAllFramesName)
CHROMASDK_DECLARE_METHOD(PLUGIN_FILL_NONZERO_COLOR_NAME, FillNonZeroColorName)
CHROMASDK_DECLARE_METHOD(PLUGIN_FILL_NONZERO_COLOR_ALL_FRAMES_NAME, FillNonZeroColorAllFramesName)
CHROMASDK_DECLARE_METHOD(PLUGIN_OFFSET_COLORS_NAME, OffsetColorsName)
CHROMASDK_DECLARE_METHOD(PLUGIN_OFFSET_COLORS_ALL_FRAMES_NAME, OffsetColorsAllFramesName)
CHROMASDK_DECLARE_METHOD(PLUGIN_OFFSET_NONZERO_COLORS_NAME, OffsetNonZeroColorsName)
CHROMASDK_DECLARE_METHOD(PLUGIN_OFFSET_NONZERO_COLORS_ALL_FRAMES_NAME, OffsetNonZeroColorsAllFramesName)
CHROMASDK_DECLARE_METHOD(PLUGIN_MULTIPLY_INTENSITY_NAME, MultiplyIntensityName)
CHROMASDK_DECLARE_METHOD(PLUGIN_MULTIPLY_INTENSITY_ALL_FRAMES_NAME, MultiplyIntensityAllFramesName)
CHROMASDK_DECLARE_METHOD(PLUGIN_KEYBOARD_USE_CHROMA_CUSTOM, KeyboardUseChromaCustom)
CHROMASDK_DECLARE_METHOD(PLUGIN_KEYBOARD_USE_CHROMA_CUSTOM_NAME, KeyboardUseChromaCustomName)
CHROMASDK_DECLARE_METHOD(PLUGIN_GET_ANIMATION_NAME, GetAnimationName)
CHROMASDK_DECLARE_METHOD(PLUGIN_STOP_ALL, StopAll)
CHROMASDK_DECLARE_METHOD(PLUGIN_CLEAR_ANIMATION_TYPE, ClearAnimationType)
CHROMASDK_DECLARE_METHOD(PLUGIN_CLEAR_ALL, ClearAll)
CHROMASDK_DECLARE_METHOD(PLUGIN_GET_ANIMATION_COUNT, GetAnimationCount)
CHROMASDK_DECLARE_METHOD(PLUGIN_GET_ANIMATION_ID, GetAnimationId)
CHROMASDK_DECLARE_METHOD(PLUGIN_GET_PLAYING_ANIMATION_COUNT, GetPlayingAnimationCount)
CHROMASDK_DECLARE_METHOD(PLUGIN_GET_PLAYING_ANIMATION_ID, GetPlayingAnimationId)
CHROMASDK_DECLARE_METHOD(PLUGIN_CREATE_EFFECT, CreateEffect)
CHROMASDK_DECLARE_METHOD(PLUGIN_SET_EFFECT, SetEffect)
CHROMASDK_DECLARE_METHOD(PLUGIN_DELETE_EFFECT, DeleteEffect)

#define CHROMASDK_VALIDATE_METHOD(Signature, FieldName) _gMethod ## FieldName = (Signature) GetProcAddress(library, "Plugin" #FieldName); \
if (_gMethod ## FieldName == nullptr) \
{ \
	fprintf(stderr, "Failed to find method: %s!\r\n", "Plugin" #FieldName); \
	return -1; \
}

int Init()
{
	HMODULE library = LoadLibrary(CHROMA_EDITOR_DLL);
	if (library == NULL)
	{
		fprintf(stderr, "Failed to load Chroma Editor Library!\r\n");
		return -1;
	}

	fprintf(stderr, "Loaded Chroma Editor DLL!\r\n");

	CHROMASDK_VALIDATE_METHOD(PLUGIN_IS_INITIALIZED, IsInitialized);
	CHROMASDK_VALIDATE_METHOD(PLUGIN_IS_DIALOG_OPEN, IsDialogOpen);
	CHROMASDK_VALIDATE_METHOD(PLUGIN_OPEN_EDITOR_DIALOG, OpenEditorDialog);
	CHROMASDK_VALIDATE_METHOD(PLUGIN_OPEN_EDITOR_DIALOG_AND_PLAY, OpenEditorDialogAndPlay);
	CHROMASDK_VALIDATE_METHOD(PLUGIN_OPEN_ANIMATION, OpenAnimation);
	CHROMASDK_VALIDATE_METHOD(PLUGIN_CLOSE_ANIMATION, CloseAnimation);
	CHROMASDK_VALIDATE_METHOD(PLUGIN_PREVIEW_FRAME, PreviewFrame);
	CHROMASDK_VALIDATE_METHOD(PLUGIN_PLAY_ANIMATION, PlayAnimation);
	CHROMASDK_VALIDATE_METHOD(PLUGIN_PLAY_ANIMATION_NAME, PlayAnimationName);
	CHROMASDK_VALIDATE_METHOD(PLUGIN_STOP_ANIMATION_NAME, StopAnimationName);
	CHROMASDK_VALIDATE_METHOD(PLUGIN_STOP_ANIMATION_TYPE, StopAnimationType);
	CHROMASDK_VALIDATE_METHOD(PLUGIN_IS_PLAYING_NAME, IsPlayingName);
	CHROMASDK_VALIDATE_METHOD(PLUGIN_IS_PLAYING_TYPE, IsPlayingType);
	CHROMASDK_VALIDATE_METHOD(PLUGIN_LOAD_COMPOSITE, LoadComposite);
	CHROMASDK_VALIDATE_METHOD(PLUGIN_UNLOAD_COMPOSITE, UnloadComposite);
	CHROMASDK_VALIDATE_METHOD(PLUGIN_PLAY_COMPOSITE, PlayComposite);
	CHROMASDK_VALIDATE_METHOD(PLUGIN_STOP_COMPOSITE, StopComposite);
	CHROMASDK_VALIDATE_METHOD(PLUGIN_CLOSE_COMPOSITE, CloseComposite);
	CHROMASDK_VALIDATE_METHOD(PLUGIN_CLOSE_ALL, CloseAll);
	CHROMASDK_VALIDATE_METHOD(PLUGIN_CREATE_ANIMATION, CreateAnimation);
	CHROMASDK_VALIDATE_METHOD(PLUGIN_CREATE_ANIMATION_IN_MEMORY, CreateAnimationInMemory);
	CHROMASDK_VALIDATE_METHOD(PLUGIN_INIT, Init);
	CHROMASDK_VALIDATE_METHOD(PLUGIN_UNINIT, Uninit);
	CHROMASDK_VALIDATE_METHOD(PLUGIN_CLOSE_ANIMATION_NAME, CloseAnimationName);
	CHROMASDK_VALIDATE_METHOD(PLUGIN_LOAD_ANIMATION_NAME, LoadAnimationName);
	CHROMASDK_VALIDATE_METHOD(PLUGIN_UNLOAD_ANIMATION_NAME, UnloadAnimationName);
	CHROMASDK_VALIDATE_METHOD(PLUGIN_GET_MAX_ROW, GetMaxRow);
	CHROMASDK_VALIDATE_METHOD(PLUGIN_GET_MAX_COLUMN, GetMaxColumn);
	CHROMASDK_VALIDATE_METHOD(PLUGIN_ADD_FRAME, AddFrame);
	CHROMASDK_VALIDATE_METHOD(PLUGIN_GET_FRAME, GetFrame);
	CHROMASDK_VALIDATE_METHOD(PLUGIN_GET_FRAME_COUNT_NAME, GetFrameCountName);
	CHROMASDK_VALIDATE_METHOD(PLUGIN_SET_KEY_COLOR, SetKeyColor);
	CHROMASDK_VALIDATE_METHOD(PLUGIN_SET_KEY_COLOR_NAME, SetKeyColorName);
	CHROMASDK_VALIDATE_METHOD(PLUGIN_SET_KEYS_COLOR_NAME, SetKeysColorName);
	CHROMASDK_VALIDATE_METHOD(PLUGIN_SET_KEY_NONZERO_COLOR_NAME, SetKeyNonZeroColorName);
	CHROMASDK_VALIDATE_METHOD(PLUGIN_SET_KEYS_NONZERO_COLOR_NAME, SetKeysNonZeroColorName);
	CHROMASDK_VALIDATE_METHOD(PLUGIN_COPY_NONZERO_ALL_KEYS_ALL_FRAMES_NAME, CopyNonZeroAllKeysAllFramesName);
	CHROMASDK_VALIDATE_METHOD(PLUGIN_COPY_KEY_COLOR_NAME, CopyKeyColorName);
	CHROMASDK_VALIDATE_METHOD(PLUGIN_FILL_COLOR_NAME, FillColorName);
	CHROMASDK_VALIDATE_METHOD(PLUGIN_FILL_COLOR_ALL_FRAMES_NAME, FillColorAllFramesName);
	CHROMASDK_VALIDATE_METHOD(PLUGIN_FILL_NONZERO_COLOR_NAME, FillNonZeroColorName);
	CHROMASDK_VALIDATE_METHOD(PLUGIN_FILL_NONZERO_COLOR_ALL_FRAMES_NAME, FillNonZeroColorAllFramesName);
	CHROMASDK_VALIDATE_METHOD(PLUGIN_OFFSET_COLORS_NAME, OffsetColorsName);
	CHROMASDK_VALIDATE_METHOD(PLUGIN_OFFSET_COLORS_ALL_FRAMES_NAME, OffsetColorsAllFramesName);
	CHROMASDK_VALIDATE_METHOD(PLUGIN_OFFSET_NONZERO_COLORS_NAME, OffsetNonZeroColorsName);
	CHROMASDK_VALIDATE_METHOD(PLUGIN_OFFSET_NONZERO_COLORS_ALL_FRAMES_NAME, OffsetNonZeroColorsAllFramesName);
	CHROMASDK_VALIDATE_METHOD(PLUGIN_MULTIPLY_INTENSITY_NAME, MultiplyIntensityName);
	CHROMASDK_VALIDATE_METHOD(PLUGIN_MULTIPLY_INTENSITY_ALL_FRAMES_NAME, MultiplyIntensityAllFramesName);
	CHROMASDK_VALIDATE_METHOD(PLUGIN_KEYBOARD_USE_CHROMA_CUSTOM, KeyboardUseChromaCustom);
	CHROMASDK_VALIDATE_METHOD(PLUGIN_KEYBOARD_USE_CHROMA_CUSTOM_NAME, KeyboardUseChromaCustomName);
	CHROMASDK_VALIDATE_METHOD(PLUGIN_GET_ANIMATION_NAME, GetAnimationName);
	CHROMASDK_VALIDATE_METHOD(PLUGIN_STOP_ALL, StopAll);
	CHROMASDK_VALIDATE_METHOD(PLUGIN_CLEAR_ANIMATION_TYPE, ClearAnimationType);
	CHROMASDK_VALIDATE_METHOD(PLUGIN_CLEAR_ALL, ClearAll);
	CHROMASDK_VALIDATE_METHOD(PLUGIN_GET_ANIMATION_COUNT, GetAnimationCount);
	CHROMASDK_VALIDATE_METHOD(PLUGIN_GET_ANIMATION_ID, GetAnimationId);
	CHROMASDK_VALIDATE_METHOD(PLUGIN_GET_PLAYING_ANIMATION_COUNT, GetPlayingAnimationCount);
	CHROMASDK_VALIDATE_METHOD(PLUGIN_GET_PLAYING_ANIMATION_ID, GetPlayingAnimationId);
	CHROMASDK_VALIDATE_METHOD(PLUGIN_CREATE_EFFECT, CreateEffect);
	CHROMASDK_VALIDATE_METHOD(PLUGIN_SET_EFFECT, SetEffect);
	CHROMASDK_VALIDATE_METHOD(PLUGIN_DELETE_EFFECT, DeleteEffect);	

	fprintf(stderr, "Found all DLL methods!\r\n");
	return 0;
}

int OpenAndPlay(const char* path)
{
	int animationId = (int)_gMethodOpenAnimation(path);
	fprintf(stdout, "OpenAnimation: %s result=%d\r\n", path, animationId);
	if (animationId >= 0)
	{
		int result = (int)_gMethodPlayAnimation(animationId);
		fprintf(stdout, "PlayAnimation: %d result=%d\r\n", animationId, result);
		return result;
	}
	else
	{
		return -1;
	}
}

int CloseAnimation(int animationId)
{
	int result = (int)_gMethodCloseAnimation(animationId);
	fprintf(stdout, "CloseAnimation: %d result=%d\r\n", animationId, result);
	return result;
}

int main(int argc, char *argv[])
{
	fprintf(stderr, "App launched!\r\n");
	if (Init() != 0)
	{
		return -1;
	}	

#if RUN_UNIT_TESTS
	DebugUnitTests();
#endif

	if (argc <= 1)
	{
		char* buffer = nullptr;
		size_t sz = 0;
		if (_dupenv_s(&buffer, &sz, "USERPROFILE") == 0
			&& buffer != nullptr)
		{
			//fprintf(stdout, "EnvVarName = %s\n", buffer);
			char path[256] = { 0 };
			sprintf_s(path, "%s\\Desktop\\temp.chroma", buffer);		
			free(buffer);
			_gMethodOpenEditorDialogAndPlay(path);
		}
		else
		{
			_gMethodOpenEditorDialogAndPlay("temp.chroma");
		}
	}
	else
	{
		_gMethodOpenEditorDialogAndPlay(argv[1]);
	}

	while (_gMethodIsDialogOpen())
	{
		Sleep(0);
	}

	_gMethodUninit();
	fprintf(stdout, "CConsoleEditor exited.\r\n");

    return 0;
}

void IsPlaying(const char* name)
{
	fprintf(stdout, "%s_ChromaLink IsPlayingName: %s\r\n", name, _gMethodIsPlayingName("Random_Keyboard.chroma") ? "true" : "false");
	fprintf(stdout, "%s_Headset IsPlayingName: %s\r\n", name, _gMethodIsPlayingName("Random_Keyboard.chroma") ? "true" : "false");
	fprintf(stdout, "%s_Keyboard IsPlayingName: %s\r\n", name, _gMethodIsPlayingName("Random_Keyboard.chroma") ? "true" : "false");
	fprintf(stdout, "%s_Keypad IsPlayingName: %s\r\n", name, _gMethodIsPlayingName("Random_Keyboard.chroma") ? "true" : "false");
	fprintf(stdout, "%s_Mouse IsPlayingName: %s\r\n", name, _gMethodIsPlayingName("Random_Keyboard.chroma") ? "true" : "false");
	fprintf(stdout, "%s_Mousepad IsPlayingName: %s\r\n", name, _gMethodIsPlayingName("Random_Keyboard.chroma") ? "true" : "false");

	fprintf(stdout, "ChromaLink IsPlayingType: %s\r\n", _gMethodIsPlayingType((int)EChromaSDKDeviceTypeEnum::DE_1D, (int)EChromaSDKDevice1DEnum::DE_ChromaLink) ? "true" : "false");
	fprintf(stdout, "Headset IsPlayingType: %s\r\n", _gMethodIsPlayingType((int)EChromaSDKDeviceTypeEnum::DE_1D, (int)EChromaSDKDevice1DEnum::DE_Headset) ? "true" : "false");
	fprintf(stdout, "Keyboard IsPlayingType: %s\r\n", _gMethodIsPlayingType((int)EChromaSDKDeviceTypeEnum::DE_2D, (int)EChromaSDKDevice2DEnum::DE_Keyboard) ? "true" : "false");
	fprintf(stdout, "Keypad IsPlayingType: %s\r\n", _gMethodIsPlayingType((int)EChromaSDKDeviceTypeEnum::DE_2D, (int)EChromaSDKDevice2DEnum::DE_Keypad) ? "true" : "false");
	fprintf(stdout, "Mouse IsPlayingType: %s\r\n", _gMethodIsPlayingType((int)EChromaSDKDeviceTypeEnum::DE_2D, (int)EChromaSDKDevice2DEnum::DE_Mouse) ? "true" : "false");
	fprintf(stdout, "Mousepad IsPlayingType: %s\r\n", _gMethodIsPlayingType((int)EChromaSDKDeviceTypeEnum::DE_1D, (int)EChromaSDKDevice1DEnum::DE_Mousepad) ? "true" : "false");
}

void DebugUnitTestsPlayComposite()
{
	while (true)
	{
		fprintf(stdout, "Measure CPU usage.\r\n");
		const char* RANDOM_COMPOSITE = "Random";
		_gMethodPlayComposite(RANDOM_COMPOSITE, false);
		Sleep(3000);
	}
}

void DebugUnitTestsOpenDialog()
{
	_gMethodOpenEditorDialog("RandomKeyboardEffect.chroma");
	while (_gMethodIsDialogOpen())
	{
		Sleep(0);
	}
}

void DebugUnitTestsOpenClose()
{
	for (int i = 0; i < 25; ++i)
	{
		if (_gMethodIsInitialized() == 0)
		{
			fprintf(stdout, "Init...\r\n");
			_gMethodInit();
		}

		fprintf(stdout, "Playing effects...\r\n");
		int randomChromaLinkEffect = OpenAndPlay("Random_ChromaLink.chroma");
		int randomHeadsetEffect = OpenAndPlay("Random_Headset.chroma");
		int randomKeyboardEffect = OpenAndPlay("Random_Keyboard.chroma");
		int randomKeypadEffect = OpenAndPlay("Random_Keypad.chroma");
		int randomMouseEffect = OpenAndPlay("Random_Mouse.chroma");
		int randomMousepadEffect = OpenAndPlay("Random_Mousepad.chroma");
		this_thread::sleep_for(chrono::seconds(1));

		_gMethodCloseAnimation(randomChromaLinkEffect);
		_gMethodCloseAnimation(randomHeadsetEffect);
		_gMethodCloseAnimation(randomKeyboardEffect);
		_gMethodCloseAnimation(randomKeypadEffect);
		_gMethodCloseAnimation(randomMouseEffect);
		_gMethodCloseAnimation(randomMousepadEffect);

		fprintf(stdout, "Simulate exit...\r\n");
		_gMethodUninit();
	}
}

void DebugUnitTestsLayering()
{
	const char* BLANK_KEYBOARD = "Blank_Keyboard.chroma";
	const char* RANDOM_KEYBOARD = "Random_Keyboard.chroma";

	const char* animationName = "";
	int animationId = -1;

	int keyboardMaxRow = _gMethodGetMaxRow((int)EChromaSDKDevice2DEnum::DE_Keyboard);
	int keyboardMaxColumn = _gMethodGetMaxColumn((int)EChromaSDKDevice2DEnum::DE_Keyboard);

	// create colors to use in making frames
	int* colors = new int[keyboardMaxRow * keyboardMaxColumn];
	for (int i = 0; i < (keyboardMaxRow * keyboardMaxColumn); ++i)
	{
		colors[i] = 0;
	}
	animationName = BLANK_KEYBOARD;
	animationId = _gMethodOpenAnimation(animationName);
	// add a bunch of blank frames
	for (int frameNumber = 0; frameNumber < 100; ++frameNumber)
	{
		_gMethodAddFrame(animationId, 0.5f, &colors[0], keyboardMaxRow * keyboardMaxColumn);
	}

	fprintf(stdout, "Playing animation %s.\r\n", animationName);
	_gMethodCopyNonZeroAllKeysAllFramesName(RANDOM_KEYBOARD, BLANK_KEYBOARD);
	_gMethodPlayAnimationName(animationName, false);
	Sleep(10000);
	_gMethodCloseAnimationName(animationName);
}

void DebugUnitTestsLoadedAnimations()
{
	const char* BLANK_KEYBOARD = "Blank_Keyboard.chroma";
	const char* BLANK_COMPOSITE = "Blank";
	const char* RANDOM_KEYBOARD = "Random_Keyboard.chroma";
	const char* RANDOM_COMPOSITE = "Random";
	const char* animationName = "";
	int animationId = -1;

	_gMethodPlayComposite(BLANK_COMPOSITE, false);
	_gMethodPlayComposite(RANDOM_COMPOSITE, true);
	Sleep(500);
	int count = _gMethodGetAnimationCount();
	fprintf(stdout, "[%d] animation(s) are open.\r\n", count);
	for (int i = 0; i < count; ++i)
	{
		animationId = _gMethodGetAnimationId(i);
		if (animationId < 0)
		{
			continue;
		}
		animationName = _gMethodGetAnimationName(animationId);
		fprintf(stdout, "Animation is open: [%d] %s\r\n", animationId, animationName);
	}
	fprintf(stdout, "Closing open animations...\r\n");
	_gMethodCloseAll();
	count = _gMethodGetAnimationCount();
	fprintf(stdout, "[%d] animation(s) are open.\r\n", count);
	fprintf(stdout, "All animations are closed.\r\n");

	animationName = RANDOM_KEYBOARD;
	fprintf(stdout, "Playing animation %s.\r\n", animationName);
	_gMethodPlayAnimationName(animationName, false);
	while (_gMethodIsPlayingName(animationName))
	{
		Sleep(0);
	}
	fprintf(stdout, "Animation complete %s.\r\n", animationName);
}

void DebugUnitTestsSetKeys()
{
	int wasdKeys[4] =
	{
		(int)Keyboard::RZKEY::RZKEY_W,
		(int)Keyboard::RZKEY::RZKEY_A,
		(int)Keyboard::RZKEY::RZKEY_S,
		(int)Keyboard::RZKEY::RZKEY_D,
	};

	const char* BLANK_KEYBOARD = "Blank_Keyboard.chroma";
	const char* BLANK_COMPOSITE = "Blank";
	const char* RANDOM_KEYBOARD = "Random_Keyboard.chroma";
	const char* RANDOM_COMPOSITE = "Random";
	const char* animationName = "";
	const char* compositeName = "";
	const int COLOR_RED = 0xFF;
	int animationId = -1;

	compositeName = RANDOM_COMPOSITE;
	_gMethodLoadComposite(compositeName);
	_gMethodPlayComposite(compositeName, false);
	Sleep(1000);
	animationName = RANDOM_KEYBOARD;
	int frameCount = _gMethodGetFrameCountName(animationName);
	for (int i = 0; i < frameCount; ++i)
	{
		_gMethodSetKeysColorName(animationName, i, wasdKeys, size(wasdKeys), COLOR_RED);
	}
	_gMethodUnloadComposite(compositeName);
	_gMethodPlayComposite(compositeName, false);
	Sleep(3000);
	_gMethodCloseComposite(compositeName);
	Sleep(1000);

	animationName = BLANK_KEYBOARD;
	frameCount = _gMethodGetFrameCountName(animationName);

	_gMethodPlayAnimationName(animationName, false);
	Sleep(1000);

	for (int i = 0; i < frameCount; ++i)
	{
		_gMethodSetKeysColorName(animationName, i, wasdKeys, size(wasdKeys), COLOR_RED);
	}
	_gMethodUnloadAnimationName(animationName);
	_gMethodPlayAnimationName(animationName, false);
	Sleep(3000);

	_gMethodCloseAnimationName(animationName);
	Sleep(100);

	for (int i = 0; i < frameCount; ++i)
	{
		_gMethodSetKeyColorName(animationName, i, (int)Keyboard::RZKEY::RZKEY_W, COLOR_RED);
	}
	_gMethodPlayAnimationName(animationName, false);
	Sleep(3000);

	_gMethodCloseAnimationName(animationName);
	Sleep(100);
}

void DebugUnitTestsClear()
{
	const char* BLANK_KEYBOARD = "Blank_Keyboard.chroma";
	const char* BLANK_COMPOSITE = "Blank";
	const char* RANDOM_KEYBOARD = "Random_Keyboard.chroma";
	const char* RANDOM_COMPOSITE = "Random";
	const char* animationName = "";
	const char* compositeName = "";
	int animationId = -1;

	fprintf(stdout, "Playing animation.\r\n");
	_gMethodPlayAnimationName(RANDOM_KEYBOARD, false);
	Sleep(100);

	fprintf(stdout, "Clearing animations.\r\n");
	_gMethodClearAll();

	Sleep(1000);

	fprintf(stdout, "Playing animations.\r\n");
	_gMethodPlayComposite("Random", false);
	Sleep(100);

	for (int wait = 0; wait < 3; ++wait)
	{
		int count = _gMethodGetAnimationCount();
		fprintf(stdout, "[%d] animation(s) are open.\r\n", count);
		for (int i = 0; i < count; ++i)
		{
			animationId = _gMethodGetAnimationId(i);
			if (animationId < 0)
			{
				continue;
			}
			animationName = _gMethodGetAnimationName(animationId);
			fprintf(stdout, "Animation is open: [%d] %s\r\n", animationId, animationName);
		}
		Sleep(500);
	}

	for (int wait = 0; wait < 10; ++wait)
	{
		int count = _gMethodGetPlayingAnimationCount();
		fprintf(stdout, "[%d] animation(s) are playing.\r\n", count);
		for (int i = 0; i < count; ++i)
		{
			animationId = _gMethodGetPlayingAnimationId(i);
			if (animationId < 0)
			{
				continue;
			}

			animationName = _gMethodGetAnimationName(animationId);
			fprintf(stdout, "Animation is playing: [%d] %s\r\n", animationId, animationName);
		}
		if (_gMethodGetPlayingAnimationCount() == 0)
		{
			fprintf(stdout, "No animations are playing.\r\n");
		}
		Sleep(500);
	}

	_gMethodClearAll();

	Sleep(3000);
}

void DebugUnitTestsWait()
{
	const char* BLANK_KEYBOARD = "Blank_Keyboard.chroma";
	const char* BLANK_COMPOSITE = "Blank";
	const char* RANDOM_KEYBOARD = "Random_Keyboard.chroma";
	const char* RANDOM_COMPOSITE = "Random";
	const char* animationName = "";
	int animationId = -1;

	fprintf(stdout, "Playing animation.\r\n");
	_gMethodPlayAnimationName(RANDOM_KEYBOARD, false);
	Sleep(100);

	fprintf(stdout, "Clearing animations.\r\n");
	_gMethodClearAll();

	Sleep(1000);

	fprintf(stdout, "Playing animations.\r\n");
	_gMethodPlayComposite("Random", false);
	Sleep(100);

	for (int wait = 0; wait < 3; ++wait)
	{
		int count = _gMethodGetAnimationCount();
		fprintf(stdout, "[%d] animation(s) are open.\r\n", count);
		for (int i = 0; i < count; ++i)
		{
			animationId = _gMethodGetAnimationId(i);
			if (animationId < 0)
			{
				continue;
			}
			animationName = _gMethodGetAnimationName(animationId);
			fprintf(stdout, "Animation is open: [%d] %s\r\n", animationId, animationName);
		}
		Sleep(500);
	}

	for (int wait = 0; wait < 10; ++wait)
	{
		int count = _gMethodGetPlayingAnimationCount();
		fprintf(stdout, "[%d] animation(s) are playing.\r\n", count);
		for (int i = 0; i < count; ++i)
		{
			animationId = _gMethodGetPlayingAnimationId(i);
			if (animationId < 0)
			{
				continue;
			}

			animationName = _gMethodGetAnimationName(animationId);
			fprintf(stdout, "Animation is playing: [%d] %s\r\n", animationId, animationName);
		}
		if (_gMethodGetPlayingAnimationCount() == 0)
		{
			fprintf(stdout, "No animations are playing.\r\n");
		}
		Sleep(500);
	}

	_gMethodClearAll();

	Sleep(3000);

	fprintf(stdout, "Playing animation.\r\n");
	_gMethodPlayAnimationName(RANDOM_KEYBOARD, false);
	Sleep(100);
}

void DebugUnitTestsCopy()
{
	const char* RANDOM_KEYBOARD = "Random_Keyboard.chroma";

	int frameCount = _gMethodGetFrameCountName(RANDOM_KEYBOARD);
	for (int index = 0; index < frameCount; ++index)
	{
		_gMethodCopyKeyColorName("Fire_Keyboard.chroma", RANDOM_KEYBOARD, index, (int)Keyboard::RZKEY::RZKEY_W);
		_gMethodCopyKeyColorName("Fire_Keyboard.chroma", RANDOM_KEYBOARD, index, (int)Keyboard::RZKEY::RZKEY_A);
		_gMethodCopyKeyColorName("Fire_Keyboard.chroma", RANDOM_KEYBOARD, index, (int)Keyboard::RZKEY::RZKEY_S);
		_gMethodCopyKeyColorName("Fire_Keyboard.chroma", RANDOM_KEYBOARD, index, (int)Keyboard::RZKEY::RZKEY_D);
	}
	_gMethodPlayAnimationName(RANDOM_KEYBOARD, true);
	Sleep(3000);

	_gMethodCloseAnimationName(RANDOM_KEYBOARD);
}

void DebugUnitTestsMisc()
{
	const char* RANDOM_KEYBOARD = "Random_Keyboard.chroma";

	fprintf(stdout, "Call: PlayComposite: Random\r\n");
	_gMethodPlayComposite("Random", true);
	IsPlaying("Random");
	Sleep(3000);

	fprintf(stdout, "Call: StopComposite\r\n");
	_gMethodStopComposite("Random");
	IsPlaying("Random");
	Sleep(3000);

	fprintf(stdout, "Call: PlayComposite: Blank\r\n");
	_gMethodPlayComposite("Blank", false);
	IsPlaying("Random"); //random should show false, type should be playing blank
	Sleep(3000);

	fprintf(stdout, "Call: PlayAnimationName\r\n");
	_gMethodPlayAnimationName(RANDOM_KEYBOARD, true);
	Sleep(3000);

	fprintf(stdout, "Call: StopAnimationName\r\n");
	_gMethodStopAnimationName(RANDOM_KEYBOARD);
	Sleep(1000);

	fprintf(stdout, "Call: PlayAnimationName\r\n");
	_gMethodPlayAnimationName(RANDOM_KEYBOARD, true);
	Sleep(3000);

	fprintf(stdout, "Call: StopAnimationType\r\n");
	_gMethodStopAnimationType((int)EChromaSDKDeviceTypeEnum::DE_2D, (int)EChromaSDKDevice2DEnum::DE_Keyboard);
}

void DebugUnitTestsOffset()
{
	fprintf(stdout, "Start of offset unit test.\r\n");
	
	const char* RANDOM_KEYBOARD = "Random_Keyboard.chroma";

	const char* animationName = RANDOM_KEYBOARD;
	_gMethodCloseAnimationName(animationName);

	int animationId = _gMethodOpenAnimation(animationName);

	int frameCount = _gMethodGetFrameCountName(animationName);

	fprintf(stdout, "Set all frames white with FillColor.\r\n");
	_gMethodFillColorAllFramesName(animationName, 255, 255, 255);

	fprintf(stdout, "Fade out black with MultiplyIntensity.\r\n");
	for (int index = 0; index < frameCount; ++index)
	{
		float ratio = (index + 1) / (float)frameCount;
		float intensity = 1.0f - ratio;
		_gMethodMultiplyIntensityName(animationName, index, intensity);
	}
	_gMethodUnloadAnimationName(animationName); //show changes
	_gMethodPlayAnimationName(animationName, false);
	while (_gMethodIsPlayingName(animationName))
	{
		Sleep(0);
	}

	fprintf(stdout, "Set all frames black with FillColor.\r\n");
	_gMethodUnloadAnimationName(animationName);
	_gMethodFillColorAllFramesName(animationName, 0, 0, 0);

	fprintf(stdout, "Fade in red with FillColor.\r\n");
	for (int index = 0; index < frameCount; ++index)
	{
		int ratio = (255 * index + 1) / frameCount;
		_gMethodFillColorName(animationName, index, ratio, 0, 0);
	}
	_gMethodUnloadAnimationName(animationName); //show changes
	_gMethodPlayAnimationName(animationName, false);
	while (_gMethodIsPlayingName(animationName))
	{
		Sleep(0);
	}

	fprintf(stdout, "Set all frames red with FillColor.\r\n");
	_gMethodFillColorAllFramesName(animationName, 255, 0, 0);

	fprintf(stdout, "Fade in green with OffsetColors.\r\n");
	for (int index = 0; index < frameCount; ++index)
	{
		const int greenOffset = 16;
		_gMethodOffsetColorsName(animationName, index, 0, index * greenOffset, 0);
	}
	_gMethodUnloadAnimationName(animationName); //show changes
	_gMethodPlayAnimationName(animationName, false);
	while (_gMethodIsPlayingName(animationName))
	{
		Sleep(0);
	}

	fprintf(stdout, "Set all frames yellow with FillColor.\r\n");
	_gMethodFillColorAllFramesName(animationName, 255, 255, 0);

	fprintf(stdout, "Fade out red with OffsetColors.\r\n");
	for (int index = 0; index < frameCount; ++index)
	{
		const int redOffset = -16;
		_gMethodOffsetColorsName(animationName, index, index * redOffset, 0, 0);
	}
	_gMethodUnloadAnimationName(animationName); //show changes
	_gMethodPlayAnimationName(animationName, false);
	while (_gMethodIsPlayingName(animationName))
	{
		Sleep(0);
	}

	fprintf(stdout, "Set all frames green with FillColor.\r\n");
	_gMethodFillColorAllFramesName(animationName, 0, 255, 0);

	fprintf(stdout, "Fade in white with OffsetColors.\r\n");
	for (int index = 0; index < frameCount; ++index)
	{
		const int redOffset = 16;
		const int blueOffset = 16;
		_gMethodOffsetColorsName(animationName, index, index * redOffset, 0, index * blueOffset);
	}
	_gMethodUnloadAnimationName(animationName); //show changes
	_gMethodPlayAnimationName(animationName, false);
	while (_gMethodIsPlayingName(animationName))
	{
		Sleep(0);
	}

	fprintf(stdout, "End of offset unit test.\r\n");
}

void DebugUnitTestsNonZero()
{
	fprintf(stdout, "Start of nonzero unit test.\r\n");

	const int COLOR_WHITE = 0xFFFFFF;

	int wasdKeys[4] =
	{
		(int)Keyboard::RZKEY::RZKEY_W,
		(int)Keyboard::RZKEY::RZKEY_A,
		(int)Keyboard::RZKEY::RZKEY_S,
		(int)Keyboard::RZKEY::RZKEY_D,
	};

	const char* SPRITE_KEYBOARD = "Sprite_Keyboard.chroma";
	const char* WAVE_KEYBOARD = "Rows_Keyboard.chroma";

	const char* animationName = WAVE_KEYBOARD;
	int animationId = _gMethodOpenAnimation(animationName);
	
	// Reload from disk
	_gMethodCloseAnimationName(animationName);

	int frameCount = _gMethodGetFrameCountName(animationName);

	fprintf(stdout, "Fade out red.\r\n");
	for (int i = 0; i < frameCount; ++i)
	{
		float ratio = (i + 1) / (float)frameCount;
		_gMethodOffsetNonZeroColorsName(animationName, i, -255 * ratio, 0, 0);
	}
	_gMethodUnloadAnimationName(animationName); //show changes
	_gMethodPlayAnimationName(animationName, false);
	while (_gMethodIsPlayingName(animationName))
	{
		Sleep(0);
	}
	fprintf(stdout, "Red should be gone.\r\n");
	Sleep(3000);

	fprintf(stdout, "Fade out green.\r\n");
	for (int i = 0; i < frameCount; ++i)
	{
		float ratio = (i + 1) / (float)frameCount;
		_gMethodOffsetNonZeroColorsName(animationName, i, -255, -255 * ratio, 0);
	}
	_gMethodUnloadAnimationName(animationName); //show changes
	_gMethodPlayAnimationName(animationName, false);
	while (_gMethodIsPlayingName(animationName))
	{
		Sleep(0);
	}
	fprintf(stdout, "Green should be gone.\r\n");
	Sleep(3000);

	fprintf(stdout, "Fade out blue.\r\n");
	for (int i = 0; i < frameCount; ++i)
	{
		float ratio = (i + 1) / (float)frameCount;
		_gMethodOffsetNonZeroColorsName(animationName, i, -255, -255, -255 * ratio);
	}
	_gMethodUnloadAnimationName(animationName); //show changes
	_gMethodPlayAnimationName(animationName, false);
	while (_gMethodIsPlayingName(animationName))
	{
		Sleep(0);
	}
	fprintf(stdout, "Blue should be gone.\r\n");
	Sleep(3000);

	fprintf(stdout, "Non zero keys should fade in to white.\r\n");
	for (int i = 0; i < frameCount; ++i)
	{
		float ratio = (i + 1) / (float)frameCount;
		_gMethodFillNonZeroColorName(animationName, i, ratio * 255, ratio * 255, ratio * 255);
	}
	_gMethodUnloadAnimationName(animationName); //show changes
	_gMethodPlayAnimationName(animationName, false);
	while (_gMethodIsPlayingName(animationName))
	{
		Sleep(0);
	}

	// Reload from disk
	_gMethodCloseAnimationName(animationName);

	animationName = SPRITE_KEYBOARD;
	frameCount = _gMethodGetFrameCountName(animationName);

	// Reload from disk
	_gMethodCloseAnimationName(animationName);

	fprintf(stdout, "WASD keys should be white every other frame.\r\n");
	for (int i = 0; i < frameCount; ++i)
	{
		_gMethodSetKeyNonZeroColorName(animationName, i, (int)Keyboard::RZKEY::RZKEY_W, COLOR_WHITE);
		_gMethodSetKeyNonZeroColorName(animationName, i, (int)Keyboard::RZKEY::RZKEY_A, COLOR_WHITE);
		_gMethodSetKeyNonZeroColorName(animationName, i, (int)Keyboard::RZKEY::RZKEY_S, COLOR_WHITE);
		_gMethodSetKeyNonZeroColorName(animationName, i, (int)Keyboard::RZKEY::RZKEY_D, COLOR_WHITE);
	}
	_gMethodUnloadAnimationName(animationName); //show changes
	_gMethodPlayAnimationName(animationName, false);
	while (_gMethodIsPlayingName(animationName))
	{
		Sleep(0);
	}

	// Reload from disk
	_gMethodCloseAnimationName(animationName);

	fprintf(stdout, "WASD keys should be white every other frame.\r\n");
	for (int i = 0; i < frameCount; ++i)
	{
		_gMethodSetKeysNonZeroColorName(animationName, i, wasdKeys, size(wasdKeys), COLOR_WHITE);
	}
	_gMethodUnloadAnimationName(animationName); //show changes
	_gMethodPlayAnimationName(animationName, false);
	while (_gMethodIsPlayingName(animationName))
	{
		Sleep(0);
	}

	fprintf(stdout, "End of nonzero unit test.\r\n");
}

void DebugUnitTestsHDKIndividualLEDs()
{
	int size = MAX_ROW * MAX_COLUMN;
	int index = 0;
	int* colors = new int[size];
	int alternateStrip1[] =
	{
		0xFF0000,
		0x00FF00,
		0x0000FF,
	};
	int alternateStrip2[] =
	{
		0xFF00FF,
		0xFFFF00,
		0x00FFFF,
	};
	int alternateStrip3[] =
	{
		0x080000,
		0x400000,
		0x7F0000,
	};
	int alternateStrip4[] =
	{
		0x000800,
		0x004000,
		0x007F00,
	};
	const int alternateSize = 3;
	for (int i = 0; i < MAX_ROW; i++)
	{
		for (int j = 0; j < MAX_COLUMN; ++j)
		{
			COLORREF color = 0;
			switch (i)
			{
			case 0:
				color = alternateStrip1[j % alternateSize];
				break;
			case 1:
				color = alternateStrip2[j % alternateSize];
				break;
			case 2:
				color = alternateStrip3[j % alternateSize];
				break;
			case 3:
				color = alternateStrip4[j % alternateSize];
				break;
			default:
				color = 0; //not used
				break;
			}
			colors[index] = color;
			++index;
		}
	}

	fprintf(stdout, "Create random HDK LED colors effect.\r\n");

	FChromaSDKGuid effectId = FChromaSDKGuid();
	_gMethodCreateEffect(CHROMABOX, EFFECT_TYPE::CHROMA_CUSTOM, colors, size, &effectId);

	fprintf(stdout, "Set HDK Effect.\r\n");

	_gMethodSetEffect(effectId);

	Sleep(3000);

	fprintf(stdout, "Delete HDK Effect.\r\n");

	_gMethodDeleteEffect(effectId);

	Sleep(1000);

	delete colors;
}

void DebugUnitTestsHDKIndividualLEDsGradient()
{
	int size = MAX_ROW * MAX_COLUMN;
	int index = 0;
	int* colors = new int[size];
	const int alternateSize = 3;
	const int HDK_MAX_LEDS = 16;
	for (int i = 0; i < MAX_ROW; i++)
	{
		for (int j = 0; j < MAX_COLUMN; ++j)
		{
			int red = 0xFF;
			int green = min(255, j / (float)HDK_MAX_LEDS * 255);
			COLORREF color = RGB(red, green, 0);
			colors[index] = color;
			++index;
		}
	}

	fprintf(stdout, "Create HDK gradient.\r\n");

	FChromaSDKGuid effectId = FChromaSDKGuid();
	_gMethodCreateEffect(CHROMABOX, EFFECT_TYPE::CHROMA_CUSTOM, colors, size, &effectId);

	fprintf(stdout, "Set HDK Effect.\r\n");

	_gMethodSetEffect(effectId);

	Sleep(3000);

	fprintf(stdout, "Delete HDK Effect.\r\n");

	_gMethodDeleteEffect(effectId);

	Sleep(1000);

	delete colors;
}

void DebugUnitTestsCreateAnimation()
{
	const char* animationName = "New_ChromaLink.chroma";
	int animationId = _gMethodCreateAnimation(animationName, (int)EChromaSDKDeviceTypeEnum::DE_1D, (int)EChromaSDKDevice1DEnum::DE_ChromaLink);
	if (animationId < 0)
	{
		fprintf(stderr, "Failed to create animation! %s\r\n", animationName);
	}
}

void DebugUnitTestsKeyboardCustom()
{
	fprintf(stdout, "Clear all.\r\n");
	_gMethodClearAll();
	Sleep(3000);

	fprintf(stdout, "Show custom keyboard keys Z N M LALT.\r\n");
	int animationId = _gMethodCreateAnimationInMemory((int)EChromaSDKDeviceTypeEnum::DE_2D, (int)EChromaSDKDevice2DEnum::DE_Keyboard);
	_gMethodKeyboardUseChromaCustom(animationId, true);
	_gMethodSetKeyColor(animationId, 0, (int)Keyboard::RZKEY::RZKEY_Z, 0x01FF0000);
	_gMethodSetKeyColor(animationId, 0, (int)Keyboard::RZKEY::RZKEY_N, 0x0100FF00);
	_gMethodSetKeyColor(animationId, 0, (int)Keyboard::RZKEY::RZKEY_M, 0x010000FF);
	_gMethodSetKeyColor(animationId, 0, (int)Keyboard::RZKEY::RZKEY_LALT, 0x01FFFFFF);
	fprintf(stdout, "Play animation with custom keys.\r\n");
	_gMethodPlayAnimation(animationId);
	Sleep(2000);
	fprintf(stdout, "Preview frame with custom keys.\r\n");
	_gMethodPreviewFrame(animationId, 0);
	Sleep(2000);
	_gMethodCloseAnimation(animationId);

	fprintf(stdout, "Clear all.\r\n");
	_gMethodClearAll();
	Sleep(3000);

	fprintf(stdout, "Show custom keyboard keys LCTRL X C V B.\r\n");
	animationId = _gMethodCreateAnimationInMemory((int)EChromaSDKDeviceTypeEnum::DE_2D, (int)EChromaSDKDevice2DEnum::DE_Keyboard);
	_gMethodKeyboardUseChromaCustom(animationId, true);
	_gMethodSetKeyColor(animationId, 0, (int)Keyboard::RZKEY::RZKEY_LCTRL, 0x01FF0000);
	_gMethodSetKeyColor(animationId, 0, (int)Keyboard::RZKEY::RZKEY_X, 0x0100FF00);
	_gMethodSetKeyColor(animationId, 0, (int)Keyboard::RZKEY::RZKEY_C, 0x010000FF);
	_gMethodSetKeyColor(animationId, 0, (int)Keyboard::RZKEY::RZKEY_V, 0x01FFFFFF);
	_gMethodSetKeyColor(animationId, 0, (int)Keyboard::RZKEY::RZKEY_B, 0x01FFFF00);
	fprintf(stdout, "Play animation with custom keys.\r\n");
	_gMethodPlayAnimation(animationId);
	Sleep(2000);
	fprintf(stdout, "Preview frame with custom keys.\r\n");
	_gMethodPreviewFrame(animationId, 0);
	Sleep(2000);
	_gMethodCloseAnimation(animationId);

	fprintf(stdout, "Clear all.\r\n");
	_gMethodClearAll();
	Sleep(3000);
}

void DebugUnitTests()
{
	_gMethodInit();

	//DebugUnitTestsKeyboardCustom();
	DebugUnitTestsPlayComposite();
	//DebugUnitTestsHDKIndividualLEDsGradient();
	//DebugUnitTestsHDKIndividualLEDs();
	//DebugUnitTestsOffset();
	//DebugUnitTestsNonZero();
	//DebugUnitTestsCreateAnimation();

	while (true)
	{
		Sleep(100);
	}
}
