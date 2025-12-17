#include "macroevent.h"

WORD KeyNameToVK(char* key)
{
    if (!key) return 0;

    if (strcmp(key, "Esc") == 0) return VK_ESCAPE;
    if (strcmp(key, "Enter") == 0) return VK_RETURN;
    if (strcmp(key, "Tab") == 0) return VK_TAB;
    if (strcmp(key, "Space") == 0) return VK_SPACE;
    if (strcmp(key, "Shift") == 0) return VK_SHIFT;
    if (strcmp(key, "Ctrl") == 0) return VK_CONTROL;
    if (strcmp(key, "Alt") == 0) return VK_MENU;

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
    ZeroMemory(inputs, sizeof(INPUT) * 2);

    switch (event->type)
    {
    case KEY_PRESS:
    case KEY_RELEASE:
    {
        WORD vk = KeyNameToVK(event->data.ke.key);
        if (!vk) return 0;

        inputs[0].type = INPUT_KEYBOARD;
        inputs[0].ki.wVk = vk;

        if (event->type == KEY_RELEASE || event->data.ke.release)
            inputs[0].ki.dwFlags = KEYEVENTF_KEYUP;

        return 1;
    }

    case MOUSE_MOVE:
    {
        inputs[0].type = INPUT_MOUSE;
        inputs[0].mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
        inputs[0].mi.dx = event->data.me.x;
        inputs[0].mi.dy = event->data.me.y;
        return 1;
    }

    case MOUSE_CLICK:
    {
        DWORD downFlag = 0, upFlag = 0;

        switch (event->data.me.button)
        {
        case 0: downFlag = MOUSEEVENTF_LEFTDOWN;  upFlag = MOUSEEVENTF_LEFTUP;  break;
        case 1: downFlag = MOUSEEVENTF_RIGHTDOWN; upFlag = MOUSEEVENTF_RIGHTUP; break;
        case 2: downFlag = MOUSEEVENTF_MIDDLEDOWN;upFlag = MOUSEEVENTF_MIDDLEUP;break;
        }

        inputs[0].type = INPUT_MOUSE;
        inputs[0].mi.dwFlags = downFlag;

        inputs[1].type = INPUT_MOUSE;
        inputs[1].mi.dwFlags = upFlag;

        return 2;
    }

    case MOUSE_WHEEL:
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

InputEvent* json_to_input_event(JsonObj* object){

}

void PlayEvents(list_t* events)
{
    int lastTime = 0;

    for (int i = 0; i < events->count; i++)
    {
        InputEvent* event = (InputEvent*)events->data;
        int delay = event->timestamp - lastTime;
        if (delay > 0)
            Sleep(delay);

        INPUT inputs[2];
        int n = InputEventToSendInput(event, inputs);
        if (n > 0)
            SendInput(n, inputs, sizeof(INPUT));

        lastTime = event->timestamp;
    }
}


