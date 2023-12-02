#pragma once

#include <stdint.h>

typedef struct sound{
    unsigned int n_samples;
    int16_t* samples;
} sound_t;

typedef struct track{
    unsigned int n_sounds;
    sound_t** sounds;
} track_t;

typedef struct mix{
    unsigned int n_tracks;
    track_t** tracks;
    float* vols;
} mix_t;

void free_sound(sound_t* s);
void free_track(track_t* t);
void free_mix(mix_t* m);
sound_t* reduce_track(track_t* t);
sound_t** reduce_mix(mix_t** m, int stereo_flag);