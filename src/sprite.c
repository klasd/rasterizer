#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "sprite.h"
#include "display.h"
#include <stdlib.h>

bool sprite_load(sprite_t* sprite, const char* filename) {
    int channels;
    unsigned char* data = stbi_load(filename, &sprite->width, &sprite->height, &channels, 4);
    
    if (!data) {
        sprite->loaded = false;
        return false;
    }
    
    sprite->pixels = malloc(sprite->width * sprite->height * sizeof(uint32_t));
    if (!sprite->pixels) {
        stbi_image_free(data);
        sprite->loaded = false;
        return false;
    }
    
    for (int y = 0; y < sprite->height; y++) {
        for (int x = 0; x < sprite->width; x++) {
            int src_index = (y * sprite->width + x) * 4;
            uint8_t r = data[src_index];
            uint8_t g = data[src_index + 1];
            uint8_t b = data[src_index + 2];
            uint8_t a = data[src_index + 3];
            
            sprite->pixels[y * sprite->width + x] = (a << 24) | (r << 16) | (g << 8) | b;
        }
    }
    
    stbi_image_free(data);
    sprite->loaded = true;
    return true;
}

void sprite_draw(sprite_t* sprite, int x, int y) {
    if (!sprite->loaded) return;
    
    for (int sy = 0; sy < sprite->height; sy++) {
        for (int sx = 0; sx < sprite->width; sx++) {
            int px = x + sx;
            int py = y + sy;
            
            if (px >= 0 && px < SCREEN_WIDTH && py >= 0 && py < SCREEN_HEIGHT) {
                uint32_t pixel = sprite->pixels[sy * sprite->width + sx];
                uint8_t alpha = (pixel >> 24) & 0xFF;
                
                if (alpha > 0) {
                    draw_pixel(px, py, pixel);
                }
            }
        }
    }
}

void sprite_destroy(sprite_t* sprite) {
    if (sprite->pixels) {
        free(sprite->pixels);
        sprite->pixels = NULL;
    }
    sprite->loaded = false;
}
