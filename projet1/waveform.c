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
    s->samples = malloc((s->n_samples) * sizeof(int16_t));
    for(int i = 0; i<(s->n_samples); i++){
        (s->samples)[i] = rand()%65536 - 32768;
    }
    return s;

}

sound_t* sine(float freq, int amplitude, float duree, int f_ech){
    sound_t* s = malloc(sizeof(sound_t));
    unsigned int number_of_samples = duree*f_ech;

    s->n_samples = number_of_samples;
    int16_t* tab = malloc(number_of_samples * sizeof(int16_t));

    double delta_t = (double)1/f_ech;
    double omega = 2*PI*freq*delta_t;
    // printf("%lf, %lf, %d", omega, delta_t, number_of_samples);

    double value;
    float boosted;
    int16_t rounded;

    for(int i = 0; i<number_of_samples; i++){
        value = sin(omega*i);
        boosted = value*amplitude;
        rounded = boosted;

        tab[i] = rounded;

        // Visualisateur de courbe dans la console
        // for(int j=0; j<value*50+50; j++){
        //     printf("#");
        // }
        // printf("\n");
    }

    s->samples = tab;
    return s;
}

sound_t* square(int freq, int amplitude, float duree, int f_ech){
        sound_t* s = malloc(sizeof(sound_t));
    unsigned int number_of_samples = duree*f_ech;

    s->n_samples = number_of_samples;
    int16_t* tab = malloc(number_of_samples * sizeof(int16_t));

    double delta_t = (double)1/f_ech;
    double periode = (double)1/freq;

    double t1 = 0, t2 = 0;
    for(int i = 0; i<number_of_samples; i++){
        if(t1<periode/2){
            tab[i] = -amplitude;
            t1 += delta_t;
            t2 = 0;
        }
        else{
            tab[i] = amplitude;
            t2 += delta_t;
            if(t2>periode/2)
                t1 = 0;
        }
    }

    s->samples = tab;
    return s;
}

sound_t* sawtooth(float freq, int amplitude, float duree, int f_ech){
            sound_t* s = malloc(sizeof(sound_t));
    unsigned int number_of_samples = duree*f_ech;

    s->n_samples = number_of_samples;
    int16_t* tab = malloc(number_of_samples * sizeof(int16_t));

    double periode = (double)1/freq;

    int nb_periode = duree/periode;
    int nb_ech_par_periode = number_of_samples / nb_periode;
    printf("%d", nb_ech_par_periode);

    for(int i = 0; i<number_of_samples; i++){
        double facteur = (double)((i%nb_ech_par_periode)-nb_ech_par_periode/2)/nb_ech_par_periode;
        tab[i] = facteur*amplitude;
    }

    s->samples = tab;
    return s;
}
