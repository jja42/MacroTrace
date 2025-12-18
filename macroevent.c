#include "macroevent.h"
#include "macrolog.h"

KeyEvent ParseKeyboardEvent(list_t* eventData){
    KeyEvent ke;

    JsonObj* keyInputObject = json_obj_get(eventData,"Key");

    ke.key = _strdup(keyInputObject->value.s);

    JsonObj* eventTypeObject = json_obj_get(eventData,"EventType");

    char* eventTypeString = eventTypeObject->value.s;

    if (strcmp(eventTypeString, "Key Press") == 0) ke.release = false;
    if (strcmp(eventTypeString, "Key Release") == 0) ke.release = true;

    return ke;
}

MouseEvent ParseMouseEvent(list_t* eventData){
    MouseEvent me;

    JsonObj* buttonInputObject = json_obj_get(eventData,"Button");

    me.button = buttonInputObject->value.s;

    JsonObj* eventTypeObject = json_obj_get(eventData,"EventType");

    char* eventTypeString = eventTypeObject->value.s;

    if (strcmp(eventTypeString, "Mouse Button Press") == 0) me.release = false;
    if (strcmp(eventTypeString, "Mouse Button Release") == 0) me.release = true;

    return me;
}

MouseEvent ParseMouseMoveEvent(list_t* eventData){
    MouseEvent me;

    list_t* positionData = json_list_get(eventData,"Position");

    JsonObj* xData = json_obj_get(positionData,"X");
    JsonObj* yData = json_obj_get(positionData,"Y");

    me.x = xData->value.num;
    me.y = yData->value.num;

    return me;
}

WheelEvent ParseWheelEvent(list_t* eventData){
    WheelEvent we;

    list_t* scrollData = json_list_get(eventData,"Data");

    JsonObj* scrollAmount = json_obj_get(scrollData,"Scroll Amount");
    JsonObj* direction = json_obj_get(scrollData,"Direction");

    we.amount = scrollAmount->value.num;

    char* directionString = direction->value.s;
    
    if (strcmp(directionString, "Up") == 0) we.up = true;
    if (strcmp(directionString, "Down") == 0) we.up = false;

    return we;
}

EventType ParseEventType(char* eventTypeString){
    if (strcmp(eventTypeString, "Key Press") == 0) return KEY_INPUT_EVENT;
    if (strcmp(eventTypeString, "Key Release") == 0) return KEY_INPUT_EVENT;
    if (strcmp(eventTypeString, "Mouse Button Press") == 0) return MOUSE_INPUT_EVENT;
    if (strcmp(eventTypeString, "Mouse Button Release") == 0) return MOUSE_INPUT_EVENT;
    if (strcmp(eventTypeString, "Mouse Movement") == 0) return MOUSE_MOVE_EVENT;
    if (strcmp(eventTypeString, "Mouse Wheel Scroll") == 0) return MOUSE_WHEEL_EVENT;
}

DWORD ParseMouseButton(char* mouseButtonString, bool release){
    if (strcmp(mouseButtonString, "Left Click") == 0){
        if(release){
            return MOUSEEVENTF_LEFTUP;
        }
        return MOUSEEVENTF_LEFTDOWN;
    }
    if (strcmp(mouseButtonString, "Right Click") == 0){
        if(release){
            return MOUSEEVENTF_RIGHTUP;
        }
        return MOUSEEVENTF_RIGHTDOWN;
    }
    if (strcmp(mouseButtonString, "Scroll Wheel Click") == 0){
        if(release){
            return MOUSEEVENTF_MIDDLEUP;
        }
        return MOUSEEVENTF_MIDDLEDOWN;
    }
    if (strcmp(mouseButtonString, "Extra Mouse Button 1 Click") == 0){
        if(release){
            return MOUSEEVENTF_XUP;
        }
        return MOUSEEVENTF_XDOWN;
    }
    if (strcmp(mouseButtonString, "Extra Mouse Button 2 Click") == 0){
        if(release){
            return MOUSEEVENTF_XUP;
        }
        return MOUSEEVENTF_XDOWN;
    }

    return 0;
}

WORD KeyNameToVK(char* key)
{
    if (!key) return 0;

    if (strcmp(key, "Esc") == 0) return VK_ESCAPE;
    if (strcmp(key, "Enter") == 0) return VK_RETURN;
    if (strcmp(key, "Tab") == 0) return VK_TAB;
    if (strcmp(key, "Caps Lock") == 0) return VK_CAPITAL;
    if (strcmp(key, "Space") == 0) return VK_SPACE;
    if (strcmp(key, "Shift") == 0) return VK_LSHIFT;
    if (strcmp(key, "Right Shift") == 0) return VK_RSHIFT;
    if (strcmp(key, "Ctrl") == 0) return VK_LCONTROL;
    if (strcmp(key, "Right Ctrl") == 0) return VK_RCONTROL;
    if (strcmp(key, "Left Windows") == 0) return VK_LWIN;
    if (strcmp(key, "Right Windows") == 0) return VK_RWIN;
    if (strcmp(key, "Application") == 0) return VK_APPS;
    if (strcmp(key, "Alt") == 0) return VK_LMENU;
    if (strcmp(key, "Right Alt") == 0) return VK_RMENU;
    if (strcmp(key, "F1") == 0) return VK_F1;
    if (strcmp(key, "F2") == 0) return VK_F2;
    if (strcmp(key, "F3") == 0) return VK_F3;
    if (strcmp(key, "F4") == 0) return VK_F4;
    if (strcmp(key, "F5") == 0) return VK_F5;
    if (strcmp(key, "F6") == 0) return VK_F6;
    if (strcmp(key, "F7") == 0) return VK_F7;
    if (strcmp(key, "F8") == 0) return VK_F8;
    if (strcmp(key, "F9") == 0) return VK_F9;
    if (strcmp(key, "F10") == 0) return VK_F10;
    if (strcmp(key, "F11") == 0) return VK_F11;
    if (strcmp(key, "F12") == 0) return VK_F12;
    if (strcmp(key, "Backspace") == 0) return VK_BACK;
    if (strcmp(key, "Prnt Scrn") == 0) return VK_PRINT;
    if (strcmp(key, "Scroll Lock") == 0) return VK_SCROLL;
    if (strcmp(key, "Pause") == 0) return VK_PAUSE;
    if (strcmp(key, "Insert") == 0) return VK_INSERT;
    if (strcmp(key, "Home") == 0) return VK_HOME;
    if (strcmp(key, "Page Up") == 0) return VK_PRIOR;
    if (strcmp(key, "Page Down") == 0) return VK_NEXT;
    if (strcmp(key, "Delete") == 0) return VK_DELETE;
    if (strcmp(key, "End") == 0) return VK_END;
    if (strcmp(key, "Num Lock") == 0) return VK_NUMLOCK;
    if (strcmp(key, "Num /") == 0) return VK_DIVIDE;
    if (strcmp(key, "Num *") == 0) return VK_MULTIPLY;
    if (strcmp(key, "Num -") == 0) return VK_SUBTRACT;
    if (strcmp(key, "Num +") == 0) return VK_ADD;
    if (strcmp(key, "Num Enter") == 0) return VK_RETURN;
    if (strcmp(key, "Num Del") == 0) return VK_DECIMAL;
    if (strcmp(key, "Num 0") == 0) return VK_NUMPAD0;
    if (strcmp(key, "Num 1") == 0) return VK_NUMPAD1;
    if (strcmp(key, "Num 2") == 0) return VK_NUMPAD2;
    if (strcmp(key, "Num 3") == 0) return VK_NUMPAD3;
    if (strcmp(key, "Num 4") == 0) return VK_NUMPAD4;
    if (strcmp(key, "Num 5") == 0) return VK_NUMPAD5;
    if (strcmp(key, "Num 6") == 0) return VK_NUMPAD6;
    if (strcmp(key, "Num 7") == 0) return VK_NUMPAD7;
    if (strcmp(key, "Num 8") == 0) return VK_NUMPAD8;
    if (strcmp(key, "Num 9") == 0) return VK_NUMPAD9;
    if (strcmp(key, "Up") == 0) return VK_UP;
    if (strcmp(key, "Left") == 0) return VK_LEFT;
    if (strcmp(key, "Right") == 0) return VK_RIGHT;
    if (strcmp(key, "Down") == 0) return VK_DOWN;
    if (strcmp(key, "Clear") == 0) return VK_CLEAR;


    // Single character (A–Z, 0–9, etc.)
    if (strlen(key) == 1)
    {
        SHORT vk = VkKeyScanA(key[0]);
        if (vk != -1)
            return LOBYTE(vk);
    }

    return 0;
}

int InputEventToSendInput(InputEvent* event, INPUT* inputs)
{
    switch (event->type)
    {
        case KEY_INPUT_EVENT:
        {
            WORD vk = KeyNameToVK(event->data.ke.key);
            if (!vk) return 0;

            inputs[0].type = INPUT_KEYBOARD;
            inputs[0].ki.wScan = MapVirtualKey(vk, MAPVK_VK_TO_VSC);
            inputs[0].ki.dwFlags = KEYEVENTF_SCANCODE;

            if (event->data.ke.release)
                inputs[0].ki.dwFlags |= KEYEVENTF_KEYUP;

            return 1;
        }

        case MOUSE_MOVE_EVENT:
        {
            inputs[0].type = INPUT_MOUSE;
            inputs[0].mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
            int screenW = GetSystemMetrics(SM_CXSCREEN) - 1;
            int screenH = GetSystemMetrics(SM_CYSCREEN) - 1;

            inputs[0].mi.dx = (event->data.me.x * 65535) / screenW;
            inputs[0].mi.dy = (event->data.me.y * 65535) / screenH;

            return 1;
        }

        case MOUSE_INPUT_EVENT:
        {
            DWORD flag = ParseMouseButton(event->data.me.button,event->data.me.release);
            inputs[0].type = INPUT_MOUSE;
            inputs[0].mi.dwFlags = flag;

            return 1;
        }
        case MOUSE_WHEEL_EVENT:
        {
            inputs[0].type = INPUT_MOUSE;
            inputs[0].mi.dwFlags = MOUSEEVENTF_WHEEL;
            inputs[0].mi.mouseData =
                event->data.we.up ? event->data.we.amount : -event->data.we.amount;

            return 1;
        }
    }

    return 0;
}

InputEvent* json_to_input_event(JsonObj* event_json){
    InputEvent* event = malloc(sizeof(InputEvent));
    list_t* eventData = event_json->value.objects;
    JsonObj* eventTypeObject = json_obj_get(eventData,"EventType");
    EventType eventType = ParseEventType(eventTypeObject->value.s);

    event->type = eventType;
    
    switch (eventType)
    {
        case KEY_INPUT_EVENT:
            event->data.ke = ParseKeyboardEvent(eventData);
            break;
        case MOUSE_MOVE_EVENT:
            event->data.me = ParseMouseMoveEvent(eventData);
            break;
        case MOUSE_INPUT_EVENT:
            event->data.me = ParseMouseEvent(eventData);
            break;
        case MOUSE_WHEEL_EVENT:
            event->data.we = ParseWheelEvent(eventData);
            break;
        default:
            break;
    }

    JsonObj* timestampObject = json_obj_get(eventData,"Timestamp");
    event->timestamp = timestampObject->value.num;

    log_event("Event Parsed");

    return event;
}



void PlayEvents(list_t* events)
{
    printf("Playing Events\n");
    
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);

    LARGE_INTEGER start, now;
    QueryPerformanceCounter(&start);

    int lastTime = 0;

    for (int i = 0; i < events->count; i++)
    {
        InputEvent* event = (InputEvent*)events->data[i];
        int delay = event->timestamp - lastTime;

        if (delay > 0)
        {
            do {
                QueryPerformanceCounter(&now);
            } while (((now.QuadPart - start.QuadPart) * 1000 / freq.QuadPart) < event->timestamp);
        }

        INPUT inputs[1] = {0};
        int n = InputEventToSendInput(event, inputs);
        if (n > 0)
            SendInput(n, inputs, sizeof(INPUT));

        lastTime = event->timestamp;
    }
    printf("Finished Playing Events\n");
}



