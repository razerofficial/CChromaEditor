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
	EXPORT_API double PluginIsDialogOpen()
	{
		// Chroma thread plays animations
		SetupChromaThread();

		if (_gDialogIsOpen)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}

	EXPORT_API double PluginOpenEditorDialog(char* path)
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

	EXPORT_API double PluginOpenAnimation(char* path)
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

	EXPORT_API double PluginLoadAnimation(double animationId)
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

	EXPORT_API double PluginUnloadAnimation(double animationId)
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

	EXPORT_API double PluginPlayAnimation(double animationId)
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

	EXPORT_API double PluginStopAnimation(double animationId)
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

	EXPORT_API double PluginCloseAnimation(double animationId)
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
}
