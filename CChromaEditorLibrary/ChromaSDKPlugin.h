#pragma once

#include <Windows.h>
#include "RzChromaSDKDefines.h"
#include "RzChromaSDKTypes.h"
#include "RzErrors.h"

typedef RZRESULT(*CHROMA_SDK_INIT)(void);
typedef RZRESULT(*CHROMA_SDK_UNINIT)(void);
typedef RZRESULT(*CHROMA_SDK_CREATE_EFFECT)(RZDEVICEID DeviceId, ChromaSDK::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
typedef RZRESULT(*CHROMA_SDK_CREATE_CHROMA_LINK_EFFECT)(ChromaSDK::ChromaLink::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
typedef RZRESULT(*CHROMA_SDK_CREATE_KEYBOARD_EFFECT)(ChromaSDK::Keyboard::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
typedef RZRESULT(*CHROMA_SDK_CREATE_KEYPAD_EFFECT)(ChromaSDK::Keypad::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
typedef RZRESULT(*CHROMA_SDK_CREATE_HEADSET_EFFECT)(ChromaSDK::Headset::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
typedef RZRESULT(*CHROMA_SDK_CREATE_MOUSE_EFFECT)(ChromaSDK::Mouse::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
typedef RZRESULT(*CHROMA_SDK_CREATE_MOUSEPAD_EFFECT)(ChromaSDK::Mousepad::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
typedef RZRESULT(*CHROMA_SDK_SET_EFFECT)(RZEFFECTID EffectId);
typedef RZRESULT(*CHROMA_SDK_DELETE_EFFECT)(RZEFFECTID EffectId);
typedef RZRESULT(*CHROMA_SDK_REGISTER_EVENT_NOTIFICATION)(HWND hWnd);
typedef RZRESULT(*CHROMA_SDK_UNREGISTER_EVENT_NOTIFICATION)(void);
typedef RZRESULT(*CHROMA_SDK_QUERY_DEVICE)(RZDEVICEID DeviceId, ChromaSDK::DEVICE_INFO_TYPE &DeviceInfo);

class ChromaSDKPlugin
{
public:
	ChromaSDKPlugin();
	~ChromaSDKPlugin();

	// SDK Methods
	int ChromaSDKInit();
	int ChromaSDKUnInit();
	RZRESULT ChromaSDKCreateEffect(RZDEVICEID deviceId, ChromaSDK::EFFECT_TYPE effect, PRZPARAM pParam, RZEFFECTID* pEffectId);
	RZRESULT ChromaSDKCreateChromaLinkEffect(ChromaSDK::ChromaLink::EFFECT_TYPE effect, PRZPARAM pParam, RZEFFECTID* pEffectId);
	RZRESULT ChromaSDKCreateHeadsetEffect(ChromaSDK::Headset::EFFECT_TYPE effect, PRZPARAM pParam, RZEFFECTID* pEffectId);
	RZRESULT ChromaSDKCreateKeyboardEffect(ChromaSDK::Keyboard::EFFECT_TYPE effect, PRZPARAM pParam, RZEFFECTID* pEffectId);
	RZRESULT ChromaSDKCreateKeypadEffect(ChromaSDK::Keypad::EFFECT_TYPE effect, PRZPARAM pParam, RZEFFECTID* pEffectId);
	RZRESULT ChromaSDKCreateMouseEffect(ChromaSDK::Mouse::EFFECT_TYPE effect, PRZPARAM pParam, RZEFFECTID* pEffectId);
	RZRESULT ChromaSDKCreateMousepadEffect(ChromaSDK::Mousepad::EFFECT_TYPE effect, PRZPARAM pParam, RZEFFECTID* pEffectId);
	RZRESULT ChromaSDKSetEffect(RZEFFECTID effectId);
	RZRESULT ChromaSDKDeleteEffect(RZEFFECTID effectId);
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
};
