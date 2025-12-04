#include "macrotrace.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "macrosave.h"

int main(void) {

    bool recording = false;

    printf("Press Any Keyboard Button to Begin Recording.\n");

    hook_set_dispatch_proc(handle_event);

    //Start the hook
    if (hook_run() != UIOHOOK_SUCCESS) {
        fprintf(stderr, "Failed to start hook!\n");
        return EXIT_FAILURE;
    }
    close_temp_trace_file();

    printf("Recording Stopped.\n");

    // char filename[100];
    // printf("Please enter a filename for your recording.\n");
    // printf("Filenames Should be One Uninterrupted Phrase. No Spaces.\n");
    // scanf("%s", filename);
    // save_trace_file(filename);

    return EXIT_SUCCESS;
}