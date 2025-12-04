#ifndef LIST_H
#define LIST_H

typedef struct List {
  int count;
  int capacity;
  void **data;
} list_t;

//Makes a new list. all spots are null. NEVER SET THE CAPACITY TO 0
list_t* new_list(int capacity);

//adds a value to the first non null space
void list_add(list_t* list, void* item);

//replace a value in a list with another
void list_replace(list_t* list, int index, void* new);

//responsible memory management.
void free_list(list_t* list);

//remove all values from the list
void clear_list(list_t* list);

//resizes a list
void resize_list(list_t* list);

//add two lists together
list_t* list_join(list_t* list1, list_t* list2);

#endif