#ifndef MACROLOG_H
#define MACROLOG_H

#include <stdio.h>

//creates the log file
void init_logger();

//opens log file for appending and appends the event string to the file
void log_event(char* event);

//opens log file for appending and converst format and arguments into string to append to file
void log_event_fmt(const char* fmt, ...);

#endif