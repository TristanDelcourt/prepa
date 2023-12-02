#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include "sound.h"

void write_int(FILE* f, int a, int size){
    assert(size>=1 && size<=4);

    for(int i = 0; i<size; i++){
        fprintf(f, "%c", (a >> ((i * 8)) % 256));
    }
}

void write_header(FILE* f, int n, int number_of_channels){

    // "RIFF"
    fprintf(f, "%c", 'R');
    fprintf(f, "%c", 'I');
    fprintf(f, "%c", 'F');
    fprintf(f, "%c", 'F');
    
    // 36+L*n/8 = 36 + 2*n*(number_of_channels)
    write_int(f, 36 + 2*n*(number_of_channels), 4);

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
    
    // number_of_channels
    write_int(f, number_of_channels, 2);

    // f = 44100
    write_int(f, 44100, 4);

    // f*(number_of_channels)*L/8 = 88200 * (number_of_channels)
    write_int(f, 88200 * (number_of_channels), 4);

    // (number_of_channels)*L/8 = 2 * (number_of_channels)
    write_int(f, 2 * (number_of_channels), 2);

    // L = 16
    write_int(f, 16, 2);

    // "data"
    fprintf(f, "%c", 'd');
    fprintf(f, "%c", 'a');
    fprintf(f, "%c", 't');
    fprintf(f, "%c", 'a');

    // L*(number_of_channels)*n/8 = 2*n
    write_int(f, (number_of_channels)*2*n, 4);
}

void save_sound(char* filename, sound_t** s, int number_of_channels){
    FILE* f = fopen(filename, "w");
    assert(f!=NULL);


    unsigned int number_of_samples = 0;
    for(int j = 0; j < number_of_channels; j++)
        if(s[j] -> n_samples > number_of_samples){
            number_of_samples = s[j] -> n_samples;
        }


    write_header(f, number_of_samples, number_of_channels);

    printf("%d\n", number_of_samples);

    for(int i = 0; i<number_of_samples; i++){
        for(int j = 0; j < number_of_channels; j++){
            if(i < s[j]->n_samples)
                write_int(f, (s[j]->samples)[i], 2);
            else
                write_int(f, 0, 2);
        }
    }

    printf("Fichier '%s' généré.\nTaille du fichier: %f Mo\nDurée de l'audio %d s\n", filename, (float)(number_of_channels)*(number_of_samples)*2/1000000, (number_of_samples)*1/44100);
    for(int j = 0; j < number_of_channels; j++)
        free_sound(s[j]);
    fclose(f);
}

void read_int(FILE* f, int16_t* a, int size){
    char buffer;
    for(int i = 0; i<size; i++){
        fscanf(f, "%c", &buffer);
        printf("%c\n", buffer);
        *a += buffer<<(8*i);
    }
}

void read_header(FILE* f, int* N, int* f_ech, int* L, int* number_of_channels){
    char* useless;
    char buffer;

    // RIFF
    fscanf(f, "%c", useless);
    fscanf(f, "%c", useless);
    fscanf(f, "%c", useless);
    fscanf(f, "%c", useless);

    // 36+L*n/8 = 36 + 2*n*(number_of_channels)
    fscanf(f, "%c", useless);
    fscanf(f, "%c", useless);
    fscanf(f, "%c", useless);
    fscanf(f, "%c", useless);

    // "WAVEfmt "
    fscanf(f, "%c", useless);
    fscanf(f, "%c", useless);
    fscanf(f, "%c", useless);
    fscanf(f, "%c", useless);
    fscanf(f, "%c", useless);
    fscanf(f, "%c", useless);
    fscanf(f, "%c", useless);
    fscanf(f, "%c", useless);

    // 16
    fscanf(f, "%c", useless);
    fscanf(f, "%c", useless);
    fscanf(f, "%c", useless);
    fscanf(f, "%c", useless);

    // 1
    fscanf(f, "%c", useless);
    fscanf(f, "%c", useless);
    
    // number_of_channels
    fscanf(f, "%c", &buffer);
    *number_of_channels = buffer;
    fscanf(f, "%c", &buffer);
    *number_of_channels += buffer << 8;

    // f = 44100
    fscanf(f, "%c", &buffer);
    *f_ech = buffer;
    fscanf(f, "%c", &buffer);
    *f_ech += buffer << 8;
    fscanf(f, "%c", &buffer);
    *f_ech = buffer << 16;
    fscanf(f, "%c", &buffer);
    *f_ech += buffer << 24;

    // f*(number_of_channels)*L/8 = 88200 * (stereoflag + 1)
    fscanf(f, "%c", useless);
    fscanf(f, "%c", useless);
    fscanf(f, "%c", useless);
    fscanf(f, "%c", useless);;

    // (number_of_channels)*L/8 = 2 * (number_of_channels)
    fscanf(f, "%c", useless);
    fscanf(f, "%c", useless);

    // L = 16
    fscanf(f, "%c", &buffer);
    *L = buffer;
    fscanf(f, "%c", &buffer);
    *L += buffer << 8;

    // "data"
    fscanf(f, "%c", useless);
    fscanf(f, "%c", useless);
    fscanf(f, "%c", useless);
    fscanf(f, "%c", useless);

    // L*(number_of_channels)*n/8 = 2*n*(number_of_channels)
    int32_t val4;
    fscanf(f, "%c", &buffer);
    val4 = buffer;  
    fscanf(f, "%c", &buffer);
    val4 += buffer << 8;
    fscanf(f, "%c", &buffer);
    val4 += buffer << 16;
    fscanf(f, "%c", &buffer);
    val4 += buffer << 24;

    *N = val4/2;

    assert(*L==16);
    assert(*f_ech == 44100);
    exit(1);

}

sound_t* read_wav(char* filename){
    FILE* f = fopen(filename, "r");
    assert(f!=NULL);

    int N;
    int f_ech;
    int L;
    int stereo_flag;
    read_header(f, &N, &f_ech, &L, &stereo_flag);


}