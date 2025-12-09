#ifndef MACROINT_H
#define MACROINT_H

#include <windows.h>
#include "json_parser.h"

char* scanCode_to_string(DWORD scanCode, int isExtended);

char* mouse_button_input_to_string(WPARAM input, WORD btn);

JsonObj* json_from_keyboard_event(DWORD scanCode, int isExtended, WPARAM type, int time);

JsonObj* json_from_mouse_event(WPARAM type, DWORD button, int x, int y, int time);

JsonObj* json_from_mouse_wheel_event(int delta, int time);

char* json_to_string(JsonObj* obj);

#endif