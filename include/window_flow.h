#ifndef GFUNC_H
#define GFUNC_H

#define dll __declspec(dllexport)

#include <windows.h>
#include <commctrl.h>

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "windows.h"
#include "word.h"
#include "user.h"

/// Defining default height and width of windows
#define TEXT_BOX_WINDOW_WIDTH 0xC8
#define TEXT_BOX_WINDOW_HEIGHT 0x14

#define BUTTON_WINDOW_WIDTH 0x32
#define BUTTON_WINDOW_HEIGHT 0x19

/// Defining default child windows identifiers
#define OK_BUTTON 0X02
#define WORDS_BUTTON 0X03
#define TEXT_BOX_MAIN_WINDOW 0x01

/// Defining error
#define NOT_POSSIBLE_CLEATE_CHILD 0x01

dll extern LRESULT CALLBACK MainProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
dll extern LRESULT CALLBACK WordsProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

#endif