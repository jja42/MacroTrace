#include <stdio.h>
#include <stdlib.h>
#include "macrointerpret.h"
#include "macrotrace.h"
#include "macrosave.h"

bool recording = false;
bool end = false;
uint64_t initial_timestamp;

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
            printf("Key Pressed: %s\n", keycode_to_string(event->data.keyboard.keycode));
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
            printf("Mouse Button Pressed: %s at (%d, %d)\n",
                   button_to_mouse_input(event->data.mouse.button),
                   event->data.mouse.x,
                   event->data.mouse.y);
            break;
        case EVENT_MOUSE_RELEASED:
            printf("Mouse Button Released: %s at (%d, %d)\n",
                   button_to_mouse_input(event->data.mouse.button),
                   event->data.mouse.x,
                   event->data.mouse.y);
            break;
        case EVENT_MOUSE_MOVED:
            printf("Mouse Moved to (%d, %d)\n", event->data.mouse.x, event->data.mouse.y);
            break;
        case EVENT_MOUSE_WHEEL:
            printf("Mouse Wheel Scrolled %d Units.\n", event->data.wheel.rotation);
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
        initial_timestamp = event->time;
        recording = true;
        access_temp_trace_file();
        return;
        }
        return;
    }
    if (event->type >= EVENT_KEY_PRESSED && event->type <= EVENT_KEY_RELEASED) {
        handle_keyboard_event(event);
        save_event(event, initial_timestamp);
    } else if (event->type >= EVENT_MOUSE_PRESSED && event->type <= EVENT_MOUSE_MOVED || event->type == EVENT_MOUSE_WHEEL) {
        handle_mouse_event(event);
        save_event(event, initial_timestamp);
    }
}

