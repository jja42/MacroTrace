#ifndef MACROUTIL_H
#define MACROUTIL_H

#include <windows.h>
#include <stdbool.h>


bool check_double_press(bool* ref, DWORD inputWVK, WPARAM wParam, DWORD desiredWVK);

#endif