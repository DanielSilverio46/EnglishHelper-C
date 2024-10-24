#ifndef MAIN_H
#define MAIN_H

#include <windows.h>
#include <string.h>
#include <stdlib.h>

#define MAIN_WINDOW_HEIGHT 0x190
#define MAIN_WINDOW_WIDTH 0x190

/*											 Change color									 *
 *									 according to hbrBackground	values				         *
 *		https://learn.microsoft.com/pt-br/windows/win32/api/winuser/ns-winuser-wndclassa     *
 *												   |										 *
 *												   V              							 */
#define MAIN_COLOR_BACKGROUND_WINDOW (HBRUSH)(COLOR_WINDOW+1) 

HINSTANCE main_hinstance;

#endif