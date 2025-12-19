#ifndef MACROEVT_H
#define MACROEVT_H

#include <windows.h>
#include "json_parser.h"

typedef enum {
MOUSE_INPUT_EVENT,
MOUSE_MOVE_EVENT,
KEY_INPUT_EVENT,
MOUSE_WHEEL_EVENT
} EventType;

typedef struct {
char* key;
bool release;
} KeyEvent;

typedef struct {
int x;
int y;
char* button;
bool release;
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


InputEvent* json_to_input_event(JsonObj* event_json);

int InputEventToSendInput(InputEvent* ev, INPUT* inputs);

WORD KeyNameToVK(char* key);

void PlayEvents(list_t* events);

EventType ParseEventType(char* eventTypeString);

KeyEvent ParseKeyboardEvent(list_t* eventData);

MouseEvent ParseMouseMoveEvent(list_t* eventData);

MouseEvent ParseMouseEvent(list_t* eventData);

WheelEvent ParseWheelEvent(list_t* eventData);
#endif