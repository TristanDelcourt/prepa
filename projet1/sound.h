#pragma once

#include <stdint.h>

typedef struct sound{
    unsigned int n_samples;
    int16_t* samples;
} sound_t;

void free_sound(sound_t* s);