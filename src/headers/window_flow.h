#ifndef GFUNC_H
#define GFUNC_H

#include <windows.h>
#include <commctrl.h>
#include <stdint.h>

#define MAIN_WINDOW_HEIGHT 0x190
#define MAIN_WINDOW_WIDTH 0x190

#define TEXT_BOX_WINDOW_WIDTH 0xC8
#define TEXT_BOX_WINDOW_HEIGHT 0x14

#define BUTTON_WINDOW_WIDTH 0x32
#define BUTTON_WINDOW_HEIGHT 0x19

__declspec(dllexport) extern LRESULT CALLBACK MainProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
__declspec(dllexport) extern LRESULT CALLBACK FileControlProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

__declspec(dllexport) extern LRESULT CALLBACK WordsSpecialActionsProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);
__declspec(dllexport) extern LRESULT CALLBACK KeyEnterProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData, HWND HwndMain);

__declspec(dllexport) extern void GetWND_Of_HWND(HWND hwnd, WNDCLASS *wnd);
__declspec(dllexport) extern void DrawPointsUser(HDC hdc, RECT *rect, int points, int fails);

#endif