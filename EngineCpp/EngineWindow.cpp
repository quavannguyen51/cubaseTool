#include "pch.h"

#include <windows.h>
#include <psapi.h>
#include <string>

static HWND g_cubaseHwnd = nullptr;

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM)
{
    DWORD pid;
    GetWindowThreadProcessId(hwnd, &pid);

    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
    if (!hProcess)
        return TRUE;

    wchar_t exeName[MAX_PATH];
    if (GetModuleBaseNameW(hProcess, NULL, exeName, MAX_PATH))
    {
        if (wcsstr(exeName, L"Cubase"))
        {
            g_cubaseHwnd = hwnd;
            CloseHandle(hProcess);
            return FALSE;
        }
    }

    CloseHandle(hProcess);
    return TRUE;
}

extern "C"
{
    __declspec(dllexport)
        HWND Engine_FindCubaseWindow()
    {
        g_cubaseHwnd = nullptr;
        EnumWindows(EnumWindowsProc, 0);
        return g_cubaseHwnd;
    }

    __declspec(dllexport)
        bool Engine_GetWindowRect(HWND hwnd, RECT* outRect)
    {
        if (!hwnd || !outRect)
            return false;

        return GetWindowRect(hwnd, outRect);
    }
}
