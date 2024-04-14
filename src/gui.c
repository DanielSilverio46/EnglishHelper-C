#include <windows.h>
#include <commctrl.h>
#include <string.h>

#include "word.h"

LRESULT CALLBACK Proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK KeyEnterProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam,
	UINT_PTR uIdSubclass, DWORD_PTR dwRefData);

void DrawTexts(HDC hdc, RECT rect);
void intToStr(unsigned int num, char *store);

char guessWord[255], TextInput[50], *portu, *engl;
unsigned int points=0, fails=0;

HWND boxTextInput;
WNDPROC oldWndProc;

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
	loadWordFile();

	const char *class = "My Class";
	
	WNDCLASS wc = {};
	wc.lpfnWndProc = Proc;
	wc.hInstance = hinstance;
	wc.lpszClassName = class;

	RegisterClass(&wc);

	HWND hwnd = CreateWindowEx(
		0,
		class,
		"English Helper",
		WS_OVERLAPPEDWINDOW,

		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

		NULL,
		NULL,
		hinstance,
		NULL 
	);

	if (hwnd == NULL)
		return 0;

	ShowWindow(hwnd, nCmdShow);

	randomWord(guessWord, sizeof(guessWord));
	divideTuple(guessWord, &engl, &portu);

	MSG msg = { };
	while(GetMessage(&msg, NULL, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
};

LRESULT CALLBACK Proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
		case WM_CREATE:
			boxTextInput = CreateWindow(
				"EDIT",
				"",
				WS_BORDER | WS_VISIBLE | WS_CHILD | ES_LEFT | ES_LOWERCASE,
			  // x    y   width  height
				350, 200,  200,    20,
				hwnd,
				NULL,
				NULL,
				NULL
			);

			oldWndProc = (WNDPROC)SetWindowLongPtr(boxTextInput, GWLP_WNDPROC,
				(LONG_PTR)KeyEnterProc);

			CreateWindow(
				"BUTTON",
				"OK",
				WS_BORDER | WS_VISIBLE | WS_CHILD,
				500, 230, 50, 25,
				hwnd,
				(HMENU)1,
				NULL,
				NULL
			);

			break;

		case WM_COMMAND:
			switch (LOWORD(wParam))
			{
				case 1:
					GetWindowText(boxTextInput, TextInput, sizeof(TextInput));
	
					if (strcmp(engl, TextInput) == 0) points++;
					else fails++;

					randomWord(guessWord, sizeof(guessWord));
					divideTuple(guessWord, &engl, &portu);

					SetWindowText(boxTextInput, 0);

					InvalidateRect(hwnd, NULL, 0);
					UpdateWindow(hwnd);

					break;
			}

			break;

		case WM_PAINT:
			PAINTSTRUCT ps;
			RECT rect;

			HDC hdc = BeginPaint(hwnd, &ps);

			FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));

			GetClientRect(hwnd, &rect);

			SetTextColor(hdc, 0);
			SetBkMode(hdc, TRANSPARENT);

			DrawTexts(hdc, rect);

			EndPaint(hwnd, &ps);

			break;

		case WM_DESTROY:
			PostQuitMessage(0);

			break;

		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
	};

	return 0;
}

LRESULT CALLBACK KeyEnterProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam,
	UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	if (uMsg == WM_KEYDOWN)
	{
		SetWindowText(hwnd, 0);
		return 0;
	};

	return CallWindowProc(oldWndProc, hwnd, uMsg, wParam, lParam);
}

void intToStr(unsigned int num, char *store)
{
	int decimalPlaces = 0;

	if (num < 10) {
		decimalPlaces = 0;
	} else if (num < 100) {
		decimalPlaces = 1;
	} else if (num < 1000){
		decimalPlaces = 2;
	};

	do {
		store[decimalPlaces] = (num % 10) + 0x30;
		decimalPlaces--;

		num /= 10;
	} while (num != 0);
}

void DrawTexts(HDC hdc, RECT rect)
{
	char PointsStr[100] = "Points: ", FailsStr[100] = "Fails: ";

	intToStr(points, &PointsStr[8]);
	intToStr(fails, &FailsStr[7]);

	rect.top += 50;
	rect.left += 100;
	DrawText(hdc, PointsStr, -1, &rect, DT_TOP | DT_LEFT);

	rect.right -= 200;
	DrawText(hdc, FailsStr, -1, &rect, DT_TOP | DT_RIGHT);

	DrawText(hdc, portu, -1, &rect, DT_VCENTER | DT_CENTER | DT_MODIFYSTRING);
}