#include <windows.h>

HWND textinput;

LRESULT CALLBACK Proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
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

	if (hwnd == NULL) {
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);

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
			textinput = CreateWindow(
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


			rect.top += 50;
			rect.left += 100;
			DrawText(hdc, "Points: 0", -1, &rect, DT_TOP | DT_LEFT);

			rect.right -= 200;
			DrawText(hdc, "Fails: 0", -1, &rect, DT_TOP | DT_RIGHT);

			EndPaint(hwnd, &ps);

			break;

		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
	};

	return 0;
};