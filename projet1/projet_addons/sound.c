#include <stdlib.h>
#include <stdio.h>
#include "sound.h"

void free_sound(sound_t* s){
    free(s->samples);
    free(s);
}

void free_track(track_t* t){
    for(int i = 0; i<(t->n_sounds); i++){
        free_sound((t->sounds)[i]);
    }
    free(t->sounds);
    free(t);
}

void free_mix(mix_t* m){
    //for(int i = 0; i<(m->n_tracks); i++){
    //    free_track((m->tracks)[i]);
    //}
    free(m->tracks);
    free(m->vols);
    free(m);
}

sound_t* reduce_track(track_t* t){
    sound_t* out = malloc(sizeof(sound_t));

    int total_samples = 0;
    for(int i = 0; i<(t->n_sounds); i++){
            total_samples += ((t->sounds)[i])->n_samples;
    }
    out->n_samples = total_samples;

    uint16_t* tab = malloc(total_samples * sizeof(uint16_t));

    int counter = 0;
    for(int i = 0; i<(t->n_sounds); i++){
        for(int j = 0; j<(((t->sounds)[i])->n_samples); j++){
            tab[counter] = (((t->sounds)[i])->samples)[j];
            counter++;
        }
    }
    out->samples = tab;
    free_track(t);
    return out;
}

sound_t** reduce_mix(mix_t** m, int number_of_channels){
    sound_t** out = malloc((number_of_channels) * sizeof(sound_t*));
    for(int i = 0; i < number_of_channels ; i++)
        out[i] = malloc(sizeof(sound_t));

    for(int stereo = 0; stereo < number_of_channels ; stereo++){
        

        int len_tab = m[stereo]->n_tracks;
        sound_t** s_tab = malloc(len_tab * sizeof(sound_t*));
        float* ponderation = malloc(len_tab * sizeof(float));

        for(int i = 0; i<len_tab; i++){
            s_tab[i] = reduce_track((m[stereo]->tracks)[i]);
            ponderation[i] = (m[stereo]->vols)[i];
        }

        int max_length = 0;
        for(int i = 0; i<len_tab; i++)
            if (((s_tab[i])->n_samples) > max_length)
                max_length = ((s_tab[i])->n_samples);

        out[stereo]->n_samples = max_length;
        out[stereo]->samples = malloc(max_length * sizeof(int16_t));

        for(int i = 0; i<max_length; i++){
            float n = 0;
            int32_t sum = 0;
            for(int j = 0; j<len_tab; j++){
                if( i < ((s_tab[j])->n_samples) ){
                    sum += ( ((s_tab[j])->samples)[i] ) * ponderation[j];
                    n += ponderation[j];
                }
            }
            (out[stereo]->samples)[i] = (float)sum/n;
        }

        for(int i = 0; i<len_tab; i++){
            free_sound(s_tab[i]);
        }
        free(s_tab);
        free_mix(m[stereo]);
        free(ponderation);

    }

    return out;
}
