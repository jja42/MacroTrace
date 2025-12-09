#ifndef MACROTRACE_H
#define MACROTRACE_H

#include <windows.h>
#include <stdbool.h>

DWORD timestamp();

LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);

void check_exit(DWORD scanCode, WPARAM wParam);
#endif