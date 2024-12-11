#include <stdio.h>

#include "headers/window_flow.h"
#include "headers/word.h"
#include "headers/main.h"

WNDPROC edit_proc;

int GetTextOfBox(HWND window_textbox, char *keep_text, int max_letters)
{
	if (GetWindowTextLength(window_textbox) < max_letters)
	{
		GetWindowText(window_textbox, keep_text, max_letters);
		return 0x01;
	}

	return 0x00;
}

LRESULT CALLBACK EditWordsProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_HOTKEY && GetFocus() == hwnd) return 0x00;

	return CallWindowProc(edit_proc, hwnd, uMsg, wParam, lParam);
}

__declspec(dllexport) LRESULT CALLBACK MainProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Tuple *tuple;

	switch (uMsg)
	{
		case WM_CREATE:
			if (CreateWindow("EDIT", NULL, ES_LEFT | ES_LOWERCASE | WS_CHILD | WS_VISIBLE | WS_BORDER,
				MAIN_WINDOW_WIDTH/0X02-TEXT_BOX_WINDOW_WIDTH/0X02, MAIN_WINDOW_HEIGHT/0x02-0x0a,
				TEXT_BOX_WINDOW_WIDTH, TEXT_BOX_WINDOW_HEIGHT,
				hwnd, (HMENU)TEXT_BOX_MAIN_WINDOW, NULL, NULL) == NULL ||

				CreateWindow("BUTTON", "ok", WS_CHILD | WS_VISIBLE | WS_BORDER,
					MAIN_WINDOW_WIDTH/0x02+0x55, MAIN_WINDOW_HEIGHT/0x02+0x30, 
					BUTTON_WINDOW_WIDTH, BUTTON_WINDOW_HEIGHT,
					hwnd, (HMENU)OK_BUTTON, NULL, NULL) == NULL ||

				CreateWindow("BUTTON", "words", WS_CHILD | WS_VISIBLE | WS_BORDER,
					MAIN_WINDOW_WIDTH/0x02-0x95, MAIN_WINDOW_HEIGHT/0x02+0x30,
					BUTTON_WINDOW_WIDTH, BUTTON_WINDOW_HEIGHT,
					hwnd, (HMENU)WORDS_BUTTON, NULL, NULL) == NULL
			) { SendMessage(hwnd, WM_CLOSE, (WPARAM)NOT_POSSIBLE_CLEATE_CHILD, 0x00); }

			InitTuple(&tuple);

			getRandomTuple(tuple->tuple, sizeof(tuple->tuple)/sizeof(char));
			SplitTuple(tuple);

			SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)tuple);

			return 0x00;
		
		case WM_PAINT:
			int str1_len;
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);
			
			tuple = (Tuple*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			str1_len = strlen(Str1(tuple));

			TextOut(hdc, (MAIN_WINDOW_HEIGHT/0X02)-str1_len, 0x32, Str1(tuple), str1_len);

			EndPaint(hwnd, &ps);
			
			return 0x00;

		case WM_COMMAND:
			switch (wParam)
			{
				case WORDS_BUTTON:
					HWND words = FindWindow("words", "Words");
					if (words != NULL) ShowWindow(words, SHOW_OPENWINDOW);

					break;

				case OK_BUTTON:
					HWND textbox = FindWindowEx(hwnd, NULL, "EDIT", NULL);
					char TextInputed[0xff];

					if (textbox != NULL)
					{
						if (GetTextOfBox(textbox, TextInputed, sizeof(TextInputed)/sizeof(char)) != 0x00)
						{
							MessageBox(NULL, "Error", NULL, MB_OK);
						}

						SetWindowText(textbox, 0x00);
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
			tuple = (Tuple*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

			FreeTuple(tuple);
			closeWordFile();

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
			HWND edit = CreateWindow(
				"EDIT", "", ES_LEFT | ES_LOWERCASE | ES_MULTILINE | WS_CHILD | WS_VISIBLE,
				0x00, 0x00, MAIN_WINDOW_WIDTH - 0x05, MAIN_WINDOW_HEIGHT- 0x20,
				hwnd, NULL, NULL, NULL
			);

			if (edit == NULL) {
				SendMessage(hwnd, WM_DESTROY, 0x00, 0x00);

				return 0x00;
			}

			char words_file_content[0xff];
			getAllWords(words_file_content, sizeof(words_file_content)/sizeof(char));

			SetWindowText(edit, words_file_content);

			edit_proc = (WNDPROC)GetWindowLongPtr(edit, GWLP_WNDPROC);
			
			RegisterHotKey(edit, 0x01, MOD_CONTROL | MOD_NOREPEAT, 0x53);
			if (SetWindowLongPtr(edit, GWLP_WNDPROC, (LONG_PTR)EditWordsProc) == 0) MessageBox(NULL, "Error", NULL, MB_OK);

			return 0x00;

		case WM_CLOSE:
			ShowWindow(hwnd, SW_HIDE);

			return 0x00;

		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}
