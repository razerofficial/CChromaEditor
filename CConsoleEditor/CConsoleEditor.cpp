// CConsoleEditor.cpp : Defines the entry point for the console application.
//

#define CHROMA_EDITOR_DLL _T("CChromaEditorLibrary.dll")

#include "stdafx.h"
#include <Windows.h>

typedef void(*PLUGIN_OPEN_EDITOR_DIALOG)(const char* path);

int main()
{
	HMODULE library = LoadLibrary(CHROMA_EDITOR_DLL);
	if (library == NULL)
	{
		printf("Failed to load Chroma Editor Library!\r\n");
		return -1;
	}

	PLUGIN_OPEN_EDITOR_DIALOG methodOpenDialog = (PLUGIN_OPEN_EDITOR_DIALOG)GetProcAddress(library, "PluginOpenEditorDialog");
	if (methodOpenDialog == nullptr)
	{
		printf("Failed to find method PluginOpenEditorDialog!\r\n");
		return -1;
	}

	methodOpenDialog("Some path");

	printf("CConsoleEditor exited.\r\n");

    return 0;
}
