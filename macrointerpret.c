#include "macrointerpret.h"
#include "list.h"
#include <stdlib.h>
#include <string.h>
#include "macrolog.h"

char* keycode_to_string(uint16_t keycode) {
    switch (keycode) {
        case VC_A: return "A";
        case VC_B: return "B";
        case VC_C: return "C";
        case VC_D: return "D";
        case VC_E: return "E";
        case VC_F: return "F";
        case VC_G: return "G";
        case VC_H: return "H";
        case VC_I: return "I";
        case VC_J: return "J";
        case VC_K: return "K";
        case VC_L: return "L";
        case VC_M: return "M";
        case VC_N: return "N";
        case VC_O: return "O";
        case VC_P: return "P";
        case VC_Q: return "Q";
        case VC_R: return "R";
        case VC_S: return "S";
        case VC_T: return "T";
        case VC_U: return "U";
        case VC_V: return "V";
        case VC_W: return "W";
        case VC_X: return "X";
        case VC_Y: return "Y";
        case VC_Z: return "Z";

        case VC_1: return "1";
        case VC_2: return "2";
        case VC_3: return "3";
        case VC_4: return "4";
        case VC_5: return "5";
        case VC_6: return "6";
        case VC_7: return "7";
        case VC_8: return "8";
        case VC_9: return "9";
        case VC_0: return "0";
        case VC_MINUS: return "-";
        case VC_EQUALS: return "=";

        case VC_ENTER: return "Enter";
        case VC_ESCAPE: return "Escape";
        case VC_BACKSPACE: return "Backspace";
        case VC_TAB: return "Tab";
        case VC_CAPS_LOCK: return "Caps Lock";
        case VC_SPACE: return "Space";

        case VC_SHIFT_L: return "Left Shift";
        case VC_SHIFT_R: return "Right Shift";
        case VC_CONTROL_L: return "Left Ctrl";
        case VC_CONTROL_R: return "Right Ctrl";
        case VC_ALT_L: return "Left Alt";
        case VC_ALT_R: return "Right Alt";

        case VC_BACKQUOTE: return "`";
        case VC_OPEN_BRACKET: return "[";
        case VC_CLOSE_BRACKET: return "]";
        case VC_BACK_SLASH: return "\\";
        case VC_SEMICOLON: return ";";
        case VC_QUOTE: return "\"";
        case VC_COMMA: return ",";
        case VC_PERIOD: return ".";
        case VC_SLASH: return "/";

        case VC_PRINTSCREEN: return "Print Screen";
        case VC_SCROLL_LOCK: return "Scroll Lock";
        case VC_PAUSE: return "Pause";
        case VC_LESSER_GREATER: return "< >";

        case VC_INSERT: return "Insert";                                
        case VC_DELETE: return "Keypad";                                
        case VC_HOME: return "Home";                                  
        case VC_END: return "End";                                 
        case VC_PAGE_UP: return "Page Up";         
        case VC_PAGE_DOWN: return "Page Down";
        case VC_CLEAR: return "Clear";                                

        case VC_UP: return "Up Arrow";
        case VC_DOWN: return "Down Arrow";
        case VC_LEFT: return "Left Arrow";
        case VC_RIGHT: return "Right Arrow";

        case VC_F1: return "F1";
        case VC_F2: return "F2";
        case VC_F3: return "F3";
        case VC_F4: return "F4";
        case VC_F5: return "F5";
        case VC_F6: return "F6";
        case VC_F7: return "F7";
        case VC_F8: return "F8";
        case VC_F9: return "F9";
        case VC_F10: return "F10";
        case VC_F11: return "F11";
        case VC_F12: return "F12";

        case VC_NUM_LOCK: return "Num Lock";                             
        case VC_KP_DIVIDE: return "Division";                             
        case VC_KP_MULTIPLY: return "Multiplication";                           
        case VC_KP_SUBTRACT: return "Subtraction";                          
        case VC_KP_EQUALS: return "Keypad Equals";                            
        case VC_KP_ADD: return "Addition";                                
        case VC_KP_ENTER: return "Keypad Enter";                              
        case VC_KP_SEPARATOR: return "Keypad Separator";                        

        case VC_KP_1: return "Keypad 1";
        case VC_KP_2: return "Keypad 2";
        case VC_KP_3: return "Keypad 3";
        case VC_KP_4: return "Keypad 4";
        case VC_KP_5: return "Keypad 5";
        case VC_KP_6: return "Keypad 6";
        case VC_KP_7: return "Keypad 7";
        case VC_KP_8: return "Keypad 8";
        case VC_KP_9: return "Keypad 9";
        case VC_KP_0: return "Keypad 0";

        case VC_KP_END: return "Keypad End";
        case VC_KP_DOWN: return "Keypad Down";
        case VC_KP_PAGE_DOWN: return "Keypad Page Down";
        case VC_KP_LEFT: return "Keypad Left";
        case VC_KP_CLEAR: return "Keypad Clear";
        case VC_KP_RIGHT: return "Keypad Right";
        case VC_KP_HOME: return "Keypad Home";
        case VC_KP_UP: return "Keypad Up";
        case VC_KP_PAGE_UP: return "Keypad Page Up";
        case VC_KP_INSERT: return "Keypad Insert";
        case VC_KP_DELETE: return "Keypad Delete";  

        case VC_META_L: return "Left Command/Windows";
        case VC_META_R: return "Right Command/Windows";
        case VC_CONTEXT_MENU: return "Context";

        default: return "Unknown";
    }
}


char* button_to_mouse_input(uint16_t button)
{
    switch (button)
    {
    case MOUSE_BUTTON1: return "Left Click";
    case MOUSE_BUTTON2: return "Right Click";
    case MOUSE_BUTTON3: return "Scroll Wheel Button";
    case MOUSE_BUTTON4: return "Extra Mouse Button";
    case MOUSE_BUTTON5: return "Extra Mouse Button 2";

    default: return "Unknown";
    }
}

JsonObj* json_from_keyboard_event(int time, event_type type, int keycode){
    list_t* rootList = new_list(1);
    JsonObj* timeObj = init_json_int(strdup("Timestamp"),time);
    JsonObj* typeObj;

    switch (type)
    {
    case EVENT_KEY_PRESSED:
        typeObj = init_json_string(strdup("EventType"), strdup("Key Press"));
        break;
    case EVENT_KEY_RELEASED:
        typeObj = init_json_string(strdup("EventType"), strdup("Key Release"));
        break;
    default:
        typeObj = init_json_string(strdup("EventType"), strdup("Unknown Event"));
        break;
    }

    char* key = keycode_to_string(keycode);
    JsonObj* keycodeObj = init_json_string(strdup("Key"),strdup(key));
    
    list_add(rootList,typeObj);
    list_add(rootList,keycodeObj);
    list_add(rootList,timeObj);

    JsonObj* rootObt = init_json_object(NULL,rootList);
    log_event("Key Event JSON created");

    return rootObt;
}

JsonObj* json_from_mouse_event(int time, event_type type, int button, int  x, int  y){
    list_t* rootList = new_list(1);
    JsonObj* timeObj = init_json_int(strdup("Timestamp"),time);
    JsonObj* typeObj;
    JsonObj* eventObj;

    switch (type)
    {
    case EVENT_MOUSE_PRESSED:
        typeObj = init_json_string(strdup("EventType"), strdup("Mouse Button Press"));
        eventObj = init_json_string(strdup("Button"), strdup(button_to_mouse_input(button)));
        break;
    case EVENT_MOUSE_RELEASED:
        typeObj = init_json_string(strdup("EventType"), strdup("Mouse Button Release"));
        eventObj = init_json_string(strdup("Button"), strdup(button_to_mouse_input(button)));
        break;
    case EVENT_MOUSE_MOVED:
        typeObj = init_json_string(strdup("EventType"), strdup("Mouse Movement"));
        list_t* positionList = new_list(2);
        JsonObj* xPos = init_json_int(strdup("X"),x);
        JsonObj* yPos = init_json_int(strdup("Y"),y);
        list_add(positionList, xPos);
        list_add(positionList, yPos);
        eventObj = init_json_object(strdup("Position"), positionList);
        break;
    }

    list_add(rootList,typeObj);
    list_add(rootList,eventObj);
    list_add(rootList,timeObj);

    JsonObj* rootObt = init_json_object(NULL,rootList);
    log_event("Mouse Event JSON created");

    return rootObt;
}   

JsonObj* json_from_mouse_wheel_event(int time, event_type type, int amount, int  rotation, int  direction){
    list_t* rootList = new_list(1);
    JsonObj* timeObj = init_json_int(strdup("Timestamp"),time);

    JsonObj* typeObj = init_json_string(strdup("EventType"), strdup("Mouse Wheel Scroll"));
    
    list_t* dataList = new_list(3);
    JsonObj* amountObj = init_json_int(strdup("Scroll Amount"), amount);
    JsonObj* directionObj = init_json_int(strdup("Direction"), direction);
    JsonObj* rotationObj = init_json_int(strdup("Rotation"), rotation);
    list_add(dataList,amountObj);
    list_add(dataList,directionObj);
    list_add(dataList,rotationObj);
    JsonObj* eventObj = init_json_object(strdup("Data"), dataList);

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
        log_event("Converting JSON Value");
        list_t* children = (list_t*)obj->value.ptr;
        char** items = malloc(children->count*sizeof(char*));
        log_event("Allocated Items");
        log_event_fmt("Num Children: %d", children->count);
        //Allocate buffer
        size = 3; // {\n }
        if(obj->key != NULL){
            //Quotes, colon and space
            size += strlen(obj->key) + 4;
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
        log_event("Allocating Buffer");
        buffer = malloc((size + 1) * sizeof(char));
        log_event_fmt("JSON Total Size: %d", size);
        //Populate Buffer
        if(obj->key != NULL){
            strcpy(buffer,"\"");
            strcat(buffer,obj->key);
            strcat(buffer,"\": \n{");
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