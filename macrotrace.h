#ifndef MACROTRACE_H
#define MACROTRACE_H

#include <windows.h>
#include <stdbool.h>

//gets relative timestamp based on initial time
DWORD timestamp();

//Mouse Input Hook Function
LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam);

//Keyboard Input Hook Function
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);

//Keyboard Input Function just to detect Exit
LRESULT CALLBACK AltKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);

//checks for exit case - Double Escape
void check_exit(DWORD wvk, WPARAM wParam);
#endif