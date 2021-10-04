#include "ChromaLogger.h"
#include "ChromaAnimationAPI.h"
#include "UnitTests.h"

#include <tchar.h>

using namespace ChromaSDK;
using namespace std;

int Init()
{
	//ChromaLogger::fprintf(stderr, "Loaded Chroma Editor DLL!\r\n");
	if (ChromaAnimationAPI::InitAPI() != 0)
	{
		return -1;
	}

	return RZRESULT_SUCCESS;
}

int main()
{
	ChromaLogger::fprintf(stderr, "App launched!\r\n");

	RZRESULT result = Init();
	if (result != RZRESULT_SUCCESS)
	{
		return result;
	}

	APPINFOTYPE appInfo = {};

	_tcscpy_s(appInfo.Title, 256, _T("C++ Chroma Editor - Unit Tests"));
	_tcscpy_s(appInfo.Description, 1024, _T("Unit Tests for Chroma"));
	_tcscpy_s(appInfo.Author.Name, 256, _T("Razer"));
	_tcscpy_s(appInfo.Author.Contact, 256, _T("https://github.com/RazerOfficial/CChromaEditor"));

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
		ChromaLogger::fprintf(stderr, "Failed to initialize Chroma! %d", result);
		return result;
	}

	UnitTests::Run();

	ChromaAnimationAPI::Uninit();
	ChromaLogger::printf("Cpp_UnitTests exited.\r\n");

	return 0;
}
