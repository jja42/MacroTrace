#ifndef MACROSAVE_H
#define MACROSAVE_H

#include <stdio.h>
#include <windows.h>

void access_temp_trace_file();

void write_temp_trace_file();

void save_mouse_event(MSLLHOOKSTRUCT* ms, WPARAM type, DWORD timeStamp);

void save_keyboard_event(DWORD scanCode, int isExtended, WPARAM type, DWORD timeStamp);

void save_trace_file(char* filename);

void sanitize_filename(char *str);

#endif