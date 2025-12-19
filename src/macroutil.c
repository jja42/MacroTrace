#include "macroutil.h"

bool check_double_press(bool* ref, DWORD inputWVK, WPARAM wParam, DWORD desiredWVK)
{
    if (inputWVK != desiredWVK) {
        *ref = false;
        return false;
    }

    if (!*ref && wParam == WM_KEYUP) {
        *ref = true;
        return false;
    }

    if (*ref && wParam == WM_KEYDOWN) {
        return true;
    }

    return false;
}