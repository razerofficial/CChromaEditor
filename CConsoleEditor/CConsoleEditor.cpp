// CConsoleEditor.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "ChromaAnimationAPI.h"
#include "UnitTests.h"
#include <string>


using namespace ChromaSDK;
using namespace std;

#define TARGET_RESOLUTION  1

static MMRESULT _sTimerResult = TIMERR_NOCANDO;

int Init()
{
	//fprintf(stderr, "Loaded Chroma Editor DLL!\r\n");
	if (ChromaAnimationAPI::InitAPI() != 0)
	{
		return -1;
	}

	return 0;
}

int SafeReturn(int val)
{
	if (_sTimerResult == TIMERR_NOERROR)
	{
		timeEndPeriod(TARGET_RESOLUTION);
		fprintf(stdout, "Timer: [UNSET]\r\n");
	}
	return val;
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
	fprintf(stderr, "App launched!\r\n");

	
	// ref: https://docs.microsoft.com/en-us/windows/win32/multimedia/obtaining-and-setting-timer-resolution
	TIMECAPS tc;
	UINT     wTimerRes;
	if (timeGetDevCaps(&tc, sizeof(TIMECAPS)) == TIMERR_NOERROR)
	{
		wTimerRes = min(max(tc.wPeriodMin, TARGET_RESOLUTION), tc.wPeriodMax);

		//ref: https://docs.microsoft.com/en-us/windows/win32/api/timeapi/nf-timeapi-timebeginperiod
		_sTimerResult = timeBeginPeriod(wTimerRes);
		if (_sTimerResult != TIMERR_NOERROR)
		{
			fprintf(stderr, "Failed to set timer!\r\n");
		}
		else
		{
			fprintf(stdout, "Timer: [SET]\r\n");
		}
	}


	if (Init() != 0)
	{
		return SafeReturn(-1);
	}	

#if _DEBUG && RUN_UNIT_TESTS
	UnitTests::Run();
#else

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

	RZRESULT result = ChromaAnimationAPI::InitSDK(&appInfo);
	if (result != RZRESULT_SUCCESS)
	{
		fprintf(stderr, "Failed to initialize Chroma! %d", result);
		return SafeReturn(-1);
	}

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
		Sleep(0);
	}

#endif

	ChromaAnimationAPI::Uninit();
	fprintf(stdout, "CConsoleEditor exited.\r\n");

    return SafeReturn(0);
}
