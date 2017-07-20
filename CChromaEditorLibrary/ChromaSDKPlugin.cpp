#include "stdafx.h"
#include "ChromaSDKPlugin.h"

#ifdef _WIN64
#define CHROMASDKDLL        _T("RzChromaSDK64.dll")
#else
#define CHROMASDKDLL        _T("RzChromaSDK.dll")
#endif

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
}

ChromaSDKPlugin::~ChromaSDKPlugin()
{
	ChromaSDKUnInit();
}

RZRESULT ChromaSDKPlugin::ChromaSDKInit()
{
	if (_mMethodInit == nullptr)
	{
		fprintf(stderr, "ChromaSDKPlugin Init method is not set!\r\n");
		return -1;
	}

	return _mMethodInit();
}

RZRESULT ChromaSDKPlugin::ChromaSDKUnInit()
{
	if (_mMethodUnInit == nullptr)
	{
		fprintf(stderr, "ChromaSDKPlugin UnInit method is not set!\r\n");
		return -1;
	}

	return _mMethodUnInit();
}

RZRESULT ChromaSDKPlugin::ChromaSDKCreateEffect(RZDEVICEID deviceId, ChromaSDK::EFFECT_TYPE effect, PRZPARAM pParam, RZEFFECTID* pEffectId)
{
	if (_mMethodCreateEffect == nullptr)
	{
		fprintf(stderr, "ChromaSDKPlugin CreateEffect method is not set!\r\n");
		return -1;
	}

	return _mMethodCreateEffect(deviceId, effect, pParam, pEffectId);
}

RZRESULT ChromaSDKPlugin::ChromaSDKCreateChromaLinkEffect(ChromaSDK::ChromaLink::EFFECT_TYPE effect, PRZPARAM pParam, RZEFFECTID* pEffectId)
{
	if (_mMethodCreateChromaLinkEffect == nullptr)
	{
		fprintf(stderr, "ChromaSDKPlugin CreateChromaLinkEffect method is not set!\r\n");
		return -1;
	}

	return _mMethodCreateChromaLinkEffect(effect, pParam, pEffectId);
}

RZRESULT ChromaSDKPlugin::ChromaSDKCreateHeadsetEffect(ChromaSDK::Headset::EFFECT_TYPE effect, PRZPARAM pParam, RZEFFECTID* pEffectId)
{
	if (_mMethodCreateHeadsetEffect == nullptr)
	{
		fprintf(stderr, "ChromaSDKPlugin CreateHeadsetEffect method is not set!\r\n");
		return -1;
	}

	return _mMethodCreateHeadsetEffect(effect, pParam, pEffectId);
}

RZRESULT ChromaSDKPlugin::ChromaSDKCreateKeyboardEffect(ChromaSDK::Keyboard::EFFECT_TYPE effect, PRZPARAM pParam, RZEFFECTID* pEffectId)
{
	if (_mMethodCreateKeyboardEffect == nullptr)
	{
		fprintf(stderr, "ChromaSDKPlugin CreateKeyboardEffect method is not set!\r\n");
		return -1;
	}

	return _mMethodCreateKeyboardEffect(effect, pParam, pEffectId);
}

RZRESULT ChromaSDKPlugin::ChromaSDKCreateKeypadEffect(ChromaSDK::Keypad::EFFECT_TYPE effect, PRZPARAM pParam, RZEFFECTID* pEffectId)
{
	if (_mMethodCreateKeypadEffect == nullptr)
	{
		fprintf(stderr, "ChromaSDKPlugin CreateKeypadEffect method is not set!\r\n");
		return -1;
	}

	return _mMethodCreateKeypadEffect(effect, pParam, pEffectId);
}

RZRESULT ChromaSDKPlugin::ChromaSDKCreateMouseEffect(ChromaSDK::Mouse::EFFECT_TYPE effect, PRZPARAM pParam, RZEFFECTID* pEffectId)
{
	if (_mMethodCreateMouseEffect == nullptr)
	{
		fprintf(stderr, "ChromaSDKPlugin CreateMouseEffect method is not set!\r\n");
		return -1;
	}

	return _mMethodCreateMouseEffect(effect, pParam, pEffectId);
}

RZRESULT ChromaSDKPlugin::ChromaSDKCreateMousepadEffect(ChromaSDK::Mousepad::EFFECT_TYPE effect, PRZPARAM pParam, RZEFFECTID* pEffectId)
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
