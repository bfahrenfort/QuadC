//
// Created by b on 5/9/2021.
//
#include <windows.h>

#ifndef QUIRKTYPER_DIALOG_H
#define QUIRKTYPER_DIALOG_H

#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);

BOOL CALLBACK QrkProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);

#ifdef __cplusplus
}
#endif //__cplusplus

#endif //QUIRKTYPER_DIALOG_H
