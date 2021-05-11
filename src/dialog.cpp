#include "dialog.h"
#include <windows.h>
#include "resource.h"
#include "quirk.hpp"

BOOL CALLBACK DlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch(Message)
	{
		case WM_INITDIALOG:
		break;
		case WM_COMMAND:
			switch(LOWORD(wParam))
            {
            }
		    break;
		case WM_CLOSE:
        {
            EndDialog(hwnd, 0);
            PostQuitMessage(0);
        }
		break;
	    case WM_DESTROY:
	        PostQuitMessage(0);
		break;
		default:
			return FALSE;
	}
	return TRUE;
}
