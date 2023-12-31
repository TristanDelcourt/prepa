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

// Libère la mémoire alloué pour un sound
void free_sound(sound_t* s);

// Libère la mémoire alloué pour un track
void free_track(track_t* t);

// Libère la mémoire alloué pour un mix
void free_mix(mix_t* m);

// Prends en entrée un track et le réduit en un seul sound
sound_t* reduce_track(track_t* t);

// Prends en entrée un mix et le réduit en un seul sound (comme l'implémentation du stéréo a besoin de liste de sound, cette fonction renvoie un liste de taille 1)
sound_t** reduce_mix(mix_t** m, int number_of_channels);