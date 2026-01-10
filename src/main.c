#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <SDL.h>
#include "display.h"
#include "vec2.h"

bool is_running = false;

vec2_t vertices[4] = {
        { .x = 40, .y = 40 },
        { .x = 80, .y = 40 },
        { .x = 40, .y = 80 }
};

void process_input(void) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                is_running = false;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    is_running = false;
                break;
        }
    }
}

// Edge function to determine which side of an edge a point is on
float edge_cross(vec2_t* a, vec2_t* b, vec2_t* p) {
    vec2_t ab = { b->x - a->x, b->y - a->y };
    vec2_t ap = { p->x - a->x, p->y - a->y };
    return ab.x * ap.y - ab.y * ap.x;
}

void draw_triangle(vec2_t v0, vec2_t v1, vec2_t v2, uint32_t color) {
    // Find the bounding box of the triangle
    int x_min = fmin(fmin(v0.x, v1.x), v2.x);
    int y_min = fmin(fmin(v0.y, v1.y), v2.y);
    int x_max = fmax(fmax(v0.x, v1.x), v2.x);
    int y_max = fmax(fmax(v0.y, v1.y), v2.y);

    // Loop all candidate pixels inside the bounding box
    for (int y = y_min; y <= y_max; y++) {
        for (int x = x_min; x <= x_max; x++) {
            vec2_t p = { x, y };

            // Compute edge functions for each edge
            float w0 = edge_cross(&v1, &v2, &p);
            float w1 = edge_cross(&v2, &v0, &p);
            float w2 = edge_cross(&v0, &v1, &p);

            // Check if point is inside triangle (all same sign)
            bool inside = (w0 >= 0 && w1 >= 0 && w2 >= 0) ||
                          (w0 <= 0 && w1 <= 0 && w2 <= 0);

            if (inside) {
                draw_pixel(x, y, color);
            }
        }
    }
}

void render(void) {
    clear_framebuffer(0xFF000000);

    vec2_t v0 = vertices[0];
    vec2_t v1 = vertices[1];
    vec2_t v2 = vertices[2];

    draw_triangle(v0, v1, v2, 0xFF00FF00);

    render_framebuffer();
}

int main(void) {
    is_running = create_window();

    while (is_running) {
        fix_framerate();
        process_input();
        render();
    }

    destroy_window();

    return EXIT_SUCCESS;
}
