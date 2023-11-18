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
    printf("%lf, %lf, %d", omega, delta_t, number_of_samples);

    double value;
    float boosted;
    int16_t rounded;

    for(int i = 0; i<number_of_samples; i++){
        value = sin(omega*i);
        //printf("%f | ", value);
        
        boosted = value*amplitude;
        //printf("%f | ", boosted);

        rounded = boosted;
        //printf("%d\n", rounded);

        // Visualisateur de courbe dans la console
        /*
        for(int j=0; j<value*50+50; j++){
            printf("#");
        }
        printf("\n");
        */

        tab[i] = rounded;
    }

    s->samples = tab;
    return s;
}
