#include <stdlib.h>
#include <time.h>
#include "sound.h"
#include "wav.h"
#include "waveform.h"

int main(){
    srand(time(NULL));

    char filename[] = "test2.wav";

    /* Q8
    sound_t* s = malloc(sizeof(sound_t));
    s->n_samples = 3;

    s->samples = malloc(3*sizeof(int16_t));
    (s->samples)[0] = 15387;
    (s->samples)[1] = 815;
    (s->samples)[2] = -6337;
    */

    /* Test write_int
    FILE* f = fopen("godhelpme.wav", "w");
    for(int i = 0; i<65535; i++){
        write_int(f, i-32768, 2);
    }
    fclose(f);
    */

    sound_t* s = sine(440, 16000, 1, 44100); 
    save_sound(filename, s);
    
    //free_sound(s);
    return 0;
}