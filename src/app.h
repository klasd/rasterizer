#ifndef APP_H
#define APP_H

#include <stdbool.h>
#include <stdint.h>
#include "vec2.h"

extern bool is_running;
extern vec2_t vertices[4];
extern float rotation_angle;
extern vec2_t rotation_center;

void process_input(void);
void render(void);

#endif