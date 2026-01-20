#include <SDL.h>
#include "app.h"
#include "display.h"
#include "graphics.h"

bool is_running = false;

vec2_t vertices[4] = {
        { .x = 40, .y = 40 },
        { .x = 80, .y = 40 },
        { .x = 40, .y = 80 }
};

float rotation_angle = 0.0f;
vec2_t rotation_center = { .x = 60, .y = 60 };
#define ROTATION_SPEED 0.02f

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

void render(void) {
    clear_framebuffer(0xFF000000);

    vec2_t v0 = vec2_rotate(vertices[0], rotation_center, rotation_angle);
    vec2_t v1 = vec2_rotate(vertices[1], rotation_center, rotation_angle);
    vec2_t v2 = vec2_rotate(vertices[2], rotation_center, rotation_angle);

    draw_triangle(v0, v1, v2, 0xFF00FF00);

    rotation_angle += ROTATION_SPEED;

    render_framebuffer();
}