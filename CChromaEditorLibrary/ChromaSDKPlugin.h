#pragma once

#include "ChromaSDKPluginTypes.h"
#include <map>

class ChromaSDKPlugin
{
public:
	ChromaSDKPlugin();
	~ChromaSDKPlugin();

	// SDK Methods
	RZRESULT ChromaSDKInit();
	RZRESULT ChromaSDKUnInit();
	RZRESULT ChromaSDKCreateEffect(RZDEVICEID deviceId, ChromaSDK::EFFECT_TYPE effect, PRZPARAM pParam, RZEFFECTID* pEffectId);
	RZRESULT ChromaSDKCreateChromaLinkEffect(ChromaSDK::ChromaLink::EFFECT_TYPE effect, PRZPARAM pParam, RZEFFECTID* pEffectId);
	RZRESULT ChromaSDKCreateHeadsetEffect(ChromaSDK::Headset::EFFECT_TYPE effect, PRZPARAM pParam, RZEFFECTID* pEffectId);
	RZRESULT ChromaSDKCreateKeyboardEffect(ChromaSDK::Keyboard::EFFECT_TYPE effect, PRZPARAM pParam, RZEFFECTID* pEffectId);
	RZRESULT ChromaSDKCreateKeypadEffect(ChromaSDK::Keypad::EFFECT_TYPE effect, PRZPARAM pParam, RZEFFECTID* pEffectId);
	RZRESULT ChromaSDKCreateMouseEffect(ChromaSDK::Mouse::EFFECT_TYPE effect, PRZPARAM pParam, RZEFFECTID* pEffectId);
	RZRESULT ChromaSDKCreateMousepadEffect(ChromaSDK::Mousepad::EFFECT_TYPE effect, PRZPARAM pParam, RZEFFECTID* pEffectId);
	RZRESULT ChromaSDKSetEffect(RZEFFECTID effectId);
	RZRESULT ChromaSDKDeleteEffect(RZEFFECTID effectId);

	// Library Methods
	int GetMaxLeds(const EChromaSDKDevice1DEnum& device);
	int GetMaxRow(const EChromaSDKDevice2DEnum& device);
	int GetMaxColumn(const EChromaSDKDevice2DEnum& device);
	std::vector<COLORREF> CreateColors1D(const EChromaSDKDevice1DEnum& device);
	std::vector<FChromaSDKColors> CreateColors2D(const EChromaSDKDevice2DEnum& device);
	std::vector<COLORREF> CreateRandomColors1D(const EChromaSDKDevice1DEnum& device);
	std::vector<FChromaSDKColors> CreateRandomColors2D(const EChromaSDKDevice2DEnum& device);
	const std::vector<FChromaSDKColors>& SetKeyboardKeyColor(const EChromaSDKKeyboardKey& key, COLORREF color, std::vector<FChromaSDKColors>& colors);
	const std::vector<FChromaSDKColors>& SetMouseLedColor(const EChromaSDKMouseLed& led, COLORREF color, std::vector<FChromaSDKColors>& colors);
	bool IsInitialized();
	FChromaSDKEffectResult CreateEffectNone1D(const EChromaSDKDevice1DEnum& device);
	FChromaSDKEffectResult CreateEffectNone2D(const EChromaSDKDevice2DEnum& device);
	FChromaSDKEffectResult CreateEffectStatic1D(const EChromaSDKDevice1DEnum& device, COLORREF color);
	FChromaSDKEffectResult CreateEffectStatic2D(const EChromaSDKDevice2DEnum& device, COLORREF color);
	FChromaSDKEffectResult CreateEffectCustom1D(const EChromaSDKDevice1DEnum& device, const std::vector<COLORREF>& colors);
	FChromaSDKEffectResult CreateEffectCustom2D(const EChromaSDKDevice2DEnum& device, const std::vector<FChromaSDKColors>& colors);
	RZRESULT SetEffect(const FChromaSDKGuid& effectId);
	RZRESULT DeleteEffect(const FChromaSDKGuid& effectId);
private:
	bool ValidateGetProcAddress(bool condition, const char* methodName);

	HMODULE _mLibraryChroma = nullptr;

	CHROMA_SDK_INIT _mMethodInit = NULL;
	CHROMA_SDK_UNINIT _mMethodUnInit = NULL;
	CHROMA_SDK_CREATE_EFFECT _mMethodCreateEffect = NULL;
	CHROMA_SDK_CREATE_CHROMA_LINK_EFFECT _mMethodCreateChromaLinkEffect = NULL;
	CHROMA_SDK_CREATE_HEADSET_EFFECT _mMethodCreateHeadsetEffect = NULL;
	CHROMA_SDK_CREATE_KEYBOARD_EFFECT _mMethodCreateKeyboardEffect = NULL;
	CHROMA_SDK_CREATE_KEYPAD_EFFECT _mMethodCreateKeypadEffect = NULL;
	CHROMA_SDK_CREATE_MOUSE_EFFECT _mMethodCreateMouseEffect = NULL;
	CHROMA_SDK_CREATE_MOUSEPAD_EFFECT _mMethodCreateMousepadEffect = NULL;
	CHROMA_SDK_SET_EFFECT _mMethodSetEffect = NULL;
	CHROMA_SDK_DELETE_EFFECT _mMethodDeleteEffect = NULL;
	CHROMA_SDK_QUERY_DEVICE _mMethodQueryDevice = NULL;

	//handle enum mapping
	std::map<EChromaSDKKeyboardKey, int> _mKeyboardEnumMap;
	std::map<EChromaSDKMouseLed, ChromaSDK::Mouse::RZLED2> _mMouseEnumMap;
};
