#ifndef MACROSAVE_H
#define MACROSAVE_H

#include <stdio.h>
#include <uiohook.h>

void access_temp_trace_file();

void write_temp_trace_file(char* line);

void close_temp_trace_file();

void save_event(uiohook_event * const event);

void save_trace_file(char* filename);

void sanitize_filename(char *str);

#endif