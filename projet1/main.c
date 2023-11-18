#include <stdlib.h>
#include <time.h>
#include "sound.h"
#include "wav.h"
#include "waveform.h"

int main(){
    srand(time(NULL));

    char filename[] = "test2.wav";

    /*
    sound_t* s = malloc(sizeof(sound_t));
    s->n_samples = 3;

    s->samples = malloc(3*sizeof(int16_t));
    (s->samples)[0] = 15387;
    (s->samples)[1] = 815;
    (s->samples)[2] = -6337;
    */

    sound_t* s = sine(4, 16000, 1, 44100); 
    save_sound(filename, s);

    free_sound(s);
    return 0;
}