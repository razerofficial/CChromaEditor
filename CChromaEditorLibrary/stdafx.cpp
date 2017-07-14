// stdafx.cpp : source file that includes just the standard includes
// CChromaEditorLibrary.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
#include "CChromaEditorLibrary.h"

extern "C"
{
	EXPORT_API void PluginOpenEditorDialog(char* path)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		// normal function body here

		printf("CChromaEditorLibrary::PluginOpenEditorDialog %s\r\n", path);

		// dialog instance
		CMainViewDlg mainViewDlg;

		// keep dialog focused
		mainViewDlg.DoModal();
	}
}
