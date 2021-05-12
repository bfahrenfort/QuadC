#include "dialog.h"
#include <windows.h>
#include "resource.h"
#include "quirk.hpp"

using namespace QuirkUtils;

Quirk quirk;

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch(Message)
	{
		case WM_CREATE:
		{
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
                case IDM_LOAD_QUIRK:
                {
                    OPENFILENAME ofn;
                    char szFileName[MAX_PATH] = "";

                    ZeroMemory(&ofn, sizeof(ofn));

                    ofn.lStructSize = sizeof(ofn); // SEE NOTE BELOW
                    ofn.hwndOwner = hwnd;
                    ofn.lpstrFilter = "Quirkfiles (*.qrk)\0*.qrk\0";
                    ofn.lpstrFile = szFileName;
                    ofn.nMaxFile = MAX_PATH;
                    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
                    ofn.lpstrDefExt = "txt";

                    if(GetOpenFileName(&ofn))
                    {
                        int success = CheckFile(szFileName, quirk);
                        if(success == 0)
                        {
                            MessageBox(hwnd, "Quirk successfully loaded!", "Load Quirk", 0);
                        }
                    }
                }
                break;
                case IDM_NEW_QUIRK:
                {
                    int result = DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCE(IDD_QUIRK_CREATE), hwnd, QrkProc);
                    if(result == IDC_QUIRK_SAVE)
                    {
                        MessageBox(hwnd, "Save button pressed!", "Save Quirk", 0);
                    }
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

BOOL CALLBACK QrkProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    switch(Message)
    {
        case WM_INITDIALOG:

        return TRUE;
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case IDC_ROLPLY:
                {
                    int state = SendDlgItemMessage(hwnd, IDC_ROLPLY, BM_GETCHECK, 0, 0);
                    EnableWindow(GetDlgItem(hwnd, IDC_STATIC_PREFIX), state);
                    EnableWindow(GetDlgItem(hwnd, IDC_PREFIX), state);
                }
                break;
                case IDC_QUIRK_SAVE:
                {
                    // Check all the fields and load into quirk
                    EndDialog(hwnd, IDC_QUIRK_SAVE);
                }
                break;
            }
        break;
        case WM_CLOSE:
        {
            EndDialog(hwnd, 0);
        }
		break;
	    case WM_DESTROY:
	        EndDialog(hwnd, 0);
		break;
        default:
            return FALSE;
    }
    return TRUE;
}
