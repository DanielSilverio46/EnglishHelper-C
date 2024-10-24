#include "headers/window_flow.h"
#include "headers/word.h"
#include "headers/main.h"

int GetTextOfBox(HWND *window_textbox, char *keep_text, unsigned int max_letters)
{
	if (GetWindowTextLength(*window_textbox) <= max_letters)
	{
		GetWindowText(*window_textbox, keep_text, max_letters);
		return 0x00;
	}

	return 0x01;
}

__declspec(dllexport) LRESULT CALLBACK MainProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_CREATE:
			HWND TextBox = NULL, OkButton = NULL, WordsButton = NULL;

			TextBox = CreateWindow(
				"EDIT", NULL, ES_LEFT | ES_LOWERCASE | WS_CHILD | WS_VISIBLE | WS_BORDER,
				MAIN_WINDOW_WIDTH/0X02-TEXT_BOX_WINDOW_WIDTH/0X02, MAIN_WINDOW_HEIGHT/0x02-0x0a,
				TEXT_BOX_WINDOW_WIDTH, TEXT_BOX_WINDOW_HEIGHT,
				hwnd, (HMENU)TEXT_BOX_MAIN_WINDOW, main_hinstance, NULL
			);

			OkButton = CreateWindow(
				"BUTTON", "ok", WS_CHILD | WS_VISIBLE | WS_BORDER,
				MAIN_WINDOW_WIDTH/0x02+0x55, MAIN_WINDOW_HEIGHT/0x02+0x30, 
				BUTTON_WINDOW_WIDTH, BUTTON_WINDOW_HEIGHT,
				hwnd, (HMENU)OK_BUTTON, main_hinstance, NULL
			);

			WordsButton = CreateWindow(
				"BUTTON", "words", WS_CHILD | WS_VISIBLE | WS_BORDER,
				MAIN_WINDOW_WIDTH/0x02-0x95, MAIN_WINDOW_HEIGHT/0x02+0x30,
				BUTTON_WINDOW_WIDTH, BUTTON_WINDOW_HEIGHT,
				hwnd, (HMENU)WORDS_BUTTON, main_hinstance, NULL
			);

			if (TextBox == NULL || OkButton == NULL || WordsButton == NULL)
			{
				SendMessage(hwnd, WM_CLOSE, (WPARAM)NOT_POSSIBLE_CLEATE_CHILD, 0x00);
			}

			return 0x00;

		case WM_COMMAND:
			switch (wParam)
			{
				case WORDS_BUTTON:
					HWND words = FindWindow("words", "Words");

					if (words != NULL)
					{
						ShowWindow(words, SHOW_OPENWINDOW);
					}

					MessageBox(NULL, "Hello", NULL, MB_OK);

					break;

				case OK_BUTTON:
					HWND textbox = FindWindowEx(hwnd, NULL, "EDIT", NULL);
					char TextInputed[0xffff];

					if (textbox != NULL)
					{
						if (GetTextOfBox(&textbox, TextInputed, sizeof(TextBox)/sizeof(char)) != 0x00)
						{
							MessageBox(NULL, "Error", NULL, MB_OK);
						}

						MessageBox(NULL, TextInputed, NULL, MB_OK);
					}

					break;
			}

			return 0x00;

		case WM_CLOSE:
			switch (wParam)
			{
				case NOT_POSSIBLE_CLEATE_CHILD:
					MessageBox(hwnd, "Error creating buttons and text box", NULL, MB_OK | MB_ICONHAND);
					break;
			}

			DestroyWindow(hwnd);
			return 0x00;

		case WM_DESTROY:
			PostQuitMessage(0x00);
		
		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}

__declspec(dllexport) LRESULT CALLBACK WordsProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_CREATE:
			HWND TextBox = CreateWindow(
				"EDIT", "", ES_LEFT | ES_LOWERCASE | ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_BORDER,
				0x00, 0x00, MAIN_WINDOW_WIDTH - 0x05, MAIN_WINDOW_HEIGHT- 0x20,
				hwnd, NULL, main_hinstance, NULL
			);

			return 0x00;

		case WM_CLOSE:
			ShowWindow(hwnd, SW_HIDE);

			return 0x00;

		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}