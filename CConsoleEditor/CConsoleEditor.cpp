// CConsoleEditor.cpp : Defines the entry point for the console application.
//

#define CHROMA_EDITOR_DLL _T("CChromaEditorLibrary.dll")

#include "stdafx.h"
#include <chrono>
#include <thread>
#include <Windows.h>
#include "..\CChromaEditorLibrary\ChromaSDKPluginTypes.h"

typedef void(*PLUGIN_INIT)();
typedef double(*PLUGIN_IS_INITIALIZED)();
typedef void(*PLUGIN_UNINIT)();
typedef double(*PLUGIN_IS_DIALOG_OPEN)();
typedef double(*PLUGIN_OPEN_EDITOR_DIALOG)(const char* path);
typedef double(*PLUGIN_OPEN_EDITOR_DIALOG_AND_PLAY)(const char* path);
typedef double(*PLUGIN_OPEN_ANIMATION)(const char* path);
typedef double(*PLUGIN_CLOSE_ANIMATION)(double animationId);
typedef void(*PLUGIN_CLOSE_ANIMATION_NAME)(const char* path);
typedef void(*PLUGIN_CLOSE_COMPOSITE)(const char* name);
typedef void(*PLUGIN_CLOSE_ALL)();
typedef double(*PLUGIN_PLAY_ANIMATION)(double animationId);
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
typedef void(*PLUGIN_SET_KEY_COLOR_NAME)(const char* path, int frameId, int rzkey, int color);
typedef void(*PLUGIN_SET_KEYS_COLOR_NAME)(const char* path, int frameId, const int* rzkeys, int keyCount, int color);
typedef void(*PLUGIN_COPY_NONZERO_ALL_KEYS_ALL_FRAMES_NAME)(const char* sourceAnimation, const char* targetAnimation);
typedef void(*PLUGIN_COPY_KEY_COLOR_NAME)(const char* sourceAnimation, const char* targetAnimation, int frameId, int rzkey);
typedef const char*(*PLUGIN_GET_ANIMATION_NAME)(int animationId);
typedef void(*PLUGIN_CLEAR_ANIMATION_TYPE)(int deviceType, int device);
typedef void(*PLUGIN_CLEAR_ALL)();
typedef int(*PLUGIN_GET_ANIMATION_COUNT)();
typedef int(*PLUGIN_GET_ANIMATION_ID)(int index);
typedef int(*PLUGIN_GET_PLAYING_ANIMATION_COUNT)();
typedef int(*PLUGIN_GET_PLAYING_ANIMATION_ID)(int index);

#if RUN_UNIT_TESTS
void DebugUnitTests();
#endif

using namespace std;
using namespace std::chrono;
using namespace ChromaSDK;

PLUGIN_IS_INITIALIZED _gMethodIsInitialized = nullptr;
PLUGIN_IS_DIALOG_OPEN _gMethodIsDialogOpen = nullptr;
PLUGIN_OPEN_EDITOR_DIALOG _gMethodOpenDialog = nullptr;
PLUGIN_OPEN_EDITOR_DIALOG_AND_PLAY _gMethodOpenDialogAndPlay = nullptr;
PLUGIN_OPEN_ANIMATION _gMethodOpenAnimation = nullptr;
PLUGIN_CLOSE_ANIMATION _gMethodCloseAnimation = nullptr;
PLUGIN_PLAY_ANIMATION _gMethodPlayAnimation = nullptr;
PLUGIN_PLAY_ANIMATION_NAME _gMethodPlayAnimationName = nullptr;
PLUGIN_STOP_ANIMATION_NAME _gMethodStopAnimationName = nullptr;
PLUGIN_STOP_ANIMATION_TYPE _gMethodStopAnimationType = nullptr;
PLUGIN_IS_PLAYING_NAME _gMethodIsPlayingName = nullptr;
PLUGIN_IS_PLAYING_TYPE _gMethodIsPlayingType = nullptr;
PLUGIN_LOAD_COMPOSITE _gMethodLoadComposite = nullptr;
PLUGIN_UNLOAD_COMPOSITE _gMethodUnloadComposite = nullptr;
PLUGIN_PLAY_COMPOSITE _gMethodPlayComposite = nullptr;
PLUGIN_STOP_COMPOSITE _gMethodStopComposite = nullptr;
PLUGIN_CLOSE_COMPOSITE _gMethodCloseComposite = nullptr;
PLUGIN_CLOSE_ALL _gMethodCloseAll = nullptr;
PLUGIN_INIT _gMethodInit = nullptr;
PLUGIN_UNINIT _gMethodUninit = nullptr;
PLUGIN_CLOSE_ANIMATION_NAME _gMethodCloseAnimationName = nullptr;
PLUGIN_LOAD_ANIMATION_NAME _gMethodLoadAnimationName = nullptr;
PLUGIN_UNLOAD_ANIMATION_NAME _gMethodUnloadAnimationName = nullptr;
PLUGIN_GET_MAX_ROW _gMethodGetMaxRow = nullptr;
PLUGIN_GET_MAX_COLUMN _gMethodGetMaxColumn = nullptr;
PLUGIN_ADD_FRAME _gMethodAddFrame = nullptr;
PLUGIN_GET_FRAME _gMethodGetFrame = nullptr;
PLUGIN_GET_FRAME_COUNT_NAME _gMethodGetFrameCountName = nullptr;
PLUGIN_SET_KEY_COLOR_NAME _gMethodSetKeyColorName = nullptr;
PLUGIN_SET_KEYS_COLOR_NAME _gMethodSetKeysColorName = nullptr;
PLUGIN_COPY_NONZERO_ALL_KEYS_ALL_FRAMES_NAME _gMethodCopyNonZeroAllKeysAllFramesName = nullptr;
PLUGIN_COPY_KEY_COLOR_NAME _gMethodCopyKeyColorName = nullptr;
PLUGIN_GET_ANIMATION_NAME _gMethodGetAnimationName = nullptr;
PLUGIN_STOP_ALL _gMethodStopAll = nullptr;
PLUGIN_CLEAR_ANIMATION_TYPE _gMethodClearAnimationType = nullptr;
PLUGIN_CLEAR_ALL _gMethodClearAll = nullptr;
PLUGIN_GET_ANIMATION_COUNT _gMethodGetAnimationCount = nullptr;
PLUGIN_GET_ANIMATION_ID _gMethodGetAnimationId = nullptr;
PLUGIN_GET_PLAYING_ANIMATION_COUNT _gMethodGetPlayingAnimationCount = nullptr;
PLUGIN_GET_PLAYING_ANIMATION_ID _gMethodGetPlayingAnimationId = nullptr;

int Init()
{
	HMODULE library = LoadLibrary(CHROMA_EDITOR_DLL);
	if (library == NULL)
	{
		fprintf(stderr, "Failed to load Chroma Editor Library!\r\n");
		return -1;
	}

	fprintf(stderr, "Loaded Chroma Editor DLL!\r\n");

	_gMethodIsInitialized = (PLUGIN_IS_DIALOG_OPEN)GetProcAddress(library, "PluginIsInitializedD");
	if (_gMethodIsInitialized == nullptr)
	{
		fprintf(stderr, "Failed to find method PluginIsInitialized!\r\n");
		return -1;
	}

	_gMethodIsDialogOpen = (PLUGIN_IS_DIALOG_OPEN)GetProcAddress(library, "PluginIsDialogOpenD");
	if (_gMethodIsDialogOpen == nullptr)
	{
		fprintf(stderr, "Failed to find method PluginIsDialogOpen!\r\n");
		return -1;
	}

	_gMethodOpenDialog = (PLUGIN_OPEN_EDITOR_DIALOG)GetProcAddress(library, "PluginOpenEditorDialogD");
	if (_gMethodOpenDialog == nullptr)
	{
		fprintf(stderr, "Failed to find method PluginOpenEditorDialog!\r\n");
		return -1;
	}

	_gMethodOpenDialogAndPlay = (PLUGIN_OPEN_EDITOR_DIALOG_AND_PLAY)GetProcAddress(library, "PluginOpenEditorDialogAndPlayD");
	if (_gMethodOpenDialogAndPlay == nullptr)
	{
		fprintf(stderr, "Failed to find method PluginOpenEditorDialogAndPlay!\r\n");
		return -1;
	}

	_gMethodOpenAnimation = (PLUGIN_OPEN_ANIMATION)GetProcAddress(library, "PluginOpenAnimationD");
	if (_gMethodOpenAnimation == nullptr)
	{
		fprintf(stderr, "Failed to find method PluginOpenAnimation!\r\n");
		return -1;
	}

	_gMethodCloseAnimation = (PLUGIN_CLOSE_ANIMATION)GetProcAddress(library, "PluginCloseAnimationD");
	if (_gMethodCloseAnimation == nullptr)
	{
		fprintf(stderr, "Failed to find method PluginCloseAnimation!\r\n");
		return -1;
	}

	_gMethodPlayAnimation = (PLUGIN_PLAY_ANIMATION)GetProcAddress(library, "PluginPlayAnimationD");
	if (_gMethodPlayAnimation == nullptr)
	{
		fprintf(stderr, "Failed to find method PluginPlayAnimation!\r\n");
		return -1;
	}

	_gMethodPlayAnimationName = (PLUGIN_PLAY_ANIMATION_NAME)GetProcAddress(library, "PluginPlayAnimationName");
	if (_gMethodPlayAnimationName == nullptr)
	{
		fprintf(stderr, "Failed to find method PluginPlayAnimationName!\r\n");
		return -1;
	}

	_gMethodStopAnimationName = (PLUGIN_STOP_ANIMATION_NAME)GetProcAddress(library, "PluginStopAnimationName");
	if (_gMethodStopAnimationName == nullptr)
	{
		fprintf(stderr, "Failed to find method PluginStopAnimationName!\r\n");
		return -1;
	}

	_gMethodStopAnimationType = (PLUGIN_STOP_ANIMATION_TYPE)GetProcAddress(library, "PluginStopAnimationType");
	if (_gMethodStopAnimationType == nullptr)
	{
		fprintf(stderr, "Failed to find method PluginStopAnimationType!\r\n");
		return -1;
	}

	_gMethodIsPlayingName = (PLUGIN_IS_PLAYING_NAME)GetProcAddress(library, "PluginIsPlayingName");
	if (_gMethodIsPlayingName == nullptr)
	{
		fprintf(stderr, "Failed to find method PluginIsPlayingName!\r\n");
		return -1;
	}

	_gMethodIsPlayingType = (PLUGIN_IS_PLAYING_TYPE)GetProcAddress(library, "PluginIsPlayingType");
	if (_gMethodIsPlayingType == nullptr)
	{
		fprintf(stderr, "Failed to find method PluginIsPlayingType!\r\n");
		return -1;
	}

	_gMethodLoadComposite = (PLUGIN_LOAD_COMPOSITE)GetProcAddress(library, "PluginLoadComposite");
	if (_gMethodLoadComposite == nullptr)
	{
		fprintf(stderr, "Failed to find method PluginLoadComposite!\r\n");
		return -1;
	}

	_gMethodUnloadComposite = (PLUGIN_UNLOAD_COMPOSITE)GetProcAddress(library, "PluginUnloadComposite");
	if (_gMethodUnloadComposite == nullptr)
	{
		fprintf(stderr, "Failed to find method PluginUnloadComposite!\r\n");
		return -1;
	}

	_gMethodPlayComposite = (PLUGIN_PLAY_COMPOSITE)GetProcAddress(library, "PluginPlayComposite");
	if (_gMethodPlayComposite == nullptr)
	{
		fprintf(stderr, "Failed to find method PluginPlayComposite!\r\n");
		return -1;
	}

	_gMethodStopComposite = (PLUGIN_STOP_COMPOSITE)GetProcAddress(library, "PluginStopComposite");
	if (_gMethodStopComposite == nullptr)
	{
		fprintf(stderr, "Failed to find method PluginStopComposite!\r\n");
		return -1;
	}

	_gMethodCloseComposite = (PLUGIN_CLOSE_COMPOSITE)GetProcAddress(library, "PluginCloseComposite");
	if (_gMethodCloseComposite == nullptr)
	{
		fprintf(stderr, "Failed to find method PluginCloseComposite!\r\n");
		return -1;
	}

	_gMethodCloseAll = (PLUGIN_CLOSE_ALL)GetProcAddress(library, "PluginCloseAll");
	if (_gMethodCloseAll == nullptr)
	{
		fprintf(stderr, "Failed to find method PluginCloseAll!\r\n");
		return -1;
	}

	_gMethodInit = (PLUGIN_UNINIT)GetProcAddress(library, "PluginInit");
	if (_gMethodInit == nullptr)
	{
		fprintf(stderr, "Failed to find method PluginInit!\r\n");
		return -1;
	}

	_gMethodUninit = (PLUGIN_UNINIT)GetProcAddress(library, "PluginUninit");
	if (_gMethodUninit == nullptr)
	{
		fprintf(stderr, "Failed to find method PluginUninit!\r\n");
		return -1;
	}

	_gMethodCloseAnimationName = (PLUGIN_CLOSE_ANIMATION_NAME)GetProcAddress(library, "PluginCloseAnimationName");
	if (_gMethodCloseAnimationName == nullptr)
	{
		fprintf(stderr, "Failed to find method PluginCloseAnimationName!\r\n");
		return -1;
	}

	_gMethodLoadAnimationName = (PLUGIN_LOAD_ANIMATION_NAME)GetProcAddress(library, "PluginLoadAnimationName");
	if (_gMethodLoadAnimationName == nullptr)
	{
		fprintf(stderr, "Failed to find method PluginLoadAnimationName!\r\n");
		return -1;
	}

	_gMethodUnloadAnimationName = (PLUGIN_UNLOAD_ANIMATION_NAME)GetProcAddress(library, "PluginUnloadAnimationName");
	if (_gMethodUnloadAnimationName == nullptr)
	{
		fprintf(stderr, "Failed to find method PluginUnloadAnimationName!\r\n");
		return -1;
	}

	_gMethodGetMaxRow = (PLUGIN_GET_MAX_ROW)GetProcAddress(library, "PluginGetMaxRow");
	if (_gMethodGetMaxRow == nullptr)
	{
		fprintf(stderr, "Failed to find method PluginGetMaxRow!\r\n");
		return -1;
	}

	_gMethodGetMaxColumn = (PLUGIN_GET_MAX_COLUMN)GetProcAddress(library, "PluginGetMaxColumn");
	if (_gMethodGetMaxColumn == nullptr)
	{
		fprintf(stderr, "Failed to find method PluginGetMaxColumn!\r\n");
		return -1;
	}

	_gMethodAddFrame = (PLUGIN_ADD_FRAME)GetProcAddress(library, "PluginAddFrame");
	if (_gMethodAddFrame == nullptr)
	{
		fprintf(stderr, "Failed to find method PluginAddFrame!\r\n");
		return -1;
	}

	_gMethodGetFrame = (PLUGIN_GET_FRAME)GetProcAddress(library, "PluginGetFrame");
	if (_gMethodGetFrame == nullptr)
	{
		fprintf(stderr, "Failed to find method PluginGetFrame!\r\n");
		return -1;
	}

	_gMethodGetFrameCountName = (PLUGIN_GET_FRAME_COUNT_NAME)GetProcAddress(library, "PluginGetFrameCountName");
	if (_gMethodGetFrameCountName == nullptr)
	{
		fprintf(stderr, "Failed to find method PluginGetFrameCountName!\r\n");
		return -1;
	}

	_gMethodSetKeyColorName = (PLUGIN_SET_KEY_COLOR_NAME)GetProcAddress(library, "PluginSetKeyColorName");
	if (_gMethodSetKeyColorName == nullptr)
	{
		fprintf(stderr, "Failed to find method PluginSetKeyColorName!\r\n");
		return -1;
	}

	_gMethodSetKeysColorName = (PLUGIN_SET_KEYS_COLOR_NAME)GetProcAddress(library, "PluginSetKeysColorName");
	if (_gMethodSetKeysColorName == nullptr)
	{
		fprintf(stderr, "Failed to find method PluginSetKeysColorName!\r\n");
		return -1;
	}

	_gMethodCopyNonZeroAllKeysAllFramesName = (PLUGIN_COPY_NONZERO_ALL_KEYS_ALL_FRAMES_NAME)GetProcAddress(library, "PluginCopyNonZeroAllKeysAllFramesName");
	if (_gMethodCopyNonZeroAllKeysAllFramesName == nullptr)
	{
		fprintf(stderr, "Failed to find method PluginCopyNonZeroAllKeysAllFramesName!\r\n");
		return -1;
	}

	_gMethodCopyKeyColorName = (PLUGIN_COPY_KEY_COLOR_NAME)GetProcAddress(library, "PluginCopyKeyColorName");
	if (_gMethodCopyKeyColorName == nullptr)
	{
		fprintf(stderr, "Failed to find method PluginCopyKeyColorName!\r\n");
		return -1;
	}

	_gMethodGetAnimationName = (PLUGIN_GET_ANIMATION_NAME)GetProcAddress(library, "PluginGetAnimationName");
	if (_gMethodGetAnimationName == nullptr)
	{
		fprintf(stderr, "Failed to find method PluginGetAnimationName!\r\n");
		return -1;
	}

	_gMethodStopAll = (PLUGIN_STOP_ALL)GetProcAddress(library, "PluginStopAll");
	if (_gMethodStopAll == nullptr)
	{
		fprintf(stderr, "Failed to find method PluginStopAll!\r\n");
		return -1;
	}

	_gMethodClearAnimationType = (PLUGIN_CLEAR_ANIMATION_TYPE)GetProcAddress(library, "PluginClearAnimationType");
	if (_gMethodClearAnimationType == nullptr)
	{
		fprintf(stderr, "Failed to find method PluginClearAnimationType!\r\n");
		return -1;
	}

	_gMethodClearAll = (PLUGIN_CLEAR_ALL)GetProcAddress(library, "PluginClearAll");
	if (_gMethodClearAll == nullptr)
	{
		fprintf(stderr, "Failed to find method PluginClearAll!\r\n");
		return -1;
	}

	_gMethodGetAnimationCount = (PLUGIN_GET_ANIMATION_COUNT)GetProcAddress(library, "PluginGetAnimationCount");
	if (_gMethodGetAnimationCount == nullptr)
	{
		fprintf(stderr, "Failed to find method PluginGetAnimationCount!\r\n");
		return -1;
	}

	_gMethodGetAnimationId = (PLUGIN_GET_ANIMATION_ID)GetProcAddress(library, "PluginGetAnimationId");
	if (_gMethodGetAnimationId == nullptr)
	{
		fprintf(stderr, "Failed to find method PluginGetAnimationId!\r\n");
		return -1;
	}

	_gMethodGetPlayingAnimationCount = (PLUGIN_GET_PLAYING_ANIMATION_COUNT)GetProcAddress(library, "PluginGetPlayingAnimationCount");
	if (_gMethodGetPlayingAnimationCount == nullptr)
	{
		fprintf(stderr, "Failed to find method PluginGetPlayingAnimationCount!\r\n");
		return -1;
	}

	_gMethodGetPlayingAnimationId = (PLUGIN_GET_PLAYING_ANIMATION_ID)GetProcAddress(library, "PluginGetPlayingAnimationId");
	if (_gMethodGetPlayingAnimationId == nullptr)
	{
		fprintf(stderr, "Failed to find method PluginGetPlayingAnimationId!\r\n");
		return -1;
	}

	fprintf(stderr, "Found DLL methods!\r\n");
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
			_gMethodOpenDialogAndPlay(path);
		}
		else
		{
			_gMethodOpenDialogAndPlay("temp.chroma");
		}
	}
	else
	{
		_gMethodOpenDialogAndPlay(argv[1]);
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

void DebugUnitTests()
{
	if (false) // test editor
	{
		_gMethodOpenDialog("RandomKeyboardEffect.chroma");
		while (_gMethodIsDialogOpen())
		{
			Sleep(0);
		}
	}
	else if (false) // test api
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
	else
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

		frameCount = _gMethodGetFrameCountName(RANDOM_KEYBOARD);
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

		while (true)
		{
			Sleep(100);
		}
	}
}
