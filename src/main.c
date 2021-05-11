#include <windows.h>
#include <stdio.h>
#include "cmd_line.h"
#include "dialog.h"
#include "resource.h"

#ifndef __GNUC__
#define _CRT_SECURE_NO_WARNINGS
#endif //__GNUC__

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
    if(__argc > 1)
    {
        // Attach to the console
        AttachConsole(ATTACH_PARENT_PROCESS);

        freopen("CONIN$", "r", stdin);
        freopen("CONOUT$", "w", stdout);
        freopen("CONERR$", "w", stderr);

        CmdLine(__argc, __argv);
    }
    else
    {
        HWND hwnd;
        MSG msg;

        hwnd = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_MAIN), 0, DlgProc);
        ShowWindow(hwnd, nCmdShow);
        UpdateWindow(hwnd);

        while (GetMessage(&msg, NULL, 0, 0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        return msg.wParam;
    }
}
