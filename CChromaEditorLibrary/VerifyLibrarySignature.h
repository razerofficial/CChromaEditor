#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <tchar.h>

typedef _TCHAR *PTCHAR;

namespace ChromaSDK
{
	class VerifyLibrarySignature
	{
	public:
		static BOOL VerifyModule(HMODULE hModule);
	private:
		static BOOL IsValidPath(PTCHAR szFileName);
		static BOOL IsFileSignedByRazer(PTCHAR szFileName);
		static BOOL IsFileSigned(PTCHAR szFileName);
	};
}
