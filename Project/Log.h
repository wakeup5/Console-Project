#pragma once
#include <Windows.h>
#include <stdio.h>

void LogToOutputW(const TCHAR* szFormat, ...);
void LogToOutputA(const CHAR* szFormat, ...);