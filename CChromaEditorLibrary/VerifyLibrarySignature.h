#pragma once

#include <Windows.h>

namespace ChromaSDK
{
	BOOL VerifyLibrarySignature(const TCHAR* szModuleName, HMODULE hModule);
}
