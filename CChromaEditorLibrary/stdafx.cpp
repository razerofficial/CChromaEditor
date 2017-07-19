// stdafx.cpp : source file that includes just the standard includes
// CChromaEditorLibrary.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
#include "CChromaEditorLibrary.h"
#include <thread>

using namespace std;

bool _gDialogIsOpen = false;
char _gPath[256] = {0};

void ThreadOpenEditorDialog()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	// normal function body here

	printf_s("CChromaEditorLibrary::ThreadOpenEditorDialog %s\r\n", _gPath);

	// dialog instance
	CMainViewDlg mainViewDlg;

	// keep dialog focused
	mainViewDlg.DoModal();

	// dialog is closed
	_gDialogIsOpen = false;
}

extern "C"
{
	EXPORT_API double PluginIsDialogOpen()
	{
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
		printf("CChromaEditorLibrary::PluginOpenEditorDialog %s\r\n", path);

		if (_gDialogIsOpen)
		{
			return -1;
		}

		_gDialogIsOpen = true;
		sprintf_s(_gPath, "%s", path);
		thread newThread(ThreadOpenEditorDialog);
		newThread.detach();

		while (_gDialogIsOpen)
		{
			Sleep(0);
		}

		return 0;
	}
}
