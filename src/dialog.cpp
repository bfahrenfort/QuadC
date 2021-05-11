#include "dialog.h"
#include <windows.h>
#include "resource.h"
#include "quirk.hpp"

BOOL CALLBACK DlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    HINSTANCE hInst;

	switch(Message)
	{
		case WM_INITDIALOG:
		{
		    // Get my HINSTANCE
		    hInst = GetModuleHandle(nullptr);

		    // Give the dialog a menu
		    HMENU menu = LoadMenu(hInst, MAKEINTRESOURCE(IDM_MAINMENU));
            SetMenu(hwnd, menu);

            // Set its icon in the top left corner
            auto hIcon = (HICON) LoadImage(hInst,
                                            MAKEINTRESOURCE(IDI_MAIN),
                                            IMAGE_ICON,
                                            GetSystemMetrics(SM_CXSMICON),
                                            GetSystemMetrics(SM_CYSMICON),
                                            0);
            SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM) hIcon);
		}
		break;
		case WM_COMMAND:
        {
            switch(LOWORD(wParam))
            {
                case IDM_ABOUT:
                {
                    MessageBox(hwnd, "THIS IS STUPID.", "About", 0);
                }
                break;
                case IDM_EXIT:
                {
                    EndDialog(hwnd, 0);
                    PostQuitMessage(0);
                }
                break;
            }
        }
        break;
		case WM_CLOSE
        {
            EndDialog(hwnd, 0);
            PostQuitMessage(0);
        }
		break;
	    case WM_DESTROY:
	        EndDialog(hwnd, 0);
	        PostQuitMessage(0);
		break;
		default:
			return FALSE;
	}
	return TRUE;
}
