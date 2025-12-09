#include "macrointerpret.h"
#include "list.h"
#include <stdlib.h>
#include <string.h>
#include "macrolog.h"

int eventCount = 0;

char* scanCode_to_string(DWORD scanCode, int isExtended) {
    static char buffer[64];

    // Build the LPARAM for GetKeyNameText
    LPARAM lParam = (scanCode << 16) | (isExtended << 24);

    int result = GetKeyNameTextA(lParam, buffer, sizeof(buffer));

    if (result > 0)
        return buffer;

    return "Unknown Key";
}


char* mouse_button_input_to_string(WPARAM input, WORD btn)
{
    switch (input)
    {
        case WM_LBUTTONDOWN:
        case WM_LBUTTONUP:
            return "Left Click";
        case WM_RBUTTONDOWN:
        case WM_RBUTTONUP:
            return "Right Click";
        case WM_MBUTTONDOWN:
        case WM_MBUTTONUP:
            return "Scroll Wheel Click  ";
        case WM_XBUTTONDOWN:
        case WM_XBUTTONUP:
            if (btn == XBUTTON1) {
                return "Extra Mouse Button 1";
            }
            else{
                return "Extra Mouse Button 2";
            }
        default: return "Unknown Button";
    }
}

JsonObj* json_from_keyboard_event(DWORD scanCode, int isExtended, WPARAM type, int time){
    eventCount++;
    list_t* rootList = new_list(1);
    JsonObj* countObj = init_json_int(strdup("EventNum"), eventCount);
    JsonObj* timeObj = init_json_int(strdup("Timestamp"),time);
    JsonObj* typeObj;

    switch (type)
    {
        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
            typeObj = init_json_string(strdup("EventType"), strdup("Key Press"));
            break;
        case WM_KEYUP:
        case WM_SYSKEYUP:
            typeObj = init_json_string(strdup("EventType"), strdup("Key Release"));
            break;
    default:
        typeObj = init_json_string(strdup("EventType"), strdup("Unknown Event"));
        break;
    }

    char* key = scanCode_to_string(scanCode, isExtended);
    JsonObj* keycodeObj = init_json_string(strdup("Key"),strdup(key));
    
    list_add(rootList,countObj);
    list_add(rootList,typeObj);
    list_add(rootList,keycodeObj);
    list_add(rootList,timeObj);

    JsonObj* rootObt = init_json_object(NULL,rootList);
    log_event("Key Event JSON created");

    return rootObt;
}

JsonObj* json_from_mouse_event(WPARAM type, DWORD button, int x, int y, int time){
    eventCount++;
    list_t* rootList = new_list(1);
    JsonObj* countObj = init_json_int(strdup("EventNum"), eventCount);
    JsonObj* timeObj = init_json_int(strdup("Timestamp"),time);
    JsonObj* typeObj;
    JsonObj* eventObj;

    switch (type)
    {
        case WM_LBUTTONDOWN:
        case WM_RBUTTONDOWN:
        case WM_MBUTTONDOWN:
        case WM_XBUTTONDOWN:
            typeObj = init_json_string(strdup("EventType"), strdup("Mouse Button Press"));
            eventObj = init_json_string(strdup("Button"), strdup(mouse_button_input_to_string(button,button)));
            break;
        case WM_LBUTTONUP:
        case WM_RBUTTONUP:
        case WM_MBUTTONUP:
        case WM_XBUTTONUP:
            typeObj = init_json_string(strdup("EventType"), strdup("Mouse Button Release"));
            eventObj = init_json_string(strdup("Button"), strdup(mouse_button_input_to_string(button,button)));
            break;
        case WM_MOUSEMOVE:
            typeObj = init_json_string(strdup("EventType"), strdup("Mouse Movement"));
            list_t* positionList = new_list(2);
            JsonObj* xPos = init_json_int(strdup("X"),x);
            JsonObj* yPos = init_json_int(strdup("Y"),y);
            list_add(positionList, xPos);
            list_add(positionList, yPos);
            eventObj = init_json_object(strdup("Position"), positionList);
            break;
    }

    list_add(rootList,countObj);
    list_add(rootList,typeObj);
    list_add(rootList,eventObj);
    list_add(rootList,timeObj);

    JsonObj* rootObt = init_json_object(NULL,rootList);
    log_event("Mouse Event JSON created");

    return rootObt;
}   

JsonObj* json_from_mouse_wheel_event(int delta, int time){
    eventCount++;
    list_t* rootList = new_list(1);
    JsonObj* countObj = init_json_int(strdup("EventNum"), eventCount);
    JsonObj* timeObj = init_json_int(strdup("Timestamp"),time);

    JsonObj* typeObj = init_json_string(strdup("EventType"), strdup("Mouse Wheel Scroll"));
    
    list_t* dataList = new_list(3);
    JsonObj* amountObj = init_json_int(strdup("Scroll Amount"), abs(delta));
    list_add(dataList,amountObj);
    if(delta > 0){
        JsonObj* directionObj = init_json_string(strdup("Direction"), strdup("Up"));
        list_add(dataList,directionObj);
    }
    else
    {
        JsonObj* directionObj = init_json_string(strdup("Direction"), strdup("Down"));
        list_add(dataList,directionObj);
    }
    JsonObj* eventObj = init_json_object(strdup("Data"), dataList);

    list_add(rootList,countObj);
    list_add(rootList,typeObj);
    list_add(rootList,eventObj);
    list_add(rootList,timeObj);

    JsonObj* rootObt = init_json_object(NULL,rootList);

    log_event("Wheel Event JSON created");

    return rootObt;
}

char* json_to_string(JsonObj* obj){
    char* buffer;
    int size;
    switch (obj->type)
    {
    case J_INT:
        char int_value[12]; 
        snprintf(int_value, sizeof(int_value), "%d", obj->value.num);
        //2 extra quotes + colon + space
        size = strlen(obj->key) + strlen(int_value) + 4;
        buffer = malloc(sizeof(char) * size + 1);
        if (buffer == NULL)
        {
            printf("Failed to allocate buffer");
            return NULL;
        }
        snprintf(buffer, size + 1, "\"%s\": %s", obj->key, int_value);
        log_event("Converted Int Value");
        break;
    case J_BOOL:
        const char* bool_value = obj->value.boolean ? "true" : "false";
        //2 extra quotes + colon + space
        size = strlen(obj->key) + strlen(bool_value) + 4;
        buffer = malloc(sizeof(char) * size + 1);
        if (buffer == NULL)
        {
            printf("Failed to allocate buffer");
            return NULL;
        }
        snprintf(buffer, size + 1, "\"%s\": %s", obj->key, bool_value);
        log_event("Converted Bool Value");
        break;
    case J_STRING:
        //4 extra quotes + colon + space
        size = strlen(obj->key) + strlen(obj->value.s) + 6;
        buffer = malloc(sizeof(char) * size + 1);
        if (buffer == NULL)
        {
            printf("Failed to allocate buffer");
            return NULL;
        }
        snprintf(buffer, size + 1, "\"%s\": \"%s\"", obj->key, obj->value.s);
        log_event("Converted String Value");
        break;
    case J_ARRAY:
    {
        list_t* array = (list_t*)obj->value.ptr;
        char** items = malloc(array->count*sizeof(char*));
        //Allocate buffer
        size = 4; // [\n ]\n
        size += strlen(obj->key);
        for (int i = 0; i < array->count; i++) {
            items[i] = json_to_string((JsonObj*)array->data[i]);
                if (i != array->count - 1){
                    size += strlen(items[i]) + 2; // ",\n"
                }
                else
                {
                    size += strlen(items[i]) + 1; //\n
                }
        }
        buffer = malloc((size + 1) * sizeof(char));
        //Populate Buffer
        strcpy(buffer,"\"");
        strcat(buffer,obj->key);
        strcat(buffer,"\": [\n");
        for (int i = 0; i < array->count; i++) {
            strcat(buffer, items[i]);
            if (i != array->count - 1) 
            {
                strcat(buffer, ",\n");
            }
            else{
                strcat(buffer,"\n");
            }
            free(items[i]);
        }
        strcat(buffer, "]");
        free(items);
        log_event("Converted Array Value");
        break;
    }
    case JSON:{
        list_t* children = (list_t*)obj->value.ptr;
        char** items = malloc(children->count*sizeof(char*));
        //Allocate buffer
        size = 3; // {\n }
        if(obj->key != NULL){
            //Quotes, colon and space, newline
            size += strlen(obj->key) + 5;
        }
        for (int i = 0; i < children->count; i++) {
            items[i] = json_to_string((JsonObj*)children->data[i]);
            if (i != children->count - 1){
                    size += strlen(items[i]) + 2; // ",\n"
                }
                else
                {
                    size += strlen(items[i]) + 1; //\n
                }
        }
        buffer = malloc((size + 1) * sizeof(char));
        log_event_fmt("Converting JSON Value. Total Size: %d", size);
        //Populate Buffer
        if(obj->key != NULL){
            strcpy(buffer,"\"");
            strcat(buffer,obj->key);
            strcat(buffer,"\": \n{\n");
        }
        else{
            strcpy(buffer, "{\n");
        }
        for (int i = 0; i < children->count; i++) {
            strcat(buffer, items[i]);
            if (i != children->count - 1) 
            {
                strcat(buffer, ",\n");
            }
            else{
                strcat(buffer,"\n");
            }
            free(items[i]);
        }
        strcat(buffer, "}");
        free(items);
        log_event("Converted JSON Value");
        break;
    }
    default:
        return NULL;
    }
    return buffer;
}