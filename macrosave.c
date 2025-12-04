#include "macrosave.h"
#include <string.h>
#include <ctype.h>
#include "list.h"
#include "macrointerpret.h"
#include <stdlib.h>
#include "macrolog.h"

FILE* temptraceFile;
list_t* json_objects;
JsonObj* jsonRoot;

void access_temp_trace_file()
{
//Initialize Json Object List
json_objects = new_list(1);

//Create Trace File
temptraceFile = fopen("temp/temp_trace.json", "w");

init_logger();
}

void write_temp_trace_file(){
    log_event_fmt("Json Objects Length: %d", json_objects->count);
    JsonObj* mainObj = init_json_array(strdup("Events"),json_objects);
    list_t* json = new_list(1);
    list_add(json,mainObj);
    log_event("Main Json Initialized");
    jsonRoot = init_json_object(NULL,json);
    log_event("Root Json Initialized");
    char* buffer = json_to_string(jsonRoot);
    log_event("Buffer Initialized");
    fwrite(buffer,sizeof(char),strlen(buffer),temptraceFile);
    free(buffer);
    fclose(temptraceFile);
    free_json(jsonRoot);
    free_list(json_objects);
}

void sanitize_filename(char *str) {
    for (size_t i = 0; i < strlen(str); i++) {
        if (!isalnum(str[i]) && str[i] != '-' && str[i] != '_') {
            str[i] = '_';
        }
    }
}

void save_trace_file(char* filename){
    sanitize_filename(filename);

    int index;

    //Read From Temp File
    FILE* traceFile;
    temptraceFile = fopen("temp/temp_trace.txt","r");

    char traceFilename[strlen(filename)+20];
    snprintf(traceFilename, sizeof(traceFilename), "tracefiles/%s.txt", filename);

    //Create Trace File
    traceFile = fopen(traceFilename, "w");
    if (traceFilename == NULL)
    {
        printf("ERROR: Cannot create macro file: %s\n", traceFilename);
        return;
    }

    // Read contents from file
    while ((index = fgetc(temptraceFile)) != EOF)
    {
        fputc(index, traceFile);
    }

    printf("Macro Saved to %s\n", traceFilename);

    fclose(temptraceFile);
    fclose(traceFile);
    return;
}

void save_event(uiohook_event * const event, uint64_t initial_time){
    uint64_t time   = event->time;
    event_type type = event->type;
    uint64_t real_time = time - initial_time;

    switch (type) {
        case EVENT_KEY_PRESSED:
        case EVENT_KEY_RELEASED:
        {
            uint16_t keycode = event->data.keyboard.keycode;
            JsonObj* obj = json_from_keyboard_event((int)real_time, type, (int)keycode);
            list_add(json_objects,obj);
            break;
        }

        case EVENT_MOUSE_PRESSED:
        case EVENT_MOUSE_RELEASED:
        case EVENT_MOUSE_MOVED:
        {
            uint16_t button = event->data.mouse.button;
            int16_t  x = event->data.mouse.x;
            int16_t  y = event->data.mouse.y;

            JsonObj* obj = json_from_mouse_event((int)real_time, type, (int)button, (int)x, (int)y);
            list_add(json_objects,obj);
            break;
        }

        case EVENT_MOUSE_WHEEL: {
            uint16_t amount = event->data.wheel.amount;
            int16_t  rotation = event->data.wheel.rotation;
            uint8_t direction = event->data.wheel.direction;

            JsonObj* obj = json_from_mouse_wheel_event((int)real_time, type, (int)amount, (int)rotation, (int)direction);
            list_add(json_objects,obj);
            break;
        }

        default:
            break;
    }
}
