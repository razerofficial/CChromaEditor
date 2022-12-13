// stdafx.cpp : source file that includes just the standard includes
// CChromaEditorLibrary.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
#include "CChromaEditorLibrary.h"
#include "ChromaThread.h"
#include "RzChromaSDK.h"
#include "ChromaLogger.h"
#include "RzChromaStreamPlugin.h"
#include <map>
#include <iostream>
#include <sstream>
#include <thread>

using namespace ChromaSDK;
using namespace std;

/* Setup log mechanism */
static DebugLogPtr _gDebugLogPtr;
void LogDebug(const char* format, ...)
{
	if (NULL == _gDebugLogPtr)
	{
		va_list args;
		va_start(args, format);
		vfprintf_s(stdout, format, args);
		va_end(args);
	}
	else if (NULL == format)
	{
		_gDebugLogPtr("");
	}
	else
	{
		char buffer[1024] = { 0 };
		va_list args;
		va_start(args, format);
		vsprintf_s(buffer, format, args);
		va_end(args);
		_gDebugLogPtr(&buffer[0]);
	}
}
void LogError(const char* format, ...)
{
	if (NULL == _gDebugLogPtr)
	{
		va_list args;
		va_start(args, format);
		vfprintf_s(stderr, format, args);
		va_end(args);
	}
	else if (NULL == format)
	{
		_gDebugLogPtr("");
	}
	else
	{
		char buffer[1024] = { 0 };
		va_list args;
		va_start(args, format);
		vsprintf_s(buffer, format, args);
		va_end(args);
		_gDebugLogPtr(&buffer[0]);
	}
}
/* End of setup log mechanism */

bool _gDialogIsOpen = false;
string _gPath = "";
int _gAnimationId = 0;
map<string, int> _gAnimationMapID;
map<int, AnimationBase*> _gAnimations;
map<EChromaSDKDevice1DEnum, int> _gPlayMap1D;
map<EChromaSDKDevice2DEnum, int> _gPlayMap2D;

void SetupChromaThread()
{
	if (ChromaThread::Instance() == nullptr)
	{
		ChromaThread::Init();
	}
	if (ChromaThread::Instance() != nullptr)
	{
		ChromaThread::Instance()->Start();
	}
}

void StopChromaThread()
{
	if (ChromaThread::Instance() != nullptr)
	{
		ChromaThread::Instance()->Stop();
	}
}

void ThreadOpenEditorDialog(bool playOnOpen)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	// normal function body here

	//LogError("CChromaEditorLibrary::ThreadOpenEditorDialog %s\r\n", _gPath.c_str());

	// dialog instance
	CMainViewDlg mainViewDlg;

	mainViewDlg.OpenOrCreateAnimation(_gPath);

	if (playOnOpen)
	{
		mainViewDlg.PlayAnimationOnOpen();
	}

	// keep dialog focused
	mainViewDlg.DoModal();

	// dialog is closed
	_gDialogIsOpen = false;
}

extern "C"
{

	EXPORT_API void PluginUnloadLibrarySDK()
	{
		RzChromaSDK::Unload();
	}

	EXPORT_API void PluginUnloadLibraryStreamingPlugin()
	{
		RzChromaStreamPlugin::Unload();
	}

#pragma region Core API
	EXPORT_API RZRESULT PluginCoreInit()
	{
		return RzChromaSDK::Init();
	}
	EXPORT_API RZRESULT PluginCoreInitSDK(ChromaSDK::APPINFOTYPE* appInfo)
	{
#ifdef _DEBUG
		if (appInfo != nullptr)
		{
			wcout << "PluginCoreInitSDK: Title=" << appInfo->Title << endl;
			wcout << "PluginCoreInitSDK: Description=" << appInfo->Description << endl;
			wcout << "PluginCoreInitSDK: Author.Name=" << appInfo->Author.Name << endl;
			wcout << "PluginCoreInitSDK: Author.Contact=" << appInfo->Author.Contact << endl;
			wcout << "PluginCoreInitSDK: SupportedDevice=" << appInfo->SupportedDevice << endl;
			wcout << "PluginCoreInitSDK: Category=" << appInfo->Category << endl;
		}
#endif
		return RzChromaSDK::InitSDK(appInfo);
	}
	EXPORT_API RZRESULT PluginCoreUnInit()
	{
		return RzChromaSDK::UnInit();
	}
	EXPORT_API RZRESULT PluginCoreCreateEffect(RZDEVICEID DeviceId, ChromaSDK::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId)
	{
		return RzChromaSDK::CreateEffect(DeviceId, Effect, pParam, pEffectId);
	}
	EXPORT_API RZRESULT PluginCoreCreateChromaLinkEffect(ChromaSDK::ChromaLink::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId)
	{
		return RzChromaSDK::CreateChromaLinkEffect(Effect, pParam, pEffectId);
	}
	EXPORT_API RZRESULT PluginCoreCreateKeyboardEffect(ChromaSDK::Keyboard::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId)
	{
		return RzChromaSDK::CreateKeyboardEffect(Effect, pParam, pEffectId);
	}
	EXPORT_API RZRESULT PluginCoreCreateKeypadEffect(ChromaSDK::Keypad::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId)
	{
		return RzChromaSDK::CreateKeypadEffect(Effect, pParam, pEffectId);
	}
	EXPORT_API RZRESULT PluginCoreCreateHeadsetEffect(ChromaSDK::Headset::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId)
	{
		return RzChromaSDK::CreateHeadsetEffect(Effect, pParam, pEffectId);
	}
	EXPORT_API RZRESULT PluginCoreCreateMouseEffect(ChromaSDK::Mouse::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId)
	{
		return RzChromaSDK::CreateMouseEffect(Effect, pParam, pEffectId);
	}
	EXPORT_API RZRESULT PluginCoreCreateMousepadEffect(ChromaSDK::Mousepad::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId)
	{
		return RzChromaSDK::CreateMousepadEffect(Effect, pParam, pEffectId);
	}
	EXPORT_API RZRESULT PluginCoreSetEffect(RZEFFECTID EffectId)
	{
		return RzChromaSDK::SetEffect(EffectId);
	}
	EXPORT_API RZRESULT PluginCoreDeleteEffect(RZEFFECTID EffectId)
	{
		return RzChromaSDK::DeleteEffect(EffectId);
	}
	EXPORT_API RZRESULT PluginCoreQueryDevice(RZDEVICEID DeviceId, ChromaSDK::DEVICE_INFO_TYPE &DeviceInfo)
	{
		return RzChromaSDK::QueryDevice(DeviceId, DeviceInfo);
	}

	EXPORT_API bool PluginCoreStreamSetFocus(const char* focus)
	{
		return RzChromaStreamPlugin::StreamSetFocus(focus);
	}
	EXPORT_API bool PluginCoreStreamGetFocus(char* focus, unsigned char* length)
	{
		return RzChromaStreamPlugin::StreamGetFocus(focus, length);
	}


	EXPORT_API bool PluginCoreStreamSupportsStreaming()
	{
		return RzChromaStreamPlugin::GetLibraryLoadedState() == RZRESULT_SUCCESS;
	}
	EXPORT_API bool PluginCoreStreamBroadcast(const char* streamId, const char* streamKey)
	{
		return RzChromaStreamPlugin::StreamBroadcast(streamId, streamKey);
	}

	EXPORT_API bool PluginCoreStreamBroadcastEnd()
	{
		return RzChromaStreamPlugin::StreamBroadcastEnd();
	}

	EXPORT_API void PluginCoreStreamGetAuthShortcode(char* shortcode, unsigned char* length,
		const wchar_t* platform, const wchar_t* title)
	{
		RzChromaStreamPlugin::StreamGetAuthShortcode(shortcode, length, platform, title);
	}

	EXPORT_API void PluginCoreStreamGetId(const char* shortcode, char* streamId, unsigned char* length)
	{
		RzChromaStreamPlugin::StreamGetId(shortcode, streamId, length);
	}

	EXPORT_API void PluginCoreStreamGetKey(const char* shortcode, char* streamKey, unsigned char* length)
	{
		RzChromaStreamPlugin::StreamGetKey(shortcode, streamKey, length);
	}

	EXPORT_API Stream::StreamStatusType PluginCoreStreamGetStatus()
	{
		return RzChromaStreamPlugin::StreamGetStatus();
	}

	EXPORT_API const char* PluginCoreStreamGetStatusString(ChromaSDK::Stream::StreamStatusType status)
	{
		return RzChromaStreamPlugin::StreamGetStatusString(status);
	}

	EXPORT_API bool PluginCoreStreamReleaseShortcode(const char* shortcode)
	{
		return RzChromaStreamPlugin::StreamReleaseShortcode(shortcode);
	}

	EXPORT_API bool PluginCoreStreamWatch(const char* streamId, unsigned long long timestamp)
	{
		return RzChromaStreamPlugin::StreamWatch(streamId, timestamp);
	}

	EXPORT_API bool PluginCoreStreamWatchEnd()
	{
		return RzChromaStreamPlugin::StreamWatchEnd();
	}
#pragma endregion

	EXPORT_API void PluginSetLogDelegate(DebugLogPtr fp)
	{
		_gDebugLogPtr = fp;
		//LogDebug("PluginSetLogDelegate:");
	}

	EXPORT_API bool PluginIsPlatformSupported()
	{
		return true;
	}

	EXPORT_API double PluginIsPlatformSupportedD()
	{
		if (PluginIsPlatformSupported())
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}

	EXPORT_API bool PluginIsInitialized()
	{
		return ChromaSDKPlugin::GetInstance()->IsInitialized();
	}

	EXPORT_API double PluginIsInitializedD()
	{
		if (PluginIsInitialized())
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}

	EXPORT_API RZRESULT PluginGetLibraryLoadedState()
	{
		return RzChromaSDK::GetLibraryLoadedState();
	}

	EXPORT_API double PluginGetLibraryLoadedStateD()
	{
		return (double)PluginGetLibraryLoadedState();
	}

	EXPORT_API int PluginGetRGB(int red, int green, int blue)
	{
		return (red & 0xFF) | ((green & 0xFF) << 8) | ((blue & 0xFF) << 16);
	}

	EXPORT_API double PluginGetRGBD(double red, double green, double blue)
	{
		return (double)PluginGetRGB((int)red, (int)green, (int)blue);
	}

	EXPORT_API bool PluginIsDialogOpen()
	{
		return _gDialogIsOpen;
	}

	EXPORT_API double PluginIsDialogOpenD()
	{
		if (PluginIsDialogOpen())
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}

	EXPORT_API int PluginOpenEditorDialog(const char* path)
	{
		PluginIsInitialized();

		//LogDebug("PluginOpenEditorDialog %s\r\n", path);

		if (_gDialogIsOpen)
		{
			LogError("PluginOpenEditorDialog: Dialog is already open!\r\n");
			return -1;
		}

		_gDialogIsOpen = true;
		_gPath = path;
		thread newThread(ThreadOpenEditorDialog, false);
		newThread.detach();

		return 0;
	}

	EXPORT_API double PluginOpenEditorDialogD(const char* path)
	{
		return PluginOpenEditorDialog(path);
	}

	EXPORT_API int PluginOpenEditorDialogAndPlay(const char* path)
	{
		PluginIsInitialized();

		//LogDebug("PluginOpenEditorDialogAndPlay %s\r\n", path);

		if (_gDialogIsOpen)
		{
			LogError("PluginOpenEditorDialogAndPlay: Dialog is already open!\r\n");
			return -1;
		}

		_gDialogIsOpen = true;
		_gPath = path;
		thread newThread(ThreadOpenEditorDialog, true);
		newThread.detach();

		return 0;
	}

	EXPORT_API double PluginOpenEditorDialogAndPlayD(const char* path)
	{
		return PluginOpenEditorDialogAndPlay(path);
	}

	EXPORT_API const char* PluginGetAnimationName(int animationId)
	{
		if (animationId < 0)
		{
			return "";
		}
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (animation == nullptr)
		{
			return "";
		}
		return animation->GetName().c_str();
	}

	EXPORT_API void PluginStopAll()
	{
		PluginStopAnimationType((int)EChromaSDKDeviceTypeEnum::DE_1D, (int)EChromaSDKDevice1DEnum::DE_ChromaLink);
		PluginStopAnimationType((int)EChromaSDKDeviceTypeEnum::DE_1D, (int)EChromaSDKDevice1DEnum::DE_Headset);
		PluginStopAnimationType((int)EChromaSDKDeviceTypeEnum::DE_2D, (int)EChromaSDKDevice2DEnum::DE_Keyboard);
		PluginStopAnimationType((int)EChromaSDKDeviceTypeEnum::DE_2D, (int)EChromaSDKDevice2DEnum::DE_Keypad);
		PluginStopAnimationType((int)EChromaSDKDeviceTypeEnum::DE_2D, (int)EChromaSDKDevice2DEnum::DE_Mouse);
		PluginStopAnimationType((int)EChromaSDKDeviceTypeEnum::DE_1D, (int)EChromaSDKDevice1DEnum::DE_Mousepad);
	}

	EXPORT_API void PluginClearAnimationType(int deviceType, int device)
	{
		PluginStopAnimationType(deviceType, device);

		FChromaSDKEffectResult result;
		switch ((EChromaSDKDeviceTypeEnum)deviceType)
		{
		case EChromaSDKDeviceTypeEnum::DE_1D:
			result = ChromaSDKPlugin::GetInstance()->CreateEffectNone1D((EChromaSDKDevice1DEnum)device);
			if (result.Result == 0)
			{
				ChromaSDKPlugin::GetInstance()->SetEffect(result.EffectId);
				ChromaSDKPlugin::GetInstance()->DeleteEffect(result.EffectId);
			}
			break;
		case EChromaSDKDeviceTypeEnum::DE_2D:
			result = ChromaSDKPlugin::GetInstance()->CreateEffectNone2D((EChromaSDKDevice2DEnum)device);
			if (result.Result == 0)
			{
				ChromaSDKPlugin::GetInstance()->SetEffect(result.EffectId);
				ChromaSDKPlugin::GetInstance()->DeleteEffect(result.EffectId);
			}
			break;
		}
	}

	EXPORT_API void PluginClearAll()
	{
		PluginClearAnimationType((int)EChromaSDKDeviceTypeEnum::DE_1D, (int)EChromaSDKDevice1DEnum::DE_ChromaLink);
		PluginClearAnimationType((int)EChromaSDKDeviceTypeEnum::DE_1D, (int)EChromaSDKDevice1DEnum::DE_Headset);
		PluginClearAnimationType((int)EChromaSDKDeviceTypeEnum::DE_2D, (int)EChromaSDKDevice2DEnum::DE_Keyboard);
		PluginClearAnimationType((int)EChromaSDKDeviceTypeEnum::DE_2D, (int)EChromaSDKDevice2DEnum::DE_Keypad);
		PluginClearAnimationType((int)EChromaSDKDeviceTypeEnum::DE_2D, (int)EChromaSDKDevice2DEnum::DE_Mouse);
		PluginClearAnimationType((int)EChromaSDKDeviceTypeEnum::DE_1D, (int)EChromaSDKDevice1DEnum::DE_Mousepad);
	}

	EXPORT_API int PluginGetAnimationCount()
	{
		return (int)_gAnimationMapID.size();
	}

	EXPORT_API int PluginGetAnimationId(int index)
	{
		int i = 0;
		for (std::map<string, int>::iterator it = _gAnimationMapID.begin(); it != _gAnimationMapID.end(); ++it)
		{
			if (index == i)
			{
				return (*it).second;
			}
			++i;
		}
		return -1;
	}

	EXPORT_API int PluginGetPlayingAnimationCount()
	{
		if (ChromaThread::Instance() == nullptr)
		{
			return 0;
		}
		return ChromaThread::Instance()->GetAnimationCount();
	}

	EXPORT_API int PluginGetPlayingAnimationId(int index)
	{
		if (ChromaThread::Instance() == nullptr)
		{
			return -1;
		}
		return ChromaThread::Instance()->GetAnimationId(index);
	}

	EXPORT_API int PluginOpenAnimation(const char* path)
	{
		try
		{
			PluginCloseAnimationName(path);

			//return animation id
			AnimationBase* animation = ChromaSDKPlugin::GetInstance()->OpenAnimation(path);
			if (animation == nullptr)
			{
				//LogError("PluginOpenAnimation: Animation is null! name=%s\r\n", path);
				return -1;
			}
			else
			{
				animation->SetName(path);
				int id = _gAnimationId;
				_gAnimations[id] = animation;
				++_gAnimationId;
				_gAnimationMapID[path] = id;
				return id;
			}
		}
		catch (exception)
		{
			LogError("PluginOpenAnimation: Exception path=%s\r\n", path);
			return -1;
		}
	}

	EXPORT_API int PluginOpenAnimationFromMemory(const BYTE* data, const char* name)
	{
		try
		{
			PluginCloseAnimationName(name);

			//return animation id
			AnimationBase* animation = ChromaSDKPlugin::GetInstance()->OpenAnimationFromMemory(data);
			if (animation == nullptr)
			{
				//LogError("PluginOpenAnimationFromMemory: Animation is null! name=%s\r\n", name);
				return -1;
			}
			else
			{
				animation->SetName(name);
				int id = _gAnimationId;
				_gAnimations[id] = animation;
				++_gAnimationId;
				_gAnimationMapID[name] = id;
				return id;
			}
		}
		catch (exception)
		{
			LogError("PluginOpenAnimationFromMemory: Exception path=%s\r\n", name);
			return -1;
		}
	}

	EXPORT_API double PluginOpenAnimationD(const char* path)
	{
		return PluginOpenAnimation(path);
	}

	EXPORT_API int PluginLoadAnimation(int animationId)
	{
		try
		{
			if (_gAnimations.find(animationId) != _gAnimations.end())
			{
				AnimationBase* animation = _gAnimations[animationId];
				if (animation == nullptr)
				{
					LogError("PluginLoadAnimation: Animation is null! id=%d\r\n", animationId);
					return -1;
				}
				animation->Load();
				return animationId;
			}
		}
		catch (exception)
		{
			LogError("PluginLoadAnimation: Exception animationId=%d\r\n", (int)animationId);
		}
		return -1;
	}

	EXPORT_API void PluginLoadAnimationName(const char* path)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginLoadAnimationName: Animation not found! %s\r\n", path);
			return;
		}
		PluginLoadAnimation(animationId);
	}

	EXPORT_API double PluginLoadAnimationD(double animationId)
	{
		return (double)PluginLoadAnimation((int)animationId);
	}

	EXPORT_API int PluginUnloadAnimation(int animationId)
	{
		try
		{
			if (_gAnimations.find(animationId) != _gAnimations.end())
			{
				AnimationBase* animation = _gAnimations[animationId];
				if (animation == nullptr)
				{
					LogError("PluginUnloadAnimation: Animation is null! id=%d\r\n", animationId);
					return -1;
				}
				animation->Unload();
				return animationId;
			}
		}
		catch (exception)
		{
			LogError("PluginUnloadAnimation: Exception animationId=%d\r\n", (int)animationId);
		}
		return -1;
	}

	EXPORT_API void PluginUnloadAnimationName(const char* path)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginUnloadAnimationName: Animation not found! %s\r\n", path);
			return;
		}
		PluginUnloadAnimation(animationId);
	}

	EXPORT_API double PluginUnloadAnimationD(double animationId)
	{
		return (double)PluginUnloadAnimation((int)animationId);
	}

	EXPORT_API int PluginPlayAnimation(int animationId)
	{
		try
		{
			// Chroma thread plays animations
			SetupChromaThread();

			if (!PluginIsInitialized())
			{
				LogError("PluginPlayAnimation: Plugin is not initialized!\r\n");
				return -1;
			}

			if (_gAnimations.find(animationId) != _gAnimations.end())
			{
				AnimationBase* animation = _gAnimations[animationId];
				if (animation == nullptr)
				{
					LogError("PluginPlayAnimation: Animation is null! id=%d\r\n", animationId);
					return -1;
				}
				int deviceType = animation->GetDeviceTypeId();
				int deviceId = animation->GetDeviceId();
				if (deviceType == (int)EChromaSDKDeviceTypeEnum::DE_2D &&
					deviceId == (int)EChromaSDKDevice2DEnum::DE_KeyboardExtended)
				{
					deviceId = (int)EChromaSDKDevice2DEnum::DE_Keyboard;
				}
				PluginStopAnimationType(deviceType, deviceId);
				switch (animation->GetDeviceType())
				{
				case EChromaSDKDeviceTypeEnum::DE_1D:
					_gPlayMap1D[(EChromaSDKDevice1DEnum)deviceId] = animationId;
					break;
				case EChromaSDKDeviceTypeEnum::DE_2D:
					_gPlayMap2D[(EChromaSDKDevice2DEnum)deviceId] = animationId;
					break;
				}
				if (animation->HasUsePreloading())
				{
					animation->Load();
				}
				animation->Play(false);
				return animationId;
			}
		}
		catch (exception)
		{
			LogError("PluginPlayAnimation: Exception animationId=%d\r\n", (int)animationId);
		}
		return -1;
	}

	EXPORT_API double PluginPlayAnimationD(double animationId)
	{
		return (double)PluginPlayAnimation((int)animationId);
	}

	EXPORT_API bool PluginIsPlaying(int animationId)
	{
		try
		{
			if (_gAnimations.find(animationId) != _gAnimations.end())
			{
				AnimationBase* animation = _gAnimations[animationId];
				if (animation == nullptr)
				{
					LogError("PluginIsPlaying: Animation is null! id=%d\r\n", animationId);
					return false;
				}
				return animation->IsPlaying();
			}
		}
		catch (exception)
		{
			LogError("PluginIsPlaying: Exception animationId=%d\r\n", (int)animationId);
		}
		return false;
	}

	EXPORT_API double PluginIsPlayingD(double animationId)
	{
		if (PluginIsPlaying((int)animationId))
		{
			return 1.0;
		}
		else
		{
			return 0.0;
		}
	}

	EXPORT_API int PluginStopAnimation(int animationId)
	{
		try
		{
			if (_gAnimations.find(animationId) != _gAnimations.end())
			{
				AnimationBase* animation = _gAnimations[animationId];
				if (animation == nullptr)
				{
					LogError("PluginStopAnimation: Animation is null! id=%d\r\n", animationId);
					return -1;
				}
				animation->Stop();
				return animationId;
			}
		}
		catch (exception)
		{
			LogError("PluginStopAnimation: Exception animationId=%d\r\n", (int)animationId);
		}
		return -1;
	}

	EXPORT_API double PluginStopAnimationD(double animationId)
	{
		return (double)PluginStopAnimation((int)animationId);
	}

	EXPORT_API int PluginCloseAnimation(int animationId)
	{
		try
		{
			if (_gAnimations.find(animationId) != _gAnimations.end())
			{
				AnimationBase* animation = _gAnimations[animationId];
				if (animation == nullptr)
				{
					LogError("PluginCloseAnimation: Animation is null! id=%d\r\n", animationId);
					return -1;
				}
				animation->Stop();
				animation->Unload();
				string animationName = animation->GetName();
				if (_gAnimationMapID.find(animationName) != _gAnimationMapID.end())
				{
					_gAnimationMapID.erase(animationName);
				}
				if (ChromaThread::Instance())
				{
					ChromaThread::Instance()->DeleteAnimation(animation);
				}
				_gAnimations.erase(animationId);
				return animationId;
			}
		}
		catch (exception)
		{
			LogError("PluginCloseAnimation: Exception animationId=%d\r\n", (int)animationId);
		}
		return -1;
	}

	EXPORT_API double PluginCloseAnimationD(double animationId)
	{
		return (double)PluginCloseAnimation((int)animationId);
	}

	EXPORT_API RZRESULT PluginInit()
	{
		// Chroma thread plays animations
		SetupChromaThread();

		PluginUseIdleAnimations(false);
		PluginStopAll();
		PluginCloseAll();

		_gAnimationId = 0;

		return RzChromaSDK::Init();
	}

	EXPORT_API RZRESULT PluginInitSDK(ChromaSDK::APPINFOTYPE* AppInfo)
	{
		// Chroma thread plays animations
		SetupChromaThread();

		PluginUseIdleAnimations(false);
		PluginStopAll();
		PluginCloseAll();

		_gAnimationId = 0;

		return RzChromaSDK::InitSDK(AppInfo);
	}

	EXPORT_API double PluginInitD()
	{
		return (double)PluginInit();
	}

	EXPORT_API RZRESULT PluginUninit()
	{
		// Chroma thread plays animations
		StopChromaThread();

		RZRESULT result = RzChromaSDK::UnInit();
		if (PluginIsInitialized())
		{
			while (_gAnimations.size() > 0)
			{
				auto iter = _gAnimations.begin();
				int animationId = iter->first;
				PluginCloseAnimation(animationId);
			}
		}
		_gAnimationId = 0;
		_gAnimationMapID.clear();
		_gAnimations.clear();
		_gPlayMap1D.clear();
		_gPlayMap2D.clear();
		return result;
	}

	EXPORT_API double PluginUninitD()
	{
		return (double)PluginUninit();
	}

	EXPORT_API int PluginCreateAnimationInMemory(int deviceType, int device)
	{
		switch ((EChromaSDKDeviceTypeEnum)deviceType)
		{
		case EChromaSDKDeviceTypeEnum::DE_1D:
			{
				Animation1D* animation1D = new Animation1D();
				animation1D->SetDevice((EChromaSDKDevice1DEnum)device);
				vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
				frames.clear();
				FChromaSDKColorFrame1D frame = FChromaSDKColorFrame1D();
				frame.Colors = ChromaSDKPlugin::GetInstance()->CreateColors1D((EChromaSDKDevice1DEnum)device);
				frames.push_back(frame);

				int id = _gAnimationId;
				_gAnimations[id] = animation1D;
				++_gAnimationId;
				return id;
			}
			break;
		case EChromaSDKDeviceTypeEnum::DE_2D:
			{
				Animation2D* animation2D = new Animation2D();
				animation2D->SetDevice((EChromaSDKDevice2DEnum)device);
				vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
				frames.clear();
				FChromaSDKColorFrame2D frame = FChromaSDKColorFrame2D((EChromaSDKDevice2DEnum)device);
				frame.Colors = ChromaSDKPlugin::GetInstance()->CreateColors2D((EChromaSDKDevice2DEnum)device);
				frames.push_back(frame);
				
				int id = _gAnimationId;
				_gAnimations[id] = animation2D;
				++_gAnimationId;
				return id;
			}
			break;
		}
		return -1;
	}

	EXPORT_API int PluginCreateAnimation(const char* path, int deviceType, int device)
	{
		switch ((EChromaSDKDeviceTypeEnum)deviceType)
		{
			case EChromaSDKDeviceTypeEnum::DE_1D:
				{
					Animation1D* animation1D = new Animation1D();
					animation1D->SetDevice((EChromaSDKDevice1DEnum)device);
					vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
					frames.clear();
					FChromaSDKColorFrame1D frame = FChromaSDKColorFrame1D();
					frame.Colors = ChromaSDKPlugin::GetInstance()->CreateColors1D((EChromaSDKDevice1DEnum)device);
					frames.push_back(frame);
					animation1D->Save(path);
					delete animation1D;
					return PluginOpenAnimation(path);
				}
				break;
			case EChromaSDKDeviceTypeEnum::DE_2D:
				{
					Animation2D* animation2D = new Animation2D();
					animation2D->SetDevice((EChromaSDKDevice2DEnum)device);
					vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
					frames.clear();
					FChromaSDKColorFrame2D frame = FChromaSDKColorFrame2D((EChromaSDKDevice2DEnum)device);
					frame.Colors = ChromaSDKPlugin::GetInstance()->CreateColors2D((EChromaSDKDevice2DEnum)device);
					frames.push_back(frame);
					animation2D->Save(path);
					delete animation2D;
					return PluginOpenAnimation(path);
				}
				break;
		}
		return -1;
	}

	EXPORT_API int PluginSaveAnimation(int animationId, const char* path)
	{
		PluginStopAnimation(animationId);

		if (_gAnimations.find(animationId) != _gAnimations.end())
		{
			AnimationBase* animation = _gAnimations[animationId];
			if (animation == nullptr)
			{
				LogError("PluginSaveAnimation: Animation is null! id=%d\r\n", animationId);
				return -1;
			}
			animation->Save(path);
			return animationId;
		}
		return -1;
	}

	EXPORT_API int PluginSaveAnimationName(const char* sourceAnimation, const char* targetAnimation)
	{
		int animationId = PluginGetAnimation(sourceAnimation);
		if (animationId < 0)
		{
			LogError("PluginSaveAnimationName: Animation not found! %s\r\n", sourceAnimation);
			return -1;
		}
		return PluginSaveAnimation(animationId, targetAnimation);
	}

	EXPORT_API int PluginResetAnimation(int animationId)
	{
		PluginStopAnimation(animationId);

		if (_gAnimations.find(animationId) != _gAnimations.end())
		{
			AnimationBase* animation = _gAnimations[animationId];
			if (animation == nullptr)
			{
				LogError("PluginResetAnimation: Animation is null! id=%d\r\n", animationId);
				return -1;
			}
			animation->ResetFrames();
			return animationId;
		}

		return -1;
	}

	EXPORT_API int PluginGetFrameCount(int animationId)
	{
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			LogError("PluginGetFrameCount: Animation is null! id=%d\r\n", animationId);
			return -1;
		}
		return animation->GetFrameCount();
	}

	EXPORT_API int PluginGetFrameCountName(const char* path)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginGetFrameCountName: Animation not found! %s\r\n", path);
			return -1;
		}
		return PluginGetFrameCount(animationId);
	}

	EXPORT_API double PluginGetFrameCountNameD(const char* path)
	{
		return (double)PluginGetFrameCountName(path);
	}

	EXPORT_API int PluginGetCurrentFrame(int animationId)
	{
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			LogError("PluginGetCurrentFrame: Animation is null! id=%d", animationId);
			return -1;
		}
		return animation->GetCurrentFrame();
	}

	EXPORT_API int PluginGetCurrentFrameName(const char* path)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginGetCurrentFrameName: Animation not found! %s\r\n", path);
			return -1;
		}
		return PluginGetCurrentFrame(animationId);
	}

	EXPORT_API double PluginGetCurrentFrameNameD(const char* path)
	{
		return (double)PluginGetCurrentFrameName(path);
	}

	EXPORT_API int PluginGetDeviceType(int animationId)
	{
		if (_gAnimations.find(animationId) != _gAnimations.end())
		{
			AnimationBase* animation = _gAnimations[animationId];
			if (animation == nullptr)
			{
				LogError("PluginGetDeviceType: Animation is null! id=%d\r\n", animationId);
				return -1;
			}
			return (int)animation->GetDeviceType();
		}

		return -1;
	}

	EXPORT_API int PluginGetDeviceTypeName(const char* path)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginGetDeviceTypeName: Animation not found! %s\r\n", path);
			return -1;
		}
		return PluginGetDeviceType(animationId);
	}

	EXPORT_API double PluginGetDeviceTypeNameD(const char* path)
	{
		return (double)PluginGetDeviceTypeName(path);
	}

	EXPORT_API int PluginGetDevice(int animationId)
	{
		if (_gAnimations.find(animationId) != _gAnimations.end())
		{
			AnimationBase* animation = _gAnimations[animationId];
			if (animation == nullptr)
			{
				LogError("PluginGetDevice: Animation is null! id=%d\r\n", animationId);
				return -1;
			}
			switch (animation->GetDeviceType())
			{
			case EChromaSDKDeviceTypeEnum::DE_1D:
				{
					Animation1D* animation1D = dynamic_cast<Animation1D*>(animation);
					return (int)animation1D->GetDevice();
				}
				break;
			case EChromaSDKDeviceTypeEnum::DE_2D:
				{
					Animation2D* animation2D = dynamic_cast<Animation2D*>(animation);
					return (int)animation2D->GetDevice();
				}
				break;
			}
		}

		return -1;
	}

	EXPORT_API int PluginGetDeviceName(const char* path)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginGetDeviceName: Animation not found! %s\r\n", path);
			return -1;
		}
		return PluginGetDevice(animationId);
	}

	EXPORT_API double PluginGetDeviceNameD(const char* path)
	{
		return (double)PluginGetDeviceName(path);
	}

	EXPORT_API int PluginSetDevice(int animationId, int deviceType, int device)
	{
		PluginStopAnimation(animationId);

		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			LogError("PluginSetDevice: Animation is null! id=%d\r\n", animationId);
			return -1;
		}
		string path = animation->GetName();
		PluginCloseAnimation(animationId);
		return PluginCreateAnimation(path.c_str(), deviceType, device);
	}

	EXPORT_API int PluginGetMaxLeds(int device)
	{
		return ChromaSDKPlugin::GetInstance()->GetMaxLeds((EChromaSDKDevice1DEnum)device);
	}

	EXPORT_API double PluginGetMaxLedsD(double device)
	{
		return (double)PluginGetMaxLeds((int)device);
	}

	EXPORT_API int PluginGetMaxRow(int device)
	{
		return ChromaSDKPlugin::GetInstance()->GetMaxRow((EChromaSDKDevice2DEnum)device);
	}

	EXPORT_API double PluginGetMaxRowD(double device)
	{
		return (double)PluginGetMaxRow((int)device);
	}

	EXPORT_API int PluginGetMaxColumn(int device)
	{
		return ChromaSDKPlugin::GetInstance()->GetMaxColumn((EChromaSDKDevice2DEnum)device);
	}

	EXPORT_API double PluginGetMaxColumnD(double device)
	{
		return (double)PluginGetMaxColumn((int)device);
	}

	EXPORT_API int PluginAddFrame(int animationId, float duration, int* colors, int length)
	{
		PluginStopAnimation(animationId);

		if (_gAnimations.find(animationId) != _gAnimations.end())
		{
			AnimationBase* animation = _gAnimations[animationId];
			if (animation == nullptr)
			{
				LogError("PluginAddFrame: Animation is null! id=%d\r\n", animationId);
				return -1;
			}
			switch (animation->GetDeviceType())
			{
			case EChromaSDKDeviceTypeEnum::DE_1D:
				{
					Animation1D* animation1D = dynamic_cast<Animation1D*>(animation);
					int maxLeds = ChromaSDKPlugin::GetInstance()->GetMaxLeds(animation1D->GetDevice());
					vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
					FChromaSDKColorFrame1D frame = FChromaSDKColorFrame1D();
					if (duration < 0.033f)
					{
						duration = 0.033f;
					}
					frame.Duration = duration;
					vector<COLORREF> newColors = ChromaSDKPlugin::GetInstance()->CreateColors1D(animation1D->GetDevice());
					for (int i = 0; i < maxLeds && i < length; ++i)
					{
						newColors[i] = colors[i];
					}
					frame.Colors = newColors;
					frames.push_back(frame);
				}
				break;
			case EChromaSDKDeviceTypeEnum::DE_2D:
				{
					Animation2D* animation2D = dynamic_cast<Animation2D*>(animation);
					int maxRow = ChromaSDKPlugin::GetInstance()->GetMaxRow(animation2D->GetDevice());
					int maxColumn = ChromaSDKPlugin::GetInstance()->GetMaxColumn(animation2D->GetDevice());
					vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
					FChromaSDKColorFrame2D frame = FChromaSDKColorFrame2D(animation2D->GetDevice());
					if (duration < 0.033f)
					{
						duration = 0.033f;
					}
					frame.Duration = duration;
					vector<FChromaSDKColors> newColors = ChromaSDKPlugin::GetInstance()->CreateColors2D(animation2D->GetDevice());
					int index = 0;
					for (int i = 0; i < maxRow && index < length; ++i)
					{
						std::vector<COLORREF>& row = newColors[i].Colors;
						for (int j = 0; j < maxColumn && index < length; ++j)
						{
							row[j] = colors[index];
							++index;
						}
					}
					frame.Colors = newColors;
					frames.push_back(frame);
				}
				break;
			}
			return animationId;
		}

		return -1;
	}

	EXPORT_API int PluginUpdateFrame(int animationId, int frameIndex, float duration, int* colors, int length, int* keys, int keysLength)
	{
		PluginStopAnimation(animationId);

		if (_gAnimations.find(animationId) != _gAnimations.end())
		{
			AnimationBase* animation = _gAnimations[animationId];
			if (animation == nullptr)
			{
				LogError("PluginUpdateFrame: Animation is null! id=%d\r\n", animationId);
				return -1;
			}
			switch (animation->GetDeviceType())
			{
			case EChromaSDKDeviceTypeEnum::DE_1D:
				{
					Animation1D* animation1D = dynamic_cast<Animation1D*>(animation);
					int maxLeds = ChromaSDKPlugin::GetInstance()->GetMaxLeds(animation1D->GetDevice());
					vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
					if (frameIndex < 0 || frameIndex >= int(frames.size()))
					{
						LogError("PluginUpdateFrame: frame index is invalid! %d of %d\r\n", frameIndex, int(frames.size()));
						return -1;
					}
					FChromaSDKColorFrame1D& frame = frames[frameIndex];
					if(duration < 0.033f)
					{
						duration = 0.033f;
					}
					frame.Duration = duration;
					vector<COLORREF> newColors = ChromaSDKPlugin::GetInstance()->CreateColors1D(animation1D->GetDevice());
					for (int i = 0; i < maxLeds && i < length; ++i)
					{
						newColors[i] = colors[i];
					}
					frame.Colors = newColors;
				}
				break;
			case EChromaSDKDeviceTypeEnum::DE_2D:
				{
					Animation2D* animation2D = dynamic_cast<Animation2D*>(animation);
					int maxRow = ChromaSDKPlugin::GetInstance()->GetMaxRow(animation2D->GetDevice());
					int maxColumn = ChromaSDKPlugin::GetInstance()->GetMaxColumn(animation2D->GetDevice());
					vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
					if (frameIndex < 0 || frameIndex >= int(frames.size()))
					{
						LogError("PluginUpdateFrame: frame index is invalid! %d of %d\r\n", frameIndex, int(frames.size()));
						return -1;
					}
					FChromaSDKColorFrame2D& frame = frames[frameIndex];
					if (duration < 0.033f)
					{
						duration = 0.033f;
					}
					frame.Duration = duration;
					
					vector<FChromaSDKColors> newColors = ChromaSDKPlugin::GetInstance()->CreateColors2D(animation2D->GetDevice());					
					int index = 0;
					for (int i = 0; i < maxRow && index < length; ++i)
					{
						std::vector<COLORREF>& row = newColors[i].Colors;
						for (int j = 0; j < maxColumn && index < length; ++j)
						{
							row[j] = colors[index];
							++index;
						}
					}
					frame.Colors = newColors;

					switch (animation2D->GetDevice()) {
					case EChromaSDKDevice2DEnum::DE_Keyboard:
					case EChromaSDKDevice2DEnum::DE_KeyboardExtended:
						if (keys)
						{
							// Keyboard and KeyboardExtended are 6x22
							maxRow = ChromaSDKPlugin::GetInstance()->GetMaxRow(EChromaSDKDevice2DEnum::DE_Keyboard);
							maxColumn = ChromaSDKPlugin::GetInstance()->GetMaxColumn(EChromaSDKDevice2DEnum::DE_Keyboard);

							vector<FChromaSDKColors> newKeys = ChromaSDKPlugin::GetInstance()->CreateColors2D(animation2D->GetDevice());
							index = 0;
							for (int i = 0; i < maxRow && index < keysLength; ++i)
							{
								std::vector<COLORREF>& row = newKeys[i].Colors;
								for (int j = 0; j < maxColumn && index < keysLength; ++j)
								{
									row[j] = keys[index];
									++index;
								}
							}
							frame.Keys = newKeys;
						}
						break;
					}					
				}
				break;
			}
			return animationId;
		}

		return -1;
	}

	EXPORT_API int PluginUpdateFrameName(const char* path, int frameIndex, float duration, int* colors, int length, int* keys, int keysLength)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginUpdateFrameName: Animation not found! %s\r\n", path);
			return -1;
		}
		return PluginUpdateFrame(animationId, frameIndex, duration, colors, length, keys, keysLength);
	}

	EXPORT_API int PluginGetFrame(int animationId, int frameIndex, float* duration, int* colors, int length)
	{
		PluginStopAnimation(animationId);

		if (_gAnimations.find(animationId) != _gAnimations.end())
		{
			AnimationBase* animation = _gAnimations[animationId];
			if (animation == nullptr)
			{
				LogError("PluginGetFrame: Animation is null! id=%d\r\n", animationId);
				return -1;
			}
			switch (animation->GetDeviceType())
			{
			case EChromaSDKDeviceTypeEnum::DE_1D:
				{
					Animation1D* animation1D = dynamic_cast<Animation1D*>(animation);
					int maxLeds = ChromaSDKPlugin::GetInstance()->GetMaxLeds(animation1D->GetDevice());
					vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
					if (frameIndex < 0 || frameIndex >= int(frames.size()))
					{
						LogError("PluginGetFrame: frame index is invalid! %d of %d\r\n", frameIndex, int(frames.size()));
						return -1;
					}
					FChromaSDKColorFrame1D& frame = frames[frameIndex];
					*duration = frame.Duration;
					vector<COLORREF>& frameColors = frame.Colors;
					for (int i = 0; i < maxLeds && i < length; ++i)
					{
						colors[i] = frameColors[i];
					}
				}
				break;
			case EChromaSDKDeviceTypeEnum::DE_2D:
				{
					Animation2D* animation2D = dynamic_cast<Animation2D*>(animation);
					int maxRow = ChromaSDKPlugin::GetInstance()->GetMaxRow(animation2D->GetDevice());
					int maxColumn = ChromaSDKPlugin::GetInstance()->GetMaxColumn(animation2D->GetDevice());
					vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
					if (frameIndex < 0 || frameIndex >= int(frames.size()))
					{
						LogError("PluginGetFrame: frame index is invalid! %d of %d\r\n", frameIndex, int(frames.size()));
						return -1;
					}
					FChromaSDKColorFrame2D& frame = frames[frameIndex];
					*duration = frame.Duration;
					vector<FChromaSDKColors>& frameColors = frame.Colors;
					int index = 0;
					for (int i = 0; i < maxRow && index < length; ++i)
					{
						std::vector<COLORREF>& row = frameColors[i].Colors;
						for (int j = 0; j < maxColumn && index < length; ++j)
						{
							colors[index] = row[j];
							++index;
						}
					}
				}
				break;
			}
			return animationId;
		}

		return -1;
	}

	EXPORT_API int PluginPreviewFrame(int animationId, int frameIndex)
	{
		//LogDebug("PluginPreviewFrame: animationId=%d frameIndex=%d\r\n", animationId, frameIndex);

		PluginStopAnimation(animationId);

		// Chroma thread plays animations
		SetupChromaThread();

		if (!PluginIsInitialized())
		{
			LogError("PluginPreviewFrame: Plugin is not initialized!\r\n");
			return -1;
		}

		if (_gAnimations.find(animationId) != _gAnimations.end())
		{
			AnimationBase* animation = _gAnimations[animationId];
			if (animation == nullptr)
			{
				LogError("PluginPreviewFrame: Animation is null! id=%d\r\n", animationId);
				return -1;
			}
			switch (animation->GetDeviceType())
			{
			case EChromaSDKDeviceTypeEnum::DE_1D:
				{
					Animation1D* animation1D = dynamic_cast<Animation1D*>(animation);
					int maxLeds = ChromaSDKPlugin::GetInstance()->GetMaxLeds(animation1D->GetDevice());
					vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
					if (frameIndex < 0 || frameIndex >= int(frames.size()))
					{
						LogError("PluginPreviewFrame: frame index is invalid! %d of %d\r\n", frameIndex, int(frames.size()));
						return -1;
					}
					FChromaSDKColorFrame1D& frame = frames[frameIndex];
					vector<COLORREF>& colors = frame.Colors;
					FChromaSDKEffectResult result = ChromaSDKPlugin::GetInstance()->CreateEffectCustom1D(animation1D->GetDevice(), colors);
					if (result.Result == 0)
					{
						ChromaSDKPlugin::GetInstance()->SetEffect(result.EffectId);
						ChromaSDKPlugin::GetInstance()->DeleteEffect(result.EffectId);
					}
				}
				break;
			case EChromaSDKDeviceTypeEnum::DE_2D:
				{
					Animation2D* animation2D = dynamic_cast<Animation2D*>(animation);
					int maxRow = ChromaSDKPlugin::GetInstance()->GetMaxRow(animation2D->GetDevice());
					int maxColumn = ChromaSDKPlugin::GetInstance()->GetMaxColumn(animation2D->GetDevice());
					vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
					if (frameIndex < 0 || frameIndex >= int(frames.size()))
					{
						LogError("PluginPreviewFrame: frame index is invalid! %d of %d\r\n", frameIndex, int(frames.size()));
						return -1;
					}
					FChromaSDKColorFrame2D& frame = frames[frameIndex];
					vector<FChromaSDKColors>& colors = frame.Colors;
					vector<FChromaSDKColors>& keys = frame.Keys;
					FChromaSDKEffectResult result;
					switch (animation2D->GetDevice())
					{
					case EChromaSDKDevice2DEnum::DE_Keyboard:
						if (animation2D->UseChromaCustom())
						{
							result = ChromaSDKPlugin::GetInstance()->CreateEffectKeyboardCustom2D(colors, keys);
						}
						else
						{
							result = ChromaSDKPlugin::GetInstance()->CreateEffectCustom2D(animation2D->GetDevice(), colors, keys);
						}
						break;
					case EChromaSDKDevice2DEnum::DE_KeyboardExtended:
						if (animation2D->UseChromaCustom())
						{
							result = ChromaSDKPlugin::GetInstance()->CreateEffectKeyboardExtendedCustom2D(colors, keys);
						}
						else
						{
							result = ChromaSDKPlugin::GetInstance()->CreateEffectCustom2D(animation2D->GetDevice(), colors, keys);
						}
						break;
					default:
						result = ChromaSDKPlugin::GetInstance()->CreateEffectCustom2D(animation2D->GetDevice(), colors, keys);
						break;
					}					
					if (result.Result == 0)
					{
						ChromaSDKPlugin::GetInstance()->SetEffect(result.EffectId);
						ChromaSDKPlugin::GetInstance()->DeleteEffect(result.EffectId);
					}
				}
				break;
			}
			return animationId;
		}

		return -1;
	}

	EXPORT_API void PluginPreviewFrameName(const char* path, int frameIndex)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginPreviewFrameName: Animation not found! %s\r\n", path);
			return;
		}
		PluginPreviewFrame(animationId, frameIndex);
	}

	EXPORT_API double PluginPreviewFrameD(double animationId, double frameIndex)
	{
		return (int)PluginPreviewFrame((int)animationId, (int)frameIndex);
	}

	EXPORT_API int PluginOverrideFrameDuration(int animationId, float duration)
	{
		PluginStopAnimation(animationId);

		if (_gAnimations.find(animationId) != _gAnimations.end())
		{
			AnimationBase* animation = _gAnimations[animationId];
			if (animation == nullptr)
			{
				LogError("PluginOverrideFrameDuration: Animation is null! id=%d\r\n", animationId);
				return -1;
			}
			switch (animation->GetDeviceType())
			{
			case EChromaSDKDeviceTypeEnum::DE_1D:
				{
					Animation1D* animation1D = dynamic_cast<Animation1D*>(animation);
					vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
					for (int i = 0; i < int(frames.size()); ++i)
					{
						FChromaSDKColorFrame1D& frame = frames[i];
						if (duration < 0.033f)
						{
							duration = 0.033f;
						}
						frame.Duration = duration;
					}
				}
				break;
			case EChromaSDKDeviceTypeEnum::DE_2D:
				{
					Animation2D* animation2D = dynamic_cast<Animation2D*>(animation);
					vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
					for (int i = 0; i < int(frames.size()); ++i)
					{
						FChromaSDKColorFrame2D& frame = frames[i];
						if (duration < 0.033f)
						{
							duration = 0.033f;
						}
						frame.Duration = duration;
					}
				}
				break;
			}
			return animationId;
		}

		return -1;
	}

	EXPORT_API void PluginOverrideFrameDurationName(const char* path, float duration)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginOverrideFrameDurationName: Animation not found! %s\r\n", path);
			return;
		}
		PluginOverrideFrameDuration(animationId, duration);
	}

	EXPORT_API double PluginOverrideFrameDurationD(double animationId, double duration)
	{
		return (double)PluginOverrideFrameDuration((int)animationId, (float)duration);
	}

	EXPORT_API int PluginReverse(int animationId)
	{
		PluginStopAnimation(animationId);

		if (_gAnimations.find(animationId) != _gAnimations.end())
		{
			AnimationBase* animation = _gAnimations[animationId];
			if (animation == nullptr)
			{
				LogError("PluginReverse: Animation is null! id=%d\r\n", animationId);
				return -1;
			}
			switch (animation->GetDeviceType())
			{
				case EChromaSDKDeviceTypeEnum::DE_1D:
				{
					Animation1D* animation1D = dynamic_cast<Animation1D*>(animation);
					vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
					vector<FChromaSDKColorFrame1D> copy = vector<FChromaSDKColorFrame1D>();
					for (int i = int(frames.size()) - 1; i >= 0; --i)
					{
						FChromaSDKColorFrame1D& frame = frames[i];
						copy.push_back(frame);
					}
					frames.clear();
					for (int i = 0; i < int(copy.size()); ++i)
					{
						FChromaSDKColorFrame1D& frame = copy[i];
						frames.push_back(frame);
					}
				}
				break;
				case EChromaSDKDeviceTypeEnum::DE_2D:
				{
					Animation2D* animation2D = dynamic_cast<Animation2D*>(animation);
					vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
					vector<FChromaSDKColorFrame2D> copy = vector<FChromaSDKColorFrame2D>();
					for (int i = int(frames.size()) - 1; i >= 0; --i)
					{
						FChromaSDKColorFrame2D& frame = frames[i];
						copy.push_back(frame);
					}
					frames.clear();
					for (int i = 0; i < int(copy.size()); ++i)
					{
						FChromaSDKColorFrame2D& frame = copy[i];
						frames.push_back(frame);
					}
				}
				break;
			}
			return animationId;
		}

		return -1;
	}

	EXPORT_API int PluginMirrorHorizontally(int animationId)
	{
		PluginStopAnimation(animationId);

		if (_gAnimations.find(animationId) != _gAnimations.end())
		{
			AnimationBase* animation = _gAnimations[animationId];
			if (animation == nullptr)
			{
				LogError("PluginMirrorHorizontally: Animation is null! id=%d\r\n", animationId);
				return -1;
			}
			switch (animation->GetDeviceType())
			{
				case EChromaSDKDeviceTypeEnum::DE_1D:
				{
					Animation1D* animation1D = dynamic_cast<Animation1D*>(animation);
					vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
					int maxLeds = ChromaSDKPlugin::GetInstance()->GetMaxLeds(animation1D->GetDevice());
					for (int index = 0; index < int(frames.size()); ++index)
					{
						FChromaSDKColorFrame1D& frame = frames[index];
						std::vector<COLORREF>& colors = frame.Colors;
						std::vector<COLORREF> newColors = ChromaSDKPlugin::GetInstance()->CreateColors1D(animation1D->GetDevice());
						for (int i = 0; i < maxLeds; ++i)
						{
							int reverse = maxLeds - 1 - i;
							newColors[i] = colors[reverse];
						}
						frame.Colors = newColors;
					}
				}
				break;
				case EChromaSDKDeviceTypeEnum::DE_2D:
				{
					Animation2D* animation2D = dynamic_cast<Animation2D*>(animation);
					vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
					int maxRow = ChromaSDKPlugin::GetInstance()->GetMaxRow(animation2D->GetDevice());
					int maxColumn = ChromaSDKPlugin::GetInstance()->GetMaxColumn(animation2D->GetDevice());
					for (int index = 0; index < int(frames.size()); ++index)
					{
						FChromaSDKColorFrame2D& frame = frames[index];
						std::vector<FChromaSDKColors>& colors = frame.Colors;
						std::vector<FChromaSDKColors> newColors = ChromaSDKPlugin::GetInstance()->CreateColors2D(animation2D->GetDevice());
						for (int i = 0; i < maxRow; ++i)
						{
							std::vector<COLORREF>& row = colors[i].Colors;
							std::vector<COLORREF>& newRow = newColors[i].Colors;
							for (int j = 0; j < maxColumn; ++j)
							{
								int reverse = maxColumn - 1 - j;
								newRow[j] = row[reverse];
							}
						}
						frame.Colors = newColors;
					}
				}
				break;
			}
			return animationId;
		}

		return -1;
	}

	EXPORT_API int PluginMirrorVertically(int animationId)
	{
		PluginStopAnimation(animationId);

		if (_gAnimations.find(animationId) != _gAnimations.end())
		{
			AnimationBase* animation = _gAnimations[animationId];
			if (animation == nullptr)
			{
				LogError("PluginMirrorVertically: Animation is null! id=%d\r\n", animationId);
				return -1;
			}
			switch (animation->GetDeviceType())
			{
				case EChromaSDKDeviceTypeEnum::DE_1D:
				//skip, only 1 high
				break;
				case EChromaSDKDeviceTypeEnum::DE_2D:
				{
					Animation2D* animation2D = dynamic_cast<Animation2D*>(animation);
					vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
					int maxRow = ChromaSDKPlugin::GetInstance()->GetMaxRow(animation2D->GetDevice());
					for (int index = 0; index < int(frames.size()); ++index)
					{
						FChromaSDKColorFrame2D& frame = frames[index];
						std::vector<FChromaSDKColors>& colors = frame.Colors;
						std::vector<FChromaSDKColors> newColors = ChromaSDKPlugin::GetInstance()->CreateColors2D(animation2D->GetDevice());
						for (int i = 0; i < maxRow; ++i)
						{
							int reverse = maxRow - 1 - i;
							newColors[reverse].Colors = colors[i].Colors;
						}
						frame.Colors = newColors;
					}
				}
				break;
			}
			return animationId;
		}

		return -1;
	}

	int PluginGetAnimationIdFromInstance(AnimationBase* animation)
	{
		if (animation == nullptr)
		{
			LogError("PluginGetAnimationIdFromInstance: Invalid animation!\r\n");
			return -1;
		}
		for (int index = 0; index < int(_gAnimations.size()); ++index)
		{
			if (_gAnimations[index] == animation)
			{
				return index;
			}
		}
		return -1;
	}

	int GetAnimationIdFromInstance(AnimationBase* animation)
	{
		if (animation == nullptr)
		{
			ChromaLogger::fprintf(stderr, "GetAnimationIdFromInstance: Invalid animation!\r\n");
			return -1;
		}
		for (auto iter = _gAnimations.begin(); iter != _gAnimations.end(); ++iter)
		{
			if (iter->second == animation)
			{
				return iter->first;
			}
		}
		return -1;
	}

	AnimationBase* GetAnimationInstance(int animationId)
	{
		if (_gAnimations.find(animationId) != _gAnimations.end())
		{
			return _gAnimations[animationId];
		}
		return nullptr;
	}

	AnimationBase* GetAnimationInstanceName(const char* path)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			//LogError("GetAnimationInstanceName: Animation not found! %s\r\n", path);
			return nullptr;
		}
		return GetAnimationInstance(animationId);
	}

	ChromaSDK::AnimationBase* GetAnimationInstanceIfOpenName(const char* path)
	{
		auto it = _gAnimationMapID.find(path);
		if (it != _gAnimationMapID.end())
		{
			return GetAnimationInstance(it->second);
		}
		//LogError("GetAnimationInstanceIfOpenName: Animation not found! %s\r\n", path);
		return nullptr;
	}

	EXPORT_API int PluginGetAnimation(const char* name)
	{
		if (_gAnimationMapID.find(name) != _gAnimationMapID.end())
		{
			return _gAnimationMapID[name];
		}
		return PluginOpenAnimation(name);
	}

	EXPORT_API double PluginGetAnimationD(const char* name)
	{
		return PluginGetAnimation(name);
	}

	EXPORT_API void PluginCloseAnimationName(const char* path)
	{
		if (_gAnimationMapID.find(path) != _gAnimationMapID.end())
		{
			int animationId = _gAnimationMapID[path];
			PluginCloseAnimation(animationId);
		}
		/*
		else
		{
			LogError("PluginCloseAnimationName: Animation not found! %s\r\n", path);
		}
		*/
	}

	EXPORT_API double PluginCloseAnimationNameD(const char* path)
	{
		PluginCloseAnimationName(path);
		return 0;
	}

	EXPORT_API void PluginCloseAll()
	{
		while (PluginGetAnimationCount() > 0)
		{
			int animationId = PluginGetAnimationId(0);
			PluginCloseAnimation(animationId);
		}
	}

	EXPORT_API void PluginPlayAnimationLoop(int animationId, bool loop)
	{
		// Chroma thread plays animations
		SetupChromaThread();

		if (!PluginIsInitialized())
		{
			LogError("PluginPlayAnimationLoop: Plugin is not initialized!\r\n");
			return;
		}

		if (_gAnimations.find(animationId) != _gAnimations.end())
		{
			AnimationBase* animation = _gAnimations[animationId];
			if (animation == nullptr)
			{
				LogError("PluginPlayAnimationLoop: Animation is null! id=%d\r\n", animationId);
				return;
			}
			int deviceType = animation->GetDeviceType();
			int deviceId = animation->GetDeviceId();
			if (deviceType == (int)EChromaSDKDeviceTypeEnum::DE_2D &&
				deviceId == (int)EChromaSDKDevice2DEnum::DE_KeyboardExtended)
			{
				deviceId = (int)EChromaSDKDevice2DEnum::DE_Keyboard;
			}
			PluginStopAnimationType(deviceType, deviceId);
			//LogDebug("PluginPlayAnimationLoop: %s\r\n", animation->GetName().c_str());
			switch (deviceType)
			{
			case EChromaSDKDeviceTypeEnum::DE_1D:
				_gPlayMap1D[(EChromaSDKDevice1DEnum)deviceId] = animationId;
				break;
			case EChromaSDKDeviceTypeEnum::DE_2D:
				_gPlayMap2D[(EChromaSDKDevice2DEnum)deviceId] = animationId;
				break;
			}
			if (animation->HasUsePreloading())
			{
				animation->Load();
			}
			animation->Play(loop);
		}
	}

	EXPORT_API void PluginPlayAnimationName(const char* path, bool loop)
	{

		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			//LogError("PluginPlayAnimationName: Animation not found! %s\r\n", path);
			return;
		}
		PluginPlayAnimationLoop(animationId, loop);
	}

	EXPORT_API double PluginPlayAnimationNameD(const char* path, double loop)
	{
		if (loop == 0)
		{
			PluginPlayAnimationName(path, false);
		}
		else
		{
			PluginPlayAnimationName(path, true);
		}
		return 0;
	}

	EXPORT_API void PluginPlayAnimationFrame(int animationId, int frameId, bool loop)
	{
		if (_gAnimations.find(animationId) != _gAnimations.end())
		{
			AnimationBase* animation = _gAnimations[animationId];
			if (animation == nullptr)
			{
				LogError("PluginPlayAnimationFrame: Animation is null! id=%d\r\n", animationId);
				return;
			}
			PluginStopAnimationType(animation->GetDeviceType(), animation->GetDeviceId());
			//LogDebug("PluginPlayAnimationFrame: %s\r\n", animation->GetName().c_str());
			animation->SetCurrentFrame(frameId);
			switch (animation->GetDeviceType())
			{
			case EChromaSDKDeviceTypeEnum::DE_1D:
				_gPlayMap1D[(EChromaSDKDevice1DEnum)animation->GetDeviceId()] = animationId;
				break;
			case EChromaSDKDeviceTypeEnum::DE_2D:
				_gPlayMap2D[(EChromaSDKDevice2DEnum)animation->GetDeviceId()] = animationId;
				break;
			}
			if (animation->HasUsePreloading())
			{
				animation->Load();
			}
			animation->Play(loop);
		}
	}

	EXPORT_API void PluginPlayAnimationFrameName(const char* path, int frameId, bool loop)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginPlayAnimationFrameName: Animation not found! %s\r\n", path);
			return;
		}
		PluginPlayAnimationFrame(animationId, frameId, loop);
	}

	EXPORT_API double PluginPlayAnimationFrameNameD(const char* path, double frameId, double loop)
	{
		if (loop == 0)
		{
			PluginPlayAnimationFrameName(path, (int)frameId, false);
		}
		else
		{
			PluginPlayAnimationFrameName(path, (int)frameId, true);
		}
		return 0;
	}

	EXPORT_API void PluginStopAnimationName(const char* path)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginStopAnimationName: Animation not found! %s\r\n", path);
			return;
		}
		PluginStopAnimation(animationId);
	}

	EXPORT_API double PluginStopAnimationNameD(const char* path)
	{
		PluginStopAnimationName(path);
		return 0;
	}

	EXPORT_API void PluginStopAnimationType(int deviceType, int device)
	{
		int deviceId = device;
		if (deviceType == (int)EChromaSDKDeviceTypeEnum::DE_2D &&
			device == (int)EChromaSDKDevice2DEnum::DE_KeyboardExtended)
		{
			deviceId = (int)EChromaSDKDevice2DEnum::DE_Keyboard;
		}

		switch ((EChromaSDKDeviceTypeEnum)deviceType)
		{
		case EChromaSDKDeviceTypeEnum::DE_1D:
			{
				if (_gPlayMap1D.find((EChromaSDKDevice1DEnum)deviceId) != _gPlayMap1D.end())
				{
					int prevAnimation = _gPlayMap1D[(EChromaSDKDevice1DEnum)deviceId];
					if (prevAnimation != -1)
					{
						PluginStopAnimation(prevAnimation);
						_gPlayMap1D[(EChromaSDKDevice1DEnum)deviceId] = -1;
					}
				}
			}
			break;
		case EChromaSDKDeviceTypeEnum::DE_2D:
			{
				if (_gPlayMap2D.find((EChromaSDKDevice2DEnum)deviceId) != _gPlayMap2D.end())
				{
					int prevAnimation = _gPlayMap2D[(EChromaSDKDevice2DEnum)deviceId];
					if (prevAnimation != -1)
					{
						PluginStopAnimation(prevAnimation);
						_gPlayMap2D[(EChromaSDKDevice2DEnum)deviceId] = -1;
					}
				}
			}
			break;
		}
	}

	EXPORT_API double PluginStopAnimationTypeD(double deviceType, double device)
	{
		PluginStopAnimationType((int)deviceType, (int)device);
		return 0;
	}

	EXPORT_API bool PluginIsPlayingName(const char* path)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginIsPlayingName: Animation not found! %s\r\n", path);
			return false;
		}
		return PluginIsPlaying(animationId);
	}

	EXPORT_API double PluginIsPlayingNameD(const char* path)
	{
		if (PluginIsPlayingName(path))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}

	EXPORT_API bool PluginIsPlayingType(int deviceType, int device)
	{
		switch ((EChromaSDKDeviceTypeEnum)deviceType)
		{
		case EChromaSDKDeviceTypeEnum::DE_1D:
			{
				if (_gPlayMap1D.find((EChromaSDKDevice1DEnum)device) != _gPlayMap1D.end())
				{
					int prevAnimation = _gPlayMap1D[(EChromaSDKDevice1DEnum)device];
					if (prevAnimation != -1)
					{
						return PluginIsPlaying(prevAnimation);
					}
				}
			}
			break;
		case EChromaSDKDeviceTypeEnum::DE_2D:
			{
				if (_gPlayMap2D.find((EChromaSDKDevice2DEnum)device) != _gPlayMap2D.end())
				{
					int prevAnimation = _gPlayMap2D[(EChromaSDKDevice2DEnum)device];
					if (prevAnimation != -1)
					{
						return PluginIsPlaying(prevAnimation);
					}
				}
			}
			break;
		}
		return false;
	}

	EXPORT_API double PluginIsPlayingTypeD(double deviceType, double device)
	{
		if (PluginIsPlayingType((int)deviceType, (int)device))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}

	EXPORT_API void PluginLoadComposite(const char* name)
	{
		string baseName = name;
		PluginLoadAnimationName((baseName + "_ChromaLink.chroma").c_str());
		PluginLoadAnimationName((baseName + "_Headset.chroma").c_str());
		PluginLoadAnimationName((baseName + "_Keyboard.chroma").c_str());
		PluginLoadAnimationName((baseName + "_Keypad.chroma").c_str());
		PluginLoadAnimationName((baseName + "_Mouse.chroma").c_str());
		PluginLoadAnimationName((baseName + "_Mousepad.chroma").c_str());
	}

	EXPORT_API void PluginUnloadComposite(const char* name)
	{
		string baseName = name;
		PluginUnloadAnimationName((baseName + "_ChromaLink.chroma").c_str());
		PluginUnloadAnimationName((baseName + "_Headset.chroma").c_str());
		PluginUnloadAnimationName((baseName + "_Keyboard.chroma").c_str());
		PluginUnloadAnimationName((baseName + "_KeyboardExtended.chroma").c_str());
		PluginUnloadAnimationName((baseName + "_Keypad.chroma").c_str());
		PluginUnloadAnimationName((baseName + "_Mouse.chroma").c_str());
		PluginUnloadAnimationName((baseName + "_Mousepad.chroma").c_str());
	}

	EXPORT_API void PluginPlayComposite(const char* name, bool loop)
	{
		string baseName = name;
		PluginPlayAnimationName((baseName + "_ChromaLink.chroma").c_str(), loop);
		PluginPlayAnimationName((baseName + "_Headset.chroma").c_str(), loop);
		PluginPlayAnimationName((baseName + "_Keyboard.chroma").c_str(), loop);
		PluginPlayAnimationName((baseName + "_KeyboardExtended.chroma").c_str(), loop);
		PluginPlayAnimationName((baseName + "_Keypad.chroma").c_str(), loop);
		PluginPlayAnimationName((baseName + "_Mouse.chroma").c_str(), loop);
		PluginPlayAnimationName((baseName + "_Mousepad.chroma").c_str(), loop);
	}

	EXPORT_API double PluginPlayCompositeD(const char* name, double loop)
	{
		if (loop == 0)
		{
			PluginPlayComposite(name, false);
		}
		else
		{
			PluginPlayComposite(name, true);
		}
		return 0;
	}

	EXPORT_API void PluginStopComposite(const char* name)
	{
		string baseName = name;
		PluginStopAnimationName((baseName + "_ChromaLink.chroma").c_str());
		PluginStopAnimationName((baseName + "_Headset.chroma").c_str());
		PluginStopAnimationName((baseName + "_Keyboard.chroma").c_str());
		PluginStopAnimationName((baseName + "_Keypad.chroma").c_str());
		PluginStopAnimationName((baseName + "_Mouse.chroma").c_str());
		PluginStopAnimationName((baseName + "_Mousepad.chroma").c_str());
	}

	EXPORT_API double PluginStopCompositeD(const char* name)
	{
		PluginStopComposite(name);
		return 0;
	}

	EXPORT_API void PluginCloseComposite(const char* name)
	{
		string baseName = name;
		PluginCloseAnimationName((baseName + "_ChromaLink.chroma").c_str());
		PluginCloseAnimationName((baseName + "_Headset.chroma").c_str());
		PluginCloseAnimationName((baseName + "_Keyboard.chroma").c_str());
		PluginCloseAnimationName((baseName + "_Keypad.chroma").c_str());
		PluginCloseAnimationName((baseName + "_Mouse.chroma").c_str());
		PluginCloseAnimationName((baseName + "_Mousepad.chroma").c_str());
	}

	EXPORT_API double PluginCloseCompositeD(const char* name)
	{
		PluginCloseComposite(name);
		return 0;
	}

	EXPORT_API int PluginGetKeyColor(int animationId, int frameId, int rzkey)
	{
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return 0;
		}
		if (animation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_2D &&
			animation->GetDeviceId() == (int)EChromaSDKDevice2DEnum::DE_Keyboard)
		{
			Animation2D* animation2D = (Animation2D*)(animation);
			vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
			if (frameId >= 0 &&
				frameId < int(frames.size()))
			{
				FChromaSDKColorFrame2D& frame = frames[frameId];
				return frame.Colors[HIBYTE(rzkey)].Colors[LOBYTE(rzkey)];
			}
		}
		return 0;
	}

	EXPORT_API int PluginGetKeyColorName(const char* path, int frameId, int rzkey)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginGetKeyColorName: Animation not found! %s\r\n", path);
			return 0;
		}
		return PluginGetKeyColor(animationId, frameId, rzkey);
	}

	EXPORT_API double PluginGetKeyColorD(const char* path, double frameId, double rzkey)
	{
		return (double)PluginGetKeyColorName(path, (int)frameId, (int)rzkey);
	}

	EXPORT_API int PluginGet1DColor(int animationId, int frameId, int led)
	{
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return 0;
		}
		if (animation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_1D)
		{
			Animation1D* animation1D = (Animation1D*)(animation);
			vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
			if (frameId >= 0 &&
				frameId < int(frames.size()))
			{
				FChromaSDKColorFrame1D& frame = frames[frameId];
				if (led >= 0 &&
					led < int(frame.Colors.size()))
				{
					return frame.Colors[led];
				}
			}
		}
		return 0;
	}

	EXPORT_API int PluginGet1DColorName(const char* path, int frameId, int index)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginGet1DColorName: Animation not found! %s\r\n", path);
			return 0;
		}
		return PluginGet1DColor(animationId, frameId, index);
	}

	EXPORT_API double PluginGet1DColorNameD(const char* path, double frameId, double index)
	{
		return (double)PluginGet1DColorName(path, (int)frameId, (int)index);
	}

	EXPORT_API int PluginGet2DColor(int animationId, int frameId, int row, int column)
	{
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return 0;
		}
		if (animation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_2D)
		{
			Animation2D* animation2D = (Animation2D*)(animation);
			vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
			if (frameId >= 0 &&
				frameId < int(frames.size()))
			{
				FChromaSDKColorFrame2D& frame = frames[frameId];
				if (row >= 0 &&
					row < int(frame.Colors.size()))
				{
					FChromaSDKColors& items = frame.Colors[row];
					if (column >= 0 &&
						column < int(items.Colors.size()))
					{
						return items.Colors[column];
					}
				}
			}
		}
		return 0;
	}

	EXPORT_API int PluginGet2DColorName(const char* path, int frameId, int row, int column)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginGet2DColorName: Animation not found! %s\r\n", path);
			return 0;
		}
		return PluginGet2DColor(animationId, frameId, row, column);
	}

	EXPORT_API double PluginGet2DColorNameD(const char* path, double frameId, double row, double column)
	{
		return (double)PluginGet2DColorName(path, (int)frameId, (int)row, (int)column);
	}


	EXPORT_API void PluginSetKeyColor(int animationId, int frameId, int rzkey, int color)
	{
		PluginStopAnimation(animationId);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		if (animation->GetDeviceType() != EChromaSDKDeviceTypeEnum::DE_2D)
		{
			return;
		}

		switch (animation->GetDeviceId())
		{
		case (int)EChromaSDKDevice2DEnum::DE_Keyboard:
		case (int)EChromaSDKDevice2DEnum::DE_KeyboardExtended:
			break;
		default:
			return;
		}

		int customFlag = 1 << 24;
		int keyColor = color | customFlag;

		Animation2D* animation2D = (Animation2D*)(animation);
		vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
		if (frameId >= 0 &&
			frameId < int(frames.size()))
		{
			FChromaSDKColorFrame2D& frame = frames[frameId];
			frame.Keys[HIBYTE(rzkey)].Colors[LOBYTE(rzkey)] = keyColor;
		}
	}

	EXPORT_API void PluginSetKeyColorName(const char* path, int frameId, int rzkey, int color)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginSetKeyColorName: Animation not found! %s\r\n", path);
			return;
		}
		PluginSetKeyColor(animationId, frameId, rzkey, color);
	}

	EXPORT_API void PluginSetKeyRowColumnColorName(const char* path, int frameId, int row, int column, int color)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginSetKeyColorName: Animation not found! %s\r\n", path);
			return;
		}
		int rzkey = (row << 8) | column;
		PluginSetKeyColor(animationId, frameId, rzkey, color);
	}

	EXPORT_API double PluginSetKeyColorNameD(const char* path, double frameId, double rzkey, double color)
	{
		PluginSetKeyColorName(path, (int)frameId, (int)rzkey, (int)color);
		return 0;
	}


	EXPORT_API void PluginSetKeyColorRGB(int animationId, int frameId, int rzkey, int red, int green, int blue)
	{
		PluginStopAnimation(animationId);
		int color = PluginGetRGB(red, green, blue);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		if (animation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_2D &&
			animation->GetDeviceId() == (int)EChromaSDKDevice2DEnum::DE_Keyboard)
		{
			Animation2D* animation2D = (Animation2D*)(animation);
			vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
			if (frameId >= 0 &&
				frameId < int(frames.size()))
			{
				FChromaSDKColorFrame2D& frame = frames[frameId];
				frame.Colors[HIBYTE(rzkey)].Colors[LOBYTE(rzkey)] = color;
			}
		}
	}

	EXPORT_API void PluginSetKeyColorRGBName(const char* path, int frameId, int rzkey, int red, int green, int blue)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginSetKeyColorRGBName: Animation not found! %s\r\n", path);
			return;
		}
		PluginSetKeyColorRGB(animationId, frameId, rzkey, red, green, blue);
	}

	EXPORT_API double PluginSetKeyColorRGBNameD(const char* path, double frameId, double rzkey, double red, double green, double blue)
	{
		PluginSetKeyColorRGBName(path, (int)frameId, (int)rzkey, (int)red, (int)green, (int)blue);
		return 0;
	}


	EXPORT_API void PluginSetKeyColorAllFrames(int animationId, int rzkey, int color)
	{
		PluginStopAnimation(animationId);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		if (animation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_2D)
		{
			switch (animation->GetDeviceId())
			{
			case (int)EChromaSDKDevice2DEnum::DE_Keyboard:
			case (int)EChromaSDKDevice2DEnum::DE_KeyboardExtended:
				{
					int customFlag = 1 << 24;
					int keyColor = color | customFlag;
					Animation2D* animation2D = (Animation2D*)(animation);
					vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
					for (int frameId = 0; frameId < int(frames.size()); ++frameId)
					{
						FChromaSDKColorFrame2D& frame = frames[frameId];
						frame.Keys[HIBYTE(rzkey)].Colors[LOBYTE(rzkey)] = keyColor;
					}
				}
				break;
			}
		}
	}

	EXPORT_API void PluginSetKeyColorAllFramesName(const char* path, int rzkey, int color)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginSetKeyColorAllFramesName: Animation not found! %s\r\n", path);
			return;
		}
		PluginSetKeyColorAllFrames(animationId, rzkey, color);
	}

	EXPORT_API double PluginSetKeyColorAllFramesNameD(const char* path, double rzkey, double color)
	{
		PluginSetKeyColorAllFramesName(path, (int)rzkey, (int)color);
		return 0;
	}


	EXPORT_API void PluginSetKeyColorAllFramesRGB(int animationId, int rzkey, int red, int green, int blue)
	{
		PluginStopAnimation(animationId);
		int color = PluginGetRGB(red, green, blue);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		if (animation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_2D &&
			animation->GetDeviceId() == (int)EChromaSDKDevice2DEnum::DE_Keyboard)
		{
			Animation2D* animation2D = (Animation2D*)(animation);
			vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
			for (int frameId = 0; frameId < int(frames.size()); ++frameId)
			{
				FChromaSDKColorFrame2D& frame = frames[frameId];
				frame.Colors[HIBYTE(rzkey)].Colors[LOBYTE(rzkey)] = color;
			}
		}
	}

	EXPORT_API void PluginSetKeyColorAllFramesRGBName(const char* path, int rzkey, int red, int green, int blue)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginSetKeyColorAllFramesRGBName: Animation not found! %s\r\n", path);
			return;
		}
		PluginSetKeyColorAllFramesRGB(animationId, rzkey, red, green, blue);
	}

	EXPORT_API double PluginSetKeyColorAllFramesRGBNameD(const char* path, double rzkey, double red, double green, double blue)
	{
		PluginSetKeyColorAllFramesRGBName(path, (int)rzkey, (int)red, (int)green, (int)blue);
		return 0;
	}


	EXPORT_API void PluginSetKeysColor(int animationId, int frameId, const int* rzkeys, int keyCount, int color)
	{
		PluginStopAnimation(animationId);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		if (animation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_2D)
		{
			switch (animation->GetDeviceId())
			{
			case (int)EChromaSDKDevice2DEnum::DE_Keyboard:
			case (int)EChromaSDKDevice2DEnum::DE_KeyboardExtended:
				{
					int customFlag = 1 << 24;
					int keyColor = color | customFlag;
					Animation2D* animation2D = (Animation2D*)(animation);
					vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
					if (frameId >= 0 &&
						frameId < int(frames.size()))
					{
						FChromaSDKColorFrame2D& frame = frames[frameId];
						for (int index = 0; index < keyCount; ++index)
						{
							const int* rzkey = &rzkeys[index];
							frame.Keys[HIBYTE(*rzkey)].Colors[LOBYTE(*rzkey)] = keyColor;
						}
					}
				}
				break;
			}
		}
	}

	EXPORT_API void PluginSetKeysColorName(const char* path, int frameId, const int* rzkeys, int keyCount, int color)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginSetKeyColorName: Animation not found! %s\r\n", path);
			return;
		}
		PluginSetKeysColor(animationId, frameId, rzkeys, keyCount, color);
	}


	EXPORT_API void PluginSetKeysColorRGB(int animationId, int frameId, const int* rzkeys, int keyCount, int red, int green, int blue)
	{
		PluginStopAnimation(animationId);
		int color = PluginGetRGB(red, green, blue);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		if (animation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_2D &&
			animation->GetDeviceId() == (int)EChromaSDKDevice2DEnum::DE_Keyboard)
		{
			Animation2D* animation2D = (Animation2D*)(animation);
			vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
			if (frameId >= 0 &&
				frameId < int(frames.size()))
			{
				for (int index = 0; index < keyCount; ++index)
				{
					const int* rzkey = &rzkeys[index];
					FChromaSDKColorFrame2D& frame = frames[frameId];
					frame.Colors[HIBYTE(*rzkey)].Colors[LOBYTE(*rzkey)] = color;
				}
			}
		}
	}

	EXPORT_API void PluginSetKeysColorRGBName(const char* path, int frameId, const int* rzkeys, int keyCount, int red, int green, int blue)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginSetKeyColorRGBName: Animation not found! %s\r\n", path);
			return;
		}
		PluginSetKeysColorRGB(animationId, frameId, rzkeys, keyCount, red, green, blue);
	}


	EXPORT_API void PluginSetKeysColorAllFrames(int animationId, const int* rzkeys, int keyCount, int color)
	{
		PluginStopAnimation(animationId);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		if (animation->GetDeviceType() != EChromaSDKDeviceTypeEnum::DE_2D)
		{
			return;
		}

		switch (animation->GetDeviceId())
		{
		case (int)EChromaSDKDevice2DEnum::DE_Keyboard:
		case (int)EChromaSDKDevice2DEnum::DE_KeyboardExtended:
			break;
		default:
			return;
		}

		int customFlag = 1 << 24;
		int keyColor = color | customFlag;

		Animation2D* animation2D = (Animation2D*)(animation);
		vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
		for (int frameId = 0; frameId < int(frames.size()); ++frameId)
		{
			FChromaSDKColorFrame2D& frame = frames[frameId];
			for (int index = 0; index < keyCount; ++index)
			{
				const int* rzkey = &rzkeys[index];
				frame.Keys[HIBYTE(*rzkey)].Colors[LOBYTE(*rzkey)] = keyColor;
			}
		}
	}

	EXPORT_API void PluginSetKeysColorAllFramesName(const char* path, const int* rzkeys, int keyCount, int color)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginSetKeysColorAllFramesName: Animation not found! %s\r\n", path);
			return;
		}
		PluginSetKeysColorAllFrames(animationId, rzkeys, keyCount, color);
	}


	EXPORT_API void PluginSetKeysColorAllFramesRGB(int animationId, const int* rzkeys, int keyCount, int red, int green, int blue)
	{
		PluginStopAnimation(animationId);
		int color = PluginGetRGB(red, green, blue);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		if (animation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_2D &&
			animation->GetDeviceId() == (int)EChromaSDKDevice2DEnum::DE_Keyboard)
		{
			Animation2D* animation2D = (Animation2D*)(animation);
			vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
			for (int frameId = 0; frameId < int(frames.size()); ++frameId)
			{
				for (int index = 0; index < keyCount; ++index)
				{
					const int* rzkey = &rzkeys[index];
					FChromaSDKColorFrame2D& frame = frames[frameId];
					frame.Colors[HIBYTE(*rzkey)].Colors[LOBYTE(*rzkey)] = color;
				}
			}
		}
	}

	EXPORT_API void PluginSetKeysColorAllFramesRGBName(const char* path, const int* rzkeys, int keyCount, int red, int green, int blue)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginSetKeysColorAllFramesRGBName: Animation not found! %s\r\n", path);
			return;
		}
		PluginSetKeysColorAllFramesRGB(animationId, rzkeys, keyCount, red, green, blue);
	}


	EXPORT_API void PluginSetKeyNonZeroColor(int animationId, int frameId, int rzkey, int color)
	{
		PluginStopAnimation(animationId);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		if (animation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_2D &&
			animation->GetDeviceId() == (int)EChromaSDKDevice2DEnum::DE_Keyboard)
		{
			Animation2D* animation2D = (Animation2D*)(animation);
			vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
			if (frameId >= 0 &&
				frameId < int(frames.size()))
			{
				FChromaSDKColorFrame2D& frame = frames[frameId];
				if (frame.Colors[HIBYTE(rzkey)].Colors[LOBYTE(rzkey)] != 0)
				{
					frame.Colors[HIBYTE(rzkey)].Colors[LOBYTE(rzkey)] = color;
				}
			}
		}
	}

	EXPORT_API void PluginSetKeyNonZeroColorName(const char* path, int frameId, int rzkey, int color)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginSetKeyNonZeroColorName: Animation not found! %s\r\n", path);
			return;
		}
		PluginSetKeyNonZeroColor(animationId, frameId, rzkey, color);
	}

	EXPORT_API double PluginSetKeyNonZeroColorNameD(const char* path, double frameId, double rzkey, double color)
	{
		PluginSetKeyNonZeroColorName(path, (int)frameId, (int)rzkey, (int)color);
		return 0;
	}


	EXPORT_API void PluginSetKeyNonZeroColorRGB(int animationId, int frameId, int rzkey, int red, int green, int blue)
	{
		PluginStopAnimation(animationId);
		int color = PluginGetRGB(red, green, blue);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		if (animation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_2D &&
			animation->GetDeviceId() == (int)EChromaSDKDevice2DEnum::DE_Keyboard)
		{
			Animation2D* animation2D = (Animation2D*)(animation);
			vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
			if (frameId >= 0 &&
				frameId < int(frames.size()))
			{
				FChromaSDKColorFrame2D& frame = frames[frameId];
				if (frame.Colors[HIBYTE(rzkey)].Colors[LOBYTE(rzkey)] != 0)
				{
					frame.Colors[HIBYTE(rzkey)].Colors[LOBYTE(rzkey)] = color;
				}
			}
		}
	}

	EXPORT_API void PluginSetKeyNonZeroColorRGBName(const char* path, int frameId, int rzkey, int red, int green, int blue)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginSetKeyNonZeroColorRGBName: Animation not found! %s\r\n", path);
			return;
		}
		PluginSetKeyNonZeroColorRGB(animationId, frameId, rzkey, red, green, blue);
	}

	EXPORT_API double PluginSetKeyNonZeroColorRGBNameD(const char* path, double frameId, double rzkey, double red, double green, double blue)
	{
		PluginSetKeyNonZeroColorRGBName(path, (int)frameId, (int)rzkey, (int)red, (int)green, (int)blue);
		return 0;
	}


	EXPORT_API void PluginSetKeyZeroColor(int animationId, int frameId, int rzkey, int color)
	{
		PluginStopAnimation(animationId);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		if (animation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_2D &&
			animation->GetDeviceId() == (int)EChromaSDKDevice2DEnum::DE_Keyboard)
		{
			Animation2D* animation2D = (Animation2D*)(animation);
			vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
			if (frameId >= 0 &&
				frameId < int(frames.size()))
			{
				FChromaSDKColorFrame2D& frame = frames[frameId];
				if (frame.Colors[HIBYTE(rzkey)].Colors[LOBYTE(rzkey)] == 0)
				{
					frame.Colors[HIBYTE(rzkey)].Colors[LOBYTE(rzkey)] = color;
				}
			}
		}
	}

	EXPORT_API void PluginSetKeyZeroColorName(const char* path, int frameId, int rzkey, int color)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginSetKeyZeroColorName: Animation not found! %s\r\n", path);
			return;
		}
		PluginSetKeyZeroColor(animationId, frameId, rzkey, color);
	}

	EXPORT_API double PluginSetKeyZeroColorNameD(const char* path, double frameId, double rzkey, double color)
	{
		PluginSetKeyZeroColorName(path, (int)frameId, (int)rzkey, (int)color);
		return 0;
	}


	EXPORT_API void PluginSetKeyZeroColorRGB(int animationId, int frameId, int rzkey, int red, int green, int blue)
	{
		PluginStopAnimation(animationId);
		int color = PluginGetRGB(red, green, blue);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		if (animation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_2D &&
			animation->GetDeviceId() == (int)EChromaSDKDevice2DEnum::DE_Keyboard)
		{
			Animation2D* animation2D = (Animation2D*)(animation);
			vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
			if (frameId >= 0 &&
				frameId < int(frames.size()))
			{
				FChromaSDKColorFrame2D& frame = frames[frameId];
				if (frame.Colors[HIBYTE(rzkey)].Colors[LOBYTE(rzkey)] == 0)
				{
					frame.Colors[HIBYTE(rzkey)].Colors[LOBYTE(rzkey)] = color;
				}
			}
		}
	}

	EXPORT_API void PluginSetKeyZeroColorRGBName(const char* path, int frameId, int rzkey, int red, int green, int blue)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginSetKeyZeroColorRGBName: Animation not found! %s\r\n", path);
			return;
		}
		PluginSetKeyZeroColorRGB(animationId, frameId, rzkey, red, green, blue);
	}

	EXPORT_API double PluginSetKeyZeroColorRGBNameD(const char* path, double frameId, double rzkey, double red, double green, double blue)
	{
		PluginSetKeyZeroColorRGBName(path, (int)frameId, (int)rzkey, (int)red, (int)green, (int)blue);
		return 0;
	}


	EXPORT_API void PluginSetKeysNonZeroColor(int animationId, int frameId, const int* rzkeys, int keyCount, int color)
	{
		PluginStopAnimation(animationId);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		if (animation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_2D &&
			animation->GetDeviceId() == (int)EChromaSDKDevice2DEnum::DE_Keyboard)
		{
			Animation2D* animation2D = (Animation2D*)(animation);
			vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
			if (frameId >= 0 &&
				frameId < int(frames.size()))
			{
				for (int index = 0; index < keyCount; ++index)
				{
					const int* rzkey = &rzkeys[index];
					FChromaSDKColorFrame2D& frame = frames[frameId];
					if (frame.Colors[HIBYTE(*rzkey)].Colors[LOBYTE(*rzkey)] != 0)
					{
						frame.Colors[HIBYTE(*rzkey)].Colors[LOBYTE(*rzkey)] = color;
					}
				}
			}
		}
	}

	EXPORT_API void PluginSetKeysNonZeroColorName(const char* path, int frameId, const int* rzkeys, int keyCount, int color)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginSetKeyNonZeroColorName: Animation not found! %s\r\n", path);
			return;
		}
		PluginSetKeysNonZeroColor(animationId, frameId, rzkeys, keyCount, color);
	}


	EXPORT_API void PluginSetKeysNonZeroColorRGB(int animationId, int frameId, const int* rzkeys, int keyCount, int red, int green, int blue)
	{
		PluginStopAnimation(animationId);
		int color = PluginGetRGB(red, green, blue);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		if (animation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_2D &&
			animation->GetDeviceId() == (int)EChromaSDKDevice2DEnum::DE_Keyboard)
		{
			Animation2D* animation2D = (Animation2D*)(animation);
			vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
			if (frameId >= 0 &&
				frameId < int(frames.size()))
			{
				for (int index = 0; index < keyCount; ++index)
				{
					const int* rzkey = &rzkeys[index];
					FChromaSDKColorFrame2D& frame = frames[frameId];
					if (frame.Colors[HIBYTE(*rzkey)].Colors[LOBYTE(*rzkey)] != 0)
					{
						frame.Colors[HIBYTE(*rzkey)].Colors[LOBYTE(*rzkey)] = color;
					}
				}
			}
		}
	}

	EXPORT_API void PluginSetKeysNonZeroColorRGBName(const char* path, int frameId, const int* rzkeys, int keyCount, int red, int green, int blue)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginSetKeyNonZeroColorRGBName: Animation not found! %s\r\n", path);
			return;
		}
		PluginSetKeysNonZeroColorRGB(animationId, frameId, rzkeys, keyCount, red, green, blue);
	}


	EXPORT_API void PluginSetKeysZeroColor(int animationId, int frameId, const int* rzkeys, int keyCount, int color)
	{
		PluginStopAnimation(animationId);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		if (animation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_2D &&
			animation->GetDeviceId() == (int)EChromaSDKDevice2DEnum::DE_Keyboard)
		{
			Animation2D* animation2D = (Animation2D*)(animation);
			vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
			if (frameId >= 0 &&
				frameId < int(frames.size()))
			{
				for (int index = 0; index < keyCount; ++index)
				{
					const int* rzkey = &rzkeys[index];
					FChromaSDKColorFrame2D& frame = frames[frameId];
					if (frame.Colors[HIBYTE(*rzkey)].Colors[LOBYTE(*rzkey)] == 0)
					{
						frame.Colors[HIBYTE(*rzkey)].Colors[LOBYTE(*rzkey)] = color;
					}
				}
			}
		}
	}

	EXPORT_API void PluginSetKeysZeroColorName(const char* path, int frameId, const int* rzkeys, int keyCount, int color)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginSetKeyZeroColorName: Animation not found! %s\r\n", path);
			return;
		}
		PluginSetKeysZeroColor(animationId, frameId, rzkeys, keyCount, color);
	}


	EXPORT_API void PluginSetKeysZeroColorRGB(int animationId, int frameId, const int* rzkeys, int keyCount, int red, int green, int blue)
	{
		PluginStopAnimation(animationId);
		int color = PluginGetRGB(red, green, blue);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		if (animation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_2D &&
			animation->GetDeviceId() == (int)EChromaSDKDevice2DEnum::DE_Keyboard)
		{
			Animation2D* animation2D = (Animation2D*)(animation);
			vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
			if (frameId >= 0 &&
				frameId < int(frames.size()))
			{
				for (int index = 0; index < keyCount; ++index)
				{
					const int* rzkey = &rzkeys[index];
					FChromaSDKColorFrame2D& frame = frames[frameId];
					if (frame.Colors[HIBYTE(*rzkey)].Colors[LOBYTE(*rzkey)] == 0)
					{
						frame.Colors[HIBYTE(*rzkey)].Colors[LOBYTE(*rzkey)] = color;
					}
				}
			}
		}
	}

	EXPORT_API void PluginSetKeysZeroColorRGBName(const char* path, int frameId, const int* rzkeys, int keyCount, int red, int green, int blue)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginSetKeyZeroColorName: Animation not found! %s\r\n", path);
			return;
		}
		PluginSetKeysZeroColorRGB(animationId, frameId, rzkeys, keyCount, red, green, blue);
	}


	EXPORT_API void PluginSetKeysNonZeroColorAllFrames(int animationId, const int* rzkeys, int keyCount, int color)
	{
		PluginStopAnimation(animationId);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		if (animation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_2D &&
			animation->GetDeviceId() == (int)EChromaSDKDevice2DEnum::DE_Keyboard)
		{
			Animation2D* animation2D = (Animation2D*)(animation);
			vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
			for (int frameId = 0; frameId < int(frames.size()); ++frameId)
			{
				for (int index = 0; index < keyCount; ++index)
				{
					const int* rzkey = &rzkeys[index];
					FChromaSDKColorFrame2D& frame = frames[frameId];
					if (frame.Colors[HIBYTE(*rzkey)].Colors[LOBYTE(*rzkey)] != 0)
					{
						frame.Colors[HIBYTE(*rzkey)].Colors[LOBYTE(*rzkey)] = color;
					}
				}
			}
		}
	}

	EXPORT_API void PluginSetKeysNonZeroColorAllFramesName(const char* path, const int* rzkeys, int keyCount, int color)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginSetKeysNonZeroColorAllFramesName: Animation not found! %s\r\n", path);
			return;
		}
		PluginSetKeysNonZeroColorAllFrames(animationId, rzkeys, keyCount, color);
	}


	EXPORT_API void PluginSetKeysZeroColorAllFrames(int animationId, const int* rzkeys, int keyCount, int color)
	{
		PluginStopAnimation(animationId);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		if (animation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_2D &&
			animation->GetDeviceId() == (int)EChromaSDKDevice2DEnum::DE_Keyboard)
		{
			Animation2D* animation2D = (Animation2D*)(animation);
			vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
			for (int frameId = 0; frameId < int(frames.size()); ++frameId)
			{
				for (int index = 0; index < keyCount; ++index)
				{
					const int* rzkey = &rzkeys[index];
					FChromaSDKColorFrame2D& frame = frames[frameId];
					if (frame.Colors[HIBYTE(*rzkey)].Colors[LOBYTE(*rzkey)] == 0)
					{
						frame.Colors[HIBYTE(*rzkey)].Colors[LOBYTE(*rzkey)] = color;
					}
				}
			}
		}
	}

	EXPORT_API void PluginSetKeysZeroColorAllFramesName(const char* path, const int* rzkeys, int keyCount, int color)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginSetKeysZeroColorAllFramesName: Animation not found! %s\r\n", path);
			return;
		}
		PluginSetKeysZeroColorAllFrames(animationId, rzkeys, keyCount, color);
	}


	EXPORT_API void PluginSetKeysZeroColorAllFramesRGB(int animationId, const int* rzkeys, int keyCount, int red, int green, int blue)
	{
		PluginStopAnimation(animationId);
		int color = PluginGetRGB(red, green, blue);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		if (animation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_2D &&
			animation->GetDeviceId() == (int)EChromaSDKDevice2DEnum::DE_Keyboard)
		{
			Animation2D* animation2D = (Animation2D*)(animation);
			vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
			for (int frameId = 0; frameId < int(frames.size()); ++frameId)
			{
				for (int index = 0; index < keyCount; ++index)
				{
					const int* rzkey = &rzkeys[index];
					FChromaSDKColorFrame2D& frame = frames[frameId];
					if (frame.Colors[HIBYTE(*rzkey)].Colors[LOBYTE(*rzkey)] == 0)
					{
						frame.Colors[HIBYTE(*rzkey)].Colors[LOBYTE(*rzkey)] = color;
					}
				}
			}
		}
	}

	EXPORT_API void PluginSetKeysZeroColorAllFramesRGBName(const char* path, const int* rzkeys, int keyCount, int red, int green, int blue)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginSetKeysZeroColorAllFramesRGBName: Animation not found! %s\r\n", path);
			return;
		}
		PluginSetKeysZeroColorAllFramesRGB(animationId, rzkeys, keyCount, red, green, blue);
	}


	EXPORT_API void PluginSet1DColor(int animationId, int frameId, int led, int color)
	{
		PluginStopAnimation(animationId);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		if (animation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_1D)
		{
			Animation1D* animation1D = (Animation1D*)(animation);
			vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
			if (frameId >= 0 &&
				frameId < int(frames.size()))
			{
				FChromaSDKColorFrame1D& frame = frames[frameId];
				if (led >= 0 &&
					led < int(frame.Colors.size()))
				{
					frame.Colors[led] = color;
				}
			}
		}
	}

	EXPORT_API void PluginSet1DColorName(const char* path, int frameId, int index, int color)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginSet1DColorName: Animation not found! %s\r\n", path);
			return;
		}
		PluginSet1DColor(animationId, frameId, index, color);
	}

	EXPORT_API double PluginSet1DColorNameD(const char* path, double frameId, double index, double color)
	{
		PluginSet1DColorName(path, (int)frameId, (int)index, (int)color);
		return 0;
	}

	EXPORT_API void PluginSet2DColor(int animationId, int frameId, int row, int column, int color)
	{
		PluginStopAnimation(animationId);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		if (animation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_2D)
		{
			Animation2D* animation2D = (Animation2D*)(animation);
			vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
			if (frameId >= 0 &&
				frameId < int(frames.size()))
			{
				FChromaSDKColorFrame2D& frame = frames[frameId];
				if (row >= 0 &&
					row < int(frame.Colors.size()))
				{
					FChromaSDKColors& items = frame.Colors[row];
					if (column >= 0 &&
						column < int(items.Colors.size()))
					{
						items.Colors[column] = color;
					}
				}
			}
		}
	}

	EXPORT_API void PluginSet2DColorName(const char* path, int frameId, int row, int column, int color)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginSet2DColorName: Animation not found! %s\r\n", path);
			return;
		}
		PluginSet2DColor(animationId, frameId, row, column, color);
	}

	// GMS only allows 4 params when string datatype is used
	EXPORT_API double PluginSet2DColorNameD(const char* path, double frameId, double rowColumnIndex, double color)
	{
		int device = PluginGetDeviceName(path);
		if (device == -1)
		{
			return 0;
		}
		int maxColumn = PluginGetMaxColumn(device);
		int index = (int)rowColumnIndex;
		int row = index / maxColumn;
		int column = index - (row * maxColumn);
		PluginSet2DColorName(path, (int)frameId, row, column, (int)color);
		return 0;
	}


	EXPORT_API void PluginCopyKeyColor(int sourceAnimationId, int targetAnimationId, int frameId, int rzkey)
	{
		PluginStopAnimation(targetAnimationId);
		AnimationBase* sourceAnimation = GetAnimationInstance(sourceAnimationId);
		if (nullptr == sourceAnimation)
		{
			return;
		}
		AnimationBase* targetAnimation = GetAnimationInstance(targetAnimationId);
		if (nullptr == targetAnimation)
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() != EChromaSDKDeviceTypeEnum::DE_2D ||
			sourceAnimation->GetDeviceId() != (int)EChromaSDKDevice2DEnum::DE_Keyboard)
		{
			return;
		}
		if (targetAnimation->GetDeviceType() != EChromaSDKDeviceTypeEnum::DE_2D ||
			targetAnimation->GetDeviceId() != (int)EChromaSDKDevice2DEnum::DE_Keyboard)
		{
			return;
		}
		if (frameId < 0)
		{
			return;
		}
		Animation2D* sourceAnimation2D = (Animation2D*)(sourceAnimation);
		Animation2D* targetAnimation2D = (Animation2D*)(targetAnimation);
		vector<FChromaSDKColorFrame2D>& sourceFrames = sourceAnimation2D->GetFrames();
		vector<FChromaSDKColorFrame2D>& targetFrames = targetAnimation2D->GetFrames();
		if (sourceFrames.size() == 0)
		{
			return;
		}
		if (targetFrames.size() == 0)
		{
			return;
		}
		if (frameId < int(targetFrames.size()))
		{
			FChromaSDKColorFrame2D& sourceFrame = sourceFrames[frameId % sourceFrames.size()];
			FChromaSDKColorFrame2D& targetFrame = targetFrames[frameId];
			targetFrame.Colors[HIBYTE(rzkey)].Colors[LOBYTE(rzkey)] = sourceFrame.Colors[HIBYTE(rzkey)].Colors[LOBYTE(rzkey)];
		}
	}

	EXPORT_API void PluginCopyKeysColor(int sourceAnimationId, int targetAnimationId, int frameId, const int* keys, int size)
	{
		PluginStopAnimation(targetAnimationId);
		AnimationBase* sourceAnimation = GetAnimationInstance(sourceAnimationId);
		if (nullptr == sourceAnimation)
		{
			return;
		}
		AnimationBase* targetAnimation = GetAnimationInstance(targetAnimationId);
		if (nullptr == targetAnimation)
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() != EChromaSDKDeviceTypeEnum::DE_2D ||
			sourceAnimation->GetDeviceId() != (int)EChromaSDKDevice2DEnum::DE_Keyboard)
		{
			return;
		}
		if (targetAnimation->GetDeviceType() != EChromaSDKDeviceTypeEnum::DE_2D ||
			targetAnimation->GetDeviceId() != (int)EChromaSDKDevice2DEnum::DE_Keyboard)
		{
			return;
		}

		Animation2D* sourceAnimation2D = (Animation2D*)(sourceAnimation);
		vector<FChromaSDKColorFrame2D>& sourceFrames = sourceAnimation2D->GetFrames();
		if (frameId < 0 ||
			frameId >= (int)sourceFrames.size())
		{
			return;
		}

		Animation2D* targetAnimation2D = (Animation2D*)(targetAnimation);
		vector<FChromaSDKColorFrame2D>& targetFrames = targetAnimation2D->GetFrames();
		if (frameId < 0 ||
			frameId >= (int)targetFrames.size())
		{
			return;
		}

		FChromaSDKColorFrame2D& sourceFrame = sourceFrames[frameId];
		FChromaSDKColorFrame2D& targetFrame = targetFrames[frameId];
		for (int i = 0; i < size; ++i)
		{
			int rzkey = keys[i];
			targetFrame.Colors[HIBYTE(rzkey)].Colors[LOBYTE(rzkey)] = sourceFrame.Colors[HIBYTE(rzkey)].Colors[LOBYTE(rzkey)];
		}
	}
	EXPORT_API void PluginCopyKeysColorName(const char* sourceAnimation, const char* targetAnimation, int frameId, const int* keys, int size)
	{
		int sourceAnimationId = PluginGetAnimation(sourceAnimation);
		if (sourceAnimationId < 0)
		{
			LogError("PluginCopyKeysColorName: Source Animation not found! %s\r\n", sourceAnimation);
			return;
		}

		int targetAnimationId = PluginGetAnimation(targetAnimation);
		if (targetAnimationId < 0)
		{
			LogError("PluginCopyKeysColorName: Target Animation not found! %s\r\n", targetAnimation);
			return;
		}

		PluginCopyKeysColor(sourceAnimationId, targetAnimationId, frameId, keys, size);
	}

	EXPORT_API void PluginCopyKeysColorAllFrames(int sourceAnimationId, int targetAnimationId, const int* keys, int size)
	{
		PluginStopAnimation(targetAnimationId);
		AnimationBase* sourceAnimation = GetAnimationInstance(sourceAnimationId);
		if (nullptr == sourceAnimation)
		{
			return;
		}
		AnimationBase* targetAnimation = GetAnimationInstance(targetAnimationId);
		if (nullptr == targetAnimation)
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() != EChromaSDKDeviceTypeEnum::DE_2D ||
			sourceAnimation->GetDeviceId() != (int)EChromaSDKDevice2DEnum::DE_Keyboard)
		{
			return;
		}
		if (targetAnimation->GetDeviceType() != EChromaSDKDeviceTypeEnum::DE_2D ||
			targetAnimation->GetDeviceId() != (int)EChromaSDKDevice2DEnum::DE_Keyboard)
		{
			return;
		}

		Animation2D* sourceAnimation2D = (Animation2D*)(sourceAnimation);
		vector<FChromaSDKColorFrame2D>& sourceFrames = sourceAnimation2D->GetFrames();

		Animation2D* targetAnimation2D = (Animation2D*)(targetAnimation);
		vector<FChromaSDKColorFrame2D>& targetFrames = targetAnimation2D->GetFrames();

		int sourceFrameCount = sourceAnimation->GetFrameCount();
		int targetFrameCount = targetAnimation->GetFrameCount();
		for (int frameId = 0; frameId < sourceFrameCount && frameId < targetFrameCount; ++frameId)
		{
			FChromaSDKColorFrame2D& sourceFrame = sourceFrames[frameId];
			FChromaSDKColorFrame2D& targetFrame = targetFrames[frameId];

			for (int i = 0; i < size; ++i)
			{
				int rzkey = keys[i];
				targetFrame.Colors[HIBYTE(rzkey)].Colors[LOBYTE(rzkey)] = sourceFrame.Colors[HIBYTE(rzkey)].Colors[LOBYTE(rzkey)];
			}
		}
	}
	EXPORT_API void PluginCopyKeysColorAllFramesName(const char* sourceAnimation, const char* targetAnimation, const int* keys, int size)
	{
		int sourceAnimationId = PluginGetAnimation(sourceAnimation);
		if (sourceAnimationId < 0)
		{
			LogError("PluginCopyKeysColorAllFramesName: Source Animation not found! %s\r\n", sourceAnimation);
			return;
		}

		int targetAnimationId = PluginGetAnimation(targetAnimation);
		if (targetAnimationId < 0)
		{
			LogError("PluginCopyKeysColorAllFramesName: Target Animation not found! %s\r\n", targetAnimation);
			return;
		}

		PluginCopyKeysColorAllFrames(sourceAnimationId, targetAnimationId, keys, size);
	}

	EXPORT_API void PluginCopyKeysColorOffset(int sourceAnimationId, int targetAnimationId, int sourceFrameId, int targetFrameId, const int* keys, int size)
	{
		PluginStopAnimation(targetAnimationId);
		AnimationBase* sourceAnimation = GetAnimationInstance(sourceAnimationId);
		if (nullptr == sourceAnimation)
		{
			return;
		}
		AnimationBase* targetAnimation = GetAnimationInstance(targetAnimationId);
		if (nullptr == targetAnimation)
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() != EChromaSDKDeviceTypeEnum::DE_2D ||
			sourceAnimation->GetDeviceId() != (int)EChromaSDKDevice2DEnum::DE_Keyboard)
		{
			return;
		}
		if (targetAnimation->GetDeviceType() != EChromaSDKDeviceTypeEnum::DE_2D ||
			targetAnimation->GetDeviceId() != (int)EChromaSDKDevice2DEnum::DE_Keyboard)
		{
			return;
		}

		Animation2D* sourceAnimation2D = (Animation2D*)(sourceAnimation);
		vector<FChromaSDKColorFrame2D>& sourceFrames = sourceAnimation2D->GetFrames();
		if (sourceFrameId < 0 ||
			sourceFrameId >= (int)sourceFrames.size())
		{
			return;
		}

		Animation2D* targetAnimation2D = (Animation2D*)(targetAnimation);
		vector<FChromaSDKColorFrame2D>& targetFrames = targetAnimation2D->GetFrames();
		if (targetFrameId < 0 ||
			targetFrameId >= (int)targetFrames.size())
		{
			return;
		}

		FChromaSDKColorFrame2D& sourceFrame = sourceFrames[sourceFrameId];
		FChromaSDKColorFrame2D& targetFrame = targetFrames[targetFrameId];
		for (int i = 0; i < size; ++i)
		{
			int rzkey = keys[i];
			targetFrame.Colors[HIBYTE(rzkey)].Colors[LOBYTE(rzkey)] = sourceFrame.Colors[HIBYTE(rzkey)].Colors[LOBYTE(rzkey)];
		}
	}
	EXPORT_API void PluginCopyKeysColorOffsetName(const char* sourceAnimation, const char* targetAnimation, int sourceFrameId, int targetFrameId, const int* keys, int size)
	{
		int sourceAnimationId = PluginGetAnimation(sourceAnimation);
		if (sourceAnimationId < 0)
		{
			LogError("PluginCopyKeysColorOffsetName: Source Animation not found! %s\r\n", sourceAnimation);
			return;
		}

		int targetAnimationId = PluginGetAnimation(targetAnimation);
		if (targetAnimationId < 0)
		{
			LogError("PluginCopyKeysColorOffsetName: Target Animation not found! %s\r\n", targetAnimation);
			return;
		}

		PluginCopyKeysColorOffset(sourceAnimationId, targetAnimationId, sourceFrameId, targetFrameId, keys, size);
	}

	EXPORT_API void PluginCopyKeyColorName(const char* sourceAnimation, const char* targetAnimation, int frameId, int rzkey)
	{
		int sourceAnimationId = PluginGetAnimation(sourceAnimation);
		if (sourceAnimationId < 0)
		{
			LogError("PluginCopyKeyColorName: Source Animation not found! %s\r\n", sourceAnimation);
			return;
		}

		int targetAnimationId = PluginGetAnimation(targetAnimation);
		if (targetAnimationId < 0)
		{
			LogError("PluginCopyKeyColorName: Target Animation not found! %s\r\n", targetAnimation);
			return;
		}

		PluginCopyKeyColor(sourceAnimationId, targetAnimationId, frameId, rzkey);
	}

	EXPORT_API double PluginCopyKeyColorNameD(const char* sourceAnimation, const char* targetAnimation, double frameId, double rzkey)
	{
		PluginCopyKeyColorName(sourceAnimation, targetAnimation, (int)frameId, (int)rzkey);
		return 0;
	}


	EXPORT_API void PluginCopyKeyColorOffset(int sourceAnimationId, int targetAnimationId, int frameId, int rzkey, int offset)
	{
		PluginStopAnimation(targetAnimationId);
		AnimationBase* sourceAnimation = GetAnimationInstance(sourceAnimationId);
		if (nullptr == sourceAnimation)
		{
			return;
		}
		AnimationBase* targetAnimation = GetAnimationInstance(targetAnimationId);
		if (nullptr == targetAnimation)
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() != EChromaSDKDeviceTypeEnum::DE_2D ||
			sourceAnimation->GetDeviceId() != (int)EChromaSDKDevice2DEnum::DE_Keyboard)
		{
			return;
		}
		if (targetAnimation->GetDeviceType() != EChromaSDKDeviceTypeEnum::DE_2D ||
			targetAnimation->GetDeviceId() != (int)EChromaSDKDevice2DEnum::DE_Keyboard)
		{
			return;
		}
		if (frameId < 0)
		{
			return;
		}
		Animation2D* sourceAnimation2D = (Animation2D*)(sourceAnimation);
		Animation2D* targetAnimation2D = (Animation2D*)(targetAnimation);
		vector<FChromaSDKColorFrame2D>& sourceFrames = sourceAnimation2D->GetFrames();
		vector<FChromaSDKColorFrame2D>& targetFrames = targetAnimation2D->GetFrames();
		if (sourceFrames.size() == 0)
		{
			return;
		}
		if (targetFrames.size() == 0)
		{
			return;
		}
		if (frameId < int(sourceFrames.size()) &&
			(frameId + offset) < int(targetFrames.size()))
		{
			FChromaSDKColorFrame2D& sourceFrame = sourceFrames[frameId];
			FChromaSDKColorFrame2D& targetFrame = targetFrames[(frameId+offset)];
			targetFrame.Colors[HIBYTE(rzkey)].Colors[LOBYTE(rzkey)] = sourceFrame.Colors[HIBYTE(rzkey)].Colors[LOBYTE(rzkey)];
		}
	}


	EXPORT_API void PluginCopyKeyColorAllFrames(int sourceAnimationId, int targetAnimationId, int rzkey)
	{
		PluginStopAnimation(targetAnimationId);
		AnimationBase* sourceAnimation = GetAnimationInstance(sourceAnimationId);
		if (nullptr == sourceAnimation)
		{
			return;
		}
		AnimationBase* targetAnimation = GetAnimationInstance(targetAnimationId);
		if (nullptr == targetAnimation)
		{
			return;
		}
		int sourceFrameCount = sourceAnimation->GetFrameCount();
		int targetFrameCount = targetAnimation->GetFrameCount();
		for (int frameId = 0; frameId < sourceFrameCount && frameId < targetFrameCount; ++frameId)
		{
			PluginCopyKeyColor(sourceAnimationId, targetAnimationId, frameId, rzkey);
		}
	}

	EXPORT_API void PluginCopyKeyColorAllFramesName(const char* sourceAnimation, const char* targetAnimation, int rzkey)
	{
		int sourceAnimationId = PluginGetAnimation(sourceAnimation);
		if (sourceAnimationId < 0)
		{
			LogError("PluginCopyKeyColorAllFramesName: Source Animation not found! %s\r\n", sourceAnimation);
			return;
		}

		int targetAnimationId = PluginGetAnimation(targetAnimation);
		if (targetAnimationId < 0)
		{
			LogError("PluginCopyKeyColorAllFramesName: Target Animation not found! %s\r\n", targetAnimation);
			return;
		}

		PluginCopyKeyColorAllFrames(sourceAnimationId, targetAnimationId, rzkey);
	}

	EXPORT_API double PluginCopyKeyColorAllFramesNameD(const char* sourceAnimation, const char* targetAnimation, double rzkey)
	{
		PluginCopyKeyColorAllFramesName(sourceAnimation, targetAnimation, (int)rzkey);
		return 0;
	}


	EXPORT_API void PluginCopyKeyColorAllFramesOffset(int sourceAnimationId, int targetAnimationId, int rzkey, int offset)
	{
		PluginStopAnimation(targetAnimationId);
		AnimationBase* sourceAnimation = GetAnimationInstance(sourceAnimationId);
		if (nullptr == sourceAnimation)
		{
			return;
		}
		AnimationBase* targetAnimation = GetAnimationInstance(targetAnimationId);
		if (nullptr == targetAnimation)
		{
			return;
		}
		int sourceFrameCount = sourceAnimation->GetFrameCount();
		int targetFrameCount = targetAnimation->GetFrameCount();
		for (int frameId = 0; frameId < sourceFrameCount && (frameId+offset) < targetFrameCount; ++frameId)
		{
			PluginCopyKeyColorOffset(sourceAnimationId, targetAnimationId, frameId, rzkey, offset);
		}
	}

	EXPORT_API void PluginCopyKeyColorAllFramesOffsetName(const char* sourceAnimation, const char* targetAnimation, int rzkey, int offset)
	{
		int sourceAnimationId = PluginGetAnimation(sourceAnimation);
		if (sourceAnimationId < 0)
		{
			LogError("PluginCopyKeyColorAllFramesOffsetName: Source Animation not found! %s\r\n", sourceAnimation);
			return;
		}

		int targetAnimationId = PluginGetAnimation(targetAnimation);
		if (targetAnimationId < 0)
		{
			LogError("PluginCopyKeyColorAllFramesOffsetName: Target Animation not found! %s\r\n", targetAnimation);
			return;
		}

		PluginCopyKeyColorAllFramesOffset(sourceAnimationId, targetAnimationId, rzkey, offset);
	}

	EXPORT_API double PluginCopyKeyColorAllFramesOffsetNameD(const char* sourceAnimation, const char* targetAnimation, double rzkey, double offset)
	{
		PluginCopyKeyColorAllFramesOffsetName(sourceAnimation, targetAnimation, (int)rzkey, (int)offset);
		return 0;
	}


	EXPORT_API void PluginCopyAllKeys(int sourceAnimationId, int targetAnimationId, int frameId)
	{
		PluginStopAnimation(targetAnimationId);
		AnimationBase* sourceAnimation = GetAnimationInstance(sourceAnimationId);
		if (nullptr == sourceAnimation)
		{
			return;
		}
		AnimationBase* targetAnimation = GetAnimationInstance(targetAnimationId);
		if (nullptr == targetAnimation)
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() != targetAnimation->GetDeviceType() ||
			sourceAnimation->GetDeviceId() != targetAnimation->GetDeviceId())
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_1D)
		{
			Animation1D* sourceAnimation1D = (Animation1D*)(sourceAnimation);
			Animation1D* targetAnimation1D = (Animation1D*)(targetAnimation);
			vector<FChromaSDKColorFrame1D>& sourceFrames = sourceAnimation1D->GetFrames();
			vector<FChromaSDKColorFrame1D>& targetFrames = targetAnimation1D->GetFrames();
			if (sourceFrames.size() == 0)
			{
				return;
			}
			if (targetFrames.size() == 0)
			{
				return;
			}
			int maxLeds = PluginGetMaxLeds((int)sourceAnimation1D->GetDevice());
			if (frameId >= 0 && frameId < int(targetFrames.size()))
			{
				FChromaSDKColorFrame1D& sourceFrame = sourceFrames[frameId % sourceFrames.size()];
				FChromaSDKColorFrame1D& targetFrame = targetFrames[frameId];
				for (int i = 0; i < maxLeds; ++i)
				{
					int color = sourceFrame.Colors[i];
					targetFrame.Colors[i] = color;
				}
			}
		}
		else if (sourceAnimation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_2D)
		{
			Animation2D* sourceAnimation2D = (Animation2D*)(sourceAnimation);
			Animation2D* targetAnimation2D = (Animation2D*)(targetAnimation);
			vector<FChromaSDKColorFrame2D>& sourceFrames = sourceAnimation2D->GetFrames();
			vector<FChromaSDKColorFrame2D>& targetFrames = targetAnimation2D->GetFrames();
			if (sourceFrames.size() == 0)
			{
				return;
			}
			if (targetFrames.size() == 0)
			{
				return;
			}
			int maxRow = PluginGetMaxRow((int)sourceAnimation2D->GetDevice());
			int maxColumn = PluginGetMaxColumn((int)sourceAnimation2D->GetDevice());
			if (frameId >= 0 && frameId < int(targetFrames.size()))
			{
				FChromaSDKColorFrame2D& sourceFrame = sourceFrames[frameId % sourceFrames.size()];
				FChromaSDKColorFrame2D& targetFrame = targetFrames[frameId];
				for (int i = 0; i < maxRow; ++i)
				{
					for (int j = 0; j < maxColumn; ++j)
					{
						int color = sourceFrame.Colors[i].Colors[j];
						targetFrame.Colors[i].Colors[j] = color;
					}
				}
			}
		}
	}

	EXPORT_API void PluginCopyAllKeysName(const char* sourceAnimation, const char* targetAnimation, int frameId)
	{
		int sourceAnimationId = PluginGetAnimation(sourceAnimation);
		if (sourceAnimationId < 0)
		{
			LogError("PluginCopyAllKeysName: Source Animation not found! %s\r\n", sourceAnimation);
			return;
		}

		int targetAnimationId = PluginGetAnimation(targetAnimation);
		if (targetAnimationId < 0)
		{
			LogError("PluginCopyAllKeysName: Target Animation not found! %s\r\n", targetAnimation);
			return;
		}

		PluginCopyAllKeys(sourceAnimationId, targetAnimationId, frameId);
	}


	EXPORT_API void PluginCopyNonZeroAllKeys(int sourceAnimationId, int targetAnimationId, int frameId)
	{
		PluginStopAnimation(targetAnimationId);
		AnimationBase* sourceAnimation = GetAnimationInstance(sourceAnimationId);
		if (nullptr == sourceAnimation)
		{
			return;
		}
		AnimationBase* targetAnimation = GetAnimationInstance(targetAnimationId);
		if (nullptr == targetAnimation)
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() != targetAnimation->GetDeviceType() ||
			sourceAnimation->GetDeviceId() != targetAnimation->GetDeviceId())
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_1D)
		{
			Animation1D* sourceAnimation1D = (Animation1D*)(sourceAnimation);
			Animation1D* targetAnimation1D = (Animation1D*)(targetAnimation);
			vector<FChromaSDKColorFrame1D>& sourceFrames = sourceAnimation1D->GetFrames();
			vector<FChromaSDKColorFrame1D>& targetFrames = targetAnimation1D->GetFrames();
			if (sourceFrames.size() == 0)
			{
				return;
			}
			if (targetFrames.size() == 0)
			{
				return;
			}
			int maxLeds = PluginGetMaxLeds((int)sourceAnimation1D->GetDevice());
			if (frameId >= 0 && frameId < int(targetFrames.size()))
			{
				FChromaSDKColorFrame1D& sourceFrame = sourceFrames[frameId % sourceFrames.size()];
				FChromaSDKColorFrame1D& targetFrame = targetFrames[frameId];
				for (int i = 0; i < maxLeds; ++i)
				{
					int color = sourceFrame.Colors[i];
					if (color != 0)
					{
						targetFrame.Colors[i] = color;
					}
				}
			}
		}
		else if (sourceAnimation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_2D)
		{
			Animation2D* sourceAnimation2D = (Animation2D*)(sourceAnimation);
			Animation2D* targetAnimation2D = (Animation2D*)(targetAnimation);
			vector<FChromaSDKColorFrame2D>& sourceFrames = sourceAnimation2D->GetFrames();
			vector<FChromaSDKColorFrame2D>& targetFrames = targetAnimation2D->GetFrames();
			if (sourceFrames.size() == 0)
			{
				return;
			}
			if (targetFrames.size() == 0)
			{
				return;
			}
			int maxRow = PluginGetMaxRow((int)sourceAnimation2D->GetDevice());
			int maxColumn = PluginGetMaxColumn((int)sourceAnimation2D->GetDevice());
			if (frameId >= 0 && frameId < int(targetFrames.size()))
			{
				FChromaSDKColorFrame2D& sourceFrame = sourceFrames[frameId % sourceFrames.size()];
				FChromaSDKColorFrame2D& targetFrame = targetFrames[frameId];
				for (int i = 0; i < maxRow; ++i)
				{
					for (int j = 0; j < maxColumn; ++j)
					{
						int color = sourceFrame.Colors[i].Colors[j];
						if (color != 0)
						{
							targetFrame.Colors[i].Colors[j] = color;
						}
					}
				}
			}
		}
	}

	EXPORT_API void PluginCopyNonZeroAllKeysName(const char* sourceAnimation, const char* targetAnimation, int frameId)
	{
		int sourceAnimationId = PluginGetAnimation(sourceAnimation);
		if (sourceAnimationId < 0)
		{
			LogError("PluginCopyNonZeroAllKeysName: Source Animation not found! %s\r\n", sourceAnimation);
			return;
		}

		int targetAnimationId = PluginGetAnimation(targetAnimation);
		if (targetAnimationId < 0)
		{
			LogError("PluginCopyNonZeroAllKeysName: Target Animation not found! %s\r\n", targetAnimation);
			return;
		}

		PluginCopyNonZeroAllKeys(sourceAnimationId, targetAnimationId, frameId);
	}

	EXPORT_API double PluginCopyNonZeroAllKeysNameD(const char* sourceAnimation, const char* targetAnimation, double frameId)
	{
		PluginCopyNonZeroAllKeysName(sourceAnimation, targetAnimation, (int)frameId);
		return 0;
	}


	EXPORT_API void PluginCopyNonZeroAllKeysOffset(int sourceAnimationId, int targetAnimationId, int frameId, int offset)
	{
		PluginStopAnimation(targetAnimationId);
		AnimationBase* sourceAnimation = GetAnimationInstance(sourceAnimationId);
		if (nullptr == sourceAnimation)
		{
			return;
		}
		AnimationBase* targetAnimation = GetAnimationInstance(targetAnimationId);
		if (nullptr == targetAnimation)
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() != targetAnimation->GetDeviceType() ||
			sourceAnimation->GetDeviceId() != targetAnimation->GetDeviceId())
		{
			return;
		}
		if (frameId < 0)
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_1D)
		{
			Animation1D* sourceAnimation1D = (Animation1D*)(sourceAnimation);
			Animation1D* targetAnimation1D = (Animation1D*)(targetAnimation);
			vector<FChromaSDKColorFrame1D>& sourceFrames = sourceAnimation1D->GetFrames();
			vector<FChromaSDKColorFrame1D>& targetFrames = targetAnimation1D->GetFrames();
			if (sourceFrames.size() == 0)
			{
				return;
			}
			if (targetFrames.size() == 0)
			{
				return;
			}
			int maxLeds = PluginGetMaxLeds((int)sourceAnimation1D->GetDevice());
			if (frameId < int(sourceFrames.size()) && (frameId + offset) < int(targetFrames.size()))
			{
				FChromaSDKColorFrame1D& sourceFrame = sourceFrames[frameId];
				FChromaSDKColorFrame1D& targetFrame = targetFrames[(frameId + offset) % targetFrames.size()];
				for (int i = 0; i < maxLeds; ++i)
				{
					int color = sourceFrame.Colors[i];
					if (color != 0)
					{
						targetFrame.Colors[i] = color;
					}
				}
			}
		}
		else if (sourceAnimation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_2D)
		{
			Animation2D* sourceAnimation2D = (Animation2D*)(sourceAnimation);
			Animation2D* targetAnimation2D = (Animation2D*)(targetAnimation);
			vector<FChromaSDKColorFrame2D>& sourceFrames = sourceAnimation2D->GetFrames();
			vector<FChromaSDKColorFrame2D>& targetFrames = targetAnimation2D->GetFrames();
			if (sourceFrames.size() == 0)
			{
				return;
			}
			if (targetFrames.size() == 0)
			{
				return;
			}
			int maxRow = PluginGetMaxRow((int)sourceAnimation2D->GetDevice());
			int maxColumn = PluginGetMaxColumn((int)sourceAnimation2D->GetDevice());
			if (frameId < int(sourceFrames.size()) && (frameId + offset) < int(targetFrames.size()))
			{
				FChromaSDKColorFrame2D& sourceFrame = sourceFrames[frameId];
				FChromaSDKColorFrame2D& targetFrame = targetFrames[(frameId + offset) % targetFrames.size()];
				for (int i = 0; i < maxRow; ++i)
				{
					for (int j = 0; j < maxColumn; ++j)
					{
						int color = sourceFrame.Colors[i].Colors[j];
						if (color != 0)
						{
							targetFrame.Colors[i].Colors[j] = color;
						}
					}
				}
			}
		}
	}

	EXPORT_API void PluginCopyNonZeroAllKeysOffsetName(const char* sourceAnimation, const char* targetAnimation, int frameId, int offset)
	{
		int sourceAnimationId = PluginGetAnimation(sourceAnimation);
		if (sourceAnimationId < 0)
		{
			LogError("PluginCopyNonZeroAllKeysOffsetName: Source Animation not found! %s\r\n", sourceAnimation);
			return;
		}

		int targetAnimationId = PluginGetAnimation(targetAnimation);
		if (targetAnimationId < 0)
		{
			LogError("PluginCopyNonZeroAllKeysOffsetName: Target Animation not found! %s\r\n", targetAnimation);
			return;
		}

		PluginCopyNonZeroAllKeysOffset(sourceAnimationId, targetAnimationId, frameId, offset);
	}

	EXPORT_API double PluginCopyNonZeroAllKeysOffsetNameD(const char* sourceAnimation, const char* targetAnimation, double frameId, double offset)
	{
		PluginCopyNonZeroAllKeysOffsetName(sourceAnimation, targetAnimation, (int)frameId, (int)offset);
		return 0;
	}


	EXPORT_API void PluginCopyNonZeroTargetAllKeysOffset(int sourceAnimationId, int targetAnimationId, int frameId, int offset)
	{
		PluginStopAnimation(targetAnimationId);
		AnimationBase* sourceAnimation = GetAnimationInstance(sourceAnimationId);
		if (nullptr == sourceAnimation)
		{
			return;
		}
		AnimationBase* targetAnimation = GetAnimationInstance(targetAnimationId);
		if (nullptr == targetAnimation)
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() != targetAnimation->GetDeviceType() ||
			sourceAnimation->GetDeviceId() != sourceAnimation->GetDeviceId())
		{
			return;
		}
		if (frameId < 0)
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_1D)
		{
			Animation1D* sourceAnimation1D = (Animation1D*)(sourceAnimation);
			Animation1D* targetAnimation1D = (Animation1D*)(targetAnimation);
			vector<FChromaSDKColorFrame1D>& sourceFrames = sourceAnimation1D->GetFrames();
			vector<FChromaSDKColorFrame1D>& targetFrames = targetAnimation1D->GetFrames();
			if (sourceFrames.size() == 0)
			{
				return;
			}
			if (targetFrames.size() == 0)
			{
				return;
			}
			int maxLeds = PluginGetMaxLeds((int)sourceAnimation1D->GetDevice());
			if (frameId < int(sourceFrames.size()))
			{
				FChromaSDKColorFrame1D& sourceFrame = sourceFrames[frameId];
				FChromaSDKColorFrame1D& targetFrame = targetFrames[(frameId + offset) % targetFrames.size()];
				for (int i = 0; i < maxLeds; ++i)
				{
					int color = sourceFrame.Colors[i];
					if (color != 0 &&
						targetFrame.Colors[i] != 0)
					{
						targetFrame.Colors[i] = color;
					}
				}
			}
		}
		else if (sourceAnimation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_2D)
		{
			Animation2D* sourceAnimation2D = (Animation2D*)(sourceAnimation);
			Animation2D* targetAnimation2D = (Animation2D*)(targetAnimation);
			vector<FChromaSDKColorFrame2D>& sourceFrames = sourceAnimation2D->GetFrames();
			vector<FChromaSDKColorFrame2D>& targetFrames = targetAnimation2D->GetFrames();
			if (sourceFrames.size() == 0)
			{
				return;
			}
			if (targetFrames.size() == 0)
			{
				return;
			}
			int maxRow = PluginGetMaxRow((int)sourceAnimation2D->GetDevice());
			int maxColumn = PluginGetMaxColumn((int)sourceAnimation2D->GetDevice());
			if (frameId < int(sourceFrames.size()))
			{
				FChromaSDKColorFrame2D& sourceFrame = sourceFrames[frameId];
				FChromaSDKColorFrame2D& targetFrame = targetFrames[(frameId + offset) % targetFrames.size()];
				for (int i = 0; i < maxRow; ++i)
				{
					for (int j = 0; j < maxColumn; ++j)
					{
						int color = sourceFrame.Colors[i].Colors[j];
						if (color != 0 &&
							targetFrame.Colors[i].Colors[j] != 0)
						{
							targetFrame.Colors[i].Colors[j] = color;
						}
					}
				}
			}
		}
	}

	EXPORT_API void PluginCopyNonZeroTargetAllKeysOffsetName(const char* sourceAnimation, const char* targetAnimation, int frameId, int offset)
	{
		int sourceAnimationId = PluginGetAnimation(sourceAnimation);
		if (sourceAnimationId < 0)
		{
			LogError("PluginCopyNonZeroTargetAllKeysOffsetName: Source Animation not found! %s\r\n", sourceAnimation);
			return;
		}

		int targetAnimationId = PluginGetAnimation(targetAnimation);
		if (targetAnimationId < 0)
		{
			LogError("PluginCopyNonZeroTargetAllKeysOffsetName: Target Animation not found! %s\r\n", targetAnimation);
			return;
		}

		PluginCopyNonZeroTargetAllKeysOffset(sourceAnimationId, targetAnimationId, frameId, offset);
	}

	EXPORT_API double PluginCopyNonZeroTargetAllKeysOffsetNameD(const char* sourceAnimation, const char* targetAnimation, double frameId, double offset)
	{
		PluginCopyNonZeroTargetAllKeysOffsetName(sourceAnimation, targetAnimation, (int)frameId, (int)offset);
		return 0;
	}


	EXPORT_API void PluginAddNonZeroAllKeysOffset(int sourceAnimationId, int targetAnimationId, int frameId, int offset)
	{
		PluginStopAnimation(targetAnimationId);
		AnimationBase* sourceAnimation = GetAnimationInstance(sourceAnimationId);
		if (nullptr == sourceAnimation)
		{
			return;
		}
		AnimationBase* targetAnimation = GetAnimationInstance(targetAnimationId);
		if (nullptr == targetAnimation)
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() != targetAnimation->GetDeviceType() ||
			sourceAnimation->GetDeviceId() != targetAnimation->GetDeviceId())
		{
			return;
		}
		if (frameId < 0)
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_1D)
		{
			Animation1D* sourceAnimation1D = (Animation1D*)(sourceAnimation);
			Animation1D* targetAnimation1D = (Animation1D*)(targetAnimation);
			vector<FChromaSDKColorFrame1D>& sourceFrames = sourceAnimation1D->GetFrames();
			vector<FChromaSDKColorFrame1D>& targetFrames = targetAnimation1D->GetFrames();
			if (sourceFrames.size() == 0)
			{
				return;
			}
			if (targetFrames.size() == 0)
			{
				return;
			}
			int maxLeds = PluginGetMaxLeds((int)sourceAnimation1D->GetDevice());
			if (frameId < int(sourceFrames.size()))
			{
				FChromaSDKColorFrame1D& sourceFrame = sourceFrames[frameId];
				FChromaSDKColorFrame1D& targetFrame = targetFrames[(frameId + offset) % targetFrames.size()];
				for (int i = 0; i < maxLeds; ++i)
				{
					int color = sourceFrame.Colors[i];
					if (color != 0)
					{
						int sourceRed = color & 0xFF;
						int sourceGreen = (color & 0xFF00) >> 8;
						int sourceBlue = (color & 0xFF0000) >> 16;

						int oldColor = targetFrame.Colors[i];
						int oldRed = oldColor & 0xFF;
						int oldGreen = (oldColor & 0xFF00) >> 8;
						int oldBlue = (oldColor & 0xFF0000) >> 16;

						int red = min(255, max(0, oldRed + sourceRed)) & 0xFF;
						int green = min(255, max(0, oldGreen + sourceGreen)) & 0xFF;
						int blue = min(255, max(0, oldBlue + sourceBlue)) & 0xFF;
						int newColor = red | (green << 8) | (blue << 16);

						targetFrame.Colors[i] = newColor;
					}
				}
			}
		}
		else if (sourceAnimation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_2D)
		{
			Animation2D* sourceAnimation2D = (Animation2D*)(sourceAnimation);
			Animation2D* targetAnimation2D = (Animation2D*)(targetAnimation);
			vector<FChromaSDKColorFrame2D>& sourceFrames = sourceAnimation2D->GetFrames();
			vector<FChromaSDKColorFrame2D>& targetFrames = targetAnimation2D->GetFrames();
			if (sourceFrames.size() == 0)
			{
				return;
			}
			if (targetFrames.size() == 0)
			{
				return;
			}
			int maxRow = PluginGetMaxRow((int)sourceAnimation2D->GetDevice());
			int maxColumn = PluginGetMaxColumn((int)sourceAnimation2D->GetDevice());
			if (frameId < int(sourceFrames.size()))
			{
				FChromaSDKColorFrame2D& sourceFrame = sourceFrames[frameId];
				FChromaSDKColorFrame2D& targetFrame = targetFrames[(frameId + offset) % targetFrames.size()];
				for (int i = 0; i < maxRow; ++i)
				{
					for (int j = 0; j < maxColumn; ++j)
					{
						int color = sourceFrame.Colors[i].Colors[j];
						if (color != 0)
						{
							int sourceRed = color & 0xFF;
							int sourceGreen = (color & 0xFF00) >> 8;
							int sourceBlue = (color & 0xFF0000) >> 16;

							int oldColor = targetFrame.Colors[i].Colors[j];
							int oldRed = oldColor & 0xFF;
							int oldGreen = (oldColor & 0xFF00) >> 8;
							int oldBlue = (oldColor & 0xFF0000) >> 16;

							int red = min(255, max(0, oldRed + sourceRed)) & 0xFF;
							int green = min(255, max(0, oldGreen + sourceGreen)) & 0xFF;
							int blue = min(255, max(0, oldBlue + sourceBlue)) & 0xFF;
							int newColor = red | (green << 8) | (blue << 16);

							targetFrame.Colors[i].Colors[j] = newColor;
						}
					}
				}
			}
		}
	}

	EXPORT_API void PluginAddNonZeroAllKeysOffsetName(const char* sourceAnimation, const char* targetAnimation, int frameId, int offset)
	{
		int sourceAnimationId = PluginGetAnimation(sourceAnimation);
		if (sourceAnimationId < 0)
		{
			LogError("PluginAddNonZeroAllKeysOffsetName: Source Animation not found! %s\r\n", sourceAnimation);
			return;
		}

		int targetAnimationId = PluginGetAnimation(targetAnimation);
		if (targetAnimationId < 0)
		{
			LogError("PluginAddNonZeroAllKeysOffsetName: Target Animation not found! %s\r\n", targetAnimation);
			return;
		}

		PluginAddNonZeroAllKeysOffset(sourceAnimationId, targetAnimationId, frameId, offset);
	}

	EXPORT_API double PluginAddNonZeroAllKeysOffsetNameD(const char* sourceAnimation, const char* targetAnimation, double frameId, double offset)
	{
		PluginAddNonZeroAllKeysOffsetName(sourceAnimation, targetAnimation, (int)frameId, (int)offset);
		return 0;
	}


	EXPORT_API void PluginAddNonZeroTargetAllKeysOffset(int sourceAnimationId, int targetAnimationId, int frameId, int offset)
	{
		PluginStopAnimation(targetAnimationId);
		AnimationBase* sourceAnimation = GetAnimationInstance(sourceAnimationId);
		if (nullptr == sourceAnimation)
		{
			return;
		}
		AnimationBase* targetAnimation = GetAnimationInstance(targetAnimationId);
		if (nullptr == targetAnimation)
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() != targetAnimation->GetDeviceType() ||
			sourceAnimation->GetDeviceId() != sourceAnimation->GetDeviceId())
		{
			return;
		}
		if (frameId < 0)
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_1D)
		{
			Animation1D* sourceAnimation1D = (Animation1D*)(sourceAnimation);
			Animation1D* targetAnimation1D = (Animation1D*)(targetAnimation);
			vector<FChromaSDKColorFrame1D>& sourceFrames = sourceAnimation1D->GetFrames();
			vector<FChromaSDKColorFrame1D>& targetFrames = targetAnimation1D->GetFrames();
			if (sourceFrames.size() == 0)
			{
				return;
			}
			if (targetFrames.size() == 0)
			{
				return;
			}
			int maxLeds = PluginGetMaxLeds(sourceAnimation->GetDeviceId());
			if (frameId < int(sourceFrames.size()))
			{
				FChromaSDKColorFrame1D& sourceFrame = sourceFrames[frameId];
				FChromaSDKColorFrame1D& targetFrame = targetFrames[(frameId + offset) % targetFrames.size()];
				for (int i = 0; i < maxLeds; ++i)
				{
					int color = sourceFrame.Colors[i];
					if (color != 0 &&
						targetFrame.Colors[i] != 0)
					{
						int sourceRed = color & 0xFF;
						int sourceGreen = (color & 0xFF00) >> 8;
						int sourceBlue = (color & 0xFF0000) >> 16;

						int oldColor = targetFrame.Colors[i];
						int oldRed = oldColor & 0xFF;
						int oldGreen = (oldColor & 0xFF00) >> 8;
						int oldBlue = (oldColor & 0xFF0000) >> 16;

						int red = min(255, max(0, oldRed + sourceRed)) & 0xFF;
						int green = min(255, max(0, oldGreen + sourceGreen)) & 0xFF;
						int blue = min(255, max(0, oldBlue + sourceBlue)) & 0xFF;
						int newColor = red | (green << 8) | (blue << 16);

						targetFrame.Colors[i] = newColor;
					}
				}
			}
		}
		else if (sourceAnimation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_2D)
		{
			Animation2D* sourceAnimation2D = (Animation2D*)(sourceAnimation);
			Animation2D* targetAnimation2D = (Animation2D*)(targetAnimation);
			vector<FChromaSDKColorFrame2D>& sourceFrames = sourceAnimation2D->GetFrames();
			vector<FChromaSDKColorFrame2D>& targetFrames = targetAnimation2D->GetFrames();
			if (sourceFrames.size() == 0)
			{
				return;
			}
			if (targetFrames.size() == 0)
			{
				return;
			}
			int maxRow = PluginGetMaxRow(sourceAnimation->GetDeviceId());
			int maxColumn = PluginGetMaxColumn(sourceAnimation->GetDeviceId());
			if (frameId < int(sourceFrames.size()))
			{
				FChromaSDKColorFrame2D& sourceFrame = sourceFrames[frameId];
				FChromaSDKColorFrame2D& targetFrame = targetFrames[(frameId + offset) % targetFrames.size()];
				for (int i = 0; i < maxRow; ++i)
				{
					for (int j = 0; j < maxColumn; ++j)
					{
						int color = sourceFrame.Colors[i].Colors[j];
						if (color != 0 &&
							targetFrame.Colors[i].Colors[j] != 0)
						{
							int sourceRed = color & 0xFF;
							int sourceGreen = (color & 0xFF00) >> 8;
							int sourceBlue = (color & 0xFF0000) >> 16;

							int oldColor = targetFrame.Colors[i].Colors[j];
							int oldRed = oldColor & 0xFF;
							int oldGreen = (oldColor & 0xFF00) >> 8;
							int oldBlue = (oldColor & 0xFF0000) >> 16;

							int red = min(255, max(0, oldRed + sourceRed)) & 0xFF;
							int green = min(255, max(0, oldGreen + sourceGreen)) & 0xFF;
							int blue = min(255, max(0, oldBlue + sourceBlue)) & 0xFF;
							int newColor = red | (green << 8) | (blue << 16);

							targetFrame.Colors[i].Colors[j] = newColor;
						}
					}
				}
			}
		}
	}

	EXPORT_API void PluginAddNonZeroTargetAllKeysOffsetName(const char* sourceAnimation, const char* targetAnimation, int frameId, int offset)
	{
		int sourceAnimationId = PluginGetAnimation(sourceAnimation);
		if (sourceAnimationId < 0)
		{
			LogError("PluginAddNonZeroTargetAllKeysOffsetName: Source Animation not found! %s\r\n", sourceAnimation);
			return;
		}

		int targetAnimationId = PluginGetAnimation(targetAnimation);
		if (targetAnimationId < 0)
		{
			LogError("PluginAddNonZeroTargetAllKeysOffsetName: Target Animation not found! %s\r\n", targetAnimation);
			return;
		}

		PluginAddNonZeroTargetAllKeysOffset(sourceAnimationId, targetAnimationId, frameId, offset);
	}

	EXPORT_API double PluginAddNonZeroTargetAllKeysOffsetNameD(const char* sourceAnimation, const char* targetAnimation, double frameId, double offset)
	{
		PluginAddNonZeroTargetAllKeysOffsetName(sourceAnimation, targetAnimation, (int)frameId, (int)offset);
		return 0;
	}


	EXPORT_API void PluginSubtractNonZeroAllKeysOffset(int sourceAnimationId, int targetAnimationId, int frameId, int offset)
	{
		PluginStopAnimation(targetAnimationId);
		AnimationBase* sourceAnimation = GetAnimationInstance(sourceAnimationId);
		if (nullptr == sourceAnimation)
		{
			return;
		}
		AnimationBase* targetAnimation = GetAnimationInstance(targetAnimationId);
		if (nullptr == targetAnimation)
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() != targetAnimation->GetDeviceType() ||
			sourceAnimation->GetDeviceId() != targetAnimation->GetDeviceId())
		{
			return;
		}
		if (frameId < 0)
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_1D)
		{
			Animation1D* sourceAnimation1D = (Animation1D*)(sourceAnimation);
			Animation1D* targetAnimation1D = (Animation1D*)(targetAnimation);
			vector<FChromaSDKColorFrame1D>& sourceFrames = sourceAnimation1D->GetFrames();
			vector<FChromaSDKColorFrame1D>& targetFrames = targetAnimation1D->GetFrames();
			if (sourceFrames.size() == 0)
			{
				return;
			}
			if (targetFrames.size() == 0)
			{
				return;
			}
			int maxLeds = PluginGetMaxLeds((int)sourceAnimation1D->GetDevice());
			if (frameId < int(sourceFrames.size()))
			{
				FChromaSDKColorFrame1D& sourceFrame = sourceFrames[frameId];
				FChromaSDKColorFrame1D& targetFrame = targetFrames[(frameId + offset) % targetFrames.size()];
				for (int i = 0; i < maxLeds; ++i)
				{
					int color = sourceFrame.Colors[i];
					if (color != 0)
					{
						int sourceRed = color & 0xFF;
						int sourceGreen = (color & 0xFF00) >> 8;
						int sourceBlue = (color & 0xFF0000) >> 16;

						int oldColor = targetFrame.Colors[i];
						int oldRed = oldColor & 0xFF;
						int oldGreen = (oldColor & 0xFF00) >> 8;
						int oldBlue = (oldColor & 0xFF0000) >> 16;

						int red = min(255, max(0, oldRed - sourceRed)) & 0xFF;
						int green = min(255, max(0, oldGreen - sourceGreen)) & 0xFF;
						int blue = min(255, max(0, oldBlue - sourceBlue)) & 0xFF;
						int newColor = red | (green << 8) | (blue << 16);

						targetFrame.Colors[i] = newColor;
					}
				}
			}
		}
		else if (sourceAnimation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_2D)
		{
			Animation2D* sourceAnimation2D = (Animation2D*)(sourceAnimation);
			Animation2D* targetAnimation2D = (Animation2D*)(targetAnimation);
			vector<FChromaSDKColorFrame2D>& sourceFrames = sourceAnimation2D->GetFrames();
			vector<FChromaSDKColorFrame2D>& targetFrames = targetAnimation2D->GetFrames();
			if (sourceFrames.size() == 0)
			{
				return;
			}
			if (targetFrames.size() == 0)
			{
				return;
			}
			int maxRow = PluginGetMaxRow((int)sourceAnimation2D->GetDevice());
			int maxColumn = PluginGetMaxColumn((int)sourceAnimation2D->GetDevice());
			if (frameId < int(sourceFrames.size()))
			{
				FChromaSDKColorFrame2D& sourceFrame = sourceFrames[frameId];
				FChromaSDKColorFrame2D& targetFrame = targetFrames[(frameId + offset) % targetFrames.size()];
				for (int i = 0; i < maxRow; ++i)
				{
					for (int j = 0; j < maxColumn; ++j)
					{
						int color = sourceFrame.Colors[i].Colors[j];
						if (color != 0)
						{
							int sourceRed = color & 0xFF;
							int sourceGreen = (color & 0xFF00) >> 8;
							int sourceBlue = (color & 0xFF0000) >> 16;

							int oldColor = targetFrame.Colors[i].Colors[j];
							int oldRed = oldColor & 0xFF;
							int oldGreen = (oldColor & 0xFF00) >> 8;
							int oldBlue = (oldColor & 0xFF0000) >> 16;

							int red = min(255, max(0, oldRed - sourceRed)) & 0xFF;
							int green = min(255, max(0, oldGreen - sourceGreen)) & 0xFF;
							int blue = min(255, max(0, oldBlue - sourceBlue)) & 0xFF;
							int newColor = red | (green << 8) | (blue << 16);

							targetFrame.Colors[i].Colors[j] = newColor;
						}
					}
				}
			}
		}
	}

	EXPORT_API void PluginSubtractNonZeroAllKeysOffsetName(const char* sourceAnimation, const char* targetAnimation, int frameId, int offset)
	{
		int sourceAnimationId = PluginGetAnimation(sourceAnimation);
		if (sourceAnimationId < 0)
		{
			LogError("PluginSubtractNonZeroAllKeysOffsetName: Source Animation not found! %s\r\n", sourceAnimation);
			return;
		}

		int targetAnimationId = PluginGetAnimation(targetAnimation);
		if (targetAnimationId < 0)
		{
			LogError("PluginSubtractNonZeroAllKeysOffsetName: Target Animation not found! %s\r\n", targetAnimation);
			return;
		}

		PluginSubtractNonZeroAllKeysOffset(sourceAnimationId, targetAnimationId, frameId, offset);
	}

	EXPORT_API double PluginSubtractNonZeroAllKeysOffsetNameD(const char* sourceAnimation, const char* targetAnimation, double frameId, double offset)
	{
		PluginSubtractNonZeroAllKeysOffsetName(sourceAnimation, targetAnimation, (int)frameId, (int)offset);
		return 0;
	}


	EXPORT_API void PluginSubtractNonZeroTargetAllKeysOffset(int sourceAnimationId, int targetAnimationId, int frameId, int offset)
	{
		PluginStopAnimation(targetAnimationId);
		AnimationBase* sourceAnimation = GetAnimationInstance(sourceAnimationId);
		if (nullptr == sourceAnimation)
		{
			return;
		}
		AnimationBase* targetAnimation = GetAnimationInstance(targetAnimationId);
		if (nullptr == targetAnimation)
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() != targetAnimation->GetDeviceType() ||
			sourceAnimation->GetDeviceId() != sourceAnimation->GetDeviceId())
		{
			return;
		}
		if (frameId < 0)
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_1D)
		{
			Animation1D* sourceAnimation1D = (Animation1D*)(sourceAnimation);
			Animation1D* targetAnimation1D = (Animation1D*)(targetAnimation);
			vector<FChromaSDKColorFrame1D>& sourceFrames = sourceAnimation1D->GetFrames();
			vector<FChromaSDKColorFrame1D>& targetFrames = targetAnimation1D->GetFrames();
			if (sourceFrames.size() == 0)
			{
				return;
			}
			if (targetFrames.size() == 0)
			{
				return;
			}
			int maxLeds = PluginGetMaxLeds((int)sourceAnimation1D->GetDevice());
			if (frameId < int(sourceFrames.size()))
			{
				FChromaSDKColorFrame1D& sourceFrame = sourceFrames[frameId];
				FChromaSDKColorFrame1D& targetFrame = targetFrames[(frameId + offset) % targetFrames.size()];
				for (int i = 0; i < maxLeds; ++i)
				{
					int color = sourceFrame.Colors[i];
					if (color != 0 &&
						targetFrame.Colors[i] != 0)
					{
						int sourceRed = color & 0xFF;
						int sourceGreen = (color & 0xFF00) >> 8;
						int sourceBlue = (color & 0xFF0000) >> 16;

						int oldColor = targetFrame.Colors[i];
						int oldRed = oldColor & 0xFF;
						int oldGreen = (oldColor & 0xFF00) >> 8;
						int oldBlue = (oldColor & 0xFF0000) >> 16;

						int red = min(255, max(0, oldRed - sourceRed)) & 0xFF;
						int green = min(255, max(0, oldGreen - sourceGreen)) & 0xFF;
						int blue = min(255, max(0, oldBlue - sourceBlue)) & 0xFF;
						int newColor = red | (green << 8) | (blue << 16);

						targetFrame.Colors[i] = newColor;
					}
				}
			}
		}
		else if (sourceAnimation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_2D)
		{
			Animation2D* sourceAnimation2D = (Animation2D*)(sourceAnimation);
			Animation2D* targetAnimation2D = (Animation2D*)(targetAnimation);
			vector<FChromaSDKColorFrame2D>& sourceFrames = sourceAnimation2D->GetFrames();
			vector<FChromaSDKColorFrame2D>& targetFrames = targetAnimation2D->GetFrames();
			if (sourceFrames.size() == 0)
			{
				return;
			}
			if (targetFrames.size() == 0)
			{
				return;
			}
			int maxRow = PluginGetMaxRow((int)sourceAnimation2D->GetDevice());
			int maxColumn = PluginGetMaxColumn((int)sourceAnimation2D->GetDevice());
			if (frameId < int(sourceFrames.size()))
			{
				FChromaSDKColorFrame2D& sourceFrame = sourceFrames[frameId];
				FChromaSDKColorFrame2D& targetFrame = targetFrames[(frameId + offset) % targetFrames.size()];
				for (int i = 0; i < maxRow; ++i)
				{
					for (int j = 0; j < maxColumn; ++j)
					{
						int color = sourceFrame.Colors[i].Colors[j];
						if (color != 0 &&
							targetFrame.Colors[i].Colors[j] != 0)
						{
							int sourceRed = color & 0xFF;
							int sourceGreen = (color & 0xFF00) >> 8;
							int sourceBlue = (color & 0xFF0000) >> 16;

							int oldColor = targetFrame.Colors[i].Colors[j];
							int oldRed = oldColor & 0xFF;
							int oldGreen = (oldColor & 0xFF00) >> 8;
							int oldBlue = (oldColor & 0xFF0000) >> 16;

							int red = min(255, max(0, oldRed - sourceRed)) & 0xFF;
							int green = min(255, max(0, oldGreen - sourceGreen)) & 0xFF;
							int blue = min(255, max(0, oldBlue - sourceBlue)) & 0xFF;
							int newColor = red | (green << 8) | (blue << 16);

							targetFrame.Colors[i].Colors[j] = newColor;
						}
					}
				}
			}
		}
	}

	EXPORT_API void PluginSubtractNonZeroTargetAllKeysOffsetName(const char* sourceAnimation, const char* targetAnimation, int frameId, int offset)
	{
		int sourceAnimationId = PluginGetAnimation(sourceAnimation);
		if (sourceAnimationId < 0)
		{
			LogError("PluginSubtractNonZeroTargetAllKeysOffsetName: Source Animation not found! %s\r\n", sourceAnimation);
			return;
		}

		int targetAnimationId = PluginGetAnimation(targetAnimation);
		if (targetAnimationId < 0)
		{
			LogError("PluginSubtractNonZeroTargetAllKeysOffsetName: Target Animation not found! %s\r\n", targetAnimation);
			return;
		}

		PluginSubtractNonZeroTargetAllKeysOffset(sourceAnimationId, targetAnimationId, frameId, offset);
	}

	EXPORT_API double PluginSubtractNonZeroTargetAllKeysOffsetNameD(const char* sourceAnimation, const char* targetAnimation, double frameId, double offset)
	{
		PluginSubtractNonZeroTargetAllKeysOffsetName(sourceAnimation, targetAnimation, (int)frameId, (int)offset);
		return 0;
	}


	EXPORT_API void PluginCopyNonZeroAllKeysAllFrames(int sourceAnimationId, int targetAnimationId)
	{
		PluginStopAnimation(targetAnimationId);
		AnimationBase* sourceAnimation = GetAnimationInstance(sourceAnimationId);
		if (nullptr == sourceAnimation)
		{
			return;
		}
		AnimationBase* targetAnimation = GetAnimationInstance(targetAnimationId);
		if (nullptr == targetAnimation)
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() != targetAnimation->GetDeviceType() ||
			sourceAnimation->GetDeviceId() != targetAnimation->GetDeviceId())
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_1D)
		{
			Animation1D* sourceAnimation1D = (Animation1D*)(sourceAnimation);
			Animation1D* targetAnimation1D = (Animation1D*)(targetAnimation);
			vector<FChromaSDKColorFrame1D>& sourceFrames = sourceAnimation1D->GetFrames();
			vector<FChromaSDKColorFrame1D>& targetFrames = targetAnimation1D->GetFrames();
			if (sourceFrames.size() == 0)
			{
				return;
			}
			if (targetFrames.size() == 0)
			{
				return;
			}
			int maxLeds = PluginGetMaxLeds((int)sourceAnimation1D->GetDevice());
			for (int frameId = 0; frameId < int(targetFrames.size()); ++frameId)
			{
				FChromaSDKColorFrame1D& sourceFrame = sourceFrames[frameId % sourceFrames.size()];
				FChromaSDKColorFrame1D& targetFrame = targetFrames[frameId];
				for (int i = 0; i < maxLeds; ++i)
				{
					int color = sourceFrame.Colors[i];
					if (color != 0)
					{
						targetFrame.Colors[i] = color;
					}
				}
			}
		}
		else if (sourceAnimation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_2D)
		{
			Animation2D* sourceAnimation2D = (Animation2D*)(sourceAnimation);
			Animation2D* targetAnimation2D = (Animation2D*)(targetAnimation);
			vector<FChromaSDKColorFrame2D>& sourceFrames = sourceAnimation2D->GetFrames();
			vector<FChromaSDKColorFrame2D>& targetFrames = targetAnimation2D->GetFrames();
			if (sourceFrames.size() == 0)
			{
				return;
			}
			if (targetFrames.size() == 0)
			{
				return;
			}
			int maxRow = PluginGetMaxRow((int)sourceAnimation2D->GetDevice());
			int maxColumn = PluginGetMaxColumn((int)sourceAnimation2D->GetDevice());
			for (int frameId = 0; frameId < int(targetFrames.size()); ++frameId)
			{
				FChromaSDKColorFrame2D& sourceFrame = sourceFrames[frameId % sourceFrames.size()];
				FChromaSDKColorFrame2D& targetFrame = targetFrames[frameId];
				for (int i = 0; i < maxRow; ++i)
				{
					for (int j = 0; j < maxColumn; ++j)
					{
						int color = sourceFrame.Colors[i].Colors[j];
						if (color != 0)
						{
							targetFrame.Colors[i].Colors[j] = color;
						}
					}
				}
			}
		}
	}

	EXPORT_API void PluginCopyNonZeroAllKeysAllFramesName(const char* sourceAnimation, const char* targetAnimation)
	{
		int sourceAnimationId = PluginGetAnimation(sourceAnimation);
		if (sourceAnimationId < 0)
		{
			LogError("PluginCopyNonZeroAllKeysAllFramesName: Source Animation not found! %s\r\n", sourceAnimation);
			return;
		}

		int targetAnimationId = PluginGetAnimation(targetAnimation);
		if (targetAnimationId < 0)
		{
			LogError("PluginCopyNonZeroAllKeysAllFramesName: Target Animation not found! %s\r\n", targetAnimation);
			return;
		}

		PluginCopyNonZeroAllKeysAllFrames(sourceAnimationId, targetAnimationId);
	}

	EXPORT_API double PluginCopyNonZeroAllKeysAllFramesNameD(const char* sourceAnimation, const char* targetAnimation)
	{
		PluginCopyNonZeroAllKeysAllFramesName(sourceAnimation, targetAnimation);
		return 0;
	}

	EXPORT_API void PluginAddNonZeroAllKeys(int sourceAnimationId, int targetAnimationId, int frameId)
	{
		PluginStopAnimation(targetAnimationId);
		AnimationBase* sourceAnimation = GetAnimationInstance(sourceAnimationId);
		if (nullptr == sourceAnimation)
		{
			return;
		}
		AnimationBase* targetAnimation = GetAnimationInstance(targetAnimationId);
		if (nullptr == targetAnimation)
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() != targetAnimation->GetDeviceType() ||
			sourceAnimation->GetDeviceId() != targetAnimation->GetDeviceId())
		{
			return;
		}
		if (frameId < 0)
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_1D)
		{
			Animation1D* sourceAnimation1D = (Animation1D*)(sourceAnimation);
			Animation1D* targetAnimation1D = (Animation1D*)(targetAnimation);
			vector<FChromaSDKColorFrame1D>& sourceFrames = sourceAnimation1D->GetFrames();
			vector<FChromaSDKColorFrame1D>& targetFrames = targetAnimation1D->GetFrames();
			if (sourceFrames.size() == 0)
			{
				return;
			}
			if (targetFrames.size() == 0)
			{
				return;
			}
			int maxLeds = PluginGetMaxLeds((int)sourceAnimation1D->GetDevice());
			if (frameId < int(targetFrames.size()))
			{
				FChromaSDKColorFrame1D& sourceFrame = sourceFrames[frameId % sourceFrames.size()];
				FChromaSDKColorFrame1D& targetFrame = targetFrames[frameId];
				for (int i = 0; i < maxLeds; ++i)
				{
					int color = sourceFrame.Colors[i];
					if (color != 0)
					{
						int sourceRed = color & 0xFF;
						int sourceGreen = (color & 0xFF00) >> 8;
						int sourceBlue = (color & 0xFF0000) >> 16;

						int oldColor = targetFrame.Colors[i];
						int oldRed = oldColor & 0xFF;
						int oldGreen = (oldColor & 0xFF00) >> 8;
						int oldBlue = (oldColor & 0xFF0000) >> 16;

						int red = min(255, max(0, oldRed + sourceRed)) & 0xFF;
						int green = min(255, max(0, oldGreen + sourceGreen)) & 0xFF;
						int blue = min(255, max(0, oldBlue + sourceBlue)) & 0xFF;
						int newColor = red | (green << 8) | (blue << 16);

						targetFrame.Colors[i] = newColor;
					}
				}
			}
		}
		else if (sourceAnimation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_2D)
		{
			Animation2D* sourceAnimation2D = (Animation2D*)(sourceAnimation);
			Animation2D* targetAnimation2D = (Animation2D*)(targetAnimation);
			vector<FChromaSDKColorFrame2D>& sourceFrames = sourceAnimation2D->GetFrames();
			vector<FChromaSDKColorFrame2D>& targetFrames = targetAnimation2D->GetFrames();
			if (sourceFrames.size() == 0)
			{
				return;
			}
			if (targetFrames.size() == 0)
			{
				return;
			}
			int maxRow = PluginGetMaxRow((int)sourceAnimation2D->GetDevice());
			int maxColumn = PluginGetMaxColumn((int)sourceAnimation2D->GetDevice());
			if (frameId < int(targetFrames.size()))
			{
				FChromaSDKColorFrame2D& sourceFrame = sourceFrames[frameId % sourceFrames.size()];
				FChromaSDKColorFrame2D& targetFrame = targetFrames[frameId];
				for (int i = 0; i < maxRow; ++i)
				{
					for (int j = 0; j < maxColumn; ++j)
					{
						int color = sourceFrame.Colors[i].Colors[j];
						if (color != 0)
						{
							int sourceRed = color & 0xFF;
							int sourceGreen = (color & 0xFF00) >> 8;
							int sourceBlue = (color & 0xFF0000) >> 16;

							int oldColor = targetFrame.Colors[i].Colors[j];
							int oldRed = oldColor & 0xFF;
							int oldGreen = (oldColor & 0xFF00) >> 8;
							int oldBlue = (oldColor & 0xFF0000) >> 16;

							int red = min(255, max(0, oldRed + sourceRed)) & 0xFF;
							int green = min(255, max(0, oldGreen + sourceGreen)) & 0xFF;
							int blue = min(255, max(0, oldBlue + sourceBlue)) & 0xFF;
							int newColor = red | (green << 8) | (blue << 16);

							targetFrame.Colors[i].Colors[j] = newColor;
						}
					}
				}
			}
		}		
	}

	EXPORT_API void PluginAddNonZeroAllKeysName(const char* sourceAnimation, const char* targetAnimation, int frameId)
	{
		int sourceAnimationId = PluginGetAnimation(sourceAnimation);
		if (sourceAnimationId < 0)
		{
			LogError("PluginAddNonZeroAllKeysName: Source Animation not found! %s\r\n", sourceAnimation);
			return;
		}

		int targetAnimationId = PluginGetAnimation(targetAnimation);
		if (targetAnimationId < 0)
		{
			LogError("PluginAddNonZeroAllKeysName: Target Animation not found! %s\r\n", targetAnimation);
			return;
		}

		PluginAddNonZeroAllKeys(sourceAnimationId, targetAnimationId, frameId);
	}

	EXPORT_API void PluginAddNonZeroAllKeysAllFrames(int sourceAnimationId, int targetAnimationId)
	{
		PluginStopAnimation(targetAnimationId);
		AnimationBase* sourceAnimation = GetAnimationInstance(sourceAnimationId);
		if (nullptr == sourceAnimation)
		{
			return;
		}
		AnimationBase* targetAnimation = GetAnimationInstance(targetAnimationId);
		if (nullptr == targetAnimation)
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() != targetAnimation->GetDeviceType() ||
			sourceAnimation->GetDeviceId() != targetAnimation->GetDeviceId())
		{
			return;
		}

		if (sourceAnimation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_1D)
		{
			Animation1D* sourceAnimation1D = (Animation1D*)(sourceAnimation);
			Animation1D* targetAnimation1D = (Animation1D*)(targetAnimation);
			vector<FChromaSDKColorFrame1D>& sourceFrames = sourceAnimation1D->GetFrames();
			vector<FChromaSDKColorFrame1D>& targetFrames = targetAnimation1D->GetFrames();
			if (sourceFrames.size() == 0)
			{
				return;
			}
			if (targetFrames.size() == 0)
			{
				return;
			}
			int maxLeds = PluginGetMaxLeds((int)sourceAnimation1D->GetDevice());
			for (int frameId = 0; frameId < int(targetFrames.size()); ++frameId)
			{
				FChromaSDKColorFrame1D& sourceFrame = sourceFrames[frameId % sourceFrames.size()];
				FChromaSDKColorFrame1D& targetFrame = targetFrames[frameId];
				for (int i = 0; i < maxLeds; ++i)
				{
					int color = sourceFrame.Colors[i];
					if (color != 0)
					{
						int sourceRed = color & 0xFF;
						int sourceGreen = (color & 0xFF00) >> 8;
						int sourceBlue = (color & 0xFF0000) >> 16;

						int oldColor = targetFrame.Colors[i];
						int oldRed = oldColor & 0xFF;
						int oldGreen = (oldColor & 0xFF00) >> 8;
						int oldBlue = (oldColor & 0xFF0000) >> 16;

						int red = min(255, max(0, oldRed + sourceRed)) & 0xFF;
						int green = min(255, max(0, oldGreen + sourceGreen)) & 0xFF;
						int blue = min(255, max(0, oldBlue + sourceBlue)) & 0xFF;
						int newColor = red | (green << 8) | (blue << 16);

						targetFrame.Colors[i] = newColor;
					}
				}
			}
		}
		else if (sourceAnimation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_2D)
		{
			Animation2D* sourceAnimation2D = (Animation2D*)(sourceAnimation);
			Animation2D* targetAnimation2D = (Animation2D*)(targetAnimation);
			vector<FChromaSDKColorFrame2D>& sourceFrames = sourceAnimation2D->GetFrames();
			vector<FChromaSDKColorFrame2D>& targetFrames = targetAnimation2D->GetFrames();
			if (sourceFrames.size() == 0)
			{
				return;
			}
			if (targetFrames.size() == 0)
			{
				return;
			}
			int maxRow = PluginGetMaxRow((int)sourceAnimation2D->GetDevice());
			int maxColumn = PluginGetMaxColumn((int)sourceAnimation2D->GetDevice());
			for (int frameId = 0; frameId < int(targetFrames.size()); ++frameId)
			{
				FChromaSDKColorFrame2D& sourceFrame = sourceFrames[frameId % sourceFrames.size()];
				FChromaSDKColorFrame2D& targetFrame = targetFrames[frameId];
				for (int i = 0; i < maxRow; ++i)
				{
					for (int j = 0; j < maxColumn; ++j)
					{
						int color = sourceFrame.Colors[i].Colors[j];
						if (color != 0)
						{
							int sourceRed = color & 0xFF;
							int sourceGreen = (color & 0xFF00) >> 8;
							int sourceBlue = (color & 0xFF0000) >> 16;

							int oldColor = targetFrame.Colors[i].Colors[j];
							int oldRed = oldColor & 0xFF;
							int oldGreen = (oldColor & 0xFF00) >> 8;
							int oldBlue = (oldColor & 0xFF0000) >> 16;

							int red = min(255, max(0, oldRed + sourceRed)) & 0xFF;
							int green = min(255, max(0, oldGreen + sourceGreen)) & 0xFF;
							int blue = min(255, max(0, oldBlue + sourceBlue)) & 0xFF;
							int newColor = red | (green << 8) | (blue << 16);

							targetFrame.Colors[i].Colors[j] = newColor;
						}
					}
				}
			}
		}		
	}

	EXPORT_API void PluginAddNonZeroAllKeysAllFramesName(const char* sourceAnimation, const char* targetAnimation)
	{
		int sourceAnimationId = PluginGetAnimation(sourceAnimation);
		if (sourceAnimationId < 0)
		{
			LogError("PluginAddNonZeroAllKeysAllFramesName: Source Animation not found! %s\r\n", sourceAnimation);
			return;
		}

		int targetAnimationId = PluginGetAnimation(targetAnimation);
		if (targetAnimationId < 0)
		{
			LogError("PluginAddNonZeroAllKeysAllFramesName: Target Animation not found! %s\r\n", targetAnimation);
			return;
		}

		PluginAddNonZeroAllKeysAllFrames(sourceAnimationId, targetAnimationId);
	}

	EXPORT_API double PluginAddNonZeroAllKeysAllFramesNameD(const char* sourceAnimation, const char* targetAnimation)
	{
		PluginAddNonZeroAllKeysAllFramesName(sourceAnimation, targetAnimation);
		return 0;
	}


	EXPORT_API void PluginSubtractNonZeroAllKeys(int sourceAnimationId, int targetAnimationId, int frameId)
	{
		PluginStopAnimation(targetAnimationId);
		AnimationBase* sourceAnimation = GetAnimationInstance(sourceAnimationId);
		if (nullptr == sourceAnimation)
		{
			return;
		}
		AnimationBase* targetAnimation = GetAnimationInstance(targetAnimationId);
		if (nullptr == targetAnimation)
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() != targetAnimation->GetDeviceType() ||
			sourceAnimation->GetDeviceId() != targetAnimation->GetDeviceId())
		{
			return;
		}
		if (frameId < 0)
		{
			return;
		}

		if (sourceAnimation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_1D)
		{
			Animation1D* sourceAnimation1D = (Animation1D*)(sourceAnimation);
			Animation1D* targetAnimation1D = (Animation1D*)(targetAnimation);
			vector<FChromaSDKColorFrame1D>& sourceFrames = sourceAnimation1D->GetFrames();
			vector<FChromaSDKColorFrame1D>& targetFrames = targetAnimation1D->GetFrames();
			if (sourceFrames.size() == 0)
			{
				return;
			}
			if (targetFrames.size() == 0)
			{
				return;
			}
			int maxLeds = PluginGetMaxLeds((int)sourceAnimation1D->GetDevice());
			if (frameId < int(targetFrames.size()))
			{
				FChromaSDKColorFrame1D& sourceFrame = sourceFrames[frameId % sourceFrames.size()];
				FChromaSDKColorFrame1D& targetFrame = targetFrames[frameId];
				for (int i = 0; i < maxLeds; ++i)
				{
					int color = sourceFrame.Colors[i];
					if (color != 0)
					{
						int sourceRed = color & 0xFF;
						int sourceGreen = (color & 0xFF00) >> 8;
						int sourceBlue = (color & 0xFF0000) >> 16;

						int oldColor = targetFrame.Colors[i];
						int oldRed = oldColor & 0xFF;
						int oldGreen = (oldColor & 0xFF00) >> 8;
						int oldBlue = (oldColor & 0xFF0000) >> 16;

						int red = min(255, max(0, oldRed - sourceRed)) & 0xFF;
						int green = min(255, max(0, oldGreen - sourceGreen)) & 0xFF;
						int blue = min(255, max(0, oldBlue - sourceBlue)) & 0xFF;
						int newColor = red | (green << 8) | (blue << 16);

						targetFrame.Colors[i] = newColor;
					}
				}
			}
		}
		else if (sourceAnimation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_2D)
		{
			Animation2D* sourceAnimation2D = (Animation2D*)(sourceAnimation);
			Animation2D* targetAnimation2D = (Animation2D*)(targetAnimation);
			vector<FChromaSDKColorFrame2D>& sourceFrames = sourceAnimation2D->GetFrames();
			vector<FChromaSDKColorFrame2D>& targetFrames = targetAnimation2D->GetFrames();
			if (sourceFrames.size() == 0)
			{
				return;
			}
			if (targetFrames.size() == 0)
			{
				return;
			}
			int maxRow = PluginGetMaxRow((int)sourceAnimation2D->GetDevice());
			int maxColumn = PluginGetMaxColumn((int)sourceAnimation2D->GetDevice());
			if (frameId < int(targetFrames.size()))
			{
				FChromaSDKColorFrame2D& sourceFrame = sourceFrames[frameId % sourceFrames.size()];
				FChromaSDKColorFrame2D& targetFrame = targetFrames[frameId];
				for (int i = 0; i < maxRow; ++i)
				{
					for (int j = 0; j < maxColumn; ++j)
					{
						int color = sourceFrame.Colors[i].Colors[j];
						if (color != 0)
						{
							int sourceRed = color & 0xFF;
							int sourceGreen = (color & 0xFF00) >> 8;
							int sourceBlue = (color & 0xFF0000) >> 16;

							int oldColor = targetFrame.Colors[i].Colors[j];
							int oldRed = oldColor & 0xFF;
							int oldGreen = (oldColor & 0xFF00) >> 8;
							int oldBlue = (oldColor & 0xFF0000) >> 16;

							int red = min(255, max(0, oldRed - sourceRed)) & 0xFF;
							int green = min(255, max(0, oldGreen - sourceGreen)) & 0xFF;
							int blue = min(255, max(0, oldBlue - sourceBlue)) & 0xFF;
							int newColor = red | (green << 8) | (blue << 16);

							targetFrame.Colors[i].Colors[j] = newColor;
						}
					}
				}
			}
		}
	}

	EXPORT_API void PluginSubtractNonZeroAllKeysName(const char* sourceAnimation, const char* targetAnimation, int frameId)
	{
		int sourceAnimationId = PluginGetAnimation(sourceAnimation);
		if (sourceAnimationId < 0)
		{
			LogError("PluginSubtractNonZeroAllKeysName: Source Animation not found! %s\r\n", sourceAnimation);
			return;
		}

		int targetAnimationId = PluginGetAnimation(targetAnimation);
		if (targetAnimationId < 0)
		{
			LogError("PluginSubtractNonZeroAllKeysName: Target Animation not found! %s\r\n", targetAnimation);
			return;
		}

		PluginSubtractNonZeroAllKeys(sourceAnimationId, targetAnimationId, frameId);
	}


	EXPORT_API void PluginSubtractNonZeroAllKeysAllFrames(int sourceAnimationId, int targetAnimationId)
	{
		PluginStopAnimation(targetAnimationId);
		AnimationBase* sourceAnimation = GetAnimationInstance(sourceAnimationId);
		if (nullptr == sourceAnimation)
		{
			return;
		}
		AnimationBase* targetAnimation = GetAnimationInstance(targetAnimationId);
		if (nullptr == targetAnimation)
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() != targetAnimation->GetDeviceType() ||
			sourceAnimation->GetDeviceId() != targetAnimation->GetDeviceId())
		{
			return;
		}

		if (sourceAnimation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_1D)
		{
			Animation1D* sourceAnimation1D = (Animation1D*)(sourceAnimation);
			Animation1D* targetAnimation1D = (Animation1D*)(targetAnimation);
			vector<FChromaSDKColorFrame1D>& sourceFrames = sourceAnimation1D->GetFrames();
			vector<FChromaSDKColorFrame1D>& targetFrames = targetAnimation1D->GetFrames();
			if (sourceFrames.size() == 0)
			{
				return;
			}
			if (targetFrames.size() == 0)
			{
				return;
			}
			int maxLeds = PluginGetMaxLeds((int)sourceAnimation1D->GetDevice());
			for (int frameId = 0; frameId < int(targetFrames.size()); ++frameId)
			{
				FChromaSDKColorFrame1D& sourceFrame = sourceFrames[frameId % sourceFrames.size()];
				FChromaSDKColorFrame1D& targetFrame = targetFrames[frameId];
				for (int i = 0; i < maxLeds; ++i)
				{
					int color = sourceFrame.Colors[i];
					if (color != 0)
					{
						int sourceRed = color & 0xFF;
						int sourceGreen = (color & 0xFF00) >> 8;
						int sourceBlue = (color & 0xFF0000) >> 16;

						int oldColor = targetFrame.Colors[i];
						int oldRed = oldColor & 0xFF;
						int oldGreen = (oldColor & 0xFF00) >> 8;
						int oldBlue = (oldColor & 0xFF0000) >> 16;

						int red = min(255, max(0, oldRed - sourceRed)) & 0xFF;
						int green = min(255, max(0, oldGreen - sourceGreen)) & 0xFF;
						int blue = min(255, max(0, oldBlue - sourceBlue)) & 0xFF;
						int newColor = red | (green << 8) | (blue << 16);

						targetFrame.Colors[i] = newColor;
					}
				}
			}
		}
		else if (sourceAnimation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_2D)
		{
			Animation2D* sourceAnimation2D = (Animation2D*)(sourceAnimation);
			Animation2D* targetAnimation2D = (Animation2D*)(targetAnimation);
			vector<FChromaSDKColorFrame2D>& sourceFrames = sourceAnimation2D->GetFrames();
			vector<FChromaSDKColorFrame2D>& targetFrames = targetAnimation2D->GetFrames();
			if (sourceFrames.size() == 0)
			{
				return;
			}
			if (targetFrames.size() == 0)
			{
				return;
			}
			int maxRow = PluginGetMaxRow((int)sourceAnimation2D->GetDevice());
			int maxColumn = PluginGetMaxColumn((int)sourceAnimation2D->GetDevice());
			for (int frameId = 0; frameId < int(targetFrames.size()); ++frameId)
			{
				FChromaSDKColorFrame2D& sourceFrame = sourceFrames[frameId % sourceFrames.size()];
				FChromaSDKColorFrame2D& targetFrame = targetFrames[frameId];
				for (int i = 0; i < maxRow; ++i)
				{
					for (int j = 0; j < maxColumn; ++j)
					{
						int color = sourceFrame.Colors[i].Colors[j];
						if (color != 0)
						{
							int sourceRed = color & 0xFF;
							int sourceGreen = (color & 0xFF00) >> 8;
							int sourceBlue = (color & 0xFF0000) >> 16;

							int oldColor = targetFrame.Colors[i].Colors[j];
							int oldRed = oldColor & 0xFF;
							int oldGreen = (oldColor & 0xFF00) >> 8;
							int oldBlue = (oldColor & 0xFF0000) >> 16;

							int red = min(255, max(0, oldRed - sourceRed)) & 0xFF;
							int green = min(255, max(0, oldGreen - sourceGreen)) & 0xFF;
							int blue = min(255, max(0, oldBlue - sourceBlue)) & 0xFF;
							int newColor = red | (green << 8) | (blue << 16);

							targetFrame.Colors[i].Colors[j] = newColor;
						}
					}
				}
			}
		}
	}

	EXPORT_API void PluginSubtractNonZeroAllKeysAllFramesName(const char* sourceAnimation, const char* targetAnimation)
	{
		int sourceAnimationId = PluginGetAnimation(sourceAnimation);
		if (sourceAnimationId < 0)
		{
			LogError("PluginSubtractNonZeroAllKeysAllFramesName: Source Animation not found! %s\r\n", sourceAnimation);
			return;
		}

		int targetAnimationId = PluginGetAnimation(targetAnimation);
		if (targetAnimationId < 0)
		{
			LogError("PluginSubtractNonZeroAllKeysAllFramesName: Target Animation not found! %s\r\n", targetAnimation);
			return;
		}

		PluginSubtractNonZeroAllKeysAllFrames(sourceAnimationId, targetAnimationId);
	}

	EXPORT_API double PluginSubtractNonZeroAllKeysAllFramesNameD(const char* sourceAnimation, const char* targetAnimation)
	{
		PluginSubtractNonZeroAllKeysAllFramesName(sourceAnimation, targetAnimation);
		return 0;
	}


	EXPORT_API void PluginCopyNonZeroAllKeysAllFramesOffset(int sourceAnimationId, int targetAnimationId, int offset)
	{
		PluginStopAnimation(targetAnimationId);
		AnimationBase* sourceAnimation = GetAnimationInstance(sourceAnimationId);
		if (nullptr == sourceAnimation)
		{
			return;
		}
		AnimationBase* targetAnimation = GetAnimationInstance(targetAnimationId);
		if (nullptr == targetAnimation)
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() != targetAnimation->GetDeviceType() ||
			sourceAnimation->GetDeviceId() != targetAnimation->GetDeviceId())
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_1D)
		{
			Animation1D* sourceAnimation1D = (Animation1D*)(sourceAnimation);
			Animation1D* targetAnimation1D = (Animation1D*)(targetAnimation);
			vector<FChromaSDKColorFrame1D>& sourceFrames = sourceAnimation1D->GetFrames();
			vector<FChromaSDKColorFrame1D>& targetFrames = targetAnimation1D->GetFrames();
			if (sourceFrames.size() == 0)
			{
				return;
			}
			if (targetFrames.size() == 0)
			{
				return;
			}
			int maxLeds = PluginGetMaxLeds((int)sourceAnimation1D->GetDevice());
			for (int frameId = 0; frameId < int(sourceFrames.size()) && (frameId + offset) < int(targetFrames.size()); ++frameId)
			{
				FChromaSDKColorFrame1D& sourceFrame = sourceFrames[frameId];
				FChromaSDKColorFrame1D& targetFrame = targetFrames[(frameId + offset) % targetFrames.size()];
				for (int i = 0; i < maxLeds; ++i)
				{
					int color = sourceFrame.Colors[i];
					if (color != 0)
					{
						targetFrame.Colors[i] = color;
					}
				}
			}
		}
		else if (sourceAnimation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_2D)
		{
			Animation2D* sourceAnimation2D = (Animation2D*)(sourceAnimation);
			Animation2D* targetAnimation2D = (Animation2D*)(targetAnimation);
			vector<FChromaSDKColorFrame2D>& sourceFrames = sourceAnimation2D->GetFrames();
			vector<FChromaSDKColorFrame2D>& targetFrames = targetAnimation2D->GetFrames();
			if (sourceFrames.size() == 0)
			{
				return;
			}
			if (targetFrames.size() == 0)
			{
				return;
			}
			int maxRow = PluginGetMaxRow((int)sourceAnimation2D->GetDevice());
			int maxColumn = PluginGetMaxColumn((int)sourceAnimation2D->GetDevice());
			for (int frameId = 0; frameId < int(sourceFrames.size()) && (frameId + offset) < int(targetFrames.size()); ++frameId)
			{
				FChromaSDKColorFrame2D& sourceFrame = sourceFrames[frameId];
				FChromaSDKColorFrame2D& targetFrame = targetFrames[(frameId + offset) % targetFrames.size()];
				for (int i = 0; i < maxRow; ++i)
				{
					for (int j = 0; j < maxColumn; ++j)
					{
						int color = sourceFrame.Colors[i].Colors[j];
						if (color != 0)
						{
							targetFrame.Colors[i].Colors[j] = color;
						}
					}
				}
			}
		}
	}

	EXPORT_API void PluginCopyNonZeroAllKeysAllFramesOffsetName(const char* sourceAnimation, const char* targetAnimation, int offset)
	{
		int sourceAnimationId = PluginGetAnimation(sourceAnimation);
		if (sourceAnimationId < 0)
		{
			LogError("PluginCopyNonZeroAllKeysAllFramesOffsetName: Source Animation not found! %s\r\n", sourceAnimation);
			return;
		}

		int targetAnimationId = PluginGetAnimation(targetAnimation);
		if (targetAnimationId < 0)
		{
			LogError("PluginCopyNonZeroAllKeysAllFramesOffsetName: Target Animation not found! %s\r\n", targetAnimation);
			return;
		}

		PluginCopyNonZeroAllKeysAllFramesOffset(sourceAnimationId, targetAnimationId, offset);
	}

	EXPORT_API double PluginCopyNonZeroAllKeysAllFramesOffsetNameD(const char* sourceAnimation, const char* targetAnimation, double offset)
	{
		PluginCopyNonZeroAllKeysAllFramesOffsetName(sourceAnimation, targetAnimation, (int)offset);
		return 0;
	}


	EXPORT_API void PluginCopyNonZeroTargetAllKeysAllFramesOffset(int sourceAnimationId, int targetAnimationId, int offset)
	{
		PluginStopAnimation(targetAnimationId);
		AnimationBase* sourceAnimation = GetAnimationInstance(sourceAnimationId);
		if (nullptr == sourceAnimation)
		{
			return;
		}
		AnimationBase* targetAnimation = GetAnimationInstance(targetAnimationId);
		if (nullptr == targetAnimation)
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() != targetAnimation->GetDeviceType() ||
			sourceAnimation->GetDeviceId() != sourceAnimation->GetDeviceId())
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_1D)
		{
			Animation1D* sourceAnimation1D = (Animation1D*)(sourceAnimation);
			Animation1D* targetAnimation1D = (Animation1D*)(targetAnimation);
			vector<FChromaSDKColorFrame1D>& sourceFrames = sourceAnimation1D->GetFrames();
			vector<FChromaSDKColorFrame1D>& targetFrames = targetAnimation1D->GetFrames();
			if (sourceFrames.size() == 0)
			{
				return;
			}
			if (targetFrames.size() == 0)
			{
				return;
			}
			int maxLeds = PluginGetMaxLeds((int)sourceAnimation1D->GetDevice());
			for (int frameId = 0; frameId < int(sourceFrames.size()); ++frameId)
			{
				FChromaSDKColorFrame1D& sourceFrame = sourceFrames[frameId];
				FChromaSDKColorFrame1D& targetFrame = targetFrames[(frameId + offset) % targetFrames.size()];
				for (int i = 0; i < maxLeds; ++i)
				{
					int color = sourceFrame.Colors[i];
					if (color != 0 &&
						targetFrame.Colors[i] != 0)
					{
						targetFrame.Colors[i] = color;
					}
				}
			}
		}
		else if (sourceAnimation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_2D)
		{
			Animation2D* sourceAnimation2D = (Animation2D*)(sourceAnimation);
			Animation2D* targetAnimation2D = (Animation2D*)(targetAnimation);
			vector<FChromaSDKColorFrame2D>& sourceFrames = sourceAnimation2D->GetFrames();
			vector<FChromaSDKColorFrame2D>& targetFrames = targetAnimation2D->GetFrames();
			if (sourceFrames.size() == 0)
			{
				return;
			}
			if (targetFrames.size() == 0)
			{
				return;
			}
			int maxRow = PluginGetMaxRow((int)sourceAnimation2D->GetDevice());
			int maxColumn = PluginGetMaxColumn((int)sourceAnimation2D->GetDevice());
			for (int frameId = 0; frameId < int(sourceFrames.size()); ++frameId)
			{
				FChromaSDKColorFrame2D& sourceFrame = sourceFrames[frameId];
				FChromaSDKColorFrame2D& targetFrame = targetFrames[(frameId + offset) % targetFrames.size()];
				for (int i = 0; i < maxRow; ++i)
				{
					for (int j = 0; j < maxColumn; ++j)
					{
						int color = sourceFrame.Colors[i].Colors[j];
						if (color != 0 &&
							targetFrame.Colors[i].Colors[j] != 0)
						{
							targetFrame.Colors[i].Colors[j] = color;
						}
					}
				}
			}
		}
	}

	EXPORT_API void PluginCopyNonZeroTargetAllKeysAllFramesOffsetName(const char* sourceAnimation, const char* targetAnimation, int offset)
	{
		int sourceAnimationId = PluginGetAnimation(sourceAnimation);
		if (sourceAnimationId < 0)
		{
			LogError("PluginCopyNonZeroTargetAllKeysAllFramesOffsetName: Source Animation not found! %s\r\n", sourceAnimation);
			return;
		}

		int targetAnimationId = PluginGetAnimation(targetAnimation);
		if (targetAnimationId < 0)
		{
			LogError("PluginCopyNonZeroTargetAllKeysAllFramesOffsetName: Target Animation not found! %s\r\n", targetAnimation);
			return;
		}

		PluginCopyNonZeroTargetAllKeysAllFramesOffset(sourceAnimationId, targetAnimationId, offset);
	}

	EXPORT_API double PluginCopyNonZeroTargetAllKeysAllFramesOffsetNameD(const char* sourceAnimation, const char* targetAnimation, double offset)
	{
		PluginCopyNonZeroTargetAllKeysAllFramesOffsetName(sourceAnimation, targetAnimation, (int)offset);
		return 0;
	}


	EXPORT_API void PluginAddNonZeroAllKeysAllFramesOffset(int sourceAnimationId, int targetAnimationId, int offset)
	{
		PluginStopAnimation(targetAnimationId);
		AnimationBase* sourceAnimation = GetAnimationInstance(sourceAnimationId);
		if (nullptr == sourceAnimation)
		{
			return;
		}
		AnimationBase* targetAnimation = GetAnimationInstance(targetAnimationId);
		if (nullptr == targetAnimation)
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() != targetAnimation->GetDeviceType() ||
			sourceAnimation->GetDeviceId() != targetAnimation->GetDeviceId())
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_1D)
		{
			Animation1D* sourceAnimation1D = (Animation1D*)(sourceAnimation);
			Animation1D* targetAnimation1D = (Animation1D*)(targetAnimation);
			vector<FChromaSDKColorFrame1D>& sourceFrames = sourceAnimation1D->GetFrames();
			vector<FChromaSDKColorFrame1D>& targetFrames = targetAnimation1D->GetFrames();
			if (sourceFrames.size() == 0)
			{
				return;
			}
			if (targetFrames.size() == 0)
			{
				return;
			}
			int maxLeds = PluginGetMaxLeds((int)sourceAnimation1D->GetDevice());
			for (int frameId = 0; frameId < int(sourceFrames.size()); ++frameId)
			{
				FChromaSDKColorFrame1D& sourceFrame = sourceFrames[frameId];
				FChromaSDKColorFrame1D& targetFrame = targetFrames[(frameId + offset) % targetFrames.size()];
				for (int i = 0; i < maxLeds; ++i)
				{
					int color = sourceFrame.Colors[i];
					if (color != 0)
					{
						int sourceRed = color & 0xFF;
						int sourceGreen = (color & 0xFF00) >> 8;
						int sourceBlue = (color & 0xFF0000) >> 16;

						int oldColor = targetFrame.Colors[i];
						int oldRed = oldColor & 0xFF;
						int oldGreen = (oldColor & 0xFF00) >> 8;
						int oldBlue = (oldColor & 0xFF0000) >> 16;

						int red = min(255, max(0, oldRed + sourceRed)) & 0xFF;
						int green = min(255, max(0, oldGreen + sourceGreen)) & 0xFF;
						int blue = min(255, max(0, oldBlue + sourceBlue)) & 0xFF;
						int newColor = red | (green << 8) | (blue << 16);

						targetFrame.Colors[i] = newColor;
					}
				}
			}
		}
		else if (sourceAnimation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_2D)
		{
			Animation2D* sourceAnimation2D = (Animation2D*)(sourceAnimation);
			Animation2D* targetAnimation2D = (Animation2D*)(targetAnimation);
			vector<FChromaSDKColorFrame2D>& sourceFrames = sourceAnimation2D->GetFrames();
			vector<FChromaSDKColorFrame2D>& targetFrames = targetAnimation2D->GetFrames();
			if (sourceFrames.size() == 0)
			{
				return;
			}
			if (targetFrames.size() == 0)
			{
				return;
			}
			int maxRow = PluginGetMaxRow((int)sourceAnimation2D->GetDevice());
			int maxColumn = PluginGetMaxColumn((int)sourceAnimation2D->GetDevice());
			for (int frameId = 0; frameId < int(sourceFrames.size()); ++frameId)
			{
				FChromaSDKColorFrame2D& sourceFrame = sourceFrames[frameId];
				FChromaSDKColorFrame2D& targetFrame = targetFrames[(frameId + offset) % targetFrames.size()];
				for (int i = 0; i < maxRow; ++i)
				{
					for (int j = 0; j < maxColumn; ++j)
					{
						int color = sourceFrame.Colors[i].Colors[j];
						if (color != 0)
						{
							int sourceRed = color & 0xFF;
							int sourceGreen = (color & 0xFF00) >> 8;
							int sourceBlue = (color & 0xFF0000) >> 16;

							int oldColor = targetFrame.Colors[i].Colors[j];
							int oldRed = oldColor & 0xFF;
							int oldGreen = (oldColor & 0xFF00) >> 8;
							int oldBlue = (oldColor & 0xFF0000) >> 16;

							int red = min(255, max(0, oldRed + sourceRed)) & 0xFF;
							int green = min(255, max(0, oldGreen + sourceGreen)) & 0xFF;
							int blue = min(255, max(0, oldBlue + sourceBlue)) & 0xFF;
							int newColor = red | (green << 8) | (blue << 16);

							targetFrame.Colors[i].Colors[j] = newColor;
						}
					}
				}
			}
		}
	}

	EXPORT_API void PluginAddNonZeroAllKeysAllFramesOffsetName(const char* sourceAnimation, const char* targetAnimation, int offset)
	{
		int sourceAnimationId = PluginGetAnimation(sourceAnimation);
		if (sourceAnimationId < 0)
		{
			LogError("PluginAddNonZeroAllKeysAllFramesOffsetName: Source Animation not found! %s\r\n", sourceAnimation);
			return;
		}

		int targetAnimationId = PluginGetAnimation(targetAnimation);
		if (targetAnimationId < 0)
		{
			LogError("PluginAddNonZeroAllKeysAllFramesOffsetName: Target Animation not found! %s\r\n", targetAnimation);
			return;
		}

		PluginAddNonZeroAllKeysAllFramesOffset(sourceAnimationId, targetAnimationId, offset);
	}

	EXPORT_API double PluginAddNonZeroAllKeysAllFramesOffsetNameD(const char* sourceAnimation, const char* targetAnimation, double offset)
	{
		PluginAddNonZeroAllKeysAllFramesOffsetName(sourceAnimation, targetAnimation, (int)offset);
		return 0;
	}


	EXPORT_API void PluginAddNonZeroTargetAllKeysAllFrames(int sourceAnimationId, int targetAnimationId)
	{
		PluginStopAnimation(targetAnimationId);
		AnimationBase* sourceAnimation = GetAnimationInstance(sourceAnimationId);
		if (nullptr == sourceAnimation)
		{
			return;
		}
		AnimationBase* targetAnimation = GetAnimationInstance(targetAnimationId);
		if (nullptr == targetAnimation)
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() != targetAnimation->GetDeviceType() ||
			sourceAnimation->GetDeviceId() != sourceAnimation->GetDeviceId())
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_1D)
		{
			Animation1D* sourceAnimation1D = (Animation1D*)(sourceAnimation);
			Animation1D* targetAnimation1D = (Animation1D*)(targetAnimation);
			vector<FChromaSDKColorFrame1D>& sourceFrames = sourceAnimation1D->GetFrames();
			vector<FChromaSDKColorFrame1D>& targetFrames = targetAnimation1D->GetFrames();
			if (sourceFrames.size() == 0)
			{
				return;
			}
			if (targetFrames.size() == 0)
			{
				return;
			}
			int maxLeds = PluginGetMaxLeds((int)sourceAnimation1D->GetDevice());
			for (int frameId = 0; frameId < int(targetFrames.size()); ++frameId)
			{
				FChromaSDKColorFrame1D& sourceFrame = sourceFrames[frameId % sourceFrames.size()];
				FChromaSDKColorFrame1D& targetFrame = targetFrames[frameId];
				for (int i = 0; i < maxLeds; ++i)
				{
					int color = sourceFrame.Colors[i];
					if (color != 0 &&
						targetFrame.Colors[i] != 0)
					{
						int sourceRed = color & 0xFF;
						int sourceGreen = (color & 0xFF00) >> 8;
						int sourceBlue = (color & 0xFF0000) >> 16;

						int oldColor = targetFrame.Colors[i];
						int oldRed = oldColor & 0xFF;
						int oldGreen = (oldColor & 0xFF00) >> 8;
						int oldBlue = (oldColor & 0xFF0000) >> 16;

						int red = min(255, max(0, oldRed + sourceRed)) & 0xFF;
						int green = min(255, max(0, oldGreen + sourceGreen)) & 0xFF;
						int blue = min(255, max(0, oldBlue + sourceBlue)) & 0xFF;
						int newColor = red | (green << 8) | (blue << 16);

						targetFrame.Colors[i] = newColor;
					}
				}
			}
		}
		else if (sourceAnimation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_2D)
		{
			Animation2D* sourceAnimation2D = (Animation2D*)(sourceAnimation);
			Animation2D* targetAnimation2D = (Animation2D*)(targetAnimation);
			vector<FChromaSDKColorFrame2D>& sourceFrames = sourceAnimation2D->GetFrames();
			vector<FChromaSDKColorFrame2D>& targetFrames = targetAnimation2D->GetFrames();
			if (sourceFrames.size() == 0)
			{
				return;
			}
			if (targetFrames.size() == 0)
			{
				return;
			}
			int maxRow = PluginGetMaxRow((int)sourceAnimation2D->GetDevice());
			int maxColumn = PluginGetMaxColumn((int)sourceAnimation2D->GetDevice());
			for (int frameId = 0; frameId < int(targetFrames.size()); ++frameId)
			{
				FChromaSDKColorFrame2D& sourceFrame = sourceFrames[frameId % sourceFrames.size()];
				FChromaSDKColorFrame2D& targetFrame = targetFrames[frameId];
				for (int i = 0; i < maxRow; ++i)
				{
					for (int j = 0; j < maxColumn; ++j)
					{
						int color = sourceFrame.Colors[i].Colors[j];
						if (color != 0 &&
							targetFrame.Colors[i].Colors[j] != 0)
						{
							int sourceRed = color & 0xFF;
							int sourceGreen = (color & 0xFF00) >> 8;
							int sourceBlue = (color & 0xFF0000) >> 16;

							int oldColor = targetFrame.Colors[i].Colors[j];
							int oldRed = oldColor & 0xFF;
							int oldGreen = (oldColor & 0xFF00) >> 8;
							int oldBlue = (oldColor & 0xFF0000) >> 16;

							int red = min(255, max(0, oldRed + sourceRed)) & 0xFF;
							int green = min(255, max(0, oldGreen + sourceGreen)) & 0xFF;
							int blue = min(255, max(0, oldBlue + sourceBlue)) & 0xFF;
							int newColor = red | (green << 8) | (blue << 16);

							targetFrame.Colors[i].Colors[j] = newColor;
						}
					}
				}
			}
		}
	}

	EXPORT_API void PluginAddNonZeroTargetAllKeysAllFramesName(const char* sourceAnimation, const char* targetAnimation)
	{
		int sourceAnimationId = PluginGetAnimation(sourceAnimation);
		if (sourceAnimationId < 0)
		{
			LogError("PluginAddNonZeroTargetAllKeysAllFramesName: Source Animation not found! %s\r\n", sourceAnimation);
			return;
		}

		int targetAnimationId = PluginGetAnimation(targetAnimation);
		if (targetAnimationId < 0)
		{
			LogError("PluginAddNonZeroTargetAllKeysAllFramesName: Target Animation not found! %s\r\n", targetAnimation);
			return;
		}

		PluginAddNonZeroTargetAllKeysAllFrames(sourceAnimationId, targetAnimationId);
	}

	EXPORT_API double PluginAddNonZeroTargetAllKeysAllFramesNameD(const char* sourceAnimation, const char* targetAnimation)
	{
		PluginAddNonZeroTargetAllKeysAllFramesName(sourceAnimation, targetAnimation);
		return 0;
	}


	EXPORT_API void PluginAddNonZeroTargetAllKeysAllFramesOffset(int sourceAnimationId, int targetAnimationId, int offset)
	{
		PluginStopAnimation(targetAnimationId);
		AnimationBase* sourceAnimation = GetAnimationInstance(sourceAnimationId);
		if (nullptr == sourceAnimation)
		{
			return;
		}
		AnimationBase* targetAnimation = GetAnimationInstance(targetAnimationId);
		if (nullptr == targetAnimation)
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() != targetAnimation->GetDeviceType() ||
			sourceAnimation->GetDeviceId() != sourceAnimation->GetDeviceId())
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_1D)
		{
			Animation1D* sourceAnimation1D = (Animation1D*)(sourceAnimation);
			Animation1D* targetAnimation1D = (Animation1D*)(targetAnimation);
			vector<FChromaSDKColorFrame1D>& sourceFrames = sourceAnimation1D->GetFrames();
			vector<FChromaSDKColorFrame1D>& targetFrames = targetAnimation1D->GetFrames();
			if (sourceFrames.size() == 0)
			{
				return;
			}
			if (targetFrames.size() == 0)
			{
				return;
			}
			int maxLeds = PluginGetMaxLeds(sourceAnimation->GetDeviceId());
			for (int frameId = 0; frameId < int(sourceFrames.size()); ++frameId)
			{
				FChromaSDKColorFrame1D& sourceFrame = sourceFrames[frameId];
				FChromaSDKColorFrame1D& targetFrame = targetFrames[(frameId + offset) % targetFrames.size()];
				for (int i = 0; i < maxLeds; ++i)
				{
					int color = sourceFrame.Colors[i];
					if (color != 0 &&
						targetFrame.Colors[i] != 0)
					{
						int sourceRed = color & 0xFF;
						int sourceGreen = (color & 0xFF00) >> 8;
						int sourceBlue = (color & 0xFF0000) >> 16;

						int oldColor = targetFrame.Colors[i];
						int oldRed = oldColor & 0xFF;
						int oldGreen = (oldColor & 0xFF00) >> 8;
						int oldBlue = (oldColor & 0xFF0000) >> 16;

						int red = min(255, max(0, oldRed + sourceRed)) & 0xFF;
						int green = min(255, max(0, oldGreen + sourceGreen)) & 0xFF;
						int blue = min(255, max(0, oldBlue + sourceBlue)) & 0xFF;
						int newColor = red | (green << 8) | (blue << 16);

						targetFrame.Colors[i] = newColor;
					}
				}
			}
		}
		else if (sourceAnimation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_2D)
		{
			Animation2D* sourceAnimation2D = (Animation2D*)(sourceAnimation);
			Animation2D* targetAnimation2D = (Animation2D*)(targetAnimation);
			vector<FChromaSDKColorFrame2D>& sourceFrames = sourceAnimation2D->GetFrames();
			vector<FChromaSDKColorFrame2D>& targetFrames = targetAnimation2D->GetFrames();
			if (sourceFrames.size() == 0)
			{
				return;
			}
			if (targetFrames.size() == 0)
			{
				return;
			}
			int maxRow = PluginGetMaxRow(sourceAnimation->GetDeviceId());
			int maxColumn = PluginGetMaxColumn(sourceAnimation->GetDeviceId());
			for (int frameId = 0; frameId < int(sourceFrames.size()); ++frameId)
			{
				FChromaSDKColorFrame2D& sourceFrame = sourceFrames[frameId];
				FChromaSDKColorFrame2D& targetFrame = targetFrames[(frameId + offset) % targetFrames.size()];
				for (int i = 0; i < maxRow; ++i)
				{
					for (int j = 0; j < maxColumn; ++j)
					{
						int color = sourceFrame.Colors[i].Colors[j];
						if (color != 0 &&
							targetFrame.Colors[i].Colors[j] != 0)
						{
							int sourceRed = color & 0xFF;
							int sourceGreen = (color & 0xFF00) >> 8;
							int sourceBlue = (color & 0xFF0000) >> 16;

							int oldColor = targetFrame.Colors[i].Colors[j];
							int oldRed = oldColor & 0xFF;
							int oldGreen = (oldColor & 0xFF00) >> 8;
							int oldBlue = (oldColor & 0xFF0000) >> 16;

							int red = min(255, max(0, oldRed + sourceRed)) & 0xFF;
							int green = min(255, max(0, oldGreen + sourceGreen)) & 0xFF;
							int blue = min(255, max(0, oldBlue + sourceBlue)) & 0xFF;
							int newColor = red | (green << 8) | (blue << 16);

							targetFrame.Colors[i].Colors[j] = newColor;
						}
					}
				}
			}
		}
	}

	EXPORT_API void PluginAddNonZeroTargetAllKeysAllFramesOffsetName(const char* sourceAnimation, const char* targetAnimation, int offset)
	{
		int sourceAnimationId = PluginGetAnimation(sourceAnimation);
		if (sourceAnimationId < 0)
		{
			LogError("PluginAddNonZeroTargetAllKeysAllFramesOffsetName: Source Animation not found! %s\r\n", sourceAnimation);
			return;
		}

		int targetAnimationId = PluginGetAnimation(targetAnimation);
		if (targetAnimationId < 0)
		{
			LogError("PluginAddNonZeroTargetAllKeysAllFramesOffsetName: Target Animation not found! %s\r\n", targetAnimation);
			return;
		}

		PluginAddNonZeroTargetAllKeysAllFramesOffset(sourceAnimationId, targetAnimationId, offset);
	}

	EXPORT_API double PluginAddNonZeroTargetAllKeysAllFramesOffsetNameD(const char* sourceAnimation, const char* targetAnimation, double offset)
	{
		PluginAddNonZeroTargetAllKeysAllFramesOffsetName(sourceAnimation, targetAnimation, (int)offset);
		return 0;
	}


	EXPORT_API void PluginSubtractNonZeroAllKeysAllFramesOffset(int sourceAnimationId, int targetAnimationId, int offset)
	{
		PluginStopAnimation(targetAnimationId);
		AnimationBase* sourceAnimation = GetAnimationInstance(sourceAnimationId);
		if (nullptr == sourceAnimation)
		{
			return;
		}
		AnimationBase* targetAnimation = GetAnimationInstance(targetAnimationId);
		if (nullptr == targetAnimation)
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() != targetAnimation->GetDeviceType() ||
			sourceAnimation->GetDeviceId() != targetAnimation->GetDeviceId())
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_1D)
		{
			Animation1D* sourceAnimation1D = (Animation1D*)(sourceAnimation);
			Animation1D* targetAnimation1D = (Animation1D*)(targetAnimation);
			vector<FChromaSDKColorFrame1D>& sourceFrames = sourceAnimation1D->GetFrames();
			vector<FChromaSDKColorFrame1D>& targetFrames = targetAnimation1D->GetFrames();
			if (sourceFrames.size() == 0)
			{
				return;
			}
			if (targetFrames.size() == 0)
			{
				return;
			}
			int maxLeds = PluginGetMaxLeds((int)sourceAnimation1D->GetDevice());
			for (int frameId = 0; frameId < int(sourceFrames.size()); ++frameId)
			{
				FChromaSDKColorFrame1D& sourceFrame = sourceFrames[frameId];
				FChromaSDKColorFrame1D& targetFrame = targetFrames[(frameId + offset) % targetFrames.size()];
				for (int i = 0; i < maxLeds; ++i)
				{
					int color = sourceFrame.Colors[i];
					if (color != 0)
					{
						int sourceRed = color & 0xFF;
						int sourceGreen = (color & 0xFF00) >> 8;
						int sourceBlue = (color & 0xFF0000) >> 16;

						int oldColor = targetFrame.Colors[i];
						int oldRed = oldColor & 0xFF;
						int oldGreen = (oldColor & 0xFF00) >> 8;
						int oldBlue = (oldColor & 0xFF0000) >> 16;

						int red = min(255, max(0, oldRed - sourceRed)) & 0xFF;
						int green = min(255, max(0, oldGreen - sourceGreen)) & 0xFF;
						int blue = min(255, max(0, oldBlue - sourceBlue)) & 0xFF;
						int newColor = red | (green << 8) | (blue << 16);

						targetFrame.Colors[i] = newColor;
					}
				}
			}
		}
		else if (sourceAnimation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_2D)
		{
			Animation2D* sourceAnimation2D = (Animation2D*)(sourceAnimation);
			Animation2D* targetAnimation2D = (Animation2D*)(targetAnimation);
			vector<FChromaSDKColorFrame2D>& sourceFrames = sourceAnimation2D->GetFrames();
			vector<FChromaSDKColorFrame2D>& targetFrames = targetAnimation2D->GetFrames();
			if (sourceFrames.size() == 0)
			{
				return;
			}
			if (targetFrames.size() == 0)
			{
				return;
			}
			int maxRow = PluginGetMaxRow((int)sourceAnimation2D->GetDevice());
			int maxColumn = PluginGetMaxColumn((int)sourceAnimation2D->GetDevice());
			for (int frameId = 0; frameId < int(sourceFrames.size()); ++frameId)
			{
				FChromaSDKColorFrame2D& sourceFrame = sourceFrames[frameId];
				FChromaSDKColorFrame2D& targetFrame = targetFrames[(frameId + offset) % targetFrames.size()];
				for (int i = 0; i < maxRow; ++i)
				{
					for (int j = 0; j < maxColumn; ++j)
					{
						int color = sourceFrame.Colors[i].Colors[j];
						if (color != 0)
						{
							int sourceRed = color & 0xFF;
							int sourceGreen = (color & 0xFF00) >> 8;
							int sourceBlue = (color & 0xFF0000) >> 16;

							int oldColor = targetFrame.Colors[i].Colors[j];
							int oldRed = oldColor & 0xFF;
							int oldGreen = (oldColor & 0xFF00) >> 8;
							int oldBlue = (oldColor & 0xFF0000) >> 16;

							int red = min(255, max(0, oldRed - sourceRed)) & 0xFF;
							int green = min(255, max(0, oldGreen - sourceGreen)) & 0xFF;
							int blue = min(255, max(0, oldBlue - sourceBlue)) & 0xFF;
							int newColor = red | (green << 8) | (blue << 16);

							targetFrame.Colors[i].Colors[j] = newColor;
						}
					}
				}
			}
		}
	}

	EXPORT_API void PluginSubtractNonZeroAllKeysAllFramesOffsetName(const char* sourceAnimation, const char* targetAnimation, int offset)
	{
		int sourceAnimationId = PluginGetAnimation(sourceAnimation);
		if (sourceAnimationId < 0)
		{
			LogError("PluginSubtractNonZeroAllKeysAllFramesOffsetName: Source Animation not found! %s\r\n", sourceAnimation);
			return;
		}

		int targetAnimationId = PluginGetAnimation(targetAnimation);
		if (targetAnimationId < 0)
		{
			LogError("PluginSubtractNonZeroAllKeysAllFramesOffsetName: Target Animation not found! %s\r\n", targetAnimation);
			return;
		}

		PluginSubtractNonZeroAllKeysAllFramesOffset(sourceAnimationId, targetAnimationId, offset);
	}

	EXPORT_API double PluginSubtractNonZeroAllKeysAllFramesOffsetNameD(const char* sourceAnimation, const char* targetAnimation, double offset)
	{
		PluginSubtractNonZeroAllKeysAllFramesOffsetName(sourceAnimation, targetAnimation, (int)offset);
		return 0;
	}


	EXPORT_API void PluginSubtractNonZeroTargetAllKeysAllFrames(int sourceAnimationId, int targetAnimationId)
	{
		PluginStopAnimation(targetAnimationId);
		AnimationBase* sourceAnimation = GetAnimationInstance(sourceAnimationId);
		if (nullptr == sourceAnimation)
		{
			return;
		}
		AnimationBase* targetAnimation = GetAnimationInstance(targetAnimationId);
		if (nullptr == targetAnimation)
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() != targetAnimation->GetDeviceType() ||
			sourceAnimation->GetDeviceId() != sourceAnimation->GetDeviceId())
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_1D)
		{
			Animation1D* sourceAnimation1D = (Animation1D*)(sourceAnimation);
			Animation1D* targetAnimation1D = (Animation1D*)(targetAnimation);
			vector<FChromaSDKColorFrame1D>& sourceFrames = sourceAnimation1D->GetFrames();
			vector<FChromaSDKColorFrame1D>& targetFrames = targetAnimation1D->GetFrames();
			if (sourceFrames.size() == 0)
			{
				return;
			}
			if (targetFrames.size() == 0)
			{
				return;
			}
			int maxLeds = PluginGetMaxLeds((int)sourceAnimation1D->GetDevice());
			for (int frameId = 0; frameId < int(targetFrames.size()); ++frameId)
			{
				FChromaSDKColorFrame1D& sourceFrame = sourceFrames[frameId % sourceFrames.size()];
				FChromaSDKColorFrame1D& targetFrame = targetFrames[frameId];
				for (int i = 0; i < maxLeds; ++i)
				{
					int color = sourceFrame.Colors[i];
					if (color != 0 &&
						targetFrame.Colors[i] != 0)
					{
						int sourceRed = color & 0xFF;
						int sourceGreen = (color & 0xFF00) >> 8;
						int sourceBlue = (color & 0xFF0000) >> 16;

						int oldColor = targetFrame.Colors[i];
						int oldRed = oldColor & 0xFF;
						int oldGreen = (oldColor & 0xFF00) >> 8;
						int oldBlue = (oldColor & 0xFF0000) >> 16;

						int red = min(255, max(0, oldRed - sourceRed)) & 0xFF;
						int green = min(255, max(0, oldGreen - sourceGreen)) & 0xFF;
						int blue = min(255, max(0, oldBlue - sourceBlue)) & 0xFF;
						int newColor = red | (green << 8) | (blue << 16);

						targetFrame.Colors[i] = newColor;
					}
				}
			}
		}
		else if (sourceAnimation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_2D)
		{
			Animation2D* sourceAnimation2D = (Animation2D*)(sourceAnimation);
			Animation2D* targetAnimation2D = (Animation2D*)(targetAnimation);
			vector<FChromaSDKColorFrame2D>& sourceFrames = sourceAnimation2D->GetFrames();
			vector<FChromaSDKColorFrame2D>& targetFrames = targetAnimation2D->GetFrames();
			if (sourceFrames.size() == 0)
			{
				return;
			}
			if (targetFrames.size() == 0)
			{
				return;
			}
			int maxRow = PluginGetMaxRow((int)sourceAnimation2D->GetDevice());
			int maxColumn = PluginGetMaxColumn((int)sourceAnimation2D->GetDevice());
			for (int frameId = 0; frameId < int(targetFrames.size()); ++frameId)
			{
				FChromaSDKColorFrame2D& sourceFrame = sourceFrames[frameId % sourceFrames.size()];
				FChromaSDKColorFrame2D& targetFrame = targetFrames[frameId];
				for (int i = 0; i < maxRow; ++i)
				{
					for (int j = 0; j < maxColumn; ++j)
					{
						int color = sourceFrame.Colors[i].Colors[j];
						if (color != 0 &&
							targetFrame.Colors[i].Colors[j] != 0)
						{
							int sourceRed = color & 0xFF;
							int sourceGreen = (color & 0xFF00) >> 8;
							int sourceBlue = (color & 0xFF0000) >> 16;

							int oldColor = targetFrame.Colors[i].Colors[j];
							int oldRed = oldColor & 0xFF;
							int oldGreen = (oldColor & 0xFF00) >> 8;
							int oldBlue = (oldColor & 0xFF0000) >> 16;

							int red = min(255, max(0, oldRed - sourceRed)) & 0xFF;
							int green = min(255, max(0, oldGreen - sourceGreen)) & 0xFF;
							int blue = min(255, max(0, oldBlue - sourceBlue)) & 0xFF;
							int newColor = red | (green << 8) | (blue << 16);

							targetFrame.Colors[i].Colors[j] = newColor;
						}
					}
				}
			}
		}
	}

	EXPORT_API void PluginSubtractNonZeroTargetAllKeysAllFramesName(const char* sourceAnimation, const char* targetAnimation)
	{
		int sourceAnimationId = PluginGetAnimation(sourceAnimation);
		if (sourceAnimationId < 0)
		{
			LogError("PluginSubtractNonZeroTargetAllKeysAllFramesName: Source Animation not found! %s\r\n", sourceAnimation);
			return;
		}

		int targetAnimationId = PluginGetAnimation(targetAnimation);
		if (targetAnimationId < 0)
		{
			LogError("PluginSubtractNonZeroTargetAllKeysAllFramesName: Target Animation not found! %s\r\n", targetAnimation);
			return;
		}

		PluginSubtractNonZeroTargetAllKeysAllFrames(sourceAnimationId, targetAnimationId);
	}

	EXPORT_API double PluginSubtractNonZeroTargetAllKeysAllFramesNameD(const char* sourceAnimation, const char* targetAnimation)
	{
		PluginSubtractNonZeroTargetAllKeysAllFramesName(sourceAnimation, targetAnimation);
		return 0;
	}


	EXPORT_API void PluginSubtractNonZeroTargetAllKeysAllFramesOffset(int sourceAnimationId, int targetAnimationId, int offset)
	{
		PluginStopAnimation(targetAnimationId);
		AnimationBase* sourceAnimation = GetAnimationInstance(sourceAnimationId);
		if (nullptr == sourceAnimation)
		{
			return;
		}
		AnimationBase* targetAnimation = GetAnimationInstance(targetAnimationId);
		if (nullptr == targetAnimation)
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() != targetAnimation->GetDeviceType() ||
			sourceAnimation->GetDeviceId() != sourceAnimation->GetDeviceId())
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_1D)
		{
			Animation1D* sourceAnimation1D = (Animation1D*)(sourceAnimation);
			Animation1D* targetAnimation1D = (Animation1D*)(targetAnimation);
			vector<FChromaSDKColorFrame1D>& sourceFrames = sourceAnimation1D->GetFrames();
			vector<FChromaSDKColorFrame1D>& targetFrames = targetAnimation1D->GetFrames();
			if (sourceFrames.size() == 0)
			{
				return;
			}
			if (targetFrames.size() == 0)
			{
				return;
			}
			int maxLeds = PluginGetMaxLeds((int)sourceAnimation1D->GetDevice());
			for (int frameId = 0; frameId < int(sourceFrames.size()); ++frameId)
			{
				FChromaSDKColorFrame1D& sourceFrame = sourceFrames[frameId];
				FChromaSDKColorFrame1D& targetFrame = targetFrames[(frameId + offset) % targetFrames.size()];
				for (int i = 0; i < maxLeds; ++i)
				{
					int color = sourceFrame.Colors[i];
					if (color != 0 &&
						targetFrame.Colors[i] != 0)
					{
						int sourceRed = color & 0xFF;
						int sourceGreen = (color & 0xFF00) >> 8;
						int sourceBlue = (color & 0xFF0000) >> 16;

						int oldColor = targetFrame.Colors[i];
						int oldRed = oldColor & 0xFF;
						int oldGreen = (oldColor & 0xFF00) >> 8;
						int oldBlue = (oldColor & 0xFF0000) >> 16;

						int red = min(255, max(0, oldRed - sourceRed)) & 0xFF;
						int green = min(255, max(0, oldGreen - sourceGreen)) & 0xFF;
						int blue = min(255, max(0, oldBlue - sourceBlue)) & 0xFF;
						int newColor = red | (green << 8) | (blue << 16);

						targetFrame.Colors[i] = newColor;
					}
				}
			}
		}
		else if (sourceAnimation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_2D)
		{
			Animation2D* sourceAnimation2D = (Animation2D*)(sourceAnimation);
			Animation2D* targetAnimation2D = (Animation2D*)(targetAnimation);
			vector<FChromaSDKColorFrame2D>& sourceFrames = sourceAnimation2D->GetFrames();
			vector<FChromaSDKColorFrame2D>& targetFrames = targetAnimation2D->GetFrames();
			if (sourceFrames.size() == 0)
			{
				return;
			}
			if (targetFrames.size() == 0)
			{
				return;
			}
			int maxRow = PluginGetMaxRow((int)sourceAnimation2D->GetDevice());
			int maxColumn = PluginGetMaxColumn((int)sourceAnimation2D->GetDevice());
			for (int frameId = 0; frameId < int(sourceFrames.size()); ++frameId)
			{
				FChromaSDKColorFrame2D& sourceFrame = sourceFrames[frameId];
				FChromaSDKColorFrame2D& targetFrame = targetFrames[(frameId + offset) % targetFrames.size()];
				for (int i = 0; i < maxRow; ++i)
				{
					for (int j = 0; j < maxColumn; ++j)
					{
						int color = sourceFrame.Colors[i].Colors[j];
						if (color != 0 &&
							targetFrame.Colors[i].Colors[j] != 0)
						{
							int sourceRed = color & 0xFF;
							int sourceGreen = (color & 0xFF00) >> 8;
							int sourceBlue = (color & 0xFF0000) >> 16;

							int oldColor = targetFrame.Colors[i].Colors[j];
							int oldRed = oldColor & 0xFF;
							int oldGreen = (oldColor & 0xFF00) >> 8;
							int oldBlue = (oldColor & 0xFF0000) >> 16;

							int red = min(255, max(0, oldRed - sourceRed)) & 0xFF;
							int green = min(255, max(0, oldGreen - sourceGreen)) & 0xFF;
							int blue = min(255, max(0, oldBlue - sourceBlue)) & 0xFF;
							int newColor = red | (green << 8) | (blue << 16);

							targetFrame.Colors[i].Colors[j] = newColor;
						}
					}
				}
			}
		}
	}

	EXPORT_API void PluginSubtractNonZeroTargetAllKeysAllFramesOffsetName(const char* sourceAnimation, const char* targetAnimation, int offset)
	{
		int sourceAnimationId = PluginGetAnimation(sourceAnimation);
		if (sourceAnimationId < 0)
		{
			LogError("PluginSubtractNonZeroTargetAllKeysAllFramesOffsetName: Source Animation not found! %s\r\n", sourceAnimation);
			return;
		}

		int targetAnimationId = PluginGetAnimation(targetAnimation);
		if (targetAnimationId < 0)
		{
			LogError("PluginSubtractNonZeroTargetAllKeysAllFramesOffsetName: Target Animation not found! %s\r\n", targetAnimation);
			return;
		}

		PluginSubtractNonZeroTargetAllKeysAllFramesOffset(sourceAnimationId, targetAnimationId, offset);
	}

	EXPORT_API double PluginSubtractNonZeroTargetAllKeysAllFramesOffsetNameD(const char* sourceAnimation, const char* targetAnimation, double offset)
	{
		PluginSubtractNonZeroTargetAllKeysAllFramesOffsetName(sourceAnimation, targetAnimation, (int)offset);
		return 0;
	}

	EXPORT_API void PluginCopyZeroAllKeys(int sourceAnimationId, int targetAnimationId, int frameId)
	{
		PluginStopAnimation(targetAnimationId);
		AnimationBase* sourceAnimation = GetAnimationInstance(sourceAnimationId);
		if (nullptr == sourceAnimation)
		{
			return;
		}
		AnimationBase* targetAnimation = GetAnimationInstance(targetAnimationId);
		if (nullptr == targetAnimation)
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() != targetAnimation->GetDeviceType() ||
			sourceAnimation->GetDeviceId() != targetAnimation->GetDeviceId())
		{
			return;
		}
		if (frameId < 0)
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_1D)
		{
			Animation1D* sourceAnimation1D = (Animation1D*)(sourceAnimation);
			Animation1D* targetAnimation1D = (Animation1D*)(targetAnimation);
			vector<FChromaSDKColorFrame1D>& sourceFrames = sourceAnimation1D->GetFrames();
			vector<FChromaSDKColorFrame1D>& targetFrames = targetAnimation1D->GetFrames();
			if (sourceFrames.size() == 0)
			{
				return;
			}
			if (targetFrames.size() == 0)
			{
				return;
			}
			int maxLeds = PluginGetMaxLeds((int)sourceAnimation1D->GetDevice());
			if (frameId < int(targetFrames.size()))
			{
				FChromaSDKColorFrame1D& sourceFrame = sourceFrames[frameId % sourceFrames.size()];
				FChromaSDKColorFrame1D& targetFrame = targetFrames[frameId];
				for (int i = 0; i < maxLeds; ++i)
				{
					int color = sourceFrame.Colors[i];
					if (color == 0)
					{
						targetFrame.Colors[i] = color;
					}
				}
			}
		}
		else if (sourceAnimation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_2D)
		{
			Animation2D* sourceAnimation2D = (Animation2D*)(sourceAnimation);
			Animation2D* targetAnimation2D = (Animation2D*)(targetAnimation);
			vector<FChromaSDKColorFrame2D>& sourceFrames = sourceAnimation2D->GetFrames();
			vector<FChromaSDKColorFrame2D>& targetFrames = targetAnimation2D->GetFrames();
			if (sourceFrames.size() == 0)
			{
				return;
			}
			if (targetFrames.size() == 0)
			{
				return;
			}
			int maxRow = PluginGetMaxRow((int)sourceAnimation2D->GetDevice());
			int maxColumn = PluginGetMaxColumn((int)sourceAnimation2D->GetDevice());
			if (frameId < int(targetFrames.size()))
			{
				FChromaSDKColorFrame2D& sourceFrame = sourceFrames[frameId % sourceFrames.size()];
				FChromaSDKColorFrame2D& targetFrame = targetFrames[frameId];
				for (int i = 0; i < maxRow; ++i)
				{
					for (int j = 0; j < maxColumn; ++j)
					{
						int color = sourceFrame.Colors[i].Colors[j];
						if (color == 0)
						{
							targetFrame.Colors[i].Colors[j] = color;
						}
					}
				}
			}
		}
	}

	EXPORT_API void PluginCopyZeroAllKeysName(const char* sourceAnimation, const char* targetAnimation, int frameId)
	{
		int sourceAnimationId = PluginGetAnimation(sourceAnimation);
		if (sourceAnimationId < 0)
		{
			LogError("PluginCopyZeroAllKeysName: Source Animation not found! %s\r\n", sourceAnimation);
			return;
		}

		int targetAnimationId = PluginGetAnimation(targetAnimation);
		if (targetAnimationId < 0)
		{
			LogError("PluginCopyZeroAllKeysName: Target Animation not found! %s\r\n", targetAnimation);
			return;
		}

		PluginCopyZeroAllKeys(sourceAnimationId, targetAnimationId, frameId);
	}

	EXPORT_API void PluginCopyZeroAllKeysAllFrames(int sourceAnimationId, int targetAnimationId)
	{
		PluginStopAnimation(targetAnimationId);
		AnimationBase* sourceAnimation = GetAnimationInstance(sourceAnimationId);
		if (nullptr == sourceAnimation)
		{
			return;
		}
		AnimationBase* targetAnimation = GetAnimationInstance(targetAnimationId);
		if (nullptr == targetAnimation)
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() != targetAnimation->GetDeviceType() ||
			sourceAnimation->GetDeviceId() != targetAnimation->GetDeviceId())
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_1D)
		{
			Animation1D* sourceAnimation1D = (Animation1D*)(sourceAnimation);
			Animation1D* targetAnimation1D = (Animation1D*)(targetAnimation);
			vector<FChromaSDKColorFrame1D>& sourceFrames = sourceAnimation1D->GetFrames();
			vector<FChromaSDKColorFrame1D>& targetFrames = targetAnimation1D->GetFrames();
			if (sourceFrames.size() == 0)
			{
				return;
			}
			if (targetFrames.size() == 0)
			{
				return;
			}
			int maxLeds = PluginGetMaxLeds((int)sourceAnimation1D->GetDevice());
			for (int frameId = 0; frameId < int(targetFrames.size()); ++frameId)
			{
				FChromaSDKColorFrame1D& sourceFrame = sourceFrames[frameId % sourceFrames.size()];
				FChromaSDKColorFrame1D& targetFrame = targetFrames[frameId];
				for (int i = 0; i < maxLeds; ++i)
				{
					int color = sourceFrame.Colors[i];
					if (color == 0)
					{
						targetFrame.Colors[i] = color;
					}
				}
			}
		}
		else if (sourceAnimation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_2D)
		{
			Animation2D* sourceAnimation2D = (Animation2D*)(sourceAnimation);
			Animation2D* targetAnimation2D = (Animation2D*)(targetAnimation);
			vector<FChromaSDKColorFrame2D>& sourceFrames = sourceAnimation2D->GetFrames();
			vector<FChromaSDKColorFrame2D>& targetFrames = targetAnimation2D->GetFrames();
			if (sourceFrames.size() == 0)
			{
				return;
			}
			if (targetFrames.size() == 0)
			{
				return;
			}
			int maxRow = PluginGetMaxRow((int)sourceAnimation2D->GetDevice());
			int maxColumn = PluginGetMaxColumn((int)sourceAnimation2D->GetDevice());
			for (int frameId = 0; frameId < int(targetFrames.size()); ++frameId)
			{
				FChromaSDKColorFrame2D& sourceFrame = sourceFrames[frameId % sourceFrames.size()];
				FChromaSDKColorFrame2D& targetFrame = targetFrames[frameId];
				for (int i = 0; i < maxRow; ++i)
				{
					for (int j = 0; j < maxColumn; ++j)
					{
						int color = sourceFrame.Colors[i].Colors[j];
						if (color == 0)
						{
							targetFrame.Colors[i].Colors[j] = color;
						}
					}
				}
			}
		}
	}

	EXPORT_API void PluginCopyZeroAllKeysAllFramesName(const char* sourceAnimation, const char* targetAnimation)
	{
		int sourceAnimationId = PluginGetAnimation(sourceAnimation);
		if (sourceAnimationId < 0)
		{
			LogError("PluginCopyZeroAllKeysAllFramesName: Source Animation not found! %s\r\n", sourceAnimation);
			return;
		}

		int targetAnimationId = PluginGetAnimation(targetAnimation);
		if (targetAnimationId < 0)
		{
			LogError("PluginCopyZeroAllKeysAllFramesName: Target Animation not found! %s\r\n", targetAnimation);
			return;
		}

		PluginCopyZeroAllKeysAllFrames(sourceAnimationId, targetAnimationId);
	}

	EXPORT_API double PluginCopyZeroAllKeysAllFramesNameD(const char* sourceAnimation, const char* targetAnimation)
	{
		PluginCopyZeroAllKeysAllFramesName(sourceAnimation, targetAnimation);
		return 0;
	}

	EXPORT_API void PluginCopyZeroAllKeysOffset(int sourceAnimationId, int targetAnimationId, int frameId, int offset)
	{
		PluginStopAnimation(targetAnimationId);
		AnimationBase* sourceAnimation = GetAnimationInstance(sourceAnimationId);
		if (nullptr == sourceAnimation)
		{
			return;
		}
		AnimationBase* targetAnimation = GetAnimationInstance(targetAnimationId);
		if (nullptr == targetAnimation)
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() != targetAnimation->GetDeviceType() ||
			sourceAnimation->GetDeviceId() != targetAnimation->GetDeviceId())
		{
			return;
		}
		if (frameId < 0)
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_1D)
		{
			Animation1D* sourceAnimation1D = (Animation1D*)(sourceAnimation);
			Animation1D* targetAnimation1D = (Animation1D*)(targetAnimation);
			vector<FChromaSDKColorFrame1D>& sourceFrames = sourceAnimation1D->GetFrames();
			vector<FChromaSDKColorFrame1D>& targetFrames = targetAnimation1D->GetFrames();
			if (sourceFrames.size() == 0)
			{
				return;
			}
			if (targetFrames.size() == 0)
			{
				return;
			}
			int maxLeds = PluginGetMaxLeds((int)sourceAnimation1D->GetDevice());
			if (frameId < int(sourceFrames.size()))
			{
				FChromaSDKColorFrame1D& sourceFrame = sourceFrames[frameId];
				FChromaSDKColorFrame1D& targetFrame = targetFrames[(frameId + offset) % targetFrames.size()];
				for (int i = 0; i < maxLeds; ++i)
				{
					int color = sourceFrame.Colors[i];
					if (color == 0)
					{
						targetFrame.Colors[i] = color;
					}
				}
			}
		}
		else if (sourceAnimation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_2D)
		{
			Animation2D* sourceAnimation2D = (Animation2D*)(sourceAnimation);
			Animation2D* targetAnimation2D = (Animation2D*)(targetAnimation);
			vector<FChromaSDKColorFrame2D>& sourceFrames = sourceAnimation2D->GetFrames();
			vector<FChromaSDKColorFrame2D>& targetFrames = targetAnimation2D->GetFrames();
			if (sourceFrames.size() == 0)
			{
				return;
			}
			if (targetFrames.size() == 0)
			{
				return;
			}
			int maxRow = PluginGetMaxRow((int)sourceAnimation2D->GetDevice());
			int maxColumn = PluginGetMaxColumn((int)sourceAnimation2D->GetDevice());
			if (frameId < int(sourceFrames.size()))
			{
				FChromaSDKColorFrame2D& sourceFrame = sourceFrames[frameId];
				FChromaSDKColorFrame2D& targetFrame = targetFrames[(frameId + offset) % targetFrames.size()];
				for (int i = 0; i < maxRow; ++i)
				{
					for (int j = 0; j < maxColumn; ++j)
					{
						int color = sourceFrame.Colors[i].Colors[j];
						if (color == 0)
						{
							targetFrame.Colors[i].Colors[j] = color;
						}
					}
				}
			}
		}
	}

	EXPORT_API void PluginCopyZeroAllKeysOffsetName(const char* sourceAnimation, const char* targetAnimation, int frameId, int offset)
	{
		int sourceAnimationId = PluginGetAnimation(sourceAnimation);
		if (sourceAnimationId < 0)
		{
			LogError("PluginCopyZeroAllKeysOffsetName: Source Animation not found! %s\r\n", sourceAnimation);
			return;
		}

		int targetAnimationId = PluginGetAnimation(targetAnimation);
		if (targetAnimationId < 0)
		{
			LogError("PluginCopyZeroAllKeysOffsetName: Target Animation not found! %s\r\n", targetAnimation);
			return;
		}

		PluginCopyZeroAllKeysOffset(sourceAnimationId, targetAnimationId, frameId, offset);
	}

	EXPORT_API void PluginCopyZeroAllKeysAllFramesOffset(int sourceAnimationId, int targetAnimationId, int offset)
	{
		PluginStopAnimation(targetAnimationId);
		AnimationBase* sourceAnimation = GetAnimationInstance(sourceAnimationId);
		if (nullptr == sourceAnimation)
		{
			return;
		}
		AnimationBase* targetAnimation = GetAnimationInstance(targetAnimationId);
		if (nullptr == targetAnimation)
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() != targetAnimation->GetDeviceType() ||
			sourceAnimation->GetDeviceId() != targetAnimation->GetDeviceId())
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_1D)
		{
			Animation1D* sourceAnimation1D = (Animation1D*)(sourceAnimation);
			Animation1D* targetAnimation1D = (Animation1D*)(targetAnimation);
			vector<FChromaSDKColorFrame1D>& sourceFrames = sourceAnimation1D->GetFrames();
			vector<FChromaSDKColorFrame1D>& targetFrames = targetAnimation1D->GetFrames();
			if (sourceFrames.size() == 0)
			{
				return;
			}
			if (targetFrames.size() == 0)
			{
				return;
			}
			int maxLeds = PluginGetMaxLeds((int)sourceAnimation1D->GetDevice());
			for (int frameId = 0; frameId < int(sourceFrames.size()); ++frameId)
			{
				FChromaSDKColorFrame1D& sourceFrame = sourceFrames[frameId];
				FChromaSDKColorFrame1D& targetFrame = targetFrames[(frameId + offset) % targetFrames.size()];
				for (int i = 0; i < maxLeds; ++i)
				{
					int color = sourceFrame.Colors[i];
					if (color == 0)
					{
						targetFrame.Colors[i] = color;
					}
				}
			}
		}
		else if (sourceAnimation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_2D)
		{
			Animation2D* sourceAnimation2D = (Animation2D*)(sourceAnimation);
			Animation2D* targetAnimation2D = (Animation2D*)(targetAnimation);
			vector<FChromaSDKColorFrame2D>& sourceFrames = sourceAnimation2D->GetFrames();
			vector<FChromaSDKColorFrame2D>& targetFrames = targetAnimation2D->GetFrames();
			if (sourceFrames.size() == 0)
			{
				return;
			}
			if (targetFrames.size() == 0)
			{
				return;
			}
			int maxRow = PluginGetMaxRow((int)sourceAnimation2D->GetDevice());
			int maxColumn = PluginGetMaxColumn((int)sourceAnimation2D->GetDevice());
			for (int frameId = 0; frameId < int(sourceFrames.size()); ++frameId)
			{
				FChromaSDKColorFrame2D& sourceFrame = sourceFrames[frameId];
				FChromaSDKColorFrame2D& targetFrame = targetFrames[(frameId + offset) % targetFrames.size()];
				for (int i = 0; i < maxRow; ++i)
				{
					for (int j = 0; j < maxColumn; ++j)
					{
						int color = sourceFrame.Colors[i].Colors[j];
						if (color == 0)
						{
							targetFrame.Colors[i].Colors[j] = color;
						}
					}
				}
			}
		}
	}

	EXPORT_API void PluginCopyZeroAllKeysAllFramesOffsetName(const char* sourceAnimation, const char* targetAnimation, int offset)
	{
		int sourceAnimationId = PluginGetAnimation(sourceAnimation);
		if (sourceAnimationId < 0)
		{
			LogError("PluginCopyZeroAllKeysAllFramesOffsetName: Source Animation not found! %s\r\n", sourceAnimation);
			return;
		}

		int targetAnimationId = PluginGetAnimation(targetAnimation);
		if (targetAnimationId < 0)
		{
			LogError("PluginCopyZeroAllKeysAllFramesOffsetName: Target Animation not found! %s\r\n", targetAnimation);
			return;
		}

		PluginCopyZeroAllKeysAllFramesOffset(sourceAnimationId, targetAnimationId, offset);
	}

	EXPORT_API double PluginCopyZeroAllKeysAllFramesOffsetNameD(const char* sourceAnimation, const char* targetAnimation, double offset)
	{
		PluginCopyZeroAllKeysAllFramesOffsetName(sourceAnimation, targetAnimation, (int)offset);
		return 0;
	}


	EXPORT_API void PluginCopyNonZeroTargetAllKeys(int sourceAnimationId, int targetAnimationId, int frameId)
	{
		PluginStopAnimation(targetAnimationId);
		AnimationBase* sourceAnimation = GetAnimationInstance(sourceAnimationId);
		if (nullptr == sourceAnimation)
		{
			return;
		}
		AnimationBase* targetAnimation = GetAnimationInstance(targetAnimationId);
		if (nullptr == targetAnimation)
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() != targetAnimation->GetDeviceType() ||
			sourceAnimation->GetDeviceId() != sourceAnimation->GetDeviceId())
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_1D)
		{
			Animation1D* sourceAnimation1D = (Animation1D*)(sourceAnimation);
			Animation1D* targetAnimation1D = (Animation1D*)(targetAnimation);
			vector<FChromaSDKColorFrame1D>& sourceFrames = sourceAnimation1D->GetFrames();
			vector<FChromaSDKColorFrame1D>& targetFrames = targetAnimation1D->GetFrames();
			if (sourceFrames.size() == 0)
			{
				return;
			}
			if (targetFrames.size() == 0)
			{
				return;
			}
			int maxLeds = PluginGetMaxLeds((int)sourceAnimation1D->GetDevice());
			if (frameId >= 0 && frameId < int(targetFrames.size()))
			{
				FChromaSDKColorFrame1D& sourceFrame = sourceFrames[frameId % sourceFrames.size()];
				FChromaSDKColorFrame1D& targetFrame = targetFrames[frameId];
				for (int i = 0; i < maxLeds; ++i)
				{
					int color = sourceFrame.Colors[i];
					if (color != 0 &&
						targetFrame.Colors[i] != 0)
					{
						targetFrame.Colors[i] = color;
					}
				}
			}
		}
		else if (sourceAnimation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_2D)
		{
			Animation2D* sourceAnimation2D = (Animation2D*)(sourceAnimation);
			Animation2D* targetAnimation2D = (Animation2D*)(targetAnimation);
			vector<FChromaSDKColorFrame2D>& sourceFrames = sourceAnimation2D->GetFrames();
			vector<FChromaSDKColorFrame2D>& targetFrames = targetAnimation2D->GetFrames();
			if (sourceFrames.size() == 0)
			{
				return;
			}
			if (targetFrames.size() == 0)
			{
				return;
			}
			int maxRow = PluginGetMaxRow((int)sourceAnimation2D->GetDevice());
			int maxColumn = PluginGetMaxColumn((int)sourceAnimation2D->GetDevice());
			if (frameId >= 0 && frameId < int(targetFrames.size()))
			{
				FChromaSDKColorFrame2D& sourceFrame = sourceFrames[frameId % sourceFrames.size()];
				FChromaSDKColorFrame2D& targetFrame = targetFrames[frameId];
				for (int i = 0; i < maxRow; ++i)
				{
					for (int j = 0; j < maxColumn; ++j)
					{
						int color = sourceFrame.Colors[i].Colors[j];
						if (color != 0 &&
							targetFrame.Colors[i].Colors[j] != 0)
						{
							targetFrame.Colors[i].Colors[j] = color;
						}
					}
				}
			}
		}
	}
	EXPORT_API void PluginCopyNonZeroTargetAllKeysName(const char* sourceAnimation, const char* targetAnimation, int frameId)
	{
		int sourceAnimationId = PluginGetAnimation(sourceAnimation);
		if (sourceAnimationId < 0)
		{
			LogError("PluginCopyNonZeroTargetAllKeysName: Source Animation not found! %s\r\n", sourceAnimation);
			return;
		}

		int targetAnimationId = PluginGetAnimation(targetAnimation);
		if (targetAnimationId < 0)
		{
			LogError("PluginCopyNonZeroTargetAllKeysName: Target Animation not found! %s\r\n", targetAnimation);
			return;
		}

		PluginCopyNonZeroTargetAllKeys(sourceAnimationId, targetAnimationId, frameId);
	}
	EXPORT_API double PluginCopyNonZeroTargetAllKeysNameD(const char* sourceAnimation, const char* targetAnimation, double frameId)
	{
		PluginCopyNonZeroTargetAllKeysName(sourceAnimation, targetAnimation, (int)frameId);
		return 0;
	}


	EXPORT_API void PluginCopyNonZeroTargetAllKeysAllFrames(int sourceAnimationId, int targetAnimationId)
	{
		PluginStopAnimation(targetAnimationId);
		AnimationBase* sourceAnimation = GetAnimationInstance(sourceAnimationId);
		if (nullptr == sourceAnimation)
		{
			return;
		}
		AnimationBase* targetAnimation = GetAnimationInstance(targetAnimationId);
		if (nullptr == targetAnimation)
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() != targetAnimation->GetDeviceType() ||
			sourceAnimation->GetDeviceId() != sourceAnimation->GetDeviceId())
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_1D)
		{
			Animation1D* sourceAnimation1D = (Animation1D*)(sourceAnimation);
			Animation1D* targetAnimation1D = (Animation1D*)(targetAnimation);
			vector<FChromaSDKColorFrame1D>& sourceFrames = sourceAnimation1D->GetFrames();
			vector<FChromaSDKColorFrame1D>& targetFrames = targetAnimation1D->GetFrames();
			if (sourceFrames.size() == 0)
			{
				return;
			}
			if (targetFrames.size() == 0)
			{
				return;
			}
			int maxLeds = PluginGetMaxLeds((int)sourceAnimation1D->GetDevice());
			for (int frameId = 0; frameId < int(targetFrames.size()); ++frameId)
			{
				FChromaSDKColorFrame1D& sourceFrame = sourceFrames[frameId % sourceFrames.size()];
				FChromaSDKColorFrame1D& targetFrame = targetFrames[frameId];
				for (int i = 0; i < maxLeds; ++i)
				{
					int color = sourceFrame.Colors[i];
					if (color != 0 &&
						targetFrame.Colors[i] != 0)
					{
						targetFrame.Colors[i] = color;
					}
				}
			}
		}
		else if (sourceAnimation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_2D)
		{
			Animation2D* sourceAnimation2D = (Animation2D*)(sourceAnimation);
			Animation2D* targetAnimation2D = (Animation2D*)(targetAnimation);
			vector<FChromaSDKColorFrame2D>& sourceFrames = sourceAnimation2D->GetFrames();
			vector<FChromaSDKColorFrame2D>& targetFrames = targetAnimation2D->GetFrames();
			if (sourceFrames.size() == 0)
			{
				return;
			}
			if (targetFrames.size() == 0)
			{
				return;
			}
			int maxRow = PluginGetMaxRow((int)sourceAnimation2D->GetDevice());
			int maxColumn = PluginGetMaxColumn((int)sourceAnimation2D->GetDevice());
			for (int frameId = 0; frameId < int(targetFrames.size()); ++frameId)
			{
				FChromaSDKColorFrame2D& sourceFrame = sourceFrames[frameId % sourceFrames.size()];
				FChromaSDKColorFrame2D& targetFrame = targetFrames[frameId];
				for (int i = 0; i < maxRow; ++i)
				{
					for (int j = 0; j < maxColumn; ++j)
					{
						int color = sourceFrame.Colors[i].Colors[j];
						if (color != 0 &&
							targetFrame.Colors[i].Colors[j] != 0)
						{
							targetFrame.Colors[i].Colors[j] = color;
						}
					}
				}
			}
		}
	}

	EXPORT_API void PluginCopyNonZeroTargetAllKeysAllFramesName(const char* sourceAnimation, const char* targetAnimation)
	{
		int sourceAnimationId = PluginGetAnimation(sourceAnimation);
		if (sourceAnimationId < 0)
		{
			LogError("PluginCopyNonZeroTargetAllKeysAllFramesName: Source Animation not found! %s\r\n", sourceAnimation);
			return;
		}

		int targetAnimationId = PluginGetAnimation(targetAnimation);
		if (targetAnimationId < 0)
		{
			LogError("PluginCopyNonZeroTargetAllKeysAllFramesName: Target Animation not found! %s\r\n", targetAnimation);
			return;
		}

		PluginCopyNonZeroTargetAllKeysAllFrames(sourceAnimationId, targetAnimationId);
	}

	EXPORT_API double PluginCopyNonZeroTargetAllKeysAllFramesNameD(const char* sourceAnimation, const char* targetAnimation)
	{
		PluginCopyNonZeroTargetAllKeysAllFramesName(sourceAnimation, targetAnimation);
		return 0;
	}


	EXPORT_API void PluginCopyNonZeroTargetZeroAllKeysAllFrames(int sourceAnimationId, int targetAnimationId)
	{
		PluginStopAnimation(targetAnimationId);
		AnimationBase* sourceAnimation = GetAnimationInstance(sourceAnimationId);
		if (nullptr == sourceAnimation)
		{
			return;
		}
		AnimationBase* targetAnimation = GetAnimationInstance(targetAnimationId);
		if (nullptr == targetAnimation)
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() != targetAnimation->GetDeviceType() ||
			sourceAnimation->GetDeviceId() != sourceAnimation->GetDeviceId())
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_1D)
		{
			Animation1D* sourceAnimation1D = (Animation1D*)(sourceAnimation);
			Animation1D* targetAnimation1D = (Animation1D*)(targetAnimation);
			vector<FChromaSDKColorFrame1D>& sourceFrames = sourceAnimation1D->GetFrames();
			vector<FChromaSDKColorFrame1D>& targetFrames = targetAnimation1D->GetFrames();
			if (sourceFrames.size() == 0)
			{
				return;
			}
			if (targetFrames.size() == 0)
			{
				return;
			}
			int maxLeds = PluginGetMaxLeds((int)sourceAnimation1D->GetDevice());
			for (int frameId = 0; frameId < int(targetFrames.size()); ++frameId)
			{
				FChromaSDKColorFrame1D& sourceFrame = sourceFrames[frameId % sourceFrames.size()];
				FChromaSDKColorFrame1D& targetFrame = targetFrames[frameId];
				for (int i = 0; i < maxLeds; ++i)
				{
					int color = sourceFrame.Colors[i];
					if (color != 0 &&
						targetFrame.Colors[i] == 0)
					{
						targetFrame.Colors[i] = color;
					}
				}
			}
		}
		else if (sourceAnimation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_2D)
		{
			Animation2D* sourceAnimation2D = (Animation2D*)(sourceAnimation);
			Animation2D* targetAnimation2D = (Animation2D*)(targetAnimation);
			vector<FChromaSDKColorFrame2D>& sourceFrames = sourceAnimation2D->GetFrames();
			vector<FChromaSDKColorFrame2D>& targetFrames = targetAnimation2D->GetFrames();
			if (sourceFrames.size() == 0)
			{
				return;
			}
			if (targetFrames.size() == 0)
			{
				return;
			}
			int maxRow = PluginGetMaxRow((int)sourceAnimation2D->GetDevice());
			int maxColumn = PluginGetMaxColumn((int)sourceAnimation2D->GetDevice());
			for (int frameId = 0; frameId < int(targetFrames.size()); ++frameId)
			{
				FChromaSDKColorFrame2D& sourceFrame = sourceFrames[frameId % sourceFrames.size()];
				FChromaSDKColorFrame2D& targetFrame = targetFrames[frameId];
				for (int i = 0; i < maxRow; ++i)
				{
					for (int j = 0; j < maxColumn; ++j)
					{
						int color = sourceFrame.Colors[i].Colors[j];
						if (color != 0 &&
							targetFrame.Colors[i].Colors[j] == 0)
						{
							targetFrame.Colors[i].Colors[j] = color;
						}
					}
				}
			}
		}
	}

	EXPORT_API void PluginCopyNonZeroTargetZeroAllKeysAllFramesName(const char* sourceAnimation, const char* targetAnimation)
	{
		int sourceAnimationId = PluginGetAnimation(sourceAnimation);
		if (sourceAnimationId < 0)
		{
			LogError("PluginCopyNonZeroTargetZeroAllKeysAllFramesName: Source Animation not found! %s\r\n", sourceAnimation);
			return;
		}

		int targetAnimationId = PluginGetAnimation(targetAnimation);
		if (targetAnimationId < 0)
		{
			LogError("PluginCopyNonZeroTargetZeroAllKeysAllFramesName: Target Animation not found! %s\r\n", targetAnimation);
			return;
		}

		PluginCopyNonZeroTargetZeroAllKeysAllFrames(sourceAnimationId, targetAnimationId);
	}

	EXPORT_API double PluginCopyNonZeroTargetZeroAllKeysAllFramesNameD(const char* sourceAnimation, const char* targetAnimation)
	{
		PluginCopyNonZeroTargetZeroAllKeysAllFramesName(sourceAnimation, targetAnimation);
		return 0;
	}

	EXPORT_API void PluginCopyZeroTargetAllKeys(int sourceAnimationId, int targetAnimationId, int frameId)
	{
		PluginStopAnimation(targetAnimationId);
		AnimationBase* sourceAnimation = GetAnimationInstance(sourceAnimationId);
		if (nullptr == sourceAnimation)
		{
			return;
		}
		AnimationBase* targetAnimation = GetAnimationInstance(targetAnimationId);
		if (nullptr == targetAnimation)
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() != targetAnimation->GetDeviceType() ||
			sourceAnimation->GetDeviceId() != targetAnimation->GetDeviceId())
		{
			return;
		}
		if (frameId < 0)
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_1D)
		{
			Animation1D* sourceAnimation1D = (Animation1D*)(sourceAnimation);
			Animation1D* targetAnimation1D = (Animation1D*)(targetAnimation);
			vector<FChromaSDKColorFrame1D>& sourceFrames = sourceAnimation1D->GetFrames();
			vector<FChromaSDKColorFrame1D>& targetFrames = targetAnimation1D->GetFrames();
			if (sourceFrames.size() == 0)
			{
				return;
			}
			if (targetFrames.size() == 0)
			{
				return;
			}
			int maxLeds = PluginGetMaxLeds((int)sourceAnimation1D->GetDevice());
			if (frameId < int(targetFrames.size()))
			{
				FChromaSDKColorFrame1D& sourceFrame = sourceFrames[frameId % sourceFrames.size()];
				FChromaSDKColorFrame1D& targetFrame = targetFrames[frameId];
				for (int i = 0; i < maxLeds; ++i)
				{
					int color = sourceFrame.Colors[i];
					if (color != 0 &&
						targetFrame.Colors[i] == 0)
					{
						targetFrame.Colors[i] = color;
					}
				}
			}
		}
		else if (sourceAnimation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_2D)
		{
			Animation2D* sourceAnimation2D = (Animation2D*)(sourceAnimation);
			Animation2D* targetAnimation2D = (Animation2D*)(targetAnimation);
			vector<FChromaSDKColorFrame2D>& sourceFrames = sourceAnimation2D->GetFrames();
			vector<FChromaSDKColorFrame2D>& targetFrames = targetAnimation2D->GetFrames();
			if (sourceFrames.size() == 0)
			{
				return;
			}
			if (targetFrames.size() == 0)
			{
				return;
			}
			int maxRow = PluginGetMaxRow((int)sourceAnimation2D->GetDevice());
			int maxColumn = PluginGetMaxColumn((int)sourceAnimation2D->GetDevice());
			if (frameId < int(targetFrames.size()))
			{
				FChromaSDKColorFrame2D& sourceFrame = sourceFrames[frameId % sourceFrames.size()];
				FChromaSDKColorFrame2D& targetFrame = targetFrames[frameId];
				for (int i = 0; i < maxRow; ++i)
				{
					for (int j = 0; j < maxColumn; ++j)
					{
						int color = sourceFrame.Colors[i].Colors[j];
						if (color != 0 &&
							targetFrame.Colors[i].Colors[j] == 0)
						{
							targetFrame.Colors[i].Colors[j] = color;
						}
					}
				}
			}
		}
	}

	EXPORT_API void PluginCopyZeroTargetAllKeysName(const char* sourceAnimation, const char* targetAnimation, int frameId)
	{
		int sourceAnimationId = PluginGetAnimation(sourceAnimation);
		if (sourceAnimationId < 0)
		{
			LogError("PluginCopyZeroTargetAllKeysName: Source Animation not found! %s\r\n", sourceAnimation);
			return;
		}

		int targetAnimationId = PluginGetAnimation(targetAnimation);
		if (targetAnimationId < 0)
		{
			LogError("PluginCopyZeroTargetAllKeysName: Target Animation not found! %s\r\n", targetAnimation);
			return;
		}

		PluginCopyZeroTargetAllKeys(sourceAnimationId, targetAnimationId, frameId);
	}

	EXPORT_API void PluginCopyZeroTargetAllKeysAllFrames(int sourceAnimationId, int targetAnimationId)
	{
		PluginStopAnimation(targetAnimationId);
		AnimationBase* sourceAnimation = GetAnimationInstance(sourceAnimationId);
		if (nullptr == sourceAnimation)
		{
			return;
		}
		AnimationBase* targetAnimation = GetAnimationInstance(targetAnimationId);
		if (nullptr == targetAnimation)
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() != targetAnimation->GetDeviceType() ||
			sourceAnimation->GetDeviceId() != targetAnimation->GetDeviceId())
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_1D)
		{
			Animation1D* sourceAnimation1D = (Animation1D*)(sourceAnimation);
			Animation1D* targetAnimation1D = (Animation1D*)(targetAnimation);
			vector<FChromaSDKColorFrame1D>& sourceFrames = sourceAnimation1D->GetFrames();
			vector<FChromaSDKColorFrame1D>& targetFrames = targetAnimation1D->GetFrames();
			if (sourceFrames.size() == 0)
			{
				return;
			}
			if (targetFrames.size() == 0)
			{
				return;
			}
			int maxLeds = PluginGetMaxLeds((int)sourceAnimation1D->GetDevice());
			for (int frameId = 0; frameId < int(targetFrames.size()); ++frameId)
			{
				FChromaSDKColorFrame1D& sourceFrame = sourceFrames[frameId % sourceFrames.size()];
				FChromaSDKColorFrame1D& targetFrame = targetFrames[frameId];
				for (int i = 0; i < maxLeds; ++i)
				{
					int color = sourceFrame.Colors[i];
					if (color != 0 &&
						targetFrame.Colors[i] == 0)
					{
						targetFrame.Colors[i] = color;
					}
				}
			}
		}
		else if (sourceAnimation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_2D)
		{
			Animation2D* sourceAnimation2D = (Animation2D*)(sourceAnimation);
			Animation2D* targetAnimation2D = (Animation2D*)(targetAnimation);
			vector<FChromaSDKColorFrame2D>& sourceFrames = sourceAnimation2D->GetFrames();
			vector<FChromaSDKColorFrame2D>& targetFrames = targetAnimation2D->GetFrames();
			if (sourceFrames.size() == 0)
			{
				return;
			}
			if (targetFrames.size() == 0)
			{
				return;
			}
			int maxRow = PluginGetMaxRow((int)sourceAnimation2D->GetDevice());
			int maxColumn = PluginGetMaxColumn((int)sourceAnimation2D->GetDevice());
			for (int frameId = 0; frameId < int(targetFrames.size()); ++frameId)
			{
				FChromaSDKColorFrame2D& sourceFrame = sourceFrames[frameId % sourceFrames.size()];
				FChromaSDKColorFrame2D& targetFrame = targetFrames[frameId];
				for (int i = 0; i < maxRow; ++i)
				{
					for (int j = 0; j < maxColumn; ++j)
					{
						int color = sourceFrame.Colors[i].Colors[j];
						if (color != 0 &&
							targetFrame.Colors[i].Colors[j] == 0)
						{
							targetFrame.Colors[i].Colors[j] = color;
						}
					}
				}
			}
		}
	}

	EXPORT_API void PluginCopyZeroTargetAllKeysAllFramesName(const char* sourceAnimation, const char* targetAnimation)
	{
		int sourceAnimationId = PluginGetAnimation(sourceAnimation);
		if (sourceAnimationId < 0)
		{
			LogError("PluginCopyZeroTargetAllKeysAllFramesName: Source Animation not found! %s\r\n", sourceAnimation);
			return;
		}

		int targetAnimationId = PluginGetAnimation(targetAnimation);
		if (targetAnimationId < 0)
		{
			LogError("PluginCopyZeroTargetAllKeysAllFramesName: Target Animation not found! %s\r\n", targetAnimation);
			return;
		}

		PluginCopyZeroTargetAllKeysAllFrames(sourceAnimationId, targetAnimationId);
	}

	EXPORT_API double PluginCopyZeroTargetAllKeysAllFramesNameD(const char* sourceAnimation, const char* targetAnimation)
	{
		PluginCopyZeroTargetAllKeysAllFramesName(sourceAnimation, targetAnimation);
		return 0;
	}


	EXPORT_API void PluginCopyNonZeroKeyColor(int sourceAnimationId, int targetAnimationId, int frameId, int rzkey)
	{
		PluginStopAnimation(targetAnimationId);
		AnimationBase* sourceAnimation = GetAnimationInstance(sourceAnimationId);
		if (nullptr == sourceAnimation)
		{
			return;
		}
		AnimationBase* targetAnimation = GetAnimationInstance(targetAnimationId);
		if (nullptr == targetAnimation)
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() != EChromaSDKDeviceTypeEnum::DE_2D ||
			sourceAnimation->GetDeviceId() != (int)EChromaSDKDevice2DEnum::DE_Keyboard)
		{
			return;
		}
		if (targetAnimation->GetDeviceType() != EChromaSDKDeviceTypeEnum::DE_2D ||
			targetAnimation->GetDeviceId() != (int)EChromaSDKDevice2DEnum::DE_Keyboard)
		{
			return;
		}
		if (frameId < 0)
		{
			return;
		}
		Animation2D* sourceAnimation2D = (Animation2D*)(sourceAnimation);
		Animation2D* targetAnimation2D = (Animation2D*)(targetAnimation);
		vector<FChromaSDKColorFrame2D>& sourceFrames = sourceAnimation2D->GetFrames();
		vector<FChromaSDKColorFrame2D>& targetFrames = targetAnimation2D->GetFrames();
		if (sourceFrames.size() == 0)
		{
			return;
		}
		if (targetFrames.size() == 0)
		{
			return;
		}
		if (frameId < int(targetFrames.size()))
		{
			FChromaSDKColorFrame2D& sourceFrame = sourceFrames[frameId % sourceFrames.size()];
			FChromaSDKColorFrame2D& targetFrame = targetFrames[frameId];
			int color = sourceFrame.Colors[HIBYTE(rzkey)].Colors[LOBYTE(rzkey)];
			if (color != 0)
			{
				targetFrame.Colors[HIBYTE(rzkey)].Colors[LOBYTE(rzkey)] = color;
			}
		}
	}

	EXPORT_API void PluginCopyNonZeroKeyColorName(const char* sourceAnimation, const char* targetAnimation, int frameId, int rzkey)
	{
		int sourceAnimationId = PluginGetAnimation(sourceAnimation);
		if (sourceAnimationId < 0)
		{
			LogError("PluginCopyNonZeroKeyColorName: Source Animation not found! %s\r\n", sourceAnimation);
			return;
		}

		int targetAnimationId = PluginGetAnimation(targetAnimation);
		if (targetAnimationId < 0)
		{
			LogError("PluginCopyNonZeroKeyColorName: Target Animation not found! %s\r\n", targetAnimation);
			return;
		}

		PluginCopyNonZeroKeyColor(sourceAnimationId, targetAnimationId, frameId, rzkey);
	}

	EXPORT_API double PluginCopyNonZeroKeyColorNameD(const char* sourceAnimation, const char* targetAnimation, double frameId, double rzkey)
	{
		PluginCopyNonZeroKeyColorName(sourceAnimation, targetAnimation, (int)frameId, (int)rzkey);
		return 0;
	}


	EXPORT_API void PluginCopyZeroKeyColor(int sourceAnimationId, int targetAnimationId, int frameId, int rzkey)
	{
		PluginStopAnimation(targetAnimationId);
		AnimationBase* sourceAnimation = GetAnimationInstance(sourceAnimationId);
		if (nullptr == sourceAnimation)
		{
			return;
		}
		AnimationBase* targetAnimation = GetAnimationInstance(targetAnimationId);
		if (nullptr == targetAnimation)
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() != EChromaSDKDeviceTypeEnum::DE_2D ||
			sourceAnimation->GetDeviceId() != (int)EChromaSDKDevice2DEnum::DE_Keyboard)
		{
			return;
		}
		if (targetAnimation->GetDeviceType() != EChromaSDKDeviceTypeEnum::DE_2D ||
			targetAnimation->GetDeviceId() != (int)EChromaSDKDevice2DEnum::DE_Keyboard)
		{
			return;
		}
		if (frameId < 0)
		{
			return;
		}
		Animation2D* sourceAnimation2D = (Animation2D*)(sourceAnimation);
		Animation2D* targetAnimation2D = (Animation2D*)(targetAnimation);
		vector<FChromaSDKColorFrame2D>& sourceFrames = sourceAnimation2D->GetFrames();
		vector<FChromaSDKColorFrame2D>& targetFrames = targetAnimation2D->GetFrames();
		if (sourceFrames.size() == 0)
		{
			return;
		}
		if (targetFrames.size() == 0)
		{
			return;
		}
		if (frameId < int(targetFrames.size()))
		{
			FChromaSDKColorFrame2D& sourceFrame = sourceFrames[frameId % sourceFrames.size()];
			FChromaSDKColorFrame2D& targetFrame = targetFrames[frameId];
			int color = sourceFrame.Colors[HIBYTE(rzkey)].Colors[LOBYTE(rzkey)];
			if (color == 0)
			{
				targetFrame.Colors[HIBYTE(rzkey)].Colors[LOBYTE(rzkey)] = color;
			}
		}
	}

	EXPORT_API void PluginCopyZeroKeyColorName(const char* sourceAnimation, const char* targetAnimation, int frameId, int rzkey)
	{
		int sourceAnimationId = PluginGetAnimation(sourceAnimation);
		if (sourceAnimationId < 0)
		{
			LogError("PluginCopyZeroKeyColorName: Source Animation not found! %s\r\n", sourceAnimation);
			return;
		}

		int targetAnimationId = PluginGetAnimation(targetAnimation);
		if (targetAnimationId < 0)
		{
			LogError("PluginCopyZeroKeyColorName: Target Animation not found! %s\r\n", targetAnimation);
			return;
		}

		PluginCopyZeroKeyColor(sourceAnimationId, targetAnimationId, frameId, rzkey);
	}

	EXPORT_API double PluginCopyZeroKeyColorNameD(const char* sourceAnimation, const char* targetAnimation, double frameId, double rzkey)
	{
		PluginCopyZeroKeyColorName(sourceAnimation, targetAnimation, (int)frameId, (int)rzkey);
		return 0;
	}


	EXPORT_API void PluginFillColor(int animationId, int frameId, int color)
	{
		PluginStopAnimation(animationId);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		switch (animation->GetDeviceType())
		{
		case EChromaSDKDeviceTypeEnum::DE_1D:
		{
			Animation1D* animation1D = (Animation1D*)(animation);
			vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
			if (frameId >= 0 &&
				frameId < (int)frames.size())
			{
				FChromaSDKColorFrame1D& frame = frames[frameId];
				int maxLeds = ChromaSDKPlugin::GetInstance()->GetMaxLeds(animation1D->GetDevice());
				vector<COLORREF>& colors = frame.Colors;
				for (int i = 0; i < maxLeds; ++i)
				{
					colors[i] = color;
				}
			}
		}
		break;
		case EChromaSDKDeviceTypeEnum::DE_2D:
		{
			Animation2D* animation2D = (Animation2D*)(animation);
			vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
			if (frameId >= 0 &&
				frameId < (int)frames.size())
			{
				FChromaSDKColorFrame2D& frame = frames[frameId];
				int maxRow = ChromaSDKPlugin::GetInstance()->GetMaxRow(animation2D->GetDevice());
				int maxColumn = ChromaSDKPlugin::GetInstance()->GetMaxColumn(animation2D->GetDevice());
				for (int i = 0; i < maxRow; ++i)
				{
					FChromaSDKColors& row = frame.Colors[i];
					for (int j = 0; j < maxColumn; ++j)
					{
						row.Colors[j] = color;
					}
				}
			}
		}
		break;
		}
	}

	EXPORT_API void PluginFillColorName(const char* path, int frameId, int color)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginFillColorName: Animation not found! %s\r\n", path);
			return;
		}
		PluginFillColor(animationId, frameId, color);
	}

	EXPORT_API double PluginFillColorNameD(const char* path, double frameId, double color)
	{
		PluginFillColorName(path, (int)frameId, (int)color);
		return 0;
	}


	EXPORT_API void PluginFillThresholdColors(int animationId, int frameId, int threshold, int color)
	{
		PluginStopAnimation(animationId);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		switch (animation->GetDeviceType())
		{
		case EChromaSDKDeviceTypeEnum::DE_1D:
		{
			Animation1D* animation1D = (Animation1D*)(animation);
			vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
			if (frameId >= 0 &&
				frameId < (int)frames.size())
			{
				FChromaSDKColorFrame1D& frame = frames[frameId];
				int maxLeds = ChromaSDKPlugin::GetInstance()->GetMaxLeds(animation1D->GetDevice());
				vector<COLORREF>& colors = frame.Colors;
				for (int i = 0; i < maxLeds; ++i)
				{
					int oldColor = colors[i];
					int red = oldColor & 0xFF;
					int green = (oldColor & 0xFF00) >> 8;
					int blue = (oldColor & 0xFF0000) >> 16;
					if ((red != 0 ||
						green != 0 ||
						blue != 0) &&
						red <= threshold &&
						green <= threshold &&
						blue <= threshold) {
						colors[i] = color;
					}
				}
			}
		}
		break;
		case EChromaSDKDeviceTypeEnum::DE_2D:
		{
			Animation2D* animation2D = (Animation2D*)(animation);
			vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
			if (frameId >= 0 &&
				frameId < (int)frames.size())
			{
				FChromaSDKColorFrame2D& frame = frames[frameId];
				int maxRow = ChromaSDKPlugin::GetInstance()->GetMaxRow(animation2D->GetDevice());
				int maxColumn = ChromaSDKPlugin::GetInstance()->GetMaxColumn(animation2D->GetDevice());
				for (int i = 0; i < maxRow; ++i)
				{
					FChromaSDKColors& row = frame.Colors[i];
					for (int j = 0; j < maxColumn; ++j)
					{
						int oldColor = row.Colors[j];
						int red = oldColor & 0xFF;
						int green = (oldColor & 0xFF00) >> 8;
						int blue = (oldColor & 0xFF0000) >> 16;
						if ((red != 0 ||
							green != 0 ||
							blue != 0) &&
							red <= threshold &&
							green <= threshold &&
							blue <= threshold) {
							row.Colors[j] = color;
						}
					}
				}
			}
		}
		break;
		}
	}

	EXPORT_API void PluginFillThresholdColorsName(const char* path, int frameId, int threshold, int color)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginFillThresholdColorsName: Animation not found! %s\r\n", path);
			return;
		}
		PluginFillThresholdColors(animationId, frameId, threshold, color);
	}

	EXPORT_API double PluginFillThresholdColorsNameD(const char* path, double frameId, double threshold, double color)
	{
		PluginFillThresholdColorsName(path, (int)frameId, (int)threshold, (int)color);
		return 0;
	}


	EXPORT_API void PluginFillColorRGB(int animationId, int frameId, int red, int green, int blue)
	{
		PluginStopAnimation(animationId);
		int color = PluginGetRGB(red, green, blue);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		switch (animation->GetDeviceType())
		{
		case EChromaSDKDeviceTypeEnum::DE_1D:
		{
			Animation1D* animation1D = (Animation1D*)(animation);
			vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
			if (frameId >= 0 &&
				frameId < (int)frames.size())
			{
				FChromaSDKColorFrame1D& frame = frames[frameId];
				int maxLeds = ChromaSDKPlugin::GetInstance()->GetMaxLeds(animation1D->GetDevice());
				vector<COLORREF>& colors = frame.Colors;
				for (int i = 0; i < maxLeds; ++i)
				{
					colors[i] = color;
				}
			}
		}
		break;
		case EChromaSDKDeviceTypeEnum::DE_2D:
		{
			Animation2D* animation2D = (Animation2D*)(animation);
			vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
			if (frameId >= 0 &&
				frameId < (int)frames.size())
			{
				FChromaSDKColorFrame2D& frame = frames[frameId];
				int maxRow = ChromaSDKPlugin::GetInstance()->GetMaxRow(animation2D->GetDevice());
				int maxColumn = ChromaSDKPlugin::GetInstance()->GetMaxColumn(animation2D->GetDevice());
				for (int i = 0; i < maxRow; ++i)
				{
					FChromaSDKColors& row = frame.Colors[i];
					for (int j = 0; j < maxColumn; ++j)
					{
						row.Colors[j] = color;
					}
				}
			}
		}
		break;
		}
	}

	EXPORT_API void PluginFillColorRGBName(const char* path, int frameId, int red, int green, int blue)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginFillColorRGBName: Animation not found! %s\r\n", path);
			return;
		}
		PluginFillColorRGB(animationId, frameId, red, green, blue);
	}

	EXPORT_API double PluginFillColorRGBNameD(const char* path, double frameId, double red, double green, double blue)
	{
		PluginFillColorRGBName(path, (int)frameId, (int)red, (int)green, (int)blue);
		return 0;
	}


	EXPORT_API void PluginFillThresholdColorsRGB(int animationId, int frameId, int threshold, int red, int green, int blue)
	{
		PluginStopAnimation(animationId);
		int color = PluginGetRGB(red, green, blue);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		switch (animation->GetDeviceType())
		{
		case EChromaSDKDeviceTypeEnum::DE_1D:
		{
			Animation1D* animation1D = (Animation1D*)(animation);
			vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
			if (frameId >= 0 &&
				frameId < (int)frames.size())
			{
				FChromaSDKColorFrame1D& frame = frames[frameId];
				int maxLeds = ChromaSDKPlugin::GetInstance()->GetMaxLeds(animation1D->GetDevice());
				vector<COLORREF>& colors = frame.Colors;
				for (int i = 0; i < maxLeds; ++i)
				{
					int oldColor = colors[i];
					int r = oldColor & 0xFF;
					int g = (oldColor & 0xFF00) >> 8;
					int b = (oldColor & 0xFF0000) >> 16;
					if (r != 0 &&
						g != 0 &&
						b != 0 &&
						r <= threshold &&
						g <= threshold &&
						b <= threshold) {
						colors[i] = color;
					}
				}
			}
		}
		break;
		case EChromaSDKDeviceTypeEnum::DE_2D:
		{
			Animation2D* animation2D = (Animation2D*)(animation);
			vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
			if (frameId >= 0 &&
				frameId < (int)frames.size())
			{
				FChromaSDKColorFrame2D& frame = frames[frameId];
				int maxRow = ChromaSDKPlugin::GetInstance()->GetMaxRow(animation2D->GetDevice());
				int maxColumn = ChromaSDKPlugin::GetInstance()->GetMaxColumn(animation2D->GetDevice());
				for (int i = 0; i < maxRow; ++i)
				{
					FChromaSDKColors& row = frame.Colors[i];
					for (int j = 0; j < maxColumn; ++j)
					{
						int oldColor = row.Colors[j];
						int r = oldColor & 0xFF;
						int g = (oldColor & 0xFF00) >> 8;
						int b = (oldColor & 0xFF0000) >> 16;
						if (r != 0 &&
							g != 0 &&
							b != 0 &&
							r <= threshold &&
							g <= threshold &&
							b <= threshold) {
							row.Colors[j] = color;
						}
					}
				}
			}
		}
		break;
		}
	}

	EXPORT_API void PluginFillThresholdColorsRGBName(const char* path, int frameId, int threshold, int red, int green, int blue)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginFillThresholdColorsRGBName: Animation not found! %s\r\n", path);
			return;
		}
		PluginFillThresholdColorsRGB(animationId, frameId, threshold, red, green, blue);
	}

	EXPORT_API double PluginFillThresholdColorsRGBNameD(const char* path, double frameId, double threshold, double red, double green, double blue)
	{
		PluginFillThresholdColorsRGBName(path, (int)frameId, (int)threshold, (int)red, (int)green, (int)blue);
		return 0;
	}


	EXPORT_API void PluginFillThresholdRGBColorsRGB(int animationId, int frameId, int redThreshold, int greenThreshold, int blueThreshold, int red, int green, int blue)
	{
		PluginStopAnimation(animationId);
		int color = PluginGetRGB(red, green, blue);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		switch (animation->GetDeviceType())
		{
		case EChromaSDKDeviceTypeEnum::DE_1D:
		{
			Animation1D* animation1D = (Animation1D*)(animation);
			vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
			if (frameId >= 0 &&
				frameId < (int)frames.size())
			{
				FChromaSDKColorFrame1D& frame = frames[frameId];
				int maxLeds = ChromaSDKPlugin::GetInstance()->GetMaxLeds(animation1D->GetDevice());
				vector<COLORREF>& colors = frame.Colors;
				for (int i = 0; i < maxLeds; ++i)
				{
					int oldColor = colors[i];
					int red = oldColor & 0xFF;
					int green = (oldColor & 0xFF00) >> 8;
					int blue = (oldColor & 0xFF0000) >> 16;
					if (red != 0 &&
						green != 0 &&
						blue != 0 &&
						red <= redThreshold &&
						green <= greenThreshold &&
						blue <= blueThreshold) {
						colors[i] = color;
					}
				}
			}
		}
		break;
		case EChromaSDKDeviceTypeEnum::DE_2D:
		{
			Animation2D* animation2D = (Animation2D*)(animation);
			vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
			if (frameId >= 0 &&
				frameId < (int)frames.size())
			{
				FChromaSDKColorFrame2D& frame = frames[frameId];
				int maxRow = ChromaSDKPlugin::GetInstance()->GetMaxRow(animation2D->GetDevice());
				int maxColumn = ChromaSDKPlugin::GetInstance()->GetMaxColumn(animation2D->GetDevice());
				for (int i = 0; i < maxRow; ++i)
				{
					FChromaSDKColors& row = frame.Colors[i];
					for (int j = 0; j < maxColumn; ++j)
					{
						int oldColor = row.Colors[j];
						int red = oldColor & 0xFF;
						int green = (oldColor & 0xFF00) >> 8;
						int blue = (oldColor & 0xFF0000) >> 16;
						if (red != 0 &&
							green != 0 &&
							blue != 0 &&
							red <= redThreshold &&
							green <= greenThreshold &&
							blue <= blueThreshold) {
							row.Colors[j] = color;
						}
					}
				}
			}
		}
		break;
		}
	}
	EXPORT_API void PluginFillThresholdRGBColorsRGBName(const char* path, int frameId, int redThreshold, int greenThreshold, int blueThreshold, int red, int green, int blue)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginFillThresholdRGBColorsRGBName: Animation not found! %s\r\n", path);
			return;
		}
		PluginFillThresholdRGBColorsRGB(animationId, frameId, redThreshold, greenThreshold, blueThreshold, red, green, blue);
	}
	EXPORT_API double PluginFillThresholdRGBColorsRGBNameD(const char* path, double frameId, double redThreshold, double greenThreshold, double blueThreshold, double red, double green, double blue)
	{
		PluginFillThresholdRGBColorsRGBName(path, (int)frameId, (int)redThreshold, (int)greenThreshold, (int)blueThreshold, (int)red, (int)green, (int)blue);
		return 0;
	}


	EXPORT_API void PluginFillThresholdColorsMinMaxRGB(int animationId, int frameId, int minThreshold, int minRed, int minGreen, int minBlue, int maxThreshold, int maxRed, int maxGreen, int maxBlue)
	{
		PluginStopAnimation(animationId);
		int minColor = PluginGetRGB(minRed, minGreen, minBlue);
		int maxColor = PluginGetRGB(maxRed, maxGreen, maxBlue);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		switch (animation->GetDeviceType())
		{
		case EChromaSDKDeviceTypeEnum::DE_1D:
		{
			Animation1D* animation1D = (Animation1D*)(animation);
			vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
			if (frameId >= 0 &&
				frameId < (int)frames.size())
			{
				FChromaSDKColorFrame1D& frame = frames[frameId];
				int maxLeds = ChromaSDKPlugin::GetInstance()->GetMaxLeds(animation1D->GetDevice());
				vector<COLORREF>& colors = frame.Colors;
				for (int i = 0; i < maxLeds; ++i)
				{
					int oldColor = colors[i];
					int red = oldColor & 0xFF;
					int green = (oldColor & 0xFF00) >> 8;
					int blue = (oldColor & 0xFF0000) >> 16;
					if (red != 0 ||
						green != 0 ||
						blue != 0)
					{
						if (red <= minThreshold &&
							green <= minThreshold &&
							blue <= minThreshold) {
							colors[i] = minColor;
						}
						else if (red >= maxThreshold ||
							green >= maxThreshold ||
							blue >= maxThreshold) {
							colors[i] = maxColor;
						}
					}
				}
			}
		}
		break;
		case EChromaSDKDeviceTypeEnum::DE_2D:
		{
			Animation2D* animation2D = (Animation2D*)(animation);
			vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
			if (frameId >= 0 &&
				frameId < (int)frames.size())
			{
				FChromaSDKColorFrame2D& frame = frames[frameId];
				int maxRow = ChromaSDKPlugin::GetInstance()->GetMaxRow(animation2D->GetDevice());
				int maxColumn = ChromaSDKPlugin::GetInstance()->GetMaxColumn(animation2D->GetDevice());
				for (int i = 0; i < maxRow; ++i)
				{
					FChromaSDKColors& row = frame.Colors[i];
					for (int j = 0; j < maxColumn; ++j)
					{
						int oldColor = row.Colors[j];
						int red = oldColor & 0xFF;
						int green = (oldColor & 0xFF00) >> 8;
						int blue = (oldColor & 0xFF0000) >> 16;
						if (red != 0 ||
							green != 0 ||
							blue != 0)
						{
							if (red <= minThreshold &&
								green <= minThreshold &&
								blue <= minThreshold) {
								row.Colors[j] = minColor;
							}
							else if (red >= maxThreshold ||
								green >= maxThreshold ||
								blue >= maxThreshold) {
								row.Colors[j] = maxColor;
							}
						}
					}
				}
			}
		}
		break;
		}
	}

	EXPORT_API void PluginFillThresholdColorsMinMaxRGBName(const char* path, int frameId, int minThreshold, int minRed, int minGreen, int minBlue, int maxThreshold, int maxRed, int maxGreen, int maxBlue)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginFillThresholdColorsMinMaxRGBName: Animation not found! %s\r\n", path);
			return;
		}
		PluginFillThresholdColorsMinMaxRGB(animationId, frameId, minThreshold, minRed, minGreen, minBlue, maxThreshold, maxRed, maxGreen, maxBlue);
	}

	EXPORT_API double PluginFillThresholdColorsMinMaxRGBNameD(const char* path, double frameId, double minThreshold, double minRed, double minGreen, double minBlue, double maxThreshold, double maxRed, double maxGreen, double maxBlue)
	{
		PluginFillThresholdColorsMinMaxRGBName(path, (int)frameId, (int)minThreshold, (int)minRed, (int)minGreen, (int)minBlue, (int)maxThreshold, (int)maxRed, (int)maxGreen, (int)maxBlue);
		return 0;
	}


	EXPORT_API void PluginFillColorAllFrames(int animationId, int color)
	{
		PluginStopAnimation(animationId);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		int frameCount = PluginGetFrameCount(animationId);
		for (int frameId = 0; frameId < frameCount; ++frameId)
		{
			PluginFillColor(animationId, frameId, color);
		}
	}

	EXPORT_API void PluginFillColorAllFramesName(const char* path, int color)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginFillColorAllFramesName: Animation not found! %s\r\n", path);
			return;
		}
		PluginFillColorAllFrames(animationId, color);
	}

	EXPORT_API double PluginFillColorAllFramesNameD(const char* path, double color)
	{
		PluginFillColorAllFramesName(path, (int)color);
		return 0;
	}


	EXPORT_API void PluginFillThresholdColorsAllFrames(int animationId, int threshold, int color)
	{
		PluginStopAnimation(animationId);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		int frameCount = PluginGetFrameCount(animationId);
		for (int frameId = 0; frameId < frameCount; ++frameId)
		{
			PluginFillThresholdColors(animationId, frameId, threshold, color);
		}
	}

	EXPORT_API void PluginFillThresholdColorsAllFramesName(const char* path, int threshold, int color)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginFillThresholdColorsAllFramesName: Animation not found! %s\r\n", path);
			return;
		}
		PluginFillThresholdColorsAllFrames(animationId, threshold, color);
	}

	EXPORT_API double PluginFillThresholdColorsAllFramesNameD(const char* path, double threshold, double color)
	{
		PluginFillThresholdColorsAllFramesName(path, (int)threshold, (int)color);
		return 0;
	}


	EXPORT_API void PluginFillColorAllFramesRGB(int animationId, int red, int green, int blue)
	{
		PluginStopAnimation(animationId);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		int frameCount = PluginGetFrameCount(animationId);
		for (int frameId = 0; frameId < frameCount; ++frameId)
		{
			PluginFillColorRGB(animationId, frameId, red, green, blue);
		}
	}

	EXPORT_API void PluginFillColorAllFramesRGBName(const char* path, int red, int green, int blue)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginFillColorAllFramesRGBName: Animation not found! %s\r\n", path);
			return;
		}
		PluginFillColorAllFramesRGB(animationId, red, green, blue);
	}

	EXPORT_API double PluginFillColorAllFramesRGBNameD(const char* path, double red, double green, double blue)
	{
		PluginFillColorAllFramesRGBName(path, (int)red, (int)green, (int)blue);
		return 0;
	}


	EXPORT_API void PluginFillThresholdColorsAllFramesRGB(int animationId, int threshold, int red, int green, int blue)
	{
		PluginStopAnimation(animationId);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		int frameCount = PluginGetFrameCount(animationId);
		for (int frameId = 0; frameId < frameCount; ++frameId)
		{
			PluginFillThresholdColorsRGB(animationId, frameId, threshold, red, green, blue);
		}
	}

	EXPORT_API void PluginFillThresholdColorsAllFramesRGBName(const char* path, int threshold, int red, int green, int blue)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginFillThresholdColorsAllFramesRGBName: Animation not found! %s\r\n", path);
			return;
		}
		PluginFillThresholdColorsAllFramesRGB(animationId, threshold, red, green, blue);
	}

	EXPORT_API double PluginFillThresholdColorsAllFramesRGBNameD(const char* path, double threshold, double red, double green, double blue)
	{
		PluginFillThresholdColorsAllFramesRGBName(path, (int)threshold, (int)red, (int)green, (int)blue);
		return 0;
	}


	EXPORT_API void PluginFillThresholdRGBColorsAllFramesRGB(int animationId, int redThreshold, int greenThreshold, int blueThreshold, int red, int green, int blue)
	{
		PluginStopAnimation(animationId);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		int frameCount = PluginGetFrameCount(animationId);
		for (int frameId = 0; frameId < frameCount; ++frameId)
		{
			PluginFillThresholdRGBColorsRGB(animationId, frameId, redThreshold, greenThreshold, blueThreshold, red, green, blue);
		}
	}

	EXPORT_API void PluginFillThresholdRGBColorsAllFramesRGBName(const char* path, int redThreshold, int greenThreshold, int blueThreshold, int red, int green, int blue)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginFillThresholdRGBColorsAllFramesRGBName: Animation not found! %s\r\n", path);
			return;
		}
		PluginFillThresholdRGBColorsAllFramesRGB(animationId, redThreshold, greenThreshold, blueThreshold, red, green, blue);
	}

	EXPORT_API double PluginFillThresholdRGBColorsAllFramesRGBNameD(const char* path, double redThreshold, double greenThreshold, double blueThreshold, double red, double green, double blue)
	{
		PluginFillThresholdRGBColorsAllFramesRGBName(path, (int)redThreshold, (int)greenThreshold, (int)blueThreshold, (int)red, (int)green, (int)blue);
		return 0;
	}


	EXPORT_API void PluginFillThresholdColorsMinMaxAllFramesRGB(int animationId, int minThreshold, int minRed, int minGreen, int minBlue, int maxThreshold, int maxRed, int maxGreen, int maxBlue)
	{
		PluginStopAnimation(animationId);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		int frameCount = PluginGetFrameCount(animationId);
		for (int frameId = 0; frameId < frameCount; ++frameId)
		{
			PluginFillThresholdColorsMinMaxRGB(animationId, frameId, minThreshold, minRed, minGreen, minBlue, maxThreshold, maxRed, maxGreen, maxBlue);
		}
	}

	EXPORT_API void PluginFillThresholdColorsMinMaxAllFramesRGBName(const char* path, int minThreshold, int minRed, int minGreen, int minBlue, int maxThreshold, int maxRed, int maxGreen, int maxBlue)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginFillThresholdColorsAllFramesRGBName: Animation not found! %s\r\n", path);
			return;
		}
		PluginFillThresholdColorsMinMaxAllFramesRGB(animationId, minThreshold, minRed, minGreen, minBlue, maxThreshold, maxRed, maxGreen, maxBlue);
	}

	EXPORT_API double PluginFillThresholdColorsMinMaxAllFramesRGBNameD(const char* path, double minThreshold, double minRed, double minGreen, double minBlue, double maxThreshold, double maxRed, double maxGreen, double maxBlue)
	{
		PluginFillThresholdColorsMinMaxAllFramesRGBName(path, (int)minThreshold, (int)minRed, (int)minGreen, (int)minBlue, (int)maxThreshold, (int)maxRed, (int)maxGreen, (int)maxBlue);
		return 0;
	}


	EXPORT_API void PluginFillNonZeroColor(int animationId, int frameId, int color)
	{
		PluginStopAnimation(animationId);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		switch (animation->GetDeviceType())
		{
		case EChromaSDKDeviceTypeEnum::DE_1D:
		{
			Animation1D* animation1D = (Animation1D*)(animation);
			vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
			if (frameId >= 0 &&
				frameId < (int)frames.size())
			{
				FChromaSDKColorFrame1D& frame = frames[frameId];
				int maxLeds = ChromaSDKPlugin::GetInstance()->GetMaxLeds(animation1D->GetDevice());
				vector<COLORREF>& colors = frame.Colors;
				for (int i = 0; i < maxLeds; ++i)
				{
					if (colors[i] != 0)
					{
						colors[i] = color;
					}
				}
			}
		}
		break;
		case EChromaSDKDeviceTypeEnum::DE_2D:
		{
			Animation2D* animation2D = (Animation2D*)(animation);
			vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
			if (frameId >= 0 &&
				frameId < (int)frames.size())
			{
				FChromaSDKColorFrame2D& frame = frames[frameId];
				int maxRow = ChromaSDKPlugin::GetInstance()->GetMaxRow(animation2D->GetDevice());
				int maxColumn = ChromaSDKPlugin::GetInstance()->GetMaxColumn(animation2D->GetDevice());
				for (int i = 0; i < maxRow; ++i)
				{
					FChromaSDKColors& row = frame.Colors[i];
					for (int j = 0; j < maxColumn; ++j)
					{
						if (row.Colors[j] != 0)
						{
							row.Colors[j] = color;
						}
					}
				}
			}
		}
		break;
		}
	}

	EXPORT_API void PluginFillNonZeroColorName(const char* path, int frameId, int color)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginFillNonZeroColorName: Animation not found! %s\r\n", path);
			return;
		}
		PluginFillNonZeroColor(animationId, frameId, color);
	}

	EXPORT_API double PluginFillNonZeroColorNameD(const char* path, double frameId, double color)
	{
		PluginFillNonZeroColorName(path, (int)frameId, (int)color);
		return 0;
	}


	EXPORT_API void PluginFillNonZeroColorRGB(int animationId, int frameId, int red, int green, int blue)
	{
		//clamp values
		red = max(0, min(255, red));
		green = max(0, min(255, green));
		blue = max(0, min(255, blue));
		int color = (red & 0xFF) | ((green & 0xFF) << 8) | ((blue & 0xFF) << 16);

		PluginStopAnimation(animationId);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		switch (animation->GetDeviceType())
		{
		case EChromaSDKDeviceTypeEnum::DE_1D:
		{
			Animation1D* animation1D = (Animation1D*)(animation);
			vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
			if (frameId >= 0 &&
				frameId < (int)frames.size())
			{
				FChromaSDKColorFrame1D& frame = frames[frameId];
				int maxLeds = ChromaSDKPlugin::GetInstance()->GetMaxLeds(animation1D->GetDevice());
				vector<COLORREF>& colors = frame.Colors;
				for (int i = 0; i < maxLeds; ++i)
				{
					if (colors[i] != 0)
					{
						colors[i] = color;
					}
				}
			}
		}
		break;
		case EChromaSDKDeviceTypeEnum::DE_2D:
		{
			Animation2D* animation2D = (Animation2D*)(animation);
			vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
			if (frameId >= 0 &&
				frameId < (int)frames.size())
			{
				FChromaSDKColorFrame2D& frame = frames[frameId];
				int maxRow = ChromaSDKPlugin::GetInstance()->GetMaxRow(animation2D->GetDevice());
				int maxColumn = ChromaSDKPlugin::GetInstance()->GetMaxColumn(animation2D->GetDevice());
				for (int i = 0; i < maxRow; ++i)
				{
					FChromaSDKColors& row = frame.Colors[i];
					for (int j = 0; j < maxColumn; ++j)
					{
						if (row.Colors[j] != 0)
						{
							row.Colors[j] = color;
						}
					}
				}
			}
		}
		break;
		}
	}

	EXPORT_API void PluginFillNonZeroColorRGBName(const char* path, int frameId, int red, int green, int blue)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginFillNonZeroColorRGBName: Animation not found! %s\r\n", path);
			return;
		}
		PluginFillNonZeroColorRGB(animationId, frameId, red, green, blue);
	}

	EXPORT_API double PluginFillNonZeroColorRGBNameD(const char* path, double frameId, double red, double green, double blue)
	{
		PluginFillNonZeroColorRGBName(path, (int)frameId, (int)red, (int)green, (int)blue);
		return 0;
	}


	EXPORT_API void PluginFillZeroColor(int animationId, int frameId, int color)
	{
		PluginStopAnimation(animationId);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		switch (animation->GetDeviceType())
		{
		case EChromaSDKDeviceTypeEnum::DE_1D:
		{
			Animation1D* animation1D = (Animation1D*)(animation);
			vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
			if (frameId >= 0 &&
				frameId < (int)frames.size())
			{
				FChromaSDKColorFrame1D& frame = frames[frameId];
				int maxLeds = ChromaSDKPlugin::GetInstance()->GetMaxLeds(animation1D->GetDevice());
				vector<COLORREF>& colors = frame.Colors;
				for (int i = 0; i < maxLeds; ++i)
				{
					if (colors[i] == 0)
					{
						colors[i] = color;
					}
				}
			}
		}
		break;
		case EChromaSDKDeviceTypeEnum::DE_2D:
		{
			Animation2D* animation2D = (Animation2D*)(animation);
			vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
			if (frameId >= 0 &&
				frameId < (int)frames.size())
			{
				FChromaSDKColorFrame2D& frame = frames[frameId];
				int maxRow = ChromaSDKPlugin::GetInstance()->GetMaxRow(animation2D->GetDevice());
				int maxColumn = ChromaSDKPlugin::GetInstance()->GetMaxColumn(animation2D->GetDevice());
				for (int i = 0; i < maxRow; ++i)
				{
					FChromaSDKColors& row = frame.Colors[i];
					for (int j = 0; j < maxColumn; ++j)
					{
						if (row.Colors[j] == 0)
						{
							row.Colors[j] = color;
						}
					}
				}
			}
		}
		break;
		}
	}

	EXPORT_API void PluginFillZeroColorName(const char* path, int frameId, int color)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginFillZeroColorName: Animation not found! %s\r\n", path);
			return;
		}
		PluginFillZeroColor(animationId, frameId, color);
	}

	EXPORT_API double PluginFillZeroColorNameD(const char* path, double frameId, double color)
	{
		PluginFillZeroColorName(path, (int)frameId, (int)color);
		return 0;
	}


	EXPORT_API void PluginFillZeroColorRGB(int animationId, int frameId, int red, int green, int blue)
	{
		//clamp values
		red = max(0, min(255, red));
		green = max(0, min(255, green));
		blue = max(0, min(255, blue));
		int color = (red & 0xFF) | ((green & 0xFF) << 8) | ((blue & 0xFF) << 16);

		PluginStopAnimation(animationId);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		switch (animation->GetDeviceType())
		{
		case EChromaSDKDeviceTypeEnum::DE_1D:
		{
			Animation1D* animation1D = (Animation1D*)(animation);
			vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
			if (frameId >= 0 &&
				frameId < (int)frames.size())
			{
				FChromaSDKColorFrame1D& frame = frames[frameId];
				int maxLeds = ChromaSDKPlugin::GetInstance()->GetMaxLeds(animation1D->GetDevice());
				vector<COLORREF>& colors = frame.Colors;
				for (int i = 0; i < maxLeds; ++i)
				{
					if (colors[i] == 0)
					{
						colors[i] = color;
					}
				}
			}
		}
		break;
		case EChromaSDKDeviceTypeEnum::DE_2D:
		{
			Animation2D* animation2D = (Animation2D*)(animation);
			vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
			if (frameId >= 0 &&
				frameId < (int)frames.size())
			{
				FChromaSDKColorFrame2D& frame = frames[frameId];
				int maxRow = ChromaSDKPlugin::GetInstance()->GetMaxRow(animation2D->GetDevice());
				int maxColumn = ChromaSDKPlugin::GetInstance()->GetMaxColumn(animation2D->GetDevice());
				for (int i = 0; i < maxRow; ++i)
				{
					FChromaSDKColors& row = frame.Colors[i];
					for (int j = 0; j < maxColumn; ++j)
					{
						if (row.Colors[j] == 0)
						{
							row.Colors[j] = color;
						}
					}
				}
			}
		}
		break;
		}
	}

	EXPORT_API void PluginFillZeroColorRGBName(const char* path, int frameId, int red, int green, int blue)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginFillZeroColorRGBName: Animation not found! %s\r\n", path);
			return;
		}
		PluginFillZeroColorRGB(animationId, frameId, red, green, blue);
	}

	EXPORT_API double PluginFillZeroColorRGBNameD(const char* path, double frameId, double red, double green, double blue)
	{
		PluginFillZeroColorRGBName(path, (int)frameId, (int)red, (int)green, (int)blue);
		return 0;
	}


	EXPORT_API void PluginFillNonZeroColorAllFrames(int animationId, int color)
	{
		PluginStopAnimation(animationId);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		int frameCount = PluginGetFrameCount(animationId);
		for (int frameId = 0; frameId < frameCount; ++frameId)
		{
			PluginFillNonZeroColor(animationId, frameId, color);
		}
	}

	EXPORT_API void PluginFillNonZeroColorAllFramesName(const char* path, int color)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginFillNonZeroColorAllFramesName: Animation not found! %s\r\n", path);
			return;
		}
		PluginFillNonZeroColorAllFrames(animationId, color);
	}

	EXPORT_API double PluginFillNonZeroColorAllFramesNameD(const char* path, double color)
	{
		PluginFillNonZeroColorAllFramesName(path, (int)color);
		return 0;
	}


	EXPORT_API void PluginFillNonZeroColorAllFramesRGB(int animationId, int red, int green, int blue)
	{
		PluginStopAnimation(animationId);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		int frameCount = PluginGetFrameCount(animationId);
		for (int frameId = 0; frameId < frameCount; ++frameId)
		{
			PluginFillNonZeroColorRGB(animationId, frameId, red, green, blue);
		}
	}

	EXPORT_API void PluginFillNonZeroColorAllFramesRGBName(const char* path, int red, int green, int blue)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginFillNonZeroColorAllFramesRGBName: Animation not found! %s\r\n", path);
			return;
		}
		PluginFillNonZeroColorAllFramesRGB(animationId, red, green, blue);
	}

	EXPORT_API double PluginFillNonZeroColorAllFramesRGBNameD(const char* path, double red, double green, double blue)
	{
		PluginFillNonZeroColorAllFramesRGBName(path, (int)red, (int)green, (int)blue);
		return 0;
	}


	EXPORT_API void PluginFillZeroColorAllFrames(int animationId, int color)
	{
		PluginStopAnimation(animationId);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		int frameCount = PluginGetFrameCount(animationId);
		for (int frameId = 0; frameId < frameCount; ++frameId)
		{
			PluginFillZeroColor(animationId, frameId, color);
		}
	}

	EXPORT_API void PluginFillZeroColorAllFramesName(const char* path, int color)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginFillZeroColorAllFramesName: Animation not found! %s\r\n", path);
			return;
		}
		PluginFillZeroColorAllFrames(animationId, color);
	}

	EXPORT_API double PluginFillZeroColorAllFramesNameD(const char* path, double color)
	{
		PluginFillZeroColorAllFramesName(path, (int)color);
		return 0;
	}


	EXPORT_API void PluginFillZeroColorAllFramesRGB(int animationId, int red, int green, int blue)
	{
		PluginStopAnimation(animationId);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		int frameCount = PluginGetFrameCount(animationId);
		for (int frameId = 0; frameId < frameCount; ++frameId)
		{
			PluginFillZeroColorRGB(animationId, frameId, red, green, blue);
		}
	}

	EXPORT_API void PluginFillZeroColorAllFramesRGBName(const char* path, int red, int green, int blue)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginFillZeroColorAllFramesRGBName: Animation not found! %s\r\n", path);
			return;
		}
		PluginFillZeroColorAllFramesRGB(animationId, red, green, blue);
	}

	EXPORT_API double PluginFillZeroColorAllFramesRGBNameD(const char* path, double red, double green, double blue)
	{
		PluginFillZeroColorAllFramesRGBName(path, (int)red, (int)green, (int)blue);
		return 0;
	}


	EXPORT_API void PluginFillRandomColors(int animationId, int frameId)
	{
		PluginStopAnimation(animationId);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		int frameCount = PluginGetFrameCount(animationId);
		if (frameId >= 0 && frameId < frameCount)
		{
			switch (animation->GetDeviceType())
			{
			case EChromaSDKDeviceTypeEnum::DE_1D:
			{
				Animation1D* animation1D = (Animation1D*)(animation);
				vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
				if (frameId >= 0 &&
					frameId < (int)frames.size())
				{
					FChromaSDKColorFrame1D& frame = frames[frameId];
					frame.Colors = ChromaSDKPlugin::GetInstance()->CreateRandomColors1D(animation1D->GetDevice());
				}
			}
			break;
			case EChromaSDKDeviceTypeEnum::DE_2D:
			{
				Animation2D* animation2D = (Animation2D*)(animation);
				vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
				if (frameId >= 0 &&
					frameId < (int)frames.size())
				{
					FChromaSDKColorFrame2D& frame = frames[frameId];
					frame.Colors = ChromaSDKPlugin::GetInstance()->CreateRandomColors2D(animation2D->GetDevice());
				}
			}
			break;
			}
		}
	}

	EXPORT_API void PluginFillRandomColorsName(const char* path, int frameId)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginFillRandomColorsName: Animation not found! %s\r\n", path);
			return;
		}
		PluginFillRandomColors(animationId, frameId);
	}

	EXPORT_API double PluginFillRandomColorsNameD(const char* path, double frameId)
	{
		PluginFillRandomColorsName(path, (int)frameId);
		return 0;
	}


	EXPORT_API void PluginFillRandomColorsAllFrames(int animationId)
	{
		PluginStopAnimation(animationId);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		int frameCount = PluginGetFrameCount(animationId);
		for (int frameId = 0; frameId < frameCount; ++frameId)
		{
			switch (animation->GetDeviceType())
			{
			case EChromaSDKDeviceTypeEnum::DE_1D:
			{
				Animation1D* animation1D = (Animation1D*)(animation);
				vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
				if (frameId >= 0 &&
					frameId < (int)frames.size())
				{
					FChromaSDKColorFrame1D& frame = frames[frameId];
					frame.Colors = ChromaSDKPlugin::GetInstance()->CreateRandomColors1D(animation1D->GetDevice());
				}
			}
			break;
			case EChromaSDKDeviceTypeEnum::DE_2D:
			{
				Animation2D* animation2D = (Animation2D*)(animation);
				vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
				if (frameId >= 0 &&
					frameId < (int)frames.size())
				{
					FChromaSDKColorFrame2D& frame = frames[frameId];
					frame.Colors = ChromaSDKPlugin::GetInstance()->CreateRandomColors2D(animation2D->GetDevice());
				}
			}
			break;
			}
		}
	}

	EXPORT_API void PluginFillRandomColorsAllFramesName(const char* path)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginFillRandomColorsAllFramesName: Animation not found! %s\r\n", path);
			return;
		}
		PluginFillRandomColorsAllFrames(animationId);
	}

	EXPORT_API double PluginFillRandomColorsAllFramesNameD(const char* path)
	{
		PluginFillRandomColorsAllFramesName(path);
		return 0;
	}


	EXPORT_API void PluginFillRandomColorsBlackAndWhite(int animationId, int frameId)
	{
		PluginStopAnimation(animationId);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		int frameCount = PluginGetFrameCount(animationId);
		if (frameId >= 0 && frameId < frameCount)
		{
			switch (animation->GetDeviceType())
			{
			case EChromaSDKDeviceTypeEnum::DE_1D:
			{
				Animation1D* animation1D = (Animation1D*)(animation);
				vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
				if (frameId >= 0 &&
					frameId < (int)frames.size())
				{
					FChromaSDKColorFrame1D& frame = frames[frameId];
					frame.Colors = ChromaSDKPlugin::GetInstance()->CreateRandomColorsBlackAndWhite1D(animation1D->GetDevice());
				}
			}
			break;
			case EChromaSDKDeviceTypeEnum::DE_2D:
			{
				Animation2D* animation2D = (Animation2D*)(animation);
				vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
				if (frameId >= 0 &&
					frameId < (int)frames.size())
				{
					FChromaSDKColorFrame2D& frame = frames[frameId];
					frame.Colors = ChromaSDKPlugin::GetInstance()->CreateRandomColorsBlackAndWhite2D(animation2D->GetDevice());
				}
			}
			break;
			}
		}
	}

	EXPORT_API void PluginFillRandomColorsBlackAndWhiteName(const char* path, int frameId)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginFillRandomColorsBlackAndWhiteName: Animation not found! %s\r\n", path);
			return;
		}
		PluginFillRandomColorsBlackAndWhite(animationId, frameId);
	}

	EXPORT_API double PluginFillRandomColorsBlackAndWhiteNameD(const char* path, double frameId)
	{
		PluginFillRandomColorsBlackAndWhiteName(path, (int)frameId);
		return 0;
	}


	EXPORT_API void PluginFillRandomColorsBlackAndWhiteAllFrames(int animationId)
	{
		PluginStopAnimation(animationId);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		int frameCount = PluginGetFrameCount(animationId);
		for (int frameId = 0; frameId < frameCount; ++frameId)
		{
			switch (animation->GetDeviceType())
			{
			case EChromaSDKDeviceTypeEnum::DE_1D:
			{
				Animation1D* animation1D = (Animation1D*)(animation);
				vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
				if (frameId >= 0 &&
					frameId < (int)frames.size())
				{
					FChromaSDKColorFrame1D& frame = frames[frameId];
					frame.Colors = ChromaSDKPlugin::GetInstance()->CreateRandomColorsBlackAndWhite1D(animation1D->GetDevice());
				}
			}
			break;
			case EChromaSDKDeviceTypeEnum::DE_2D:
			{
				Animation2D* animation2D = (Animation2D*)(animation);
				vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
				if (frameId >= 0 &&
					frameId < (int)frames.size())
				{
					FChromaSDKColorFrame2D& frame = frames[frameId];
					frame.Colors = ChromaSDKPlugin::GetInstance()->CreateRandomColorsBlackAndWhite2D(animation2D->GetDevice());
				}
			}
			break;
			}
		}
	}

	EXPORT_API void PluginFillRandomColorsBlackAndWhiteAllFramesName(const char* path)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginFillRandomColorsBlackAndWhiteNameAllFrames: Animation not found! %s\r\n", path);
			return;
		}
		PluginFillRandomColorsBlackAndWhiteAllFrames(animationId);
	}

	EXPORT_API double PluginFillRandomColorsBlackAndWhiteAllFramesNameD(const char* path)
	{
		PluginFillRandomColorsBlackAndWhiteAllFramesName(path);
		return 0;
	}


	EXPORT_API void PluginInvertColors(int animationId, int frameId)
	{
		PluginStopAnimation(animationId);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		int frameCount = PluginGetFrameCount(animationId);
		if (frameId >= 0 && frameId < frameCount)
		{
			switch (animation->GetDeviceType())
			{
			case EChromaSDKDeviceTypeEnum::DE_1D:
			{
				Animation1D* animation1D = (Animation1D*)(animation);
				vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
				if (frameId >= 0 &&
					frameId < (int)frames.size())
				{
					FChromaSDKColorFrame1D& frame = frames[frameId];
					int maxLeds = ChromaSDKPlugin::GetInstance()->GetMaxLeds(animation1D->GetDevice());
					vector<COLORREF>& colors = frame.Colors;
					for (int i = 0; i < maxLeds; ++i)
					{
						int color = colors[i];
						int red = 255 - (color & 0xFF);
						int green = 255 - ((color & 0xFF00) >> 8);
						int blue = 255 - ((color & 0xFF0000) >> 16);
						color = (red & 0xFF) | ((green & 0xFF) << 8) | ((blue & 0xFF) << 16);
						colors[i] = color;
					}
				}
			}
			break;
			case EChromaSDKDeviceTypeEnum::DE_2D:
			{
				Animation2D* animation2D = (Animation2D*)(animation);
				vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
				if (frameId >= 0 &&
					frameId < (int)frames.size())
				{
					FChromaSDKColorFrame2D& frame = frames[frameId];
					int maxRow = ChromaSDKPlugin::GetInstance()->GetMaxRow(animation2D->GetDevice());
					int maxColumn = ChromaSDKPlugin::GetInstance()->GetMaxColumn(animation2D->GetDevice());
					for (int i = 0; i < maxRow; ++i)
					{
						FChromaSDKColors& row = frame.Colors[i];
						for (int j = 0; j < maxColumn; ++j)
						{
							int color = row.Colors[j];
							int red = 255 - (color & 0xFF);
							int green = 255 - ((color & 0xFF00) >> 8);
							int blue = 255 - ((color & 0xFF0000) >> 16);
							color = (red & 0xFF) | ((green & 0xFF) << 8) | ((blue & 0xFF) << 16);
							row.Colors[j] = color;
						}
					}
				}
			}
			break;
			}
		}
	}

	EXPORT_API void PluginInvertColorsName(const char* path, int frameId)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginInvertColorsName: Animation not found! %s\r\n", path);
			return;
		}
		PluginInvertColors(animationId, frameId);
	}

	EXPORT_API double PluginInvertColorsNameD(const char* path, double frameId)
	{
		PluginInvertColorsName(path, (int)frameId);
		return 0;
	}


	EXPORT_API void PluginInvertColorsAllFrames(int animationId)
	{
		PluginStopAnimation(animationId);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		int frameCount = PluginGetFrameCount(animationId);
		for (int frameId = 0; frameId < frameCount; ++frameId)
		{
			switch (animation->GetDeviceType())
			{
			case EChromaSDKDeviceTypeEnum::DE_1D:
			{
				Animation1D* animation1D = (Animation1D*)(animation);
				vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
				if (frameId >= 0 &&
					frameId < (int)frames.size())
				{
					FChromaSDKColorFrame1D& frame = frames[frameId];
					int maxLeds = ChromaSDKPlugin::GetInstance()->GetMaxLeds(animation1D->GetDevice());
					vector<COLORREF>& colors = frame.Colors;
					for (int i = 0; i < maxLeds; ++i)
					{
						int color = colors[i];
						int red = 255 - (color & 0xFF);
						int green = 255 - ((color & 0xFF00) >> 8);
						int blue = 255 - ((color & 0xFF0000) >> 16);
						color = (red & 0xFF) | ((green & 0xFF) << 8) | ((blue & 0xFF) << 16);
						colors[i] = color;
					}
				}
			}
			break;
			case EChromaSDKDeviceTypeEnum::DE_2D:
			{
				Animation2D* animation2D = (Animation2D*)(animation);
				vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
				if (frameId >= 0 &&
					frameId < (int)frames.size())
				{
					FChromaSDKColorFrame2D& frame = frames[frameId];
					int maxRow = ChromaSDKPlugin::GetInstance()->GetMaxRow(animation2D->GetDevice());
					int maxColumn = ChromaSDKPlugin::GetInstance()->GetMaxColumn(animation2D->GetDevice());
					for (int i = 0; i < maxRow; ++i)
					{
						FChromaSDKColors& row = frame.Colors[i];
						for (int j = 0; j < maxColumn; ++j)
						{
							int color = row.Colors[j];
							int red = 255 - (color & 0xFF);
							int green = 255 - ((color & 0xFF00) >> 8);
							int blue = 255 - ((color & 0xFF0000) >> 16);
							color = (red & 0xFF) | ((green & 0xFF) << 8) | ((blue & 0xFF) << 16);
							row.Colors[j] = color;
						}
					}
				}
			}
			break;
			}
		}
	}

	EXPORT_API void PluginInvertColorsAllFramesName(const char* path)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginInvertColorsAllFramesName: Animation not found! %s\r\n", path);
			return;
		}
		PluginInvertColorsAllFrames(animationId);
	}

	EXPORT_API double PluginInvertColorsAllFramesNameD(const char* path)
	{
		PluginInvertColorsAllFramesName(path);
		return 0;
	}


	EXPORT_API void PluginOffsetColors(int animationId, int frameId, int offsetRed, int offsetGreen, int offsetBlue)
	{
		PluginStopAnimation(animationId);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		switch (animation->GetDeviceType())
		{
		case EChromaSDKDeviceTypeEnum::DE_1D:
		{
			Animation1D* animation1D = (Animation1D*)(animation);
			vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
			if (frameId >= 0 &&
				frameId < (int)frames.size())
			{
				FChromaSDKColorFrame1D& frame = frames[frameId];
				int maxLeds = ChromaSDKPlugin::GetInstance()->GetMaxLeds(animation1D->GetDevice());
				vector<COLORREF>& colors = frame.Colors;
				for (int i = 0; i < maxLeds; ++i)
				{
					int color = colors[i];
					int red = (color & 0xFF);
					int green = (color & 0xFF00) >> 8;
					int blue = (color & 0xFF0000) >> 16;
					red = max(0, min(255, red + offsetRed));
					green = max(0, min(255, green + offsetGreen));
					blue = max(0, min(255, blue + offsetBlue));
					color = (red & 0xFF) | ((green & 0xFF) << 8) | ((blue & 0xFF) << 16);
					colors[i] = color;
				}
			}
		}
		break;
		case EChromaSDKDeviceTypeEnum::DE_2D:
		{
			Animation2D* animation2D = (Animation2D*)(animation);
			vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
			if (frameId >= 0 &&
				frameId < (int)frames.size())
			{
				FChromaSDKColorFrame2D& frame = frames[frameId];
				int maxRow = ChromaSDKPlugin::GetInstance()->GetMaxRow(animation2D->GetDevice());
				int maxColumn = ChromaSDKPlugin::GetInstance()->GetMaxColumn(animation2D->GetDevice());
				for (int i = 0; i < maxRow; ++i)
				{
					FChromaSDKColors& row = frame.Colors[i];
					for (int j = 0; j < maxColumn; ++j)
					{
						int color = row.Colors[j];
						int red = (color & 0xFF);
						int green = (color & 0xFF00) >> 8;
						int blue = (color & 0xFF0000) >> 16;
						red = max(0, min(255, red + offsetRed));
						green = max(0, min(255, green + offsetGreen));
						blue = max(0, min(255, blue + offsetBlue));
						color = (red & 0xFF) | ((green & 0xFF) << 8) | ((blue & 0xFF) << 16);
						row.Colors[j] = color;
					}
				}
			}
		}
		break;
		}
	}

	EXPORT_API void PluginOffsetColorsName(const char* path, int frameId, int red, int green, int blue)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginOffsetColorsName: Animation not found! %s\r\n", path);
			return;
		}
		PluginOffsetColors(animationId, frameId, red, green, blue);
	}

	EXPORT_API double PluginOffsetColorsNameD(const char* path, double frameId, double red, double green, double blue)
	{
		PluginOffsetColorsName(path, (int)frameId, (int)red, (int)green, (int)blue);
		return 0;
	}


	EXPORT_API void PluginOffsetColorsAllFrames(int animationId, int offsetRed, int offsetGreen, int offsetBlue)
	{
		PluginStopAnimation(animationId);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		int frameCount = PluginGetFrameCount(animationId);
		for (int frameId = 0; frameId < frameCount; ++frameId)
		{
			PluginOffsetColors(animationId, frameId, offsetRed, offsetGreen, offsetBlue);
		}
	}

	EXPORT_API void PluginOffsetColorsAllFramesName(const char* path, int red, int green, int blue)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginOffsetColorsAllFramesName: Animation not found! %s\r\n", path);
			return;
		}
		PluginOffsetColorsAllFrames(animationId, red, green, blue);
	}

	EXPORT_API double PluginOffsetColorsAllFramesNameD(const char* path, double red, double green, double blue)
	{
		PluginOffsetColorsAllFramesName(path, (int)red, (int)green, (int)blue);
		return 0;
	}


	EXPORT_API void PluginOffsetNonZeroColors(int animationId, int frameId, int offsetRed, int offsetGreen, int offsetBlue)
	{
		PluginStopAnimation(animationId);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		switch (animation->GetDeviceType())
		{
		case EChromaSDKDeviceTypeEnum::DE_1D:
		{
			Animation1D* animation1D = (Animation1D*)(animation);
			vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
			if (frameId >= 0 &&
				frameId < (int)frames.size())
			{
				FChromaSDKColorFrame1D& frame = frames[frameId];
				int maxLeds = ChromaSDKPlugin::GetInstance()->GetMaxLeds(animation1D->GetDevice());
				vector<COLORREF>& colors = frame.Colors;
				for (int i = 0; i < maxLeds; ++i)
				{
					int color = colors[i];
					if (color != 0)
					{
						int red = (color & 0xFF);
						int green = (color & 0xFF00) >> 8;
						int blue = (color & 0xFF0000) >> 16;
						red = max(0, min(255, red + offsetRed));
						green = max(0, min(255, green + offsetGreen));
						blue = max(0, min(255, blue + offsetBlue));
						color = (red & 0xFF) | ((green & 0xFF) << 8) | ((blue & 0xFF) << 16);
						colors[i] = color;
					}
				}
			}
		}
		break;
		case EChromaSDKDeviceTypeEnum::DE_2D:
		{
			Animation2D* animation2D = (Animation2D*)(animation);
			vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
			if (frameId >= 0 &&
				frameId < (int)frames.size())
			{
				FChromaSDKColorFrame2D& frame = frames[frameId];
				int maxRow = ChromaSDKPlugin::GetInstance()->GetMaxRow(animation2D->GetDevice());
				int maxColumn = ChromaSDKPlugin::GetInstance()->GetMaxColumn(animation2D->GetDevice());
				for (int i = 0; i < maxRow; ++i)
				{
					FChromaSDKColors& row = frame.Colors[i];
					for (int j = 0; j < maxColumn; ++j)
					{
						int color = row.Colors[j];
						if (color != 0)
						{
							int red = (color & 0xFF);
							int green = (color & 0xFF00) >> 8;
							int blue = (color & 0xFF0000) >> 16;
							red = max(0, min(255, red + offsetRed));
							green = max(0, min(255, green + offsetGreen));
							blue = max(0, min(255, blue + offsetBlue));
							color = (red & 0xFF) | ((green & 0xFF) << 8) | ((blue & 0xFF) << 16);
							row.Colors[j] = color;
						}
					}
				}
			}
		}
		break;
		}
	}

	EXPORT_API void PluginOffsetNonZeroColorsName(const char* path, int frameId, int red, int green, int blue)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginOffsetNonZeroColorsName: Animation not found! %s\r\n", path);
			return;
		}
		PluginOffsetNonZeroColors(animationId, frameId, red, green, blue);
	}

	EXPORT_API double PluginOffsetNonZeroColorsNameD(const char* path, double frameId, double red, double green, double blue)
	{
		PluginOffsetNonZeroColorsName(path, (int)frameId, (int)red, (int)green, (int)blue);
		return 0;
	}


	EXPORT_API void PluginOffsetNonZeroColorsAllFrames(int animationId, int offsetRed, int offsetGreen, int offsetBlue)
	{
		PluginStopAnimation(animationId);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		int frameCount = PluginGetFrameCount(animationId);
		for (int frameId = 0; frameId < frameCount; ++frameId)
		{
			PluginOffsetNonZeroColors(animationId, frameId, offsetRed, offsetGreen, offsetBlue);
		}
	}

	EXPORT_API void PluginOffsetNonZeroColorsAllFramesName(const char* path, int red, int green, int blue)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginOffsetNonZeroColorsAllFramesName: Animation not found! %s\r\n", path);
			return;
		}
		PluginOffsetNonZeroColorsAllFrames(animationId, red, green, blue);
	}

	EXPORT_API double PluginOffsetNonZeroColorsAllFramesNameD(const char* path, double red, double green, double blue)
	{
		PluginOffsetNonZeroColorsAllFramesName(path, (int)red, (int)green, (int)blue);
		return 0;
	}


	EXPORT_API void PluginMultiplyIntensity(int animationId, int frameId, float intensity)
	{
		PluginStopAnimation(animationId);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		switch (animation->GetDeviceType())
		{
		case EChromaSDKDeviceTypeEnum::DE_1D:
		{
			Animation1D* animation1D = (Animation1D*)(animation);
			vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
			if (frameId >= 0 &&
				frameId < (int)frames.size())
			{
				FChromaSDKColorFrame1D& frame = frames[frameId];
				int maxLeds = ChromaSDKPlugin::GetInstance()->GetMaxLeds(animation1D->GetDevice());
				vector<COLORREF>& colors = frame.Colors;
				for (int i = 0; i < maxLeds; ++i)
				{
					int color = colors[i];
					int red = (color & 0xFF);
					int green = (color & 0xFF00) >> 8;
					int blue = (color & 0xFF0000) >> 16;
					red = max(0, min(255, (int)(red * intensity)));
					green = max(0, min(255, (int)(green * intensity)));
					blue = max(0, min(255, (int)(blue * intensity)));
					color = (red & 0xFF) | ((green & 0xFF) << 8) | ((blue & 0xFF) << 16);
					colors[i] = color;
				}
			}
		}
		break;
		case EChromaSDKDeviceTypeEnum::DE_2D:
		{
			Animation2D* animation2D = (Animation2D*)(animation);
			vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
			if (frameId >= 0 &&
				frameId < (int)frames.size())
			{
				FChromaSDKColorFrame2D& frame = frames[frameId];
				int maxRow = ChromaSDKPlugin::GetInstance()->GetMaxRow(animation2D->GetDevice());
				int maxColumn = ChromaSDKPlugin::GetInstance()->GetMaxColumn(animation2D->GetDevice());
				for (int i = 0; i < maxRow; ++i)
				{
					FChromaSDKColors& row = frame.Colors[i];
					for (int j = 0; j < maxColumn; ++j)
					{
						int color = row.Colors[j];
						int red = (color & 0xFF);
						int green = (color & 0xFF00) >> 8;
						int blue = (color & 0xFF0000) >> 16;
						red = max(0, min(255, (int)(red * intensity)));
						green = max(0, min(255, (int)(green * intensity)));
						blue = max(0, min(255, (int)(blue * intensity)));
						color = (red & 0xFF) | ((green & 0xFF) << 8) | ((blue & 0xFF) << 16);
						row.Colors[j] = color;
					}
				}
			}
		}
		break;
		}
	}

	EXPORT_API void PluginMultiplyIntensityName(const char* path, int frameId, float intensity)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginMultiplyIntensityName: Animation not found! %s\r\n", path);
			return;
		}
		PluginMultiplyIntensity(animationId, frameId, intensity);
	}

	EXPORT_API double PluginMultiplyIntensityNameD(const char* path, double frameId, double intensity)
	{
		PluginMultiplyIntensityName(path, (int)frameId, (float)intensity);
		return 0;
	}


	EXPORT_API void PluginMultiplyIntensityColor(int animationId, int frameId, int color)
	{
		int red = (color & 0xFF);
		int green = (color & 0xFF00) >> 8;
		int blue = (color & 0xFF0000) >> 16;
		float redIntensity = red / 255.0f;
		float greenIntensity = green / 255.0f;
		float blueIntensity = blue / 255.0f;

		PluginStopAnimation(animationId);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		switch (animation->GetDeviceType())
		{
		case EChromaSDKDeviceTypeEnum::DE_1D:
		{
			Animation1D* animation1D = (Animation1D*)(animation);
			vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
			if (frameId >= 0 &&
				frameId < (int)frames.size())
			{
				FChromaSDKColorFrame1D& frame = frames[frameId];
				int maxLeds = ChromaSDKPlugin::GetInstance()->GetMaxLeds(animation1D->GetDevice());
				vector<COLORREF>& colors = frame.Colors;
				for (int i = 0; i < maxLeds; ++i)
				{
					int color = colors[i];
					int red = (color & 0xFF);
					int green = (color & 0xFF00) >> 8;
					int blue = (color & 0xFF0000) >> 16;
					red = max(0, min(255, (int)(red * redIntensity)));
					green = max(0, min(255, (int)(green * greenIntensity)));
					blue = max(0, min(255, (int)(blue * blueIntensity)));
					color = (red & 0xFF) | ((green & 0xFF) << 8) | ((blue & 0xFF) << 16);
					colors[i] = color;
				}
			}
		}
		break;
		case EChromaSDKDeviceTypeEnum::DE_2D:
		{
			Animation2D* animation2D = (Animation2D*)(animation);
			vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
			if (frameId >= 0 &&
				frameId < (int)frames.size())
			{
				FChromaSDKColorFrame2D& frame = frames[frameId];
				int maxRow = ChromaSDKPlugin::GetInstance()->GetMaxRow(animation2D->GetDevice());
				int maxColumn = ChromaSDKPlugin::GetInstance()->GetMaxColumn(animation2D->GetDevice());
				for (int i = 0; i < maxRow; ++i)
				{
					FChromaSDKColors& row = frame.Colors[i];
					for (int j = 0; j < maxColumn; ++j)
					{
						int color = row.Colors[j];
						int red = (color & 0xFF);
						int green = (color & 0xFF00) >> 8;
						int blue = (color & 0xFF0000) >> 16;
						red = max(0, min(255, (int)(red * redIntensity)));
						green = max(0, min(255, (int)(green * greenIntensity)));
						blue = max(0, min(255, (int)(blue * blueIntensity)));
						color = (red & 0xFF) | ((green & 0xFF) << 8) | ((blue & 0xFF) << 16);
						row.Colors[j] = color;
					}
				}
			}
		}
		break;
		}
	}

	EXPORT_API void PluginMultiplyIntensityColorName(const char* path, int frameId, int color)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginMultiplyIntensityColorName: Animation not found! %s\r\n", path);
			return;
		}
		PluginMultiplyIntensityColor(animationId, frameId, color);
	}

	EXPORT_API double PluginMultiplyIntensityColorNameD(const char* path, double frameId, double color)
	{
		PluginMultiplyIntensityColorName(path, (int)frameId, (int)color);
		return 0;
	}


	EXPORT_API void PluginMultiplyIntensityColorAllFrames(int animationId, int color)
	{
		PluginStopAnimation(animationId);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		int frameCount = PluginGetFrameCount(animationId);
		for (int frameId = 0; frameId < frameCount; ++frameId)
		{
			PluginMultiplyIntensityColor(animationId, frameId, color);
		}		
	}

	EXPORT_API void PluginMultiplyIntensityColorAllFramesName(const char* path, int color)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginMultiplyIntensityColorAllFramesName: Animation not found! %s\r\n", path);
			return;
		}
		PluginMultiplyIntensityColorAllFrames(animationId, color);
	}

	EXPORT_API double PluginMultiplyIntensityColorAllFramesNameD(const char* path, double color)
	{
		PluginMultiplyIntensityColorAllFramesName(path, (int)color);
		return 0;
	}


	EXPORT_API void PluginMultiplyIntensityRGB(int animationId, int frameId, int red, int green, int blue)
	{
		float redIntensity = red / 255.0f;
		float greenIntensity = green / 255.0f;
		float blueIntensity = blue / 255.0f;

		PluginStopAnimation(animationId);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		switch (animation->GetDeviceType())
		{
		case EChromaSDKDeviceTypeEnum::DE_1D:
		{
			Animation1D* animation1D = (Animation1D*)(animation);
			vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
			if (frameId >= 0 &&
				frameId < (int)frames.size())
			{
				FChromaSDKColorFrame1D& frame = frames[frameId];
				int maxLeds = ChromaSDKPlugin::GetInstance()->GetMaxLeds(animation1D->GetDevice());
				vector<COLORREF>& colors = frame.Colors;
				for (int i = 0; i < maxLeds; ++i)
				{
					int color = colors[i];
					int red = (color & 0xFF);
					int green = (color & 0xFF00) >> 8;
					int blue = (color & 0xFF0000) >> 16;
					red = max(0, min(255, (int)(red * redIntensity)));
					green = max(0, min(255, (int)(green * greenIntensity)));
					blue = max(0, min(255, (int)(blue * blueIntensity)));
					color = (red & 0xFF) | ((green & 0xFF) << 8) | ((blue & 0xFF) << 16);
					colors[i] = color;
				}
			}
		}
		break;
		case EChromaSDKDeviceTypeEnum::DE_2D:
		{
			Animation2D* animation2D = (Animation2D*)(animation);
			vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
			if (frameId >= 0 &&
				frameId < (int)frames.size())
			{
				FChromaSDKColorFrame2D& frame = frames[frameId];
				int maxRow = ChromaSDKPlugin::GetInstance()->GetMaxRow(animation2D->GetDevice());
				int maxColumn = ChromaSDKPlugin::GetInstance()->GetMaxColumn(animation2D->GetDevice());
				for (int i = 0; i < maxRow; ++i)
				{
					FChromaSDKColors& row = frame.Colors[i];
					for (int j = 0; j < maxColumn; ++j)
					{
						int color = row.Colors[j];
						int red = (color & 0xFF);
						int green = (color & 0xFF00) >> 8;
						int blue = (color & 0xFF0000) >> 16;
						red = max(0, min(255, (int)(red * redIntensity)));
						green = max(0, min(255, (int)(green * greenIntensity)));
						blue = max(0, min(255, (int)(blue * blueIntensity)));
						color = (red & 0xFF) | ((green & 0xFF) << 8) | ((blue & 0xFF) << 16);
						row.Colors[j] = color;
					}
				}
			}
		}
		break;
		}
	}

	EXPORT_API void PluginMultiplyIntensityRGBName(const char* path, int frameId, int red, int green, int blue)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginMultiplyIntensityRGBName: Animation not found! %s\r\n", path);
			return;
		}
		PluginMultiplyIntensityRGB(animationId, frameId, red, green, blue);
	}

	EXPORT_API double PluginMultiplyIntensityRGBNameD(const char* path, double frameId, double red, double green, double blue)
	{
		PluginMultiplyIntensityRGBName(path, (int)frameId, (int)red, (int)green, (int)blue);
		return 0;
	}


	EXPORT_API void PluginMultiplyIntensityAllFrames(int animationId, float intensity)
	{
		PluginStopAnimation(animationId);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		int frameCount = PluginGetFrameCount(animationId);
		for (int frameId = 0; frameId < frameCount; ++frameId)
		{
			PluginMultiplyIntensity(animationId, frameId, intensity);
		}
	}

	EXPORT_API void PluginMultiplyIntensityAllFramesName(const char* path, float intensity)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginMultiplyIntensityAllFramesName: Animation not found! %s\r\n", path);
			return;
		}
		PluginMultiplyIntensityAllFrames(animationId, intensity);
	}

	EXPORT_API double PluginMultiplyIntensityAllFramesNameD(const char* path, double intensity)
	{
		PluginMultiplyIntensityAllFramesName(path, (float)intensity);
		return 0;
	}


	EXPORT_API void PluginMultiplyIntensityAllFramesRGB(int animationId, int red, int green, int blue)
	{
		PluginStopAnimation(animationId);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		int frameCount = PluginGetFrameCount(animationId);
		for (int frameId = 0; frameId < frameCount; ++frameId)
		{
			PluginMultiplyIntensityRGB(animationId, frameId, red, green, blue);
		}
	}

	EXPORT_API void PluginMultiplyIntensityAllFramesRGBName(const char* path, int red, int green, int blue)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginMultiplyIntensityAllFramesRGBName: Animation not found! %s\r\n", path);
			return;
		}
		PluginMultiplyIntensityAllFramesRGB(animationId, red, green, blue);
	}

	EXPORT_API double PluginMultiplyIntensityAllFramesRGBNameD(const char* path, double red, double green, double blue)
	{
		PluginMultiplyIntensityAllFramesRGBName(path, (int)red, (int)green, (int)blue);
		return 0;
	}


	EXPORT_API float PluginLerp(float start, float end, float amt)
	{
		return (1 - amt)*start + amt * end;
	}

	EXPORT_API int PluginLerpColor(int from, int to, float t) {
		int red = (int)floor(PluginLerp((float)(from & 0xFF), (float)(to & 0xFF), t));
		int green = (int)floor(PluginLerp((float)((from & 0xFF00) >> 8), (float)((to & 0xFF00) >> 8), t));
		int blue = (int)floor(PluginLerp((float)((from & 0xFF0000) >> 16), (float)((to & 0xFF0000) >> 16), t));
		int color = red | (green << 8) | (blue << 16);
		return color;
	}


	EXPORT_API void PluginMultiplyTargetColorLerp(int animationId, int frameId, int color1, int color2)
	{
		PluginStopAnimation(animationId);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		switch (animation->GetDeviceType())
		{
		case EChromaSDKDeviceTypeEnum::DE_1D:
		{
			Animation1D* animation1D = (Animation1D*)(animation);
			vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
			if (frameId >= 0 &&
				frameId < (int)frames.size())
			{
				FChromaSDKColorFrame1D& frame = frames[frameId];
				int maxLeds = ChromaSDKPlugin::GetInstance()->GetMaxLeds(animation1D->GetDevice());
				vector<COLORREF>& colors = frame.Colors;
				for (int i = 0; i < maxLeds; ++i)
				{
					int color = colors[i];
					float red = (color & 0xFF) / 255.0f;
					float green = ((color & 0xFF00) >> 8) / 255.0f;
					float blue = ((color & 0xFF0000) >> 16) / 255.0f;
					float t = (red + green + blue) / 3.0f;
					colors[i] = PluginLerpColor(color1, color2, t);
				}
			}
		}
		break;
		case EChromaSDKDeviceTypeEnum::DE_2D:
		{
			Animation2D* animation2D = (Animation2D*)(animation);
			vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
			if (frameId >= 0 &&
				frameId < (int)frames.size())
			{
				FChromaSDKColorFrame2D& frame = frames[frameId];
				int maxRow = ChromaSDKPlugin::GetInstance()->GetMaxRow(animation2D->GetDevice());
				int maxColumn = ChromaSDKPlugin::GetInstance()->GetMaxColumn(animation2D->GetDevice());
				for (int i = 0; i < maxRow; ++i)
				{
					FChromaSDKColors& row = frame.Colors[i];
					for (int j = 0; j < maxColumn; ++j)
					{
						int color = row.Colors[j];
						float red = (color & 0xFF) / 255.0f;
						float green = ((color & 0xFF00) >> 8) / 255.0f;
						float blue = ((color & 0xFF0000) >> 16) / 255.0f;
						float t = (red + green + blue) / 3.0f;
						row.Colors[j] = PluginLerpColor(color1, color2, t);
					}
				}
			}
		}
		break;
		}
	}

	EXPORT_API void PluginMultiplyTargetColorLerpName(const char* path, int frameId, int color1, int color2)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginMultiplyTargetColorLerpName: Animation not found! %s\r\n", path);
			return;
		}
		PluginMultiplyTargetColorLerp(animationId, frameId, color1, color2);
	}

	EXPORT_API void PluginMultiplyNonZeroTargetColorLerp(int animationId, int frameId, int color1, int color2)
	{
		PluginStopAnimation(animationId);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		switch (animation->GetDeviceType())
		{
		case EChromaSDKDeviceTypeEnum::DE_1D:
		{
			Animation1D* animation1D = (Animation1D*)(animation);
			vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
			if (frameId >= 0 &&
				frameId < (int)frames.size())
			{
				FChromaSDKColorFrame1D& frame = frames[frameId];
				int maxLeds = ChromaSDKPlugin::GetInstance()->GetMaxLeds(animation1D->GetDevice());
				vector<COLORREF>& colors = frame.Colors;
				for (int i = 0; i < maxLeds; ++i)
				{
					int color = colors[i];
					if (color != 0)
					{
						float red = (color & 0xFF) / 255.0f;
						float green = ((color & 0xFF00) >> 8) / 255.0f;
						float blue = ((color & 0xFF0000) >> 16) / 255.0f;
						float t = (red + green + blue) / 3.0f;
						colors[i] = PluginLerpColor(color1, color2, t);
					}
				}
			}
		}
		break;
		case EChromaSDKDeviceTypeEnum::DE_2D:
		{
			Animation2D* animation2D = (Animation2D*)(animation);
			vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
			if (frameId >= 0 &&
				frameId < (int)frames.size())
			{
				FChromaSDKColorFrame2D& frame = frames[frameId];
				int maxRow = ChromaSDKPlugin::GetInstance()->GetMaxRow(animation2D->GetDevice());
				int maxColumn = ChromaSDKPlugin::GetInstance()->GetMaxColumn(animation2D->GetDevice());
				for (int i = 0; i < maxRow; ++i)
				{
					FChromaSDKColors& row = frame.Colors[i];
					for (int j = 0; j < maxColumn; ++j)
					{
						int color = row.Colors[j];
						if (color != 0)
						{
							float red = (color & 0xFF) / 255.0f;
							float green = ((color & 0xFF00) >> 8) / 255.0f;
							float blue = ((color & 0xFF0000) >> 16) / 255.0f;
							float t = (red + green + blue) / 3.0f;
							row.Colors[j] = PluginLerpColor(color1, color2, t);
						}
					}
				}
			}
		}
		break;
		}
	}


	EXPORT_API void PluginMultiplyTargetColorLerpAllFrames(int animationId, int color1, int color2)
	{
		PluginStopAnimation(animationId);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		int frameCount = animation->GetFrameCount();
		for (int frameId = 0; frameId < frameCount; ++frameId)
		{
			PluginMultiplyTargetColorLerp(animationId, frameId, color1, color2);
		}
	}
	EXPORT_API void PluginMultiplyTargetColorLerpAllFramesName(const char* path, int color1, int color2)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginMultiplyTargetColorLerpAllFramesName: Animation not found! %s\r\n", path);
			return;
		}
		PluginMultiplyTargetColorLerpAllFrames(animationId, color1, color2);
	}
	EXPORT_API double PluginMultiplyTargetColorLerpAllFramesNameD(const char* path, double color1, double color2)
	{
		PluginMultiplyTargetColorLerpAllFramesName(path, (int)color1, (int)color2);
		return 0;
	}


	EXPORT_API void PluginMultiplyColorLerpAllFrames(int animationId, int color1, int color2)
	{
		PluginStopAnimation(animationId);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		int frameCount = animation->GetFrameCount();
		for (int frameId = 0; frameId < frameCount; ++frameId)
		{
			float t = (frameId + 1) / (float)frameCount;
			int color = PluginLerpColor(color1, color2, t);
			PluginMultiplyIntensityColor(animationId, frameId, color);
		}
	}
	EXPORT_API void PluginMultiplyColorLerpAllFramesName(const char* path, int color1, int color2)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginMultiplyColorLerpAllFramesName: Animation not found! %s\r\n", path);
			return;
		}
		PluginMultiplyColorLerpAllFrames(animationId, color1, color2);
	}
	EXPORT_API double PluginMultiplyColorLerpAllFramesNameD(const char* path, double color1, double color2)
	{
		PluginMultiplyColorLerpAllFramesName(path, (int)color1, (int)color2);
		return 0;
	}


	EXPORT_API void PluginMultiplyTargetColorLerpAllFramesRGB(int animationId, int red1, int green1, int blue1, int red2, int green2, int blue2)
	{
		PluginStopAnimation(animationId);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		int color1 = PluginGetRGB(red1, green1, blue1);
		int color2 = PluginGetRGB(red2, green2, blue2);
		int frameCount = animation->GetFrameCount();
		for (int frameId = 0; frameId < frameCount; ++frameId)
		{
			PluginMultiplyTargetColorLerp(animationId, frameId, color1, color2);
		}
	}
	EXPORT_API void PluginMultiplyTargetColorLerpAllFramesRGBName(const char* path, int red1, int green1, int blue1, int red2, int green2, int blue2)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginMultiplyTargetColorLerpAllFramesRGBName: Animation not found! %s\r\n", path);
			return;
		}
		PluginMultiplyTargetColorLerpAllFramesRGB(animationId, red1, green1, blue1, red2, green2, blue2);
	}
	EXPORT_API double PluginMultiplyTargetColorLerpAllFramesRGBNameD(const char* path, double red1, double green1, double blue1, double red2, double green2, double blue2)
	{
		PluginMultiplyTargetColorLerpAllFramesRGBName(path, (int)red1, (int)green1, (int)blue1, (int)red2, (int)green2, (int)blue2);
		return 0;
	}


	EXPORT_API void PluginMultiplyNonZeroTargetColorLerpAllFrames(int animationId, int color1, int color2)
	{
		PluginStopAnimation(animationId);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		int frameCount = animation->GetFrameCount();
		for (int frameId = 0; frameId < frameCount; ++frameId)
		{
			PluginMultiplyNonZeroTargetColorLerp(animationId, frameId, color1, color2);
		}
	}
	EXPORT_API void PluginMultiplyNonZeroTargetColorLerpAllFramesName(const char* path, int color1, int color2)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginMultiplyNonZeroTargetColorLerpAllFramesName: Animation not found! %s\r\n", path);
			return;
		}
		PluginMultiplyNonZeroTargetColorLerpAllFrames(animationId, color1, color2);
	}
	EXPORT_API double PluginMultiplyNonZeroTargetColorLerpAllFramesNameD(const char* path, double color1, double color2)
	{
		PluginMultiplyNonZeroTargetColorLerpAllFramesName(path, (int)color1, (int)color2);
		return 0;
	}


	EXPORT_API void PluginMultiplyNonZeroTargetColorLerpAllFramesRGB(int animationId, int red1, int green1, int blue1, int red2, int green2, int blue2)
	{
		PluginStopAnimation(animationId);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		int color1 = PluginGetRGB(red1, green1, blue1);
		int color2 = PluginGetRGB(red2, green2, blue2);
		int frameCount = animation->GetFrameCount();
		for (int frameId = 0; frameId < frameCount; ++frameId)
		{
			PluginMultiplyNonZeroTargetColorLerp(animationId, frameId, color1, color2);
		}
	}
	EXPORT_API void PluginMultiplyNonZeroTargetColorLerpAllFramesRGBName(const char* path, int red1, int green1, int blue1, int red2, int green2, int blue2)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginMultiplyNonZeroTargetColorLerpAllFramesRGBName: Animation not found! %s\r\n", path);
			return;
		}
		PluginMultiplyNonZeroTargetColorLerpAllFramesRGB(animationId, red1, green1, blue1, red2, green2, blue2);
	}
	EXPORT_API double PluginMultiplyNonZeroTargetColorLerpAllFramesRGBNameD(const char* path, double red1, double green1, double blue1, double red2, double green2, double blue2)
	{
		PluginMultiplyNonZeroTargetColorLerpAllFramesRGBName(path, (int)red1, (int)green1, (int)blue1, (int)red2, (int)green2, (int)blue2);
		return 0;
	}


	EXPORT_API void PluginReverseAllFrames(int animationId)
	{
		PluginStopAnimation(animationId);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		switch (animation->GetDeviceType())
		{
		case EChromaSDKDeviceTypeEnum::DE_1D:
		{
			Animation1D* animation1D = (Animation1D*)(animation);
			vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
			reverse(frames.begin(), frames.end());
		}
		break;
		case EChromaSDKDeviceTypeEnum::DE_2D:
		{
			Animation2D* animation2D = (Animation2D*)(animation);
			vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
			reverse(frames.begin(), frames.end());
		}
		break;
		}
	}

	EXPORT_API void PluginReverseAllFramesName(const char* path)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginReverseAllFramesName: Animation not found! %s\r\n", path);
			return;
		}
		PluginReverseAllFrames(animationId);
	}

	EXPORT_API double PluginReverseAllFramesNameD(const char* path)
	{
		PluginReverseAllFramesName(path);
		return 0;
	}


	EXPORT_API void PluginSetCurrentFrame(int animationId, int frameId)
	{
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		animation->SetCurrentFrame(frameId);
	}

	EXPORT_API void PluginSetCurrentFrameName(const char* path, int frameId)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginSetCurrentFrameName: Animation not found! %s\r\n", path);
			return;
		}
		PluginSetCurrentFrame(animationId, frameId);
	}

	EXPORT_API double PluginSetCurrentFrameNameD(const char* path, double frameId)
	{
		PluginSetCurrentFrameName(path, (int)frameId);
		return 0;
	}

	EXPORT_API void PluginPauseAnimation(int animationId)
	{
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		animation->Pause();
	}

	EXPORT_API void PluginPauseAnimationName(const char* path)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginPauseAnimationName: Animation not found! %s\r\n", path);
			return;
		}
		PluginPauseAnimation(animationId);
	}

	EXPORT_API double PluginPauseAnimationNameD(const char* path)
	{
		PluginPauseAnimationName(path);
		return 0;
	}

	EXPORT_API bool PluginIsAnimationPaused(int animationId)
	{
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return false;
		}
		return animation->IsPaused();
	}

	EXPORT_API bool PluginIsAnimationPausedName(const char* path)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginIsAnimationPausedName: Animation not found! %s\r\n", path);
			return false;
		}
		return PluginIsAnimationPaused(animationId);
	}

	EXPORT_API double PluginIsAnimationPausedNameD(const char* path)
	{
		if (PluginIsAnimationPausedName(path))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}

	EXPORT_API bool PluginHasAnimationLoop(int animationId)
	{
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return false;
		}
		return animation->HasLoop();
	}

	EXPORT_API bool PluginHasAnimationLoopName(const char* path)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginHasAnimationLoopName: Animation not found! %s\r\n", path);
			return false;
		}
		return PluginHasAnimationLoop(animationId);
	}

	EXPORT_API double PluginHasAnimationLoopNameD(const char* path)
	{
		if (PluginHasAnimationLoopName(path))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}

	EXPORT_API void PluginResumeAnimation(int animationId, bool loop)
	{
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		animation->Resume(loop);
	}

	EXPORT_API void PluginResumeAnimationName(const char* path, bool loop)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginResumeAnimationName: Animation not found! %s\r\n", path);
			return;
		}
		PluginResumeAnimation(animationId, loop);
	}

	EXPORT_API double PluginResumeAnimationNameD(const char* path, double loop)
	{
		if (loop == 0)
		{
			PluginResumeAnimationName(path, false);
		}
		else
		{
			PluginResumeAnimationName(path, true);
		}
		return 0;
	}


	EXPORT_API void PluginSetChromaCustomFlag(int animationId, bool flag)
	{
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		if (animation->GetDeviceType() != (int)EChromaSDKDeviceTypeEnum::DE_2D)
		{
			return;
		}
		switch (animation->GetDeviceId())
		{
		case (int)EChromaSDKDevice2DEnum::DE_Keyboard:
		case (int)EChromaSDKDevice2DEnum::DE_KeyboardExtended:
			break;
		default:
			return;
		}
		Animation2D* animation2D = dynamic_cast<Animation2D*>(animation);
		animation2D->SetChromaCustom(flag);
	}

	EXPORT_API void PluginSetChromaCustomFlagName(const char* path, bool flag)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginKeyboardUseChromaCustomName: Animation not found! %s\r\n", path);
			return;
		}
		PluginSetChromaCustomFlag(animationId, flag);
	}

	EXPORT_API double PluginSetChromaCustomFlagNameD(const char* path, double flag)
	{
		if (flag == 0)
		{
			PluginSetChromaCustomFlagName(path, false);
		}
		else
		{
			PluginSetChromaCustomFlagName(path, true);
		}
		return 0;
	}


	EXPORT_API void PluginSetChromaCustomColorAllFrames(int animationId)
	{
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		if (animation->GetDeviceType() != (int)EChromaSDKDeviceTypeEnum::DE_2D)
		{
			return;
		}
		if (animation->GetDeviceId() != (int)EChromaSDKDevice2DEnum::DE_Keyboard)
		{
			return;
		}
		Animation2D* animation2D = dynamic_cast<Animation2D*>(animation);
		vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
		for (int frameId = 0; frameId < int(frames.size()); ++frameId)
		{
			FChromaSDKColorFrame2D& frame = frames[frameId];
			int maxRow = ChromaSDKPlugin::GetInstance()->GetMaxRow(animation2D->GetDevice());
			int maxColumn = ChromaSDKPlugin::GetInstance()->GetMaxColumn(animation2D->GetDevice());
			for (int i = 0; i < maxRow; ++i)
			{
				FChromaSDKColors& row = frame.Colors[i];
				for (int j = 0; j < maxColumn; ++j)
				{
					int color = row.Colors[j];
					int customFlag = 0x1;
					int red = (color & 0xFF);
					int green = (color & 0xFF00) >> 8;
					int blue = (color & 0xFF0000) >> 16;
					color = (red & 0xFF) | ((green & 0xFF) << 8) | ((blue & 0xFF) << 16) | (customFlag << 24);
					row.Colors[j] = color;
				}
			}
		}
	}

	EXPORT_API void PluginSetChromaCustomColorAllFramesName(const char* path)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginSetChromaCustomColorAllFramesName: Animation not found! %s\r\n", path);
			return;
		}
		PluginSetChromaCustomColorAllFrames(animationId);
	}

	EXPORT_API double PluginSetChromaCustomColorAllFramesNameD(const char* path)
	{
		PluginSetChromaCustomColorAllFramesName(path);
		return 0;
	}


	EXPORT_API void PluginMakeBlankFrames(int animationId, int frameCount, float duration, int color)
	{
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		PluginStopAnimation(animationId);
		if (animation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_1D)
		{
			Animation1D* animation1D = dynamic_cast<Animation1D*>(animation);
			vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
			frames.clear();
			int maxLeds = ChromaSDKPlugin::GetInstance()->GetMaxLeds(animation1D->GetDevice());
			for (int frameId = 0; frameId < frameCount; ++frameId)
			{
				FChromaSDKColorFrame1D frame = FChromaSDKColorFrame1D();
				frame.Duration = duration;
				frame.Colors = ChromaSDKPlugin::GetInstance()->CreateColors1D(animation1D->GetDevice());
				for (int i = 0; i < maxLeds; ++i)
				{
					frame.Colors[i] = color;
				}
				frames.push_back(frame);
			}
		}
		else if (animation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_2D)
		{
			Animation2D* animation2D = dynamic_cast<Animation2D*>(animation);
			vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
			frames.clear();
			int maxRow = ChromaSDKPlugin::GetInstance()->GetMaxRow(animation2D->GetDevice());
			int maxColumn = ChromaSDKPlugin::GetInstance()->GetMaxColumn(animation2D->GetDevice());
			for (int frameId = 0; frameId < frameCount; ++frameId)
			{
				FChromaSDKColorFrame2D frame = FChromaSDKColorFrame2D(animation2D->GetDevice());
				frame.Duration = duration;
				frame.Colors = ChromaSDKPlugin::GetInstance()->CreateColors2D(animation2D->GetDevice());
				for (int i = 0; i < maxRow; ++i)
				{
					FChromaSDKColors& row = frame.Colors[i];
					for (int j = 0; j < maxColumn; ++j)
					{
						row.Colors[j] = color;
					}
				}
				frames.push_back(frame);
			}
		}
	}

	EXPORT_API void PluginMakeBlankFramesName(const char* path, int frameCount, float duration, int color)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginMakeBlankFramesName: Animation not found! %s\r\n", path);
			return;
		}
		PluginMakeBlankFrames(animationId, frameCount, duration, color);
	}

	EXPORT_API double PluginMakeBlankFramesNameD(const char* path, double frameCount, double duration, double color)
	{
		PluginMakeBlankFramesName(path, (int)frameCount, (float)duration, (int)color);
		return 0;
	}


	EXPORT_API void PluginMakeBlankFramesRGB(int animationId, int frameCount, float duration, int red, int green, int blue)
	{
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		PluginStopAnimation(animationId);
		int color = (red & 0xFF) | ((green & 0xFF) << 8) | ((blue & 0xFF) << 16);
		if (animation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_1D)
		{
			Animation1D* animation1D = dynamic_cast<Animation1D*>(animation);
			vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
			frames.clear();
			int maxLeds = ChromaSDKPlugin::GetInstance()->GetMaxLeds(animation1D->GetDevice());
			for (int frameId = 0; frameId < frameCount; ++frameId)
			{
				FChromaSDKColorFrame1D frame = FChromaSDKColorFrame1D();
				frame.Duration = duration;
				frame.Colors = ChromaSDKPlugin::GetInstance()->CreateColors1D(animation1D->GetDevice());
				for (int i = 0; i < maxLeds; ++i)
				{
					frame.Colors[i] = color;
				}
				frames.push_back(frame);
			}
		}
		else if (animation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_2D)
		{
			Animation2D* animation2D = dynamic_cast<Animation2D*>(animation);
			vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
			frames.clear();
			int maxRow = ChromaSDKPlugin::GetInstance()->GetMaxRow(animation2D->GetDevice());
			int maxColumn = ChromaSDKPlugin::GetInstance()->GetMaxColumn(animation2D->GetDevice());
			for (int frameId = 0; frameId < frameCount; ++frameId)
			{
				FChromaSDKColorFrame2D frame = FChromaSDKColorFrame2D(animation2D->GetDevice());
				frame.Duration = duration;
				frame.Colors = ChromaSDKPlugin::GetInstance()->CreateColors2D(animation2D->GetDevice());
				for (int i = 0; i < maxRow; ++i)
				{
					FChromaSDKColors& row = frame.Colors[i];
					for (int j = 0; j < maxColumn; ++j)
					{
						row.Colors[j] = color;
					}
				}
				frames.push_back(frame);
			}
		}
	}

	EXPORT_API void PluginMakeBlankFramesRGBName(const char* path, int frameCount, float duration, int red, int green, int blue)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginMakeBlankFramesRGBName: Animation not found! %s\r\n", path);
			return;
		}
		PluginMakeBlankFramesRGB(animationId, frameCount, duration, red, green, blue);
	}

	EXPORT_API double PluginMakeBlankFramesRGBNameD(const char* path, double frameCount, double duration, double red, double green, double blue)
	{
		PluginMakeBlankFramesRGBName(path, (int)frameCount, (float)duration, (int)red, (int)green, (int)blue);
		return 0;
	}


	EXPORT_API void PluginMakeBlankFramesRandom(int animationId, int frameCount, float duration)
	{
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		PluginStopAnimation(animationId);
		if (animation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_1D)
		{
			Animation1D* animation1D = dynamic_cast<Animation1D*>(animation);
			vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
			frames.clear();
			for (int frameId = 0; frameId < frameCount; ++frameId)
			{
				FChromaSDKColorFrame1D frame = FChromaSDKColorFrame1D();
				frame.Duration = duration;
				frame.Colors = ChromaSDKPlugin::GetInstance()->CreateColors1D(animation1D->GetDevice());
				int maxLeds = ChromaSDKPlugin::GetInstance()->GetMaxLeds(animation1D->GetDevice());
				vector<COLORREF>& colors = frame.Colors;
				for (int i = 0; i < maxLeds; ++i)
				{
					int red = fastrand() % 256;
					int green = fastrand() % 256;
					int blue = fastrand() % 256;
					COLORREF color = PluginGetRGB(red, green, blue);
					colors[i] = color;
				}
				frames.push_back(frame);
			}
		}
		else if (animation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_2D)
		{
			Animation2D* animation2D = dynamic_cast<Animation2D*>(animation);
			vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
			frames.clear();
			for (int frameId = 0; frameId < frameCount; ++frameId)
			{
				FChromaSDKColorFrame2D frame = FChromaSDKColorFrame2D(animation2D->GetDevice());
				frame.Duration = duration;
				frame.Colors = ChromaSDKPlugin::GetInstance()->CreateColors2D(animation2D->GetDevice());
				int maxRow = ChromaSDKPlugin::GetInstance()->GetMaxRow(animation2D->GetDevice());
				int maxColumn = ChromaSDKPlugin::GetInstance()->GetMaxColumn(animation2D->GetDevice());
				for (int i = 0; i < maxRow; ++i)
				{
					FChromaSDKColors& row = frame.Colors[i];
					for (int j = 0; j < maxColumn; ++j)
					{
						int red = fastrand() % 256;
						int green = fastrand() % 256;
						int blue = fastrand() % 256;
						COLORREF color = PluginGetRGB(red, green, blue);
						row.Colors[j] = color;
					}
				}
				frames.push_back(frame);
			}
		}
	}

	EXPORT_API void PluginMakeBlankFramesRandomName(const char* path, int frameCount, float duration)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginMakeBlankFramesRandomName: Animation not found! %s\r\n", path);
			return;
		}
		PluginMakeBlankFramesRandom(animationId, frameCount, duration);
	}

	EXPORT_API double PluginMakeBlankFramesRandomNameD(const char* path, double frameCount, double duration)
	{
		PluginMakeBlankFramesRandomName(path, (int)frameCount, (float)duration);
		return 0;
	}


	EXPORT_API void PluginMakeBlankFramesRandomBlackAndWhite(int animationId, int frameCount, float duration)
	{
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		PluginStopAnimation(animationId);
		if (animation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_1D)
		{
			Animation1D* animation1D = dynamic_cast<Animation1D*>(animation);
			vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
			frames.clear();
			for (int frameId = 0; frameId < frameCount; ++frameId)
			{
				FChromaSDKColorFrame1D frame = FChromaSDKColorFrame1D();
				frame.Duration = duration;
				frame.Colors = ChromaSDKPlugin::GetInstance()->CreateColors1D(animation1D->GetDevice());
				int maxLeds = ChromaSDKPlugin::GetInstance()->GetMaxLeds(animation1D->GetDevice());
				vector<COLORREF>& colors = frame.Colors;
				for (int i = 0; i < maxLeds; ++i)
				{
					int gray = fastrand() % 256;
					COLORREF color = RGB(gray, gray, gray);
					colors[i] = color;
				}
				frames.push_back(frame);
			}
		}
		else if (animation->GetDeviceType() == EChromaSDKDeviceTypeEnum::DE_2D)
		{
			Animation2D* animation2D = dynamic_cast<Animation2D*>(animation);
			vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
			frames.clear();
			for (int frameId = 0; frameId < frameCount; ++frameId)
			{
				FChromaSDKColorFrame2D frame = FChromaSDKColorFrame2D(animation2D->GetDevice());
				frame.Duration = duration;
				frame.Colors = ChromaSDKPlugin::GetInstance()->CreateColors2D(animation2D->GetDevice());
				int maxRow = ChromaSDKPlugin::GetInstance()->GetMaxRow(animation2D->GetDevice());
				int maxColumn = ChromaSDKPlugin::GetInstance()->GetMaxColumn(animation2D->GetDevice());
				for (int i = 0; i < maxRow; ++i)
				{
					FChromaSDKColors& row = frame.Colors[i];
					for (int j = 0; j < maxColumn; ++j)
					{
						int gray = fastrand() % 256;
						COLORREF color = RGB(gray, gray, gray);
						row.Colors[j] = color;
					}
				}
				frames.push_back(frame);
			}
		}
	}

	EXPORT_API void PluginMakeBlankFramesRandomBlackAndWhiteName(const char* path, int frameCount, float duration)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginMakeBlankFramesRandomBlackAndWhiteName: Animation not found! %s\r\n", path);
			return;
		}
		PluginMakeBlankFramesRandomBlackAndWhite(animationId, frameCount, duration);
	}

	EXPORT_API double PluginMakeBlankFramesRandomBlackAndWhiteNameD(const char* path, double frameCount, double duration)
	{
		PluginMakeBlankFramesRandomBlackAndWhiteName(path, (int)frameCount, (float)duration);
		return 0;
	}


	EXPORT_API void PluginDuplicateFrames(int animationId)
	{
		PluginStopAnimation(animationId);

		if (_gAnimations.find(animationId) != _gAnimations.end())
		{
			AnimationBase* animation = _gAnimations[animationId];
			if (animation == nullptr)
			{
				LogError("PluginDuplicateFrames: Animation is null! id=%d\r\n", animationId);
				return;
			}
			int frameCount = PluginGetFrameCount(animationId);
			switch (animation->GetDeviceType())
			{
				case EChromaSDKDeviceTypeEnum::DE_1D:
				{
					Animation1D* animation1D = (Animation1D*)(animation);
					vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
					vector<FChromaSDKColorFrame1D> newFrames = vector<FChromaSDKColorFrame1D>();
					for (int frameId = 0; frameId < frameCount; ++frameId)
					{
						FChromaSDKColorFrame1D frame = frames[frameId];
						newFrames.push_back(frame);
						FChromaSDKColorFrame1D frame2 = frames[frameId];
						newFrames.push_back(frame2);
					}
					frames.clear();
					for (int frameId = 0; frameId < (int)newFrames.size(); ++frameId)
					{
						FChromaSDKColorFrame1D frame = newFrames[frameId];
						frames.push_back(frame);
					}
				}
				break;
				case EChromaSDKDeviceTypeEnum::DE_2D:
				{
					Animation2D* animation2D = (Animation2D*)(animation);
					vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
					vector<FChromaSDKColorFrame2D> newFrames = vector<FChromaSDKColorFrame2D>();
					for (int frameId = 0; frameId < frameCount; ++frameId)
					{
						FChromaSDKColorFrame2D frame = frames[frameId];
						newFrames.push_back(frame);
						FChromaSDKColorFrame2D frame2 = frames[frameId];
						newFrames.push_back(frame2);
					}
					frames.clear();
					for (int frameId = 0; frameId < (int)newFrames.size(); ++frameId)
					{
						FChromaSDKColorFrame2D frame = newFrames[frameId];
						frames.push_back(frame);
					}
				}
				break;
			}
		}
	}
	EXPORT_API void PluginDuplicateFramesName(const char* path)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginDuplicateFramesName: Animation not found! %s\r\n", path);
			return;
		}
		PluginDuplicateFrames(animationId);
	}
	EXPORT_API double PluginDuplicateFramesNameD(const char* path)
	{
		PluginDuplicateFramesName(path);
		return 0;
	}


	EXPORT_API void PluginDuplicateFirstFrame(int animationId, int frameCount)
	{
		PluginStopAnimation(animationId);

		if (_gAnimations.find(animationId) != _gAnimations.end())
		{
			AnimationBase* animation = _gAnimations[animationId];
			if (animation == nullptr)
			{
				LogError("PluginDuplicateFirstFrame: Animation is null! id=%d\r\n", animationId);
				return;
			}
			if (PluginGetFrameCount(animationId) == 0)
			{
				LogError("PluginDuplicateFirstFrame: Animation has no frames! id=%d\r\n", animationId);
				return;
			}
			switch (animation->GetDeviceType())
			{
			case EChromaSDKDeviceTypeEnum::DE_1D:
			{
				Animation1D* animation1D = (Animation1D*)(animation);
				vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
				FChromaSDKColorFrame1D firstFrame = frames[0]; //copy
				frames.clear();
				for (int frameId = 0; frameId < frameCount; ++frameId)
				{
					frames.push_back(firstFrame);
				}
			}
			break;
			case EChromaSDKDeviceTypeEnum::DE_2D:
			{
				Animation2D* animation2D = (Animation2D*)(animation);
				vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
				FChromaSDKColorFrame2D firstFrame = frames[0]; //copy
				frames.clear();
				for (int frameId = 0; frameId < frameCount; ++frameId)
				{
					frames.push_back(firstFrame);
				}
			}
			break;
			}
		}
	}
	EXPORT_API void PluginDuplicateFirstFrameName(const char* path, int frameCount)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginDuplicateFirstFrameName: Animation not found! %s\r\n", path);
			return;
		}
		PluginDuplicateFirstFrame(animationId, frameCount);
	}
	EXPORT_API double PluginDuplicateFirstFrameNameD(const char* path, double frameCount)
	{
		PluginDuplicateFirstFrameName(path, (int)frameCount);
		return 0;
	}


	EXPORT_API void PluginDuplicateMirrorFrames(int animationId)
	{
		PluginStopAnimation(animationId);

		if (_gAnimations.find(animationId) != _gAnimations.end())
		{
			AnimationBase* animation = _gAnimations[animationId];
			if (animation == nullptr)
			{
				LogError("PluginDuplicateMirrorFrames: Animation is null! id=%d\r\n", animationId);
				return;
			}
			int frameCount = PluginGetFrameCount(animationId);
			if (frameCount == 0)
			{
				LogError("PluginDuplicateMirrorFrames: Animation has no frames! id=%d\r\n", animationId);
				return;
			}
			switch (animation->GetDeviceType())
			{
			case EChromaSDKDeviceTypeEnum::DE_1D:
			{
				Animation1D* animation1D = (Animation1D*)(animation);
				vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
				for (int frameId = frameCount - 1; frameId >= 0; --frameId)
				{
					FChromaSDKColorFrame1D frame = frames[frameId]; //copy
					frames.push_back(frame);
				}
			}
			break;
			case EChromaSDKDeviceTypeEnum::DE_2D:
			{
				Animation2D* animation2D = (Animation2D*)(animation);
				vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
				for (int frameId = frameCount - 1; frameId >= 0; --frameId)
				{
					FChromaSDKColorFrame2D frame = frames[frameId]; //copy
					frames.push_back(frame);
				}
			}
			break;
			}
		}
	}
	EXPORT_API void PluginDuplicateMirrorFramesName(const char* path)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginDuplicateMirrorFramesName: Animation not found! %s\r\n", path);
			return;
		}
		PluginDuplicateMirrorFrames(animationId);
	}
	EXPORT_API double PluginDuplicateMirrorFramesNameD(const char* path)
	{
		PluginDuplicateMirrorFramesName(path);
		return 0;
	}


	EXPORT_API void PluginInsertFrame(int animationId, int sourceFrame, int targetFrame)
	{
		PluginStopAnimation(animationId);

		if (_gAnimations.find(animationId) != _gAnimations.end())
		{
			AnimationBase* animation = _gAnimations[animationId];
			if (animation == nullptr)
			{
				LogError("PluginInsertFrame: Animation is null! id=%d\r\n", animationId);
				return;
			}
			int frameCount = PluginGetFrameCount(animationId);
			if (sourceFrame < 0 ||
				sourceFrame >= frameCount)
			{
				return;
			}
			if (targetFrame < 0 ||
				targetFrame >= frameCount)
			{
				return;
			}
			switch (animation->GetDeviceType())
			{
			case EChromaSDKDeviceTypeEnum::DE_1D:
			{
				Animation1D* animation1D = (Animation1D*)(animation);
				vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
				vector<FChromaSDKColorFrame1D> newFrames = vector<FChromaSDKColorFrame1D>();
				for (int frameId = 0; frameId < frameCount; ++frameId)
				{
					if (targetFrame == frameId)
					{
						FChromaSDKColorFrame1D frame = frames[sourceFrame];
						newFrames.push_back(frame);
					}

					FChromaSDKColorFrame1D frame = frames[frameId];
					newFrames.push_back(frame);
				}
				frames.clear();
				for (int frameId = 0; frameId < (int)newFrames.size(); ++frameId)
				{
					FChromaSDKColorFrame1D frame = newFrames[frameId];
					frames.push_back(frame);
				}
			}
			break;
			case EChromaSDKDeviceTypeEnum::DE_2D:
			{
				Animation2D* animation2D = (Animation2D*)(animation);
				vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
				vector<FChromaSDKColorFrame2D> newFrames = vector<FChromaSDKColorFrame2D>();
				for (int frameId = 0; frameId < frameCount; ++frameId)
				{
					if (targetFrame == frameId)
					{
						FChromaSDKColorFrame2D frame = frames[sourceFrame];
						newFrames.push_back(frame);
					}

					FChromaSDKColorFrame2D frame = frames[frameId];
					newFrames.push_back(frame);
				}
				frames.clear();
				for (int frameId = 0; frameId < (int)newFrames.size(); ++frameId)
				{
					FChromaSDKColorFrame2D frame = newFrames[frameId];
					frames.push_back(frame);
				}
			}
			break;
			}
		}
	}
	EXPORT_API void PluginInsertFrameName(const char* path, int sourceFrame, int targetFrame)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginInsertFrameName: Animation not found! %s\r\n", path);
			return;
		}
		PluginInsertFrame(animationId, sourceFrame, targetFrame);
	}
	EXPORT_API double PluginInsertFrameNameD(const char* path, double sourceFrame, double targetFrame)
	{
		PluginInsertFrameName(path, (int)sourceFrame, (int)targetFrame);
		return 0;
	}


	EXPORT_API void PluginInsertDelay(int animationId, int frameId, int delay)
	{
		PluginStopAnimation(animationId);

		if (_gAnimations.find(animationId) != _gAnimations.end())
		{
			AnimationBase* animation = _gAnimations[animationId];
			if (animation == nullptr)
			{
				LogError("PluginInsertFrame: Animation is null! id=%d\r\n", animationId);
				return;
			}
			int frameCount = PluginGetFrameCount(animationId);
			if (frameId < 0 ||
				frameId >= frameCount)
			{
				return;
			}
			switch (animation->GetDeviceType())
			{
			case EChromaSDKDeviceTypeEnum::DE_1D:
			{
				Animation1D* animation1D = (Animation1D*)(animation);
				vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
				vector<FChromaSDKColorFrame1D> newFrames = vector<FChromaSDKColorFrame1D>();
				for (int index = 0; index < frameCount; ++index)
				{
					FChromaSDKColorFrame1D frame = frames[index];
					if (index == frameId)
					{
						for (int d = 0; d < delay; ++d)
						{
							newFrames.push_back(frame);
						}
					}
					newFrames.push_back(frame);
				}
				frames.clear();
				for (int frameId = 0; frameId < (int)newFrames.size(); ++frameId)
				{
					FChromaSDKColorFrame1D frame = newFrames[frameId];
					frames.push_back(frame);
				}
			}
			break;
			case EChromaSDKDeviceTypeEnum::DE_2D:
			{
				Animation2D* animation2D = (Animation2D*)(animation);
				vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
				vector<FChromaSDKColorFrame2D> newFrames = vector<FChromaSDKColorFrame2D>();
				for (int index = 0; index < frameCount; ++index)
				{
					FChromaSDKColorFrame2D frame = frames[index];
					if (index == frameId)
					{
						for (int d = 0; d < delay; ++d)
						{
							newFrames.push_back(frame);
						}
					}
					newFrames.push_back(frame);
				}
				frames.clear();
				for (int frameId = 0; frameId < (int)newFrames.size(); ++frameId)
				{
					FChromaSDKColorFrame2D frame = newFrames[frameId];
					frames.push_back(frame);
				}
			}
			break;
			}
		}
	}
	EXPORT_API void PluginInsertDelayName(const char* path, int frameId, int delay)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginInsertDelayName: Animation not found! %s\r\n", path);
			return;
		}
		PluginInsertDelay(animationId, frameId, delay);
	}
	EXPORT_API double PluginInsertDelayNameD(const char* path, double frameId, double delay)
	{
		PluginInsertDelayName(path, (int)frameId, (int)delay);
		return 0;
	}


	EXPORT_API void PluginReduceFrames(int animationId, int n)
	{
		PluginStopAnimation(animationId);

		if (_gAnimations.find(animationId) != _gAnimations.end())
		{
			AnimationBase* animation = _gAnimations[animationId];
			if (animation == nullptr)
			{
				LogError("PluginReduceFrames: Animation is null! id=%d\r\n", animationId);
				return;
			}
			if (n <= 0)
			{
				return;
			}
			int frameCount = PluginGetFrameCount(animationId);
			switch (animation->GetDeviceType())
			{
			case EChromaSDKDeviceTypeEnum::DE_1D:
			{
				Animation1D* animation1D = (Animation1D*)(animation);
				vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
				vector<FChromaSDKColorFrame1D> newFrames = vector<FChromaSDKColorFrame1D>();
				for (int frameId = 0; frameId < frameCount; ++frameId)
				{
					if (frameId % n == 0)
					{
						continue;
					}
					FChromaSDKColorFrame1D& frame = frames[frameId];
					newFrames.push_back(frame);
				}
				frames.clear();
				for (int frameId = 0; frameId < (int)newFrames.size(); ++frameId)
				{
					FChromaSDKColorFrame1D& frame = newFrames[frameId];
					frames.push_back(frame);
				}
				if (frames.size() == 0) //always keep one frame
				{
					FChromaSDKColorFrame1D frame = FChromaSDKColorFrame1D();
					frame.Colors = ChromaSDKPlugin::GetInstance()->CreateColors1D(animation1D->GetDevice());
					frames.push_back(frame);
				}
			}
			break;
			case EChromaSDKDeviceTypeEnum::DE_2D:
			{
				Animation2D* animation2D = (Animation2D*)(animation);
				vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
				vector<FChromaSDKColorFrame2D> newFrames = vector<FChromaSDKColorFrame2D>();
				for (int frameId = 0; frameId < frameCount; ++frameId)
				{
					if (frameId % n == 0)
					{
						continue;
					}
					FChromaSDKColorFrame2D& frame = frames[frameId];
					newFrames.push_back(frame);
				}
				frames.clear();
				for (int frameId = 0; frameId < (int)newFrames.size(); ++frameId)
				{
					FChromaSDKColorFrame2D& frame = newFrames[frameId];
					frames.push_back(frame);
				}
				if (frames.size() == 0) //always keep one frame
				{
					FChromaSDKColorFrame2D frame = FChromaSDKColorFrame2D(animation2D->GetDevice());
					frame.Colors = ChromaSDKPlugin::GetInstance()->CreateColors2D(animation2D->GetDevice());
					frames.push_back(frame);
				}
			}
			break;
			}
		}
	}
	EXPORT_API void PluginReduceFramesName(const char* path, int n)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginReduceFramesName: Animation not found! %s\r\n", path);
			return;
		}
		PluginReduceFrames(animationId, n);
	}
	EXPORT_API double PluginReduceFramesNameD(const char* path, double n)
	{
		PluginReduceFramesName(path, (int)n);
		return 0;
	}


	EXPORT_API void PluginTrimFrame(int animationId, int frameId)
	{
		PluginStopAnimation(animationId);

		if (_gAnimations.find(animationId) != _gAnimations.end())
		{
			AnimationBase* animation = _gAnimations[animationId];
			if (animation == nullptr)
			{
				LogError("PluginTrimFrame: Animation is null! id=%d\r\n", animationId);
				return;
			}
			int frameCount = PluginGetFrameCount(animationId);
			switch (animation->GetDeviceType())
			{
			case EChromaSDKDeviceTypeEnum::DE_1D:
			{
				Animation1D* animation1D = (Animation1D*)(animation);
				vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
				vector<FChromaSDKColorFrame1D> newFrames = vector<FChromaSDKColorFrame1D>();
				for (int index = 0; index < frameCount; ++index)
				{
					if (index != frameId)
					{
						FChromaSDKColorFrame1D& frame = frames[frameId];
						newFrames.push_back(frame);
					}
				}
				frames.clear();
				for (int frameId = 0; frameId < (int)newFrames.size(); ++frameId)
				{
					FChromaSDKColorFrame1D& frame = newFrames[frameId];
					frames.push_back(frame);
				}
			}
			break;
			case EChromaSDKDeviceTypeEnum::DE_2D:
			{
				Animation2D* animation2D = (Animation2D*)(animation);
				vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
				vector<FChromaSDKColorFrame2D> newFrames = vector<FChromaSDKColorFrame2D>();
				for (int index = 0; index < frameCount; ++index)
				{
					if (index != frameId)
					{
						FChromaSDKColorFrame2D& frame = frames[frameId];
						newFrames.push_back(frame);
					}
				}
				frames.clear();
				for (int frameId = 0; frameId < (int)newFrames.size(); ++frameId)
				{
					FChromaSDKColorFrame2D& frame = newFrames[frameId];
					frames.push_back(frame);
				}
			}
			break;
			}
		}
	}
	EXPORT_API void PluginTrimFrameName(const char* path, int frameId)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginTrimFrameName: Animation not found! %s\r\n", path);
			return;
		}
		PluginTrimFrame(animationId, frameId);
	}
	EXPORT_API double PluginTrimFrameNameD(const char* path, double frameId)
	{
		PluginTrimFrameName(path, (int)frameId);
		return 0;
	}


	EXPORT_API void PluginTrimStartFrames(int animationId, int numberOfFrames)
	{
		PluginStopAnimation(animationId);

		if (_gAnimations.find(animationId) != _gAnimations.end())
		{
			AnimationBase* animation = _gAnimations[animationId];
			if (animation == nullptr)
			{
				LogError("PluginTrimStartFrames: Animation is null! id=%d\r\n", animationId);
				return;
			}
			if (numberOfFrames < 0)
			{
				return;
			}
			int frameCount = PluginGetFrameCount(animationId);
			switch (animation->GetDeviceType())
			{
			case EChromaSDKDeviceTypeEnum::DE_1D:
			{
				Animation1D* animation1D = (Animation1D*)(animation);
				vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
				vector<FChromaSDKColorFrame1D> newFrames = vector<FChromaSDKColorFrame1D>();
				for (int frameId = numberOfFrames; frameId < frameCount; ++frameId)
				{
					FChromaSDKColorFrame1D& frame = frames[frameId];
					newFrames.push_back(frame);
				}
				frames.clear();
				for (int frameId = 0; frameId < (int)newFrames.size(); ++frameId)
				{
					FChromaSDKColorFrame1D& frame = newFrames[frameId];
					frames.push_back(frame);
				}
			}
			break;
			case EChromaSDKDeviceTypeEnum::DE_2D:
			{
				Animation2D* animation2D = (Animation2D*)(animation);
				vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
				vector<FChromaSDKColorFrame2D> newFrames = vector<FChromaSDKColorFrame2D>();
				for (int frameId = numberOfFrames; frameId < frameCount; ++frameId)
				{
					FChromaSDKColorFrame2D& frame = frames[frameId];
					newFrames.push_back(frame);
				}
				frames.clear();
				for (int frameId = 0; frameId < (int)newFrames.size(); ++frameId)
				{
					FChromaSDKColorFrame2D& frame = newFrames[frameId];
					frames.push_back(frame);
				}
			}
			break;
			}
		}
	}
	EXPORT_API void PluginTrimStartFramesName(const char* path, int numberOfFrames)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginTrimStartFramesName: Animation not found! %s\r\n", path);
			return;
		}
		PluginTrimStartFrames(animationId, numberOfFrames);
	}
	EXPORT_API double PluginTrimStartFramesNameD(const char* path, double numberOfFrames)
	{
		PluginTrimStartFramesName(path, (int)numberOfFrames);
		return 0;
	}


	EXPORT_API void PluginTrimEndFrames(int animationId, int lastFrameId)
	{
		PluginStopAnimation(animationId);

		if (_gAnimations.find(animationId) != _gAnimations.end())
		{
			AnimationBase* animation = _gAnimations[animationId];
			if (animation == nullptr)
			{
				LogError("PluginTrimEndFrames: Animation is null! id=%d\r\n", animationId);
				return;
			}
			if (lastFrameId <= 0)
			{
				return;
			}
			int frameCount = PluginGetFrameCount(animationId);
			switch (animation->GetDeviceType())
			{
			case EChromaSDKDeviceTypeEnum::DE_1D:
			{
				Animation1D* animation1D = (Animation1D*)(animation);
				vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
				while (lastFrameId < (int)frames.size())
				{
					frames.pop_back();
				}				
			}
			break;
			case EChromaSDKDeviceTypeEnum::DE_2D:
			{
				Animation2D* animation2D = (Animation2D*)(animation);
				vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
				while (lastFrameId < (int)frames.size())
				{
					frames.pop_back();
				}
			}
			break;
			}
		}
	}
	EXPORT_API void PluginTrimEndFramesName(const char* path, int lastFrameId)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginTrimEndFramesName: Animation not found! %s\r\n", path);
			return;
		}
		PluginTrimEndFrames(animationId, lastFrameId);
	}
	EXPORT_API double PluginTrimEndFramesNameD(const char* path, double lastFrameId)
	{
		PluginTrimEndFramesName(path, (int)lastFrameId);
		return 0;
	}


	EXPORT_API void PluginFadeStartFrames(int animationId, int fade)
	{
		PluginStopAnimation(animationId);

		if (_gAnimations.find(animationId) != _gAnimations.end())
		{
			AnimationBase* animation = _gAnimations[animationId];
			if (animation == nullptr)
			{
				LogError("PluginTrimStartFrames: Animation is null! id=%d\r\n", animationId);
				return;
			}
			if (fade <= 0)
			{
				return;
			}
			int frameCount = PluginGetFrameCount(animationId);
			for (int frameId = 0; frameId < fade && frameId < frameCount; ++frameId)
			{
				float t = (frameId + 1) / (float)fade;
				PluginMultiplyIntensity(animationId, frameId, t);
			}
		}
	}
	EXPORT_API void PluginFadeStartFramesName(const char* path, int fade)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginFadeStartFramesName: Animation not found! %s\r\n", path);
			return;
		}
		PluginFadeStartFrames(animationId, fade);
	}
	EXPORT_API double PluginFadeStartFramesNameD(const char* path, double fade)
	{
		PluginFadeStartFramesName(path, (int)fade);
		return 0;
	}


	EXPORT_API void PluginFadeEndFrames(int animationId, int fade)
	{
		PluginStopAnimation(animationId);

		if (_gAnimations.find(animationId) != _gAnimations.end())
		{
			AnimationBase* animation = _gAnimations[animationId];
			if (animation == nullptr)
			{
				LogError("PluginFadeEndFrames: Animation is null! id=%d\r\n", animationId);
				return;
			}
			if (fade <= 0)
			{
				return;
			}
			int frameCount = PluginGetFrameCount(animationId);
			for (int offset = 0; offset < fade; ++offset)
			{
				int frameId = frameCount - 1 - offset;
				float t = (offset + 1) / (float)fade;
				PluginMultiplyIntensity(animationId, frameId, t);
			}
		}
	}
	EXPORT_API void PluginFadeEndFramesName(const char* path, int fade)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginFadeEndFramesName: Animation not found! %s\r\n", path);
			return;
		}
		PluginFadeEndFrames(animationId, fade);
	}
	EXPORT_API double PluginFadeEndFramesNameD(const char* path, double fade)
	{
		PluginFadeEndFramesName(path, (int)fade);
		return 0;
	}


	EXPORT_API void PluginCopyRedChannelAllFrames(int animationId, float greenIntensity, float blueIntensity)
	{
		PluginStopAnimation(animationId);

		if (_gAnimations.find(animationId) != _gAnimations.end())
		{
			AnimationBase* animation = _gAnimations[animationId];
			if (animation == nullptr)
			{
				LogError("PluginCopyRedChannelAllFrames: Animation is null! id=%d\r\n", animationId);
				return;
			}
			int frameCount = PluginGetFrameCount(animationId);
			for (int frameId = 0; frameId < frameCount; ++frameId)
			{
				switch (animation->GetDeviceType())
				{
				case EChromaSDKDeviceTypeEnum::DE_1D:
				{
					Animation1D* animation1D = (Animation1D*)(animation);
					vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
					if (frameId >= 0 &&
						frameId < (int)frames.size())
					{
						FChromaSDKColorFrame1D& frame = frames[frameId];
						int maxLeds = ChromaSDKPlugin::GetInstance()->GetMaxLeds(animation1D->GetDevice());
						vector<COLORREF>& colors = frame.Colors;
						for (int i = 0; i < maxLeds; ++i)
						{
							int color = colors[i];
							int red = (color & 0xFF);
							int green = max(0, min(255, (int)(red * greenIntensity)));
							int blue = max(0, min(255, (int)(red * blueIntensity)));
							color = (red & 0xFF) | ((green & 0xFF) << 8) | ((blue & 0xFF) << 16);
							colors[i] = color;
						}
					}
				}
				break;
				case EChromaSDKDeviceTypeEnum::DE_2D:
				{
					Animation2D* animation2D = (Animation2D*)(animation);
					vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
					if (frameId >= 0 &&
						frameId < (int)frames.size())
					{
						FChromaSDKColorFrame2D& frame = frames[frameId];
						int maxRow = ChromaSDKPlugin::GetInstance()->GetMaxRow(animation2D->GetDevice());
						int maxColumn = ChromaSDKPlugin::GetInstance()->GetMaxColumn(animation2D->GetDevice());
						for (int i = 0; i < maxRow; ++i)
						{
							FChromaSDKColors& row = frame.Colors[i];
							for (int j = 0; j < maxColumn; ++j)
							{
								int color = row.Colors[j];
								int red = (color & 0xFF);
								int green = max(0, min(255, (int)(red * greenIntensity)));
								int blue = max(0, min(255, (int)(red * blueIntensity)));
								color = (red & 0xFF) | ((green & 0xFF) << 8) | ((blue & 0xFF) << 16);
								row.Colors[j] = color;
							}
						}
					}
				}
				break;
				}
			}
		}
	}
	EXPORT_API void PluginCopyRedChannelAllFramesName(const char* path, float greenIntensity, float blueIntensity)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginCopyRedChannelAllFramesName: Animation not found! %s\r\n", path);
			return;
		}
		PluginCopyRedChannelAllFrames(animationId, greenIntensity, blueIntensity);
	}
	EXPORT_API double PluginCopyRedChannelAllFramesNameD(const char* path, double greenIntensity, double blueIntensity)
	{
		PluginCopyRedChannelAllFramesName(path, (float)greenIntensity, (float)blueIntensity);
		return 0;
	}


	EXPORT_API void PluginCopyGreenChannelAllFrames(int animationId, float redIntensity, float blueIntensity)
	{
		PluginStopAnimation(animationId);

		if (_gAnimations.find(animationId) != _gAnimations.end())
		{
			AnimationBase* animation = _gAnimations[animationId];
			if (animation == nullptr)
			{
				LogError("PluginCopyGreenChannelAllFrames: Animation is null! id=%d\r\n", animationId);
				return;
			}
			int frameCount = PluginGetFrameCount(animationId);
			for (int frameId = 0; frameId < frameCount; ++frameId)
			{
				switch (animation->GetDeviceType())
				{
				case EChromaSDKDeviceTypeEnum::DE_1D:
				{
					Animation1D* animation1D = (Animation1D*)(animation);
					vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
					if (frameId >= 0 &&
						frameId < (int)frames.size())
					{
						FChromaSDKColorFrame1D& frame = frames[frameId];
						int maxLeds = ChromaSDKPlugin::GetInstance()->GetMaxLeds(animation1D->GetDevice());
						vector<COLORREF>& colors = frame.Colors;
						for (int i = 0; i < maxLeds; ++i)
						{
							int color = colors[i];
							int green = (color & 0xFF0000) >> 16;
							int red = max(0, min(255, (int)(green * redIntensity)));
							int blue = max(0, min(255, (int)(green * blueIntensity)));
							color = (red & 0xFF) | ((green & 0xFF) << 8) | ((blue & 0xFF) << 16);
							colors[i] = color;
						}
					}
				}
				break;
				case EChromaSDKDeviceTypeEnum::DE_2D:
				{
					Animation2D* animation2D = (Animation2D*)(animation);
					vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
					if (frameId >= 0 &&
						frameId < (int)frames.size())
					{
						FChromaSDKColorFrame2D& frame = frames[frameId];
						int maxRow = ChromaSDKPlugin::GetInstance()->GetMaxRow(animation2D->GetDevice());
						int maxColumn = ChromaSDKPlugin::GetInstance()->GetMaxColumn(animation2D->GetDevice());
						for (int i = 0; i < maxRow; ++i)
						{
							FChromaSDKColors& row = frame.Colors[i];
							for (int j = 0; j < maxColumn; ++j)
							{
								int color = row.Colors[j];
								int green = (color & 0xFF0000) >> 16;
								int red = max(0, min(255, (int)(green * redIntensity)));
								int blue = max(0, min(255, (int)(green * blueIntensity)));
								color = (red & 0xFF) | ((green & 0xFF) << 8) | ((blue & 0xFF) << 16);
								row.Colors[j] = color;
							}
						}
					}
				}
				break;
				}
			}
		}
	}
	EXPORT_API void PluginCopyGreenChannelAllFramesName(const char* path, float redIntensity, float blueIntensity)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginCopyGreenChannelAllFramesName: Animation not found! %s\r\n", path);
			return;
		}
		PluginCopyGreenChannelAllFrames(animationId, redIntensity, blueIntensity);
	}
	EXPORT_API double PluginCopyGreenChannelAllFramesNameD(const char* path, double redIntensity, double blueIntensity)
	{
		PluginCopyGreenChannelAllFramesName(path, (float)redIntensity, (float)blueIntensity);
		return 0;
	}


	EXPORT_API void PluginCopyBlueChannelAllFrames(int animationId, float redIntensity, float greenIntensity)
	{
		PluginStopAnimation(animationId);

		if (_gAnimations.find(animationId) != _gAnimations.end())
		{
			AnimationBase* animation = _gAnimations[animationId];
			if (animation == nullptr)
			{
				LogError("PluginCopyBlueChannelAllFrames: Animation is null! id=%d\r\n", animationId);
				return;
			}
			int frameCount = PluginGetFrameCount(animationId);
			for (int frameId = 0; frameId < frameCount; ++frameId)
			{
				switch (animation->GetDeviceType())
				{
				case EChromaSDKDeviceTypeEnum::DE_1D:
				{
					Animation1D* animation1D = (Animation1D*)(animation);
					vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
					if (frameId >= 0 &&
						frameId < (int)frames.size())
					{
						FChromaSDKColorFrame1D& frame = frames[frameId];
						int maxLeds = ChromaSDKPlugin::GetInstance()->GetMaxLeds(animation1D->GetDevice());
						vector<COLORREF>& colors = frame.Colors;
						for (int i = 0; i < maxLeds; ++i)
						{
							int color = colors[i];
							int green = (color & 0xFF00) >> 8;
							int red = max(0, min(255, (int)(green * redIntensity)));
							int blue = max(0, min(255, (int)(green * greenIntensity)));
							color = (red & 0xFF) | ((green & 0xFF) << 8) | ((blue & 0xFF) << 16);
							colors[i] = color;
						}
					}
				}
				break;
				case EChromaSDKDeviceTypeEnum::DE_2D:
				{
					Animation2D* animation2D = (Animation2D*)(animation);
					vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
					if (frameId >= 0 &&
						frameId < (int)frames.size())
					{
						FChromaSDKColorFrame2D& frame = frames[frameId];
						int maxRow = ChromaSDKPlugin::GetInstance()->GetMaxRow(animation2D->GetDevice());
						int maxColumn = ChromaSDKPlugin::GetInstance()->GetMaxColumn(animation2D->GetDevice());
						for (int i = 0; i < maxRow; ++i)
						{
							FChromaSDKColors& row = frame.Colors[i];
							for (int j = 0; j < maxColumn; ++j)
							{
								int color = row.Colors[j];
								int green = (color & 0xFF00) >> 8;
								int red = max(0, min(255, (int)(green * redIntensity)));
								int blue = max(0, min(255, (int)(green * greenIntensity)));
								color = (red & 0xFF) | ((green & 0xFF) << 8) | ((blue & 0xFF) << 16);
								row.Colors[j] = color;
							}
						}
					}
				}
				break;
				}
			}
		}
	}
	EXPORT_API void PluginCopyBlueChannelAllFramesName(const char* path, float redIntensity, float greenIntensity)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginCopyBlueChannelAllFramesName: Animation not found! %s\r\n", path);
			return;
		}
		PluginCopyBlueChannelAllFrames(animationId, redIntensity, greenIntensity);
	}
	EXPORT_API double PluginCopyBlueChannelAllFramesNameD(const char* path, double redIntensity, double greenIntensity)
	{
		PluginCopyBlueChannelAllFramesName(path, (float)redIntensity, (float)greenIntensity);
		return 0;
	}


	EXPORT_API int PluginCopyAnimation(int sourceAnimationId, const char* targetAnimation)
	{
		AnimationBase* sourceAnimation = GetAnimationInstance(sourceAnimationId);
		if (nullptr == sourceAnimation)
		{
			return -1;
		}
		PluginCloseAnimationName(targetAnimation);
		int deviceType = sourceAnimation->GetDeviceTypeId();
		int device = sourceAnimation->GetDeviceId();
		int targetAnimationId = PluginCreateAnimationInMemory(deviceType, device);
		if (targetAnimationId < 0)
		{
			return -1;
		}
		switch ((EChromaSDKDeviceTypeEnum)deviceType)
		{
		case EChromaSDKDeviceTypeEnum::DE_1D:
		{
			Animation1D* targetAnimation1D = new Animation1D();
			targetAnimation1D->SetDevice((EChromaSDKDevice1DEnum)device);
			targetAnimation1D->SetName(targetAnimation);
			vector<FChromaSDKColorFrame1D>& targetFrames = targetAnimation1D->GetFrames();
			targetFrames.clear();
			Animation1D* sourceAnimation1D = (Animation1D*)sourceAnimation;
			vector<FChromaSDKColorFrame1D>& sourceFrames = sourceAnimation1D->GetFrames();
			for (int frameId = 0; frameId < (int)sourceFrames.size(); ++frameId)
			{
				FChromaSDKColorFrame1D frame = sourceFrames[frameId];
				targetFrames.push_back(frame);
			}

			int id = _gAnimationId;
			_gAnimations[id] = targetAnimation1D;
			++_gAnimationId;
			_gAnimationMapID[targetAnimation] = id;
			return id;
		}
		break;
		case EChromaSDKDeviceTypeEnum::DE_2D:
		{
			Animation2D* targetAnimation2D = new Animation2D();
			targetAnimation2D->SetDevice((EChromaSDKDevice2DEnum)device);
			targetAnimation2D->SetName(targetAnimation);
			vector<FChromaSDKColorFrame2D>& targetFrames = targetAnimation2D->GetFrames();
			targetFrames.clear();
			Animation2D* sourceAnimation2D = (Animation2D*)sourceAnimation;
			vector<FChromaSDKColorFrame2D>& sourceFrames = sourceAnimation2D->GetFrames();
			for (int frameId = 0; frameId < (int)sourceFrames.size(); ++frameId)
			{
				FChromaSDKColorFrame2D frame = sourceFrames[frameId];
				targetFrames.push_back(frame);
			}

			int id = _gAnimationId;
			_gAnimations[id] = targetAnimation2D;
			++_gAnimationId;
			_gAnimationMapID[targetAnimation] = id;
			return id;
		}
		break;
		}
		return -1;
	}
	EXPORT_API void PluginCopyAnimationName(const char* sourceAnimation, const char* targetAnimation)
	{
		int sourceAnimationId = PluginGetAnimation(sourceAnimation);
		if (sourceAnimationId < 0)
		{
			LogError("PluginCopyAnimationName: Source animation not found! %s\r\n", sourceAnimation);
			return;
		}
		PluginCopyAnimation(sourceAnimationId, targetAnimation);
	}
	EXPORT_API double PluginCopyAnimationNameD(const char* sourceAnimation, const char* targetAnimation)
	{
		PluginCopyAnimationName(sourceAnimation, targetAnimation);
		return 0;
	}


	EXPORT_API void PluginAppendAllFrames(int sourceAnimationId, int targetAnimationId)
	{
		AnimationBase* sourceAnimation = GetAnimationInstance(sourceAnimationId);
		if (nullptr == sourceAnimation)
		{
			return;
		}
		AnimationBase* targetAnimation = GetAnimationInstance(targetAnimationId);
		if (nullptr == targetAnimation)
		{
			return;
		}
		if (sourceAnimation->GetDeviceType() != targetAnimation->GetDeviceType() ||
			sourceAnimation->GetDeviceId() != sourceAnimation->GetDeviceId())
		{
			return;
		}
		PluginStopAnimation(targetAnimationId);
		switch (sourceAnimation->GetDeviceType())
		{
		case EChromaSDKDeviceTypeEnum::DE_1D:
		{
			Animation1D* sourceAnimation1D = (Animation1D*)sourceAnimation;
			vector<FChromaSDKColorFrame1D>& sourceFrames = sourceAnimation1D->GetFrames();
			Animation1D* targetAnimation1D = (Animation1D*)targetAnimation;
			vector<FChromaSDKColorFrame1D>& targetFrames = targetAnimation1D->GetFrames();
			int frameCount = (int)sourceFrames.size();
			for (int frameId = 0; frameId < frameCount; ++frameId)
			{
				FChromaSDKColorFrame1D frame = sourceFrames[frameId];
				targetFrames.push_back(frame);
			}
		}
		break;
		case EChromaSDKDeviceTypeEnum::DE_2D:
		{
			Animation2D* sourceAnimation2D = (Animation2D*)sourceAnimation;
			vector<FChromaSDKColorFrame2D>& sourceFrames = sourceAnimation2D->GetFrames();
			Animation2D* targetAnimation2D = (Animation2D*)targetAnimation;
			vector<FChromaSDKColorFrame2D>& targetFrames = targetAnimation2D->GetFrames();
			int frameCount = (int)sourceFrames.size();
			for (int frameId = 0; frameId < frameCount; ++frameId)
			{
				FChromaSDKColorFrame2D frame = sourceFrames[frameId];
				targetFrames.push_back(frame);
			}
		}
		break;
		}
	}
	EXPORT_API void PluginAppendAllFramesName(const char* sourceAnimation, const char* targetAnimation)
	{
		int sourceAnimationId = PluginGetAnimation(sourceAnimation);
		if (sourceAnimationId < 0)
		{
			LogError("PluginAppendAllFramesName: Source animation not found! %s\r\n", sourceAnimation);
			return;
		}
		int targetAnimationId = PluginGetAnimation(targetAnimation);
		if (targetAnimationId < 0)
		{
			LogError("PluginAppendAllFramesName: Target animation not found! %s\r\n", targetAnimation);
			return;
		}
		PluginAppendAllFrames(sourceAnimationId, targetAnimationId);
	}
	EXPORT_API double PluginAppendAllFramesNameD(const char* sourceAnimation, const char* targetAnimation)
	{
		PluginAppendAllFramesName(sourceAnimation, targetAnimation);
		return 0;
	}


	EXPORT_API RZRESULT PluginCreateEffect(RZDEVICEID deviceId, EFFECT_TYPE effect, int* colors, int size, FChromaSDKGuid* effectId)
	{
		// Chroma thread plays animations
		SetupChromaThread();

		vector<FChromaSDKColors> newColors = vector<FChromaSDKColors>();

		int index = 0;
		for (int i = 0; i < MAX_ROW; i++)
		{
			FChromaSDKColors row = FChromaSDKColors();
			for (int j = 0; j < MAX_COLUMN; ++j)
			{
				if (index < size)
				{
					int color = colors[index];
					row.Colors.push_back(color);
				}
				++index;
			}
			newColors.push_back(row);
		}

		FChromaSDKEffectResult result = ChromaSDKPlugin::GetInstance()->CreateEffect(deviceId, effect, newColors);

		effectId->Data.Data1 = result.EffectId.Data.Data1;
		effectId->Data.Data2 = result.EffectId.Data.Data2;
		effectId->Data.Data3 = result.EffectId.Data.Data3;
		effectId->Data.Data4[0] = result.EffectId.Data.Data4[0];
		effectId->Data.Data4[1] = result.EffectId.Data.Data4[1];
		effectId->Data.Data4[2] = result.EffectId.Data.Data4[2];
		effectId->Data.Data4[3] = result.EffectId.Data.Data4[3];
		effectId->Data.Data4[4] = result.EffectId.Data.Data4[4];
		effectId->Data.Data4[5] = result.EffectId.Data.Data4[5];
		effectId->Data.Data4[6] = result.EffectId.Data.Data4[6];
		effectId->Data.Data4[7] = result.EffectId.Data.Data4[7];
		return result.Result;
	}

	EXPORT_API RZRESULT PluginSetEffect(const FChromaSDKGuid& effectId)
	{
		// Chroma thread plays animations
		SetupChromaThread();

		RZRESULT result = ChromaSDKPlugin::GetInstance()->SetEffect(effectId);
		return result;
	}

	EXPORT_API RZRESULT PluginDeleteEffect(const FChromaSDKGuid& effectId)
	{
		// Chroma thread plays animations
		SetupChromaThread();

		RZRESULT result = ChromaSDKPlugin::GetInstance()->DeleteEffect(effectId);
		return result;
	}

	EXPORT_API void PluginUseIdleAnimation(int device, bool flag)
	{
		// Chroma thread plays animations
		SetupChromaThread();

		ChromaSDKPlugin::GetInstance()->UseIdleAnimation((EChromaSDKDeviceEnum)device, flag);
	}

	EXPORT_API void PluginUseIdleAnimations(bool flag)
	{
		ChromaSDKPlugin::GetInstance()->UseIdleAnimation(EChromaSDKDeviceEnum::DE_ChromaLink, flag);
		ChromaSDKPlugin::GetInstance()->UseIdleAnimation(EChromaSDKDeviceEnum::DE_Headset, flag);
		ChromaSDKPlugin::GetInstance()->UseIdleAnimation(EChromaSDKDeviceEnum::DE_Keyboard, flag);
		ChromaSDKPlugin::GetInstance()->UseIdleAnimation(EChromaSDKDeviceEnum::DE_Keypad, flag);
		ChromaSDKPlugin::GetInstance()->UseIdleAnimation(EChromaSDKDeviceEnum::DE_Mouse, flag);
		ChromaSDKPlugin::GetInstance()->UseIdleAnimation(EChromaSDKDeviceEnum::DE_Mousepad, flag);
	}

	EXPORT_API void PluginSetIdleAnimation(int animationId)
	{
		// Chroma thread plays animations
		SetupChromaThread();

		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			LogError("PluginSetIdleAnimation: Animation is null! id=%d\r\n", animationId);
			return;
		}

		ChromaSDKPlugin::GetInstance()->SetIdleAnimationName(animation->GetName().c_str());
	}

	EXPORT_API void PluginSetIdleAnimationName(const char* path)
	{
		// Chroma thread plays animations
		SetupChromaThread();

		ChromaSDKPlugin::GetInstance()->SetIdleAnimationName(path);
	}

	EXPORT_API void PluginUsePreloading(int animationId, bool flag)
	{
		// Chroma thread plays animations
		SetupChromaThread();

		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			LogError("PluginUsePreloading: Animation is null! id=%d\r\n", animationId);
			return;
		}

		animation->UsePreloading(flag);
	}

	EXPORT_API void PluginUsePreloadingName(const char* path, bool flag)
	{
		// Chroma thread plays animations
		SetupChromaThread();

		AnimationBase* animation = GetAnimationInstanceName(path);
		if (nullptr == animation)
		{
			LogError("PluginUsePreloadingName: Animation is null! %s\r\n", path);
			return;
		}

		animation->UsePreloading(flag);
	}

	EXPORT_API void PluginSetStaticColor(int deviceType, int device, int color)
	{
		PluginStopAnimationType(deviceType, device);
		FChromaSDKEffectResult result;
		switch ((EChromaSDKDeviceTypeEnum)deviceType)
		{
		case EChromaSDKDeviceTypeEnum::DE_1D:
			result = ChromaSDKPlugin::GetInstance()->CreateEffectStatic1D((EChromaSDKDevice1DEnum)device, color);
			if (result.Result == 0)
			{
				ChromaSDKPlugin::GetInstance()->SetEffect(result.EffectId);
				ChromaSDKPlugin::GetInstance()->DeleteEffect(result.EffectId);
			}
			break;
		case EChromaSDKDeviceTypeEnum::DE_2D:
			result = ChromaSDKPlugin::GetInstance()->CreateEffectStatic2D((EChromaSDKDevice2DEnum)device, color);
			if (result.Result == 0)
			{
				ChromaSDKPlugin::GetInstance()->SetEffect(result.EffectId);
				ChromaSDKPlugin::GetInstance()->DeleteEffect(result.EffectId);
			}
			break;
		}
	}

	EXPORT_API void PluginSetStaticColorAll(int color)
	{
		PluginSetStaticColor((int)EChromaSDKDeviceTypeEnum::DE_1D, (int)EChromaSDKDevice1DEnum::DE_ChromaLink, color);
		PluginSetStaticColor((int)EChromaSDKDeviceTypeEnum::DE_1D, (int)EChromaSDKDevice1DEnum::DE_Headset, color);
		PluginSetStaticColor((int)EChromaSDKDeviceTypeEnum::DE_2D, (int)EChromaSDKDevice2DEnum::DE_Keyboard, color);
		PluginSetStaticColor((int)EChromaSDKDeviceTypeEnum::DE_2D, (int)EChromaSDKDevice2DEnum::DE_Keypad, color);
		PluginSetStaticColor((int)EChromaSDKDeviceTypeEnum::DE_2D, (int)EChromaSDKDevice2DEnum::DE_Mouse, color);
		PluginSetStaticColor((int)EChromaSDKDeviceTypeEnum::DE_1D, (int)EChromaSDKDevice1DEnum::DE_Mousepad, color);
	}

	EXPORT_API void PluginStaticColor(int deviceType, int device, int color)
	{
		PluginSetStaticColor(deviceType, device, color);
	}

	EXPORT_API void PluginStaticColorAll(int color)
	{
		PluginSetStaticColorAll(color);
	}

	EXPORT_API double PluginStaticColorD(double deviceType, double device, double color)
	{
		PluginStaticColor((int)deviceType, (int)device, (int)color);
		return 0;
	}

	EXPORT_API RZRESULT PluginSetEffectCustom1D(const int device, const int* colors)
	{
		int maxLeds = ChromaSDKPlugin::GetInstance()->GetMaxLeds((EChromaSDKDevice1DEnum)device);

		RZRESULT result = 0;
		switch ((EChromaSDKDevice1DEnum)device)
		{
		case EChromaSDKDevice1DEnum::DE_ChromaLink:
		{
			ChromaLink::CUSTOM_EFFECT_TYPE pParam = {};
			for (int i = 0; i < maxLeds; i++)
			{
				pParam.Color[i] = colors[i];
			}
			result = RzChromaSDK::CreateChromaLinkEffect(ChromaLink::CHROMA_CUSTOM, &pParam, nullptr);
		}
		break;
		case EChromaSDKDevice1DEnum::DE_Headset:
		{
			Headset::CUSTOM_EFFECT_TYPE pParam = {};
			for (int i = 0; i < maxLeds; i++)
			{
				pParam.Color[i] = colors[i];
			}
			result = RzChromaSDK::CreateHeadsetEffect(Headset::CHROMA_CUSTOM, &pParam, nullptr);
		}
		break;
		case EChromaSDKDevice1DEnum::DE_Mousepad:
		{
			Mousepad::CUSTOM_EFFECT_TYPE pParam = {};
			for (int i = 0; i < maxLeds; i++)
			{
				pParam.Color[i] = colors[i];
			}
			result = RzChromaSDK::CreateMousepadEffect(Mousepad::CHROMA_CUSTOM, &pParam, nullptr);
		}
		break;
		default:
			LogError("PluginSetEffectCustom1D Unsupported device used!\r\n");
			return RZRESULT_FAILED;
		}
		return result;
	}

	EXPORT_API RZRESULT PluginSetEffectCustom2D(const int device, const int* colors)
	{
		int maxRow = ChromaSDKPlugin::GetInstance()->GetMaxRow((EChromaSDKDevice2DEnum)device);
		int maxColumn = ChromaSDKPlugin::GetInstance()->GetMaxColumn((EChromaSDKDevice2DEnum)device);

		RZRESULT result = 0;
		switch ((EChromaSDKDevice2DEnum)device)
		{
		case EChromaSDKDevice2DEnum::DE_Keyboard:
		{
			Keyboard::CUSTOM_EFFECT_TYPE pParam = {};
			int index = 0;
			for (int i = 0; i < maxRow; i++)
			{
				for (int j = 0; j < maxColumn; j++)
				{
					pParam.Color[i][j] = colors[index];
					++index;
				}
			}
			result = RzChromaSDK::CreateKeyboardEffect(Keyboard::CHROMA_CUSTOM, &pParam, nullptr);
		}
		break;
		case EChromaSDKDevice2DEnum::DE_KeyboardExtended:
		{
			Keyboard::v2::CUSTOM_EFFECT_TYPE pParam = {};
			int index = 0;
			for (int i = 0; i < maxRow; i++)
			{
				for (int j = 0; j < maxColumn; j++)
				{
					pParam.Color[i][j] = colors[index];
					++index;
				}
			}
			result = RzChromaSDK::CreateKeyboardEffect(Keyboard::CHROMA_CUSTOM2, &pParam, nullptr);
		}
		break;
		case EChromaSDKDevice2DEnum::DE_Keypad:
		{
			Keypad::CUSTOM_EFFECT_TYPE pParam = {};
			int index = 0;
			for (int i = 0; i < maxRow; i++)
			{
				for (int j = 0; j < maxColumn; j++)
				{
					pParam.Color[i][j] = colors[index];
					++index;
				}
			}
			result = RzChromaSDK::CreateKeypadEffect(Keypad::CHROMA_CUSTOM, &pParam, nullptr);
		}
		break;
		case EChromaSDKDevice2DEnum::DE_Mouse:
		{
			Mouse::CUSTOM_EFFECT_TYPE2 pParam = {};
			int index = 0;
			for (int i = 0; i < maxRow; i++)
			{
				for (int j = 0; j < maxColumn; j++)
				{
					pParam.Color[i][j] = colors[index];
					++index;
				}
			}
			result = RzChromaSDK::CreateMouseEffect(Mouse::CHROMA_CUSTOM2, &pParam, nullptr);
		}
		break;
		default:
			LogError("PluginSetEffectCustom2D Unsupported device used!\r\n");
			return RZRESULT_FAILED;
		}

		return result;
	}

	EXPORT_API RZRESULT PluginSetEffectKeyboardCustom2D(const int device, const int* colors, const int* keys)
	{
		switch ((EChromaSDKDevice2DEnum)device)
		{
		case EChromaSDKDevice2DEnum::DE_Keyboard:
		case EChromaSDKDevice2DEnum::DE_KeyboardExtended:
			break;
		default:
			return RZRESULT_FAILED;
		}

		int maxRow = ChromaSDKPlugin::GetInstance()->GetMaxRow((EChromaSDKDevice2DEnum)device);
		int maxColumn = ChromaSDKPlugin::GetInstance()->GetMaxColumn((EChromaSDKDevice2DEnum)device);

		RZRESULT result = 0;

		Keyboard::CUSTOM_KEY_EFFECT_TYPE pParam = {};
		int index = 0;
		for (int i = 0; i < maxRow; i++)
		{
			for (int j = 0; j < maxColumn; j++)
			{
				pParam.Color[i][j] = colors[index];
				++index;
			}
		}

		if (keys)
		{
			// Keyboard and KeyboardExtended are 6x22
			maxRow = ChromaSDKPlugin::GetInstance()->GetMaxRow(EChromaSDKDevice2DEnum::DE_Keyboard);
			maxColumn = ChromaSDKPlugin::GetInstance()->GetMaxColumn(EChromaSDKDevice2DEnum::DE_Keyboard);

			index = 0;
			for (int i = 0; i < maxRow; i++)
			{
				for (int j = 0; j < maxColumn; j++)
				{
					pParam.Key[i][j] = keys[index];
					++index;
				}
			}
		}

		result = RzChromaSDK::CreateKeyboardEffect(Keyboard::CHROMA_CUSTOM_KEY, &pParam, nullptr);
		return result;
	}

	EXPORT_API RZRESULT PluginSetCustomColorFlag2D(int device, int* colors)
	{
		int maxRow = ChromaSDKPlugin::GetInstance()->GetMaxRow((EChromaSDKDevice2DEnum)device);
		int maxColumn = ChromaSDKPlugin::GetInstance()->GetMaxColumn((EChromaSDKDevice2DEnum)device);

		const int customFlag = 0x1 << 24;
		RZRESULT result = 0;
		switch ((EChromaSDKDevice2DEnum)device)
		{
		case EChromaSDKDevice2DEnum::DE_Keyboard:
		case EChromaSDKDevice2DEnum::DE_KeyboardExtended:
		{
			int index = 0;
			for (int i = 0; i < maxRow; i++)
			{
				for (int j = 0; j < maxColumn; j++)
				{
					colors[index] = colors[index] | customFlag;
					++index;
				}
			}
		}
		break;
		default:
			return RZRESULT_FAILED;
		}

		return RZRESULT_SUCCESS;
	}

	EXPORT_API int PluginAddColor(const int color1, const int color2)
	{
		int red1 = color1 & 0xFF;
		int green1 = (color1 & 0xFF00) >> 8;
		int blue1 = (color1 & 0xFF0000) >> 16;

		int red2 = color2 & 0xFF;
		int green2 = (color2 & 0xFF00) >> 8;
		int blue2 = (color2 & 0xFF0000) >> 16;

		int red = min(255, max(0, red1 + red2)) & 0xFF;
		int green = min(255, max(0, green1 + green2)) & 0xFF;
		int blue = min(255, max(0, blue1 + blue2)) & 0xFF;

		int newColor = red | (green << 8) | (blue << 16);
		return newColor;
	}

	EXPORT_API int PluginSubtractColor(const int color1, const int color2)
	{
		int red1 = color1 & 0xFF;
		int green1 = (color1 & 0xFF00) >> 8;
		int blue1 = (color1 & 0xFF0000) >> 16;

		int red2 = color2 & 0xFF;
		int green2 = (color2 & 0xFF00) >> 8;
		int blue2 = (color2 & 0xFF0000) >> 16;

		int red = min(255, max(0, red1 - red2)) & 0xFF;
		int green = min(255, max(0, green1 - green2)) & 0xFF;
		int blue = min(255, max(0, blue1 - blue2)) & 0xFF;

		int newColor = red | (green << 8) | (blue << 16);
		return newColor;
	}

	EXPORT_API void PluginSubtractThresholdColorsMinMaxRGB(const int animationId, const int frameId, const int minThreshold, const int minRed, const int minGreen, const int minBlue, const int maxThreshold, const int maxRed, const int maxGreen, const int maxBlue)
	{
		PluginStopAnimation(animationId);
		int minColor = PluginGetRGB(minRed, minGreen, minBlue);
		int maxColor = PluginGetRGB(maxRed, maxGreen, maxBlue);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		switch (animation->GetDeviceType())
		{
		case EChromaSDKDeviceTypeEnum::DE_1D:
		{
			Animation1D* animation1D = (Animation1D*)(animation);
			vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
			if (frameId >= 0 &&
				frameId < (int)frames.size())
			{
				FChromaSDKColorFrame1D& frame = frames[frameId];
				int maxLeds = PluginGetMaxLeds((int)animation1D->GetDevice());
				vector<COLORREF>& colors = frame.Colors;
				for (int i = 0; i < maxLeds; ++i)
				{
					int oldColor = colors[i];
					int red = oldColor & 0xFF;
					int green = (oldColor & 0xFF00) >> 8;
					int blue = (oldColor & 0xFF0000) >> 16;
					if (red != 0 ||
						green != 0 ||
						blue != 0)
					{
						if (red <= minThreshold &&
							green <= minThreshold &&
							blue <= minThreshold) {

							colors[i] = PluginSubtractColor(oldColor, minColor);
						}
						else if (red >= maxThreshold ||
							green >= maxThreshold ||
							blue >= maxThreshold) {
							colors[i] = PluginSubtractColor(oldColor, maxColor);
						}
					}
				}
			}
		}
		break;
		case EChromaSDKDeviceTypeEnum::DE_2D:
		{
			Animation2D* animation2D = (Animation2D*)(animation);
			vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
			if (frameId >= 0 &&
				frameId < (int)frames.size())
			{
				FChromaSDKColorFrame2D& frame = frames[frameId];
				int maxRow = PluginGetMaxRow((int)animation2D->GetDevice());
				int maxColumn = PluginGetMaxColumn((int)animation2D->GetDevice());
				for (int i = 0; i < maxRow; ++i)
				{
					FChromaSDKColors& row = frame.Colors[i];
					for (int j = 0; j < maxColumn; ++j)
					{
						int oldColor = row.Colors[j];
						int red = oldColor & 0xFF;
						int green = (oldColor & 0xFF00) >> 8;
						int blue = (oldColor & 0xFF0000) >> 16;
						if (red != 0 ||
							green != 0 ||
							blue != 0)
						{
							if (red <= minThreshold &&
								green <= minThreshold &&
								blue <= minThreshold) {
								row.Colors[j] = PluginSubtractColor(oldColor, minColor);
							}
							else if (red >= maxThreshold ||
								green >= maxThreshold ||
								blue >= maxThreshold) {
								row.Colors[j] = PluginSubtractColor(oldColor, maxColor);
							}
						}
					}
				}
			}
		}
		break;
		}
	}
	EXPORT_API void PluginSubtractThresholdColorsMinMaxRGBName(const char* path, const int frameId, const int minThreshold, const int minRed, const int minGreen, const int minBlue, const int maxThreshold, const int maxRed, const int maxGreen, const int maxBlue)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			ChromaLogger::fprintf(stderr, "PluginSubtractThresholdColorsMinMaxRGBName: Animation not found! %s\r\n", path);
			return;
		}
		return PluginSubtractThresholdColorsMinMaxRGB(animationId, frameId, minThreshold, minRed, minGreen, minBlue, maxThreshold, maxRed, maxGreen, maxBlue);
	}
	EXPORT_API double PluginSubtractThresholdColorsMinMaxRGBNameD(const char* path, const int frameId, const int minThreshold, const int minRed, const int minGreen, const int minBlue, const int maxThreshold, const int maxRed, const int maxGreen, const int maxBlue)
	{
		PluginSubtractThresholdColorsMinMaxRGBName(path, (int)minThreshold, (int)frameId, (int)minRed, (int)minGreen, (int)minBlue, (int)maxThreshold, (int)maxRed, (int)maxGreen, (int)maxBlue);
		return 0;
	}

	EXPORT_API void PluginSubtractThresholdColorsMinMaxAllFramesRGB(const int animationId, const int minThreshold, const int minRed, const int minGreen, const int minBlue, const int maxThreshold, const int maxRed, const int maxGreen, const int maxBlue)
	{
		PluginStopAnimation(animationId);
		AnimationBase* animation = GetAnimationInstance(animationId);
		if (nullptr == animation)
		{
			return;
		}
		int frameCount = animation->GetFrameCount();
		for (int frameId = 0; frameId < frameCount; ++frameId)
		{
			PluginSubtractThresholdColorsMinMaxRGB(animationId, frameId, minThreshold, minRed, minGreen, minBlue, maxThreshold, maxRed, maxGreen, maxBlue);
		}
	}
	EXPORT_API void PluginSubtractThresholdColorsMinMaxAllFramesRGBName(const char* path, const int minThreshold, const int minRed, const int minGreen, const int minBlue, const int maxThreshold, const int maxRed, const int maxGreen, const int maxBlue)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			ChromaLogger::fprintf(stderr, "PluginSubtractThresholdColorsMinMaxAllFramesRGBName: Animation not found! %s\r\n", path);
			return;
		}
		return PluginSubtractThresholdColorsMinMaxAllFramesRGB(animationId, minThreshold, minRed, minGreen, minBlue, maxThreshold, maxRed, maxGreen, maxBlue);
	}
	EXPORT_API double PluginSubtractThresholdColorsMinMaxAllFramesRGBNameD(const char* path, double minThreshold, double minRed, double minGreen, double minBlue, double maxThreshold, double maxRed, double maxGreen, double maxBlue)
	{
		PluginSubtractThresholdColorsMinMaxAllFramesRGBName(path, (int)minThreshold, (int)minRed, (int)minGreen, (int)minBlue, (int)maxThreshold, (int)maxRed, (int)maxGreen, (int)maxBlue);
		return 0;
	}
}
