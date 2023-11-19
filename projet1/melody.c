#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "sound.h"
#include "waveform.h"
#include "wav.h"

float pitch_to_freq(int n){
    return 440 * pow(2, (float)n/12);
}

track_t* read_track(FILE* f){
    track_t* t = malloc(sizeof(track_t));
    int n;
    fscanf(f, "%d", &n);

    t->n_sounds = n;
    t->sounds = malloc(n*sizeof(sound_t*));

    char* type = malloc(10* sizeof(char));
    fscanf(f, "%s", type);

    for(int i = 0; i<n; i++){
        float pitch;
        float duree;
        float volume;
        fscanf(f, "%f %f %f", &pitch, &duree, &volume);

        if(!(strcmp("sawtooth", type)))
            (t->sounds)[i] = sawtooth(pitch_to_freq(pitch), volume*32768, duree, 44100);
        else if(!(strcmp("sine", type)))
            (t->sounds)[i] = sine(pitch_to_freq(pitch), volume*32768, duree, 44100);
        else if(!(strcmp("square", type)))
            (t->sounds)[i] = square(pitch_to_freq(pitch), volume*32768, duree, 44100);
    }

    free(type);
    return t;
}

mix_t* load_mix(char* filename){
    FILE* f = fopen(filename, "r");
    assert(f!=NULL);

    int nb_tracks;
    fscanf(f, "%d", &nb_tracks);

    float* vol = malloc(nb_tracks * sizeof(float));
    for(int i = 0 ; i<nb_tracks; i++)
        fscanf(f, "%f", &(vol[i]));
    
    track_t** t_tab = malloc(nb_tracks * sizeof(track_t*));
    for(int i = 0; i<nb_tracks; i++){
        t_tab[i] = read_track(f);
    }
    
    mix_t* m = malloc(sizeof(mix_t));
    m->n_tracks = nb_tracks;
    m->tracks = t_tab;
    m->vols = vol;

    fclose(f);
    return m;
}