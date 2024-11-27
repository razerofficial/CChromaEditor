#pragma once

class UnitTests
{
public:

	static void IsPlaying(const wchar_t* name);

	static void UnitTestsInit();

	static RZRESULT UnitTestsInitSDK();

	static void UnitTestsUninit();

	static void UnitTestsPlayComposite();

	static void UnitTestsOpenDialog();

	static void UnitTestsOpenClose();

	static void UnitTestsLayering();

	static void UnitTestsLoadedAnimations();

	static void UnitTestsSetKeys();

	static void UnitTestsClear();

	static void UnitTestsWait();

	static void UnitTestsCopy();

	static void UnitTestsMisc();

	static void UnitTestsOffset();

	static void UnitTestsNonZero();

	static void UnitTestsHDKIndividualLEDs();

	static void UnitTestsHDKIndividualLEDsGradient();

	static void UnitTestsCreateAnimation();

	static void UnitTestsKeyboardCustom();

	static void UnitTestsFadeStart();

	static void UnitTestsFadeEnd();

	static void UnitTestsCopyAnimation();

	static void UnitTestsSaveAnimation();

	static void UnitTestsSaveAnimation2();

	static void UnitTestsCreateRandomBlackAndWhite();

	static void UnitTestsDuplicateFirstFrame();

	static void UnitTestsDamage();

	static int OpenAndPlay(const wchar_t* path);

	static int CloseAnimation(int animationId);

	static void UnitTestFireKeyboard();

	static void UnitTestsOpenAnimationFromMemory();

	static void UnitTestsMeasurePreloading();

	static void UnitTestsMeasurePreloadingWithCaching();

	static void UnitTestsMeasureGetAnimation();

	static void UnitTestsMeasureGetAnimationWithCaching();

	static void UnitTestsFrameValidation();

	static void UnitTestsCopyKeysColorAllFramesName();

	static void UnitTestsSpecialCharacters();

	static void UnitTestsEmpty();
	static void UnitTestsLarge();

	static void UnitTests8x24Keys();

	static void UnitTestsGetSetKeyColor();
	
	static void UnitTestsSetCurrentFrameName();

	static void UnitTestsPauseAnimations();

	static void UnitTestsIsActive();

	static void UnitTestsIsConnected();

	static void UnitTestsSetEventName();

	static void UnitTestsUnicode();

	static void UnitTestsIdleAnimation();

	static void UnitTestsIdleAnimation2();

	static void UnitTestsIdleAnimation3();
	
	static void UnitTestsIdleAnimation4();

	static void UnitTestsIdleAnimation5();

	static void PrintAnimationDuration(const wchar_t* path);

	static void UnitTestsFrameDuration();

	static void UnitTestsTotalDuration();

	static void UnitTestsSetStaticColor();

	static void UnitTestsSetKeysColorAllFramesRGB();

	static void Run();

};
