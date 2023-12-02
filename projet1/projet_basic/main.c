#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "sound.h"
#include "wav.h"
#include "waveform.h"
#include "melody.h"

int main(int argc, char** argv){
    assert(argc==3);
    srand(time(NULL));


    //Q8
    /*
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

    /*// Q13
    sound_t* s1 = sine(440, 0, 0.5, 44100); 
    sound_t* s2 = sine(440, 16000, 0.4, 44100); 
    sound_t* s3 = sine(440, 0, 0.1, 44100); 
    sound_t* s4 = sine(440, 16000, 0.4, 44100); 
    sound_t* s5 = sine(440, 0, 0.1, 44100); 
    sound_t* s6 = sine(440, 16000, 0.5, 44100); 
    sound_t* s7 = sine(493.88, 16000, 0.5, 44100); 
    sound_t* s8 = sine(554.36, 16000, 1, 44100); 
    sound_t* s9 = sine(493.88, 16000, 1, 44100); 

    track_t* t = malloc(sizeof(track_t));
    t->n_sounds = 9;
    sound_t** tab = malloc(9 * sizeof(sound_t*));
    t->sounds = tab;
    (t->sounds)[0] = s1;
    (t->sounds)[1] = s2;
    (t->sounds)[2] = s3;
    (t->sounds)[3] = s4;
    (t->sounds)[4] = s5;
    (t->sounds)[5] = s6;
    (t->sounds)[6] = s7;
    (t->sounds)[7] = s8;
    (t->sounds)[8] = s9;

    */


    /*
    sound_t* s1 = sine(440, 16000, 5, 44100);
    save_sound("sin_test.wav", s1);
    
    sound_t* s2 = square(440, 16000, 5, 44100);
    save_sound("square_test.wav", s2);

    //sound_t* s3 = triangle(440, 32768, 5, 44100);
    //save_sound("triangle_test.wav", s3);

    sound_t* s4 = sawtooth(440, 16000, 5, 44100);
    save_sound("sawtooth_test.wav", s4);
    */

    /*
    FILE* f = fopen("sonata_une_piste.txt", "r");
    track_t* t = read_track(f);
    sound_t* thing = reduce_track(t);
    save_sound("sonata_une_piste.wav", thing);
    */

    /*
    char filename1[] = "test1.txt";
    mix_t* m1 = load_mix(filename1);
    sound_t* s1 = reduce_mix(m1);
    save_sound("test1.wav", s1);

    char filename2[] = "test2.txt";
    mix_t* m2 = load_mix(filename2);
    sound_t* s2 = reduce_mix(m2);
    save_sound("test2.wav", s2);
    
    char filename3[] = "test3.txt";
    mix_t* m3 = load_mix(filename3);
    sound_t* s3 = reduce_mix(m3);
    save_sound("test3.wav", s3);
    */

    
    mix_t* m = load_mix(argv[1]);
    sound_t* s = reduce_mix(m);
    save_sound(argv[2], s);


    return 0;
}