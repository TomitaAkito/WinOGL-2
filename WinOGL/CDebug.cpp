#include "pch.h"
#include "CDebug.h"


void CDebug::printf_ex(LPCTSTR pszFormat, ...) {
    va_list	argp;
    TCHAR pszBuf[256];
    va_start(argp, pszFormat);
    _vstprintf(pszBuf, sizeof(pszBuf), pszFormat, argp);
    va_end(argp);
    OutputDebugString(pszBuf);
}
