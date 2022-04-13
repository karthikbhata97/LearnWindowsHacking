// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

#include <iostream>
#include <fstream>

/* Global log file, because we can't print out from a DLL loaded inside another program.
 */
const std::wstring gLogFilename = L"C:\\Users\\WolfgangRichter\\OneDrive - Soroco India Private Limited\\Desktop\\src-dll-injection.log";
std::wofstream gLogFile(gLogFilename);

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        gLogFile << L"DllMain: DLL_PROCESS_ATTACH" << std::endl;
        gLogFile << L"\tPID: " << GetCurrentProcessId() << std::endl;
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

