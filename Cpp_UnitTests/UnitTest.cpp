#include "ChromaAnimationAPI.h"
#include "UnitTests.h"
#include "ChromaLogger.h"

#include <chrono>
#include <string>
#include <thread>
#include <tchar.h>
#include <vector>


using namespace std;
using namespace std::chrono;
using namespace ChromaSDK;

const float MATH_PI = 3.14159f;


void UnitTests::IsPlaying(const wchar_t* name)
{
	ChromaLogger::wprintf(L"%s_ChromaLink IsPlayingName: %s\r\n", name, ChromaAnimationAPI::IsPlayingName(L"Random_Keyboard.chroma") ? L"true" : L"false");
	ChromaLogger::wprintf(L"%s_Headset IsPlayingName: %s\r\n", name, ChromaAnimationAPI::IsPlayingName(L"Random_Keyboard.chroma") ? L"true" : L"false");
	ChromaLogger::wprintf(L"%s_Keyboard IsPlayingName: %s\r\n", name, ChromaAnimationAPI::IsPlayingName(L"Random_Keyboard.chroma") ? L"true" : L"false");
	ChromaLogger::wprintf(L"%s_Keypad IsPlayingName: %s\r\n", name, ChromaAnimationAPI::IsPlayingName(L"Random_Keyboard.chroma") ? L"true" : L"false");
	ChromaLogger::wprintf(L"%s_Mouse IsPlayingName: %s\r\n", name, ChromaAnimationAPI::IsPlayingName(L"Random_Keyboard.chroma") ? L"true" : L"false");
	ChromaLogger::wprintf(L"%s_Mousepad IsPlayingName: %s\r\n", name, ChromaAnimationAPI::IsPlayingName(L"Random_Keyboard.chroma") ? L"true" : L"false");

	ChromaLogger::wprintf(L"ChromaLink IsPlayingType: %s\r\n", ChromaAnimationAPI::IsPlayingType((int)EChromaSDKDeviceTypeEnum::DE_1D, (int)EChromaSDKDevice1DEnum::DE_ChromaLink) ? L"true" : L"false");
	ChromaLogger::wprintf(L"Headset IsPlayingType: %s\r\n", ChromaAnimationAPI::IsPlayingType((int)EChromaSDKDeviceTypeEnum::DE_1D, (int)EChromaSDKDevice1DEnum::DE_Headset) ? L"true" : L"false");
	ChromaLogger::wprintf(L"Keyboard IsPlayingType: %s\r\n", ChromaAnimationAPI::IsPlayingType((int)EChromaSDKDeviceTypeEnum::DE_2D, (int)EChromaSDKDevice2DEnum::DE_Keyboard) ? L"true" : L"false");
	ChromaLogger::wprintf(L"Keypad IsPlayingType: %s\r\n", ChromaAnimationAPI::IsPlayingType((int)EChromaSDKDeviceTypeEnum::DE_2D, (int)EChromaSDKDevice2DEnum::DE_Keypad) ? L"true" : L"false");
	ChromaLogger::wprintf(L"Mouse IsPlayingType: %s\r\n", ChromaAnimationAPI::IsPlayingType((int)EChromaSDKDeviceTypeEnum::DE_2D, (int)EChromaSDKDevice2DEnum::DE_Mouse) ? L"true" : L"false");
	ChromaLogger::wprintf(L"Mousepad IsPlayingType: %s\r\n", ChromaAnimationAPI::IsPlayingType((int)EChromaSDKDeviceTypeEnum::DE_1D, (int)EChromaSDKDevice1DEnum::DE_Mousepad) ? L"true" : L"false");
}

void UnitTests::UnitTestsInit()
{
	RZRESULT result = ChromaAnimationAPI::Init();
	ChromaLogger::wprintf(L"Init result=%ld\r\n", result);

	Sleep(1000);
}

RZRESULT UnitTests::UnitTestsInitSDK()
{
	APPINFOTYPE appInfo = {};

	_tcscpy_s(appInfo.Title, 256, _T("Razer Chroma Editor"));
	_tcscpy_s(appInfo.Description, 1024, _T("Standalone Editor for Chroma"));
	_tcscpy_s(appInfo.Author.Name, 256, _T("Razer"));
	_tcscpy_s(appInfo.Author.Contact, 256, _T("https://developer.razer.com/chroma"));

	//appInfo.SupportedDevice = 
	//    0x01 | // Keyboards
	//    0x02 | // Mice
	//    0x04 | // Headset
	//    0x08 | // Mousepads
	//    0x10 | // Keypads
	//    0x20   // ChromaLink devices
	appInfo.SupportedDevice = (0x01 | 0x02 | 0x04 | 0x08 | 0x10 | 0x20);
	appInfo.Category = 1;

	RZRESULT result = ChromaAnimationAPI::InitSDK(&appInfo);
	if (result != RZRESULT_SUCCESS)
	{
		ChromaLogger::wprintf(L"UnitTests::UnitTestsInitSDK result=%ld\r\n", result);
	}

	Sleep(100);

	return result;
}

void UnitTests::UnitTestsUninit()
{
	ChromaAnimationAPI::StopAll();

	ChromaAnimationAPI::CloseAll();

	ChromaAnimationAPI::Uninit();

	Sleep(1000);

	ChromaLogger::wprintf(L"Unit Tests have completed!\r\n");

	exit(0);
}

void UnitTests::UnitTestsPlayComposite()
{
	while (true)
	{
		ChromaLogger::wprintf(L"Measure CPU usage.\r\n");
		const wchar_t* RANDOM_COMPOSITE = L"Animations/Random";
		ChromaAnimationAPI::PlayComposite(RANDOM_COMPOSITE, false);
		Sleep(3000);
	}
}

void UnitTests::UnitTestsOpenDialog()
{
	ChromaAnimationAPI::OpenEditorDialog(L"RandomKeyboardEffect.chroma");
	while (ChromaAnimationAPI::IsDialogOpen())
	{
		Sleep(0);
	}
}

void UnitTests::UnitTestsOpenClose()
{
	for (int i = 0; i < 25; ++i)
	{
		if (ChromaAnimationAPI::IsInitialized() == 0)
		{
			ChromaLogger::wprintf(L"Init...\r\n");
			ChromaAnimationAPI::Init();
		}

		ChromaLogger::wprintf(L"Playing effects...\r\n");
		int randomChromaLinkEffect = OpenAndPlay(L"Animations/Random_ChromaLink.chroma");
		int randomHeadsetEffect = OpenAndPlay(L"Animations/Random_Headset.chroma");
		int randomKeyboardEffect = OpenAndPlay(L"Animations/Random_Keyboard.chroma");
		int randomKeypadEffect = OpenAndPlay(L"Animations/Random_Keypad.chroma");
		int randomMouseEffect = OpenAndPlay(L"Animations/Random_Mouse.chroma");
		int randomMousepadEffect = OpenAndPlay(L"Animations/Random_Mousepad.chroma");
		this_thread::sleep_for(chrono::seconds(1));

		ChromaAnimationAPI::CloseAnimation(randomChromaLinkEffect);
		ChromaAnimationAPI::CloseAnimation(randomHeadsetEffect);
		ChromaAnimationAPI::CloseAnimation(randomKeyboardEffect);
		ChromaAnimationAPI::CloseAnimation(randomKeypadEffect);
		ChromaAnimationAPI::CloseAnimation(randomMouseEffect);
		ChromaAnimationAPI::CloseAnimation(randomMousepadEffect);

		ChromaLogger::wprintf(L"Simulate exit...\r\n");
		ChromaAnimationAPI::Uninit();
	}
}

void UnitTests::UnitTestsLayering()
{
	const wchar_t* BLANK_KEYBOARD = L"Animations/Blank_Keyboard.chroma";
	const wchar_t* RANDOM_KEYBOARD = L"Animations/Random_Keyboard.chroma";

	const wchar_t* animationName = L"";
	int animationId = -1;

	int keyboardMaxRow = ChromaAnimationAPI::GetMaxRow((int)EChromaSDKDevice2DEnum::DE_Keyboard);
	int keyboardMaxColumn = ChromaAnimationAPI::GetMaxColumn((int)EChromaSDKDevice2DEnum::DE_Keyboard);

	// create colors to use in making frames
	int* colors = new int[keyboardMaxRow * keyboardMaxColumn];
	for (int i = 0; i < (keyboardMaxRow * keyboardMaxColumn); ++i)
	{
		colors[i] = 0;
	}
	animationName = BLANK_KEYBOARD;
	animationId = ChromaAnimationAPI::OpenAnimation(animationName);
	// add a bunch of blank frames
	for (int frameNumber = 0; frameNumber < 100; ++frameNumber)
	{
		ChromaAnimationAPI::AddFrame(animationId, 0.5f, &colors[0], keyboardMaxRow * keyboardMaxColumn);
	}

	ChromaLogger::wprintf(L"Playing animation %s.\r\n", animationName);
	ChromaAnimationAPI::CopyNonZeroAllKeysAllFramesName(RANDOM_KEYBOARD, BLANK_KEYBOARD);
	ChromaAnimationAPI::PlayAnimationName(animationName, false);
	Sleep(10000);
	ChromaAnimationAPI::CloseAnimationName(animationName);
}

void UnitTests::UnitTestsLoadedAnimations()
{
	const wchar_t* BLANK_KEYBOARD = L"Animations/Blank_Keyboard.chroma";
	const wchar_t* BLANK_COMPOSITE = L"Animations/Blank";
	const wchar_t* RANDOM_KEYBOARD = L"Animations/Random_Keyboard.chroma";
	const wchar_t* RANDOM_COMPOSITE = L"Animations/Random";
	const wchar_t* animationName = L"";
	int animationId = -1;

	ChromaAnimationAPI::PlayComposite(BLANK_COMPOSITE, false);
	ChromaAnimationAPI::PlayComposite(RANDOM_COMPOSITE, true);
	Sleep(500);
	int count = ChromaAnimationAPI::GetAnimationCount();
	ChromaLogger::wprintf(L"[%d] animation(s) are open.\r\n", count);
	for (int i = 0; i < count; ++i)
	{
		animationId = ChromaAnimationAPI::GetAnimationId(i);
		if (animationId < 0)
		{
			continue;
		}
		animationName = ChromaAnimationAPI::GetAnimationName(animationId);
		ChromaLogger::wprintf(L"Animation is open: [%d] %s\r\n", animationId, animationName);
	}
	ChromaLogger::wprintf(L"Closing open animations...\r\n");
	ChromaAnimationAPI::CloseAll();
	count = ChromaAnimationAPI::GetAnimationCount();
	ChromaLogger::wprintf(L"[%d] animation(s) are open.\r\n", count);
	ChromaLogger::wprintf(L"All animations are closed.\r\n");

	animationName = RANDOM_KEYBOARD;
	ChromaLogger::wprintf(L"Playing animation %s.\r\n", animationName);
	ChromaAnimationAPI::PlayAnimationName(animationName, false);
	while (ChromaAnimationAPI::IsPlayingName(animationName))
	{
		ChromaLogger::wprintf(L"Animation is playing... %s.\r\n", animationName);
		Sleep(1000);
	}
	ChromaLogger::wprintf(L"Animation complete %s.\r\n", animationName);
}

void UnitTests::UnitTestsSetKeys()
{
	int wasdKeys[4] =
	{
		(int)Keyboard::RZKEY::RZKEY_W,
		(int)Keyboard::RZKEY::RZKEY_A,
		(int)Keyboard::RZKEY::RZKEY_S,
		(int)Keyboard::RZKEY::RZKEY_D,
	};

	const wchar_t* BLANK_KEYBOARD = L"Animations/Blank_Keyboard.chroma";
	const wchar_t* BLANK_COMPOSITE = L"Animations/Blank";
	const wchar_t* RANDOM_KEYBOARD = L"Animations/Random_Keyboard.chroma";
	const wchar_t* RANDOM_COMPOSITE = L"Animations/Random";
	const wchar_t* animationName = L"";
	const wchar_t* compositeName = L"";
	const int COLOR_RED = 0xFF;
	int animationId = -1;

	compositeName = RANDOM_COMPOSITE;
	ChromaAnimationAPI::LoadComposite(compositeName);
	ChromaAnimationAPI::PlayComposite(compositeName, false);
	Sleep(1000);
	animationName = RANDOM_KEYBOARD;
	int frameCount = ChromaAnimationAPI::GetFrameCountName(animationName);
	for (int i = 0; i < frameCount; ++i)
	{
		ChromaAnimationAPI::SetKeysColorName(animationName, i, wasdKeys, (int)size(wasdKeys), COLOR_RED);
	}
	ChromaAnimationAPI::UnloadComposite(compositeName);
	ChromaAnimationAPI::PlayComposite(compositeName, false);
	Sleep(3000);
	ChromaAnimationAPI::CloseComposite(compositeName);
	Sleep(1000);

	animationName = BLANK_KEYBOARD;
	frameCount = ChromaAnimationAPI::GetFrameCountName(animationName);

	ChromaAnimationAPI::PlayAnimationName(animationName, false);
	Sleep(1000);

	for (int i = 0; i < frameCount; ++i)
	{
		ChromaAnimationAPI::SetKeysColorName(animationName, i, wasdKeys, (int)size(wasdKeys), COLOR_RED);
	}
	ChromaAnimationAPI::UnloadAnimationName(animationName);
	ChromaAnimationAPI::PlayAnimationName(animationName, false);
	Sleep(3000);

	ChromaAnimationAPI::CloseAnimationName(animationName);
	Sleep(100);

	for (int i = 0; i < frameCount; ++i)
	{
		ChromaAnimationAPI::SetKeyColorName(animationName, i, (int)Keyboard::RZKEY::RZKEY_W, COLOR_RED);
	}
	ChromaAnimationAPI::PlayAnimationName(animationName, false);
	Sleep(3000);

	ChromaAnimationAPI::CloseAnimationName(animationName);
	Sleep(100);
}

void UnitTests::UnitTestsClear()
{
	const wchar_t* BLANK_KEYBOARD = L"Animations/Blank_Keyboard.chroma";
	const wchar_t* BLANK_COMPOSITE = L"Animations/Blank";
	const wchar_t* RANDOM_KEYBOARD = L"Animations/Random_Keyboard.chroma";
	const wchar_t* RANDOM_COMPOSITE = L"Animations/Random";
	const wchar_t* animationName = L"";
	const wchar_t* compositeName = L"";
	int animationId = -1;

	ChromaLogger::wprintf(L"Playing animation.\r\n");
	ChromaAnimationAPI::PlayAnimationName(RANDOM_KEYBOARD, false);
	Sleep(100);

	ChromaLogger::wprintf(L"Clearing animations.\r\n");
	ChromaAnimationAPI::ClearAll();

	Sleep(1000);

	ChromaLogger::wprintf(L"Playing animations.\r\n");
	ChromaAnimationAPI::PlayComposite(L"Random", false);
	Sleep(100);

	for (int wait = 0; wait < 3; ++wait)
	{
		int count = ChromaAnimationAPI::GetAnimationCount();
		ChromaLogger::wprintf(L"[%d] animation(s) are open.\r\n", count);
		for (int i = 0; i < count; ++i)
		{
			animationId = ChromaAnimationAPI::GetAnimationId(i);
			if (animationId < 0)
			{
				continue;
			}
			animationName = ChromaAnimationAPI::GetAnimationName(animationId);
			ChromaLogger::wprintf(L"Animation is open: [%d] %s\r\n", animationId, animationName);
		}
		Sleep(500);
	}

	for (int wait = 0; wait < 10; ++wait)
	{
		int count = ChromaAnimationAPI::GetPlayingAnimationCount();
		ChromaLogger::wprintf(L"[%d] animation(s) are playing.\r\n", count);
		for (int i = 0; i < count; ++i)
		{
			animationId = ChromaAnimationAPI::GetPlayingAnimationId(i);
			if (animationId < 0)
			{
				continue;
			}

			animationName = ChromaAnimationAPI::GetAnimationName(animationId);
			ChromaLogger::wprintf(L"Animation is playing: [%d] %s\r\n", animationId, animationName);
		}
		if (ChromaAnimationAPI::GetPlayingAnimationCount() == 0)
		{
			ChromaLogger::wprintf(L"No animations are playing.\r\n");
		}
		Sleep(500);
	}

	ChromaAnimationAPI::ClearAll();

	Sleep(3000);
}

void UnitTests::UnitTestsWait()
{
	const wchar_t* BLANK_KEYBOARD = L"Animations/Blank_Keyboard.chroma";
	const wchar_t* BLANK_COMPOSITE = L"Animations/Blank";
	const wchar_t* RANDOM_KEYBOARD = L"Animations/Random_Keyboard.chroma";
	const wchar_t* RANDOM_COMPOSITE = L"Animations/Random";
	const wchar_t* animationName = L"";
	int animationId = -1;

	ChromaLogger::wprintf(L"Playing animation.\r\n");
	ChromaAnimationAPI::PlayAnimationName(RANDOM_KEYBOARD, false);
	Sleep(100);

	ChromaLogger::wprintf(L"Clearing animations.\r\n");
	ChromaAnimationAPI::ClearAll();

	Sleep(1000);

	ChromaLogger::wprintf(L"Playing animations.\r\n");
	ChromaAnimationAPI::PlayComposite(L"Random", false);
	Sleep(100);

	for (int wait = 0; wait < 3; ++wait)
	{
		int count = ChromaAnimationAPI::GetAnimationCount();
		ChromaLogger::wprintf(L"[%d] animation(s) are open.\r\n", count);
		for (int i = 0; i < count; ++i)
		{
			animationId = ChromaAnimationAPI::GetAnimationId(i);
			if (animationId < 0)
			{
				continue;
			}
			animationName = ChromaAnimationAPI::GetAnimationName(animationId);
			ChromaLogger::wprintf(L"Animation is open: [%d] %s\r\n", animationId, animationName);
		}
		Sleep(500);
	}

	for (int wait = 0; wait < 10; ++wait)
	{
		int count = ChromaAnimationAPI::GetPlayingAnimationCount();
		ChromaLogger::wprintf(L"[%d] animation(s) are playing.\r\n", count);
		for (int i = 0; i < count; ++i)
		{
			animationId = ChromaAnimationAPI::GetPlayingAnimationId(i);
			if (animationId < 0)
			{
				continue;
			}

			animationName = ChromaAnimationAPI::GetAnimationName(animationId);
			ChromaLogger::wprintf(L"Animation is playing: [%d] %s\r\n", animationId, animationName);
		}
		if (ChromaAnimationAPI::GetPlayingAnimationCount() == 0)
		{
			ChromaLogger::wprintf(L"No animations are playing.\r\n");
		}
		Sleep(500);
	}

	ChromaAnimationAPI::ClearAll();

	Sleep(3000);

	ChromaLogger::wprintf(L"Playing animation.\r\n");
	ChromaAnimationAPI::PlayAnimationName(RANDOM_KEYBOARD, false);
	Sleep(100);
}

void UnitTests::UnitTestsCopy()
{
	const wchar_t* RANDOM_KEYBOARD = L"Animations/Random_Keyboard.chroma";

	int frameCount = ChromaAnimationAPI::GetFrameCountName(RANDOM_KEYBOARD);
	for (int index = 0; index < frameCount; ++index)
	{
		ChromaAnimationAPI::CopyKeyColorName(L"Fire_Keyboard.chroma", RANDOM_KEYBOARD, index, (int)Keyboard::RZKEY::RZKEY_W);
		ChromaAnimationAPI::CopyKeyColorName(L"Fire_Keyboard.chroma", RANDOM_KEYBOARD, index, (int)Keyboard::RZKEY::RZKEY_A);
		ChromaAnimationAPI::CopyKeyColorName(L"Fire_Keyboard.chroma", RANDOM_KEYBOARD, index, (int)Keyboard::RZKEY::RZKEY_S);
		ChromaAnimationAPI::CopyKeyColorName(L"Fire_Keyboard.chroma", RANDOM_KEYBOARD, index, (int)Keyboard::RZKEY::RZKEY_D);
	}
	ChromaAnimationAPI::PlayAnimationName(RANDOM_KEYBOARD, true);
	Sleep(3000);

	ChromaAnimationAPI::CloseAnimationName(RANDOM_KEYBOARD);
}

void UnitTests::UnitTestsMisc()
{
	const wchar_t* RANDOM_KEYBOARD = L"Animations/Random_Keyboard.chroma";

	ChromaLogger::wprintf(L"Call: PlayComposite: Random\r\n");
	ChromaAnimationAPI::PlayComposite(L"Random", true);
	IsPlaying(L"Random");
	Sleep(3000);

	ChromaLogger::wprintf(L"Call: StopComposite\r\n");
	ChromaAnimationAPI::StopComposite(L"Random");
	IsPlaying(L"Random");
	Sleep(3000);

	ChromaLogger::wprintf(L"Call: PlayComposite: Blank\r\n");
	ChromaAnimationAPI::PlayComposite(L"Blank", false);
	IsPlaying(L"Random"); //random should show false, type should be playing blank
	Sleep(3000);

	ChromaLogger::wprintf(L"Call: PlayAnimationName\r\n");
	ChromaAnimationAPI::PlayAnimationName(RANDOM_KEYBOARD, true);
	Sleep(3000);

	ChromaLogger::wprintf(L"Call: StopAnimationName\r\n");
	ChromaAnimationAPI::StopAnimationName(RANDOM_KEYBOARD);
	Sleep(1000);

	ChromaLogger::wprintf(L"Call: PlayAnimationName\r\n");
	ChromaAnimationAPI::PlayAnimationName(RANDOM_KEYBOARD, true);
	Sleep(3000);

	ChromaLogger::wprintf(L"Call: StopAnimationType\r\n");
	ChromaAnimationAPI::StopAnimationType((int)EChromaSDKDeviceTypeEnum::DE_2D, (int)EChromaSDKDevice2DEnum::DE_Keyboard);
}

void UnitTests::UnitTestsOffset()
{
	ChromaLogger::wprintf(L"Start of offset unit test.\r\n");

	const wchar_t* RANDOM_KEYBOARD = L"Animations/Random_Keyboard.chroma";

	const wchar_t* animationName = RANDOM_KEYBOARD;
	ChromaAnimationAPI::CloseAnimationName(animationName);

	int animationId = ChromaAnimationAPI::OpenAnimation(animationName);

	int frameCount = ChromaAnimationAPI::GetFrameCountName(animationName);

	ChromaLogger::wprintf(L"Set all frames white with FillColor.\r\n");
	ChromaAnimationAPI::FillColorAllFramesRGBName(animationName, 255, 255, 255);

	ChromaLogger::wprintf(L"Fade out black with MultiplyIntensity.\r\n");
	for (int index = 0; index < frameCount; ++index)
	{
		float ratio = (index + 1) / (float)frameCount;
		float intensity = 1.0f - ratio;
		ChromaAnimationAPI::MultiplyIntensityName(animationName, index, intensity);
	}
	ChromaAnimationAPI::UnloadAnimationName(animationName); //show changes
	ChromaAnimationAPI::PlayAnimationName(animationName, false);
	while (ChromaAnimationAPI::IsPlayingName(animationName))
	{
		Sleep(0);
	}

	ChromaLogger::wprintf(L"Set all frames black with FillColor.\r\n");
	ChromaAnimationAPI::UnloadAnimationName(animationName);
	ChromaAnimationAPI::FillColorAllFramesRGBName(animationName, 0, 0, 0);

	ChromaLogger::wprintf(L"Fade in red with FillColor.\r\n");
	for (int index = 0; index < frameCount; ++index)
	{
		int ratio = (255 * index + 1) / frameCount;
		ChromaAnimationAPI::FillColorRGBName(animationName, index, ratio, 0, 0);
	}
	ChromaAnimationAPI::UnloadAnimationName(animationName); //show changes
	ChromaAnimationAPI::PlayAnimationName(animationName, false);
	while (ChromaAnimationAPI::IsPlayingName(animationName))
	{
		Sleep(0);
	}

	ChromaLogger::wprintf(L"Set all frames red with FillColor.\r\n");
	ChromaAnimationAPI::FillColorAllFramesRGBName(animationName, 255, 0, 0);

	ChromaLogger::wprintf(L"Fade in green with OffsetColors.\r\n");
	for (int index = 0; index < frameCount; ++index)
	{
		const int greenOffset = 16;
		ChromaAnimationAPI::OffsetColorsName(animationName, index, 0, index * greenOffset, 0);
	}
	ChromaAnimationAPI::UnloadAnimationName(animationName); //show changes
	ChromaAnimationAPI::PlayAnimationName(animationName, false);
	while (ChromaAnimationAPI::IsPlayingName(animationName))
	{
		Sleep(0);
	}

	ChromaLogger::wprintf(L"Set all frames yellow with FillColor.\r\n");
	ChromaAnimationAPI::FillColorAllFramesRGBName(animationName, 255, 255, 0);

	ChromaLogger::wprintf(L"Fade out red with OffsetColors.\r\n");
	for (int index = 0; index < frameCount; ++index)
	{
		const int redOffset = -16;
		ChromaAnimationAPI::OffsetColorsName(animationName, index, index * redOffset, 0, 0);
	}
	ChromaAnimationAPI::UnloadAnimationName(animationName); //show changes
	ChromaAnimationAPI::PlayAnimationName(animationName, false);
	while (ChromaAnimationAPI::IsPlayingName(animationName))
	{
		Sleep(0);
	}

	ChromaLogger::wprintf(L"Set all frames green with FillColor.\r\n");
	ChromaAnimationAPI::FillColorAllFramesRGBName(animationName, 0, 255, 0);

	ChromaLogger::wprintf(L"Fade in white with OffsetColors.\r\n");
	for (int index = 0; index < frameCount; ++index)
	{
		const int redOffset = 16;
		const int blueOffset = 16;
		ChromaAnimationAPI::OffsetColorsName(animationName, index, index * redOffset, 0, index * blueOffset);
	}
	ChromaAnimationAPI::UnloadAnimationName(animationName); //show changes
	ChromaAnimationAPI::PlayAnimationName(animationName, false);
	while (ChromaAnimationAPI::IsPlayingName(animationName))
	{
		Sleep(0);
	}

	ChromaLogger::wprintf(L"End of offset unit test.\r\n");
}

void UnitTests::UnitTestsNonZero()
{
	ChromaLogger::wprintf(L"Start of nonzero unit test.\r\n");

	const int COLOR_WHITE = 0xFFFFFF;

	int wasdKeys[4] =
	{
		(int)Keyboard::RZKEY::RZKEY_W,
		(int)Keyboard::RZKEY::RZKEY_A,
		(int)Keyboard::RZKEY::RZKEY_S,
		(int)Keyboard::RZKEY::RZKEY_D,
	};

	const wchar_t* SPRITE_KEYBOARD = L"Animations/Sprite_Keyboard.chroma";
	const wchar_t* WAVE_KEYBOARD = L"Animations/Rows_Keyboard.chroma";

	const wchar_t* animationName = WAVE_KEYBOARD;
	int animationId = ChromaAnimationAPI::OpenAnimation(animationName);

	// Reload from disk
	ChromaAnimationAPI::CloseAnimationName(animationName);

	int frameCount = ChromaAnimationAPI::GetFrameCountName(animationName);

	ChromaLogger::wprintf(L"Fade out red.\r\n");
	for (int i = 0; i < frameCount; ++i)
	{
		float ratio = (i + 1) / (float)frameCount;
		ChromaAnimationAPI::OffsetNonZeroColorsName(animationName, i, (int)(-255 * ratio), 0, 0);
	}
	ChromaAnimationAPI::UnloadAnimationName(animationName); //show changes
	ChromaAnimationAPI::PlayAnimationName(animationName, false);
	while (ChromaAnimationAPI::IsPlayingName(animationName))
	{
		Sleep(0);
	}
	ChromaLogger::wprintf(L"Red should be gone.\r\n");
	Sleep(3000);

	ChromaLogger::wprintf(L"Fade out green.\r\n");
	for (int i = 0; i < frameCount; ++i)
	{
		float ratio = (i + 1) / (float)frameCount;
		ChromaAnimationAPI::OffsetNonZeroColorsName(animationName, i, -255, (int)(-255 * ratio), 0);
	}
	ChromaAnimationAPI::UnloadAnimationName(animationName); //show changes
	ChromaAnimationAPI::PlayAnimationName(animationName, false);
	while (ChromaAnimationAPI::IsPlayingName(animationName))
	{
		Sleep(0);
	}
	ChromaLogger::wprintf(L"Green should be gone.\r\n");
	Sleep(3000);

	ChromaLogger::wprintf(L"Fade out blue.\r\n");
	for (int i = 0; i < frameCount; ++i)
	{
		float ratio = (i + 1) / (float)frameCount;
		ChromaAnimationAPI::OffsetNonZeroColorsName(animationName, i, -255, -255, (int)(-255 * ratio));
	}
	ChromaAnimationAPI::UnloadAnimationName(animationName); //show changes
	ChromaAnimationAPI::PlayAnimationName(animationName, false);
	while (ChromaAnimationAPI::IsPlayingName(animationName))
	{
		Sleep(0);
	}
	ChromaLogger::wprintf(L"Blue should be gone.\r\n");
	Sleep(3000);

	ChromaLogger::wprintf(L"Non zero keys should fade in to white.\r\n");
	for (int i = 0; i < frameCount; ++i)
	{
		float ratio = (i + 1) / (float)frameCount;
		ChromaAnimationAPI::FillNonZeroColorRGBName(animationName, i, (int)(ratio * 255), (int)(ratio * 255), (int)(ratio * 255));
	}
	ChromaAnimationAPI::UnloadAnimationName(animationName); //show changes
	ChromaAnimationAPI::PlayAnimationName(animationName, false);
	while (ChromaAnimationAPI::IsPlayingName(animationName))
	{
		Sleep(0);
	}

	// Reload from disk
	ChromaAnimationAPI::CloseAnimationName(animationName);

	animationName = SPRITE_KEYBOARD;
	frameCount = ChromaAnimationAPI::GetFrameCountName(animationName);

	// Reload from disk
	ChromaAnimationAPI::CloseAnimationName(animationName);

	ChromaLogger::wprintf(L"WASD keys should be white every other frame.\r\n");
	for (int i = 0; i < frameCount; ++i)
	{
		ChromaAnimationAPI::SetKeyNonZeroColorName(animationName, i, (int)Keyboard::RZKEY::RZKEY_W, COLOR_WHITE);
		ChromaAnimationAPI::SetKeyNonZeroColorName(animationName, i, (int)Keyboard::RZKEY::RZKEY_A, COLOR_WHITE);
		ChromaAnimationAPI::SetKeyNonZeroColorName(animationName, i, (int)Keyboard::RZKEY::RZKEY_S, COLOR_WHITE);
		ChromaAnimationAPI::SetKeyNonZeroColorName(animationName, i, (int)Keyboard::RZKEY::RZKEY_D, COLOR_WHITE);
	}
	ChromaAnimationAPI::UnloadAnimationName(animationName); //show changes
	ChromaAnimationAPI::PlayAnimationName(animationName, false);
	while (ChromaAnimationAPI::IsPlayingName(animationName))
	{
		Sleep(0);
	}

	// Reload from disk
	ChromaAnimationAPI::CloseAnimationName(animationName);

	ChromaLogger::wprintf(L"WASD keys should be white every other frame.\r\n");
	for (int i = 0; i < frameCount; ++i)
	{
		ChromaAnimationAPI::SetKeysNonZeroColorName(animationName, i, wasdKeys, (int)size(wasdKeys), COLOR_WHITE);
	}
	ChromaAnimationAPI::UnloadAnimationName(animationName); //show changes
	ChromaAnimationAPI::PlayAnimationName(animationName, false);
	while (ChromaAnimationAPI::IsPlayingName(animationName))
	{
		Sleep(0);
	}

	ChromaLogger::wprintf(L"End of nonzero unit test.\r\n");
}

void UnitTests::UnitTestsHDKIndividualLEDs()
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

	ChromaLogger::wprintf(L"Create random HDK LED colors effect.\r\n");

	FChromaSDKGuid effectId = FChromaSDKGuid();
	ChromaAnimationAPI::CreateEffect(CHROMABOX, EFFECT_TYPE::CHROMA_CUSTOM, colors, size, &effectId);

	ChromaLogger::wprintf(L"Set HDK Effect.\r\n");

	ChromaAnimationAPI::SetEffect(effectId);

	Sleep(3000);

	ChromaLogger::wprintf(L"Delete HDK Effect.\r\n");

	ChromaAnimationAPI::DeleteEffect(effectId);

	Sleep(1000);

	delete []colors;
}

void UnitTests::UnitTestsHDKIndividualLEDsGradient()
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
			int green = min(255, (int)(j / (float)HDK_MAX_LEDS * 255));
			COLORREF color = RGB(red, green, 0);
			colors[index] = color;
			++index;
		}
	}

	ChromaLogger::wprintf(L"Create HDK gradient.\r\n");

	FChromaSDKGuid effectId = FChromaSDKGuid();
	ChromaAnimationAPI::CreateEffect(CHROMABOX, EFFECT_TYPE::CHROMA_CUSTOM, colors, size, &effectId);

	ChromaLogger::wprintf(L"Set HDK Effect.\r\n");

	ChromaAnimationAPI::SetEffect(effectId);

	Sleep(3000);

	ChromaLogger::wprintf(L"Delete HDK Effect.\r\n");

	ChromaAnimationAPI::DeleteEffect(effectId);

	Sleep(1000);

	delete []colors;
}

void UnitTests::UnitTestsCreateAnimation()
{
	const wchar_t* animationName = L"Animations/New_ChromaLink.chroma";
	int animationId = ChromaAnimationAPI::CreateAnimation(animationName, (int)EChromaSDKDeviceTypeEnum::DE_1D, (int)EChromaSDKDevice1DEnum::DE_ChromaLink);
	if (animationId < 0)
	{
		ChromaLogger::fwprintf(stderr, L"Failed to create animation! %s\r\n", animationName);
	}
}

void UnitTests::UnitTestsKeyboardCustom()
{
	ChromaLogger::wprintf(L"Clear all.\r\n");
	ChromaAnimationAPI::ClearAll();
	Sleep(3000);

	ChromaLogger::wprintf(L"Show custom keyboard keys Z N M LALT.\r\n");
	int animationId = ChromaAnimationAPI::CreateAnimationInMemory((int)EChromaSDKDeviceTypeEnum::DE_2D, (int)EChromaSDKDevice2DEnum::DE_Keyboard);
	ChromaAnimationAPI::SetChromaCustomFlag(animationId, true);
	ChromaAnimationAPI::SetKeyColor(animationId, 0, (int)Keyboard::RZKEY::RZKEY_Z, 0x01FF0000);
	ChromaAnimationAPI::SetKeyColor(animationId, 0, (int)Keyboard::RZKEY::RZKEY_N, 0x0100FF00);
	ChromaAnimationAPI::SetKeyColor(animationId, 0, (int)Keyboard::RZKEY::RZKEY_M, 0x010000FF);
	ChromaAnimationAPI::SetKeyColor(animationId, 0, (int)Keyboard::RZKEY::RZKEY_LALT, 0x01FFFFFF);
	ChromaLogger::wprintf(L"Play animation with custom keys.\r\n");
	ChromaAnimationAPI::PlayAnimation(animationId);
	Sleep(2000);
	ChromaLogger::wprintf(L"Preview frame with custom keys.\r\n");
	ChromaAnimationAPI::PreviewFrame(animationId, 0);
	Sleep(2000);
	ChromaAnimationAPI::CloseAnimation(animationId);

	ChromaLogger::wprintf(L"Clear all.\r\n");
	ChromaAnimationAPI::ClearAll();
	Sleep(3000);

	ChromaLogger::wprintf(L"Show custom keyboard keys LCTRL X C V B.\r\n");
	animationId = ChromaAnimationAPI::CreateAnimationInMemory((int)EChromaSDKDeviceTypeEnum::DE_2D, (int)EChromaSDKDevice2DEnum::DE_Keyboard);
	ChromaAnimationAPI::SetChromaCustomFlag(animationId, true);
	ChromaAnimationAPI::SetKeyColor(animationId, 0, (int)Keyboard::RZKEY::RZKEY_LCTRL, 0x01FF0000);
	ChromaAnimationAPI::SetKeyColor(animationId, 0, (int)Keyboard::RZKEY::RZKEY_X, 0x0100FF00);
	ChromaAnimationAPI::SetKeyColor(animationId, 0, (int)Keyboard::RZKEY::RZKEY_C, 0x010000FF);
	ChromaAnimationAPI::SetKeyColor(animationId, 0, (int)Keyboard::RZKEY::RZKEY_V, 0x01FFFFFF);
	ChromaAnimationAPI::SetKeyColor(animationId, 0, (int)Keyboard::RZKEY::RZKEY_B, 0x01FFFF00);
	ChromaLogger::wprintf(L"Play animation with custom keys.\r\n");
	ChromaAnimationAPI::PlayAnimation(animationId);
	Sleep(2000);
	ChromaLogger::wprintf(L"Preview frame with custom keys.\r\n");
	ChromaAnimationAPI::PreviewFrame(animationId, 0);
	Sleep(2000);
	ChromaAnimationAPI::CloseAnimation(animationId);

	ChromaLogger::wprintf(L"Clear all.\r\n");
	ChromaAnimationAPI::ClearAll();
	Sleep(3000);
}

void UnitTests::UnitTestsFadeStart()
{
	const wchar_t* baseLayer = L"Animations/Blank_Keyboard.chroma";
	ChromaAnimationAPI::CloseAnimationName(baseLayer);
	ChromaAnimationAPI::GetAnimation(baseLayer);

	int frameCount = 100;
	ChromaAnimationAPI::MakeBlankFramesRGBName(baseLayer, frameCount, 0.1f, 255, 255, 255);
	ChromaAnimationAPI::FadeStartFramesName(baseLayer, frameCount);

	ChromaAnimationAPI::SetChromaCustomFlagName(baseLayer, true);
	ChromaAnimationAPI::SetChromaCustomColorAllFramesName(baseLayer);
	ChromaAnimationAPI::OverrideFrameDurationName(baseLayer, 0.033f);
	ChromaAnimationAPI::PlayAnimationName(baseLayer, true);

	Sleep(1000);
}

void UnitTests::UnitTestsFadeEnd()
{
	const wchar_t* baseLayer = L"Animations/Blank_Keyboard.chroma";
	ChromaAnimationAPI::CloseAnimationName(baseLayer);
	ChromaAnimationAPI::GetAnimation(baseLayer);

	int frameCount = 100;
	ChromaAnimationAPI::MakeBlankFramesRGBName(baseLayer, frameCount, 0.1f, 255, 255, 255);
	ChromaAnimationAPI::FadeEndFramesName(baseLayer, frameCount);

	ChromaAnimationAPI::SetChromaCustomFlagName(baseLayer, true);
	ChromaAnimationAPI::SetChromaCustomColorAllFramesName(baseLayer);
	ChromaAnimationAPI::OverrideFrameDurationName(baseLayer, 0.033f);
	ChromaAnimationAPI::PlayAnimationName(baseLayer, true);

	Sleep(1000);
}

void UnitTests::UnitTestsCopyAnimation()
{
	const wchar_t* baseLayer = L"Animations/Fire_Keyboard.chroma";
	const wchar_t* layerTemp = L"TempLayer";
	ChromaAnimationAPI::CloseAnimationName(baseLayer);
	ChromaAnimationAPI::GetAnimation(baseLayer);

	ChromaAnimationAPI::MultiplyIntensityAllFramesRGBName(baseLayer, 255, 0, 0);

	ChromaAnimationAPI::SetChromaCustomFlagName(baseLayer, true);
	ChromaAnimationAPI::SetChromaCustomColorAllFramesName(baseLayer);
	ChromaAnimationAPI::OverrideFrameDurationName(baseLayer, 0.033f);

	ChromaAnimationAPI::CopyAnimationName(baseLayer, layerTemp);

	ChromaAnimationAPI::PlayAnimationName(layerTemp, true);

	Sleep(1000);
}

void UnitTests::UnitTestsSaveAnimation()
{
	// get current time
	high_resolution_clock::time_point timer = high_resolution_clock::now();

	int baseAnimation = ChromaAnimationAPI::CreateAnimationInMemory((int)EChromaSDKDeviceTypeEnum::DE_2D, (int)EChromaSDKDevice2DEnum::DE_Keyboard);
	int frameCount = 100;
	ChromaAnimationAPI::MakeBlankFramesRandom(baseAnimation, frameCount, 0.1f);

	ChromaAnimationAPI::SetChromaCustomFlag(baseAnimation, true);
	ChromaAnimationAPI::SetChromaCustomColorAllFrames(baseAnimation);

	ChromaAnimationAPI::SaveAnimation(baseAnimation, L"SaveAnimation.chroma");

	// get time in seconds
	duration<double, milli> time_span = high_resolution_clock::now() - timer;
	float deltaTime = (float)(time_span.count() / 1000.0f);
	ChromaLogger::wprintf(L"Elapsed time: %f\r\n", deltaTime);

	ChromaAnimationAPI::PlayAnimationLoop(baseAnimation, true);

	Sleep(3000);

	ChromaAnimationAPI::CloseAnimation(baseAnimation);

	Sleep(1000);
}

void UnitTests::UnitTestsSaveAnimation2()
{
	const wchar_t* baseLayer = L"Animations/Fire_Keyboard.chroma";
	ChromaAnimationAPI::CloseAnimationName(baseLayer);
	ChromaAnimationAPI::GetAnimation(baseLayer);

	ChromaAnimationAPI::MultiplyIntensityAllFramesRGBName(baseLayer, 255, 0, 0);

	ChromaAnimationAPI::SetChromaCustomFlagName(baseLayer, true);
	ChromaAnimationAPI::SetChromaCustomColorAllFramesName(baseLayer);
	ChromaAnimationAPI::OverrideFrameDurationName(baseLayer, 0.033f);

	ChromaAnimationAPI::SaveAnimationName(baseLayer, L"SaveAnimation.chroma");

	ChromaAnimationAPI::PlayAnimationName(baseLayer, true);

	Sleep(1000);
}

void UnitTests::UnitTestsCreateRandomBlackAndWhite()
{
	// get current time
	high_resolution_clock::time_point timer = high_resolution_clock::now();

	int baseAnimation = ChromaAnimationAPI::CreateAnimationInMemory((int)EChromaSDKDeviceTypeEnum::DE_2D, (int)EChromaSDKDevice2DEnum::DE_Keyboard);
	int frameCount = 100;
	ChromaAnimationAPI::MakeBlankFramesRandomBlackAndWhite(baseAnimation, frameCount, 0.1f);
	ChromaAnimationAPI::MultiplyIntensityAllFrames(baseAnimation, 0.25f);

	ChromaAnimationAPI::SetChromaCustomFlag(baseAnimation, true);
	ChromaAnimationAPI::SetChromaCustomColorAllFrames(baseAnimation);
	ChromaAnimationAPI::PlayAnimationLoop(baseAnimation, true);

	// get time in seconds
	duration<double, milli> time_span = high_resolution_clock::now() - timer;
	float deltaTime = (float)(time_span.count() / 1000.0f);
	ChromaLogger::wprintf(L"Elapsed time: %f\r\n", deltaTime);

	Sleep(3000);

	ChromaAnimationAPI::CloseAnimation(baseAnimation);

	Sleep(1000);
}

void UnitTests::UnitTestsDuplicateFirstFrame()
{
	const wchar_t* baseLayer = L"Animations/CircleSmall_Keyboard.chroma";
	ChromaAnimationAPI::CloseAnimationName(baseLayer);
	int baseAnimation = ChromaAnimationAPI::OpenAnimation(baseLayer);

	int frameCount = 24;
	ChromaAnimationAPI::DuplicateFirstFrameName(baseLayer, frameCount);

	for (int frameId = 0; frameId < frameCount; ++frameId) {
		float t = 1 - fabsf(cosf(MATH_PI*frameId / (float)frameCount));
		ChromaAnimationAPI::MultiplyIntensityRGBName(baseLayer, frameId, 0, (int)(127 * t), 0);
	}

	ChromaAnimationAPI::SetChromaCustomFlagName(baseLayer, true);
	ChromaAnimationAPI::SetChromaCustomColorAllFramesName(baseLayer);
	ChromaAnimationAPI::PlayAnimationName(baseLayer, true);
}

int UnitTests::OpenAndPlay(const wchar_t* path)
{
	int animationId = (int)ChromaAnimationAPI::OpenAnimation(path);
	ChromaLogger::wprintf(L"OpenAnimation: %s result=%d\r\n", path, animationId);
	if (animationId >= 0)
	{
		int result = (int)ChromaAnimationAPI::PlayAnimation(animationId);
		ChromaLogger::wprintf(L"PlayAnimation: %d result=%d\r\n", animationId, result);
		return result;
	}
	else
	{
		return -1;
	}
}

int UnitTests::CloseAnimation(int animationId)
{
	int result = (int)ChromaAnimationAPI::CloseAnimation(animationId);
	ChromaLogger::wprintf(L"CloseAnimation: %d result=%d\r\n", animationId, result);
	return result;
}

void UnitTests::UnitTestsOpenAnimationFromMemory()
{
	const wchar_t* path = L"Animations/Random_Keyboard.chroma";
	FILE* stream = nullptr;
	try
	{
		if (0 != _wfopen_s(&stream, path, L"rb") ||
			stream == nullptr)
		{
			ChromaLogger::fwprintf(stderr, L"UnitTestsOpenAnimationFromMemory: Failed to open animation! %s\r\n", path);
			return;
		}

		ChromaLogger::wprintf(L"UnitTestsOpenAnimationFromMemory: Reading animation file contents...\r\n");

		vector<BYTE> lstBuffer;

		BYTE data = 0;
		size_t read = 0;
		do
		{
			read = fread(&data, sizeof(BYTE), 1, stream);
			lstBuffer.push_back(data);
		} while (read != 0);

 		ChromaLogger::fwprintf(stderr, L"UnitTestsOpenAnimationFromMemory: File size is! %d\r\n", (int)lstBuffer.size());

		BYTE* buffer = new BYTE[lstBuffer.size()];
		copy(lstBuffer.begin(), lstBuffer.end(), buffer);

		ChromaLogger::wprintf(L"UnitTestsOpenAnimationFromMemory: Opening file from buffer...\r\n");

		const wchar_t* name = L"MemoryAnimation.chroma";
		ChromaAnimationAPI::OpenAnimationFromMemory(buffer, name);

		ChromaLogger::wprintf(L"UnitTestsOpenAnimationFromMemory: Deleting buffer...\r\n");

		delete []buffer;

		ChromaLogger::wprintf(L"UnitTestsOpenAnimationFromMemory: Playing animation...\r\n");

		ChromaAnimationAPI::PlayAnimationName(name, true);

		Sleep(5000);
	}
	catch (exception)
	{
		ChromaLogger::fwprintf(stderr, L"UnitTestsOpenAnimationFromMemory: Exception path=%s\r\n", path);
	}

	if (stream != nullptr)
	{
		fclose(stream);
	}

	ChromaLogger::wprintf(L"UnitTestsOpenAnimationFromMemory: Complete!\r\n");
}

void UnitTests::UnitTestsIdleAnimation()
{
	const wchar_t* randomAnimation = L"Animations/Random_Keyboard.chroma";
	const wchar_t* idleAnimation = L"Animations/Fire_Keyboard.chroma";

	const int delay = 3000;

	ChromaLogger::wprintf(L"Idle is [ON].\r\n");
	ChromaAnimationAPI::UseIdleAnimation((int)EChromaSDKDeviceEnum::DE_Keyboard, true);

	ChromaAnimationAPI::CloseAnimationName(idleAnimation);
	ChromaAnimationAPI::OverrideFrameDurationName(idleAnimation, 0.1f);
	ChromaAnimationAPI::SetIdleAnimationName(idleAnimation);
	
	ChromaAnimationAPI::CloseAnimationName(randomAnimation);
	ChromaAnimationAPI::OverrideFrameDurationName(randomAnimation, 0.1f);

	ChromaLogger::wprintf(L"Play random animation.\r\n");
	ChromaAnimationAPI::PlayAnimationName(randomAnimation, false);
	ChromaLogger::wprintf(L"Waiting 3 sec...\r\n");
	Sleep(delay);
	ChromaLogger::wprintf(L"\r\n");

	ChromaLogger::wprintf(L"Close idle animation while active...\r\n");
	ChromaAnimationAPI::CloseAnimationName(idleAnimation);
	ChromaAnimationAPI::OverrideFrameDurationName(idleAnimation, 0.1f);
	Sleep(delay);
	ChromaLogger::wprintf(L"\r\n");

	ChromaLogger::wprintf(L"Set idle animation.\r\n");
	ChromaAnimationAPI::SetIdleAnimationName(idleAnimation);

	ChromaLogger::wprintf(L"Play random animation.\r\n");
	ChromaAnimationAPI::PlayAnimationName(randomAnimation, false);
	ChromaLogger::wprintf(L"Waiting 3 sec...\r\n");
	Sleep(delay);
	ChromaLogger::wprintf(L"\r\n");

	ChromaLogger::wprintf(L"Play random animation.\r\n");
	ChromaAnimationAPI::PlayAnimationName(randomAnimation, false);
	ChromaLogger::wprintf(L"Waiting 3 sec...\r\n");
	Sleep(delay);
	ChromaLogger::wprintf(L"\r\n");

	ChromaLogger::wprintf(L"Clear all animations with idle [ON].\r\n");
	ChromaAnimationAPI::ClearAll();
	ChromaLogger::wprintf(L"Waiting 3 sec...\r\n");
	Sleep(delay);
	ChromaLogger::wprintf(L"\r\n");

	ChromaLogger::wprintf(L"Idle is [OFF].\r\n");
	ChromaAnimationAPI::UseIdleAnimation((int)EChromaSDKDeviceEnum::DE_Keyboard, false);
	ChromaAnimationAPI::ClearAll();
	ChromaLogger::wprintf(L"Waiting 3 sec...\r\n");
	Sleep(delay);
	ChromaLogger::wprintf(L"\r\n");
}

void UnitTests::UnitTestsDamage()
{
	vector<wstring> damageList;
	for (int i = 0; i < 8; ++i)
	{
		wstring name = L"Animations/Damage";
		switch (i + 1)
		{
		case 1:
			name += L"1";
			break;
		case 2:
			name += L"2";
			break;
		case 3:
			name += L"3";
			break;
		case 4:
			name += L"4";
			break;
		case 5:
			name += L"5";
			break;
		case 6:
			name += L"6";
			break;
		case 7:
			name += L"7";
			break;
		case 8:
			name += L"8";
			break;
		}
		name += L"_Keyboard.chroma";
		damageList.push_back(name);
	}

	int frameCount = 1;

	const wchar_t* BLANK_KEYBOARD = L"Animations/Blank_Keyboard.chroma";
	ChromaAnimationAPI::GetAnimation(BLANK_KEYBOARD);

	const wchar_t* COPY_BLANK_KEYBOARD = L"Copy_Blank_Keyboard.chroma";

	const wchar_t* RAINBOW_KEYBOARD = L"Animations/Rainbow_Keyboard.chroma";

	// get current time
	high_resolution_clock::time_point timer = high_resolution_clock::now();

	// Focus on one damage animation at a time
	int selected = 0;

	int keys[] =
	{
		Keyboard::RZKEY::RZKEY_W,
		Keyboard::RZKEY::RZKEY_A,
		Keyboard::RZKEY::RZKEY_S,
		Keyboard::RZKEY::RZKEY_D,
	};

	int frameCountRainbow = ChromaAnimationAPI::GetFrameCountName(RAINBOW_KEYBOARD);

	int indexRainbow = 0;

	while (true)
	{
		// get time in seconds
		duration<double, milli> time_span = high_resolution_clock::now() - timer;
		float deltaTime = (float)(time_span.count() / 1000.0f);

		//integer number of times to blink per second
		const float speed = 2;

		ChromaAnimationAPI::CopyAnimationName(BLANK_KEYBOARD, COPY_BLANK_KEYBOARD);

		for (int i = 0; i < 8; ++i)
		{
			// randomly select another animation
			if (rand() % 100 == 0)
			{
				selected = i;
			}
			if (selected != i)
			{
				continue;
			}

			float t = fabsf(cosf((speed * MATH_PI * deltaTime)));

			wstring& name = damageList[i];

			wstring copy = L"copy_";
			copy += name;
			ChromaAnimationAPI::CopyAnimationName(name.c_str(), copy.c_str());

			ChromaAnimationAPI::MultiplyIntensityRGBName(copy.c_str(), 0, (int)(255*t), 0, 0);

			ChromaAnimationAPI::CopyNonZeroAllKeysName(copy.c_str(), COPY_BLANK_KEYBOARD, 0);
		}

		ChromaAnimationAPI::CopyKeysColorOffsetName(RAINBOW_KEYBOARD, COPY_BLANK_KEYBOARD, indexRainbow, 0, keys, (int)size(keys));

		ChromaAnimationAPI::PreviewFrameName(COPY_BLANK_KEYBOARD, 0);
		
		Sleep(33);
		indexRainbow = (indexRainbow+1) % frameCountRainbow;
	}
}

void UnitTests::UnitTestFireKeyboard()
{
	const wchar_t* path = L"Animations/Fire_Keyboard.chroma";
	ChromaAnimationAPI::PlayAnimationName(path, false);
	Sleep(3000);
}

void UnitTests::UnitTestsMeasurePreloading()
{
	const wchar_t* RAINBOW_KEYBOARD = L"Animations/Rainbow_Keyboard.chroma";

	ChromaLogger::wprintf(L"Measure [immediate mode] elapsed time...\r\n");
	for (int i = 0; i < 10; ++i)
	{
		// unload the animation (shouldn't be loaded)
		ChromaAnimationAPI::UnloadAnimationName(RAINBOW_KEYBOARD);

		// close animation before test
		ChromaAnimationAPI::CloseAnimationName(RAINBOW_KEYBOARD);

		// open the animation
		ChromaAnimationAPI::GetAnimation(RAINBOW_KEYBOARD);

		// set default preloading flag to true
		ChromaAnimationAPI::UsePreloadingName(RAINBOW_KEYBOARD, false);

		// get current time
		high_resolution_clock::time_point timer = high_resolution_clock::now();

		// PlayAnimation() will not invoke Load() in immediate mode

		// play the animation
		ChromaAnimationAPI::PlayAnimationName(RAINBOW_KEYBOARD, true);

		// get time in seconds
		duration<double, milli> time_span = high_resolution_clock::now() - timer;
		float deltaTime = (float)(time_span.count() / 1000.0f);
		ChromaLogger::wprintf(L"Immediate elapsed time: %f\r\n", deltaTime);

		Sleep(500);
	}

	ChromaLogger::wprintf(L"Measure [preload mode] elapsed time...\r\n");
	for (int i = 0; i < 10; ++i)
	{
		// unload the animation
		ChromaAnimationAPI::UnloadAnimationName(RAINBOW_KEYBOARD);

		// close animation before test
		ChromaAnimationAPI::CloseAnimationName(RAINBOW_KEYBOARD);

		// set the preloading flag to true (true is the default)
		ChromaAnimationAPI::UsePreloadingName(RAINBOW_KEYBOARD, true);

		// open the animation
		ChromaAnimationAPI::GetAnimation(RAINBOW_KEYBOARD);

		// get current time
		high_resolution_clock::time_point timer = high_resolution_clock::now();

		// PlayAnimation() is going to invoke Load() in preloading mode (default)

		// play the animation
		ChromaAnimationAPI::PlayAnimationName(RAINBOW_KEYBOARD, true);

		// get time in seconds
		duration<double, milli> time_span = high_resolution_clock::now() - timer;
		float deltaTime = (float)(time_span.count() / 1000.0f);
		ChromaLogger::wprintf(L"Preload elapsed time: %f\r\n", deltaTime);

		Sleep(500);
	}
}

void UnitTests::UnitTestsMeasurePreloadingWithCaching()
{
	const wchar_t* path = L"Animations/Rainbow_Keyboard.chroma";
	FILE* stream = nullptr;
	try
	{
		if (0 != _wfopen_s(&stream, path, L"rb") ||
			stream == nullptr)
		{
			ChromaLogger::fwprintf(stderr, L"UnitTestsMeasurePreloadingWithCaching: Failed to open animation! %s\r\n", path);
			return;
		}

		ChromaLogger::wprintf(L"UnitTestsMeasurePreloadingWithCaching: Reading animation file contents...\r\n");

		vector<BYTE> lstBuffer;

		BYTE data = 0;
		size_t read = 0;
		do
		{
			read = fread(&data, sizeof(BYTE), 1, stream);
			lstBuffer.push_back(data);
		} while (read != 0);

		ChromaLogger::fwprintf(stderr, L"UnitTestsMeasurePreloadingWithCaching: File size is! %d\r\n", (int)lstBuffer.size());

		BYTE* buffer = new BYTE[lstBuffer.size()];
		copy(lstBuffer.begin(), lstBuffer.end(), buffer);

		ChromaLogger::wprintf(L"UnitTestsMeasurePreloadingWithCaching: Opening file from buffer...\r\n");

		const wchar_t* name = L"MemoryAnimation.chroma";

		// measure performance

		ChromaLogger::wprintf(L"Measure [immediate mode] elapsed time...\r\n");
		for (int i = 0; i < 10; ++i)
		{
			// open the animation
			int animationId = ChromaAnimationAPI::OpenAnimationFromMemory(buffer, name);

			// set default preloading flag to true
			ChromaAnimationAPI::UsePreloading(animationId, false);

			// get current time
			high_resolution_clock::time_point timer = high_resolution_clock::now();

			// PlayAnimation() will not invoke Load() in immediate mode

			// play the animation
			ChromaAnimationAPI::PlayAnimationLoop(animationId, true);

			// get time in seconds
			duration<double, milli> time_span = high_resolution_clock::now() - timer;
			float deltaTime = (float)(time_span.count() / 1000.0f);
			ChromaLogger::wprintf(L"Immediate elapsed time: %f\r\n", deltaTime);

			Sleep(500);

			// close animation
			ChromaAnimationAPI::CloseAnimation(animationId);
		}

		ChromaLogger::wprintf(L"Measure [preload mode] elapsed time...\r\n");
		for (int i = 0; i < 10; ++i)
		{
			// open the animation
			int animationId = ChromaAnimationAPI::OpenAnimationFromMemory(buffer, name);

			// set the preloading flag to true (true is the default)
			ChromaAnimationAPI::UsePreloading(animationId, true);

			// get current time
			high_resolution_clock::time_point timer = high_resolution_clock::now();

			// PlayAnimation() is going to invoke Load() in preloading mode (default)

			// play the animation
			ChromaAnimationAPI::PlayAnimationLoop(animationId, true);

			// get time in seconds
			duration<double, milli> time_span = high_resolution_clock::now() - timer;
			float deltaTime = (float)(time_span.count() / 1000.0f);
			ChromaLogger::wprintf(L"Preload elapsed time: %f\r\n", deltaTime);

			Sleep(500);

			// close animation
			ChromaAnimationAPI::CloseAnimation(animationId);
		}

		// clear buffer for loading from memory
		ChromaLogger::wprintf(L"UnitTestsMeasurePreloadingWithCaching: Deleting buffer...\r\n");
		delete []buffer;
	}
	catch (exception)
	{
		ChromaLogger::fwprintf(stderr, L"UnitTestsMeasurePreloadingWithCaching: Exception path=%s\r\n", path);
	}

	if (stream != nullptr)
	{
		fclose(stream);
	}

	ChromaLogger::wprintf(L"UnitTestsMeasurePreloadingWithCaching: Complete!\r\n");
}

void UnitTests::UnitTestsMeasureGetAnimation()
{
	const wchar_t* path = L"Animations/Rainbow_Keyboard.chroma";

	// measure performance

	ChromaLogger::wprintf(L"Measure [GetAnimation()] elapsed time...\r\n");
	for (int i = 0; i < 10; ++i)
	{
		// get current time
		high_resolution_clock::time_point timer = high_resolution_clock::now();

		// open the animation
		ChromaAnimationAPI::GetAnimation(path);

		// get time in seconds
		duration<double, milli> time_span = high_resolution_clock::now() - timer;
		float deltaTime = (float)(time_span.count() / 1000.0f);
		ChromaLogger::wprintf(L"GetAnimation() elapsed time: %f\r\n", deltaTime);

		Sleep(500);

		// close animation
		ChromaAnimationAPI::CloseAnimationName(path);
	}

	ChromaLogger::wprintf(L"UnitTestsMeasureGetAnimation: Complete!\r\n");
}

void UnitTests::UnitTestsMeasureGetAnimationWithCaching()
{
	const wchar_t* path = L"Animations/Rainbow_Keyboard.chroma";
	FILE* stream = nullptr;
	try
	{
		if (0 != _wfopen_s(&stream, path, L"rb") ||
			stream == nullptr)
		{
			ChromaLogger::fwprintf(stderr, L"UnitTestsMeasureGetAnimationWithCaching: Failed to open animation! %s\r\n", path);
			return;
		}

		ChromaLogger::wprintf(L"UnitTestsMeasureGetAnimationWithCaching: Reading animation file contents...\r\n");

		vector<BYTE> lstBuffer;

		BYTE data = 0;
		size_t read = 0;
		do
		{
			read = fread(&data, sizeof(BYTE), 1, stream);
			lstBuffer.push_back(data);
		} while (read != 0);

		ChromaLogger::fwprintf(stderr, L"UnitTestsMeasureGetAnimationWithCaching: File size is! %d\r\n", (int)lstBuffer.size());

		BYTE* buffer = new BYTE[lstBuffer.size()];
		copy(lstBuffer.begin(), lstBuffer.end(), buffer);

		ChromaLogger::wprintf(L"UnitTestsMeasureGetAnimationWithCaching: Opening file from buffer...\r\n");

		const wchar_t* name = L"MemoryAnimation.chroma";

		// measure performance

		float total = 0;

		ChromaLogger::wprintf(L"Measure [GetAnimation()] elapsed time...\r\n");
		int tries = 1000;
		for (int i = 0; i < tries; ++i)
		{
			// get current time
			high_resolution_clock::time_point timer = high_resolution_clock::now();

			// open the animation
			int animationId = ChromaAnimationAPI::OpenAnimationFromMemory(buffer, name);

			// no need to load the animation

			// get time in seconds
			duration<double, milli> time_span = high_resolution_clock::now() - timer;
			float deltaTime = (float)(time_span.count() / 1000.0f);
			total += deltaTime;
			ChromaLogger::wprintf(L"%d GetAnimation() elapsed time: %f average: %f\r\n", i, deltaTime, total / (float)(i+1));

			Sleep(500);

			// close animation
			ChromaAnimationAPI::CloseAll();
		}

		// clear buffer for loading from memory
		ChromaLogger::wprintf(L"UnitTestsMeasureGetAnimationWithCaching: Deleting buffer...\r\n");
		delete []buffer;
	}
	catch (exception)
	{
		ChromaLogger::fwprintf(stderr, L"UnitTestsMeasureGetAnimationWithCaching: Exception path=%s\r\n", path);
	}

	if (stream != nullptr)
	{
		fclose(stream);
	}

	ChromaLogger::wprintf(L"UnitTestsMeasureGetAnimationWithCaching: Complete!\r\n");
}

void UnitTests::UnitTestsCopyKeysColorAllFramesName()
{
	const wchar_t* baseLayer = L"Animations/Spiral_Keyboard.chroma";
	const wchar_t* layer2 = L"Animations/Rainbow_Keyboard.chroma";
	ChromaAnimationAPI::CloseAnimationName(baseLayer);
	ChromaAnimationAPI::CloseAnimationName(layer2);
	ChromaAnimationAPI::GetAnimation(baseLayer);
	ChromaAnimationAPI::GetAnimation(layer2);
	int color1 = ChromaAnimationAPI::GetRGB(32, 32, 32);
	int color2 = ChromaAnimationAPI::GetRGB(64, 64, 64);
	ChromaAnimationAPI::MultiplyTargetColorLerpAllFramesName(baseLayer, color1, color2);
	int keys[] = {
	 Keyboard::RZKEY::RZKEY_W,
	 Keyboard::RZKEY::RZKEY_A,
	 Keyboard::RZKEY::RZKEY_S,
	 Keyboard::RZKEY::RZKEY_D,
	 Keyboard::RZKEY::RZKEY_P,
	 Keyboard::RZKEY::RZKEY_M,
	 Keyboard::RZKEY::RZKEY_F1,
	};
	ChromaAnimationAPI::CopyKeysColorAllFramesName(layer2, baseLayer, keys, (int)size(keys));
	ChromaAnimationAPI::SetChromaCustomFlagName(baseLayer, true);
	ChromaAnimationAPI::SetChromaCustomColorAllFramesName(baseLayer);
	ChromaAnimationAPI::OverrideFrameDurationName(baseLayer, 0.033f);
	ChromaAnimationAPI::PlayAnimationName(baseLayer, true);

	ChromaLogger::wprintf(L"Done.\r\n");
	Sleep(60000);
}

void UnitTests::UnitTestsFrameValidation()
{
	const wchar_t* path = L"Animations/FrameValidation_Keyboard.chroma";
	
	// unload the animation (shouldn't be loaded)
	ChromaAnimationAPI::UnloadAnimationName(path);

	// close animation before test
	ChromaAnimationAPI::CloseAnimationName(path);

	// open the animation
	ChromaAnimationAPI::GetAnimation(path);

	//ChromaLogger::wprintf(L"Set Frame: 23\r\n");	
	//ChromaAnimationAPI::SetCurrentFrameName(path, 23);
	//ChromaAnimationAPI::PreviewFrameName(path, 23);
	//Sleep(1000);

	//ChromaLogger::wprintf(L"Set Frame: 24\r\n");
	//ChromaAnimationAPI::SetCurrentFrameName(path, 24);
	//ChromaAnimationAPI::PreviewFrameName(path, 24);
	//Sleep(1000);

	ChromaAnimationAPI::UsePreloadingName(path, false);

	ChromaAnimationAPI::OverrideFrameDurationName(path, 0.033f);
	ChromaAnimationAPI::PlayAnimationName(path, true);

	ChromaLogger::wprintf(L"Done.\r\n");
	Sleep(60000);
}

void UnitTests::UnitTestsSpecialCharacters()
{
	ChromaLogger::wprintf(L"Play animation with special characters in path.\r\n");
	ChromaAnimationAPI::PlayComposite(L"Animations/André/Message", false);
	Sleep(3000);
}

void UnitTests::Run()
{
	ChromaLogger::wprintf(L"Start of unit tests...\r\n");
	//UnitTestsInit();
	UnitTestsInitSDK();

	if (!ChromaAnimationAPI::IsInitialized())
	{
		ChromaLogger::wprintf(L"Library hasn't loaded, aborting unit tests...\r\n");
		return;
	}

	//UnitTestsLoadedAnimations();
	//UnitTestsDamage();
	//UnitTestFireKeyboard();
	//UnitTestsOpenAnimationFromMemory();
	//UnitTestsFadeStart();
	//UnitTestsFadeEnd();
	//UnitTestsCopyAnimation();
	//UnitTestsSaveAnimation();
	//UnitTestsSaveAnimation2();
	//UnitTestsDuplicateFirstFrame();
	//UnitTestsCreateRandomBlackAndWhite();
	//UnitTestsKeyboardCustom();
	//UnitTestsPlayComposite();
	//UnitTestsHDKIndividualLEDsGradient();
	//UnitTestsHDKIndividualLEDs();
	//UnitTestsOffset();
	//UnitTestsNonZero();
	//UnitTestsCreateAnimation();
	//UnitTestsMeasurePreloading();
	//UnitTestsMeasurePreloadingWithCaching();
	//UnitTestsMeasureGetAnimation();
	//UnitTestsMeasureGetAnimationWithCaching();
	//UnitTestsIdleAnimation();
	//UnitTestsFrameValidation();

	//UnitTestsCopyKeysColorAllFramesName();

	UnitTestsSpecialCharacters();

	UnitTestsUninit();

	while (true)
	{
		Sleep(1000);
	}
}
