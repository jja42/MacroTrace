#ifndef MACROLOG_H
#define MACROLOG_H

#include <stdio.h>


void init_logger();

void log_event(char* event);

void log_event_fmt(const char* fmt, ...);

#endif