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

bool _gDialogIsOpen = false;
string _gPath = "";
int _gAnimationId = 0;
map<int, AnimationBase*> _gAnimations;

void SetupChromaThread()
{
	ChromaThread::Instance()->Start();
}

void ThreadOpenEditorDialog()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	// normal function body here

	//fprintf(stdout, "CChromaEditorLibrary::ThreadOpenEditorDialog %s\r\n", _gPath.c_str());

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
	EXPORT_API bool PluginIsDialogOpen()
	{
		// Chroma thread plays animations
		SetupChromaThread();

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
		// Chroma thread plays animations
		SetupChromaThread();

		//fprintf(stdout, "CChromaEditorLibrary::PluginOpenEditorDialog %s\r\n", path);

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

			//return animation id
			AnimationBase* animation = ChromaSDKPlugin::GetInstance()->OpenAnimation(path);
			int id = _gAnimationId;
			_gAnimations[id] = animation;
			++_gAnimationId;
			return id;
		}
		catch (exception)
		{
			fprintf(stderr, "PluginOpenAnimation: Exception path=%s\r\n", path);
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

			int id = (int)animationId;
			if (_gAnimations.find(id) != _gAnimations.end())
			{
				_gAnimations[id]->Load();
				return id;
			}
			return 0;
		}
		catch (exception)
		{
			fprintf(stderr, "PluginLoadAnimation: Exception animationId=%d\r\n", (int)animationId);
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

			int id = (int)animationId;
			if (_gAnimations.find(id) != _gAnimations.end())
			{
				_gAnimations[id]->Unload();
				return id;
			}
			return 0;
		}
		catch (exception)
		{
			fprintf(stderr, "PluginUnloadAnimation: Exception animationId=%d\r\n", (int)animationId);
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

			int id = (int)animationId;
			if (_gAnimations.find(id) != _gAnimations.end())
			{
				_gAnimations[id]->Play();
				return id;
			}
			return 0;
		}
		catch (exception)
		{
			fprintf(stderr, "PluginPlayAnimation: Exception animationId=%d\r\n", (int)animationId);
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

			int id = (int)animationId;
			if (_gAnimations.find(id) != _gAnimations.end())
			{
				_gAnimations[id]->Stop();
				return id;
			}
			return 0;
		}
		catch (exception)
		{
			fprintf(stderr, "PluginStopAnimation: Exception animationId=%d\r\n", (int)animationId);
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

			int id = (int)animationId;
			if (_gAnimations.find(id) != _gAnimations.end())
			{
				delete _gAnimations[id];
				_gAnimations.erase(animationId);
				return id;
			}
			return 0;
		}
		catch (exception)
		{
			fprintf(stderr, "PluginCloseAnimation: Exception animationId=%d\r\n", (int)animationId);
			return -1;
		}
	}

	EXPORT_API double PluginCloseAnimationD(double animationId)
	{
		return (double)PluginCloseAnimation((int)animationId);
	}
}
