#include "stdafx.h"
#include "RzChromaStreamPlugin.h"
#include "ChromaLogger.h"
#include "RzErrors.h"
#include <filesystem>
#include "VerifyLibrarySignature.h"
#include <tchar.h>
#include <stdio.h>
#include <psapi.h>


#ifdef _WIN64
#define CHROMA_STREAMING_DLL        L"RzChromaStreamPlugin64.dll"
#else
#define CHROMA_STREAMING_DLL        L"RzChromaStreamPlugin.dll"
#endif


using namespace ChromaSDK;


HMODULE RzChromaStreamPlugin::_sLibrary = NULL;
bool RzChromaStreamPlugin::_sInvalidSignature = false;
bool RzChromaStreamPlugin::_sLoaded = false;

// assign static methods
#undef STREAM_SDK_DECLARE_METHOD_IMPL
#define STREAM_SDK_DECLARE_METHOD_IMPL(Signature, FieldName) Signature RzChromaStreamPlugin::_sMethod ## FieldName = NULL

#pragma region Streaming
STREAM_SDK_DECLARE_METHOD_IMPL(CHROMA_SDK_STREAM_BROADCAST, StreamBroadcast);
STREAM_SDK_DECLARE_METHOD_IMPL(CHROMA_SDK_STREAM_BROADCAST_END, StreamBroadcastEnd);
STREAM_SDK_DECLARE_METHOD_IMPL(CHROMA_SDK_STREAM_GET_AUTH_SHORTCODE, StreamGetAuthShortcode);
STREAM_SDK_DECLARE_METHOD_IMPL(CHROMA_SDK_STREAM_GET_ID, StreamGetId);
STREAM_SDK_DECLARE_METHOD_IMPL(CHROMA_SDK_STREAM_GET_FOCUS, StreamGetFocus);
STREAM_SDK_DECLARE_METHOD_IMPL(CHROMA_SDK_STREAM_GET_KEY, StreamGetKey);
STREAM_SDK_DECLARE_METHOD_IMPL(CHROMA_SDK_STREAM_GET_STATUS, StreamGetStatus);
STREAM_SDK_DECLARE_METHOD_IMPL(CHROMA_SDK_STREAM_GET_STATUS_STRING, StreamGetStatusString);
STREAM_SDK_DECLARE_METHOD_IMPL(CHROMA_SDK_STREAM_RELEASE_SHORTCODE, StreamReleaseShortcode);
STREAM_SDK_DECLARE_METHOD_IMPL(CHROMA_SDK_STREAM_SET_FOCUS, StreamSetFocus);
STREAM_SDK_DECLARE_METHOD_IMPL(CHROMA_SDK_STREAM_WATCH, StreamWatch);
STREAM_SDK_DECLARE_METHOD_IMPL(CHROMA_SDK_STREAM_WATCH_END, StreamWatchEnd);
#pragma endregion


// validate static methods
#undef STREAM_SDK_VALIDATE_METHOD
#define STREAM_SDK_VALIDATE_METHOD(Signature, FieldName) if (_sMethod ## FieldName == nullptr) \
{ \
	_sMethod ## FieldName = (Signature) GetProcAddress(_sLibrary, #FieldName); \
	if (_sMethod ## FieldName == nullptr) \
	{ \
		fprintf(stderr, "RzChromaStreamPlugin: Method not available! %s\r\n", #FieldName); \
		FreeLibrary(_sLibrary); \
		_sLibrary = NULL; \
		return (LONG)RZRESULT_FAILED; \
	} \
}

// EXTRA METHODS

RZRESULT RzChromaStreamPlugin::GetLibraryLoadedState()
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
		path += CHROMA_STREAMING_DLL;

		// check the library file version
		if (!VerifyLibrarySignature::IsFileVersionSameOrNewer(path, 1, 0, 0, 6))
		{
			ChromaLogger::fprintf(stderr, "Detected old version of Chroma Stream Library!\r\n");
			return RZRESULT_DLL_NOT_FOUND;
		}

		// verify the library has a valid signature
		_sInvalidSignature = !VerifyLibrarySignature::VerifyModule(path);
		if (_sInvalidSignature)
		{
			ChromaLogger::fprintf(stderr, "Chroma Stream Library has an invalid signature!\r\n");
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
			strPathSearch += CHROMA_STREAMING_DLL;

			// check if DLL exists in search path
			std::filesystem::path p = strPathSearch.c_str();
			std::error_code pathError;
			if (!std::filesystem::exists(p, pathError))
			{
				// not found
				continue;
			}

			// check the library file version
			if (!VerifyLibrarySignature::IsFileVersionSameOrNewer(strPathSearch, 0, 1, 2, 22))
			{
				ChromaLogger::fprintf(stderr, "Detected old version of Chroma Stream Library!\r\n");
				return RZRESULT_DLL_NOT_FOUND;
			}

			// verify the library has a valid signature
			_sInvalidSignature = !VerifyLibrarySignature::VerifyModule(strPathSearch);
			if (_sInvalidSignature)
			{
				ChromaLogger::fprintf(stderr, "Chroma Stream Library has an invalid signature!\r\n");
				return RZRESULT_DLL_INVALID_SIGNATURE;
			}

			break;
		}

		std::wstring path = CHROMA_STREAMING_DLL;		
#endif

		// load the library
		HMODULE library = LoadLibrary(path.c_str());
		if (library == NULL)
		{
			ChromaLogger::fprintf(stderr, "Failed to load Chroma Stream Library!\r\n");
			return RZRESULT_DLL_NOT_FOUND;
		}

		_sLibrary = library;
	}

#pragma region Streaming
	STREAM_SDK_VALIDATE_METHOD(CHROMA_SDK_STREAM_BROADCAST, StreamBroadcast);
	STREAM_SDK_VALIDATE_METHOD(CHROMA_SDK_STREAM_BROADCAST_END, StreamBroadcastEnd);
	STREAM_SDK_VALIDATE_METHOD(CHROMA_SDK_STREAM_GET_AUTH_SHORTCODE, StreamGetAuthShortcode);
	STREAM_SDK_VALIDATE_METHOD(CHROMA_SDK_STREAM_GET_FOCUS, StreamGetFocus);
	STREAM_SDK_VALIDATE_METHOD(CHROMA_SDK_STREAM_GET_ID, StreamGetId);
	STREAM_SDK_VALIDATE_METHOD(CHROMA_SDK_STREAM_GET_KEY, StreamGetKey);
	STREAM_SDK_VALIDATE_METHOD(CHROMA_SDK_STREAM_GET_STATUS, StreamGetStatus);
	STREAM_SDK_VALIDATE_METHOD(CHROMA_SDK_STREAM_GET_STATUS_STRING, StreamGetStatusString);
	STREAM_SDK_VALIDATE_METHOD(CHROMA_SDK_STREAM_RELEASE_SHORTCODE, StreamReleaseShortcode);
	STREAM_SDK_VALIDATE_METHOD(CHROMA_SDK_STREAM_SET_FOCUS, StreamSetFocus);
	STREAM_SDK_VALIDATE_METHOD(CHROMA_SDK_STREAM_WATCH, StreamWatch);
	STREAM_SDK_VALIDATE_METHOD(CHROMA_SDK_STREAM_WATCH_END, StreamWatchEnd);
#pragma endregion

	_sLoaded = true;
	return RZRESULT_SUCCESS;
}

void RzChromaStreamPlugin::Unload()
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

#pragma region Streaming

bool RzChromaStreamPlugin::StreamBroadcast(const char* streamId, const char* streamKey)
{
	RZRESULT state = GetLibraryLoadedState();
	if (state != RZRESULT_SUCCESS)
	{
		return false;
	}
	return _sMethodStreamBroadcast(streamId, streamKey);
}
bool RzChromaStreamPlugin::StreamBroadcastEnd()
{
	RZRESULT state = GetLibraryLoadedState();
	if (state != RZRESULT_SUCCESS)
	{
		return false;
	}
	return _sMethodStreamBroadcastEnd();
}
void RzChromaStreamPlugin::StreamGetAuthShortcode(char* shortcode, unsigned char* length,
	const wchar_t* platform, const wchar_t* title)
{
	RZRESULT state = GetLibraryLoadedState();
	if (state != RZRESULT_SUCCESS)
	{
		return;
	}
	_sMethodStreamGetAuthShortcode(shortcode, length, platform, title);
}
bool RzChromaStreamPlugin::StreamGetFocus(char* focus, unsigned char* length)
{
	RZRESULT state = GetLibraryLoadedState();
	if (state != RZRESULT_SUCCESS)
	{
		return false;
	}
	return _sMethodStreamGetFocus(focus, length);
}
bool RzChromaStreamPlugin::StreamSetFocus(const char* focus)
{
	RZRESULT state = GetLibraryLoadedState();
	if (state != RZRESULT_SUCCESS)
	{
		return false;
	}
	return _sMethodStreamSetFocus(focus);
}
void RzChromaStreamPlugin::StreamGetId(const char* shortcode, char* streamId, unsigned char* length)
{
	RZRESULT state = GetLibraryLoadedState();
	if (state != RZRESULT_SUCCESS)
	{
		return;
	}
	_sMethodStreamGetId(shortcode, streamId, length);
}
void RzChromaStreamPlugin::StreamGetKey(const char* shortcode, char* streamKey, unsigned char* length)
{
	RZRESULT state = GetLibraryLoadedState();
	if (state != RZRESULT_SUCCESS)
	{
		return;
	}
	_sMethodStreamGetKey(shortcode, streamKey, length);
}
ChromaSDK::Stream::StreamStatusType RzChromaStreamPlugin::StreamGetStatus()
{
	RZRESULT state = GetLibraryLoadedState();
	if (state != RZRESULT_SUCCESS)
	{
		return ChromaSDK::Stream::StreamStatusType::SERVICE_OFFLINE;
	}
	return _sMethodStreamGetStatus();
}
const char* RzChromaStreamPlugin::StreamGetStatusString(ChromaSDK::Stream::StreamStatusType status)
{
	RZRESULT state = GetLibraryLoadedState();
	if (state != RZRESULT_SUCCESS)
	{
		return NULL;
	}
	return _sMethodStreamGetStatusString(status);
}
bool RzChromaStreamPlugin::StreamReleaseShortcode(const char* shortcode)
{
	RZRESULT state = GetLibraryLoadedState();
	if (state != RZRESULT_SUCCESS)
	{
		return false;
	}
	return _sMethodStreamReleaseShortcode(shortcode);
}
bool RzChromaStreamPlugin::StreamWatch(const char* streamId, unsigned long long timestamp)
{
	RZRESULT state = GetLibraryLoadedState();
	if (state != RZRESULT_SUCCESS)
	{
		return false;
	}
	return _sMethodStreamWatch(streamId, timestamp);
}
bool RzChromaStreamPlugin::StreamWatchEnd()
{
	RZRESULT state = GetLibraryLoadedState();
	if (state != RZRESULT_SUCCESS)
	{
		return false;
	}
	return _sMethodStreamWatchEnd();
}

#pragma endregion
