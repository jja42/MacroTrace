#include <stdio.h>
#include <stdlib.h>
#include <uiohook.h>

const char* keycode_to_string(uint16_t keycode) {
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


// Callback for keyboard events
void handle_keyboard_event(uiohook_event * const event) {
    switch (event->type) {
        case EVENT_KEY_PRESSED:
            printf("Key pressed: %s\n", keycode_to_string(event->data.keyboard.keycode));
            break;
        case EVENT_KEY_RELEASED:
            printf("Key Released: %s\n", keycode_to_string(event->data.keyboard.keycode));
            break;
        default:
            break;
    }
}

// Callback for mouse events
void handle_mouse_event(uiohook_event * const event) {
    switch (event->type) {
        case EVENT_MOUSE_PRESSED:
            printf("Mouse Button Pressed: %s at (%d, %d)\n",
                   button_to_mouse_input(event->data.mouse.button),
                   event->data.mouse.x,
                   event->data.mouse.y);
            break;
        case EVENT_MOUSE_RELEASED:
            printf("Mouse Button Released: %s at (%d, %d)\n",
                   button_to_mouse_input(event->data.mouse.button),
                   event->data.mouse.x,
                   event->data.mouse.y);
            break;
        case EVENT_MOUSE_MOVED:
            printf("Mouse Moved to (%d, %d)\n", event->data.mouse.x, event->data.mouse.y);
            break;
        default:
            break;
    }
}

// Main event dispatcher
void handle_event(uiohook_event * const event) {
    if (event->type >= EVENT_KEY_PRESSED && event->type <= EVENT_KEY_RELEASED) {
        handle_keyboard_event(event);
    } else if (event->type >= EVENT_MOUSE_PRESSED && event->type <= EVENT_MOUSE_MOVED) {
        handle_mouse_event(event);
    }
}

int main(void) {
    // Set the callback
    hook_set_dispatch_proc(handle_event);

    // Start the hook
    if (hook_run() != UIOHOOK_SUCCESS) {
        fprintf(stderr, "Failed to start hook!\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}