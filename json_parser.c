#include "json_parser.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "macrolog.h"

list_t* read_json_into_objects(char* filename){
    //read the file
    char* buffer = read_json_into_buffer(filename);
    //transform the file's contents into json objects
    if(buffer == NULL){
        return NULL;
    }
    list_t* objs = read_buffer_into_objects(buffer);
    free(buffer);
    return objs;
}

char* read_json_into_buffer(char* filepath){
    //Open File
    FILE *file;
    file = fopen(filepath,"r");

    //Check File
    if (file == NULL) {
        printf("File at %s could not be opened.\n", filepath);
        return NULL;
    }

    //Get Size
    long size = get_filesize(file);

    //Allocate a Buffer to Check
    char* buffer = malloc(sizeof(char) * (size + 1));

    //Error handling
    if (buffer == NULL)
    {
        printf("Failed to allocate buffer for file at %s\n",filepath);
        fclose(file);
        return NULL;
    }

    //Read into the buffer
    fread(buffer, sizeof(char), size, file);

    buffer[size] = '\0';

    //Close File
    fclose(file);
    return buffer;
}

list_t* read_buffer_into_objects(char* buffer){
    int index = 0;
    skip_whitespace(buffer, &index);

    JsonObj* root;

    if (buffer[index] == '{')
    {
        root = init_json_object(NULL, parse_json(buffer, &index));
    }
    else if (buffer[index] == '['){
        root = init_json_array(NULL,parse_array(buffer, &index));
    }
    else {
        printf("Invalid JSON root\n");
        return NULL;
    }

    return root->value.objects;
}

void skip_whitespace(char* buffer, int* index) {
    while (isspace(buffer[*index])){
        (*index)++;
    }
}

void find_next(char* buffer, int* index, char c) {
    skip_whitespace(buffer, index);
    if (buffer[*index] != c) {
        printf("\n ERROR: Expected '%c' at index %d\n", c, *index);
        exit(1);
    }
    (*index)++;
}

list_t* parse_json(char* buffer, int* index) {
    find_next(buffer, index, '{');

    list_t* objects = new_list(1);

    skip_whitespace(buffer, index);

    while (buffer[*index] != '}') {
        //get key
        char* key = parse_string(buffer, index);
        log_event_fmt("Key Found: %s\n", key);

        //find value
        find_next(buffer, index, ':');
        skip_whitespace(buffer,index);

        ObjType type = get_value_type(buffer,*index);
        JsonObj* object = init_json_from_buffer(type,key, buffer, index);
        list_add(objects, object);

        skip_whitespace(buffer, index);
        if (buffer[*index] == ',') {
            (*index)++;
            skip_whitespace(buffer, index);
        } else {
            break;
        }
    }

    find_next(buffer, index, '}');
    return objects;
}

list_t* parse_array(char* buffer, int* index) {
    find_next(buffer, index, '[');

    list_t* objects = new_list(1);

    skip_whitespace(buffer, index);

    while (buffer[*index] != ']') {
        //get element type in array
        ObjType type = get_value_type(buffer,*index);
        JsonObj* object = init_json_from_buffer(type, NULL, buffer, index);
        
        list_add(objects, object);

        skip_whitespace(buffer, index);

        if (buffer[*index] == ',') {
            (*index)++;
            skip_whitespace(buffer, index);
        } else {
            break;
        }
    }

    find_next(buffer, index, ']');
    return objects;
}

ObjType get_value_type(char* buffer, int index){
    switch (buffer[index])
    {
    case '\"':
        return J_STRING;
    case '{':
        return JSON;
    case '[':
        return J_ARRAY;
    default:
        if(isdigit(buffer[index])){
            return J_INT;
        }
        if(strncmp(buffer + index, "true", 4) == 0 || strncmp(buffer + index, "false", 5) == 0){
            return J_BOOL;
        }
        return NONE;
    }
}

JsonObj* init_json_from_buffer(ObjType type, char* key, char* buffer, int* index){
    switch (type)
    {
    case J_ARRAY:
        log_event("Initializing J_ARRAY\n");
        return init_json_array(key, parse_array(buffer, index));
    case JSON:
        log_event("Initializing JSON\n");
        return init_json_object(key, parse_json(buffer,index));
    case J_INT:
        log_event("Initializing J_INT\n");
        return init_json_int(key, parse_int(buffer, index));
    case J_BOOL:
        log_event("Initializing J_BOOL\n");
        return init_json_bool(key,parse_bool(buffer, index));
    case J_STRING:
        log_event("Initializing J_STRING\n");
        return init_json_string(key,parse_string(buffer,index));
    default:
        break;
    }
}

JsonObj* init_json_object(char* key, list_t* value){
    JsonObj* obj = malloc(sizeof(JsonObj));
    obj->key = key;
    obj->value.objects = value;
    obj->type = JSON;
    return obj;
}

JsonObj* init_json_array(char* key, list_t* value){
    JsonObj* obj = malloc(sizeof(JsonObj));
    obj->key = key;
    obj->value.objects = value;
    obj->type = J_ARRAY;
    return obj;
}

JsonObj* init_json_bool(char* key, bool val){
    JsonObj* obj = malloc(sizeof(JsonObj));
    obj->key = key;
    obj->value.boolean = val;
    obj->type = J_BOOL;
    return obj;
}

JsonObj* init_json_string(char* key, char* val){
    JsonObj* obj = malloc(sizeof(JsonObj));
    obj->key = key;
    obj->value.s = val;
    obj->type = J_STRING;
    return obj;
}

JsonObj* init_json_int(char* key, int val){
    JsonObj* obj = malloc(sizeof(JsonObj));
    obj->key = key;
    obj->value.num = val;
    obj->type = J_INT;
    return obj;
}

char* parse_string(char* buffer, int* index){
    //Exclude beginning quotation mark
    find_next(buffer, index, '"');   

    int start = *index;

    //Find End of String
    while (buffer[*index] != '"') {
        (*index)++;
    }

    int length = *index - start;

    //Allocate a string to hold the value
    char* string = malloc(sizeof(char) * (length + 1));

    //Error handling
    if (string == NULL)
    {
        printf("Failed to allocate string.\n");
        return NULL;
    }

    //Copy from the buffer into our string
    //Excludes the starting quotation mark
    memcpy(string,buffer + start,length);

    //Replace \\n with \n
    bool contains_newline = false;
    do{
        int index = -1;
        contains_newline = false;
        for (int i = 0; i < length; i++) {
            if (string[index] == '\\' && string[i+1] == 'n') {
                contains_newline = true;
                index = i;
                break;
            }
        }

        if(contains_newline){
            string[index] = '\n';
            for (int s = index+1; s < length; s++) {
                string[s] = string[s+1];
            }
            length -= 1;
        }

    } while (contains_newline);
    

    //Add a terminator
    string[length] = '\0';

    find_next(buffer, index, '"');

    return string;
}

int parse_int(char* buffer, int* index){

    int i;

    //get end of int
    int end_index = *index;
    while (isdigit(buffer[end_index])) end_index++;

    int length = end_index - *index;

    //allocate a string
    char* str = malloc(sizeof(char) * length + 1);

    if (str == NULL) {
        printf("Failed to allocate for int conversion.\n");
        return 0;
    }

    //copy from buffer into string
    memcpy(str, buffer + *index, length);

    str[length] = '\0';

    //convert string value into int
    i = atoi(str);

    //update index
    *index = end_index;

    free(str);

    return i;
}

bool parse_bool(char* buffer, int* index){
    bool b;

    //manual string comparison for true/false
    if(strncmp(buffer + *index, "true", 4) == 0){
        b = true;
        *index += 4;
        return b;
    } 
    if(strncmp(buffer + *index, "false", 5) == 0){
        b = false;
        *index += 5;
        return b;
    }
    return false;
}

long get_filesize(FILE *file){
//Use fseek to get to the end of the file
fseek(file, 0, SEEK_END);

//ftell gives us the last index
long filesize = ftell(file);

//undo our seeking by returning the internal position index to the start
rewind(file);

return filesize;
}

void print_json(list_t* json_objects){
    //loop through objects
    for(int i = 0; i<json_objects->count; i++){
        //ignore NULL
        if(json_objects->data[i] != NULL){

            JsonObj* object = (JsonObj*)json_objects->data[i];
        
            char* key = object->key;

            switch (object->type)
            {
            case J_STRING:
                char* value = object->value.s;
                printf("%s : %s", key, value);
                break;

            case J_INT:
                int val = object->value.num;
                printf("%s : %d", key, val);
                break;

            case J_BOOL:
                bool b = object->value.boolean;
                printf("%s : %d", key, b);
                break;

            //print [ then print each object and then print ]
            case J_ARRAY:
                printf("%s : [\n", key);
                print_json(object->value.objects);
                printf("]");
                break;

            //print { then print each object and then print }
            case JSON:
                if(key != NULL){
                    printf("%s:\n{\n",key);
                }
                else{
                    printf("Json Obj:\n{\n");
                }
                print_json(object->value.objects);
                printf("}");
                break;
        
            default:
                break;
            }
            //if not last item, add comma and newline
            if(i< json_objects->count - 1){
                printf(",\n");
            }
            //otherwise just newline
            else{
                printf("\n");
            }
        }
    }
}

void free_json(JsonObj* obj){
    //free our key which is a dynamically allocated string
    free(obj->key);
    log_event("Freed Key");
    //if we are a json holder or an array we have multiple child objects
    //we must loop through our list and free recursively
    if(obj->type == JSON || obj->type == J_ARRAY){
        list_t* l = (list_t*)obj->value.ptr;
        for(int i = 0; i < l->capacity; i++){
            if(l->data[i] != NULL){
                free_json(l->data[i]);
            }
        }
        free_list(l);
    }
    else{
        switch (obj->type)
        {
        case J_STRING:
            log_event("Freeing String");
            free(obj->value.s);
        default:
            break;
        }
    }
    log_event("Freed Object");
    free(obj);
}


list_t* json_list_get(list_t* json, char* key){
    //go through the list provided
    for(int j = 0; j <json->capacity; j++){
        if(json->data[j] != NULL){
            //cast to JsonObj and check if key matches string
            JsonObj* object = (JsonObj*)json->data[j];
            if(strcmp(object->key, key) == 0){
                return (list_t*)object->value.objects;
            }
        }
    }
    return NULL;
}

JsonObj* json_obj_get(list_t* json_objects, char* key){
    //go through the list provided
    for(int j = 0; j <json_objects->capacity; j++){
        if(json_objects->data[j] != NULL){
            //cast to JsonObj and check if key matches string
            JsonObj* object = (JsonObj*)json_objects->data[j];
            if(strcmp(object->key, key) == 0){
                return object;
            }
        }
    }
    printf("Could Not Find Item Named: %s in JSON List\n", key);
    return NULL;
}