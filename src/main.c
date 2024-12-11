#include "headers/main.h"
#include "headers/window_flow.h"
#include "headers/word.h"

#define IDI_APP_ICON 101

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
	if (loadWordFile() == false) createWordFile();

	const char MAIN_CLASS[] = "main", WORDS_CLASS[] = "words";

	// Main Window
	WNDCLASS MainWindowClass = {};
	MainWindowClass.lpfnWndProc = MainProc;
	MainWindowClass.hInstance = hinstance;
	MainWindowClass.lpszClassName = MAIN_CLASS;
	MainWindowClass.hbrBackground = MAIN_COLOR_BACKGROUND_WINDOW;
	MainWindowClass.hIcon = LoadIcon(hinstance, MAKEINTRESOURCE(IDI_APP_ICON));

	WNDCLASS WordsWindowClass = {};
	WordsWindowClass.lpfnWndProc = WordsProc;
	WordsWindowClass.hInstance = hinstance;
	WordsWindowClass.lpszClassName = WORDS_CLASS;
	WordsWindowClass.hbrBackground = MAIN_COLOR_BACKGROUND_WINDOW;

	RegisterClass(&MainWindowClass);
	RegisterClass(&WordsWindowClass);

	HWND hwnd_main = CreateWindowEx(
		0x00, MAIN_CLASS, "English Helper",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, MAIN_WINDOW_HEIGHT, MAIN_WINDOW_WIDTH,
		NULL, NULL, hinstance, NULL 
	);

	HWND hwnd_words = CreateWindowEx(
		0x00, WORDS_CLASS, "Words",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, MAIN_WINDOW_HEIGHT, MAIN_WINDOW_WIDTH,
		NULL, NULL, hinstance, NULL
	);

	if (hwnd_main == NULL || hwnd_words == NULL)
	{
		MessageBox(NULL, "Not possible load windows", NULL, MB_OK | MB_ICONHAND);
		return 0x00;
	}

	ShowWindow(hwnd_main, SHOW_OPENWINDOW);
	ShowWindow(hwnd_words, SW_HIDE);

	MSG msg = {};

	while(GetMessage(&msg, NULL, 0x00, 0x00) > 0x00) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0x00;
};