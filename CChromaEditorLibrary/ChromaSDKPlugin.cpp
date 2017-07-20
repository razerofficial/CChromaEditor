#include "stdafx.h"
#include "ChromaSDKPlugin.h"

#ifdef _WIN64
#define CHROMASDKDLL        _T("RzChromaSDK64.dll")
#else
#define CHROMASDKDLL        _T("RzChromaSDK.dll")
#endif

using namespace std;

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

FChromaSDKEffectResult ChromaSDKPlugin::CreateEffectNone1D(const EChromaSDKDevice1DEnum& device)
{
	fprintf(stdout, "ChromaSDKPlugin::CreateEffectNone1D Invoke.\r\n");

	FChromaSDKEffectResult data = FChromaSDKEffectResult();

	RZRESULT result = 0;
	RZEFFECTID effectId = RZEFFECTID();
	switch (device)
	{
	case EChromaSDKDevice1DEnum::DE_ChromaLink:
		result = ChromaSDKCreateChromaLinkEffect(ChromaSDK::ChromaLink::CHROMA_NONE, NULL, &effectId);
		break;
	case EChromaSDKDevice1DEnum::DE_Headset:
		result = ChromaSDKCreateHeadsetEffect(ChromaSDK::Headset::CHROMA_NONE, NULL, &effectId);
		break;
	case EChromaSDKDevice1DEnum::DE_Mousepad:
		result = ChromaSDKCreateMousepadEffect(ChromaSDK::Mousepad::CHROMA_NONE, NULL, &effectId);
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
		result = ChromaSDKCreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_NONE, NULL, &effectId);
		break;
	case EChromaSDKDevice2DEnum::DE_Keypad:
		result = ChromaSDKCreateKeypadEffect(ChromaSDK::Keypad::CHROMA_NONE, NULL, &effectId);
		break;
	case EChromaSDKDevice2DEnum::DE_Mouse:
		result = ChromaSDKCreateMouseEffect(ChromaSDK::Mouse::CHROMA_NONE, NULL, &effectId);
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
		ChromaSDK::ChromaLink::STATIC_EFFECT_TYPE pParam = {};
		pParam.Color = color;
		result = ChromaSDKCreateChromaLinkEffect(ChromaSDK::ChromaLink::CHROMA_STATIC, &pParam, &effectId);
	}
	break;
	case EChromaSDKDevice1DEnum::DE_Headset:
	{
		ChromaSDK::Headset::STATIC_EFFECT_TYPE pParam = {};
		pParam.Color = color;
		result = ChromaSDKCreateHeadsetEffect(ChromaSDK::Headset::CHROMA_STATIC, &pParam, &effectId);
	}
	break;
	case EChromaSDKDevice1DEnum::DE_Mousepad:
	{
		ChromaSDK::Mousepad::STATIC_EFFECT_TYPE pParam = {};
		pParam.Color = color;
		result = ChromaSDKCreateMousepadEffect(ChromaSDK::Mousepad::CHROMA_STATIC, &pParam, &effectId);
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
		ChromaSDK::Keyboard::STATIC_EFFECT_TYPE pParam = {};
		pParam.Color = color;
		result = ChromaSDKCreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_STATIC, &pParam, &effectId);
	}
	break;
	case EChromaSDKDevice2DEnum::DE_Keypad:
	{
		ChromaSDK::Keypad::STATIC_EFFECT_TYPE pParam = {};
		pParam.Color = color;
		result = ChromaSDKCreateKeypadEffect(ChromaSDK::Keypad::CHROMA_STATIC, &pParam, &effectId);
	}
	break;
	case EChromaSDKDevice2DEnum::DE_Mouse:
	{
		ChromaSDK::Mouse::STATIC_EFFECT_TYPE pParam = {};
		pParam.Color = color;
		pParam.LEDId = ChromaSDK::Mouse::RZLED_ALL;
		result = ChromaSDKCreateMouseEffect(ChromaSDK::Mouse::CHROMA_STATIC, &pParam, &effectId);
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
		maxLeds = ChromaSDK::ChromaLink::MAX_LEDS;
		if (maxLeds != colors.size())
		{
			fprintf(stderr, "ChromaSDKPlugin::CreateEffectCustom1D Array size mismatch elements: %d==%d!\r\n",
				maxLeds,
				colors.size());
			break;
		}
		ChromaSDK::ChromaLink::CUSTOM_EFFECT_TYPE pParam = {};
		for (int i = 0; i < maxLeds; i++)
		{
			pParam.Color[i] = colors[i];
		}
		result = ChromaSDKCreateChromaLinkEffect(ChromaSDK::ChromaLink::CHROMA_CUSTOM, &pParam, &effectId);
	}
	break;
	case EChromaSDKDevice1DEnum::DE_Headset:
	{
		maxLeds = ChromaSDK::Headset::MAX_LEDS;
		if (maxLeds != colors.size())
		{
			fprintf(stderr, "ChromaSDKPlugin::CreateEffectCustom1D Array size mismatch elements: %d==%d!\r\n",
				maxLeds,
				colors.size());
			break;
		}
		ChromaSDK::Headset::CUSTOM_EFFECT_TYPE pParam = {};
		for (int i = 0; i < maxLeds; i++)
		{
			pParam.Color[i] = colors[i];
		}
		result = ChromaSDKCreateHeadsetEffect(ChromaSDK::Headset::CHROMA_CUSTOM, &pParam, &effectId);
	}
	break;
	case EChromaSDKDevice1DEnum::DE_Mousepad:
	{
		maxLeds = ChromaSDK::Mousepad::MAX_LEDS;
		if (maxLeds != colors.size())
		{
			fprintf(stderr, "ChromaSDKPlugin::CreateEffectCustom1D Array size mismatch elements: %d==%d!\r\n",
				maxLeds,
				colors.size());
			break;
		}
		ChromaSDK::Mousepad::CUSTOM_EFFECT_TYPE pParam = {};
		for (int i = 0; i < maxLeds; i++)
		{
			pParam.Color[i] = colors[i];
		}
		result = ChromaSDKCreateMousepadEffect(ChromaSDK::Mousepad::CHROMA_CUSTOM, &pParam, &effectId);
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
		maxRow = ChromaSDK::Keyboard::MAX_ROW;
		maxColumn = ChromaSDK::Keyboard::MAX_COLUMN;
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
		ChromaSDK::Keyboard::CUSTOM_EFFECT_TYPE pParam = {};
		for (int i = 0; i < maxRow; i++)
		{
			const FChromaSDKColors& row = colors[i];
			for (int j = 0; j < maxColumn; j++)
			{
				pParam.Color[i][j] = row.Colors[j];
			}
		}
		result = ChromaSDKCreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_CUSTOM, &pParam, &effectId);
	}
	break;
	case EChromaSDKDevice2DEnum::DE_Keypad:
	{
		maxRow = ChromaSDK::Keypad::MAX_ROW;
		maxColumn = ChromaSDK::Keypad::MAX_COLUMN;
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
		ChromaSDK::Keypad::CUSTOM_EFFECT_TYPE pParam = {};
		for (int i = 0; i < maxRow; i++)
		{
			const FChromaSDKColors& row = colors[i];
			for (int j = 0; j < maxColumn; j++)
			{
				pParam.Color[i][j] = row.Colors[j];
			}
		}
		result = ChromaSDKCreateKeypadEffect(ChromaSDK::Keypad::CHROMA_CUSTOM, &pParam, &effectId);
	}
	break;
	case EChromaSDKDevice2DEnum::DE_Mouse:
	{
		maxRow = ChromaSDK::Mouse::MAX_ROW;
		maxColumn = ChromaSDK::Mouse::MAX_COLUMN;
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
		ChromaSDK::Mouse::CUSTOM_EFFECT_TYPE2 pParam = {};
		for (int i = 0; i < maxRow; i++)
		{
			const FChromaSDKColors& row = colors[i];
			for (int j = 0; j < maxColumn; j++)
			{
				pParam.Color[i][j] = row.Colors[j];
			}
		}
		result = ChromaSDKCreateMouseEffect(ChromaSDK::Mouse::CHROMA_CUSTOM2, &pParam, &effectId);
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
