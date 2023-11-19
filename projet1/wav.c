#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include "sound.h"

void write_int(FILE* f, int a, int size){
    assert(size>=1 && size<=4);

    for(int i = 0; i<size; i++){
        fprintf(f, "%c", (a >> ((i * 8)) % 256));
    }
}

void write_header(FILE* f, int n){
    // "RIFF"
    fprintf(f, "%c", 'R');
    fprintf(f, "%c", 'I');
    fprintf(f, "%c", 'F');
    fprintf(f, "%c", 'F');
    
    // 36+L*n/8 = 36 + 2*n
    write_int(f, 36+2*n, 4);

    // "WAVEfmt "
    fprintf(f, "%c", 'W');
    fprintf(f, "%c", 'A');
    fprintf(f, "%c", 'V');
    fprintf(f, "%c", 'E');
    fprintf(f, "%c", 'f');
    fprintf(f, "%c", 'm');
    fprintf(f, "%c", 't');
    fprintf(f, "%c", ' ');

    // 16
    write_int(f, 16, 4);

    // 1
    write_int(f, 1, 2);
    
    // 1
    write_int(f, 1, 2);

    // f = 44100
    write_int(f, 44100, 4);

    // f*L/8 = 88200
    write_int(f, 88200, 4);

    // L/8 = 2
    write_int(f, 2, 2);

    // L = 16
    write_int(f, 16, 2);

    // "data"
    fprintf(f, "%c", 'd');
    fprintf(f, "%c", 'a');
    fprintf(f, "%c", 't');
    fprintf(f, "%c", 'a');

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

    printf("Fichier '%s' généré.\nTaille du fichier: %f Mo\nDurée de l'audio %d s\n", filename, (float)(s->n_samples)*2/1000000, (s->n_samples)*1/44100);
    free_sound(s);
    fclose(f);
}
