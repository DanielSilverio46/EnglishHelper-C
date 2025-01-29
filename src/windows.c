#include "windows.h"
#include "window_flow.h"
#include "word.h"
#include "user.h"
#include "log.h"

#define IDI_APP_ICON 0x65

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
	/*
	char *params[0x5];

	for(unsigned int i = 0, count_split = 0; i != strlen(pCmdLine); ++i)
	{
		if (pCmdLine[i] == ' ')
		{
			pCmdLine[i] = '\0';
			params[count_split] = &pCmdLine[i];
			count_split++;
		}
	}
	*/

	CreateConsoleLog();

	printf("%s, %d\n\n", pCmdLine, nCmdShow);
	printf("Opening word file...\n");

	if (loadWordFile() == false)
	{
		printf("File not found.\nCreating new word file...\n");
		createWordFile();
	}

	const char MAIN_CLASS[] = "main", WORDS_CLASS[] = "words";

	#pragma region Config of Windows

	// Main Window
	WNDCLASSEX MainWindowClass = {};
	MainWindowClass.cbSize = sizeof(WNDCLASSEX);
	MainWindowClass.lpfnWndProc = MainProc;
	MainWindowClass.hInstance = hinstance;
	MainWindowClass.lpszClassName = MAIN_CLASS;
	MainWindowClass.hbrBackground = MAIN_COLOR_BACKGROUND_WINDOW;
	MainWindowClass.hIcon = LoadIcon(hinstance, MAKEINTRESOURCE(IDI_APP_ICON));
	MainWindowClass.hIconSm = LoadIcon(hinstance, MAKEINTRESOURCE(IDI_APP_ICON));

	WNDCLASSEX WordsWindowClass = {};
	WordsWindowClass.cbSize = sizeof(WNDCLASSEX);
	WordsWindowClass.lpfnWndProc = WordsProc;
	WordsWindowClass.hInstance = hinstance;
	WordsWindowClass.lpszClassName = WORDS_CLASS;
	WordsWindowClass.hbrBackground = MAIN_COLOR_BACKGROUND_WINDOW;
	
	#pragma endregion

	RegisterClassEx(&MainWindowClass);
	RegisterClassEx(&WordsWindowClass);

	printf("Creating windows...\n");

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
		MessageBox(NULL, "Not possible load windows", NULL, MB_ICONERROR);
		return 0x00;
	}

	printf("Opening main window...\n");

	ShowWindow(hwnd_main, SHOW_OPENWINDOW);
	ShowWindow(hwnd_words, SW_HIDE);

	MSG msg = {};

	printf("\nRunning messages\n");

	while(GetMessage(&msg, NULL, 0x00, 0x00) > 0x00) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0x00;
};