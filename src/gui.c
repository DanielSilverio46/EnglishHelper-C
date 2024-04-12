#include <windows.h>
#include "word.h"

HWND boxTextInput;
char guessWord[255], *portu, *engl;

int points, fails;

LRESULT CALLBACK Proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void DrawTexts(HDC hdc, RECT rect);
void intToStr(int num, char *store);

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
	char TextInput[50];

	switch(uMsg)
	{
		case WM_CREATE:
			boxTextInput = CreateWindow(
				"EDIT",
				"",
				WS_BORDER | WS_VISIBLE | WS_CHILD,
			  // x    y   width  height
				350, 200,  200,    20,
				hwnd,
				NULL,
				NULL,
				NULL
			);

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

					randomWord(guessWord, sizeof(guessWord));
					divideTuple(guessWord, &engl, &portu);

					InvalidateRect(hwnd, NULL, 0);
					UpdateWindow(hwnd);

					break;
			}

			break;

		case WM_DESTROY:
			PostQuitMessage(0);
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

		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
	};

	return 0;
}

void intToStr(int num, char *store)
{
	int decimalPlaces = -1, buffNum = num;

	do {
		buffNum /= 10;
		decimalPlaces++;
	} while (buffNum != 0);

	while (num != 0) {
		store[decimalPlaces] = (num % 10) + 0x30;
		decimalPlaces--;

		num /= 10;

	}
}

void DrawTexts(HDC hdc, RECT rect)
{
	char PointsStr[100] = "Points: ", FailsStr[100] = "Fails: ";

	intToStr(10, &PointsStr[8]);
	intToStr(10, &FailsStr[7]);

	rect.top += 50;
	rect.left += 100;
	DrawText(hdc, PointsStr, -1, &rect, DT_TOP | DT_LEFT);

	rect.right -= 200;
	DrawText(hdc, FailsStr, -1, &rect, DT_TOP | DT_RIGHT);

	DrawText(hdc, portu, -1, &rect, DT_VCENTER | DT_CENTER | DT_MODIFYSTRING);
}