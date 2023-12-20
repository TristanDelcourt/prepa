#include <stdlib.h>
#include <math.h>
#include <stdint.h> 
#include <time.h>
#include <stdio.h>
#include "sound.h"

#define PI 3.14159265358979323846

sound_t* white(float duree, int f_ech){
    sound_t* s = malloc(sizeof(sound_t));

    s->n_samples = floor(duree*f_ech);
    s->samples = malloc((s->n_samples) * sizeof(uint16_t));
    for(int i = 0; i<(s->n_samples); i++){
        (s->samples)[i] = rand()%65536-32767;
    }
    return s;

}

sound_t* sine(float freq, int amplitude, float duree, int f_ech){
    sound_t* s = malloc(sizeof(sound_t));
    unsigned int number_of_samples = duree*f_ech;

    s->n_samples = number_of_samples;
    s->samples = malloc(number_of_samples * sizeof(int16_t));

    double delta_t = 1.0/f_ech;
    double omega = 2*PI*freq*delta_t;

    for(int i = 0; i<number_of_samples; i++){
        double value = sin(omega*i);
        float boosted = value*amplitude;

        s->samples[i] = boosted;
    }

    return s;
}

sound_t* square(int freq, int amplitude, float duree, int f_ech){
    sound_t* s = sine(freq, amplitude, duree, f_ech);

    for(int i = 0; i < s->n_samples; i++){
        if(s->samples[i] > 0)
            s->samples[i] = amplitude;
        else if(s->samples[i] < 0)
            s->samples[i] = -amplitude;
        else
            s->samples[i] = 0;
    }

    return s;
    
}

sound_t* sawtooth(float freq, int amplitude, float duree, int f_ech){
    sound_t* s = malloc(sizeof(sound_t));
    unsigned int number_of_samples = duree*f_ech;

    s->n_samples = number_of_samples;
    s->samples = malloc(number_of_samples * sizeof(int16_t));

    double periode = 1.0/freq;

    int nb_periode = duree/periode+1;
    int nb_ech_par_periode = (number_of_samples / nb_periode);

    for(int i = 0; i<number_of_samples; i++){
        int help = i%nb_ech_par_periode;
        double value = (double)help/nb_ech_par_periode*2-1;
        (s->samples)[i] = value*amplitude;
    }
    return s;
}

sound_t* triangle(float freq, int amplitude, float duree, int f_ech){
    sound_t* s = malloc(sizeof(sound_t));
    unsigned int number_of_samples = duree*f_ech;

    s->n_samples = number_of_samples;
    s->samples = malloc(number_of_samples * sizeof(int16_t));

    double periode = 1.0/freq;

    int nb_periode = duree/periode+1;
    int nb_ech_par_periode = (number_of_samples / nb_periode);
    
    for(int i = 0; i<number_of_samples; i++){
        int help = i%nb_ech_par_periode;
        double phase = (double)help / nb_ech_par_periode;
        double value;
        if(phase < 0.5)
            value = 4.0 * phase - 1.0;
        else
            value = -4.0 * phase + 3.0;
        (s->samples)[i] = value*amplitude;
    }
    return s;
}