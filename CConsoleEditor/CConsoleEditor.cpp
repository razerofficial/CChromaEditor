// CConsoleEditor.cpp : Defines the entry point for the console application.
//

#define CHROMA_EDITOR_DLL _T("CChromaEditorLibrary.dll")

#include "stdafx.h"
#include <chrono>
#include <thread>
#include <Windows.h>

typedef double(*PLUGIN_IS_DIALOG_OPEN)();
typedef double(*PLUGIN_OPEN_EDITOR_DIALOG)(const char* path);
typedef double(*PLUGIN_OPEN_ANIMATION)(const char* path);
typedef double(*PLUGIN_PLAY_ANIMATION)(double animationId);

using namespace std;
using namespace std::chrono;

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

	PLUGIN_OPEN_ANIMATION methodOpenAnimation = (PLUGIN_OPEN_ANIMATION)GetProcAddress(library, "PluginOpenAnimation");
	if (methodOpenAnimation == nullptr)
	{
		fprintf(stderr, "Failed to find method PluginOpenAnimation!\r\n");
		return -1;
	}

	PLUGIN_PLAY_ANIMATION methodPlayAnimation = (PLUGIN_PLAY_ANIMATION)GetProcAddress(library, "PluginPlayAnimation");
	if (methodPlayAnimation == nullptr)
	{
		fprintf(stderr, "Failed to find method PluginPlayAnimation!\r\n");
		return -1;
	}

	if (argc <= 1)
	{
		if (true) // test editor
		{
			//methodOpenDialog("KeyboardEffect.chroma");
			//methodOpenDialog("C:\\Public\\UnityChromaSwagger\\Assets\\ChromaSDK\\Examples\\Animations\\RandomChromaLinkEffect.chroma"); 
			methodOpenDialog("C:\\Public\\UnityChromaSwagger\\Assets\\ChromaSDK\\Examples\\Animations\\KeyboardParticleAnimation2.chroma");
		}

		if (false) // test api
		{
			int animationId = methodOpenAnimation("KeyboardEffect.chroma");
			//int animationId = methodOpenAnimation("C:\\Public\\UnityChromaSwagger\\Assets\\ChromaSDK\\Examples\\Animations\\KeyboardParticleAnimation2.chroma");
			methodPlayAnimation(animationId);

			this_thread::sleep_for(chrono::seconds(1));
		}
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
