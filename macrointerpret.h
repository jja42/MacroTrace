#ifndef MACROINT_H
#define MACROINT_H

#include <uiohook.h>
#include "json_parser.h"

char* keycode_to_string(uint16_t keycode);

char* button_to_mouse_input(uint16_t button);

JsonObj* json_from_keyboard_event(int time, event_type type, int keycode);

JsonObj* json_from_mouse_event(int time, event_type type, int button, int  x, int  y);

JsonObj* json_from_mouse_wheel_event(int time, event_type type, int amount, int  rotation, int  direction);

char* json_to_string(JsonObj* obj);

#endif