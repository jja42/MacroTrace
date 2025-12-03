#include <windows.h>
#include <stdio.h>
#include <time.h>

HHOOK keyboardHook;
HHOOK mouseHook;
DWORD startTime;

// Get relative timestamp
DWORD timestamp() {
    return GetTickCount() - startTime;
}

// ----------------- KEYBOARD HOOK -----------------

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        KBDLLHOOKSTRUCT *kbd = (KBDLLHOOKSTRUCT*)lParam;

        const char *eventType = NULL;

        switch (wParam) {
            case WM_KEYDOWN: eventType = "KEY_DOWN"; break;
            case WM_KEYUP:   eventType = "KEY_UP"; break;
            case WM_SYSKEYDOWN: eventType = "SYS_KEY_DOWN"; break;
            case WM_SYSKEYUP:   eventType = "SYS_KEY_UP"; break;
        }

        if (eventType)
            printf("[%lu ms] %s: vk=%lu sc=%lu\n",
                   timestamp(), eventType, kbd->vkCode, kbd->scanCode);
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

// ----------------- MOUSE HOOK -----------------

LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        MSLLHOOKSTRUCT *ms = (MSLLHOOKSTRUCT*)lParam;
        const char *eventType = NULL;

        switch (wParam) {
            case WM_MOUSEMOVE: eventType = "MOUSE_MOVE"; break;
            case WM_LBUTTONDOWN: eventType = "LMB_DOWN"; break;
            case WM_LBUTTONUP:   eventType = "LMB_UP"; break;
            case WM_RBUTTONDOWN: eventType = "RMB_DOWN"; break;
            case WM_RBUTTONUP:   eventType = "RMB_UP"; break;
            case WM_MOUSEWHEEL:  eventType = "WHEEL"; break;
        }

        if (eventType) {
            if (wParam == WM_MOUSEWHEEL) {
                int delta = GET_WHEEL_DELTA_WPARAM(ms->mouseData);
                printf("[%lu ms] %s: delta=%d\n",
                       timestamp(), eventType, delta);
            } else if (wParam == WM_MOUSEMOVE) {
                printf("[%lu ms] %s: x=%ld y=%ld\n",
                       timestamp(), eventType, ms->pt.x, ms->pt.y);
            } else {
                printf("[%lu ms] %s: x=%ld y=%ld\n",
                       timestamp(), eventType, ms->pt.x, ms->pt.y);
            }
        }
    }

    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

// ----------------- MAIN -----------------

int main() {
    printf("MacroTrace Starter - Recording global input...\n");
    printf("Press CTRL+C in this terminal to quit.\n\n");

    startTime = GetTickCount();

    keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
    mouseHook    = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, NULL, 0);

    if (!keyboardHook || !mouseHook) {
        printf("Failed to install hooks.\n");
        return 1;
    }

    // Standard Windows message loop
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {}

    UnhookWindowsHookEx(keyboardHook);
    UnhookWindowsHookEx(mouseHook);

    return 0;
}
