#include <stdio.h>
#include <stdlib.h>
#include "macrointerpret.h"
#include "macrotrace.h"
#include "macrosave.h"

bool recording = false;
bool end = false;

void log_and_save_event(const char *fmt, ...) {
    char buffer[256];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);

    printf("%s", buffer);
    write_temp_trace_file(buffer);
}

void check_exit(uiohook_event * const event){
    if(event->data.keyboard.keycode == VC_ESCAPE){
        if(!end){
            end = true;
            return;
        }
        else{
            hook_stop();
        }
    }
    else{
        end = false;
    }
}

// Callback for keyboard events
void handle_keyboard_event(uiohook_event * const event) {
    switch (event->type) {
        case EVENT_KEY_PRESSED:
            check_exit(event);
            log_and_save_event("Key Pressed: %s\n", keycode_to_string(event->data.keyboard.keycode));
            break;
        case EVENT_KEY_RELEASED:
            log_and_save_event("Key Released: %s\n", keycode_to_string(event->data.keyboard.keycode));
            break;
        default:
            break;
    }
}

// Callback for mouse events
void handle_mouse_event(uiohook_event * const event) {
    switch (event->type) {
        case EVENT_MOUSE_PRESSED:
            log_and_save_event("Mouse Button Pressed: %s at (%d, %d)\n",
                   button_to_mouse_input(event->data.mouse.button),
                   event->data.mouse.x,
                   event->data.mouse.y);
            break;
        case EVENT_MOUSE_RELEASED:
            log_and_save_event("Mouse Button Released: %s at (%d, %d)\n",
                   button_to_mouse_input(event->data.mouse.button),
                   event->data.mouse.x,
                   event->data.mouse.y);
            break;
        case EVENT_MOUSE_MOVED:
            log_and_save_event("Mouse Moved to (%d, %d)\n", event->data.mouse.x, event->data.mouse.y);
            break;
        default:
            break;
    }
}

// Main event dispatcher
void handle_event(uiohook_event * const event) {
    if(!recording){
        if (event->type == EVENT_KEY_RELEASED) 
        {
        printf("Recording Has Begun\n");
        printf("Press Escape Twice in a Row to Stop Recording.\n");
        recording = true;
        access_temp_trace_file();
        return;
        }
        return;
    }
    if (event->type >= EVENT_KEY_PRESSED && event->type <= EVENT_KEY_RELEASED) {
        handle_keyboard_event(event);
    } else if (event->type >= EVENT_MOUSE_PRESSED && event->type <= EVENT_MOUSE_MOVED) {
        handle_mouse_event(event);
    }
}

