#include "Log.h"

void LogToOutputW(const WCHAR* szFormat, ...) 
{
    TCHAR szBuff[1024];
    va_list arg;
    va_start(arg, szFormat);
    _vsnwprintf_s(szBuff, sizeof(szBuff), szFormat, arg);
    va_end(arg);

    OutputDebugStringW(szBuff);
}

void LogToOutputA(const CHAR* szFormat, ...)
{
    CHAR szBuff[1024];
    va_list arg;
    va_start(arg, szFormat);
    _vsnprintf_s(szBuff, sizeof(szBuff), szFormat, arg);
    va_end(arg);

    OutputDebugStringA(szBuff);
}