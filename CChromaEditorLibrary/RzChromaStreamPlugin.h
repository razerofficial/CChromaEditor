#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
#include "RzChromaSDKTypes.h"

#pragma region Streaming
typedef bool(*CHROMA_SDK_STREAM_BROADCAST)(const char* streamId, const char* streamKey);
typedef bool(*CHROMA_SDK_STREAM_BROADCAST_END)();
typedef void(*CHROMA_SDK_STREAM_GET_AUTH_SHORTCODE)(char* shortcode, unsigned char* length,
	const wchar_t* platform, const wchar_t* title);
typedef bool(*CHROMA_SDK_STREAM_GET_FOCUS)(char* focus, unsigned char* length);
typedef void(*CHROMA_SDK_STREAM_GET_ID)(const char* shortcode, char* streamId, unsigned char* length);
typedef void(*CHROMA_SDK_STREAM_GET_KEY)(const char* shortcode, char* streamKey, unsigned char* length);
typedef ChromaSDK::Stream::StreamStatusType(*CHROMA_SDK_STREAM_GET_STATUS)();
typedef bool(*CHROMA_SDK_STREAM_SET_FOCUS)(const char* focus);
typedef const char*(*CHROMA_SDK_STREAM_GET_STATUS_STRING)(ChromaSDK::Stream::StreamStatusType status);
typedef bool(*CHROMA_SDK_STREAM_RELEASE_SHORTCODE)(const char* shortcode);
typedef bool(*CHROMA_SDK_STREAM_WATCH)(const char* streamId, unsigned long long timestamp);
typedef bool(*CHROMA_SDK_STREAM_WATCH_END)();
#pragma endregion

#undef STREAM_SDK_DECLARE_METHOD
#define STREAM_SDK_DECLARE_METHOD(Signature, FieldName) static Signature _sMethod ## FieldName


class RzChromaStreamPlugin
{
public:
	static RZRESULT GetLibraryLoadedState();
	static void Unload();

#pragma region Streaming
	static bool StreamBroadcast(const char* streamId, const char* streamKey);
	static bool StreamBroadcastEnd();
	static void StreamGetAuthShortcode(char* shortcode, unsigned char* length,
		const wchar_t* platform, const wchar_t* title);
	static bool StreamGetFocus(char* focus, unsigned char* length);
	static void StreamGetId(const char* shortcode, char* streamId, unsigned char* length);
	static void StreamGetKey(const char* shortcode, char* streamKey, unsigned char* length);
	static ChromaSDK::Stream::StreamStatusType StreamGetStatus();
	static const char* StreamGetStatusString(ChromaSDK::Stream::StreamStatusType status);
	static bool StreamReleaseShortcode(const char* shortcode);
	static bool StreamSetFocus(const char* focus);
	static bool StreamWatch(const char* streamId, unsigned long long timestamp);
	static bool StreamWatchEnd();
#pragma endregion

private:

	static HMODULE _sLibrary;
	static bool _sInvalidSignature;
	static bool _sLoaded;

#pragma region Streaming
	STREAM_SDK_DECLARE_METHOD(CHROMA_SDK_STREAM_BROADCAST, StreamBroadcast);
	STREAM_SDK_DECLARE_METHOD(CHROMA_SDK_STREAM_BROADCAST_END, StreamBroadcastEnd);
	STREAM_SDK_DECLARE_METHOD(CHROMA_SDK_STREAM_GET_AUTH_SHORTCODE, StreamGetAuthShortcode);
	STREAM_SDK_DECLARE_METHOD(CHROMA_SDK_STREAM_GET_FOCUS, StreamGetFocus);
	STREAM_SDK_DECLARE_METHOD(CHROMA_SDK_STREAM_GET_ID, StreamGetId);
	STREAM_SDK_DECLARE_METHOD(CHROMA_SDK_STREAM_GET_KEY, StreamGetKey);
	STREAM_SDK_DECLARE_METHOD(CHROMA_SDK_STREAM_GET_STATUS, StreamGetStatus);
	STREAM_SDK_DECLARE_METHOD(CHROMA_SDK_STREAM_GET_STATUS_STRING, StreamGetStatusString);
	STREAM_SDK_DECLARE_METHOD(CHROMA_SDK_STREAM_RELEASE_SHORTCODE, StreamReleaseShortcode);
	STREAM_SDK_DECLARE_METHOD(CHROMA_SDK_STREAM_SET_FOCUS, StreamSetFocus);
	STREAM_SDK_DECLARE_METHOD(CHROMA_SDK_STREAM_WATCH, StreamWatch);
	STREAM_SDK_DECLARE_METHOD(CHROMA_SDK_STREAM_WATCH_END, StreamWatchEnd);
#pragma endregion
};
