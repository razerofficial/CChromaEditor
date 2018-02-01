// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE classes
#include <afxodlgs.h>       // MFC OLE dialog classes
#include <afxdisp.h>        // MFC Automation classes
#endif // _AFX_NO_OLE_SUPPORT

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>                      // MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>                     // MFC DAO database classes
#endif // _AFX_NO_DAO_SUPPORT

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC support for Internet Explorer 4 Common Controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#if _MSC_VER // this is defined when compiling with Visual Studio
#define EXPORT_API __declspec(dllexport) // Visual Studio needs annotating exported functions with this
#else
#define EXPORT_API // XCode does not need annotating exported functions, so define is empty
#endif

/* Setup log mechanism */
typedef void(*DebugLogPtr)(const char *);
void LogDebug(const char* text, ...);
void LogError(const char* text, ...);
/* End of setup log mechanism */

#include "AnimationBase.h"

extern "C"
{
	//GameMaker: Only has double and char* types

	EXPORT_API void PluginSetLogDelegate(DebugLogPtr fp);

	EXPORT_API int PluginInit();
	EXPORT_API double PluginInitD();

	EXPORT_API bool PluginIsPlatformSupported();
	EXPORT_API double PluginIsPlatformSupportedD();

	EXPORT_API bool PluginIsInitialized();
	EXPORT_API double PluginIsInitializedD();

	EXPORT_API bool PluginIsDialogOpen();
	EXPORT_API double PluginIsDialogOpenD();

	EXPORT_API int PluginOpenEditorDialog(const char* path);
	EXPORT_API double PluginOpenEditorDialogD(const char* path);

	EXPORT_API int PluginOpenEditorDialogAndPlay(const char* path);
	EXPORT_API double PluginOpenEditorDialogAndPlayD(const char* path);

	EXPORT_API const char* PluginGetAnimationName(int animationId);

	EXPORT_API void PluginStopAnimationType(int deviceType, int device);
	EXPORT_API double PluginStopAnimationTypeD(double deviceType, double device);
	
	EXPORT_API void PluginStopAll();

	EXPORT_API void PluginClearAnimationType(int deviceType, int device);
	EXPORT_API void PluginClearAll();

	EXPORT_API int PluginGetAnimationCount();
	EXPORT_API int PluginGetAnimationId(int index);
	EXPORT_API int PluginGetPlayingAnimationCount();
	EXPORT_API int PluginGetPlayingAnimationId(int index);

	EXPORT_API int PluginOpenAnimation(const char* path);
	EXPORT_API double PluginOpenAnimationD(const char* path);

	EXPORT_API int PluginLoadAnimation(int animationId);
	EXPORT_API double PluginLoadAnimationD(double animationId);

	EXPORT_API int PluginUnloadAnimation(int animationId);
	EXPORT_API double PluginUnloadAnimationD(double animationId);

	EXPORT_API int PluginPlayAnimation(int animationId);
	EXPORT_API double PluginPlayAnimationD(double animationId);

	EXPORT_API bool PluginIsPlaying(int animationId);
	EXPORT_API double PluginIsPlayingD(double animationId);

	EXPORT_API int PluginStopAnimation(int animationId);
	EXPORT_API double PluginStopAnimationD(double animationId);

	EXPORT_API int PluginCloseAnimation(int animationId);
	EXPORT_API double PluginCloseAnimationD(double animationId);

	EXPORT_API int PluginUninit();
	EXPORT_API double PluginUninitD();

	EXPORT_API int PluginCreateAnimationInMemory(int deviceType, int device);
	EXPORT_API int PluginCreateAnimation(const char* path, int deviceType, int device);
	EXPORT_API int PluginSaveAnimation(int animationId, const char* path);
	EXPORT_API int PluginResetAnimation(int animationId);
	
	EXPORT_API int PluginGetDeviceType(int animationId);
	EXPORT_API int PluginGetDeviceTypeName(const char* path);
	EXPORT_API double PluginGetDeviceTypeNameD(const char* path);
	
	EXPORT_API int PluginGetDevice(int animationId);
	EXPORT_API int PluginGetDeviceName(const char* path);
	EXPORT_API double PluginGetDeviceNameD(const char* path);

	EXPORT_API int PluginSetDevice(int animationId, int deviceType, int device);

	EXPORT_API int PluginGetMaxLeds(int device);
	EXPORT_API double PluginGetMaxLedsD(double device);

	EXPORT_API int PluginGetMaxRow(int device);
	EXPORT_API double PluginGetMaxRowD(double device);

	EXPORT_API int PluginGetMaxColumn(int device);
	EXPORT_API double PluginGetMaxColumnD(double device);

	EXPORT_API int PluginAddFrame(int animationId, float duration, int* colors, int length);
	EXPORT_API int PluginUpdateFrame(int animationId, int frameIndex, float duration, int* colors, int length);
	EXPORT_API int PluginGetFrame(int animationId, int frameIndex, float* duration, int* colors, int length);
	
	EXPORT_API int PluginPreviewFrame(int animationId, int frameIndex);
	EXPORT_API double PluginPreviewFrameD(double animationId, double frameIndex);
	
	EXPORT_API int PluginOverrideFrameDuration(int animationId, float duration);
	EXPORT_API double PluginOverrideFrameDurationD(double animationId, double duration);

	EXPORT_API int PluginReverse(int animationId);
	EXPORT_API int PluginMirrorHorizontally(int animationId);
	EXPORT_API int PluginMirrorVertically(int animationId);

	int PluginGetAnimationIdFromInstance(ChromaSDK::AnimationBase* animation);
	ChromaSDK::AnimationBase* GetAnimationInstance(int animationId);
	
	EXPORT_API int PluginGetAnimation(const char* name);
	EXPORT_API double PluginGetAnimationD(const char* name);

	EXPORT_API void PluginCloseAnimationName(const char* path);
	EXPORT_API double PluginCloseAnimationNameD(const char* path);

	EXPORT_API void PluginPlayAnimationLoop(int animationId, bool loop);
	EXPORT_API void PluginPlayAnimationName(const char* path, bool loop);
	EXPORT_API double PluginPlayAnimationNameD(const char* path, double loop);

	EXPORT_API void PluginPlayAnimationFrame(int animationId, int frameId, bool loop);
	EXPORT_API void PluginPlayAnimationFrameName(const char* path, int frameId, bool loop);
	EXPORT_API double PluginPlayAnimationFrameNameD(const char* path, double frameId, double loop);

	EXPORT_API void PluginStopAnimationName(const char* path);
	EXPORT_API double PluginStopAnimationNameD(const char* path);

	EXPORT_API bool PluginIsPlayingName(const char* path);
	EXPORT_API double PluginIsPlayingNameD(const char* path);

	EXPORT_API bool PluginIsPlayingType(int deviceType, int device);
	EXPORT_API double PluginIsPlayingTypeD(double deviceType, double device);
	
	EXPORT_API void PluginPlayComposite(const char* name, bool loop);
	EXPORT_API double PluginPlayCompositeD(const char* name, double loop);
	
	EXPORT_API void PluginStopComposite(const char* name);
	EXPORT_API double PluginStopCompositeD(const char* name);

	EXPORT_API void PluginCloseComposite(const char* name);
	EXPORT_API double PluginCloseCompositeD(const char* name);

	EXPORT_API int PluginGetKeyColor(int animationId, int frameId, int rzkey);
	EXPORT_API int PluginGetKeyColorName(const char* path, int frameId, int rzkey);
	EXPORT_API double PluginGetKeyColorD(const char* path, double frameId, double rzkey);

	EXPORT_API int PluginGet1DColor(int animationId, int frameId, int led);
	EXPORT_API int PluginGet1DColorName(const char* path, int frameId, int led);
	EXPORT_API double PluginGet1DColorNameD(const char* path, double frameId, double led);

	EXPORT_API int PluginGet2DColor(int animationId, int frameId, int row, int column);
	EXPORT_API int PluginGet2DColorName(const char* path, int frameId, int row, int column);
	EXPORT_API double PluginGet2DColorNameD(const char* path, double frameId, double row, double column);
	
	EXPORT_API void PluginSetKeyColor(int animationId, int frameId, int rzkey, int color);
	EXPORT_API void PluginSetKeyColorName(const char* path, int frameId, int rzkey, int color);
	EXPORT_API double PluginSetKeyColorNameD(const char* path, double frameId, double rzkey, double color);

	EXPORT_API void PluginSetKeysColor(int animationId, int frameId, const int* rzkeys, int keyCount, int color);
	EXPORT_API void PluginSetKeysColorName(const char* path, int frameId, const int* rzkeys, int keyCount, int color);

	EXPORT_API void PluginSet1DColor(int animationId, int frameId, int led, int color);
	EXPORT_API void PluginSet1DColorName(const char* path, int frameId, int led, int color);
	EXPORT_API double PluginSet1DColorNameD(const char* path, double frameId, double led, double color);

	EXPORT_API void PluginSet2DColor(int animationId, int frameId, int row, int column, int color);
	EXPORT_API void PluginSet2DColorName(const char* path, int frameId, int row, int column, int color);
	EXPORT_API double PluginSet2DColorNameD(const char* path, double frameId, double rowColumnIndex, double color);

	EXPORT_API void PluginCopyKeyColor(int sourceAnimationId, int targetAnimationId, int frameId, int rzkey);
	EXPORT_API void PluginCopyKeyColorName(const char* sourceAnimation, const char* targetAnimation, int frameId, int rzkey);
	EXPORT_API double PluginCopyKeyColorNameD(const char* sourceAnimation, const char* targetAnimation, double frameId, double rzkey);

	EXPORT_API void PluginCopyNonZeroKeyColor(int sourceAnimationId, int targetAnimationId, int frameId, int rzkey);
	EXPORT_API void PluginCopyNonZeroKeyColorName(const char* sourceAnimation, const char* targetAnimation, int frameId, int rzkey);
	EXPORT_API double PluginCopyNonZeroKeyColorNameD(const char* sourceAnimation, const char* targetAnimation, double frameId, double rzkey);

	EXPORT_API int PluginGetFrameCount(int animationId);
	EXPORT_API int PluginGetFrameCountName(const char* path);
	EXPORT_API double PluginGetFrameCountNameD(const char* path);

	EXPORT_API int PluginGetCurrentFrame(int animationId);
	EXPORT_API int PluginGetCurrentFrameName(const char* path);
	EXPORT_API double PluginGetCurrentFrameNameD(const char* path);

	EXPORT_API void PluginSetCurrentFrame(int animationId, int frameId);
	EXPORT_API void PluginSetCurrentFrameName(const char* path, int frameId);
	EXPORT_API double PluginSetCurrentFrameNameD(const char* path, double frameId);

	EXPORT_API void PluginPauseAnimation(int animationId);
	EXPORT_API void PluginPauseAnimationName(const char* path);
	EXPORT_API double PluginPauseAnimationNameD(const char* path);

	EXPORT_API bool PluginIsAnimationPaused(int animationId);
	EXPORT_API bool PluginIsAnimationPausedName(const char* path);
	EXPORT_API double PluginIsAnimationPausedNameD(const char* path);

	EXPORT_API bool PluginHasAnimationLoop(int animationId);
	EXPORT_API bool PluginHasAnimationLoopName(const char* path);
	EXPORT_API double PluginHasAnimationLoopNameD(const char* path);

	EXPORT_API void PluginResumeAnimation(int animationId, bool loop);
	EXPORT_API void PluginResumeAnimationName(const char* path, bool loop);
	EXPORT_API double PluginResumeAnimationNameD(const char* path, double loop);
}
