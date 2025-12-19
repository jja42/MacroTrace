#include <stdio.h>
#include <stdlib.h>
#include "macrointerpret.h"
#include "macrotrace.h"
#include "macrosave.h"
#include "macrolog.h"
#include "macroutil.h"

DWORD startTime;
bool initialized = false;
bool recording = false;
bool endTrace = false;

//Get relative timestamp
DWORD timestamp() {
    return GetTickCount() - startTime;
}

//Callback for Keyboard Events
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        if(!recording){
            if(!initialized){
                if(wParam == WM_SYSKEYDOWN || wParam == WM_KEYDOWN){
                    initialized = true;
                    return CallNextHookEx(NULL, nCode, wParam, lParam);
                }
                return CallNextHookEx(NULL, nCode, wParam, lParam);
            }
            if(wParam == WM_SYSKEYUP || wParam == WM_KEYUP){
                recording = true;
                startTime = GetTickCount();
                printf("Recording Started.\n");
                access_temp_trace_file();
                init_logger();
                return CallNextHookEx(NULL, nCode, wParam, lParam);
            }
            return CallNextHookEx(NULL, nCode, wParam, lParam);
        }
        KBDLLHOOKSTRUCT *kbd = (KBDLLHOOKSTRUCT*)lParam;

        if(check_double_press(&endTrace,kbd->vkCode,wParam,VK_ESCAPE)){
            PostQuitMessage(0);
        }

        const char *eventType = NULL;
        DWORD timeStamp = timestamp();
        int isExtended;

        switch (wParam) {
            case WM_KEYDOWN: eventType = "Key Pressed"; break;
            case WM_KEYUP:   eventType = "Key Released"; break;
            case WM_SYSKEYDOWN: eventType = "Key Pressed"; break;
            case WM_SYSKEYUP:   eventType = "Key Released"; break;
            default: eventType = "Unknown Key Event"; return CallNextHookEx(NULL, nCode, wParam, lParam);
        }

        if (eventType) {
            isExtended = (kbd->flags & LLKHF_EXTENDED) != 0;
            printf("%s: %s [%lu ms]\n",
            eventType,
            scanCode_to_string(kbd->scanCode, isExtended),timeStamp);
            save_keyboard_event(kbd->scanCode, isExtended, wParam, timeStamp);
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

//Callback for Mouse Events
LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION && recording) {
        MSLLHOOKSTRUCT *ms = (MSLLHOOKSTRUCT*)lParam;
        WORD btn = HIWORD(ms->mouseData);
        DWORD timeStamp = timestamp();

        switch (wParam) {
            case WM_MOUSEWHEEL:
                int delta = GET_WHEEL_DELTA_WPARAM(ms->mouseData);
                if(delta > 0)
                {
                    printf("Mouse Wheel Scrolled Up [%lu ms]\n", timeStamp);
                }
                else{
                    printf("Mouse Wheel Scrolled Down [%lu ms]\n", timeStamp);
                }
                break;
            case WM_MOUSEMOVE:
                printf("Mouse Moved to x=%ld y=%ld [%lu ms]\n",
                      ms->pt.x, ms->pt.y, timeStamp);
                break;
            case WM_LBUTTONDOWN:
            case WM_RBUTTONDOWN:
            case WM_MBUTTONDOWN:
            case WM_XBUTTONDOWN:
                printf("Mouse Button Pressed: %s at x=%ld y=%ld [%lu ms]\n",
                mouse_button_input_to_string(wParam, btn),
                ms->pt.x, ms->pt.y,
                timeStamp);
                break;
            case WM_LBUTTONUP:
            case WM_RBUTTONUP:
            case WM_MBUTTONUP:
            case WM_XBUTTONUP:
                printf("Mouse Button Released: %s at x=%ld y=%ld [%lu ms]\n",
                mouse_button_input_to_string(wParam, btn),
                ms->pt.x, ms->pt.y,
                timeStamp);
                break;
            default:
                printf("Unknown Mouse Event [%lu ms]", timestamp());
                return CallNextHookEx(NULL, nCode, wParam, lParam);
            }

        save_mouse_event(ms, wParam, timeStamp);
    }

    return CallNextHookEx(NULL, nCode, wParam, lParam);
}
