// CConsoleEditor.cpp : Defines the entry point for the console application.
//

#define CHROMA_EDITOR_DLL _T("CChromaEditorLibrary.dll")

#include "stdafx.h"
#include <Windows.h>

typedef double(*PLUGIN_IS_DIALOG_OPEN)();
typedef double(*PLUGIN_OPEN_EDITOR_DIALOG)(const char* path);

int main(int argc, char *argv[])
{
	HMODULE library = LoadLibrary(CHROMA_EDITOR_DLL);
	if (library == NULL)
	{
		fprintf(stderr, "Failed to load Chroma Editor Library!\r\n");
		return -1;
	}

	PLUGIN_IS_DIALOG_OPEN methodIsDialogOpen = (PLUGIN_IS_DIALOG_OPEN)GetProcAddress(library, "PluginIsDialogOpen");
	if (methodIsDialogOpen == nullptr)
	{
		fprintf(stderr, "Failed to find method PluginIsDialogOpen!\r\n");
		return -1;
	}

	PLUGIN_OPEN_EDITOR_DIALOG methodOpenDialog = (PLUGIN_OPEN_EDITOR_DIALOG)GetProcAddress(library, "PluginOpenEditorDialog");
	if (methodOpenDialog == nullptr)
	{
		fprintf(stderr, "Failed to find method PluginOpenEditorDialog!\r\n");
		return -1;
	}

	if (argc <= 1)
	{
		//methodOpenDialog("KeyboardEffect.chroma");
		methodOpenDialog("C:\\Public\\UnityChromaSwagger\\Assets\\ChromaSDK\\Examples\\Animations\\KeyboardParticleAnimation.chroma");
	}
	else
	{
		methodOpenDialog(argv[1]);
	}

	while (methodIsDialogOpen())
	{
		Sleep(0);
	}

	fprintf(stdout, "CConsoleEditor exited.\r\n");

    return 0;
}
