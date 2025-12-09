#include "macrotrace.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "macrosave.h"
#include "macrolog.h"
#include <windows.h>
#include <time.h>

HHOOK keyboardHook;
HHOOK mouseHook;

int main(void) {

    printf("Press Any Keyboard Button to Begin Recording.\n");

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

    char filename[100];
    printf("Please enter a filename for your recording.\n");
    printf("Filenames Should be One Uninterrupted Phrase. No Spaces.\n");
    scanf("%s", filename);
    save_trace_file(filename);

    return EXIT_SUCCESS;
}