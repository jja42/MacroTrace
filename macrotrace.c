#include <stdio.h>
#include <stdlib.h>
#include <uiohook.h>

const char* keycode_to_string(uint16_t keycode) {
    switch (keycode) {
        case VC_A: return "A";
        case VC_B: return "B";
        case VC_C: return "C";
        case VC_D: return "D";
        case VC_E: return "E";
        case VC_F: return "F";
        case VC_G: return "G";
        case VC_H: return "H";
        case VC_I: return "I";
        case VC_J: return "J";
        case VC_K: return "K";
        case VC_L: return "L";
        case VC_M: return "M";
        case VC_N: return "N";
        case VC_O: return "O";
        case VC_P: return "P";
        case VC_Q: return "Q";
        case VC_R: return "R";
        case VC_S: return "S";
        case VC_T: return "T";
        case VC_U: return "U";
        case VC_V: return "V";
        case VC_W: return "W";
        case VC_X: return "X";
        case VC_Y: return "Y";
        case VC_Z: return "Z";

        case VC_1: return "1";
        case VC_2: return "2";
        case VC_3: return "3";
        case VC_4: return "4";
        case VC_5: return "5";
        case VC_6: return "6";
        case VC_7: return "7";
        case VC_8: return "8";
        case VC_9: return "9";
        case VC_0: return "0";

        case VC_ENTER: return "Enter";
        case VC_ESCAPE: return "Escape";
        case VC_BACKSPACE: return "Backspace";
        case VC_TAB: return "Tab";
        case VC_SPACE: return "Space";

        case VC_SHIFT_L: return "Left Shift";
        case VC_SHIFT_R: return "Right Shift";
        case VC_CONTROL_L: return "Left Ctrl";
        case VC_CONTROL_R: return "Right Ctrl";
        case VC_ALT_L: return "Left Alt";
        case VC_ALT_R: return "Right Alt";

        case VC_UP: return "Up Arrow";
        case VC_DOWN: return "Down Arrow";
        case VC_LEFT: return "Left Arrow";
        case VC_RIGHT: return "Right Arrow";

        case VC_F1: return "F1";
        case VC_F2: return "F2";
        case VC_F3: return "F3";
        case VC_F4: return "F4";
        case VC_F5: return "F5";
        case VC_F6: return "F6";
        case VC_F7: return "F7";
        case VC_F8: return "F8";
        case VC_F9: return "F9";
        case VC_F10: return "F10";
        case VC_F11: return "F11";
        case VC_F12: return "F12";

        default: return "Unknown";
    }
}


// Callback for keyboard events
void handle_keyboard_event(uiohook_event * const event) {
    switch (event->type) {
        case EVENT_KEY_PRESSED:
            printf("Key pressed: %s\n", keycode_to_string(event->data.keyboard.keycode));
            break;
        case EVENT_KEY_RELEASED:
            printf("Key Released: %s\n", keycode_to_string(event->data.keyboard.keycode));
            break;
        default:
            break;
    }
}

// Callback for mouse events
void handle_mouse_event(uiohook_event * const event) {
    switch (event->type) {
        case EVENT_MOUSE_PRESSED:
            printf("Mouse Button Pressed: %u at (%d, %d)\n",
                   event->data.mouse.button,
                   event->data.mouse.x,
                   event->data.mouse.y);
            break;
        case EVENT_MOUSE_RELEASED:
            printf("Mouse Button Released: %u at (%d, %d)\n",
                   event->data.mouse.button,
                   event->data.mouse.x,
                   event->data.mouse.y);
            break;
        case EVENT_MOUSE_MOVED:
            printf("Mouse Moved to (%d, %d)\n", event->data.mouse.x, event->data.mouse.y);
            break;
        default:
            break;
    }
}

// Main event dispatcher
void handle_event(uiohook_event * const event) {
    if (event->type >= EVENT_KEY_PRESSED && event->type <= EVENT_KEY_RELEASED) {
        handle_keyboard_event(event);
    } else if (event->type >= EVENT_MOUSE_PRESSED && event->type <= EVENT_MOUSE_MOVED) {
        handle_mouse_event(event);
    }
}

int main(void) {
    // Set the callback
    hook_set_dispatch_proc(handle_event);

    // Start the hook
    if (hook_run() != UIOHOOK_SUCCESS) {
        fprintf(stderr, "Failed to start hook!\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}