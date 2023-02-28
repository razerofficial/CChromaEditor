#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <string>

namespace ChromaSDK
{
	class VerifyLibrarySignature
	{
	public:
		static BOOL VerifyModule(const std::wstring& filename);
		static BOOL IsFileVersionSameOrNewer(const std::wstring& filename, const int minMajor, const int minMinor, const int minRevision, const int minBuild);
	private:
		static BOOL IsFileSignedByRazer(const wchar_t* szFileName);
		static BOOL IsFileSigned(const wchar_t* szFileName);
	};
}
