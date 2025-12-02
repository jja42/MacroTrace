#include <stdio.h>
#include <stdlib.h>
#include <uiohook.h>

// Callback for keyboard events
void handle_keyboard_event(uiohook_event * const event) {
    switch (event->type) {
        case EVENT_KEY_PRESSED:
            printf("Key Pressed: %u\n", event->data.keyboard.keycode);
            break;
        case EVENT_KEY_RELEASED:
            printf("Key Released: %u\n", event->data.keyboard.keycode);
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