#include "log.h"

void CreateConsoleLog(void)
{
    AllocConsole();

    FILE *StdoutConLog, *StderrConLog;

    freopen_s(&StdoutConLog, "CONOUT$", "w", stdout);
    freopen_s(&StderrConLog, "CONOUT$", "w", stderr);
}