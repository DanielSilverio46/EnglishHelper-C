/*
#ifndef __WIN32__
#error Not possible compile on this OS
#endif
*/
#include <windows.h>
#include <string.h>
#include <stdlib.h>

#include "headers/window_flow.h"


/*											 Change color									 *
 *									 according to hbrBackground	values				         *
 *		https://learn.microsoft.com/pt-br/windows/win32/api/winuser/ns-winuser-wndclassa     *
 *												   |										 *
 *												   V              							 */
#define MAIN_COLOR_BACKGROUND_WINDOW (HBRUSH)(COLOR_WINDOW + 1) 

HWND hwndWords = NULL;

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
	const char MAIN_CLASS[] = "main", WORDS_CLASS[] = "words";

	// Main Window
	WNDCLASS MainWindowClass = {};
	MainWindowClass.lpfnWndProc = MainProc;
	MainWindowClass.hInstance = hinstance;
	MainWindowClass.lpszClassName = MAIN_CLASS;
	MainWindowClass.hbrBackground = MAIN_COLOR_BACKGROUND_WINDOW;

	// Window to Modify, Set or Del Words
	WNDCLASS WordsWindowClass = {};
	WordsWindowClass.lpfnWndProc = FileControlProc;
	WordsWindowClass.hInstance = (HINSTANCE)0x0c;
	WordsWindowClass.lpszClassName = WORDS_CLASS;
	WordsWindowClass.hbrBackground = MAIN_COLOR_BACKGROUND_WINDOW;

	RegisterClass(&MainWindowClass);
	RegisterClass(&WordsWindowClass);
	

	HWND hwndMain = CreateWindowEx(
		0x00, MAIN_CLASS, "English Helper",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, MAIN_WINDOW_HEIGHT, MAIN_WINDOW_WIDTH,
		NULL, NULL, hinstance, NULL 
	);

	hwndWords = CreateWindowEx(
		0x00, WORDS_CLASS, "File Control",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, MAIN_WINDOW_HEIGHT, MAIN_WINDOW_WIDTH,
		hwndMain, NULL, (HINSTANCE)0x0c, NULL 
	);

	if (hwndMain == NULL || hwndWords == NULL)
		MessageBox(NULL, "Error on create the windows", NULL, MB_OK);

	ShowWindow(hwndMain, SW_SHOWNORMAL);

	MSG msg = {};
	while(GetMessage(&msg, NULL, 0x00, 0x00) > 0x00) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0x00;
};