#include "macrotrace.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int main(void) {

    bool recording = false;

    printf("Press Any Keyboard Button to Begin Recording.\n");

    hook_set_dispatch_proc(handle_event);

    //Start the hook
    if (hook_run() != UIOHOOK_SUCCESS) {
        fprintf(stderr, "Failed to start hook!\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}