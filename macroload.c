#include "macroload.h"
#include "json_parser.h"
#include <string.h>
#include <ctype.h>
#include "macroevent.h"
#include "macrolog.h"

list_t* events;

char* parse_filename(char* filename){
    trim_whitespace(filename);
    remove_json_extension(filename);

    return filename;
}

void load_filename(char* filename){
    printf("\n");
    filename = parse_filename(filename);

    char filepath[150]; 
    sprintf(filepath,"tracefiles/%s.json", filename);

    list_t* file_json = read_json_into_objects(filepath); //Objects in Root Json

    load_file_events(file_json);
}

void load_file_events(list_t* file_json)
{
    events = new_list(1);
    list_t* event_array = json_list_get(file_json,"Events");//Get Event Array
    for(int i = 0; i<event_array->count;i++){
         JsonObj* json_event = (JsonObj*)event_array->data[i]; //JSON in Array
         InputEvent* event = json_to_input_event(json_event);
         list_add(events,event);
         log_event_fmt("Event Num: %d Added To List",i+1);
    }
}

void trim_whitespace(char *str) {
    char *start = str;
    char *end;

    while (*start && isspace((unsigned char)*start)) start++;

    end = start + strlen(start);
    while (end > start && isspace((unsigned char)*(end - 1))) end--;

    *end = '\0';

    if (start != str) {
        memmove(str, start, end - start + 1);
    }
}

void remove_json_extension(char *str) {
    size_t len = strlen(str);
    if (len >= 5 && strcmp(str + len - 5, ".json") == 0) {
        str[len - 5] = '\0';
    }
}