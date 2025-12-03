#include "macrotrace.h"
#include <stdlib.h>
#include <stdio.h>

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