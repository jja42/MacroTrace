#include <stdio.h>

void access_temp_trace_file();

void write_temp_trace_file(char* line);

void close_temp_trace_file();

void log_and_save_event(const char *fmt, ...);

void save_trace_file(char* filename);

void sanitize_filename(char *str);