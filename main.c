#include "macrotrace.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "macrosave.h"
#include "macrolog.h"
#include <windows.h>
#include <time.h>
#include <string.h>
#include "macroload.h"

HHOOK keyboardHook;
HHOOK mouseHook;

typedef enum {
RECORD,
REPLAY,
NONE
} MacroMode;

MacroMode selectedMode;

MacroMode parse_mode(char* mode);

int main(void) {

    printf("Welcome to MacroTrace.\n");
    printf("This Program will allow you to Record and Replay Macros.\n");
    printf("Please first select which Mode you would like to use:\n");
    printf("Enter 1 or Record for Recording Mode. Enter 2 or Replay for Replay Mode\n");
    printf("Use Ctrl + C at any time to Exit\n\n");

    selectedMode = NONE;
    char mode[100];
    char filename[100];

    while(selectedMode == NONE){
        scanf("%s", mode);
        selectedMode = parse_mode(mode);
        if(selectedMode == NONE){
            printf("Invalid Mode Selection. Please select a valid Mode.\n");
        }
    }

    if(selectedMode == RECORD)
    {
        printf("\nRecording Mode Selected.\n");
        printf("Press Any Keyboard Button to Begin Recording.\n");
        printf("Press Escape Twice in a Row to End Recording.\n");

        keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
        mouseHook    = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, NULL, 0);

        if (!keyboardHook || !mouseHook) {
            printf("Failed to install hooks.\n");
            return 1;
        }

        //Standard Windows message loop
        MSG msg;
        while (GetMessage(&msg, NULL, 0, 0)) {}

        UnhookWindowsHookEx(keyboardHook);
        UnhookWindowsHookEx(mouseHook);

        write_temp_trace_file();

        printf("Recording Stopped.\n");
        log_event("Done Recording");

        
        printf("\nPlease enter a filename for your recording.\n");
        printf("Filenames Should be One Uninterrupted Phrase. No Spaces.\n\n");
        scanf("%s", filename);
        save_trace_file(filename);

        //Leave the window open after save for clarity
        printf("\nFile: \"%s.json\" Was Successfully Saved in the Trace Files Folder.\n Press any button to Exit.\n", filename);
        scanf("%s", filename);
    }

    if(selectedMode == REPLAY)
    {
        printf("\nReplay Mode Selected.\n");
        printf("Please Enter the Name of the Trace File You'd Like to Replay.\n\n");
        scanf("%s", filename);

        init_logger();

        load_filename(filename);
        //parse        
        
        keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, AltKeyboardProc, NULL, 0);

        if (!keyboardHook) {
            printf("Failed to access keyboard for input.\n");
            return 1;
        }

        printf("\nFile: \"%s.json\" Was Successfully Opened and Loaded.\n Press the ` Button to Replay the File at any time.\n", filename);
        printf("Press Escape Twice in a Row to End Replay.\n\n");

        //Standard Windows message loop
        MSG msg;
        while (GetMessage(&msg, NULL, 0, 0)) {}

        UnhookWindowsHookEx(keyboardHook);
    }

    return EXIT_SUCCESS;
}

MacroMode parse_mode(char* mode){
    mode = strlwr(mode);
    if(strcmp(mode,"2") == 0 || strcmp(mode,"replay") == 0){
        return REPLAY;
    }
    if(strcmp(mode,"1") == 0 || strcmp(mode,"record") == 0){
        return RECORD;
    }
    return NONE;
}