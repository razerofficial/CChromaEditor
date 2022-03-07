#include "stdafx.h"
#include "ChromaLogger.h"

using namespace ChromaSDK;


void ChromaLogger::printf(const char* format, ...)
{
#if _DEBUG
	va_list args;
	va_start(args, format);
	::printf(format, args);
	va_end(args);
#endif
}

void ChromaLogger::fprintf(FILE* stream, const char* format, ...)
{
#if _DEBUG
	va_list args;
	va_start(args, format);
	::fprintf(stream, format, args);
	va_end(args);
#endif
}

void ChromaLogger::wprintf(const wchar_t* format, ...)
{
#if _DEBUG
	va_list args;
	va_start(args, format);
	::wprintf(format, args);
	va_end(args);
#endif
}

void ChromaLogger::fwprintf(FILE* stream, const wchar_t* format, ...)
{
#if _DEBUG
	va_list args;
	va_start(args, format);
	::fwprintf(stream, format, args);
	va_end(args);
#endif
}
