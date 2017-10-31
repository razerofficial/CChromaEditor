// stdafx.cpp : source file that includes just the standard includes
// CChromaEditorLibrary.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
#include "CChromaEditorLibrary.h"
#include "ChromaThread.h"
#include <map>
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
	ChromaThread::Instance()->Start();
}

void StopChromaThread()
{
	ChromaThread::Instance()->Stop();
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
	EXPORT_API void PluginSetLogDelegate(DebugLogPtr fp)
	{
		_gDebugLogPtr = fp;
		LogDebug("PluginSetLogDelegate:");
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
		// Chroma thread plays animations
		SetupChromaThread();

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

		LogDebug("PluginOpenEditorDialog %s\r\n", path);

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

		LogDebug("PluginOpenEditorDialogAndPlay %s\r\n", path);

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

	EXPORT_API int PluginOpenAnimation(const char* path)
	{
		try
		{
			// Chroma thread plays animations
			SetupChromaThread();

			if (!PluginIsInitialized())
			{
				LogError("PluginOpenAnimation: Plugin is not initialized!\r\n");
				return -1;
			}

			//return animation id
			AnimationBase* animation = ChromaSDKPlugin::GetInstance()->OpenAnimation(path);
			if (animation == nullptr)
			{
				LogError("PluginOpenAnimation: Animation is null! name=%s\r\n", path);
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

	EXPORT_API double PluginOpenAnimationD(const char* path)
	{
		return PluginOpenAnimation(path);
	}

	EXPORT_API int PluginLoadAnimation(int animationId)
	{
		try
		{
			// Chroma thread plays animations
			SetupChromaThread();

			if (!PluginIsInitialized())
			{
				LogError("PluginLoadAnimation: Plugin is not initialized!\r\n");
				return -1;
			}

			if (_gAnimations.find(animationId) != _gAnimations.end())
			{
				AnimationBase* animation = _gAnimations[animationId];
				if (animation == nullptr)
				{
					LogError("PluginLoadAnimation: Animation is null! id=%d", animationId);
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

	EXPORT_API double PluginLoadAnimationD(double animationId)
	{
		return (double)PluginLoadAnimation((int)animationId);
	}

	EXPORT_API int PluginUnloadAnimation(int animationId)
	{
		try
		{
			// Chroma thread plays animations
			SetupChromaThread();

			if (!PluginIsInitialized())
			{
				LogError("PluginUnloadAnimation: Plugin is not initialized!\r\n");
				return -1;
			}

			if (_gAnimations.find(animationId) != _gAnimations.end())
			{
				AnimationBase* animation = _gAnimations[animationId];
				if (animation == nullptr)
				{
					LogError("PluginUnloadAnimation: Animation is null! id=%d", animationId);
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
					LogError("PluginPlayAnimation: Animation is null! id=%d", animationId);
					return -1;
				}
				PluginStopAnimationType(animation->GetDeviceTypeId(), animation->GetDeviceId());
				switch (animation->GetDeviceType())
				{
				case EChromaSDKDeviceTypeEnum::DE_1D:
					_gPlayMap1D[(EChromaSDKDevice1DEnum)animation->GetDeviceId()] = animationId;
					break;
				case EChromaSDKDeviceTypeEnum::DE_2D:
					_gPlayMap2D[(EChromaSDKDevice2DEnum)animation->GetDeviceId()] = animationId;
					break;
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
			// Chroma thread plays animations
			SetupChromaThread();

			if (!PluginIsInitialized())
			{
				LogError("PluginIsPlaying: Plugin is not initialized!\r\n");
				return false;
			}

			if (_gAnimations.find(animationId) != _gAnimations.end())
			{
				AnimationBase* animation = _gAnimations[animationId];
				if (animation == nullptr)
				{
					LogError("PluginIsPlaying: Animation is null! id=%d", animationId);
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
			// Chroma thread plays animations
			SetupChromaThread();

			if (!PluginIsInitialized())
			{
				LogError("PluginStopAnimation: Plugin is not initialized!\r\n");
				return -1;
			}

			if (_gAnimations.find(animationId) != _gAnimations.end())
			{
				AnimationBase* animation = _gAnimations[animationId];
				if (animation == nullptr)
				{
					LogError("PluginStopAnimation: Animation is null! id=%d", animationId);
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
			// Chroma thread plays animations
			SetupChromaThread();

			if (!PluginIsInitialized())
			{
				LogError("PluginCloseAnimation: Plugin is not initialized!\r\n");
				return -1;
			}

			if (_gAnimations.find(animationId) != _gAnimations.end())
			{
				AnimationBase* animation = _gAnimations[animationId];
				if (animation == nullptr)
				{
					LogError("PluginCloseAnimation: Animation is null! id=%d", animationId);
					return -1;
				}
				animation->Stop();
				string animationName = animation->GetName();
				if (_gAnimationMapID.find(animationName) != _gAnimationMapID.end())
				{
					_gAnimationMapID.erase(animationName);
				}
				delete _gAnimations[animationId];
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

	EXPORT_API int PluginInit()
	{
		// Chroma thread plays animations
		SetupChromaThread();

		_gAnimationId = 0;
		_gAnimationMapID.clear();
		_gAnimations.clear();
		_gPlayMap1D.clear();
		_gPlayMap2D.clear();

		return ChromaSDKPlugin::GetInstance()->ChromaSDKInit();
	}

	EXPORT_API double PluginInitD()
	{
		return (double)PluginInit();
	}

	EXPORT_API int PluginUninit()
	{
		// Chroma thread plays animations
		StopChromaThread();

		int result = ChromaSDKPlugin::GetInstance()->ChromaSDKUnInit();
		if (PluginIsInitialized())
		{
			for (auto iter = _gAnimations.begin(); iter != _gAnimations.end(); ++iter)
			{
				PluginCloseAnimation(iter->first);
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
				FChromaSDKColorFrame2D frame = FChromaSDKColorFrame2D();
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
					Animation1D animation1D = Animation1D();
					animation1D.SetDevice((EChromaSDKDevice1DEnum)device);
					vector<FChromaSDKColorFrame1D>& frames = animation1D.GetFrames();
					frames.clear();
					FChromaSDKColorFrame1D frame = FChromaSDKColorFrame1D();
					frame.Colors = ChromaSDKPlugin::GetInstance()->CreateColors1D((EChromaSDKDevice1DEnum)device);
					frames.push_back(frame);
					animation1D.Save(path);
					return PluginOpenAnimation(path);
				}
				break;
			case EChromaSDKDeviceTypeEnum::DE_2D:
				{
					Animation2D animation2D = Animation2D();
					animation2D.SetDevice((EChromaSDKDevice2DEnum)device);
					vector<FChromaSDKColorFrame2D>& frames = animation2D.GetFrames();
					frames.clear();
					FChromaSDKColorFrame2D frame = FChromaSDKColorFrame2D();
					frame.Colors = ChromaSDKPlugin::GetInstance()->CreateColors2D((EChromaSDKDevice2DEnum)device);
					frames.push_back(frame);
					animation2D.Save(path);
					return PluginOpenAnimation(path);
				}
				break;
		}
		return -1;
	}

	EXPORT_API int PluginSaveAnimation(int animationId, const char* path)
	{
		PluginStopAnimation(animationId);

		// Chroma thread plays animations
		SetupChromaThread();

		if (!PluginIsInitialized())
		{
			LogError("PluginSaveAnimation: Plugin is not initialized!\r\n");
			return -1;
		}

		if (_gAnimations.find(animationId) != _gAnimations.end())
		{
			AnimationBase* animation = _gAnimations[animationId];
			if (animation == nullptr)
			{
				LogError("PluginSaveAnimation: Animation is null! id=%d", animationId);
				return -1;
			}
			animation->Save(path);
			return animationId;
		}
		return -1;
	}

	EXPORT_API int PluginResetAnimation(int animationId)
	{
		PluginStopAnimation(animationId);

		// Chroma thread plays animations
		SetupChromaThread();

		if (!PluginIsInitialized())
		{
			LogError("PluginResetAnimation: Plugin is not initialized!\r\n");
			return -1;
		}

		if (_gAnimations.find(animationId) != _gAnimations.end())
		{
			AnimationBase* animation = _gAnimations[animationId];
			if (animation == nullptr)
			{
				LogError("PluginResetAnimation: Animation is null! id=%d", animationId);
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
			LogError("PluginGetFrameCount: Animation is null! id=%d", animationId);
			return -1;
		}
		return animation->GetFrameCount();
	}

	EXPORT_API int PluginGetFrameCountName(const char* path)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginGetFrameCountName: Animation not found! %s", path);
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
			LogError("PluginGetCurrentFrameName: Animation not found! %s", path);
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
				LogError("PluginGetDeviceType: Animation is null! id=%d", animationId);
				return -1;
			}
			return (int)animation->GetDeviceType();
		}

		return -1;
	}

	EXPORT_API int PluginGetDevice(int animationId)
	{
		if (_gAnimations.find(animationId) != _gAnimations.end())
		{
			AnimationBase* animation = _gAnimations[animationId];
			if (animation == nullptr)
			{
				LogError("PluginGetDevice: Animation is null! id=%d", animationId);
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

	EXPORT_API int PluginSetDevice(int animationId, int deviceType, int device)
	{
		PluginStopAnimation(animationId);

		// Chroma thread plays animations
		SetupChromaThread();

		if (!PluginIsInitialized())
		{
			LogError("PluginSetDevice: Plugin is not initialized!\r\n");
			return -1;
		}

		PluginCloseAnimation(animationId);

		switch ((EChromaSDKDeviceTypeEnum)deviceType)
		{
			case EChromaSDKDeviceTypeEnum::DE_1D:
			{
				Animation1D* animation1D = new Animation1D();
				animation1D->SetDevice((EChromaSDKDevice1DEnum)device);
				_gAnimations[animationId] = animation1D;
				return animationId;
			}
			break;
			case EChromaSDKDeviceTypeEnum::DE_2D:
			{
				Animation2D* animation2D = new Animation2D();
				animation2D->SetDevice((EChromaSDKDevice2DEnum)device);
				_gAnimations[animationId] = animation2D;
				return animationId;
			}
			break;
		}

		return -1;
	}

	EXPORT_API int PluginGetMaxLeds(int device)
	{
		return ChromaSDKPlugin::GetInstance()->GetMaxLeds((EChromaSDKDevice1DEnum)device);
	}

	EXPORT_API int PluginGetMaxRow(int device)
	{
		return ChromaSDKPlugin::GetInstance()->GetMaxRow((EChromaSDKDevice2DEnum)device);
	}

	EXPORT_API int PluginGetMaxColumn(int device)
	{
		return ChromaSDKPlugin::GetInstance()->GetMaxColumn((EChromaSDKDevice2DEnum)device);
	}

	EXPORT_API int PluginAddFrame(int animationId, float duration, int* colors, int length)
	{
		PluginStopAnimation(animationId);

		// Chroma thread plays animations
		SetupChromaThread();

		if (!PluginIsInitialized())
		{
			LogError("PluginAddFrame: Plugin is not initialized!\r\n");
			return -1;
		}

		if (_gAnimations.find(animationId) != _gAnimations.end())
		{
			AnimationBase* animation = _gAnimations[animationId];
			if (animation == nullptr)
			{
				LogError("PluginAddFrame: Animation is null! id=%d", animationId);
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
					if (duration >= 0.1f)
					{
						frame.Duration = duration;
					}
					else
					{
						frame.Duration = 0.1f;
					}
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
					FChromaSDKColorFrame2D frame = FChromaSDKColorFrame2D();
					if (duration >= 0.1f)
					{
						frame.Duration = duration;
					}
					else
					{
						frame.Duration = 0.1f;
					}
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

	EXPORT_API int PluginUpdateFrame(int animationId, int frameIndex, float duration, int* colors, int length)
	{
		PluginStopAnimation(animationId);

		// Chroma thread plays animations
		SetupChromaThread();

		if (!PluginIsInitialized())
		{
			LogError("PluginUpdateFrame: Plugin is not initialized!\r\n");
			return -1;
		}

		if (_gAnimations.find(animationId) != _gAnimations.end())
		{
			AnimationBase* animation = _gAnimations[animationId];
			if (animation == nullptr)
			{
				LogError("PluginUpdateFrame: Animation is null! id=%d", animationId);
				return -1;
			}
			switch (animation->GetDeviceType())
			{
			case EChromaSDKDeviceTypeEnum::DE_1D:
				{
					Animation1D* animation1D = dynamic_cast<Animation1D*>(animation);
					int maxLeds = ChromaSDKPlugin::GetInstance()->GetMaxLeds(animation1D->GetDevice());
					vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
					if (frameIndex < 0 || frameIndex >= frames.size())
					{
						LogError("PluginUpdateFrame: frame index is invalid! %d of %d", frameIndex, frames.size());
						return -1;
					}
					FChromaSDKColorFrame1D& frame = frames[frameIndex];
					if (duration >= 0.1f)
					{
						frame.Duration = duration;
					}
					else
					{
						frame.Duration = 0.1f;
					}
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
					if (frameIndex < 0 || frameIndex >= frames.size())
					{
						LogError("PluginUpdateFrame: frame index is invalid! %d of %d", frameIndex, frames.size());
						return -1;
					}
					FChromaSDKColorFrame2D& frame = frames[frameIndex];
					if (duration >= 0.1f)
					{
						frame.Duration = duration;
					}
					else
					{
						frame.Duration = 0.1f;
					}
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
				}
				break;
			}
			return animationId;
		}

		return -1;
	}

	EXPORT_API int PluginGetFrame(int animationId, int frameIndex, float* duration, int* colors, int length)
	{
		PluginStopAnimation(animationId);

		// Chroma thread plays animations
		SetupChromaThread();

		if (!PluginIsInitialized())
		{
			LogError("PluginGetFrame: Plugin is not initialized!\r\n");
			return -1;
		}

		if (_gAnimations.find(animationId) != _gAnimations.end())
		{
			AnimationBase* animation = _gAnimations[animationId];
			if (animation == nullptr)
			{
				LogError("PluginGetFrame: Animation is null! id=%d", animationId);
				return -1;
			}
			switch (animation->GetDeviceType())
			{
			case EChromaSDKDeviceTypeEnum::DE_1D:
				{
					Animation1D* animation1D = dynamic_cast<Animation1D*>(animation);
					int maxLeds = ChromaSDKPlugin::GetInstance()->GetMaxLeds(animation1D->GetDevice());
					vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
					if (frameIndex < 0 || frameIndex >= frames.size())
					{
						LogError("PluginGetFrame: frame index is invalid! %d of %d", frameIndex, frames.size());
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
					if (frameIndex < 0 || frameIndex >= frames.size())
					{
						LogError("PluginGetFrame: frame index is invalid! %d of %d", frameIndex, frames.size());
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
				LogError("PluginPreviewFrame: Animation is null! id=%d", animationId);
				return -1;
			}
			switch (animation->GetDeviceType())
			{
			case EChromaSDKDeviceTypeEnum::DE_1D:
				{
					Animation1D* animation1D = dynamic_cast<Animation1D*>(animation);
					int maxLeds = ChromaSDKPlugin::GetInstance()->GetMaxLeds(animation1D->GetDevice());
					vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
					if (frameIndex < 0 || frameIndex >= frames.size())
					{
						LogError("PluginPreviewFrame: frame index is invalid! %d of %d", frameIndex, frames.size());
						return -1;
					}
					FChromaSDKColorFrame1D frame = frames[frameIndex];
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
					if (frameIndex < 0 || frameIndex >= frames.size())
					{
						LogError("PluginPreviewFrame: frame index is invalid! %d of %d", frameIndex, frames.size());
						return -1;
					}
					FChromaSDKColorFrame2D frame = frames[frameIndex];
					vector<FChromaSDKColors>& colors = frame.Colors;
					FChromaSDKEffectResult result = ChromaSDKPlugin::GetInstance()->CreateEffectCustom2D(animation2D->GetDevice(), colors);
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

	EXPORT_API double PluginPreviewFrameD(double animationId, double frameIndex)
	{
		return (int)PluginPreviewFrame((int)animationId, (int)frameIndex);
	}

	EXPORT_API int PluginOverrideFrameDuration(int animationId, float duration)
	{
		PluginStopAnimation(animationId);

		// Chroma thread plays animations
		SetupChromaThread();

		if (!PluginIsInitialized())
		{
			LogError("PluginOverrideFrameDuration: Plugin is not initialized!\r\n");
			return -1;
		}

		if (_gAnimations.find(animationId) != _gAnimations.end())
		{
			AnimationBase* animation = _gAnimations[animationId];
			if (animation == nullptr)
			{
				LogError("PluginOverrideFrameDuration: Animation is null! id=%d", animationId);
				return -1;
			}
			switch (animation->GetDeviceType())
			{
			case EChromaSDKDeviceTypeEnum::DE_1D:
				{
					Animation1D* animation1D = dynamic_cast<Animation1D*>(animation);
					vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
					for (int i = 0; i < frames.size(); ++i)
					{
						FChromaSDKColorFrame1D& frame = frames[i];
						if (duration >= 0.1f)
						{
							frame.Duration = duration;
						}
						else
						{
							frame.Duration = 0.1f;
						}
					}
				}
				break;
			case EChromaSDKDeviceTypeEnum::DE_2D:
				{
					Animation2D* animation2D = dynamic_cast<Animation2D*>(animation);
					vector<FChromaSDKColorFrame2D>& frames = animation2D->GetFrames();
					for (int i = 0; i < frames.size(); ++i)
					{
						FChromaSDKColorFrame2D& frame = frames[i];
						if (duration >= 0.1f)
						{
							frame.Duration = duration;
						}
						else
						{
							frame.Duration = 0.1f;
						}
					}
				}
				break;
			}
			return animationId;
		}

		return -1;
	}

	EXPORT_API double PluginOverrideFrameDurationD(double animationId, double duration)
	{
		return (double)PluginOverrideFrameDuration((int)animationId, (float)duration);
	}

	EXPORT_API int PluginReverse(int animationId)
	{
		PluginStopAnimation(animationId);

		// Chroma thread plays animations
		SetupChromaThread();

		if (!PluginIsInitialized())
		{
			LogError("PluginReverse: Plugin is not initialized!\r\n");
			return -1;
		}

		if (_gAnimations.find(animationId) != _gAnimations.end())
		{
			AnimationBase* animation = _gAnimations[animationId];
			if (animation == nullptr)
			{
				LogError("PluginReverse: Animation is null! id=%d", animationId);
				return -1;
			}
			switch (animation->GetDeviceType())
			{
				case EChromaSDKDeviceTypeEnum::DE_1D:
				{
					Animation1D* animation1D = dynamic_cast<Animation1D*>(animation);
					vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
					vector<FChromaSDKColorFrame1D> copy = vector<FChromaSDKColorFrame1D>();
					for (int i = frames.size() - 1; i >= 0; --i)
					{
						FChromaSDKColorFrame1D& frame = frames[i];
						copy.push_back(frame);
					}
					frames.clear();
					for (int i = 0; i < copy.size(); ++i)
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
					for (int i = frames.size() - 1; i >= 0; --i)
					{
						FChromaSDKColorFrame2D& frame = frames[i];
						copy.push_back(frame);
					}
					frames.clear();
					for (int i = 0; i < copy.size(); ++i)
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

		// Chroma thread plays animations
		SetupChromaThread();

		if (!PluginIsInitialized())
		{
			LogError("PluginMirrorHorizontally: Plugin is not initialized!\r\n");
			return -1;
		}

		if (_gAnimations.find(animationId) != _gAnimations.end())
		{
			AnimationBase* animation = _gAnimations[animationId];
			if (animation == nullptr)
			{
				LogError("PluginMirrorHorizontally: Animation is null! id=%d", animationId);
				return -1;
			}
			switch (animation->GetDeviceType())
			{
				case EChromaSDKDeviceTypeEnum::DE_1D:
				{
					Animation1D* animation1D = dynamic_cast<Animation1D*>(animation);
					vector<FChromaSDKColorFrame1D>& frames = animation1D->GetFrames();
					int maxLeds = ChromaSDKPlugin::GetInstance()->GetMaxLeds(animation1D->GetDevice());
					for (int index = 0; index < frames.size(); ++index)
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
					for (int index = 0; index < frames.size(); ++index)
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

		// Chroma thread plays animations
		SetupChromaThread();

		if (!PluginIsInitialized())
		{
			LogError("PluginMirrorVertically: Plugin is not initialized!\r\n");
			return -1;
		}

		if (_gAnimations.find(animationId) != _gAnimations.end())
		{
			AnimationBase* animation = _gAnimations[animationId];
			if (animation == nullptr)
			{
				LogError("PluginMirrorVertically: Animation is null! id=%d", animationId);
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
					for (int index = 0; index < frames.size(); ++index)
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

	AnimationBase* GetAnimationInstance(int animationId)
	{
		if (_gAnimations.find(animationId) != _gAnimations.end())
		{
			return _gAnimations[animationId];
		}
		return nullptr;
	}

	EXPORT_API int PluginGetAnimation(const char* name)
	{
		for (std::map<string, int>::iterator it = _gAnimationMapID.begin(); it != _gAnimationMapID.end(); ++it)
		{
			const string& item = (*it).first;
			if (item.compare(name) == 0) {
				return (*it).second;
			}
		}
		return PluginOpenAnimation(name);
	}

	EXPORT_API double PluginGetAnimationD(const char* name)
	{
		return PluginGetAnimation(name);
	}

	EXPORT_API void PluginCloseAnimationName(const char* path)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginCloseAnimationName: Animation not found! %s", path);
			return;
		}
		PluginCloseAnimation(animationId);
	}

	EXPORT_API double PluginCloseAnimationNameD(const char* path)
	{
		PluginCloseAnimationName(path);
		return 0;
	}

	EXPORT_API void PluginPlayAnimationLoop(int animationId, bool loop)
	{
		if (_gAnimations.find(animationId) != _gAnimations.end())
		{
			AnimationBase* animation = _gAnimations[animationId];
			if (animation == nullptr)
			{
				LogError("PluginPlayAnimationLoop: Animation is null! id=%d\r\n", animationId);
				return;
			}
			PluginStopAnimationType(animation->GetDeviceType(), animation->GetDeviceId());
			LogDebug("PluginPlayAnimationLoop: %s\r\n", animation->GetName().c_str());
			switch (animation->GetDeviceType())
			{
			case EChromaSDKDeviceTypeEnum::DE_1D:
				_gPlayMap1D[(EChromaSDKDevice1DEnum)animation->GetDeviceId()] = animationId;
				break;
			case EChromaSDKDeviceTypeEnum::DE_2D:
				_gPlayMap2D[(EChromaSDKDevice2DEnum)animation->GetDeviceId()] = animationId;
				break;
			}
			animation->Play(loop);
		}
	}

	EXPORT_API void PluginPlayAnimationName(const char* path, bool loop)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginPlayAnimationName: Animation not found! %s", path);
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

	EXPORT_API void PluginStopAnimationName(const char* path)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginStopAnimationName: Animation not found! %s", path);
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
		switch ((EChromaSDKDeviceTypeEnum)deviceType)
		{
		case EChromaSDKDeviceTypeEnum::DE_1D:
			{
				if (_gPlayMap1D.find((EChromaSDKDevice1DEnum)device) != _gPlayMap1D.end())
				{
					int prevAnimation = _gPlayMap1D[(EChromaSDKDevice1DEnum)device];
					if (prevAnimation != -1)
					{
						PluginStopAnimation(prevAnimation);
						_gPlayMap1D[(EChromaSDKDevice1DEnum)device] = -1;
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
						PluginStopAnimation(prevAnimation);
						_gPlayMap2D[(EChromaSDKDevice2DEnum)device] = -1;
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
			LogError("PluginIsPlayingName: Animation not found! %s", path);
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

	EXPORT_API void PluginPlayComposite(const char* name, bool loop)
	{
		string baseName = name;
		PluginPlayAnimationName((baseName + "_ChromaLink.chroma").c_str(), loop);
		PluginPlayAnimationName((baseName + "_Headset.chroma").c_str(), loop);
		PluginPlayAnimationName((baseName + "_Keyboard.chroma").c_str(), loop);
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
				frameId < frames.size())
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
			LogError("PluginGetKeyColorName: Animation not found! %s", path);
			return 0;
		}
		return PluginGetKeyColor(animationId, frameId, rzkey);
	}

	EXPORT_API double PluginGetKeyColorD(const char* path, double frameId, double rzkey)
	{
		return (double)PluginGetKeyColorName(path, (int)frameId, (int)rzkey);
	}

	EXPORT_API void PluginSetKeyColor(int animationId, int frameId, int rzkey, int color)
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
				frameId < frames.size())
			{
				FChromaSDKColorFrame2D& frame = frames[frameId];
				frame.Colors[HIBYTE(rzkey)].Colors[LOBYTE(rzkey)] = color;
			}
		}
	}

	EXPORT_API void PluginSetKeyColorName(const char* path, int frameId, int rzkey, int color)
	{
		int animationId = PluginGetAnimation(path);
		if (animationId < 0)
		{
			LogError("PluginSetKeyColorName: Animation not found! %s", path);
			return;
		}
		PluginSetKeyColor(animationId, frameId, rzkey, color);
	}

	EXPORT_API double PluginSetKeyColorNameD(const char* path, double frameId, double rzkey, double color)
	{
		PluginSetKeyColorName(path, (int)frameId, (int)rzkey, (int)color);
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
		if (frameId < targetFrames.size())
		{
			FChromaSDKColorFrame2D& sourceFrame = sourceFrames[frameId % sourceFrames.size()];
			FChromaSDKColorFrame2D& targetFrame = targetFrames[frameId];
			targetFrame.Colors[HIBYTE(rzkey)].Colors[LOBYTE(rzkey)] = sourceFrame.Colors[HIBYTE(rzkey)].Colors[LOBYTE(rzkey)];
		}
	}

	EXPORT_API void PluginCopyKeyColorName(const char* sourceAnimation, const char* targetAnimation, int frameId, int rzkey)
	{
		int sourceAnimationId = PluginGetAnimation(sourceAnimation);
		if (sourceAnimationId < 0)
		{
			LogError("PluginCopyKeyColorName: Source Animation not found! %s", sourceAnimation);
			return;
		}

		int targetAnimationId = PluginGetAnimation(targetAnimation);
		if (targetAnimationId < 0)
		{
			LogError("PluginCopyKeyColorName: Target Animation not found! %s", targetAnimation);
			return;
		}

		PluginCopyKeyColor(sourceAnimationId, targetAnimationId, frameId, rzkey);
	}

	EXPORT_API double PluginCopyKeyColorNameD(const char* sourceAnimation, const char* targetAnimation, double frameId, double rzkey)
	{
		PluginCopyKeyColorName(sourceAnimation, targetAnimation, (int)frameId, (int)rzkey);
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
		if (frameId < targetFrames.size())
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
			LogError("PluginCopyNonZeroKeyColorName: Source Animation not found! %s", sourceAnimation);
			return;
		}

		int targetAnimationId = PluginGetAnimation(targetAnimation);
		if (targetAnimationId < 0)
		{
			LogError("PluginCopyNonZeroKeyColorName: Target Animation not found! %s", targetAnimation);
			return;
		}

		PluginCopyNonZeroKeyColor(sourceAnimationId, targetAnimationId, frameId, rzkey);
	}

	EXPORT_API double PluginCopyNonZeroKeyColorNameD(const char* sourceAnimation, const char* targetAnimation, double frameId, double rzkey)
	{
		PluginCopyNonZeroKeyColorName(sourceAnimation, targetAnimation, (int)frameId, (int)rzkey);
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
			LogError("PluginSetCurrentFrameName: Animation not found! %s", path);
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
			LogError("PluginPauseAnimationName: Animation not found! %s", path);
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
			LogError("PluginIsAnimationPausedName: Animation not found! %s", path);
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
			LogError("PluginHasAnimationLoopName: Animation not found! %s", path);
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
			LogError("PluginResumeAnimationName: Animation not found! %s", path);
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
}
