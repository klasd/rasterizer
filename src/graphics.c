#include <math.h>
#include "graphics.h"
#include "display.h"

float edge_cross(vec2_t* a, vec2_t* b, vec2_t* p) {
    vec2_t ab = { b->x - a->x, b->y - a->y };
    vec2_t ap = { p->x - a->x, p->y - a->y };
    return ab.x * ap.y - ab.y * ap.x;
}

void draw_triangle(vec2_t v0, vec2_t v1, vec2_t v2, uint32_t color) {
    int x_min = fmin(fmin(v0.x, v1.x), v2.x);
    int y_min = fmin(fmin(v0.y, v1.y), v2.y);
    int x_max = fmax(fmax(v0.x, v1.x), v2.x);
    int y_max = fmax(fmax(v0.y, v1.y), v2.y);

    for (int y = y_min; y <= y_max; y++) {
        for (int x = x_min; x <= x_max; x++) {
            vec2_t p = { x, y };

            float w0 = edge_cross(&v1, &v2, &p);
            float w1 = edge_cross(&v2, &v0, &p);
            float w2 = edge_cross(&v0, &v1, &p);

            bool inside = (w0 >= 0 && w1 >= 0 && w2 >= 0) ||
                          (w0 <= 0 && w1 <= 0 && w2 <= 0);

            if (inside) {
                draw_pixel(x, y, color);
            }
        }
    }
}