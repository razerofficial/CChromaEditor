#include "stdafx.h"
#include "RzChromaSDK.h"
#include "RzErrors.h"
#include "VerifyLibrarySignature.h"
#include "ChromaLogger.h"
#include <tchar.h>


#ifdef _WIN64
#define CHROMASDKDLL        _T("RzChromaSDK64.dll")
#else
#define CHROMASDKDLL        _T("RzChromaSDK.dll")
#endif


using namespace ChromaSDK;


HMODULE RzChromaSDK::_sLibraryChroma = NULL;
bool RzChromaSDK::_sInvalidSignature = false;
bool RzChromaSDK::_sLoaded = false;

// assign static methods
#undef CHROMASDK_DECLARE_METHOD_IMPL
#define CHROMASDK_DECLARE_METHOD_IMPL(Signature, FieldName) Signature RzChromaSDK::_sMethod ## FieldName = NULL

// CORE API METHODS
CHROMASDK_DECLARE_METHOD_IMPL(CHROMA_SDK_INIT, Init);
CHROMASDK_DECLARE_METHOD_IMPL(CHROMA_SDK_INIT_SDK, InitSDK);
CHROMASDK_DECLARE_METHOD_IMPL(CHROMA_SDK_UNINIT, UnInit);
CHROMASDK_DECLARE_METHOD_IMPL(CHROMA_SDK_CREATE_EFFECT, CreateEffect);
CHROMASDK_DECLARE_METHOD_IMPL(CHROMA_SDK_CREATE_CHROMA_LINK_EFFECT, CreateChromaLinkEffect);
CHROMASDK_DECLARE_METHOD_IMPL(CHROMA_SDK_CREATE_KEYBOARD_EFFECT, CreateKeyboardEffect);
CHROMASDK_DECLARE_METHOD_IMPL(CHROMA_SDK_CREATE_KEYPAD_EFFECT, CreateKeypadEffect);
CHROMASDK_DECLARE_METHOD_IMPL(CHROMA_SDK_CREATE_HEADSET_EFFECT, CreateHeadsetEffect);
CHROMASDK_DECLARE_METHOD_IMPL(CHROMA_SDK_CREATE_MOUSE_EFFECT, CreateMouseEffect);
CHROMASDK_DECLARE_METHOD_IMPL(CHROMA_SDK_CREATE_MOUSEPAD_EFFECT, CreateMousepadEffect);
CHROMASDK_DECLARE_METHOD_IMPL(CHROMA_SDK_SET_EFFECT, SetEffect);
CHROMASDK_DECLARE_METHOD_IMPL(CHROMA_SDK_DELETE_EFFECT, DeleteEffect);
CHROMASDK_DECLARE_METHOD_IMPL(CHROMA_SDK_REGISTER_EVENT_NOTIFICATION, RegisterEventNotification);
CHROMASDK_DECLARE_METHOD_IMPL(CHROMA_SDK_UNREGISTER_EVENT_NOTIFICATION, UnregisterEventNotification);
CHROMASDK_DECLARE_METHOD_IMPL(CHROMA_SDK_QUERY_DEVICE, QueryDevice);


// validate static methods
#undef CHROMASDK_VALIDATE_METHOD
#define CHROMASDK_VALIDATE_METHOD(Signature, FieldName) if (_sMethod ## FieldName == nullptr) \
{ \
	_sMethod ## FieldName = (Signature) GetProcAddress(_sLibraryChroma, #FieldName); \
	if (_sMethod ## FieldName == nullptr) \
	{ \
		return RZRESULT_FAILED; \
	} \
}


RZRESULT RzChromaSDK::Init()
{
	RZRESULT state = GetLibraryLoadedState();
	if (state != RZRESULT_SUCCESS)
	{
		return state;
	}
	return _sMethodInit();
}

RZRESULT RzChromaSDK::InitSDK(ChromaSDK::APPINFOTYPE* AppInfo)
{
	RZRESULT state = GetLibraryLoadedState();
	if (state != RZRESULT_SUCCESS)
	{
		return state;
	}
	return _sMethodInitSDK(AppInfo);
}

RZRESULT RzChromaSDK::UnInit()
{
	RZRESULT state = GetLibraryLoadedState();
	if (state != RZRESULT_SUCCESS)
	{
		return state;
	}
	return _sMethodUnInit();
}

RZRESULT RzChromaSDK::CreateEffect(RZDEVICEID DeviceId, ChromaSDK::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId)
{
	RZRESULT state = GetLibraryLoadedState();
	if (state != RZRESULT_SUCCESS)
	{
		return state;
	}
	return _sMethodCreateEffect(DeviceId, Effect, pParam, pEffectId);
}

RZRESULT RzChromaSDK::CreateChromaLinkEffect(ChromaSDK::ChromaLink::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId)
{
	RZRESULT state = GetLibraryLoadedState();
	if (state != RZRESULT_SUCCESS)
	{
		return state;
	}
	return _sMethodCreateChromaLinkEffect(Effect, pParam, pEffectId);
}

RZRESULT RzChromaSDK::CreateKeyboardEffect(ChromaSDK::Keyboard::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId)
{
	RZRESULT state = GetLibraryLoadedState();
	if (state != RZRESULT_SUCCESS)
	{
		return state;
	}
	return _sMethodCreateKeyboardEffect(Effect, pParam, pEffectId);
}

RZRESULT RzChromaSDK::CreateKeypadEffect(ChromaSDK::Keypad::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId)
{
	RZRESULT state = GetLibraryLoadedState();
	if (state != RZRESULT_SUCCESS)
	{
		return state;
	}
	return _sMethodCreateKeypadEffect(Effect, pParam, pEffectId);
}

RZRESULT RzChromaSDK::CreateHeadsetEffect(ChromaSDK::Headset::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId)
{
	RZRESULT state = GetLibraryLoadedState();
	if (state != RZRESULT_SUCCESS)
	{
		return state;
	}
	return _sMethodCreateHeadsetEffect(Effect, pParam, pEffectId);
}

RZRESULT RzChromaSDK::CreateMouseEffect(ChromaSDK::Mouse::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId)
{
	RZRESULT state = GetLibraryLoadedState();
	if (state != RZRESULT_SUCCESS)
	{
		return state;
	}
	return _sMethodCreateMouseEffect(Effect, pParam, pEffectId);
}

RZRESULT RzChromaSDK::CreateMousepadEffect(ChromaSDK::Mousepad::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId)
{
	RZRESULT state = GetLibraryLoadedState();
	if (state != RZRESULT_SUCCESS)
	{
		return state;
	}
	return _sMethodCreateMousepadEffect(Effect, pParam, pEffectId);
}

RZRESULT RzChromaSDK::SetEffect(RZEFFECTID EffectId)
{
	RZRESULT state = GetLibraryLoadedState();
	if (state != RZRESULT_SUCCESS)
	{
		return state;
	}
	return _sMethodSetEffect(EffectId);
}

RZRESULT RzChromaSDK::DeleteEffect(RZEFFECTID EffectId)
{
	RZRESULT state = GetLibraryLoadedState();
	if (state != RZRESULT_SUCCESS)
	{
		return state;
	}
	return _sMethodDeleteEffect(EffectId);
}

RZRESULT RzChromaSDK::RegisterEventNotification(HWND hWnd)
{
	RZRESULT state = GetLibraryLoadedState();
	if (state != RZRESULT_SUCCESS)
	{
		return state;
	}
	return _sMethodRegisterEventNotification(hWnd);
}

RZRESULT RzChromaSDK::UnregisterEventNotification(void)
{
	RZRESULT state = GetLibraryLoadedState();
	if (state != RZRESULT_SUCCESS)
	{
		return state;
	}
	return _sMethodUnregisterEventNotification();
}

RZRESULT RzChromaSDK::QueryDevice(RZDEVICEID DeviceId, ChromaSDK::DEVICE_INFO_TYPE &DeviceInfo)
{
	RZRESULT state = GetLibraryLoadedState();
	if (state != RZRESULT_SUCCESS)
	{
		return state;
	}
	return _sMethodQueryDevice(DeviceId, DeviceInfo);
}

// EXTRA METHODS

RZRESULT RzChromaSDK::GetLibraryLoadedState()
{
	// abort load if an invalid signature was detected
	if (_sInvalidSignature)
	{
		return RZRESULT_DLL_INVALID_SIGNATURE;
	}

	// library has loaded and validation is complete
	if (_sLoaded)
	{
		return RZRESULT_SUCCESS;
	}

	// load the library if previously not loaded
	if (_sLibraryChroma == NULL)
	{
		// load the library
		_sLibraryChroma = LoadLibrary(CHROMASDKDLL);
		if (_sLibraryChroma == NULL)
		{
			return RZRESULT_DLL_NOT_FOUND;
		}

		// verify the library has a valid signature
		_sInvalidSignature = !ChromaSDK::VerifyLibrarySignature::VerifyModule(_sLibraryChroma);
 		if (_sInvalidSignature)
		{
			ChromaLogger::fprintf(stderr, "Failed to load Chroma library with invalid signature!\r\n");
			
			// unload the library
			FreeLibrary(_sLibraryChroma);
			_sLibraryChroma = NULL;

			return RZRESULT_DLL_INVALID_SIGNATURE;
		}
	}

	// CORE API METHODS
	CHROMASDK_VALIDATE_METHOD(CHROMA_SDK_INIT, Init);
	CHROMASDK_VALIDATE_METHOD(CHROMA_SDK_INIT_SDK, InitSDK);
	CHROMASDK_VALIDATE_METHOD(CHROMA_SDK_UNINIT, UnInit);
	CHROMASDK_VALIDATE_METHOD(CHROMA_SDK_CREATE_EFFECT, CreateEffect);
	CHROMASDK_VALIDATE_METHOD(CHROMA_SDK_CREATE_CHROMA_LINK_EFFECT, CreateChromaLinkEffect);
	CHROMASDK_VALIDATE_METHOD(CHROMA_SDK_CREATE_KEYBOARD_EFFECT, CreateKeyboardEffect);
	CHROMASDK_VALIDATE_METHOD(CHROMA_SDK_CREATE_KEYPAD_EFFECT, CreateKeypadEffect);
	CHROMASDK_VALIDATE_METHOD(CHROMA_SDK_CREATE_HEADSET_EFFECT, CreateHeadsetEffect);
	CHROMASDK_VALIDATE_METHOD(CHROMA_SDK_CREATE_MOUSE_EFFECT, CreateMouseEffect);
	CHROMASDK_VALIDATE_METHOD(CHROMA_SDK_CREATE_MOUSEPAD_EFFECT, CreateMousepadEffect);
	CHROMASDK_VALIDATE_METHOD(CHROMA_SDK_SET_EFFECT, SetEffect);
	CHROMASDK_VALIDATE_METHOD(CHROMA_SDK_DELETE_EFFECT, DeleteEffect);
	CHROMASDK_VALIDATE_METHOD(CHROMA_SDK_REGISTER_EVENT_NOTIFICATION, RegisterEventNotification);
	CHROMASDK_VALIDATE_METHOD(CHROMA_SDK_UNREGISTER_EVENT_NOTIFICATION, UnregisterEventNotification);
	CHROMASDK_VALIDATE_METHOD(CHROMA_SDK_QUERY_DEVICE, QueryDevice);

	_sLoaded = true;
	return RZRESULT_SUCCESS;
}
