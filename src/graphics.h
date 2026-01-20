#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdint.h>
#include "vec2.h"

float edge_cross(vec2_t* a, vec2_t* b, vec2_t* p);
void draw_triangle(vec2_t v0, vec2_t v1, vec2_t v2, uint32_t color);

#endif