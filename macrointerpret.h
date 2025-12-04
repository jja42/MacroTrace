#ifndef MACROINT_H
#define MACROINT_H

#include <uiohook.h>
#include "json_parser.h"

char* keycode_to_string(uint16_t keycode);

char* button_to_mouse_input(uint16_t button);

JsonObj* json_from_keyboard_event(uint64_t time, event_type type, uint16_t keycode);

JsonObj* json_from_mouse_event(uint64_t time, event_type type, uint16_t button, int16_t  x, int16_t  y);

JsonObj* json_from_mouse_wheel_event(uint64_t time, event_type type, uint16_t amount, int16_t  rotation, uint8_t  direction);

#endif