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

PLUGIN_IS_DIALOG_OPEN _gMethodIsDialogOpen = nullptr;
PLUGIN_OPEN_EDITOR_DIALOG _gMethodOpenDialog = nullptr;
PLUGIN_OPEN_ANIMATION _gMethodOpenAnimation = nullptr;
PLUGIN_PLAY_ANIMATION _gMethodPlayAnimation = nullptr;

int Init()
{
	HMODULE library = LoadLibrary(CHROMA_EDITOR_DLL);
	if (library == NULL)
	{
		fprintf(stderr, "Failed to load Chroma Editor Library!\r\n");
		return -1;
	}

	fprintf(stderr, "Loaded Chroma Editor DLL!\r\n");

	_gMethodIsDialogOpen = (PLUGIN_IS_DIALOG_OPEN)GetProcAddress(library, "PluginIsDialogOpenD");
	if (_gMethodIsDialogOpen == nullptr)
	{
		fprintf(stderr, "Failed to find method PluginIsDialogOpen!\r\n");
		return -1;
	}

	_gMethodOpenDialog = (PLUGIN_OPEN_EDITOR_DIALOG)GetProcAddress(library, "PluginOpenEditorDialogD");
	if (_gMethodOpenDialog == nullptr)
	{
		fprintf(stderr, "Failed to find method PluginOpenEditorDialog!\r\n");
		return -1;
	}

	_gMethodOpenAnimation = (PLUGIN_OPEN_ANIMATION)GetProcAddress(library, "PluginOpenAnimationD");
	if (_gMethodOpenAnimation == nullptr)
	{
		fprintf(stderr, "Failed to find method PluginOpenAnimation!\r\n");
		return -1;
	}

	_gMethodPlayAnimation = (PLUGIN_PLAY_ANIMATION)GetProcAddress(library, "PluginPlayAnimationD");
	if (_gMethodPlayAnimation == nullptr)
	{
		fprintf(stderr, "Failed to find method PluginPlayAnimation!\r\n");
		return -1;
	}

	fprintf(stderr, "Found DLL methods!\r\n");
	return 0;
}

int OpenAndPlay(const char* path)
{
	int animationId = _gMethodOpenAnimation(path);
	_gMethodPlayAnimation(animationId);
	return animationId;
}

int main(int argc, char *argv[])
{
	fprintf(stderr, "App launched!\r\n");
	if (Init() != 0)
	{
		return -1;
	}	

	if (argc <= 1)
	{
		if (false) // test editor
		{
			_gMethodOpenDialog("RandomChromaLinkEffect.chroma");
		}

		if (true) // test api
		{
			int keyboardCoolFireAnimation = OpenAndPlay("KeyboardParticleAnimation2.chroma");
			int randomChromaLinkEffect = OpenAndPlay("RandomChromaLinkEffect.chroma");
			int randomHeadsetEffect = OpenAndPlay("RandomHeadsetEffect.chroma");
			int randomKeypadEffect = OpenAndPlay("RandomKeypadEffect.chroma");
			int randomMouseEffect = OpenAndPlay("RandomMouseEffect.chroma");
			int randomMousepadEffect = OpenAndPlay("RandomMousepadEffect.chroma");

			this_thread::sleep_for(chrono::seconds(2));
		}
	}
	else
	{
		_gMethodOpenDialog(argv[1]);
	}

	while (_gMethodIsDialogOpen())
	{
		Sleep(0);
	}

	fprintf(stdout, "CConsoleEditor exited.\r\n");

    return 0;
}
