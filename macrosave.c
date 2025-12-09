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
    log_event("Buffer Written");
    free(buffer);
    log_event("Buffer Freed");
    fclose(temptraceFile);
    log_event("Temp File Written");
    free_json(jsonRoot);
    log_event("JSON Freed");
}

void sanitize_filename(char *str) {
    for (size_t i = 0; i < strlen(str); i++) {
        if (!isalnum(str[i]) && str[i] != '-' && str[i] != '_') {
            str[i] = '_';
        }
    }
}

void save_trace_file(char* filename){
    printf("Saving File: %s at tracefiles/%s.json",filename,filename);
    sanitize_filename(filename);

    int index;

    //Read From Temp File
    FILE* traceFile;
    temptraceFile = fopen("temp/temp_trace.json","r");

    char traceFilename[strlen(filename)+20];
    snprintf(traceFilename, sizeof(traceFilename), "tracefiles/%s.json", filename);

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

void save_keyboard_event(DWORD scanCode, int isExtended, WPARAM type, DWORD timeStamp){
    JsonObj* obj = json_from_keyboard_event(scanCode, isExtended, type, (int)timeStamp);    
    list_add(json_objects,obj);
}

void save_mouse_event(MSLLHOOKSTRUCT* ms, WPARAM type, DWORD timeStamp){
    if(type == WM_MOUSEWHEEL){
        int delta = GET_WHEEL_DELTA_WPARAM(ms->mouseData);
        JsonObj* obj = json_from_mouse_wheel_event(delta, (int)timeStamp);
        list_add(json_objects,obj);
    }
    else{
        WORD btn = HIWORD(ms->mouseData);
        JsonObj* obj = json_from_mouse_event(type, btn, (int)ms->pt.x, (int)ms->pt.y, (int)timeStamp);    
        list_add(json_objects,obj);
    }
}
