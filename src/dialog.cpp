#include "dialog.h"
#include <windows.h>
#include "resource.h"
#include "quirk.hpp"

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    HINSTANCE hInst;

	switch(Message)
	{
		case WM_CREATE:
		{
		    // Get my HINSTANCE for later use
		    hInst = GetModuleHandle(nullptr);
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
                    PostQuitMessage(0);
                }
                break;
                default:
                    return DefWindowProc(hwnd, Message, wParam, lParam);
            }
        }
        break;
	    case WM_CLOSE:
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
            return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return TRUE;
}
