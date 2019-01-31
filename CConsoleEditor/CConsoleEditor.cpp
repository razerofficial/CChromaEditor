// CConsoleEditor.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "ChromaAnimationAPI.h"
#include "UnitTests.h"


using namespace ChromaSDK;

int Init()
{
	//fprintf(stderr, "Loaded Chroma Editor DLL!\r\n");
	if (ChromaAnimationAPI::InitAPI() != 0)
	{
		return -1;
	}

	return 0;
}

int main(int argc, char *argv[])
{
	//fprintf(stderr, "App launched!\r\n");
	if (Init() != 0)
	{
		return -1;
	}	

#if RUN_UNIT_TESTS
	UnitTests::Run();
#endif

	if (argc <= 1)
	{
		char* buffer = nullptr;
		size_t sz = 0;
		if (_dupenv_s(&buffer, &sz, "USERPROFILE") == 0
			&& buffer != nullptr)
		{
			//fprintf(stdout, "EnvVarName = %s\n", buffer);
			char path[256] = { 0 };
			sprintf_s(path, "%s\\Desktop\\temp.chroma", buffer);		
			free(buffer);
			ChromaAnimationAPI::OpenEditorDialogAndPlay(path);
		}
		else
		{
			ChromaAnimationAPI::OpenEditorDialogAndPlay("temp.chroma");
		}
	}
	else
	{
		ChromaAnimationAPI::OpenEditorDialogAndPlay(argv[1]);
	}

	while (ChromaAnimationAPI::IsDialogOpen())
	{
		Sleep(0);
	}

	ChromaAnimationAPI::Uninit();
	fprintf(stdout, "CConsoleEditor exited.\r\n");

    return 0;
}
