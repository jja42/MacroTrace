#ifndef MACROLOAD_H
#define MACROLOAD_H

#include <stdio.h>
#include "list.h"

//takes a filename and sanitizes it for file opening
char* parse_filename(char* filename);

//takes a clean filename, opens the file and then loads the json objects
void load_filename(char* filename);

//uses the list of json objects from load_filename, converting them into a list of events
void load_file_events(list_t* file_json);

//removes whitespace from filename
void trim_whitespace(char *str);

//if the user adds .json to a filename, this removes it
void remove_json_extension(char *str);

void play_loaded_events();
#endif