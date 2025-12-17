#ifndef MACROINT_H
#define MACROINT_H

#include <windows.h>
#include "json_parser.h"\

//convert ScanCode to string representation of key input
char* scanCode_to_string(DWORD scanCode, int isExtended);

//convert string representation to ScanCode
DWORD string_to_scanCode(char* key);

//get button pressed from input and return it
char* mouse_button_input_to_string(WPARAM input, WORD btn);

//constructs a json object from a keyboard event and returns it
JsonObj* json_from_keyboard_event(DWORD scanCode, int isExtended, WPARAM type, int time);

//constructs a json object from a mouse event and returns it
JsonObj* json_from_mouse_event(WPARAM type, DWORD button, int x, int y, int time);

//constructs a json object from a mouse wheel event and returns it
JsonObj* json_from_mouse_wheel_event(int delta, int time);

//converts a json object into string to be appended to a file
char* json_to_string(JsonObj* obj);

#endif