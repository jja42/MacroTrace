#ifndef MACROSAVE_H
#define MACROSAVE_H

#include <stdio.h>
#include <windows.h>

//creates temp trace file and opens for writing
void access_temp_trace_file();

//writes all of our json objects to our temp file
void write_temp_trace_file();

//deconstructs mouse event into necessary parameters to pass to macrointerpret functions, adds to json list
void save_mouse_event(MSLLHOOKSTRUCT* ms, WPARAM type, DWORD timeStamp);

//passes infromation to macrointerpret to create json object, adds to json list
void save_keyboard_event(DWORD scanCode, int isExtended, WPARAM type, DWORD timeStamp);

//writes from our temp file to our named trace file
void save_trace_file(char* filename);

//cleans up filename string to ensure useable filename
void sanitize_filename(char *str);

#endif