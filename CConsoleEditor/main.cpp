// CConsoleEditor.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "ChromaAnimationAPI.h"
#include "ChromaLogger.h"

#include <string>
#include <shellapi.h>


using namespace ChromaSDK;
using namespace std;

int Init()
{
	//ChromaLogger::fprintf(stdout, "Loaded Chroma Editor DLL!\r\n");
	if (ChromaAnimationAPI::InitAPI() != 0)
	{
		return -1;
	}

	return RZRESULT_SUCCESS;
}

#if _DEBUG
int main(int argc, char *argv[])
#else
int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR    lpCmdLine,
	int       nCmdShow)
#endif
{
	ChromaLogger::fprintf(stdout, "App launched!\r\n");

	RZRESULT result = Init();
	if (result != RZRESULT_SUCCESS)
	{
		return result;
	}	

	APPINFOTYPE appInfo = {};

	_tcscpy_s(appInfo.Title, 256, _T("Razer Chroma Editor"));
	_tcscpy_s(appInfo.Description, 1024, _T("Standalone Editor for Chroma"));
	_tcscpy_s(appInfo.Author.Name, 256, _T("Razer"));
	_tcscpy_s(appInfo.Author.Contact, 256, _T("https://developer.razer.com/chroma"));

	//appInfo.SupportedDevice = 
	//    0x01 | // Keyboards
	//    0x02 | // Mice
	//    0x04 | // Headset
	//    0x08 | // Mousepads
	//    0x10 | // Keypads
	//    0x20   // ChromaLink devices
	appInfo.SupportedDevice = (0x01 | 0x02 | 0x04 | 0x08 | 0x10 | 0x20);
	appInfo.Category = 1;

	result = ChromaAnimationAPI::CoreInitSDK(&appInfo);
 	if (result != RZRESULT_SUCCESS)
	{
		ChromaAnimationAPI::UninitAPI();
		ChromaLogger::fprintf(stderr, "Failed to initialize Chroma! %d", result);
		return result;
	}

	ChromaLogger::fprintf(stderr, "Initialized Chroma!\r\n");
	Sleep(100);

#if _DEBUG
	if (argc <= 1)
#else
	LPWSTR* szArgList;
	int argCount;
	szArgList = CommandLineToArgvW(GetCommandLine(), &argCount);
	if (argCount <= 1)
#endif
	{
		char* buffer = nullptr;
		size_t sz = 0;
		if (_dupenv_s(&buffer, &sz, "USERPROFILE") == 0
			&& buffer != nullptr)
		{
			//ChromaLogger::printf("EnvVarName = %s\n", buffer);
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
#if _DEBUG
		ChromaAnimationAPI::OpenEditorDialogAndPlay(argv[1]);
#else
		if (szArgList != NULL)
		{
			wstring ws = szArgList[1];
			string s(ws.begin(), ws.end());
			ChromaAnimationAPI::OpenEditorDialogAndPlay(s.c_str());
		}
#endif
	}

	while (ChromaAnimationAPI::IsDialogOpen())
	{
		Sleep(1);
	}

	ChromaAnimationAPI::Uninit();
	ChromaAnimationAPI::UninitAPI();
	ChromaLogger::printf("CConsoleEditor exited.\r\n");

    return RZRESULT_SUCCESS;
}
