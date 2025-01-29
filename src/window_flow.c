#include "window_flow.h"
#include "user.h"
#include "log.h"

#include "others.c"

typedef struct datas {
	Tuple *tuple;
	UserData *user_points;
} WindowData;

WNDPROC edit_proc;

int GetTextOfBox(HWND textbox, char *keep_text, int max_chars)
{
	if (GetWindowTextLength(textbox) < max_chars)
	{
		GetWindowText(textbox, keep_text, max_chars);
		return 0x00;
	}

	return 0x01;
}

LRESULT CALLBACK EditWordsProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_HOTKEY && GetFocus() == hwnd) {
		printf("Saving words...");

		unsigned long long size_save_words = 0xff;
		char *save_words = (char*)malloc(sizeof(char) * 0xff);

		// while the size of save_words is incompatible with the size of text inputed,
		// its size (save_words) will double.
		do {

			save_words = (char*)realloc(save_words, (size_save_words *= 0x02) / sizeof(char));
		
		} while(GetTextOfBox(hwnd, save_words, size_save_words/sizeof(char)) == 0x00);


		updateWordFile(save_words, strlen(save_words));

		free(save_words);

		return 0x00;
	}

	return CallWindowProc(edit_proc, hwnd, uMsg, wParam, lParam);
}

__declspec(dllexport) LRESULT CALLBACK MainProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	WindowData *data;

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


			#pragma region UserData
			data = (WindowData*)malloc(sizeof(WindowData));

			// Defining a tuple and user and passing to GWLP_USERDATA
			InitTuple(&data->tuple);

			getRandomTuple(GetTuple(data->tuple), sizeof(GetTuple(data->tuple))/sizeof(char));
			SplitTuple(data->tuple);

			initUser(&data->user_points);

			SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)data);

			#pragma endregion

			return 0x00;
		
		case WM_PAINT:
			char points[0xff] = "Points: ", fails[0xff] = "Fails: ";

			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);
			data = (WindowData*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

			intToStr(GetUserPoints(data->user_points), &points[0x08], sizeof(points)/sizeof(char));
			intToStr(GetUserFails(data->user_points), &fails[0x07], sizeof(fails)/sizeof(char));

			TextOut(hdc, (MAIN_WINDOW_HEIGHT/0X02)-strlen(GetStr1(data->tuple)), 0x32, GetStr1(data->tuple), strlen(GetStr1(data->tuple)));

			TextOut(hdc, 0x32, 0x50, points, strlen(points));
			TextOut(hdc, 0x140, 0x50, fails, strlen(fails));

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
					char text_inputed[0xff];

					HWND textbox = FindWindowEx(hwnd, NULL, "EDIT", NULL);
					data = (WindowData*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
					
					if (textbox != NULL)
					{
						if (GetTextOfBox(textbox, text_inputed, sizeof(text_inputed)/sizeof(char)) == 0x00)
						{
							printf("Text inputed: %s - len: %llu\nText hided: %s - len: %llu\n\n", text_inputed, strlen(text_inputed),
								GetStr2(data->tuple), strlen(GetStr2(data->tuple)));

							if (strcmp(text_inputed, GetStr2(data->tuple)) == 0x00) IncUserPoint(data->user_points);
							else IncUserFail(data->user_points);

							getRandomTuple(GetTuple(data->tuple), sizeof(GetTuple(data->tuple))/sizeof(char));
							SplitTuple(data->tuple);

							InvalidateRect(hwnd, NULL, TRUE);
						}

						SetWindowText(textbox, 0x00);
					}

					break;
			}

			return 0x00;

		case WM_CLOSE:
			data = (WindowData*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

			FreeTuple(data->tuple);
			deleteUser(data->user_points);

			free(data);

			#pragma region Reporting possible errors

			switch (wParam)
			{
				case NOT_POSSIBLE_CLEATE_CHILD:
					MessageBox(hwnd, "Error creating buttons and text box", NULL, MB_OK | MB_ICONHAND);
					break;
			}

			#pragma endregion

			CloseConsoleLog();

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
			char words_file_content[0xff];

			HWND edit = CreateWindow(
				"EDIT", "", ES_LEFT | ES_LOWERCASE | ES_MULTILINE | WS_CHILD | WS_VISIBLE,
				0x00, 0x00, MAIN_WINDOW_WIDTH - 0x05, MAIN_WINDOW_HEIGHT- 0x20,
				hwnd, NULL, NULL, NULL
			);

			if (edit == NULL) {
				SendMessage(hwnd, WM_DESTROY, 0x00, 0x00);

				return 0x00;
			}

			getAllWords(words_file_content, sizeof(words_file_content)/sizeof(char));

			SetWindowText(edit, words_file_content);

			edit_proc = (WNDPROC)GetWindowLongPtr(edit, GWLP_WNDPROC);
			
			RegisterHotKey(edit, 0x01, MOD_CONTROL | MOD_NOREPEAT, 0x53);
			if (SetWindowLongPtr(edit, GWLP_WNDPROC, (LONG_PTR)EditWordsProc) == 0)
				MessageBox(NULL, "Error", NULL, MB_OK);

			return 0x00;

		case WM_CLOSE:
			ShowWindow(hwnd, SW_HIDE);

			return 0x00;

		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}