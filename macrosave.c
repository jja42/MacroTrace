#include "macrosave.h"
#include <string.h>
#include <ctype.h>
#include "list.h"
#include "macrointerpret.h"

FILE* temptraceFile;
list_t* json_objects;
JsonObj* jsonRoot;

void access_temp_trace_file()
{
//Initialize Json Object List
json_objects = new_list(1);

//Create Trace File
temptraceFile = fopen("temp/temp_trace.json", "w");
}

void write_temp_trace_file(){
    JsonObj* mainObj = init_json_object("Events",json_objects,J_ARRAY);
    jsonRoot = init_json_object(NULL,mainObj,JSON);
}

void close_temp_trace_file(){
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

    int character;

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
    while ((character = fgetc(temptraceFile)) != EOF)
    {
        fputc(character, traceFile);
    }

    printf("Macro Saved to %s\n", traceFilename);

    fclose(temptraceFile);
    fclose(traceFile);
    return;
}

void save_event(uiohook_event * const event){
    uint64_t time   = event->time;
    event_type type = event->type;

    switch (type) {
        case EVENT_KEY_PRESSED:
        case EVENT_KEY_RELEASED:
        {
            uint16_t keycode = event->data.keyboard.keycode;
            JsonObj* obj = json_from_keyboard_event(time, type, keycode);
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

            mouse_event_save(time, type, button, x, y);
            JsonObj* obj = json_from_mouse_event(time, type, button, x, y);
            list_add(json_objects,obj);
            break;
        }

        case EVENT_MOUSE_WHEEL: {
            uint16_t amount = event->data.wheel.amount;
            int16_t  rotation = event->data.wheel.rotation;
            uint8_t direction = event->data.wheel.direction;

            JsonObj* obj = json_from_mouse_wheel_event(time, type, amount, rotation, direction);
            list_add(json_objects,obj);
            break;
        }

        default:
            break;
    }
}
