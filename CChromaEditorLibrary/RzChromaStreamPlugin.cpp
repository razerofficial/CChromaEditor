#include "stdafx.h"
#include "RzChromaStreamPlugin.h"
#include "RzErrors.h"
#include "VerifyLibrarySignature.h"
#include <tchar.h>
#include <stdio.h>


#ifdef _WIN64
#define CHROMA_STREAMING_DLL        _T("C:\\Program Files\\Razer Chroma SDK\\bin\\RzChromaStreamPlugin64.dll")
#else
#define CHROMA_STREAMING_DLL        _T("C:\\Program Files (x86)\\Razer Chroma SDK\\bin\\RzChromaStreamPlugin.dll")
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
		// check the library file version
		if (!VerifyLibrarySignature::IsFileVersionSameOrNewer(CHROMA_STREAMING_DLL, 0, 1, 2, 21))
		{
			return RZRESULT_DLL_NOT_FOUND;
		}

		// load the library
		_sLibrary = LoadLibrary(CHROMA_STREAMING_DLL);
		if (_sLibrary == NULL)
		{
			return RZRESULT_DLL_NOT_FOUND;
		}

		// verify the library has a valid signature
		//_sInvalidSignature = !ChromaSDK::VerifyLibrarySignature::VerifyModule(_sLibrary);
 		if (_sInvalidSignature)
		{
			fprintf(stderr, "Failed to load Chroma library with invalid signature!\r\n");
			
			// unload the library
			FreeLibrary(_sLibrary);
			_sLibrary = NULL;

			return RZRESULT_DLL_INVALID_SIGNATURE;
		}
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
	const char* platform, const char* title)
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
