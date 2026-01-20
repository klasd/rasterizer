#include <stdio.h>
#include <stdlib.h>
#include "app.h"
#include "display.h"

int main(void) {
    is_running = create_window();
    
    app_init();

    while (is_running) {
        fix_framerate();
        process_input();
        render();
    }

    app_cleanup();
    destroy_window();

    return EXIT_SUCCESS;
}
