#include "headers/window_flow.h"
#include "headers/word.h"
#include <stdio.h>
#include <stdint.h>
#include <stdio.h>

#include <string.h>
/// Defining height and width of windows

#define MAIN_WINDOW_HEIGHT 0x190
#define MAIN_WINDOW_WIDTH 0x190

#define TEXT_BOX_WINDOW_WIDTH 0xC8
#define TEXT_BOX_WINDOW_HEIGHT 0x14

#define BUTTON_WINDOW_WIDTH 0x32
#define BUTTON_WINDOW_HEIGHT 0x19

/// Defining user actions

#define OK_BUTTON_PRESSED 0x01
#define WORDS_BUTTON_PRESSED 0x02
#define CONTROL_BUTTON_PRESSED 0x03

HWND BoxTextInputPTR = NULL;

//extern HWND hwndWords;

unsigned int points=0x00, fails=0x00;

char *portu = NULL, *engl = NULL;
char guessWord[50];
int intToStr(unsigned int num, char *store, uint8_t length_store)
{
	uint8_t decimal_places = 0x00;

	if (num >= 0x64) decimal_places = 0x02;
	else if (num >= 0x0A) decimal_places = 0x01;

	if (decimal_places >= length_store) return 0x01;

	store[decimal_places+0x01] = '\0'; 

	do {
		store[decimal_places] = (char)(num % 0x0A + 0x30);
		num /= 0x0A;
		decimal_places--;
	} while (num != 0x00);

	return 0x00;
}


__declspec(dllexport) LRESULT CALLBACK MainProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
		case WM_CREATE:
			BoxTextInputPTR = CreateWindow(
				"EDIT", "",
				WS_BORDER | WS_VISIBLE | WS_CHILD | ES_LEFT | ES_LOWERCASE,
				(MAIN_WINDOW_WIDTH/0x02)-(TEXT_BOX_WINDOW_WIDTH/0x02), // Get the half x of text box and put it on half x of main window
				MAIN_WINDOW_WIDTH/0x02,
				TEXT_BOX_WINDOW_WIDTH, TEXT_BOX_WINDOW_HEIGHT,
				hwnd, NULL, NULL, NULL
			);
				
			HWND OkButton = CreateWindow(
				"BUTTON", "OK",
				WS_BORDER | WS_VISIBLE | WS_CHILD,
				(MAIN_WINDOW_WIDTH/0x02)+50, (MAIN_WINDOW_HEIGHT/0x02)+50,
				BUTTON_WINDOW_WIDTH, BUTTON_WINDOW_HEIGHT,
				hwnd, (HMENU)OK_BUTTON_PRESSED, NULL, NULL
			);

			
			HWND WordsButton = CreateWindow(
					"BUTTON", "Words",
					WS_BORDER | WS_VISIBLE | WS_CHILD,
					(MAIN_WINDOW_WIDTH/2)-100, (MAIN_WINDOW_HEIGHT/2)+50,
					BUTTON_WINDOW_WIDTH+0x0a, BUTTON_WINDOW_HEIGHT,
					hwnd, (HMENU)WORDS_BUTTON_PRESSED, NULL, NULL
			);

			if (BoxTextInputPTR == NULL || OkButton == NULL || WordsButton == NULL || loadWordFile() == 0x00)
			{
				MessageBox(NULL, "Not possible load windows BoxTextInputPTR: ", NULL, MB_OK);
			}

			if (SetWindowSubclass(BoxTextInputPTR, WordsSpecialActionsProc, 0x00, (DWORD_PTR)hwnd) == 0x00)
				MessageBox(NULL, "Not possible install subclass to BoxTextInputPTR", NULL, MB_OK);
			
			
			randomWord(guessWord);
			divideTuple(guessWord, &engl, &portu);
			return 0x00;

		case WM_COMMAND:

			switch (LOWORD(wParam))
			{
				case OK_BUTTON_PRESSED:
					char TextInput[0xFF];
					GetWindowText(BoxTextInputPTR, TextInput, sizeof(TextInput));

					if (strcmp(engl, TextInput) == 0x00) {
						points++;
					} else {
						fails++;

						char CorrectWord[0x09 + strlen(engl)];

						strcpy(CorrectWord, "Correta: ");
						strcat(CorrectWord, engl);

						MessageBox(NULL, CorrectWord, NULL, MB_OK);
					}

					randomWord(guessWord);
					divideTuple(guessWord, &engl, &portu);

					SetWindowText(BoxTextInputPTR, 0x00);
					SetFocus(BoxTextInputPTR);

					InvalidateRect(hwnd, NULL, 0x00);
					UpdateWindow(hwnd);


					break;

				case CONTROL_BUTTON_PRESSED:
					//ShowWindow(hwndWords, SW_SHOWNORMAL);
					break;
			}

			return 0x00;


		case WM_PAINT:
			WNDCLASS *wndclass;
			PAINTSTRUCT ps;
			RECT rect;

			HDC hdc = BeginPaint(hwnd, &ps);
			GetWND_Of_HWND(hwnd, wndclass);

			GetClientRect(hwnd, &rect);

			FillRect(hdc, &rect, wndclass->hbrBackground);

			SetTextColor(hdc, 0x00);
			SetBkMode(hdc, TRANSPARENT);

			//DrawPointsUser(hdc, &rect, 0x0, 0x0);

			// Drawing portuguese word for user guess the same word in english
			rect.top += 0x0A;
			DrawText(hdc, "s", (int8_t)0xff, &rect, DT_VCENTER | DT_CENTER);

			free(wndclass);
			EndPaint(hwnd, &ps);
			return 0x00;

		case WM_CLOSE:
			DestroyWindow(hwnd);
        	return 0x00;

		case WM_DESTROY:
			closeWordFile();
			PostQuitMessage(0x00);

		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
	};

	return 0x0;
}

__declspec(dllexport) LRESULT CALLBACK WordsSpecialActionsProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam,
	UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	if (uMsg == WM_KEYDOWN) {
		switch (uIdSubclass)
		{
			case 0x00:
				switch (LOWORD(wParam))
					{
						case VK_RETURN:
							SendMessage((HWND)dwRefData, WM_COMMAND, 0x01, 0x00);
							break;

						default: return DefSubclassProc(hwnd, uMsg, wParam, lParam);
					}

				break;

			case 0x01:
				if (HIWORD(GetKeyState(VK_CONTROL)) && (LOWORD(wParam) == 'S' || LOWORD(wParam) == 's'))
				{
					char *words = (char*)calloc(0xc8, sizeof(char));

					GetWindowText(hwnd, words, 0xc8);
					updateWordFile(words);
				}

				break;

		}

		return 0x00;
	}

	return DefSubclassProc(hwnd, uMsg, wParam, lParam);
}

__declspec(dllexport) void GetWND_Of_HWND(HWND hwnd, WNDCLASS *wnd)
{
	wnd = (WNDCLASS*)malloc(sizeof(WNDCLASS));
	char class_name[0xff];

	GetClassName(hwnd, class_name, (sizeof(class_name) / sizeof(char)));
	GetClassInfo(NULL, class_name, wnd);
}

__declspec(dllexport) LRESULT CALLBACK FileControlProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
		case WM_CREATE:
			HWND edit = CreateWindow("EDIT", "",
				WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_WANTRETURN | ES_LOWERCASE,
				0, 0, MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT,
				hwnd, NULL, NULL, NULL);

			SendMessage(hwnd, WM_SETTEXT, (WPARAM)edit, (LPARAM)NULL);

			if (SetWindowSubclass(edit, WordsSpecialActionsProc, 1, (DWORD_PTR)NULL) == 0)
				MessageBox(NULL, "Not possible install subclass to edit of File Control", NULL, MB_OK);

			return 0;

		case WM_SETTEXT:
			char *file_content = (char*)calloc(200, sizeof(char));

			for (int i = 0; i < totalTuples(); ++i) {
				strcat(file_content, getSpecificWord(i));
				strcat(file_content, "\r\n");
			}

			SetWindowText((HWND)wParam, file_content);
			free(file_content);

			return 0;

		case WM_CLOSE:
			ShowWindow(hwnd, SW_HIDE);
			return 0;

		case WM_DESTROY:
			ShowWindow(hwnd, SW_HIDE);
			return 0;

		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
	};

	return 0;
}