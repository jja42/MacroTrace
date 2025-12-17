#ifndef MACROEVT_H
#define MACROEVT_H

#include <windows.h>
#include "json_parser.h"

typedef enum {
MOUSE_CLICK,
MOUSE_MOVE,
KEY_PRESS,
KEY_RELEASE,
MOUSE_WHEEL
} EventType;

typedef struct {
char* key;
bool release;
} KeyEvent;

typedef struct {
int x;
int y;
int button;
bool release;
bool click;
} MouseEvent;

typedef struct {
bool up;
int amount;
} WheelEvent;

typedef struct {
EventType type;
int timestamp;
union {
    KeyEvent ke;
    MouseEvent me;
    WheelEvent we;
} data;
} InputEvent;


InputEvent* json_to_input_event(JsonObj* object);

int InputEventToSendInput(InputEvent* ev, INPUT* inputs);

WORD KeyNameToVK(char* key);

void PlayEvents(list_t* events);

#endif