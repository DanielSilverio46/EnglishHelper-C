#ifndef LOG
#define LOG

#include <windows.h>
#include <stdio.h>

void CreateConsoleLog(void);

#define CloseConsoleLog() FreeConsole()

#endif