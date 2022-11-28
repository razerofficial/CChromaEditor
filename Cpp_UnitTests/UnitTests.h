#pragma once

class UnitTests
{
public:

	static void IsPlaying(const char* name);

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

	static void UnitTestsIdleAnimation();

	static void UnitTestsDamage();

	static int OpenAndPlay(const char* path);

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

	static void Run();

};
