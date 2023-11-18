#include <stdio.h>
#include <assert.h>
#include "sound.h"

void write_int(FILE* f, int a, int size){
    assert(size>=1 && size<=4);

    for(int i = 0; i<size; i++){
        fprintf(f, "%c", (a>>(i*8))%(256));
    }
}

void write_header(FILE* f, int n){
    // "RIFF"
    fprintf(f, "%c", 0x52);
    fprintf(f, "%c", 0x49);
    fprintf(f, "%c", 0x46);
    fprintf(f, "%c", 0x46);
    
    // 36+L*n/8 = 36 + 2*n
    write_int(f, 36+2*n, 4);

    // "WAVEfmt "
    fprintf(f, "%c", 0x57);
    fprintf(f, "%c", 0x41);
    fprintf(f, "%c", 0x56);
    fprintf(f, "%c", 0x45);
    fprintf(f, "%c", 0x66);
    fprintf(f, "%c", 0x6d);
    fprintf(f, "%c", 0x74);
    fprintf(f, "%c", 0x20);

    // 16
    write_int(f, 16, 4);

    // 1
    write_int(f, 1, 2);
    
    // 1
    write_int(f, 1, 2);

    // f = 44100
    write_int(f, 44100, 4);

    // f*L/8 = 44100
    write_int(f, 88200, 4);

    // L/8 = 2
    write_int(f, 2, 2);

    // L = 16
    write_int(f, 16, 2);

    // "data"
    fprintf(f, "%c", 0x64);
    fprintf(f, "%c", 0x61);
    fprintf(f, "%c", 0x74);
    fprintf(f, "%c", 0x61);

    // L*n/8 = 2*n
    write_int(f, 2*n, 4);
}

void save_sound(char* filename, sound_t* s){
    FILE* f = fopen(filename, "w");
    assert(f!=NULL);

    unsigned int number_of_samples = s->n_samples;

    write_header(f, number_of_samples);

    for(int i = 0; i<number_of_samples; i++){
        write_int(f, (s->samples)[i], 2);
    }
    fclose(f);
}
