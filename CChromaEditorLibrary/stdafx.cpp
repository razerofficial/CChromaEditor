// stdafx.cpp : source file that includes just the standard includes
// CChromaEditorLibrary.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
#include "CChromaEditorLibrary.h"
#include "ChromaThread.h"
#include <map>
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
map<int, AnimationBase*> _gAnimations;

void SetupChromaThread()
{
	ChromaThread::Instance()->Start();
}

void StopChromaThread()
{
	ChromaThread::Instance()->Stop();
}

void ThreadOpenEditorDialog()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	// normal function body here

	//LogError("CChromaEditorLibrary::ThreadOpenEditorDialog %s\r\n", _gPath.c_str());

	// dialog instance
	CMainViewDlg mainViewDlg;

	mainViewDlg.OpenOrCreateAnimation(_gPath);

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

	EXPORT_API int PluginOpenEditorDialog(char* path)
	{
		//LogError("CChromaEditorLibrary::PluginOpenEditorDialog %s\r\n", path);

		if (_gDialogIsOpen)
		{
			return -1;
		}

		_gDialogIsOpen = true;
		_gPath = path;
		thread newThread(ThreadOpenEditorDialog);
		newThread.detach();

		return 0;
	}

	EXPORT_API double PluginOpenEditorDialogD(char* path)
	{
		return PluginOpenEditorDialog(path);
	}

	EXPORT_API int PluginOpenAnimation(char* path)
	{
		try
		{
			// Chroma thread plays animations
			SetupChromaThread();

			if (!PluginIsInitialized())
			{
				LogError("PluginOpenAnimation: Plugin is not initialized!");
				return -1;
			}

			//return animation id
			AnimationBase* animation = ChromaSDKPlugin::GetInstance()->OpenAnimation(path);
			if (animation == nullptr)
			{
				LogError("PluginOpenAnimation: Animation is null!");
				return -1;
			}
			else
			{
				int id = _gAnimationId;
				_gAnimations[id] = animation;
				++_gAnimationId;
				return id;
			}
		}
		catch (exception)
		{
			LogError("PluginOpenAnimation: Exception path=%s\r\n", path);
			return -1;
		}
	}

	EXPORT_API double PluginOpenAnimationD(char* path)
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
				LogError("PluginLoadAnimation: Plugin is not initialized!");
				return -1;
			}

			if (_gAnimations.find(animationId) != _gAnimations.end())
			{
				AnimationBase* animation = _gAnimations[animationId];
				if (animation == nullptr)
				{
					LogError("PluginLoadAnimation: Animation is null!");
					return -1;
				}
				animation->Load();
				return animationId;
			}
			return 0;
		}
		catch (exception)
		{
			LogError("PluginLoadAnimation: Exception animationId=%d\r\n", (int)animationId);
			return -1;
		}
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
				LogError("PluginUnloadAnimation: Plugin is not initialized!");
				return -1;
			}

			if (_gAnimations.find(animationId) != _gAnimations.end())
			{
				AnimationBase* animation = _gAnimations[animationId];
				if (animation == nullptr)
				{
					LogError("PluginUnloadAnimation: Animation is null!");
					return -1;
				}
				animation->Unload();
				return animationId;
			}
			return 0;
		}
		catch (exception)
		{
			LogError("PluginUnloadAnimation: Exception animationId=%d\r\n", (int)animationId);
			return -1;
		}
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
				LogError("PluginPlayAnimation: Plugin is not initialized!");
				return -1;
			}

			if (_gAnimations.find(animationId) != _gAnimations.end())
			{
				AnimationBase* animation = _gAnimations[animationId];
				if (animation == nullptr)
				{
					LogError("PluginPlayAnimation: Animation is null!");
					return -1;
				}
				animation->Play();
				return animationId;
			}
			return 0;
		}
		catch (exception)
		{
			LogError("PluginPlayAnimation: Exception animationId=%d\r\n", (int)animationId);
			return -1;
		}
	}

	EXPORT_API double PluginPlayAnimationD(double animationId)
	{
		return (double)PluginPlayAnimation((int)animationId);
	}

	EXPORT_API int PluginStopAnimation(int animationId)
	{
		try
		{
			// Chroma thread plays animations
			SetupChromaThread();

			if (!PluginIsInitialized())
			{
				LogError("PluginStopAnimation: Plugin is not initialized!");
				return -1;
			}

			if (_gAnimations.find(animationId) != _gAnimations.end())
			{
				AnimationBase* animation = _gAnimations[animationId];
				if (animation == nullptr)
				{
					LogError("PluginStopAnimation: Animation is null!");
					return -1;
				}
				animation->Stop();
				return animationId;
			}
			return 0;
		}
		catch (exception)
		{
			LogError("PluginStopAnimation: Exception animationId=%d\r\n", (int)animationId);
			return -1;
		}
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
				LogError("PluginCloseAnimation: Plugin is not initialized!");
				return -1;
			}

			if (_gAnimations.find(animationId) != _gAnimations.end())
			{
				AnimationBase* animation = _gAnimations[animationId];
				if (animation == nullptr)
				{
					LogError("PluginCloseAnimation: Animation is null!");
					return -1;
				}
				animation->Stop();
				delete _gAnimations[animationId];
				_gAnimations.erase(animationId);
				return animationId;
			}
			return 0;
		}
		catch (exception)
		{
			LogError("PluginCloseAnimation: Exception animationId=%d\r\n", (int)animationId);
			return -1;
		}
	}

	EXPORT_API double PluginCloseAnimationD(double animationId)
	{
		return (double)PluginCloseAnimation((int)animationId);
	}

	EXPORT_API int PluginInit()
	{
		// Chroma thread plays animations
		SetupChromaThread();

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
		_gAnimations.clear();
		_gAnimationId = 0;
		return result;
	}

	EXPORT_API double PluginUninitD()
	{
		return (double)PluginUninit();
	}
}
