#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include "list.h"
#include <stdio.h>
#include <stdbool.h>

typedef enum {
J_INT,
J_STRING,
J_ARRAY,
J_BOOL,
JSON,
NONE
} ObjType;

typedef struct {
char* key;
ObjType type;
union {
    char* s;
    int num;
    bool boolean;
    list_t* objects; //JSON
    void* ptr; //Unused Ptr for Generic Data
} value;
} JsonObj;

//Wrapper for the two following functions. Consolidated into one neat function
list_t* read_json_into_objects(char* filename);

//Read from our json file into a buffer 
char* read_json_into_buffer(char* filename);

//Read from our buffer and make objects that we can get data from. Refer to JsonObj
list_t* read_buffer_into_objects(char* buffer);

//return the string given a starting index
char* parse_string(char* buffer, int* index);

//return the int given a starting index
int parse_int(char* buffer, int* index);

//return the bool given a starting index
bool parse_bool(char* buffer, int* index);

//return the array given a starting index
list_t* parse_array(char* buffer, int* index);

//return the json given a starting index
list_t* parse_json(char* buffer, int* index);

//moves the index pointer just beyond the next instance of a specified char
void find_next(char* buffer, int* index, char c);

//moves through the buffer until next non-whitepsace char
void skip_whitespace(char* buffer, int* index);

//Get the obj type of the json value
ObjType get_value_type(char* buffer, int index);

//Returns the number of chars in the file. 
long get_filesize(FILE* file);

//Using type, initialize the corresponding json object type and parse the correct value from buffer at index
JsonObj* init_json_from_buffer(ObjType type, char* key, char* buffer, int* index);

//Create and return new Json Object (JSON)
JsonObj* init_json_object(char* key, list_t* value);

//Create and return new Json Object (JARRAY)
JsonObj* init_json_array(char* key, list_t* value);

//Create and return new Json Object (J_BOOL)
JsonObj* init_json_bool(char* key, bool val);

//Create and return new Json Object (J_INT)
JsonObj* init_json_int(char* key, int val);

//Create and return new Json Object (J_STRING)
JsonObj* init_json_string(char* key, char* val);

//print the json to stdout
void print_json(list_t* json_objects);

//frees a json object
void free_json(JsonObj* obj);

//given a key, get a list of nested json objects.
list_t* json_list_get(list_t* json, char* key);

//given a key, get a json object from a list of json objects.
JsonObj* json_obj_get(list_t* json_elements, char* key);

#endif