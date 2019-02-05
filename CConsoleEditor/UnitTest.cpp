#include "stdafx.h"
#include "ChromaAnimationAPI.h"
#include "UnitTests.h"

#include <chrono>
#include <thread>


using namespace std;
using namespace std::chrono;
using namespace ChromaSDK;

const float MATH_PI = 3.14159f;


void UnitTests::IsPlaying(const char* name)
{
	fprintf(stdout, "%s_ChromaLink IsPlayingName: %s\r\n", name, ChromaAnimationAPI::IsPlayingName("Random_Keyboard.chroma") ? "true" : "false");
	fprintf(stdout, "%s_Headset IsPlayingName: %s\r\n", name, ChromaAnimationAPI::IsPlayingName("Random_Keyboard.chroma") ? "true" : "false");
	fprintf(stdout, "%s_Keyboard IsPlayingName: %s\r\n", name, ChromaAnimationAPI::IsPlayingName("Random_Keyboard.chroma") ? "true" : "false");
	fprintf(stdout, "%s_Keypad IsPlayingName: %s\r\n", name, ChromaAnimationAPI::IsPlayingName("Random_Keyboard.chroma") ? "true" : "false");
	fprintf(stdout, "%s_Mouse IsPlayingName: %s\r\n", name, ChromaAnimationAPI::IsPlayingName("Random_Keyboard.chroma") ? "true" : "false");
	fprintf(stdout, "%s_Mousepad IsPlayingName: %s\r\n", name, ChromaAnimationAPI::IsPlayingName("Random_Keyboard.chroma") ? "true" : "false");

	fprintf(stdout, "ChromaLink IsPlayingType: %s\r\n", ChromaAnimationAPI::IsPlayingType((int)EChromaSDKDeviceTypeEnum::DE_1D, (int)EChromaSDKDevice1DEnum::DE_ChromaLink) ? "true" : "false");
	fprintf(stdout, "Headset IsPlayingType: %s\r\n", ChromaAnimationAPI::IsPlayingType((int)EChromaSDKDeviceTypeEnum::DE_1D, (int)EChromaSDKDevice1DEnum::DE_Headset) ? "true" : "false");
	fprintf(stdout, "Keyboard IsPlayingType: %s\r\n", ChromaAnimationAPI::IsPlayingType((int)EChromaSDKDeviceTypeEnum::DE_2D, (int)EChromaSDKDevice2DEnum::DE_Keyboard) ? "true" : "false");
	fprintf(stdout, "Keypad IsPlayingType: %s\r\n", ChromaAnimationAPI::IsPlayingType((int)EChromaSDKDeviceTypeEnum::DE_2D, (int)EChromaSDKDevice2DEnum::DE_Keypad) ? "true" : "false");
	fprintf(stdout, "Mouse IsPlayingType: %s\r\n", ChromaAnimationAPI::IsPlayingType((int)EChromaSDKDeviceTypeEnum::DE_2D, (int)EChromaSDKDevice2DEnum::DE_Mouse) ? "true" : "false");
	fprintf(stdout, "Mousepad IsPlayingType: %s\r\n", ChromaAnimationAPI::IsPlayingType((int)EChromaSDKDeviceTypeEnum::DE_1D, (int)EChromaSDKDevice1DEnum::DE_Mousepad) ? "true" : "false");
}

void UnitTests::UnitTestsInit()
{
	ChromaAnimationAPI::Init();

	Sleep(1000);
}

void UnitTests::UnitTestsUninit()
{
	ChromaAnimationAPI::StopAll();

	ChromaAnimationAPI::CloseAll();

	ChromaAnimationAPI::Uninit();

	Sleep(1000);

	fprintf(stdout, "Unit Tests have completed!\r\n");
}

void UnitTests::UnitTestsPlayComposite()
{
	while (true)
	{
		fprintf(stdout, "Measure CPU usage.\r\n");
		const char* RANDOM_COMPOSITE = "Random";
		ChromaAnimationAPI::PlayComposite(RANDOM_COMPOSITE, false);
		Sleep(3000);
	}
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
			fprintf(stdout, "Init...\r\n");
			ChromaAnimationAPI::Init();
		}

		fprintf(stdout, "Playing effects...\r\n");
		int randomChromaLinkEffect = OpenAndPlay("Random_ChromaLink.chroma");
		int randomHeadsetEffect = OpenAndPlay("Random_Headset.chroma");
		int randomKeyboardEffect = OpenAndPlay("Random_Keyboard.chroma");
		int randomKeypadEffect = OpenAndPlay("Random_Keypad.chroma");
		int randomMouseEffect = OpenAndPlay("Random_Mouse.chroma");
		int randomMousepadEffect = OpenAndPlay("Random_Mousepad.chroma");
		this_thread::sleep_for(chrono::seconds(1));

		ChromaAnimationAPI::CloseAnimation(randomChromaLinkEffect);
		ChromaAnimationAPI::CloseAnimation(randomHeadsetEffect);
		ChromaAnimationAPI::CloseAnimation(randomKeyboardEffect);
		ChromaAnimationAPI::CloseAnimation(randomKeypadEffect);
		ChromaAnimationAPI::CloseAnimation(randomMouseEffect);
		ChromaAnimationAPI::CloseAnimation(randomMousepadEffect);

		fprintf(stdout, "Simulate exit...\r\n");
		ChromaAnimationAPI::Uninit();
	}
}

void UnitTests::UnitTestsLayering()
{
	const char* BLANK_KEYBOARD = "Blank_Keyboard.chroma";
	const char* RANDOM_KEYBOARD = "Random_Keyboard.chroma";

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

	fprintf(stdout, "Playing animation %s.\r\n", animationName);
	ChromaAnimationAPI::CopyNonZeroAllKeysAllFramesName(RANDOM_KEYBOARD, BLANK_KEYBOARD);
	ChromaAnimationAPI::PlayAnimationName(animationName, false);
	Sleep(10000);
	ChromaAnimationAPI::CloseAnimationName(animationName);
}

void UnitTests::UnitTestsLoadedAnimations()
{
	const char* BLANK_KEYBOARD = "Blank_Keyboard.chroma";
	const char* BLANK_COMPOSITE = "Blank";
	const char* RANDOM_KEYBOARD = "Random_Keyboard.chroma";
	const char* RANDOM_COMPOSITE = "Random";
	const char* animationName = "";
	int animationId = -1;

	ChromaAnimationAPI::PlayComposite(BLANK_COMPOSITE, false);
	ChromaAnimationAPI::PlayComposite(RANDOM_COMPOSITE, true);
	Sleep(500);
	int count = ChromaAnimationAPI::GetAnimationCount();
	fprintf(stdout, "[%d] animation(s) are open.\r\n", count);
	for (int i = 0; i < count; ++i)
	{
		animationId = ChromaAnimationAPI::GetAnimationId(i);
		if (animationId < 0)
		{
			continue;
		}
		animationName = ChromaAnimationAPI::GetAnimationName(animationId);
		fprintf(stdout, "Animation is open: [%d] %s\r\n", animationId, animationName);
	}
	fprintf(stdout, "Closing open animations...\r\n");
	ChromaAnimationAPI::CloseAll();
	count = ChromaAnimationAPI::GetAnimationCount();
	fprintf(stdout, "[%d] animation(s) are open.\r\n", count);
	fprintf(stdout, "All animations are closed.\r\n");

	animationName = RANDOM_KEYBOARD;
	fprintf(stdout, "Playing animation %s.\r\n", animationName);
	ChromaAnimationAPI::PlayAnimationName(animationName, false);
	while (ChromaAnimationAPI::IsPlayingName(animationName))
	{
		fprintf(stdout, "Animation is playing... %s.\r\n", animationName);
		Sleep(1000);
	}
	fprintf(stdout, "Animation complete %s.\r\n", animationName);
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

	const char* BLANK_KEYBOARD = "Blank_Keyboard.chroma";
	const char* BLANK_COMPOSITE = "Blank";
	const char* RANDOM_KEYBOARD = "Random_Keyboard.chroma";
	const char* RANDOM_COMPOSITE = "Random";
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
		ChromaAnimationAPI::SetKeysColorName(animationName, i, wasdKeys, size(wasdKeys), COLOR_RED);
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
		ChromaAnimationAPI::SetKeysColorName(animationName, i, wasdKeys, size(wasdKeys), COLOR_RED);
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
	const char* BLANK_KEYBOARD = "Blank_Keyboard.chroma";
	const char* BLANK_COMPOSITE = "Blank";
	const char* RANDOM_KEYBOARD = "Random_Keyboard.chroma";
	const char* RANDOM_COMPOSITE = "Random";
	const char* animationName = "";
	const char* compositeName = "";
	int animationId = -1;

	fprintf(stdout, "Playing animation.\r\n");
	ChromaAnimationAPI::PlayAnimationName(RANDOM_KEYBOARD, false);
	Sleep(100);

	fprintf(stdout, "Clearing animations.\r\n");
	ChromaAnimationAPI::ClearAll();

	Sleep(1000);

	fprintf(stdout, "Playing animations.\r\n");
	ChromaAnimationAPI::PlayComposite("Random", false);
	Sleep(100);

	for (int wait = 0; wait < 3; ++wait)
	{
		int count = ChromaAnimationAPI::GetAnimationCount();
		fprintf(stdout, "[%d] animation(s) are open.\r\n", count);
		for (int i = 0; i < count; ++i)
		{
			animationId = ChromaAnimationAPI::GetAnimationId(i);
			if (animationId < 0)
			{
				continue;
			}
			animationName = ChromaAnimationAPI::GetAnimationName(animationId);
			fprintf(stdout, "Animation is open: [%d] %s\r\n", animationId, animationName);
		}
		Sleep(500);
	}

	for (int wait = 0; wait < 10; ++wait)
	{
		int count = ChromaAnimationAPI::GetPlayingAnimationCount();
		fprintf(stdout, "[%d] animation(s) are playing.\r\n", count);
		for (int i = 0; i < count; ++i)
		{
			animationId = ChromaAnimationAPI::GetPlayingAnimationId(i);
			if (animationId < 0)
			{
				continue;
			}

			animationName = ChromaAnimationAPI::GetAnimationName(animationId);
			fprintf(stdout, "Animation is playing: [%d] %s\r\n", animationId, animationName);
		}
		if (ChromaAnimationAPI::GetPlayingAnimationCount() == 0)
		{
			fprintf(stdout, "No animations are playing.\r\n");
		}
		Sleep(500);
	}

	ChromaAnimationAPI::ClearAll();

	Sleep(3000);
}

void UnitTests::UnitTestsWait()
{
	const char* BLANK_KEYBOARD = "Blank_Keyboard.chroma";
	const char* BLANK_COMPOSITE = "Blank";
	const char* RANDOM_KEYBOARD = "Random_Keyboard.chroma";
	const char* RANDOM_COMPOSITE = "Random";
	const char* animationName = "";
	int animationId = -1;

	fprintf(stdout, "Playing animation.\r\n");
	ChromaAnimationAPI::PlayAnimationName(RANDOM_KEYBOARD, false);
	Sleep(100);

	fprintf(stdout, "Clearing animations.\r\n");
	ChromaAnimationAPI::ClearAll();

	Sleep(1000);

	fprintf(stdout, "Playing animations.\r\n");
	ChromaAnimationAPI::PlayComposite("Random", false);
	Sleep(100);

	for (int wait = 0; wait < 3; ++wait)
	{
		int count = ChromaAnimationAPI::GetAnimationCount();
		fprintf(stdout, "[%d] animation(s) are open.\r\n", count);
		for (int i = 0; i < count; ++i)
		{
			animationId = ChromaAnimationAPI::GetAnimationId(i);
			if (animationId < 0)
			{
				continue;
			}
			animationName = ChromaAnimationAPI::GetAnimationName(animationId);
			fprintf(stdout, "Animation is open: [%d] %s\r\n", animationId, animationName);
		}
		Sleep(500);
	}

	for (int wait = 0; wait < 10; ++wait)
	{
		int count = ChromaAnimationAPI::GetPlayingAnimationCount();
		fprintf(stdout, "[%d] animation(s) are playing.\r\n", count);
		for (int i = 0; i < count; ++i)
		{
			animationId = ChromaAnimationAPI::GetPlayingAnimationId(i);
			if (animationId < 0)
			{
				continue;
			}

			animationName = ChromaAnimationAPI::GetAnimationName(animationId);
			fprintf(stdout, "Animation is playing: [%d] %s\r\n", animationId, animationName);
		}
		if (ChromaAnimationAPI::GetPlayingAnimationCount() == 0)
		{
			fprintf(stdout, "No animations are playing.\r\n");
		}
		Sleep(500);
	}

	ChromaAnimationAPI::ClearAll();

	Sleep(3000);

	fprintf(stdout, "Playing animation.\r\n");
	ChromaAnimationAPI::PlayAnimationName(RANDOM_KEYBOARD, false);
	Sleep(100);
}

void UnitTests::UnitTestsCopy()
{
	const char* RANDOM_KEYBOARD = "Random_Keyboard.chroma";

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
	const char* RANDOM_KEYBOARD = "Random_Keyboard.chroma";

	fprintf(stdout, "Call: PlayComposite: Random\r\n");
	ChromaAnimationAPI::PlayComposite("Random", true);
	IsPlaying("Random");
	Sleep(3000);

	fprintf(stdout, "Call: StopComposite\r\n");
	ChromaAnimationAPI::StopComposite("Random");
	IsPlaying("Random");
	Sleep(3000);

	fprintf(stdout, "Call: PlayComposite: Blank\r\n");
	ChromaAnimationAPI::PlayComposite("Blank", false);
	IsPlaying("Random"); //random should show false, type should be playing blank
	Sleep(3000);

	fprintf(stdout, "Call: PlayAnimationName\r\n");
	ChromaAnimationAPI::PlayAnimationName(RANDOM_KEYBOARD, true);
	Sleep(3000);

	fprintf(stdout, "Call: StopAnimationName\r\n");
	ChromaAnimationAPI::StopAnimationName(RANDOM_KEYBOARD);
	Sleep(1000);

	fprintf(stdout, "Call: PlayAnimationName\r\n");
	ChromaAnimationAPI::PlayAnimationName(RANDOM_KEYBOARD, true);
	Sleep(3000);

	fprintf(stdout, "Call: StopAnimationType\r\n");
	ChromaAnimationAPI::StopAnimationType((int)EChromaSDKDeviceTypeEnum::DE_2D, (int)EChromaSDKDevice2DEnum::DE_Keyboard);
}

void UnitTests::UnitTestsOffset()
{
	fprintf(stdout, "Start of offset unit test.\r\n");

	const char* RANDOM_KEYBOARD = "Random_Keyboard.chroma";

	const char* animationName = RANDOM_KEYBOARD;
	ChromaAnimationAPI::CloseAnimationName(animationName);

	int animationId = ChromaAnimationAPI::OpenAnimation(animationName);

	int frameCount = ChromaAnimationAPI::GetFrameCountName(animationName);

	fprintf(stdout, "Set all frames white with FillColor.\r\n");
	ChromaAnimationAPI::FillColorAllFramesRGBName(animationName, 255, 255, 255);

	fprintf(stdout, "Fade out black with MultiplyIntensity.\r\n");
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

	fprintf(stdout, "Set all frames black with FillColor.\r\n");
	ChromaAnimationAPI::UnloadAnimationName(animationName);
	ChromaAnimationAPI::FillColorAllFramesRGBName(animationName, 0, 0, 0);

	fprintf(stdout, "Fade in red with FillColor.\r\n");
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

	fprintf(stdout, "Set all frames red with FillColor.\r\n");
	ChromaAnimationAPI::FillColorAllFramesRGBName(animationName, 255, 0, 0);

	fprintf(stdout, "Fade in green with OffsetColors.\r\n");
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

	fprintf(stdout, "Set all frames yellow with FillColor.\r\n");
	ChromaAnimationAPI::FillColorAllFramesRGBName(animationName, 255, 255, 0);

	fprintf(stdout, "Fade out red with OffsetColors.\r\n");
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

	fprintf(stdout, "Set all frames green with FillColor.\r\n");
	ChromaAnimationAPI::FillColorAllFramesRGBName(animationName, 0, 255, 0);

	fprintf(stdout, "Fade in white with OffsetColors.\r\n");
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

	fprintf(stdout, "End of offset unit test.\r\n");
}

void UnitTests::UnitTestsNonZero()
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
	int animationId = ChromaAnimationAPI::OpenAnimation(animationName);

	// Reload from disk
	ChromaAnimationAPI::CloseAnimationName(animationName);

	int frameCount = ChromaAnimationAPI::GetFrameCountName(animationName);

	fprintf(stdout, "Fade out red.\r\n");
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
	fprintf(stdout, "Red should be gone.\r\n");
	Sleep(3000);

	fprintf(stdout, "Fade out green.\r\n");
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
	fprintf(stdout, "Green should be gone.\r\n");
	Sleep(3000);

	fprintf(stdout, "Fade out blue.\r\n");
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
	fprintf(stdout, "Blue should be gone.\r\n");
	Sleep(3000);

	fprintf(stdout, "Non zero keys should fade in to white.\r\n");
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

	fprintf(stdout, "WASD keys should be white every other frame.\r\n");
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

	fprintf(stdout, "WASD keys should be white every other frame.\r\n");
	for (int i = 0; i < frameCount; ++i)
	{
		ChromaAnimationAPI::SetKeysNonZeroColorName(animationName, i, wasdKeys, size(wasdKeys), COLOR_WHITE);
	}
	ChromaAnimationAPI::UnloadAnimationName(animationName); //show changes
	ChromaAnimationAPI::PlayAnimationName(animationName, false);
	while (ChromaAnimationAPI::IsPlayingName(animationName))
	{
		Sleep(0);
	}

	fprintf(stdout, "End of nonzero unit test.\r\n");
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

	fprintf(stdout, "Create random HDK LED colors effect.\r\n");

	FChromaSDKGuid effectId = FChromaSDKGuid();
	ChromaAnimationAPI::CreateEffect(CHROMABOX, EFFECT_TYPE::CHROMA_CUSTOM, colors, size, &effectId);

	fprintf(stdout, "Set HDK Effect.\r\n");

	ChromaAnimationAPI::SetEffect(effectId);

	Sleep(3000);

	fprintf(stdout, "Delete HDK Effect.\r\n");

	ChromaAnimationAPI::DeleteEffect(effectId);

	Sleep(1000);

	delete colors;
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

	fprintf(stdout, "Create HDK gradient.\r\n");

	FChromaSDKGuid effectId = FChromaSDKGuid();
	ChromaAnimationAPI::CreateEffect(CHROMABOX, EFFECT_TYPE::CHROMA_CUSTOM, colors, size, &effectId);

	fprintf(stdout, "Set HDK Effect.\r\n");

	ChromaAnimationAPI::SetEffect(effectId);

	Sleep(3000);

	fprintf(stdout, "Delete HDK Effect.\r\n");

	ChromaAnimationAPI::DeleteEffect(effectId);

	Sleep(1000);

	delete colors;
}

void UnitTests::UnitTestsCreateAnimation()
{
	const char* animationName = "New_ChromaLink.chroma";
	int animationId = ChromaAnimationAPI::CreateAnimation(animationName, (int)EChromaSDKDeviceTypeEnum::DE_1D, (int)EChromaSDKDevice1DEnum::DE_ChromaLink);
	if (animationId < 0)
	{
		fprintf(stderr, "Failed to create animation! %s\r\n", animationName);
	}
}

void UnitTests::UnitTestsKeyboardCustom()
{
	fprintf(stdout, "Clear all.\r\n");
	ChromaAnimationAPI::ClearAll();
	Sleep(3000);

	fprintf(stdout, "Show custom keyboard keys Z N M LALT.\r\n");
	int animationId = ChromaAnimationAPI::CreateAnimationInMemory((int)EChromaSDKDeviceTypeEnum::DE_2D, (int)EChromaSDKDevice2DEnum::DE_Keyboard);
	ChromaAnimationAPI::SetChromaCustomFlag(animationId, true);
	ChromaAnimationAPI::SetKeyColor(animationId, 0, (int)Keyboard::RZKEY::RZKEY_Z, 0x01FF0000);
	ChromaAnimationAPI::SetKeyColor(animationId, 0, (int)Keyboard::RZKEY::RZKEY_N, 0x0100FF00);
	ChromaAnimationAPI::SetKeyColor(animationId, 0, (int)Keyboard::RZKEY::RZKEY_M, 0x010000FF);
	ChromaAnimationAPI::SetKeyColor(animationId, 0, (int)Keyboard::RZKEY::RZKEY_LALT, 0x01FFFFFF);
	fprintf(stdout, "Play animation with custom keys.\r\n");
	ChromaAnimationAPI::PlayAnimation(animationId);
	Sleep(2000);
	fprintf(stdout, "Preview frame with custom keys.\r\n");
	ChromaAnimationAPI::PreviewFrame(animationId, 0);
	Sleep(2000);
	ChromaAnimationAPI::CloseAnimation(animationId);

	fprintf(stdout, "Clear all.\r\n");
	ChromaAnimationAPI::ClearAll();
	Sleep(3000);

	fprintf(stdout, "Show custom keyboard keys LCTRL X C V B.\r\n");
	animationId = ChromaAnimationAPI::CreateAnimationInMemory((int)EChromaSDKDeviceTypeEnum::DE_2D, (int)EChromaSDKDevice2DEnum::DE_Keyboard);
	ChromaAnimationAPI::SetChromaCustomFlag(animationId, true);
	ChromaAnimationAPI::SetKeyColor(animationId, 0, (int)Keyboard::RZKEY::RZKEY_LCTRL, 0x01FF0000);
	ChromaAnimationAPI::SetKeyColor(animationId, 0, (int)Keyboard::RZKEY::RZKEY_X, 0x0100FF00);
	ChromaAnimationAPI::SetKeyColor(animationId, 0, (int)Keyboard::RZKEY::RZKEY_C, 0x010000FF);
	ChromaAnimationAPI::SetKeyColor(animationId, 0, (int)Keyboard::RZKEY::RZKEY_V, 0x01FFFFFF);
	ChromaAnimationAPI::SetKeyColor(animationId, 0, (int)Keyboard::RZKEY::RZKEY_B, 0x01FFFF00);
	fprintf(stdout, "Play animation with custom keys.\r\n");
	ChromaAnimationAPI::PlayAnimation(animationId);
	Sleep(2000);
	fprintf(stdout, "Preview frame with custom keys.\r\n");
	ChromaAnimationAPI::PreviewFrame(animationId, 0);
	Sleep(2000);
	ChromaAnimationAPI::CloseAnimation(animationId);

	fprintf(stdout, "Clear all.\r\n");
	ChromaAnimationAPI::ClearAll();
	Sleep(3000);
}

void UnitTests::UnitTestsFadeStart()
{
	const char* baseLayer = "Blank_Keyboard.chroma";
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
	const char* baseLayer = "Blank_Keyboard.chroma";
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
	const char* baseLayer = "Fire_Keyboard.chroma";
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
	ChromaAnimationAPI::MakeBlankFramesRandom(baseAnimation, frameCount, 0.1);

	ChromaAnimationAPI::SetChromaCustomFlag(baseAnimation, true);
	ChromaAnimationAPI::SetChromaCustomColorAllFrames(baseAnimation);

	ChromaAnimationAPI::SaveAnimation(baseAnimation, "SaveAnimation.chroma");

	// get time in seconds
	duration<double, milli> time_span = high_resolution_clock::now() - timer;
	float deltaTime = (float)(time_span.count() / 1000.0f);
	fprintf(stdout, "Elapsed time: %f\r\n", deltaTime);

	ChromaAnimationAPI::PlayAnimationLoop(baseAnimation, true);

	Sleep(3000);

	ChromaAnimationAPI::CloseAnimation(baseAnimation);

	Sleep(1000);
}

void UnitTests::UnitTestsSaveAnimation2()
{
	const char* baseLayer = "Fire_Keyboard.chroma";
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
	ChromaAnimationAPI::MakeBlankFramesRandomBlackAndWhite(baseAnimation, frameCount, 0.1);
	ChromaAnimationAPI::MultiplyIntensityAllFrames(baseAnimation, 0.25f);

	ChromaAnimationAPI::SetChromaCustomFlag(baseAnimation, true);
	ChromaAnimationAPI::SetChromaCustomColorAllFrames(baseAnimation);
	ChromaAnimationAPI::PlayAnimationLoop(baseAnimation, true);

	// get time in seconds
	duration<double, milli> time_span = high_resolution_clock::now() - timer;
	float deltaTime = (float)(time_span.count() / 1000.0f);
	fprintf(stdout, "Elapsed time: %f\r\n", deltaTime);

	Sleep(3000);

	ChromaAnimationAPI::CloseAnimation(baseAnimation);

	Sleep(1000);
}

void UnitTests::UnitTestsDuplicateFirstFrame()
{
	const char* baseLayer = "CircleSmall_Keyboard.chroma";
	ChromaAnimationAPI::CloseAnimationName(baseLayer);
	int baseAnimation = ChromaAnimationAPI::OpenAnimation(baseLayer);

	int frameCount = 24;
	ChromaAnimationAPI::DuplicateFirstFrameName(baseLayer, frameCount);

	for (int frameId = 0; frameId < frameCount; ++frameId) {
		float t = 1 - fabsf(cos(MATH_PI*frameId / (float)frameCount));
		ChromaAnimationAPI::MultiplyIntensityRGBName(baseLayer, frameId, 0, 127 * t, 0);
	}

	ChromaAnimationAPI::SetChromaCustomFlagName(baseLayer, true);
	ChromaAnimationAPI::SetChromaCustomColorAllFramesName(baseLayer);
	ChromaAnimationAPI::PlayAnimationName(baseLayer, true);
}

void UnitTests::Run()
{
	fprintf(stdout, "Start of unit tests...\r\n");
	Sleep(500);
	UnitTestsInit();

	if (!ChromaAnimationAPI::IsInitialized())
	{
		fprintf(stdout, "Library hasn't loaded, aborting unit tests...\r\n");
		return;
	}

	Sleep(500);


	//UnitTestsLoadedAnimations();
	UnitTestsIdleAnimation();
	//UnitTestsOpenAnimationFromMemory();
	//UnitTestsFadeStart();
	//UnitTestsFadeEnd();
	//UnitTestsCopyAnimation();
	//UnitTestsSaveAnimation();
	//UnitTestsSaveAnimation2();
	//UnitTestsDuplicateFirstFrame();
	//UnitTestsCreateRandomBlackAndWhite();
	//UnitTestsCreateRandomBlackAndWhite();
	//UnitTestsKeyboardCustom();
	//UnitTestsPlayComposite();
	//UnitTestsHDKIndividualLEDsGradient();
	//UnitTestsHDKIndividualLEDs();
	//UnitTestsOffset();
	//UnitTestsNonZero();
	//UnitTestsCreateAnimation();
 	UnitTestsUninit();

	while (true)
	{
		Sleep(1000);
	}
}

int UnitTests::OpenAndPlay(const char* path)
{
	int animationId = (int)ChromaAnimationAPI::OpenAnimation(path);
	fprintf(stdout, "OpenAnimation: %s result=%d\r\n", path, animationId);
	if (animationId >= 0)
	{
		int result = (int)ChromaAnimationAPI::PlayAnimation(animationId);
		fprintf(stdout, "PlayAnimation: %d result=%d\r\n", animationId, result);
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
	fprintf(stdout, "CloseAnimation: %d result=%d\r\n", animationId, result);
	return result;
}

void UnitTests::UnitTestsOpenAnimationFromMemory()
{
	const char* path = "Random_Keyboard.chroma";
	FILE* stream = nullptr;
	try
	{
		if (0 != fopen_s(&stream, path, "rb") ||
			stream == nullptr)
		{
			fprintf(stderr, "UnitTestsOpenAnimationFromMemory: Failed to open animation! %s\r\n", path);
		}

		fprintf(stdout, "UnitTestsOpenAnimationFromMemory: Reading animation file contents...\r\n");

		vector<byte> lstBuffer;

		byte data = 0;
		long read = 0;
		do
		{
			read = fread(&data, sizeof(byte), 1, stream);
			lstBuffer.push_back(data);
		} while (read != 0);

 		fprintf(stderr, "UnitTestsOpenAnimationFromMemory: File size is! %d\r\n", lstBuffer.size());

		byte* buffer = new byte[lstBuffer.size()];
		copy(lstBuffer.begin(), lstBuffer.end(), buffer);

		fprintf(stdout, "UnitTestsOpenAnimationFromMemory: Opening file from buffer...\r\n");

		const char* name = "MemoryAnimation.chroma";
		ChromaAnimationAPI::OpenAnimationFromMemory(buffer, name);

		fprintf(stdout, "UnitTestsOpenAnimationFromMemory: Deleting buffer...\r\n");

		delete buffer;

		fprintf(stdout, "UnitTestsOpenAnimationFromMemory: Playing animation...\r\n");

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

	fprintf(stdout, "UnitTestsOpenAnimationFromMemory: Complete!\r\n");
}

void UnitTests::UnitTestsIdleAnimation()
{
	const char* animation = "Random_Keyboard.chroma";
	const char* idleAnimation = "Fire_Keyboard.chroma";

	fprintf(stdout, "Idle is [ON].\r\n");
	ChromaAnimationAPI::UseIdleAnimation(true);
	ChromaAnimationAPI::SetIdleAnimationName(idleAnimation);
	
	ChromaAnimationAPI::CloseAnimationName(animation);
	ChromaAnimationAPI::OverrideFrameDurationName(animation, 0.1f);

	fprintf(stdout, "Play random animation.\r\n");
	ChromaAnimationAPI::PlayAnimationName(animation, false);
	fprintf(stdout, "Waiting 3 sec...\r\n");
	Sleep(3000);
	fprintf(stdout, "\r\n");

	fprintf(stdout, "Play random animation.\r\n");
	ChromaAnimationAPI::PlayAnimationName(animation, false);
	fprintf(stdout, "Waiting 3 sec...\r\n");
	Sleep(3000);
	fprintf(stdout, "\r\n");

	fprintf(stdout, "Play random animation.\r\n");
	ChromaAnimationAPI::PlayAnimationName(animation, false);
	fprintf(stdout, "Waiting 3 sec...\r\n");
	Sleep(3000);
	fprintf(stdout, "\r\n");

	fprintf(stdout, "Clear all animations with idle [ON].\r\n");
	ChromaAnimationAPI::ClearAll();
	fprintf(stdout, "Waiting 3 sec...\r\n");
	Sleep(3000);
	fprintf(stdout, "\r\n");

	fprintf(stdout, "Idle is [OFF].\r\n");
	ChromaAnimationAPI::UseIdleAnimation(false);
	fprintf(stdout, "Waiting 3 sec...\r\n");
	Sleep(3000);
	fprintf(stdout, "\r\n");
}
