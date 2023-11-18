#include <stdlib.h>
#include <math.h>
#include <stdint.h> 
#include <time.h>
#include <stdio.h>
#include "sound.h"

# define PI 3.14159265358979323846

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

    s->n_samples = floor(duree*f_ech);
    s->samples = malloc((s->n_samples) * sizeof(int16_t));
    double delta_t = (float)1/f_ech;
    double omega = 2*PI*freq*delta_t;
    printf("%f, %f, %d", delta_t, omega, s->n_samples);
    for(int i = 0; i<(s->n_samples); i++){
        double value = sin(omega*i);
        //printf("%f | ", value);
        
        float thing = round(value*amplitude);
        //printf("%f | ", thing);

        int16_t thing2 = thing;
        //printf("%d\n", thing2);


        (s->samples)[i] = thing2;
    }
    return s;
}
