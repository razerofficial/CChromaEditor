#pragma once

#include "RzChromaSDKTypes.h"

// CORE API METHODS
typedef RZRESULT(*CHROMA_SDK_INIT)(void);
typedef RZRESULT(*CHROMA_SDK_INIT_SDK)(ChromaSDK::APPINFOTYPE* AppInfo);
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

#undef CHROMASDK_DECLARE_METHOD
#define CHROMASDK_DECLARE_METHOD(Signature, FieldName) static Signature _sMethod ## FieldName


class RzChromaSDK
{
public:
	// Core API methods
	static RZRESULT Init();
	static RZRESULT InitSDK(ChromaSDK::APPINFOTYPE* AppInfo);
	static RZRESULT UnInit();
	static RZRESULT CreateEffect(RZDEVICEID DeviceId, ChromaSDK::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
	static RZRESULT CreateChromaLinkEffect(ChromaSDK::ChromaLink::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
	static RZRESULT CreateKeyboardEffect(ChromaSDK::Keyboard::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
	static RZRESULT CreateKeypadEffect(ChromaSDK::Keypad::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
	static RZRESULT CreateHeadsetEffect(ChromaSDK::Headset::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
	static RZRESULT CreateMouseEffect(ChromaSDK::Mouse::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
	static RZRESULT CreateMousepadEffect(ChromaSDK::Mousepad::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
	static RZRESULT SetEffect(RZEFFECTID EffectId);
	static RZRESULT DeleteEffect(RZEFFECTID EffectId);
	static RZRESULT RegisterEventNotification(HWND hWnd);
	static RZRESULT UnregisterEventNotification(void);
	static RZRESULT QueryDevice(RZDEVICEID DeviceId, ChromaSDK::DEVICE_INFO_TYPE &DeviceInfo);

	// Extra methods
	static RZRESULT GetLibraryLoadedState(); // call to preload the library

	static void Unload();

private:

	static HMODULE _sLibrary;
	static bool _sInvalidSignature;
	static bool _sLoaded;

	// Core API Methods
	CHROMASDK_DECLARE_METHOD(CHROMA_SDK_INIT, Init);
	CHROMASDK_DECLARE_METHOD(CHROMA_SDK_INIT_SDK, InitSDK);
	CHROMASDK_DECLARE_METHOD(CHROMA_SDK_UNINIT, UnInit);
	CHROMASDK_DECLARE_METHOD(CHROMA_SDK_CREATE_EFFECT, CreateEffect);
	CHROMASDK_DECLARE_METHOD(CHROMA_SDK_CREATE_CHROMA_LINK_EFFECT, CreateChromaLinkEffect);
	CHROMASDK_DECLARE_METHOD(CHROMA_SDK_CREATE_KEYBOARD_EFFECT, CreateKeyboardEffect);
	CHROMASDK_DECLARE_METHOD(CHROMA_SDK_CREATE_KEYPAD_EFFECT, CreateKeypadEffect);
	CHROMASDK_DECLARE_METHOD(CHROMA_SDK_CREATE_HEADSET_EFFECT, CreateHeadsetEffect);
	CHROMASDK_DECLARE_METHOD(CHROMA_SDK_CREATE_MOUSE_EFFECT, CreateMouseEffect);
	CHROMASDK_DECLARE_METHOD(CHROMA_SDK_CREATE_MOUSEPAD_EFFECT, CreateMousepadEffect);
	CHROMASDK_DECLARE_METHOD(CHROMA_SDK_SET_EFFECT, SetEffect);
	CHROMASDK_DECLARE_METHOD(CHROMA_SDK_DELETE_EFFECT, DeleteEffect);
	CHROMASDK_DECLARE_METHOD(CHROMA_SDK_REGISTER_EVENT_NOTIFICATION, RegisterEventNotification);
	CHROMASDK_DECLARE_METHOD(CHROMA_SDK_UNREGISTER_EVENT_NOTIFICATION, UnregisterEventNotification);
	CHROMASDK_DECLARE_METHOD(CHROMA_SDK_QUERY_DEVICE, QueryDevice);
};
