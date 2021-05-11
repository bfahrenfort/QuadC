#include <windows.h>
#include <stdio.h>
#include "cmd_line.h"
#include "dialog.h"
#include "resource.h"

// GNU C compiler does not check for insecure C functions, but my clang-cl and several others like msvc do
#ifndef __GNUC__
#define _CRT_SECURE_NO_WARNINGS
#endif //__GNUC__

#define MAX_LOADSTRING 100

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
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
        WNDCLASSEX wndclass;

        char szWindowClass[MAX_LOADSTRING];
        LoadString(hInstance, IDS_WINDOW_CLASS, szWindowClass, MAX_LOADSTRING);

        wndclass.cbSize = sizeof(WNDCLASSEX);
        wndclass.style = CS_HREDRAW | CS_VREDRAW;
        wndclass.lpfnWndProc = WndProc;
        wndclass.cbClsExtra = 0;
        wndclass.cbWndExtra = DLGWINDOWEXTRA;
        wndclass.hInstance = hInstance;
        wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAIN));
        wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAIN));
        wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
        wndclass.hbrBackground = (HBRUSH) (COLOR_BTNFACE + 1);
        wndclass.lpszMenuName = MAKEINTRESOURCE(IDM_MAINMENU);
        wndclass.lpszClassName = szWindowClass;

        RegisterClassEx(&wndclass);

        hwnd = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_MAIN), 0, NULL);

        ShowWindow(hwnd, nCmdShow);

        while (GetMessage(&msg, NULL, 0, 0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        return msg.wParam;
    }
}
