#include <windows.h>
#include <stdio.h>
#include "cmd_line.h"
#include "dialog.h"
#include "resource.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
    //int argc = 0;
    //LPCWSTR args = GetCommandLineW();
    //WCHAR **argv = CommandLineToArgvW(args, &argc);
	// TODO: add some way for a cmdline opportunity with no-arg (-nowindow?)
    if(__argc > 1)
    {
        CmdLine(__argc, __argv);
    }
    else
        return DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAIN), NULL, DlgProc);
}
