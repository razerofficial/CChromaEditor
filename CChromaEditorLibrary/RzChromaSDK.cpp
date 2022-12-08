#include "stdafx.h"
#include "RzChromaSDK.h"
#include "ChromaLogger.h"
#include "RzErrors.h"
#include <filesystem>
#include "VerifyLibrarySignature.h"
#include <tchar.h>
#include <psapi.h>


#ifdef _WIN64
#define CHROMASDKDLL        L"RzChromaSDK64.dll"
#else
#define CHROMASDKDLL        L"RzChromaSDK.dll"
#endif


using namespace ChromaSDK;


HMODULE RzChromaSDK::_sLibrary = NULL;
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
	_sMethod ## FieldName = (Signature) GetProcAddress(_sLibrary, #FieldName); \
	if (_sMethod ## FieldName == nullptr) \
	{ \
		fprintf(stderr, "RzChromaSDK: Method not available! %s\r\n", #FieldName); \
		FreeLibrary(_sLibrary); \
		_sLibrary = NULL; \
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
	if (_sLibrary == NULL)
	{
		wchar_t pathTemp[MAX_PATH];
		GetModuleFileNameW(NULL, pathTemp, sizeof(pathTemp));

		std::wstring strPathCurrent;
		const size_t last_slash_idx = std::wstring(pathTemp).rfind('\\');
		if (std::string::npos != last_slash_idx)
		{
			strPathCurrent = std::wstring(pathTemp).substr(0, last_slash_idx);
		}

#ifdef USE_CHROMA_CLOUD
		std::wstring path = strPathCurrent;
		path += L"\\";
		path += CHROMASDKDLL;

		// check the library file version
		if (!VerifyLibrarySignature::IsFileVersionSameOrNewer(path, 1, 0, 0, 6))
		{
			ChromaLogger::fprintf(stderr, "Detected old version of Chroma SDK Library!\r\n");
			return RZRESULT_DLL_NOT_FOUND;
		}

		// verify the library has a valid signature
		_sInvalidSignature = !VerifyLibrarySignature::VerifyModule(path);
		if (_sInvalidSignature)
		{
			ChromaLogger::fprintf(stderr, "Chroma SDK Library has an invalid signature!\r\n");
			return RZRESULT_DLL_INVALID_SIGNATURE;
		}
#else
		// DLL Search Order:
		// 1. The directory from which the application loaded.
		// 2. The system directory.Use the GetSystemDirectory function to get the path of this directory.
		// 3. The 16 - bit system directory.There is no function that obtains the path of this directory, but it is searched.
		// 4. The Windows directory.Use the GetWindowsDirectory function to get the path of this directory.
		// 5. The current directory.
		// 6. The directories that are listed in the PATH environment variable.Note that this does not include the per - application path specified by the App Paths registry key.The App Paths key is not used when computing the DLL search path.
		std::vector<std::wstring> searchPaths;

		// #1
		searchPaths.push_back(strPathCurrent);

		// #2
		if (GetSystemDirectory(pathTemp, sizeof(pathTemp)))
		{
			std::wstring strPathSys = pathTemp;
			searchPaths.push_back(strPathSys);
		}

		// #4
		if (GetWindowsDirectory(pathTemp, sizeof(pathTemp)))
		{
			std::wstring strPathWin = pathTemp;
			searchPaths.push_back(strPathWin);
		}

		// #6
		DWORD envMaxSize = 65535; //Limit according to http://msdn.microsoft.com/en-us/library/ms683188.aspx
		std::wstring strEnvPath;
		strEnvPath.resize(envMaxSize);
		if (GetEnvironmentVariableW(L"PATH", &strEnvPath[0], envMaxSize))
		{
			const char delimiter = ';';
			size_t previous = 0;
			size_t index = strEnvPath.find(delimiter);
			while (index != std::wstring::npos)
			{
				searchPaths.push_back(strEnvPath.substr(previous, index - previous));
				previous = index + 1;
				index = strEnvPath.find(delimiter, previous);
			}
			searchPaths.push_back(strEnvPath.substr(previous));
		}

		// search DLL paths to check version and signature
		for (std::vector<std::wstring>::iterator it = searchPaths.begin(); it != searchPaths.end(); ++it)
		{
			std::wstring strPathSearch = *it;
			if (strPathSearch.length() > 0 && strPathSearch.compare(strPathSearch.length() - 1, 1, L"\\") != 0) //not endsWith slash
			{
				strPathSearch += L"\\";
			}
			strPathSearch += CHROMASDKDLL;

			// check if DLL exists in search path
			std::filesystem::path p = strPathSearch.c_str();
			std::error_code pathError;
			if (!std::filesystem::exists(p, pathError))
			{
				// not found
				continue;
			}

			// check the library file version
			if (!VerifyLibrarySignature::IsFileVersionSameOrNewer(strPathSearch, 3, 7, 3, 130))
			{
				ChromaLogger::fprintf(stderr, "Detected old version of Chroma SDK Library!\r\n");
				return RZRESULT_DLL_NOT_FOUND;
			}

			// verify the library has a valid signature
			_sInvalidSignature = !VerifyLibrarySignature::VerifyModule(strPathSearch);
			if (_sInvalidSignature)
			{
				ChromaLogger::fprintf(stderr, "Chroma SDK Library has an invalid signature!\r\n");
				return RZRESULT_DLL_INVALID_SIGNATURE;
			}

			break;
		}

		std::wstring path = CHROMASDKDLL;
#endif

		// load the library
		HMODULE library = LoadLibrary(path.c_str());
		if (library == NULL)
		{
			ChromaLogger::fprintf(stderr, "Failed to load Chroma SDK Library!\r\n");
			return RZRESULT_DLL_NOT_FOUND;
		}

		_sLibrary = library;
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

void RzChromaSDK::Unload()
{
	if (!_sLoaded)
	{
		return;
	}

	if (_sLibrary != nullptr)
	{
		FreeLibrary(_sLibrary);
		_sLibrary = nullptr;
	}
	_sLoaded = false;
}
