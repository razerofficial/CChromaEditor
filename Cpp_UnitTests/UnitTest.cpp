#include "ChromaAnimationAPI.h"
#include "UnitTests.h"
#include "ChromaLogger.h"
#include "HandleInput.h"

#include <chrono>
#include <string>
#include <thread>
#include <tchar.h>
#include <vector>


using namespace std;
using namespace std::chrono;
using namespace ChromaSDK;

const float MATH_PI = 3.14159f;


void UnitTests::IsPlaying(const char* name)
{
	printf("%s_ChromaLink IsPlayingName: %s\r\n", name, ChromaAnimationAPI::IsPlayingName("Random_Keyboard.chroma") ? "true" : "false");
	printf("%s_Headset IsPlayingName: %s\r\n", name, ChromaAnimationAPI::IsPlayingName("Random_Keyboard.chroma") ? "true" : "false");
	printf("%s_Keyboard IsPlayingName: %s\r\n", name, ChromaAnimationAPI::IsPlayingName("Random_Keyboard.chroma") ? "true" : "false");
	printf("%s_Keypad IsPlayingName: %s\r\n", name, ChromaAnimationAPI::IsPlayingName("Random_Keyboard.chroma") ? "true" : "false");
	printf("%s_Mouse IsPlayingName: %s\r\n", name, ChromaAnimationAPI::IsPlayingName("Random_Keyboard.chroma") ? "true" : "false");
	printf("%s_Mousepad IsPlayingName: %s\r\n", name, ChromaAnimationAPI::IsPlayingName("Random_Keyboard.chroma") ? "true" : "false");

	printf("ChromaLink IsPlayingType: %s\r\n", ChromaAnimationAPI::IsPlayingType((int)EChromaSDKDeviceTypeEnum::DE_1D, (int)EChromaSDKDevice1DEnum::DE_ChromaLink) ? "true" : "false");
	printf("Headset IsPlayingType: %s\r\n", ChromaAnimationAPI::IsPlayingType((int)EChromaSDKDeviceTypeEnum::DE_1D, (int)EChromaSDKDevice1DEnum::DE_Headset) ? "true" : "false");
	printf("Keyboard IsPlayingType: %s\r\n", ChromaAnimationAPI::IsPlayingType((int)EChromaSDKDeviceTypeEnum::DE_2D, (int)EChromaSDKDevice2DEnum::DE_Keyboard) ? "true" : "false");
	printf("Keypad IsPlayingType: %s\r\n", ChromaAnimationAPI::IsPlayingType((int)EChromaSDKDeviceTypeEnum::DE_2D, (int)EChromaSDKDevice2DEnum::DE_Keypad) ? "true" : "false");
	printf("Mouse IsPlayingType: %s\r\n", ChromaAnimationAPI::IsPlayingType((int)EChromaSDKDeviceTypeEnum::DE_2D, (int)EChromaSDKDevice2DEnum::DE_Mouse) ? "true" : "false");
	printf("Mousepad IsPlayingType: %s\r\n", ChromaAnimationAPI::IsPlayingType((int)EChromaSDKDeviceTypeEnum::DE_1D, (int)EChromaSDKDevice1DEnum::DE_Mousepad) ? "true" : "false");
}

void UnitTests::UnitTestsInit()
{
	RZRESULT result = ChromaAnimationAPI::Init();
	printf("Init result=%ld\r\n", result);

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
		printf("UnitTests::UnitTestsInitSDK result=%ld\r\n", result);
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

	printf("Unit Tests have completed!\r\n");
}

void UnitTests::UnitTestsPlayComposite()
{
	printf("Measure CPU usage.\r\n");
	const char* RANDOM_COMPOSITE = "Animations/Random";
	ChromaAnimationAPI::PlayComposite(RANDOM_COMPOSITE, true);
}

void UnitTests::UnitTestsOpenDialog()
{
	ChromaAnimationAPI::OpenEditorDialog("RandomKeyboardEffect.chroma");
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
			printf("Init...\r\n");
			ChromaAnimationAPI::Init();
		}

		printf("Playing effects...\r\n");
		int randomChromaLinkEffect = OpenAndPlay("Animations/Random_ChromaLink.chroma");
		int randomHeadsetEffect = OpenAndPlay("Animations/Random_Headset.chroma");
		int randomKeyboardEffect = OpenAndPlay("Animations/Random_Keyboard.chroma");
		int randomKeypadEffect = OpenAndPlay("Animations/Random_Keypad.chroma");
		int randomMouseEffect = OpenAndPlay("Animations/Random_Mouse.chroma");
		int randomMousepadEffect = OpenAndPlay("Animations/Random_Mousepad.chroma");
		this_thread::sleep_for(chrono::seconds(1));

		ChromaAnimationAPI::CloseAnimation(randomChromaLinkEffect);
		ChromaAnimationAPI::CloseAnimation(randomHeadsetEffect);
		ChromaAnimationAPI::CloseAnimation(randomKeyboardEffect);
		ChromaAnimationAPI::CloseAnimation(randomKeypadEffect);
		ChromaAnimationAPI::CloseAnimation(randomMouseEffect);
		ChromaAnimationAPI::CloseAnimation(randomMousepadEffect);

		printf("Simulate exit...\r\n");
		ChromaAnimationAPI::Uninit();
	}
}

void UnitTests::UnitTestsLayering()
{
	const char* BLANK_KEYBOARD = "Animations/Blank_Keyboard.chroma";
	const char* RANDOM_KEYBOARD = "Animations/Random_Keyboard.chroma";

	const char* animationName = "";
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

	printf("Playing animation %s.\r\n", animationName);
	ChromaAnimationAPI::CopyNonZeroAllKeysAllFramesName(RANDOM_KEYBOARD, BLANK_KEYBOARD);
	ChromaAnimationAPI::PlayAnimationName(animationName, false);
	Sleep(10000);
	ChromaAnimationAPI::CloseAnimationName(animationName);
}

void UnitTests::UnitTestsLoadedAnimations()
{
	const char* BLANK_KEYBOARD = "Animations/Blank_Keyboard.chroma";
	const char* BLANK_COMPOSITE = "Animations/Blank";
	const char* RANDOM_KEYBOARD = "Animations/Random_Keyboard.chroma";
	const char* RANDOM_COMPOSITE = "Animations/Random";
	const char* animationName = "";
	int animationId = -1;

	ChromaAnimationAPI::PlayComposite(BLANK_COMPOSITE, false);
	ChromaAnimationAPI::PlayComposite(RANDOM_COMPOSITE, true);
	Sleep(500);
	int count = ChromaAnimationAPI::GetAnimationCount();
	printf("[%d] animation(s) are open.\r\n", count);
	for (int i = 0; i < count; ++i)
	{
		animationId = ChromaAnimationAPI::GetAnimationId(i);
		if (animationId < 0)
		{
			continue;
		}
		animationName = ChromaAnimationAPI::GetAnimationName(animationId);
		printf("Animation is open: [%d] %s\r\n", animationId, animationName);
	}
	printf("Closing open animations...\r\n");
	ChromaAnimationAPI::CloseAll();
	count = ChromaAnimationAPI::GetAnimationCount();
	printf("[%d] animation(s) are open.\r\n", count);
	printf("All animations are closed.\r\n");

	animationName = RANDOM_KEYBOARD;
	printf("Playing animation %s.\r\n", animationName);
	ChromaAnimationAPI::PlayAnimationName(animationName, false);
	while (ChromaAnimationAPI::IsPlayingName(animationName))
	{
		printf("Animation is playing... %s.\r\n", animationName);
		Sleep(1000);
	}
	printf("Animation complete %s.\r\n", animationName);
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

	const char* BLANK_KEYBOARD = "Animations/Blank_Keyboard.chroma";
	const char* BLANK_COMPOSITE = "Animations/Blank";
	const char* RANDOM_KEYBOARD = "Animations/Random_Keyboard.chroma";
	const char* RANDOM_COMPOSITE = "Animations/Random";
	const char* animationName = "";
	const char* compositeName = "";
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
	const char* BLANK_KEYBOARD = "Animations/Blank_Keyboard.chroma";
	const char* BLANK_COMPOSITE = "Animations/Blank";
	const char* RANDOM_KEYBOARD = "Animations/Random_Keyboard.chroma";
	const char* RANDOM_COMPOSITE = "Animations/Random";
	const char* animationName = "";
	const char* compositeName = "";
	int animationId = -1;

	printf("Playing animation.\r\n");
	ChromaAnimationAPI::PlayAnimationName(RANDOM_KEYBOARD, false);
	Sleep(100);

	printf("Clearing animations.\r\n");
	ChromaAnimationAPI::ClearAll();

	Sleep(1000);

	printf("Playing animations.\r\n");
	ChromaAnimationAPI::PlayComposite("Random", false);
	Sleep(100);

	for (int wait = 0; wait < 3; ++wait)
	{
		int count = ChromaAnimationAPI::GetAnimationCount();
		printf("[%d] animation(s) are open.\r\n", count);
		for (int i = 0; i < count; ++i)
		{
			animationId = ChromaAnimationAPI::GetAnimationId(i);
			if (animationId < 0)
			{
				continue;
			}
			animationName = ChromaAnimationAPI::GetAnimationName(animationId);
			printf("Animation is open: [%d] %s\r\n", animationId, animationName);
		}
		Sleep(500);
	}

	for (int wait = 0; wait < 10; ++wait)
	{
		int count = ChromaAnimationAPI::GetPlayingAnimationCount();
		printf("[%d] animation(s) are playing.\r\n", count);
		for (int i = 0; i < count; ++i)
		{
			animationId = ChromaAnimationAPI::GetPlayingAnimationId(i);
			if (animationId < 0)
			{
				continue;
			}

			animationName = ChromaAnimationAPI::GetAnimationName(animationId);
			printf("Animation is playing: [%d] %s\r\n", animationId, animationName);
		}
		if (ChromaAnimationAPI::GetPlayingAnimationCount() == 0)
		{
			printf("No animations are playing.\r\n");
		}
		Sleep(500);
	}

	ChromaAnimationAPI::ClearAll();

	Sleep(3000);
}

void UnitTests::UnitTestsWait()
{
	const char* BLANK_KEYBOARD = "Animations/Blank_Keyboard.chroma";
	const char* BLANK_COMPOSITE = "Animations/Blank";
	const char* RANDOM_KEYBOARD = "Animations/Random_Keyboard.chroma";
	const char* RANDOM_COMPOSITE = "Animations/Random";
	const char* animationName = "";
	int animationId = -1;

	printf("Playing animation.\r\n");
	ChromaAnimationAPI::PlayAnimationName(RANDOM_KEYBOARD, false);
	Sleep(100);

	printf("Clearing animations.\r\n");
	ChromaAnimationAPI::ClearAll();

	Sleep(1000);

	printf("Playing animations.\r\n");
	ChromaAnimationAPI::PlayComposite("Random", false);
	Sleep(100);

	for (int wait = 0; wait < 3; ++wait)
	{
		int count = ChromaAnimationAPI::GetAnimationCount();
		printf("[%d] animation(s) are open.\r\n", count);
		for (int i = 0; i < count; ++i)
		{
			animationId = ChromaAnimationAPI::GetAnimationId(i);
			if (animationId < 0)
			{
				continue;
			}
			animationName = ChromaAnimationAPI::GetAnimationName(animationId);
			printf("Animation is open: [%d] %s\r\n", animationId, animationName);
		}
		Sleep(500);
	}

	for (int wait = 0; wait < 10; ++wait)
	{
		int count = ChromaAnimationAPI::GetPlayingAnimationCount();
		printf("[%d] animation(s) are playing.\r\n", count);
		for (int i = 0; i < count; ++i)
		{
			animationId = ChromaAnimationAPI::GetPlayingAnimationId(i);
			if (animationId < 0)
			{
				continue;
			}

			animationName = ChromaAnimationAPI::GetAnimationName(animationId);
			printf("Animation is playing: [%d] %s\r\n", animationId, animationName);
		}
		if (ChromaAnimationAPI::GetPlayingAnimationCount() == 0)
		{
			printf("No animations are playing.\r\n");
		}
		Sleep(500);
	}

	ChromaAnimationAPI::ClearAll();

	Sleep(3000);

	printf("Playing animation.\r\n");
	ChromaAnimationAPI::PlayAnimationName(RANDOM_KEYBOARD, false);
	Sleep(100);
}

void UnitTests::UnitTestsCopy()
{
	const char* RANDOM_KEYBOARD = "Animations/Random_Keyboard.chroma";

	int frameCount = ChromaAnimationAPI::GetFrameCountName(RANDOM_KEYBOARD);
	for (int index = 0; index < frameCount; ++index)
	{
		ChromaAnimationAPI::CopyKeyColorName("Fire_Keyboard.chroma", RANDOM_KEYBOARD, index, (int)Keyboard::RZKEY::RZKEY_W);
		ChromaAnimationAPI::CopyKeyColorName("Fire_Keyboard.chroma", RANDOM_KEYBOARD, index, (int)Keyboard::RZKEY::RZKEY_A);
		ChromaAnimationAPI::CopyKeyColorName("Fire_Keyboard.chroma", RANDOM_KEYBOARD, index, (int)Keyboard::RZKEY::RZKEY_S);
		ChromaAnimationAPI::CopyKeyColorName("Fire_Keyboard.chroma", RANDOM_KEYBOARD, index, (int)Keyboard::RZKEY::RZKEY_D);
	}
	ChromaAnimationAPI::PlayAnimationName(RANDOM_KEYBOARD, true);
	Sleep(3000);

	ChromaAnimationAPI::CloseAnimationName(RANDOM_KEYBOARD);
}

void UnitTests::UnitTestsMisc()
{
	const char* RANDOM_KEYBOARD = "Animations/Random_Keyboard.chroma";

	printf("Call: PlayComposite: Random\r\n");
	ChromaAnimationAPI::PlayComposite("Random", true);
	IsPlaying("Random");
	Sleep(3000);

	printf("Call: StopComposite\r\n");
	ChromaAnimationAPI::StopComposite("Random");
	IsPlaying("Random");
	Sleep(3000);

	printf("Call: PlayComposite: Blank\r\n");
	ChromaAnimationAPI::PlayComposite("Blank", false);
	IsPlaying("Random"); //random should show false, type should be playing blank
	Sleep(3000);

	printf("Call: PlayAnimationName\r\n");
	ChromaAnimationAPI::PlayAnimationName(RANDOM_KEYBOARD, true);
	Sleep(3000);

	printf("Call: StopAnimationName\r\n");
	ChromaAnimationAPI::StopAnimationName(RANDOM_KEYBOARD);
	Sleep(1000);

	printf("Call: PlayAnimationName\r\n");
	ChromaAnimationAPI::PlayAnimationName(RANDOM_KEYBOARD, true);
	Sleep(3000);

	printf("Call: StopAnimationType\r\n");
	ChromaAnimationAPI::StopAnimationType((int)EChromaSDKDeviceTypeEnum::DE_2D, (int)EChromaSDKDevice2DEnum::DE_Keyboard);
}

void UnitTests::UnitTestsOffset()
{
	printf("Start of offset unit test.\r\n");

	const char* RANDOM_KEYBOARD = "Animations/Random_Keyboard.chroma";

	const char* animationName = RANDOM_KEYBOARD;
	ChromaAnimationAPI::CloseAnimationName(animationName);

	int animationId = ChromaAnimationAPI::OpenAnimation(animationName);

	int frameCount = ChromaAnimationAPI::GetFrameCountName(animationName);

	printf("Set all frames white with FillColor.\r\n");
	ChromaAnimationAPI::FillColorAllFramesRGBName(animationName, 255, 255, 255);

	printf("Fade out black with MultiplyIntensity.\r\n");
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

	printf("Set all frames black with FillColor.\r\n");
	ChromaAnimationAPI::UnloadAnimationName(animationName);
	ChromaAnimationAPI::FillColorAllFramesRGBName(animationName, 0, 0, 0);

	printf("Fade in red with FillColor.\r\n");
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

	printf("Set all frames red with FillColor.\r\n");
	ChromaAnimationAPI::FillColorAllFramesRGBName(animationName, 255, 0, 0);

	printf("Fade in green with OffsetColors.\r\n");
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

	printf("Set all frames yellow with FillColor.\r\n");
	ChromaAnimationAPI::FillColorAllFramesRGBName(animationName, 255, 255, 0);

	printf("Fade out red with OffsetColors.\r\n");
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

	printf("Set all frames green with FillColor.\r\n");
	ChromaAnimationAPI::FillColorAllFramesRGBName(animationName, 0, 255, 0);

	printf("Fade in white with OffsetColors.\r\n");
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

	printf("End of offset unit test.\r\n");
}

void UnitTests::UnitTestsNonZero()
{
	printf("Start of nonzero unit test.\r\n");

	const int COLOR_WHITE = 0xFFFFFF;

	int wasdKeys[4] =
	{
		(int)Keyboard::RZKEY::RZKEY_W,
		(int)Keyboard::RZKEY::RZKEY_A,
		(int)Keyboard::RZKEY::RZKEY_S,
		(int)Keyboard::RZKEY::RZKEY_D,
	};

	const char* SPRITE_KEYBOARD = "Animations/Sprite_Keyboard.chroma";
	const char* WAVE_KEYBOARD = "Animations/Rows_Keyboard.chroma";

	const char* animationName = WAVE_KEYBOARD;
	int animationId = ChromaAnimationAPI::OpenAnimation(animationName);

	// Reload from disk
	ChromaAnimationAPI::CloseAnimationName(animationName);

	int frameCount = ChromaAnimationAPI::GetFrameCountName(animationName);

	printf("Fade out red.\r\n");
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
	printf("Red should be gone.\r\n");
	Sleep(3000);

	printf("Fade out green.\r\n");
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
	printf("Green should be gone.\r\n");
	Sleep(3000);

	printf("Fade out blue.\r\n");
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
	printf("Blue should be gone.\r\n");
	Sleep(3000);

	printf("Non zero keys should fade in to white.\r\n");
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

	printf("WASD keys should be white every other frame.\r\n");
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

	printf("WASD keys should be white every other frame.\r\n");
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

	printf("End of nonzero unit test.\r\n");
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

	printf("Create random HDK LED colors effect.\r\n");

	FChromaSDKGuid effectId = FChromaSDKGuid();
	ChromaAnimationAPI::CreateEffect(CHROMABOX, EFFECT_TYPE::CHROMA_CUSTOM, colors, size, &effectId);

	printf("Set HDK Effect.\r\n");

	ChromaAnimationAPI::SetEffect(effectId);

	Sleep(3000);

	printf("Delete HDK Effect.\r\n");

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

	printf("Create HDK gradient.\r\n");

	FChromaSDKGuid effectId = FChromaSDKGuid();
	ChromaAnimationAPI::CreateEffect(CHROMABOX, EFFECT_TYPE::CHROMA_CUSTOM, colors, size, &effectId);

	printf("Set HDK Effect.\r\n");

	ChromaAnimationAPI::SetEffect(effectId);

	Sleep(3000);

	printf("Delete HDK Effect.\r\n");

	ChromaAnimationAPI::DeleteEffect(effectId);

	Sleep(1000);

	delete []colors;
}

void UnitTests::UnitTestsCreateAnimation()
{
	const char* animationName = "Animations/New_ChromaLink.chroma";
	int animationId = ChromaAnimationAPI::CreateAnimation(animationName, (int)EChromaSDKDeviceTypeEnum::DE_1D, (int)EChromaSDKDevice1DEnum::DE_ChromaLink);
	if (animationId < 0)
	{
		fprintf(stderr, "Failed to create animation! %s\r\n", animationName);
	}
}

void UnitTests::UnitTestsKeyboardCustom()
{
	printf("Clear all.\r\n");
	ChromaAnimationAPI::ClearAll();
	Sleep(3000);

	printf("Show custom keyboard keys Z N M LALT.\r\n");
	int animationId = ChromaAnimationAPI::CreateAnimationInMemory((int)EChromaSDKDeviceTypeEnum::DE_2D, (int)EChromaSDKDevice2DEnum::DE_Keyboard);
	ChromaAnimationAPI::SetChromaCustomFlag(animationId, true);
	ChromaAnimationAPI::SetKeyColor(animationId, 0, (int)Keyboard::RZKEY::RZKEY_Z, 0x01FF0000);
	ChromaAnimationAPI::SetKeyColor(animationId, 0, (int)Keyboard::RZKEY::RZKEY_N, 0x0100FF00);
	ChromaAnimationAPI::SetKeyColor(animationId, 0, (int)Keyboard::RZKEY::RZKEY_M, 0x010000FF);
	ChromaAnimationAPI::SetKeyColor(animationId, 0, (int)Keyboard::RZKEY::RZKEY_LALT, 0x01FFFFFF);
	printf("Play animation with custom keys.\r\n");
	ChromaAnimationAPI::PlayAnimation(animationId);
	Sleep(2000);
	printf("Preview frame with custom keys.\r\n");
	ChromaAnimationAPI::PreviewFrame(animationId, 0);
	Sleep(2000);
	ChromaAnimationAPI::CloseAnimation(animationId);

	printf("Clear all.\r\n");
	ChromaAnimationAPI::ClearAll();
	Sleep(3000);

	printf("Show custom keyboard keys LCTRL X C V B.\r\n");
	animationId = ChromaAnimationAPI::CreateAnimationInMemory((int)EChromaSDKDeviceTypeEnum::DE_2D, (int)EChromaSDKDevice2DEnum::DE_Keyboard);
	ChromaAnimationAPI::SetChromaCustomFlag(animationId, true);
	ChromaAnimationAPI::SetKeyColor(animationId, 0, (int)Keyboard::RZKEY::RZKEY_LCTRL, 0x01FF0000);
	ChromaAnimationAPI::SetKeyColor(animationId, 0, (int)Keyboard::RZKEY::RZKEY_X, 0x0100FF00);
	ChromaAnimationAPI::SetKeyColor(animationId, 0, (int)Keyboard::RZKEY::RZKEY_C, 0x010000FF);
	ChromaAnimationAPI::SetKeyColor(animationId, 0, (int)Keyboard::RZKEY::RZKEY_V, 0x01FFFFFF);
	ChromaAnimationAPI::SetKeyColor(animationId, 0, (int)Keyboard::RZKEY::RZKEY_B, 0x01FFFF00);
	printf("Play animation with custom keys.\r\n");
	ChromaAnimationAPI::PlayAnimation(animationId);
	Sleep(2000);
	printf("Preview frame with custom keys.\r\n");
	ChromaAnimationAPI::PreviewFrame(animationId, 0);
	Sleep(2000);
	ChromaAnimationAPI::CloseAnimation(animationId);

	printf("Clear all.\r\n");
	ChromaAnimationAPI::ClearAll();
	Sleep(3000);
}

void UnitTests::UnitTestsFadeStart()
{
	const char* baseLayer = "Animations/Blank_Keyboard.chroma";
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
	const char* baseLayer = "Animations/Blank_Keyboard.chroma";
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
	const char* baseLayer = "Animations/Fire_Keyboard.chroma";
	const char* layerTemp = "TempLayer";
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

	ChromaAnimationAPI::SaveAnimation(baseAnimation, "SaveAnimation.chroma");

	// get time in seconds
	duration<double, milli> time_span = high_resolution_clock::now() - timer;
	float deltaTime = (float)(time_span.count() / 1000.0f);
	printf("Elapsed time: %f\r\n", deltaTime);

	ChromaAnimationAPI::PlayAnimationLoop(baseAnimation, true);

	Sleep(3000);

	ChromaAnimationAPI::CloseAnimation(baseAnimation);

	Sleep(1000);
}

void UnitTests::UnitTestsSaveAnimation2()
{
	const char* baseLayer = "Animations/Fire_Keyboard.chroma";
	ChromaAnimationAPI::CloseAnimationName(baseLayer);
	ChromaAnimationAPI::GetAnimation(baseLayer);

	ChromaAnimationAPI::MultiplyIntensityAllFramesRGBName(baseLayer, 255, 0, 0);

	ChromaAnimationAPI::SetChromaCustomFlagName(baseLayer, true);
	ChromaAnimationAPI::SetChromaCustomColorAllFramesName(baseLayer);
	ChromaAnimationAPI::OverrideFrameDurationName(baseLayer, 0.033f);

	ChromaAnimationAPI::SaveAnimationName(baseLayer, "SaveAnimation.chroma");

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
	printf("Elapsed time: %f\r\n", deltaTime);

	Sleep(3000);

	ChromaAnimationAPI::CloseAnimation(baseAnimation);

	Sleep(1000);
}

void UnitTests::UnitTestsDuplicateFirstFrame()
{
	const char* baseLayer = "Animations/CircleSmall_Keyboard.chroma";
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

int UnitTests::OpenAndPlay(const char* path)
{
	int animationId = (int)ChromaAnimationAPI::OpenAnimation(path);
	printf("OpenAnimation: %s result=%d\r\n", path, animationId);
	if (animationId >= 0)
	{
		int result = (int)ChromaAnimationAPI::PlayAnimation(animationId);
		printf("PlayAnimation: %d result=%d\r\n", animationId, result);
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
	printf("CloseAnimation: %d result=%d\r\n", animationId, result);
	return result;
}

void UnitTests::UnitTestsOpenAnimationFromMemory()
{
	const char* path = "Animations/Random_Keyboard.chroma";
	FILE* stream = nullptr;
	try
	{
		if (0 != fopen_s(&stream, path, "rb") ||
			stream == nullptr)
		{
			fprintf(stderr, "UnitTestsOpenAnimationFromMemory: Failed to open animation! %s\r\n", path);
			return;
		}

		printf("UnitTestsOpenAnimationFromMemory: Reading animation file contents...\r\n");

		vector<BYTE> lstBuffer;

		BYTE data = 0;
		size_t read = 0;
		do
		{
			read = fread(&data, sizeof(BYTE), 1, stream);
			lstBuffer.push_back(data);
		} while (read != 0);

 		fprintf(stderr, "UnitTestsOpenAnimationFromMemory: File size is! %d\r\n", (int)lstBuffer.size());

		BYTE* buffer = new BYTE[lstBuffer.size()];
		copy(lstBuffer.begin(), lstBuffer.end(), buffer);

		printf("UnitTestsOpenAnimationFromMemory: Opening file from buffer...\r\n");

		const char* name = "MemoryAnimation.chroma";
		ChromaAnimationAPI::OpenAnimationFromMemory(buffer, name);

		printf("UnitTestsOpenAnimationFromMemory: Deleting buffer...\r\n");

		delete []buffer;

		printf("UnitTestsOpenAnimationFromMemory: Playing animation...\r\n");

		ChromaAnimationAPI::PlayAnimationName(name, true);

		Sleep(5000);
	}
	catch (exception)
	{
		fprintf(stderr, "UnitTestsOpenAnimationFromMemory: Exception path=%s\r\n", path);
	}

	if (stream != nullptr)
	{
		fclose(stream);
	}

	printf("UnitTestsOpenAnimationFromMemory: Complete!\r\n");
}

void UnitTests::UnitTestsIdleAnimation()
{
	const char* randomAnimation = "Animations/Random_Keyboard.chroma";
	const char* idleAnimation = "Animations/Fire_Keyboard.chroma";

	const int delay = 3000;

	printf("Idle is [ON].\r\n");
	ChromaAnimationAPI::UseIdleAnimation((int)EChromaSDKDeviceEnum::DE_Keyboard, true);

	ChromaAnimationAPI::CloseAnimationName(idleAnimation);
	ChromaAnimationAPI::OverrideFrameDurationName(idleAnimation, 0.1f);
	ChromaAnimationAPI::SetIdleAnimationName(idleAnimation);
	
	ChromaAnimationAPI::CloseAnimationName(randomAnimation);
	ChromaAnimationAPI::OverrideFrameDurationName(randomAnimation, 0.1f);

	printf("Play random animation.\r\n");
	ChromaAnimationAPI::PlayAnimationName(randomAnimation, false);
	printf("Waiting 3 sec...\r\n");
	Sleep(delay);
	printf("\r\n");

	printf("Close idle animation while active...\r\n");
	ChromaAnimationAPI::CloseAnimationName(idleAnimation);
	ChromaAnimationAPI::OverrideFrameDurationName(idleAnimation, 0.1f);
	Sleep(delay);
	printf("\r\n");

	printf("Set idle animation.\r\n");
	ChromaAnimationAPI::SetIdleAnimationName(idleAnimation);

	printf("Play random animation.\r\n");
	ChromaAnimationAPI::PlayAnimationName(randomAnimation, false);
	printf("Waiting 3 sec...\r\n");
	Sleep(delay);
	printf("\r\n");

	printf("Play random animation.\r\n");
	ChromaAnimationAPI::PlayAnimationName(randomAnimation, false);
	printf("Waiting 3 sec...\r\n");
	Sleep(delay);
	printf("\r\n");

	printf("Clear all animations with idle [ON].\r\n");
	ChromaAnimationAPI::ClearAll();
	printf("Waiting 3 sec...\r\n");
	Sleep(delay);
	printf("\r\n");

	printf("Idle is [OFF].\r\n");
	ChromaAnimationAPI::UseIdleAnimation((int)EChromaSDKDeviceEnum::DE_Keyboard, false);
	ChromaAnimationAPI::ClearAll();
	printf("Waiting 3 sec...\r\n");
	Sleep(delay);
	printf("\r\n");
}

void UnitTests::UnitTestsDamage()
{
	vector<string> damageList;
	for (int i = 0; i < 8; ++i)
	{
		string name = "Animations/Damage";
		switch (i + 1)
		{
		case 1:
			name += "1";
			break;
		case 2:
			name += "2";
			break;
		case 3:
			name += "3";
			break;
		case 4:
			name += "4";
			break;
		case 5:
			name += "5";
			break;
		case 6:
			name += "6";
			break;
		case 7:
			name += "7";
			break;
		case 8:
			name += "8";
			break;
		}
		name += "_Keyboard.chroma";
		damageList.push_back(name);
	}

	int frameCount = 1;

	const char* BLANK_KEYBOARD = "Animations/Blank_Keyboard.chroma";
	ChromaAnimationAPI::GetAnimation(BLANK_KEYBOARD);

	const char* COPY_BLANK_KEYBOARD = "Copy_Blank_Keyboard.chroma";

	const char* RAINBOW_KEYBOARD = "Animations/Rainbow_Keyboard.chroma";

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

			string& name = damageList[i];

			string copy = "copy_";
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
	const char* path = "Animations/Fire_Keyboard.chroma";
	ChromaAnimationAPI::PlayAnimationName(path, false);
	Sleep(3000);
}

void UnitTests::UnitTestsMeasurePreloading()
{
	const char* RAINBOW_KEYBOARD = "Animations/Rainbow_Keyboard.chroma";

	printf("Measure [immediate mode] elapsed time...\r\n");
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
		printf("Immediate elapsed time: %f\r\n", deltaTime);

		Sleep(500);
	}

	printf("Measure [preload mode] elapsed time...\r\n");
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
		printf("Preload elapsed time: %f\r\n", deltaTime);

		Sleep(500);
	}
}

void UnitTests::UnitTestsMeasurePreloadingWithCaching()
{
	const char* path = "Animations/Rainbow_Keyboard.chroma";
	FILE* stream = nullptr;
	try
	{
		if (0 != fopen_s(&stream, path, "rb") ||
			stream == nullptr)
		{
			fprintf(stderr, "UnitTestsMeasurePreloadingWithCaching: Failed to open animation! %s\r\n", path);
			return;
		}

		printf("UnitTestsMeasurePreloadingWithCaching: Reading animation file contents...\r\n");

		vector<BYTE> lstBuffer;

		BYTE data = 0;
		size_t read = 0;
		do
		{
			read = fread(&data, sizeof(BYTE), 1, stream);
			lstBuffer.push_back(data);
		} while (read != 0);

		fprintf(stderr, "UnitTestsMeasurePreloadingWithCaching: File size is! %d\r\n", (int)lstBuffer.size());

		BYTE* buffer = new BYTE[lstBuffer.size()];
		copy(lstBuffer.begin(), lstBuffer.end(), buffer);

		printf("UnitTestsMeasurePreloadingWithCaching: Opening file from buffer...\r\n");

		const char* name = "MemoryAnimation.chroma";

		// measure performance

		printf("Measure [immediate mode] elapsed time...\r\n");
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
			printf("Immediate elapsed time: %f\r\n", deltaTime);

			Sleep(500);

			// close animation
			ChromaAnimationAPI::CloseAnimation(animationId);
		}

		printf("Measure [preload mode] elapsed time...\r\n");
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
			printf("Preload elapsed time: %f\r\n", deltaTime);

			Sleep(500);

			// close animation
			ChromaAnimationAPI::CloseAnimation(animationId);
		}

		// clear buffer for loading from memory
		printf("UnitTestsMeasurePreloadingWithCaching: Deleting buffer...\r\n");
		delete []buffer;
	}
	catch (exception)
	{
		fprintf(stderr, "UnitTestsMeasurePreloadingWithCaching: Exception path=%s\r\n", path);
	}

	if (stream != nullptr)
	{
		fclose(stream);
	}

	printf("UnitTestsMeasurePreloadingWithCaching: Complete!\r\n");
}

void UnitTests::UnitTestsMeasureGetAnimation()
{
	const char* path = "Animations/Rainbow_Keyboard.chroma";

	// measure performance

	printf("Measure [GetAnimation()] elapsed time...\r\n");
	for (int i = 0; i < 10; ++i)
	{
		// get current time
		high_resolution_clock::time_point timer = high_resolution_clock::now();

		// open the animation
		ChromaAnimationAPI::GetAnimation(path);

		// get time in seconds
		duration<double, milli> time_span = high_resolution_clock::now() - timer;
		float deltaTime = (float)(time_span.count() / 1000.0f);
		printf("GetAnimation() elapsed time: %f\r\n", deltaTime);

		Sleep(500);

		// close animation
		ChromaAnimationAPI::CloseAnimationName(path);
	}

	printf("UnitTestsMeasureGetAnimation: Complete!\r\n");
}

void UnitTests::UnitTestsMeasureGetAnimationWithCaching()
{
	const char* path = "Animations/Rainbow_Keyboard.chroma";
	FILE* stream = nullptr;
	try
	{
		if (0 != fopen_s(&stream, path, "rb") ||
			stream == nullptr)
		{
			fprintf(stderr, "UnitTestsMeasureGetAnimationWithCaching: Failed to open animation! %s\r\n", path);
			return;
		}

		printf("UnitTestsMeasureGetAnimationWithCaching: Reading animation file contents...\r\n");

		vector<BYTE> lstBuffer;

		BYTE data = 0;
		size_t read = 0;
		do
		{
			read = fread(&data, sizeof(BYTE), 1, stream);
			lstBuffer.push_back(data);
		} while (read != 0);

		fprintf(stderr, "UnitTestsMeasureGetAnimationWithCaching: File size is! %d\r\n", (int)lstBuffer.size());

		BYTE* buffer = new BYTE[lstBuffer.size()];
		copy(lstBuffer.begin(), lstBuffer.end(), buffer);

		printf("UnitTestsMeasureGetAnimationWithCaching: Opening file from buffer...\r\n");

		const char* name = "MemoryAnimation.chroma";

		// measure performance

		float total = 0;

		printf("Measure [GetAnimation()] elapsed time...\r\n");
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
			printf("%d GetAnimation() elapsed time: %f average: %f\r\n", i, deltaTime, total / (float)(i+1));

			Sleep(500);

			// close animation
			ChromaAnimationAPI::CloseAll();
		}

		// clear buffer for loading from memory
		printf("UnitTestsMeasureGetAnimationWithCaching: Deleting buffer...\r\n");
		delete []buffer;
	}
	catch (exception)
	{
		fprintf(stderr, "UnitTestsMeasureGetAnimationWithCaching: Exception path=%s\r\n", path);
	}

	if (stream != nullptr)
	{
		fclose(stream);
	}

	printf("UnitTestsMeasureGetAnimationWithCaching: Complete!\r\n");
}

void UnitTests::UnitTestsCopyKeysColorAllFramesName()
{
	const char* baseLayer = "Animations/Spiral_Keyboard.chroma";
	const char* layer2 = "Animations/Rainbow_Keyboard.chroma";
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

	printf("Done.\r\n");
	Sleep(60000);
}

void UnitTests::UnitTestsFrameValidation()
{
	const char* path = "Animations/FrameValidation_Keyboard.chroma";
	
	// unload the animation (shouldn't be loaded)
	ChromaAnimationAPI::UnloadAnimationName(path);

	// close animation before test
	ChromaAnimationAPI::CloseAnimationName(path);

	// open the animation
	ChromaAnimationAPI::GetAnimation(path);

	//printf("Set Frame: 23\r\n");	
	//ChromaAnimationAPI::SetCurrentFrameName(path, 23);
	//ChromaAnimationAPI::PreviewFrameName(path, 23);
	//Sleep(1000);

	//printf("Set Frame: 24\r\n");
	//ChromaAnimationAPI::SetCurrentFrameName(path, 24);
	//ChromaAnimationAPI::PreviewFrameName(path, 24);
	//Sleep(1000);

	ChromaAnimationAPI::UsePreloadingName(path, false);

	ChromaAnimationAPI::OverrideFrameDurationName(path, 0.033f);
	ChromaAnimationAPI::PlayAnimationName(path, true);

	printf("Done.\r\n");
	Sleep(60000);
}

void UnitTests::UnitTestsSpecialCharacters()
{
	printf("Play animation with special characters in path.\r\n");
	ChromaAnimationAPI::PlayComposite("Animations/André/Message", false);
	Sleep(3000);
}

void UnitTests::UnitTestsEmpty()
{
	printf("Open animations that don't exist.\r\n");
	ChromaAnimationAPI::PlayComposite("Animations/DO_NOT_EXIST", false);

	printf("Open animations with zero bytes.\r\n");
	ChromaAnimationAPI::PlayComposite("Animations/Empty", false);
	Sleep(3000);
}

void UnitTests::UnitTestsLarge()
{
	printf("Open large animations.\r\n");

	auto measureElapsed = [](const char* name)
	{
		high_resolution_clock::time_point timer = high_resolution_clock::now();
		ChromaAnimationAPI::OpenAnimation(name);
		duration<double, milli> timeSpan = high_resolution_clock::now() - timer;
		float deltaTime = (float)(timeSpan.count() / 1000.0f);
		printf("Elapsed time: %f %s\r\n", deltaTime, name);
	};

	high_resolution_clock::time_point timer = high_resolution_clock::now();

	measureElapsed("Animations/Large_ChromaLink.chroma");
	measureElapsed("Animations/Large_Headset.chroma");
	measureElapsed("Animations/Large_Keyboard.chroma");
	measureElapsed("Animations/Large_KeyboardExtended.chroma");
	measureElapsed("Animations/Large_Keypad.chroma");
	measureElapsed("Animations/Large_Mouse.chroma");
	measureElapsed("Animations/Large_Mousepad.chroma");

	duration<double, milli> timeSpan = high_resolution_clock::now() - timer;
	float deltaTime = (float)(timeSpan.count() / 1000.0f);
	printf("Opened large animations elapsed time: %f\r\n", deltaTime);

	Sleep(3000);
}

void UnitTests::UnitTests8x24Keys()
{
	int index = -1;

	vector<int> keys;
	keys.push_back(Keyboard::RZKEY::RZKEY_MACRO1);
	keys.push_back(Keyboard::RZKEY::RZKEY_MACRO2);
	keys.push_back(Keyboard::RZKEY::RZKEY_MACRO3);
	keys.push_back(Keyboard::RZKEY::RZKEY_MACRO4);
	keys.push_back(Keyboard::RZKEY::RZKEY_MACRO5);
	keys.push_back(Keyboard::RZKEY::RZKEY_ESC);
	keys.push_back(Keyboard::RZKEY::RZKEY_F1);
	keys.push_back(Keyboard::RZKEY::RZKEY_F2);
	keys.push_back(Keyboard::RZKEY::RZKEY_F3);
	keys.push_back(Keyboard::RZKEY::RZKEY_F4);
	keys.push_back(Keyboard::RZKEY::RZKEY_F5);
	keys.push_back(Keyboard::RZKEY::RZKEY_F6);
	keys.push_back(Keyboard::RZKEY::RZKEY_F7);
	keys.push_back(Keyboard::RZKEY::RZKEY_F8);
	keys.push_back(Keyboard::RZKEY::RZKEY_F9);
	keys.push_back(Keyboard::RZKEY::RZKEY_F10);
	keys.push_back(Keyboard::RZKEY::RZKEY_F11);
	keys.push_back(Keyboard::RZKEY::RZKEY_F12);
	keys.push_back(Keyboard::RZKEY::RZKEY_PRINTSCREEN);
	keys.push_back(Keyboard::RZKEY::RZKEY_SCROLL);
	keys.push_back(Keyboard::RZKEY::RZKEY_PAUSE);
	keys.push_back(Keyboard::RZKEY::RZKEY_OEM_1);
	keys.push_back(Keyboard::RZKEY::RZKEY_1);
	keys.push_back(Keyboard::RZKEY::RZKEY_2);
	keys.push_back(Keyboard::RZKEY::RZKEY_3);
	keys.push_back(Keyboard::RZKEY::RZKEY_4);
	keys.push_back(Keyboard::RZKEY::RZKEY_5);
	keys.push_back(Keyboard::RZKEY::RZKEY_6);
	keys.push_back(Keyboard::RZKEY::RZKEY_7);
	keys.push_back(Keyboard::RZKEY::RZKEY_8);
	keys.push_back(Keyboard::RZKEY::RZKEY_9);
	keys.push_back(Keyboard::RZKEY::RZKEY_0);
	keys.push_back(Keyboard::RZKEY::RZKEY_OEM_2);
	keys.push_back(Keyboard::RZKEY::RZKEY_OEM_3);
	keys.push_back(Keyboard::RZKEY::RZKEY_BACKSPACE);
	keys.push_back(Keyboard::RZKEY::RZKEY_INSERT);
	keys.push_back(Keyboard::RZKEY::RZKEY_HOME);
	keys.push_back(Keyboard::RZKEY::RZKEY_PAGEUP);
	keys.push_back(Keyboard::RZKEY::RZKEY_NUMLOCK);
	keys.push_back(Keyboard::RZKEY::RZKEY_NUMPAD_DIVIDE);
	keys.push_back(Keyboard::RZKEY::RZKEY_NUMPAD_MULTIPLY);
	keys.push_back(Keyboard::RZKEY::RZKEY_NUMPAD_SUBTRACT);
	keys.push_back(Keyboard::RZKEY::RZKEY_TAB);
	keys.push_back(Keyboard::RZKEY::RZKEY_Q);
	keys.push_back(Keyboard::RZKEY::RZKEY_W);
	keys.push_back(Keyboard::RZKEY::RZKEY_E);
	keys.push_back(Keyboard::RZKEY::RZKEY_R);
	keys.push_back(Keyboard::RZKEY::RZKEY_T);
	keys.push_back(Keyboard::RZKEY::RZKEY_Y);
	keys.push_back(Keyboard::RZKEY::RZKEY_U);
	keys.push_back(Keyboard::RZKEY::RZKEY_I);
	keys.push_back(Keyboard::RZKEY::RZKEY_O);
	keys.push_back(Keyboard::RZKEY::RZKEY_P);
	keys.push_back(Keyboard::RZKEY::RZKEY_OEM_4);
	keys.push_back(Keyboard::RZKEY::RZKEY_OEM_5);
	keys.push_back(Keyboard::RZKEY::RZKEY_OEM_6);
	keys.push_back(Keyboard::RZKEY::RZKEY_DELETE);
	keys.push_back(Keyboard::RZKEY::RZKEY_END);
	keys.push_back(Keyboard::RZKEY::RZKEY_PAGEDOWN);
	keys.push_back(Keyboard::RZKEY::RZKEY_NUMPAD7);
	keys.push_back(Keyboard::RZKEY::RZKEY_NUMPAD8);
	keys.push_back(Keyboard::RZKEY::RZKEY_NUMPAD9);
	keys.push_back(Keyboard::RZKEY::RZKEY_NUMPAD_ADD);
	keys.push_back(Keyboard::RZKEY::RZKEY_CAPSLOCK);
	keys.push_back(Keyboard::RZKEY::RZKEY_A);
	keys.push_back(Keyboard::RZKEY::RZKEY_S);
	keys.push_back(Keyboard::RZKEY::RZKEY_D);
	keys.push_back(Keyboard::RZKEY::RZKEY_F);
	keys.push_back(Keyboard::RZKEY::RZKEY_G);
	keys.push_back(Keyboard::RZKEY::RZKEY_H);
	keys.push_back(Keyboard::RZKEY::RZKEY_J);
	keys.push_back(Keyboard::RZKEY::RZKEY_K);
	keys.push_back(Keyboard::RZKEY::RZKEY_L);
	keys.push_back(Keyboard::RZKEY::RZKEY_OEM_7);
	keys.push_back(Keyboard::RZKEY::RZKEY_OEM_8);
	keys.push_back(Keyboard::RZKEY::RZKEY_ENTER);
	keys.push_back(Keyboard::RZKEY::RZKEY_NUMPAD4);
	keys.push_back(Keyboard::RZKEY::RZKEY_NUMPAD5);
	keys.push_back(Keyboard::RZKEY::RZKEY_NUMPAD6);
	keys.push_back(Keyboard::RZKEY::RZKEY_LSHIFT);
	keys.push_back(Keyboard::RZKEY::RZKEY_Z);
	keys.push_back(Keyboard::RZKEY::RZKEY_X);
	keys.push_back(Keyboard::RZKEY::RZKEY_C);
	keys.push_back(Keyboard::RZKEY::RZKEY_V);
	keys.push_back(Keyboard::RZKEY::RZKEY_B);
	keys.push_back(Keyboard::RZKEY::RZKEY_N);
	keys.push_back(Keyboard::RZKEY::RZKEY_M);
	keys.push_back(Keyboard::RZKEY::RZKEY_OEM_9);
	keys.push_back(Keyboard::RZKEY::RZKEY_OEM_10);
	keys.push_back(Keyboard::RZKEY::RZKEY_OEM_11);
	keys.push_back(Keyboard::RZKEY::RZKEY_RSHIFT);
	keys.push_back(Keyboard::RZKEY::RZKEY_UP);
	keys.push_back(Keyboard::RZKEY::RZKEY_NUMPAD1);
	keys.push_back(Keyboard::RZKEY::RZKEY_NUMPAD2);
	keys.push_back(Keyboard::RZKEY::RZKEY_NUMPAD3);
	keys.push_back(Keyboard::RZKEY::RZKEY_NUMPAD_ENTER);
	keys.push_back(Keyboard::RZKEY::RZKEY_LCTRL);
	keys.push_back(Keyboard::RZKEY::RZKEY_LWIN);
	keys.push_back(Keyboard::RZKEY::RZKEY_LALT);
	keys.push_back(Keyboard::RZKEY::RZKEY_SPACE);
	keys.push_back(Keyboard::RZKEY::RZKEY_RALT);
	keys.push_back(Keyboard::RZKEY::RZKEY_FN);
	keys.push_back(Keyboard::RZKEY::RZKEY_RMENU);
	keys.push_back(Keyboard::RZKEY::RZKEY_RCTRL);
	keys.push_back(Keyboard::RZKEY::RZKEY_LEFT);
	keys.push_back(Keyboard::RZKEY::RZKEY_DOWN);
	keys.push_back(Keyboard::RZKEY::RZKEY_RIGHT);
	keys.push_back(Keyboard::RZKEY::RZKEY_NUMPAD0);	
	keys.push_back(Keyboard::RZKEY::RZKEY_NUMPAD_DECIMAL);

	auto getKeyDescription = [] (int key) -> const wchar_t*
	{
		switch (key)
		{
		case Keyboard::RZKEY::RZKEY_ESC:
			return L"RZKEY_ESC";
		case Keyboard::RZKEY::RZKEY_F1:
			return L"RZKEY_F1";
		case Keyboard::RZKEY::RZKEY_F2:
			return L"RZKEY_F2";
		case Keyboard::RZKEY::RZKEY_F3:
			return L"RZKEY_F3";
		case Keyboard::RZKEY::RZKEY_F4:
			return L"RZKEY_F4";
		case Keyboard::RZKEY::RZKEY_F5:
			return L"RZKEY_F5";
		case Keyboard::RZKEY::RZKEY_F6:
			return L"RZKEY_F6";
		case Keyboard::RZKEY::RZKEY_F7:
			return L"RZKEY_F7";
		case Keyboard::RZKEY::RZKEY_F8:
			return L"RZKEY_F8";
		case Keyboard::RZKEY::RZKEY_F9:
			return L"RZKEY_F9";
		case Keyboard::RZKEY::RZKEY_F10:
			return L"RZKEY_F10";
		case Keyboard::RZKEY::RZKEY_F11:
			return L"RZKEY_F11";
		case Keyboard::RZKEY::RZKEY_F12:
			return L"RZKEY_F12";
		case Keyboard::RZKEY::RZKEY_1:
			return L"RZKEY_1";
		case Keyboard::RZKEY::RZKEY_2:
			return L"RZKEY_2";
		case Keyboard::RZKEY::RZKEY_3:
			return L"RZKEY_3";
		case Keyboard::RZKEY::RZKEY_4:
			return L"RZKEY_4";
		case Keyboard::RZKEY::RZKEY_5:
			return L"RZKEY_5";
		case Keyboard::RZKEY::RZKEY_6:
			return L"RZKEY_6";
		case Keyboard::RZKEY::RZKEY_7:
			return L"RZKEY_7";
		case Keyboard::RZKEY::RZKEY_8:
			return L"RZKEY_8";
		case Keyboard::RZKEY::RZKEY_9:
			return L"RZKEY_9";
		case Keyboard::RZKEY::RZKEY_0:
			return L"RZKEY_0";
		case Keyboard::RZKEY::RZKEY_A:
			return L"RZKEY_A";
		case Keyboard::RZKEY::RZKEY_B:
			return L"RZKEY_B";
		case Keyboard::RZKEY::RZKEY_C:
			return L"RZKEY_C";
		case Keyboard::RZKEY::RZKEY_D:
			return L"RZKEY_D";
		case Keyboard::RZKEY::RZKEY_E:
			return L"RZKEY_E";
		case Keyboard::RZKEY::RZKEY_F:
			return L"RZKEY_F";
		case Keyboard::RZKEY::RZKEY_G:
			return L"RZKEY_G";
		case Keyboard::RZKEY::RZKEY_H:
			return L"RZKEY_H";
		case Keyboard::RZKEY::RZKEY_I:
			return L"RZKEY_I";
		case Keyboard::RZKEY::RZKEY_J:
			return L"RZKEY_J";
		case Keyboard::RZKEY::RZKEY_K:
			return L"RZKEY_K";
		case Keyboard::RZKEY::RZKEY_L:
			return L"RZKEY_L";
		case Keyboard::RZKEY::RZKEY_M:
			return L"RZKEY_M";
		case Keyboard::RZKEY::RZKEY_N:
			return L"RZKEY_N";
		case Keyboard::RZKEY::RZKEY_O:
			return L"RZKEY_O";
		case Keyboard::RZKEY::RZKEY_P:
			return L"RZKEY_P";
		case Keyboard::RZKEY::RZKEY_Q:
			return L"RZKEY_Q";
		case Keyboard::RZKEY::RZKEY_R:
			return L"RZKEY_R";
		case Keyboard::RZKEY::RZKEY_S:
			return L"RZKEY_S";
		case Keyboard::RZKEY::RZKEY_T:
			return L"RZKEY_T";
		case Keyboard::RZKEY::RZKEY_U:
			return L"RZKEY_U";
		case Keyboard::RZKEY::RZKEY_V:
			return L"RZKEY_V";
		case Keyboard::RZKEY::RZKEY_W:
			return L"RZKEY_W";
		case Keyboard::RZKEY::RZKEY_X:
			return L"RZKEY_X";
		case Keyboard::RZKEY::RZKEY_Y:
			return L"RZKEY_Y";
		case Keyboard::RZKEY::RZKEY_Z:
			return L"RZKEY_Z";
		case Keyboard::RZKEY::RZKEY_NUMLOCK:
			return L"RZKEY_NUMLOCK";
		case Keyboard::RZKEY::RZKEY_NUMPAD0:
			return L"RZKEY_NUMPAD0";
		case Keyboard::RZKEY::RZKEY_NUMPAD1:
			return L"RZKEY_NUMPAD1";
		case Keyboard::RZKEY::RZKEY_NUMPAD2:
			return L"RZKEY_NUMPAD2";
		case Keyboard::RZKEY::RZKEY_NUMPAD3:
			return L"RZKEY_NUMPAD3";
		case Keyboard::RZKEY::RZKEY_NUMPAD4:
			return L"RZKEY_NUMPAD4";
		case Keyboard::RZKEY::RZKEY_NUMPAD5:
			return L"RZKEY_NUMPAD5";
		case Keyboard::RZKEY::RZKEY_NUMPAD6:
			return L"RZKEY_NUMPAD6";
		case Keyboard::RZKEY::RZKEY_NUMPAD7:
			return L"RZKEY_NUMPAD7";
		case Keyboard::RZKEY::RZKEY_NUMPAD8:
			return L"RZKEY_NUMPAD8";
		case Keyboard::RZKEY::RZKEY_NUMPAD9:
			return L"RZKEY_NUMPAD9";
		case Keyboard::RZKEY::RZKEY_NUMPAD_DIVIDE:
			return L"RZKEY_NUMPAD_DIVIDE";
		case Keyboard::RZKEY::RZKEY_NUMPAD_MULTIPLY:
			return L"RZKEY_NUMPAD_MULTIPLY";
		case Keyboard::RZKEY::RZKEY_NUMPAD_SUBTRACT:
			return L"RZKEY_NUMPAD_SUBTRACT";
		case Keyboard::RZKEY::RZKEY_NUMPAD_ADD:
			return L"RZKEY_NUMPAD_ADD";
		case Keyboard::RZKEY::RZKEY_NUMPAD_ENTER:
			return L"RZKEY_NUMPAD_ENTER";
		case Keyboard::RZKEY::RZKEY_NUMPAD_DECIMAL:
			return L"RZKEY_NUMPAD_DECIMAL";
		case Keyboard::RZKEY::RZKEY_PRINTSCREEN:
			return L"RZKEY_PRINTSCREEN";
		case Keyboard::RZKEY::RZKEY_SCROLL:
			return L"RZKEY_SCROLL";
		case Keyboard::RZKEY::RZKEY_PAUSE:
			return L"RZKEY_PAUSE";
		case Keyboard::RZKEY::RZKEY_INSERT:
			return L"RZKEY_INSERT";
		case Keyboard::RZKEY::RZKEY_HOME:
			return L"RZKEY_HOME";
		case Keyboard::RZKEY::RZKEY_PAGEUP:
			return L"RZKEY_PAGEUP";
		case Keyboard::RZKEY::RZKEY_DELETE:
			return L"RZKEY_DELETE";
		case Keyboard::RZKEY::RZKEY_END:
			return L"RZKEY_END";
		case Keyboard::RZKEY::RZKEY_PAGEDOWN:
			return L"RZKEY_PAGEDOWN";
		case Keyboard::RZKEY::RZKEY_UP:
			return L"RZKEY_UP";
		case Keyboard::RZKEY::RZKEY_LEFT:
			return L"RZKEY_LEFT";
		case Keyboard::RZKEY::RZKEY_DOWN:
			return L"RZKEY_DOWN";
		case Keyboard::RZKEY::RZKEY_RIGHT:
			return L"RZKEY_RIGHT";
		case Keyboard::RZKEY::RZKEY_TAB:
			return L"RZKEY_TAB";
		case Keyboard::RZKEY::RZKEY_CAPSLOCK:
			return L"RZKEY_CAPSLOCK";
		case Keyboard::RZKEY::RZKEY_BACKSPACE:
			return L"RZKEY_BACKSPACE";
		case Keyboard::RZKEY::RZKEY_ENTER:
			return L"RZKEY_ENTER";
		case Keyboard::RZKEY::RZKEY_LCTRL:
			return L"RZKEY_LCTRL";
		case Keyboard::RZKEY::RZKEY_LWIN:
			return L"RZKEY_LWIN";
		case Keyboard::RZKEY::RZKEY_LALT:
			return L"RZKEY_LALT";
		case Keyboard::RZKEY::RZKEY_SPACE:
			return L"RZKEY_SPACE";
		case Keyboard::RZKEY::RZKEY_RALT:
			return L"RZKEY_RALT";
		case Keyboard::RZKEY::RZKEY_FN:
			return L"RZKEY_FN";
		case Keyboard::RZKEY::RZKEY_RMENU:
			return L"RZKEY_RMENU";
		case Keyboard::RZKEY::RZKEY_RCTRL:
			return L"RZKEY_RCTRL";
		case Keyboard::RZKEY::RZKEY_LSHIFT:
			return L"RZKEY_LSHIFT";
		case Keyboard::RZKEY::RZKEY_RSHIFT:
			return L"RZKEY_RSHIFT";
		case Keyboard::RZKEY::RZKEY_MACRO1:
			return L"RZKEY_MACRO1";
		case Keyboard::RZKEY::RZKEY_MACRO2:
			return L"RZKEY_MACRO2";
		case Keyboard::RZKEY::RZKEY_MACRO3:
			return L"RZKEY_MACRO3";
		case Keyboard::RZKEY::RZKEY_MACRO4:
			return L"RZKEY_MACRO4";
		case Keyboard::RZKEY::RZKEY_MACRO5:
			return L"RZKEY_MACRO5";
		case Keyboard::RZKEY::RZKEY_OEM_1:
			return L"(tilde/半角/全角) (VK_OEM_3)";
		case Keyboard::RZKEY::RZKEY_OEM_2:
			return L"(minus) (VK_OEM_MINUS)";
		case Keyboard::RZKEY::RZKEY_OEM_3:
			return L"(equal) (VK_OEM_PLUS)";
		case Keyboard::RZKEY::RZKEY_OEM_4:
			return L"(left sqaure bracket) (VK_OEM_4)";
		case Keyboard::RZKEY::RZKEY_OEM_5:
			return L"(right square bracket) (VK_OEM_6)";
		case Keyboard::RZKEY::RZKEY_OEM_6:
			return L"(backslash) (VK_OEM_5)";
		case Keyboard::RZKEY::RZKEY_OEM_7:
			return L"(semi-colon) (VK_OEM_1)";
		case Keyboard::RZKEY::RZKEY_OEM_8:
			return L"(apostrophe) (VK_OEM_7)";
		case Keyboard::RZKEY::RZKEY_OEM_9:
			return L"(comma) (VK_OEM_COMMA)";
		case Keyboard::RZKEY::RZKEY_OEM_10:
			return L"(period) (VK_OEM_PERIOD)";
		case Keyboard::RZKEY::RZKEY_OEM_11:
			return L"(forward slash) (VK_OEM_2)";
		case Keyboard::RZKEY::RZKEY_EUR_1:
			return L"\"#\" (VK_OEM_5)";
		case Keyboard::RZKEY::RZKEY_EUR_2:
			return L"\\ (VK_OEM_102)";
		case Keyboard::RZKEY::RZKEY_JPN_1:
			return L"¥ (0xFF)";
		case Keyboard::RZKEY::RZKEY_JPN_2:
			return L"\\ (0xC1)";
		case Keyboard::RZKEY::RZKEY_JPN_3:
			return L"無変換 (VK_OEM_PA1)";
		case Keyboard::RZKEY::RZKEY_JPN_4:
			return L"変換 (0xFF)";
		case Keyboard::RZKEY::RZKEY_JPN_5:
			return L"ひらがな/カタカナ (0xFF)";
		case Keyboard::RZKEY::RZKEY_INVALID:
			return L"RZKEY_INVALID";
		}
		return L"UNKNOWN";
	};

	int key = -1;
	wstring strKey = L"NOT SET, Press the DOWN ARROW to set the first key.";

	auto printLegend = []() {
		printf("Press Esc to end unit test...\r\n");
		printf("Press UP to cycle test key...\r\n");
		printf("Press DOWN to cycle test key...\r\n");
	};

	auto printKey = [](int index, int key, const wchar_t* strKey) {
		wprintf(L"Current Index: %d Key: %d: Description: %s\r\n", index, key, strKey);
	};

	const char* baseLayer = "Dynamic_KeyboardExtended.chroma";

	// Create an animation in memory for unit testing
	int animationId = ChromaAnimationAPI::CreateAnimationInMemory((int)EChromaSDKDeviceTypeEnum::DE_2D, (int)EChromaSDKDevice2DEnum::DE_KeyboardExtended);

	// Copy the animation to name it
	ChromaAnimationAPI::CopyAnimation(animationId, baseLayer);
	
	// use Keys array
	ChromaAnimationAPI::SetChromaCustomFlagName(baseLayer, true);
	
	// Skip needing unload/load when changing Keys colors
	ChromaAnimationAPI::UsePreloadingName(baseLayer, false);

	// Start all black keys
	ChromaAnimationAPI::PlayAnimationName(baseLayer, true);

	auto updateAnimation = [](const char* baseLayer, int key) {

		// clear all keys
		ChromaAnimationAPI::MakeBlankFramesName(baseLayer, 1, 0.033f, 0);

		int color = ChromaAnimationAPI::GetRGB(255, 255, 255);		
		int row = HIBYTE(key);
		int column = LOBYTE(key);
		if (row < 6 && column < 22)
		{
			// set a single key
			ChromaAnimationAPI::SetKeyColorAllFramesName(baseLayer, key, color);

			// set by array
			//ChromaAnimationAPI::SetKeysColorName(baseLayer, 0, &key, 1, color);
		}

		// Show the changes
		ChromaAnimationAPI::PlayAnimationName(baseLayer, true);
	};

	HandleInput inputEscape = HandleInput(VK_ESCAPE);
	HandleInput inputUp = HandleInput(VK_UP);
	HandleInput inputDown = HandleInput(VK_DOWN);

	printLegend();
	printKey(index, key, strKey.c_str());

	while (true)
	{
		if (inputEscape.WasReleased())
		{
			printf("UnitTests8x24Keys: Complete.\r\n");
			break;
		}
		if (inputUp.WasPressed())
		{
			if (index > 0) {
				--index;

				key = keys[index];
				strKey = getKeyDescription(key);
				printKey(index, key, strKey.c_str());
				updateAnimation(baseLayer, key);
			}			
		}
		else if (inputDown.WasPressed())
		{
			if ((index+1) < (int)keys.size()) {
				++index;

				key = keys[index];
				strKey = getKeyDescription(key);
				printKey(index, key, strKey.c_str());
				updateAnimation(baseLayer, key);
			}
		}
		Sleep(1000/30);
	}

	ChromaAnimationAPI::StopAnimationName(baseLayer);
	ChromaAnimationAPI::CloseAnimationName(baseLayer);
}

void UnitTests::Run()
{
	printf("Start of unit tests...\r\n");
	//UnitTestsInit();
	UnitTestsInitSDK();

	if (!ChromaAnimationAPI::IsInitialized())
	{
		printf("Library hasn't loaded, aborting unit tests...\r\n");
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

	//UnitTestsSpecialCharacters();

	//UnitTestsEmpty();
	//UnitTestsLarge();

	UnitTests8x24Keys();

	printf("Press Esc to end unit tests...\r\n");
	HandleInput inputEscape = HandleInput(VK_ESCAPE);
	while (true)
	{
		if (inputEscape.WasReleased())
		{
			printf("Exiting...\r\n");
			break;
		}
		Sleep(100);
	}

	UnitTestsUninit();
}
