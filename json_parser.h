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
    void* ptr;  //for arrays/JSON obj
} value;
} JsonObj;

//Wrapper for the two following functions. Consolidated into one neat function
list_t* read_json_into_objects(char* filename);

//Read from our json file into a buffer 
char* read_json_into_buffer(char* filename);

//Read from our buffer and make objects that we can get data from. Refer to JsonObj
list_t* read_buffer_into_objects(char* buffer, bool is_substring);

//Finds the starting index of the next string in the buffer
int find_next_string(char* buffer, int index);

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

//return the index of the next delimiter
int find_next_value(char* buffer, int index);

//Get the obj type of the json value
ObjType get_value_type(char* buffer, int index);

//Get the value as a void ptr
void* get_value(char* buffer, int* index, ObjType type);

//Returns the number of chars in the file. 
long get_filesize(FILE* file);

//Create and return new Json Object (JSON)
JsonObj* init_json_object(char* key, void* value);

//Create and return new Json Object (JARRAY)
JsonObj* init_json_array(char* key, void* value);

//Create and return new Json Object (J_BOOL)
JsonObj* init_json_bool(char* key, bool val);

//Create and return new Json Object (J_INT)
JsonObj* init_json_int(char* key, int val);

//Create and return new Json Object (J_STRING)
JsonObj* init_json_string(char* key, char* val);

//return the index of the comma separating the next object
int get_next_obj_index(char* buffer,int index);

//return the index of the ending brace for the array
int get_array_end(char* buffer, int index);

//return the index of the ending brace for the json object
int get_json_end(char* buffer, int index);

//print the json to stdout
void print_json(list_t* json_objects);

//Remove Leading and Trailing Whitespace in file
void trim_whitespace(char *str);

//look for nested json
int find_next_json(char* buffer, int index);

//frees a json object
void free_json(JsonObj* obj);

//given a key, get a list of nested json objects.
list_t* json_list_get(list_t* json, char* key);

//given a key, get a json object from a list of json objects.
JsonObj* json_obj_get(list_t* json_elements, char* key);

//Get value as an int
int get_int_value(char* buffer, int* index);

//Get value as a bool
bool get_bool_value(char* buffer, int* index);

//Get value as a string
char* get_string_value(char* buffer, int* index);

#endif