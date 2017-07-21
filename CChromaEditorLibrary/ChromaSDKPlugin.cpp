#include "stdafx.h"
#include "ChromaSDKPlugin.h"

#ifdef _WIN64
#define CHROMASDKDLL        _T("RzChromaSDK64.dll")
#else
#define CHROMASDKDLL        _T("RzChromaSDK.dll")
#endif

using namespace ChromaSDK;
using namespace std;

ChromaSDKPlugin* ChromaSDKPlugin::_sInstance = nullptr;

bool ChromaSDKPlugin::ValidateGetProcAddress(bool condition, const char* methodName)
{
	if (condition)
	{
		fprintf(stderr, "ChromaSDKPlugin failed to load %s!\r\n", methodName);
	}
	else
	{
		//fprintf(stdout, "ChromaSDKPlugin loaded %s.\r\n", *methodName);
	}
	return condition;
}

ChromaSDKPlugin::ChromaSDKPlugin()
{
	_sInstance = this;
	_mLibraryChroma = LoadLibrary(CHROMASDKDLL);
	if (_mLibraryChroma == NULL)
	{
		fprintf(stderr, "ChromaSDKPlugin failed to load!\r\n");
		return;
	}
	fprintf(stdout, "ChromaSDKPlugin loaded.\r\n");

	_mMethodInit = (CHROMA_SDK_INIT)GetProcAddress(_mLibraryChroma, "Init");
	if (ValidateGetProcAddress(_mMethodInit == nullptr, "Init"))
	{
		return;
	}
	_mMethodUnInit = (CHROMA_SDK_UNINIT)GetProcAddress(_mLibraryChroma, "UnInit");
	if (ValidateGetProcAddress(_mMethodUnInit == nullptr, "UnInit"))
	{
		return;
	}
	_mMethodQueryDevice = (CHROMA_SDK_QUERY_DEVICE)GetProcAddress(_mLibraryChroma, "QueryDevice");
	if (ValidateGetProcAddress(_mMethodQueryDevice == nullptr, "QueryDevice"))
	{
		return;
	}
	_mMethodUnInit = (CHROMA_SDK_UNINIT)GetProcAddress(_mLibraryChroma, "UnInit");
	if (ValidateGetProcAddress(_mMethodUnInit == nullptr, "UnInit"))
	{
		return;
	}

	_mMethodCreateChromaLinkEffect = (CHROMA_SDK_CREATE_CHROMA_LINK_EFFECT)GetProcAddress(_mLibraryChroma, "CreateChromaLinkEffect");
	if (ValidateGetProcAddress(_mMethodCreateChromaLinkEffect == nullptr, "CreateChromaLinkEffect"))
	{
		return;
	}
	_mMethodCreateHeadsetEffect = (CHROMA_SDK_CREATE_HEADSET_EFFECT)GetProcAddress(_mLibraryChroma, "CreateHeadsetEffect");
	if (ValidateGetProcAddress(_mMethodCreateHeadsetEffect == nullptr, "CreateHeadsetEffect"))
	{
		return;
	}
	_mMethodCreateKeyboardEffect = (CHROMA_SDK_CREATE_KEYBOARD_EFFECT)GetProcAddress(_mLibraryChroma, "CreateKeyboardEffect");
	if (ValidateGetProcAddress(_mMethodCreateKeyboardEffect == nullptr, "CreateKeyboardEffect"))
	{
		return;
	}
	_mMethodCreateMouseEffect = (CHROMA_SDK_CREATE_MOUSE_EFFECT)GetProcAddress(_mLibraryChroma, "CreateMouseEffect");
	if (ValidateGetProcAddress(_mMethodCreateMouseEffect == nullptr, "CreateMouseEffect"))
	{
		return;
	}
	_mMethodCreateMousepadEffect = (CHROMA_SDK_CREATE_MOUSEPAD_EFFECT)GetProcAddress(_mLibraryChroma, "CreateMousepadEffect");
	if (ValidateGetProcAddress(_mMethodCreateMousepadEffect == nullptr, "CreateMousepadEffect"))
	{
		return;
	}
	_mMethodCreateKeypadEffect = (CHROMA_SDK_CREATE_KEYPAD_EFFECT)GetProcAddress(_mLibraryChroma, "CreateKeypadEffect");
	if (ValidateGetProcAddress(_mMethodCreateKeypadEffect == nullptr, "CreateKeypadEffect"))
	{
		return;
	}

	_mMethodCreateEffect = (CHROMA_SDK_CREATE_EFFECT)GetProcAddress(_mLibraryChroma, "CreateEffect");
	if (ValidateGetProcAddress(_mMethodCreateEffect == nullptr, "CreateEffect"))
	{
		return;
	}
	_mMethodSetEffect = (CHROMA_SDK_SET_EFFECT)GetProcAddress(_mLibraryChroma, "SetEffect");
	if (ValidateGetProcAddress(_mMethodSetEffect == nullptr, "SetEffect"))
	{
		return;
	}
	_mMethodDeleteEffect = (CHROMA_SDK_DELETE_EFFECT)GetProcAddress(_mLibraryChroma, "DeleteEffect");
	if (ValidateGetProcAddress(_mMethodDeleteEffect == nullptr, "DeleteEffect"))
	{
		return;
	}

	if (ChromaSDKInit() == 0)
	{
		fprintf(stdout, "ChromaSDKPlugin initialized.\r\n");
	}
	else
	{
		fprintf(stderr, "ChromaSDKPlugin failed to initialize!\r\n");
	}

	// keyboard mapping
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_ESC] = Keyboard::RZKEY::RZKEY_ESC;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_F1] = Keyboard::RZKEY::RZKEY_F1;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_F2] = Keyboard::RZKEY::RZKEY_F2;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_F3] = Keyboard::RZKEY::RZKEY_F3;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_F4] = Keyboard::RZKEY::RZKEY_F4;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_F5] = Keyboard::RZKEY::RZKEY_F5;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_F6] = Keyboard::RZKEY::RZKEY_F6;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_F7] = Keyboard::RZKEY::RZKEY_F7;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_F8] = Keyboard::RZKEY::RZKEY_F8;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_F9] = Keyboard::RZKEY::RZKEY_F9;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_F10] = Keyboard::RZKEY::RZKEY_F10;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_F11] = Keyboard::RZKEY::RZKEY_F11;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_F12] = Keyboard::RZKEY::RZKEY_F12;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_1] = Keyboard::RZKEY::RZKEY_1;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_2] = Keyboard::RZKEY::RZKEY_2;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_3] = Keyboard::RZKEY::RZKEY_3;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_4] = Keyboard::RZKEY::RZKEY_4;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_5] = Keyboard::RZKEY::RZKEY_5;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_6] = Keyboard::RZKEY::RZKEY_6;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_7] = Keyboard::RZKEY::RZKEY_7;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_8] = Keyboard::RZKEY::RZKEY_8;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_9] = Keyboard::RZKEY::RZKEY_9;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_0] = Keyboard::RZKEY::RZKEY_0;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_A] = Keyboard::RZKEY::RZKEY_A;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_B] = Keyboard::RZKEY::RZKEY_B;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_C] = Keyboard::RZKEY::RZKEY_C;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_D] = Keyboard::RZKEY::RZKEY_D;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_E] = Keyboard::RZKEY::RZKEY_E;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_F] = Keyboard::RZKEY::RZKEY_F;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_G] = Keyboard::RZKEY::RZKEY_G;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_H] = Keyboard::RZKEY::RZKEY_H;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_I] = Keyboard::RZKEY::RZKEY_I;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_J] = Keyboard::RZKEY::RZKEY_J;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_K] = Keyboard::RZKEY::RZKEY_K;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_L] = Keyboard::RZKEY::RZKEY_L;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_M] = Keyboard::RZKEY::RZKEY_M;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_N] = Keyboard::RZKEY::RZKEY_N;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_O] = Keyboard::RZKEY::RZKEY_O;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_P] = Keyboard::RZKEY::RZKEY_P;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_Q] = Keyboard::RZKEY::RZKEY_Q;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_R] = Keyboard::RZKEY::RZKEY_R;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_S] = Keyboard::RZKEY::RZKEY_S;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_T] = Keyboard::RZKEY::RZKEY_T;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_U] = Keyboard::RZKEY::RZKEY_U;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_V] = Keyboard::RZKEY::RZKEY_V;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_W] = Keyboard::RZKEY::RZKEY_W;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_X] = Keyboard::RZKEY::RZKEY_X;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_Y] = Keyboard::RZKEY::RZKEY_Y;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_Z] = Keyboard::RZKEY::RZKEY_Z;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_NUMLOCK] = Keyboard::RZKEY::RZKEY_NUMLOCK;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_NUMPAD0] = Keyboard::RZKEY::RZKEY_NUMPAD0;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_NUMPAD1] = Keyboard::RZKEY::RZKEY_NUMPAD1;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_NUMPAD2] = Keyboard::RZKEY::RZKEY_NUMPAD2;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_NUMPAD3] = Keyboard::RZKEY::RZKEY_NUMPAD3;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_NUMPAD4] = Keyboard::RZKEY::RZKEY_NUMPAD4;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_NUMPAD5] = Keyboard::RZKEY::RZKEY_NUMPAD5;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_NUMPAD6] = Keyboard::RZKEY::RZKEY_NUMPAD6;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_NUMPAD7] = Keyboard::RZKEY::RZKEY_NUMPAD7;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_NUMPAD8] = Keyboard::RZKEY::RZKEY_NUMPAD8;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_NUMPAD9] = Keyboard::RZKEY::RZKEY_NUMPAD9;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_NUMPAD_DIVIDE] = Keyboard::RZKEY::RZKEY_NUMPAD_DIVIDE;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_NUMPAD_MULTIPLY] = Keyboard::RZKEY::RZKEY_NUMPAD_MULTIPLY;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_NUMPAD_SUBTRACT] = Keyboard::RZKEY::RZKEY_NUMPAD_SUBTRACT;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_NUMPAD_ADD] = Keyboard::RZKEY::RZKEY_NUMPAD_ADD;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_NUMPAD_ENTER] = Keyboard::RZKEY::RZKEY_NUMPAD_ENTER;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_NUMPAD_DECIMAL] = Keyboard::RZKEY::RZKEY_NUMPAD_DECIMAL;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_PRINTSCREEN] = Keyboard::RZKEY::RZKEY_PRINTSCREEN;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_SCROLL] = Keyboard::RZKEY::RZKEY_SCROLL;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_PAUSE] = Keyboard::RZKEY::RZKEY_PAUSE;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_INSERT] = Keyboard::RZKEY::RZKEY_INSERT;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_HOME] = Keyboard::RZKEY::RZKEY_HOME;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_PAGEUP] = Keyboard::RZKEY::RZKEY_PAGEUP;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_DELETE] = Keyboard::RZKEY::RZKEY_DELETE;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_END] = Keyboard::RZKEY::RZKEY_END;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_PAGEDOWN] = Keyboard::RZKEY::RZKEY_PAGEDOWN;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_UP] = Keyboard::RZKEY::RZKEY_UP;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_LEFT] = Keyboard::RZKEY::RZKEY_LEFT;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_DOWN] = Keyboard::RZKEY::RZKEY_DOWN;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_RIGHT] = Keyboard::RZKEY::RZKEY_RIGHT;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_TAB] = Keyboard::RZKEY::RZKEY_TAB;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_CAPSLOCK] = Keyboard::RZKEY::RZKEY_CAPSLOCK;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_BACKSPACE] = Keyboard::RZKEY::RZKEY_BACKSPACE;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_ENTER] = Keyboard::RZKEY::RZKEY_ENTER;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_LCTRL] = Keyboard::RZKEY::RZKEY_LCTRL;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_LWIN] = Keyboard::RZKEY::RZKEY_LWIN;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_LALT] = Keyboard::RZKEY::RZKEY_LALT;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_SPACE] = Keyboard::RZKEY::RZKEY_SPACE;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_RALT] = Keyboard::RZKEY::RZKEY_RALT;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_FN] = Keyboard::RZKEY::RZKEY_FN;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_RMENU] = Keyboard::RZKEY::RZKEY_RMENU;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_RCTRL] = Keyboard::RZKEY::RZKEY_RCTRL;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_LSHIFT] = Keyboard::RZKEY::RZKEY_LSHIFT;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_RSHIFT] = Keyboard::RZKEY::RZKEY_RSHIFT;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_MACRO1] = Keyboard::RZKEY::RZKEY_MACRO1;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_MACRO2] = Keyboard::RZKEY::RZKEY_MACRO2;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_MACRO3] = Keyboard::RZKEY::RZKEY_MACRO3;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_MACRO4] = Keyboard::RZKEY::RZKEY_MACRO4;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_MACRO5] = Keyboard::RZKEY::RZKEY_MACRO5;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_OEM_1] = Keyboard::RZKEY::RZKEY_OEM_1;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_OEM_2] = Keyboard::RZKEY::RZKEY_OEM_2;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_OEM_3] = Keyboard::RZKEY::RZKEY_OEM_3;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_OEM_4] = Keyboard::RZKEY::RZKEY_OEM_4;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_OEM_5] = Keyboard::RZKEY::RZKEY_OEM_5;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_OEM_6] = Keyboard::RZKEY::RZKEY_OEM_6;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_OEM_7] = Keyboard::RZKEY::RZKEY_OEM_7;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_OEM_8] = Keyboard::RZKEY::RZKEY_OEM_8;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_OEM_9] = Keyboard::RZKEY::RZKEY_OEM_9;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_OEM_10] = Keyboard::RZKEY::RZKEY_OEM_10;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_OEM_11] = Keyboard::RZKEY::RZKEY_OEM_11;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_EUR_1] = Keyboard::RZKEY::RZKEY_EUR_1;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_EUR_2] = Keyboard::RZKEY::RZKEY_EUR_2;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_JPN_1] = Keyboard::RZKEY::RZKEY_JPN_1;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_JPN_2] = Keyboard::RZKEY::RZKEY_JPN_2;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_JPN_3] = Keyboard::RZKEY::RZKEY_JPN_3;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_JPN_4] = Keyboard::RZKEY::RZKEY_JPN_4;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_JPN_5] = Keyboard::RZKEY::RZKEY_JPN_5;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_KOR_1] = Keyboard::RZKEY::RZKEY_KOR_1;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_KOR_2] = Keyboard::RZKEY::RZKEY_KOR_2;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_KOR_3] = Keyboard::RZKEY::RZKEY_KOR_3;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_KOR_4] = Keyboard::RZKEY::RZKEY_KOR_4;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_KOR_5] = Keyboard::RZKEY::RZKEY_KOR_5;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_KOR_6] = Keyboard::RZKEY::RZKEY_KOR_6;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_KOR_7] = Keyboard::RZKEY::RZKEY_KOR_7;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_LOGO] = Keyboard::RZLED::RZLED_LOGO;
	_mKeyboardEnumMap[EChromaSDKKeyboardKey::KK_INVALID] = Keyboard::RZKEY::RZKEY_INVALID;

	// mouse mapping
	_mMouseEnumMap[EChromaSDKMouseLed::ML_SCROLLWHEEL] = Mouse::RZLED2::RZLED2_SCROLLWHEEL;
	_mMouseEnumMap[EChromaSDKMouseLed::ML_LOGO] = Mouse::RZLED2::RZLED2_LOGO;
	_mMouseEnumMap[EChromaSDKMouseLed::ML_BACKLIGHT] = Mouse::RZLED2::RZLED2_BACKLIGHT;
	_mMouseEnumMap[EChromaSDKMouseLed::ML_LEFT_SIDE1] = Mouse::RZLED2::RZLED2_LEFT_SIDE1;
	_mMouseEnumMap[EChromaSDKMouseLed::ML_LEFT_SIDE2] = Mouse::RZLED2::RZLED2_LEFT_SIDE2;
	_mMouseEnumMap[EChromaSDKMouseLed::ML_LEFT_SIDE3] = Mouse::RZLED2::RZLED2_LEFT_SIDE3;
	_mMouseEnumMap[EChromaSDKMouseLed::ML_LEFT_SIDE4] = Mouse::RZLED2::RZLED2_LEFT_SIDE4;
	_mMouseEnumMap[EChromaSDKMouseLed::ML_LEFT_SIDE5] = Mouse::RZLED2::RZLED2_LEFT_SIDE5;
	_mMouseEnumMap[EChromaSDKMouseLed::ML_LEFT_SIDE6] = Mouse::RZLED2::RZLED2_LEFT_SIDE6;
	_mMouseEnumMap[EChromaSDKMouseLed::ML_LEFT_SIDE7] = Mouse::RZLED2::RZLED2_LEFT_SIDE7;
	_mMouseEnumMap[EChromaSDKMouseLed::ML_BOTTOM1] = Mouse::RZLED2::RZLED2_BOTTOM1;
	_mMouseEnumMap[EChromaSDKMouseLed::ML_BOTTOM2] = Mouse::RZLED2::RZLED2_BOTTOM2;
	_mMouseEnumMap[EChromaSDKMouseLed::ML_BOTTOM3] = Mouse::RZLED2::RZLED2_BOTTOM3;
	_mMouseEnumMap[EChromaSDKMouseLed::ML_BOTTOM4] = Mouse::RZLED2::RZLED2_BOTTOM4;
	_mMouseEnumMap[EChromaSDKMouseLed::ML_BOTTOM5] = Mouse::RZLED2::RZLED2_BOTTOM5;
	_mMouseEnumMap[EChromaSDKMouseLed::ML_RIGHT_SIDE1] = Mouse::RZLED2::RZLED2_RIGHT_SIDE1;
	_mMouseEnumMap[EChromaSDKMouseLed::ML_RIGHT_SIDE2] = Mouse::RZLED2::RZLED2_RIGHT_SIDE2;
	_mMouseEnumMap[EChromaSDKMouseLed::ML_RIGHT_SIDE3] = Mouse::RZLED2::RZLED2_RIGHT_SIDE3;
	_mMouseEnumMap[EChromaSDKMouseLed::ML_RIGHT_SIDE4] = Mouse::RZLED2::RZLED2_RIGHT_SIDE4;
	_mMouseEnumMap[EChromaSDKMouseLed::ML_RIGHT_SIDE5] = Mouse::RZLED2::RZLED2_RIGHT_SIDE5;
	_mMouseEnumMap[EChromaSDKMouseLed::ML_RIGHT_SIDE6] = Mouse::RZLED2::RZLED2_RIGHT_SIDE6;
	_mMouseEnumMap[EChromaSDKMouseLed::ML_RIGHT_SIDE7] = Mouse::RZLED2::RZLED2_RIGHT_SIDE7;
}

ChromaSDKPlugin::~ChromaSDKPlugin()
{
	ChromaSDKUnInit();
}

ChromaSDKPlugin* ChromaSDKPlugin::GetInstance()
{
	return _sInstance;
}

RZRESULT ChromaSDKPlugin::ChromaSDKInit()
{
	if (_mMethodInit == nullptr)
	{
		fprintf(stderr, "ChromaSDKPlugin Init method is not set!\r\n");
		return -1;
	}

	int result = _mMethodInit();
	fprintf(stdout, "ChromaSDKPlugin Init Result=%d\r\n", result);
	return result;
}

RZRESULT ChromaSDKPlugin::ChromaSDKUnInit()
{
	if (_mMethodUnInit == nullptr)
	{
		fprintf(stderr, "ChromaSDKPlugin UnInit method is not set!\r\n");
		return -1;
	}

	int result = _mMethodUnInit();
	fprintf(stdout, "ChromaSDKPlugin UnInit Result=%d\r\n", result);
	return result;
}

RZRESULT ChromaSDKPlugin::ChromaSDKCreateEffect(RZDEVICEID deviceId, EFFECT_TYPE effect, PRZPARAM pParam, RZEFFECTID* pEffectId)
{
	if (_mMethodCreateEffect == nullptr)
	{
		fprintf(stderr, "ChromaSDKPlugin CreateEffect method is not set!\r\n");
		return -1;
	}

	return _mMethodCreateEffect(deviceId, effect, pParam, pEffectId);
}

RZRESULT ChromaSDKPlugin::ChromaSDKCreateChromaLinkEffect(ChromaLink::EFFECT_TYPE effect, PRZPARAM pParam, RZEFFECTID* pEffectId)
{
	if (_mMethodCreateChromaLinkEffect == nullptr)
	{
		fprintf(stderr, "ChromaSDKPlugin CreateChromaLinkEffect method is not set!\r\n");
		return -1;
	}

	return _mMethodCreateChromaLinkEffect(effect, pParam, pEffectId);
}

RZRESULT ChromaSDKPlugin::ChromaSDKCreateHeadsetEffect(Headset::EFFECT_TYPE effect, PRZPARAM pParam, RZEFFECTID* pEffectId)
{
	if (_mMethodCreateHeadsetEffect == nullptr)
	{
		fprintf(stderr, "ChromaSDKPlugin CreateHeadsetEffect method is not set!\r\n");
		return -1;
	}

	return _mMethodCreateHeadsetEffect(effect, pParam, pEffectId);
}

RZRESULT ChromaSDKPlugin::ChromaSDKCreateKeyboardEffect(Keyboard::EFFECT_TYPE effect, PRZPARAM pParam, RZEFFECTID* pEffectId)
{
	if (_mMethodCreateKeyboardEffect == nullptr)
	{
		fprintf(stderr, "ChromaSDKPlugin CreateKeyboardEffect method is not set!\r\n");
		return -1;
	}

	return _mMethodCreateKeyboardEffect(effect, pParam, pEffectId);
}

RZRESULT ChromaSDKPlugin::ChromaSDKCreateKeypadEffect(Keypad::EFFECT_TYPE effect, PRZPARAM pParam, RZEFFECTID* pEffectId)
{
	if (_mMethodCreateKeypadEffect == nullptr)
	{
		fprintf(stderr, "ChromaSDKPlugin CreateKeypadEffect method is not set!\r\n");
		return -1;
	}

	return _mMethodCreateKeypadEffect(effect, pParam, pEffectId);
}

RZRESULT ChromaSDKPlugin::ChromaSDKCreateMouseEffect(Mouse::EFFECT_TYPE effect, PRZPARAM pParam, RZEFFECTID* pEffectId)
{
	if (_mMethodCreateMouseEffect == nullptr)
	{
		fprintf(stderr, "ChromaSDKPlugin CreateMouseEffect method is not set!\r\n");
		return -1;
	}

	return _mMethodCreateMouseEffect(effect, pParam, pEffectId);
}

RZRESULT ChromaSDKPlugin::ChromaSDKCreateMousepadEffect(Mousepad::EFFECT_TYPE effect, PRZPARAM pParam, RZEFFECTID* pEffectId)
{
	if (_mMethodCreateMousepadEffect == nullptr)
	{
		fprintf(stderr, "ChromaSDKPlugin CreateMousepadEffect method is not set!\r\n");
		return -1;
	}

	return _mMethodCreateMousepadEffect(effect, pParam, pEffectId);
}

RZRESULT ChromaSDKPlugin::ChromaSDKSetEffect(RZEFFECTID effectId)
{
	if (_mMethodSetEffect == nullptr)
	{
		fprintf(stderr, "ChromaSDKPlugin SetEffect method is not set!\r\n");
		return -1;
	}

	return _mMethodSetEffect(effectId);
}

RZRESULT ChromaSDKPlugin::ChromaSDKDeleteEffect(RZEFFECTID effectId)
{
	if (_mMethodDeleteEffect == nullptr)
	{
		fprintf(stderr, "ChromaSDKPlugin DeleteEffect method is not set!\r\n");
		return -1;
	}

	return _mMethodDeleteEffect(effectId);
}

int ChromaSDKPlugin::GetMaxLeds(const EChromaSDKDevice1DEnum& device)
{
	switch (device)
	{
	case EChromaSDKDevice1DEnum::DE_ChromaLink:
		return ChromaLink::MAX_LEDS;
	case EChromaSDKDevice1DEnum::DE_Headset:
		return Headset::MAX_LEDS;
	case EChromaSDKDevice1DEnum::DE_Mousepad:
		return Mousepad::MAX_LEDS;
	}
	return 0;
}

int ChromaSDKPlugin::GetMaxRow(const EChromaSDKDevice2DEnum& device)
{
	switch (device)
	{
	case EChromaSDKDevice2DEnum::DE_Keyboard:
		return Keyboard::MAX_ROW;
	case EChromaSDKDevice2DEnum::DE_Keypad:
		return Keypad::MAX_ROW;
	case EChromaSDKDevice2DEnum::DE_Mouse:
		return Mouse::MAX_ROW;
	}
	return 0;
}

int ChromaSDKPlugin::GetMaxColumn(const EChromaSDKDevice2DEnum& device)
{
	switch (device)
	{
	case EChromaSDKDevice2DEnum::DE_Keyboard:
		return Keyboard::MAX_COLUMN;
	case EChromaSDKDevice2DEnum::DE_Keypad:
		return Keypad::MAX_COLUMN;
	case EChromaSDKDevice2DEnum::DE_Mouse:
		return Mouse::MAX_COLUMN;
	}
	return 0;
}

vector<COLORREF> ChromaSDKPlugin::CreateColors1D(const EChromaSDKDevice1DEnum& device)
{
	vector<COLORREF> colors = vector<COLORREF>();
	int elements = GetMaxLeds(device);
	COLORREF black = RGB(0, 0, 0);
	for (int i = 0; i < elements; ++i)
	{
		colors.push_back(black);
	}
	return colors;
}

vector<FChromaSDKColors> ChromaSDKPlugin::CreateColors2D(const EChromaSDKDevice2DEnum& device)
{
	vector<FChromaSDKColors> result = vector<FChromaSDKColors>();
	int maxRow = GetMaxRow(device);
	int maxColumn = GetMaxColumn(device);
	COLORREF black = RGB(0, 0, 0);
	for (int i = 0; i < maxRow; ++i)
	{
		FChromaSDKColors row = FChromaSDKColors();
		for (int j = 0; j < maxColumn; ++j)
		{
			row.Colors.push_back(black);
		}
		result.push_back(row);
	}
	return result;
}

vector<COLORREF> ChromaSDKPlugin::CreateRandomColors1D(const EChromaSDKDevice1DEnum& device)
{
	vector<COLORREF> colors = vector<COLORREF>();
	int elements = GetMaxLeds(device);
	for (int i = 0; i < elements; ++i)
	{
		int red = rand() % 256;
		int green = rand() % 256;
		int blue = rand() % 256;
		COLORREF color = RGB(red, green, blue);
		colors.push_back(color);
	}
	return colors;
}

vector<FChromaSDKColors> ChromaSDKPlugin::CreateRandomColors2D(const EChromaSDKDevice2DEnum& device)
{
	vector<FChromaSDKColors> result = vector<FChromaSDKColors>();
	int maxRows = GetMaxRow(device);
	int maxColumns = GetMaxColumn(device);
	for (int i = 0; i < maxRows; ++i)
	{
		FChromaSDKColors row = FChromaSDKColors();
		for (int j = 0; j < maxColumns; ++j)
		{
			int red = rand() % 256;
			int green = rand() % 256;
			int blue = rand() % 256;
			COLORREF color = RGB(red, green, blue);
			row.Colors.push_back(color);
		}
		result.push_back(row);
	}
	return result;
}

const vector<FChromaSDKColors>& ChromaSDKPlugin::SetKeyboardKeyColor(const EChromaSDKKeyboardKey& key, COLORREF color, vector<FChromaSDKColors>& colors)
{
	int maxRow = Keyboard::MAX_ROW;
	int maxColumn = Keyboard::MAX_COLUMN;
	if (maxRow != colors.size() ||
		colors.size() == 0 ||
		maxColumn != colors[0].Colors.size())
	{
		fprintf(stderr, "ChromaSDKPlugin::SetKeyboardKeyColor Array size mismatch row: %d==%d column: %d==%d!\r\n",
			maxRow,
			colors.size(),
			maxColumn,
			colors.size() > 0 ? colors[0].Colors.size() : 0);
		return colors;
	}

	int rzkey = _mKeyboardEnumMap[key];
	if (rzkey != Keyboard::RZKEY::RZKEY_INVALID)
	{
		colors[HIBYTE(rzkey)].Colors[LOBYTE(rzkey)] = color;
	}
	return colors;
}

const vector<FChromaSDKColors>& ChromaSDKPlugin::SetMouseLedColor(const EChromaSDKMouseLed& led, COLORREF color, vector<FChromaSDKColors>& colors)
{
	int maxRow = Mouse::MAX_ROW;
	int maxColumn = Mouse::MAX_COLUMN;
	if (maxRow != colors.size() ||
		colors.size() == 0 ||
		maxColumn != colors[0].Colors.size())
	{
		fprintf(stderr, "ChromaSDKPlugin::SetMouseLedColor Array size mismatch row: %d==%d column: %d==%d!\r\n",
			maxRow,
			colors.size(),
			maxColumn,
			colors.size() > 0 ? colors[0].Colors.size() : 0);
		return colors;
	}

	Mouse::RZLED2 rzled = _mMouseEnumMap[led];
	colors[HIBYTE(rzled)].Colors[LOBYTE(rzled)] = color;
	return colors;
}

FChromaSDKEffectResult ChromaSDKPlugin::CreateEffectNone1D(const EChromaSDKDevice1DEnum& device)
{
	fprintf(stdout, "ChromaSDKPlugin::CreateEffectNone1D Invoke.\r\n");

	FChromaSDKEffectResult data = FChromaSDKEffectResult();

	RZRESULT result = 0;
	RZEFFECTID effectId = RZEFFECTID();
	switch (device)
	{
	case EChromaSDKDevice1DEnum::DE_ChromaLink:
		result = ChromaSDKCreateChromaLinkEffect(ChromaLink::CHROMA_NONE, NULL, &effectId);
		break;
	case EChromaSDKDevice1DEnum::DE_Headset:
		result = ChromaSDKCreateHeadsetEffect(Headset::CHROMA_NONE, NULL, &effectId);
		break;
	case EChromaSDKDevice1DEnum::DE_Mousepad:
		result = ChromaSDKCreateMousepadEffect(Mousepad::CHROMA_NONE, NULL, &effectId);
		break;
	default:
		fprintf(stderr, "ChromaSDKPlugin::CreateEffectNone1D Unsupported device used!\r\n");
		break;
	}
	data.EffectId.Data = effectId;
	data.Result = result;

	fprintf(stdout, "ChromaSDKPlugin::CreateEffectNone1D Result=%d.\r\n", data.Result);

	return data;
}

FChromaSDKEffectResult ChromaSDKPlugin::CreateEffectNone2D(const EChromaSDKDevice2DEnum& device)
{
	fprintf(stdout, "ChromaSDKPlugin::CreateEffectNone2D Invoke.\r\n");

	FChromaSDKEffectResult data = FChromaSDKEffectResult();

	int result = 0;
	RZEFFECTID effectId = RZEFFECTID();
	switch (device)
	{
	case EChromaSDKDevice2DEnum::DE_Keyboard:
		result = ChromaSDKCreateKeyboardEffect(Keyboard::CHROMA_NONE, NULL, &effectId);
		break;
	case EChromaSDKDevice2DEnum::DE_Keypad:
		result = ChromaSDKCreateKeypadEffect(Keypad::CHROMA_NONE, NULL, &effectId);
		break;
	case EChromaSDKDevice2DEnum::DE_Mouse:
		result = ChromaSDKCreateMouseEffect(Mouse::CHROMA_NONE, NULL, &effectId);
		break;
	default:
		fprintf(stderr, "ChromaSDKPlugin::CreateEffectNone2D Unsupported device used!\r\n");
		break;
	}
	data.EffectId.Data = effectId;
	data.Result = result;

	fprintf(stdout, "ChromaSDKPlugin::CreateEffectNone2D Result=%d.\r\n", data.Result);

	return data;
}

FChromaSDKEffectResult ChromaSDKPlugin::CreateEffectStatic1D(const EChromaSDKDevice1DEnum& device, COLORREF color)
{
	FChromaSDKEffectResult data = FChromaSDKEffectResult();

	RZRESULT result = 0;
	RZEFFECTID effectId = RZEFFECTID();
	switch (device)
	{
	case EChromaSDKDevice1DEnum::DE_ChromaLink:
	{
		ChromaLink::STATIC_EFFECT_TYPE pParam = {};
		pParam.Color = color;
		result = ChromaSDKCreateChromaLinkEffect(ChromaLink::CHROMA_STATIC, &pParam, &effectId);
	}
	break;
	case EChromaSDKDevice1DEnum::DE_Headset:
	{
		Headset::STATIC_EFFECT_TYPE pParam = {};
		pParam.Color = color;
		result = ChromaSDKCreateHeadsetEffect(Headset::CHROMA_STATIC, &pParam, &effectId);
	}
	break;
	case EChromaSDKDevice1DEnum::DE_Mousepad:
	{
		Mousepad::STATIC_EFFECT_TYPE pParam = {};
		pParam.Color = color;
		result = ChromaSDKCreateMousepadEffect(Mousepad::CHROMA_STATIC, &pParam, &effectId);
	}
	break;
	default:
		fprintf(stderr, "ChromaSDKPlugin::CreateEffectStatic1D Unsupported device used!\r\n");
		break;
	}
	data.EffectId.Data = effectId;
	data.Result = result;

	return data;
}

FChromaSDKEffectResult ChromaSDKPlugin::CreateEffectStatic2D(const EChromaSDKDevice2DEnum& device, COLORREF color)
{
	FChromaSDKEffectResult data = FChromaSDKEffectResult();

	RZRESULT result = 0;
	RZEFFECTID effectId = RZEFFECTID();
	switch (device)
	{
	case EChromaSDKDevice2DEnum::DE_Keyboard:
	{
		Keyboard::STATIC_EFFECT_TYPE pParam = {};
		pParam.Color = color;
		result = ChromaSDKCreateKeyboardEffect(Keyboard::CHROMA_STATIC, &pParam, &effectId);
	}
	break;
	case EChromaSDKDevice2DEnum::DE_Keypad:
	{
		Keypad::STATIC_EFFECT_TYPE pParam = {};
		pParam.Color = color;
		result = ChromaSDKCreateKeypadEffect(Keypad::CHROMA_STATIC, &pParam, &effectId);
	}
	break;
	case EChromaSDKDevice2DEnum::DE_Mouse:
	{
		Mouse::STATIC_EFFECT_TYPE pParam = {};
		pParam.Color = color;
		pParam.LEDId = Mouse::RZLED_ALL;
		result = ChromaSDKCreateMouseEffect(Mouse::CHROMA_STATIC, &pParam, &effectId);
	}
	break;
	default:
		fprintf(stderr, "ChromaSDKPlugin::CreateEffectStatic2D Unsupported device used!\r\n");
		break;
	}
	data.EffectId.Data = effectId;
	data.Result = result;

	return data;
}

FChromaSDKEffectResult ChromaSDKPlugin::CreateEffectCustom1D(const EChromaSDKDevice1DEnum& device, const vector<COLORREF>& colors)
{
	FChromaSDKEffectResult data = FChromaSDKEffectResult();

	RZRESULT result = 0;
	RZEFFECTID effectId = RZEFFECTID();
	int maxLeds = 0;
	switch (device)
	{
	case EChromaSDKDevice1DEnum::DE_ChromaLink:
	{
		maxLeds = ChromaLink::MAX_LEDS;
		if (maxLeds != colors.size())
		{
			fprintf(stderr, "ChromaSDKPlugin::CreateEffectCustom1D Array size mismatch elements: %d==%d!\r\n",
				maxLeds,
				colors.size());
			break;
		}
		ChromaLink::CUSTOM_EFFECT_TYPE pParam = {};
		for (int i = 0; i < maxLeds; i++)
		{
			pParam.Color[i] = colors[i];
		}
		result = ChromaSDKCreateChromaLinkEffect(ChromaLink::CHROMA_CUSTOM, &pParam, &effectId);
	}
	break;
	case EChromaSDKDevice1DEnum::DE_Headset:
	{
		maxLeds = Headset::MAX_LEDS;
		if (maxLeds != colors.size())
		{
			fprintf(stderr, "ChromaSDKPlugin::CreateEffectCustom1D Array size mismatch elements: %d==%d!\r\n",
				maxLeds,
				colors.size());
			break;
		}
		Headset::CUSTOM_EFFECT_TYPE pParam = {};
		for (int i = 0; i < maxLeds; i++)
		{
			pParam.Color[i] = colors[i];
		}
		result = ChromaSDKCreateHeadsetEffect(Headset::CHROMA_CUSTOM, &pParam, &effectId);
	}
	break;
	case EChromaSDKDevice1DEnum::DE_Mousepad:
	{
		maxLeds = Mousepad::MAX_LEDS;
		if (maxLeds != colors.size())
		{
			fprintf(stderr, "ChromaSDKPlugin::CreateEffectCustom1D Array size mismatch elements: %d==%d!\r\n",
				maxLeds,
				colors.size());
			break;
		}
		Mousepad::CUSTOM_EFFECT_TYPE pParam = {};
		for (int i = 0; i < maxLeds; i++)
		{
			pParam.Color[i] = colors[i];
		}
		result = ChromaSDKCreateMousepadEffect(Mousepad::CHROMA_CUSTOM, &pParam, &effectId);
	}
	break;
	default:
		fprintf(stderr, "ChromaSDKPlugin::CreateEffectCustom1D Unsupported device used!\r\n");
		break;
	}
	data.EffectId.Data = effectId;
	data.Result = result;

	return data;
}

FChromaSDKEffectResult ChromaSDKPlugin::CreateEffectCustom2D(const EChromaSDKDevice2DEnum& device, const vector<FChromaSDKColors>& colors)
{
	FChromaSDKEffectResult data = FChromaSDKEffectResult();

	RZRESULT result = 0;
	RZEFFECTID effectId = RZEFFECTID();
	int maxRow = 0;
	int maxColumn = 0;
	switch (device)
	{
	case EChromaSDKDevice2DEnum::DE_Keyboard:
	{
		maxRow = Keyboard::MAX_ROW;
		maxColumn = Keyboard::MAX_COLUMN;
		if (maxRow != colors.size() ||
			(colors.size() > 0 &&
				maxColumn != colors[0].Colors.size()))
		{
			fprintf(stderr, "ChromaSDKPlugin::CreateEffectCustom2D Array size mismatch row: %d==%d column: %d==%d!\r\n",
				maxRow,
				colors.size(),
				maxColumn,
				colors.size() > 0 ? colors[0].Colors.size() : 0);
			break;
		}
		Keyboard::CUSTOM_EFFECT_TYPE pParam = {};
		for (int i = 0; i < maxRow; i++)
		{
			const FChromaSDKColors& row = colors[i];
			for (int j = 0; j < maxColumn; j++)
			{
				pParam.Color[i][j] = row.Colors[j];
			}
		}
		result = ChromaSDKCreateKeyboardEffect(Keyboard::CHROMA_CUSTOM, &pParam, &effectId);
	}
	break;
	case EChromaSDKDevice2DEnum::DE_Keypad:
	{
		maxRow = Keypad::MAX_ROW;
		maxColumn = Keypad::MAX_COLUMN;
		if (maxRow != colors.size() ||
			(colors.size() > 0 &&
				maxColumn != colors[0].Colors.size()))
		{
			fprintf(stderr, "ChromaSDKPlugin::CreateEffectCustom2D Array size mismatch row: %d==%d column: %d==%d!\r\n",
				maxRow,
				colors.size(),
				maxColumn,
				colors.size() > 0 ? colors[0].Colors.size() : 0);
			break;
		}
		Keypad::CUSTOM_EFFECT_TYPE pParam = {};
		for (int i = 0; i < maxRow; i++)
		{
			const FChromaSDKColors& row = colors[i];
			for (int j = 0; j < maxColumn; j++)
			{
				pParam.Color[i][j] = row.Colors[j];
			}
		}
		result = ChromaSDKCreateKeypadEffect(Keypad::CHROMA_CUSTOM, &pParam, &effectId);
	}
	break;
	case EChromaSDKDevice2DEnum::DE_Mouse:
	{
		maxRow = Mouse::MAX_ROW;
		maxColumn = Mouse::MAX_COLUMN;
		if (maxRow != colors.size() ||
			(colors.size() > 0 &&
				maxColumn != colors[0].Colors.size()))
		{
			fprintf(stderr, "ChromaSDKPlugin::CreateEffectCustom2D Array size mismatch row: %d==%d column: %d==%d!\r\n",
				maxRow,
				colors.size(),
				maxColumn,
				colors.size() > 0 ? colors[0].Colors.size() : 0);
			break;
		}
		Mouse::CUSTOM_EFFECT_TYPE2 pParam = {};
		for (int i = 0; i < maxRow; i++)
		{
			const FChromaSDKColors& row = colors[i];
			for (int j = 0; j < maxColumn; j++)
			{
				pParam.Color[i][j] = row.Colors[j];
			}
		}
		result = ChromaSDKCreateMouseEffect(Mouse::CHROMA_CUSTOM2, &pParam, &effectId);
	}
	break;
	default:
		fprintf(stderr, "ChromaSDKPlugin::CreateEffectCustom2D Unsupported device used!\r\n");
		break;
	}
	data.EffectId.Data = effectId;
	data.Result = result;

	return data;
}

RZRESULT ChromaSDKPlugin::SetEffect(const FChromaSDKGuid& effectId)
{
	fprintf(stdout, "ChromaSDKPlugin::SetEffect Invoke.\r\n");
	RZRESULT result = ChromaSDKSetEffect(effectId.Data);
	fprintf(stdout, "ChromaSDKPlugin::SetEffect Result=%d.\r\n", result);
	return result;
}

RZRESULT ChromaSDKPlugin::DeleteEffect(const FChromaSDKGuid& effectId)
{
	fprintf(stdout, "ChromaSDKPlugin::DeleteEffect Invoke.\r\n");
	RZRESULT result = ChromaSDKDeleteEffect(effectId.Data);
	fprintf(stdout, "ChromaSDKPlugin::DeleteEffect Result=%d.\r\n", result);
	return result;
}
