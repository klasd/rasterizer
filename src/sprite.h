#ifndef SPRITE_H
#define SPRITE_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint32_t* pixels;
    int width;
    int height;
    bool loaded;
} sprite_t;

bool sprite_load(sprite_t* sprite, const char* filename);
void sprite_draw(sprite_t* sprite, int x, int y);
void sprite_destroy(sprite_t* sprite);

#endif