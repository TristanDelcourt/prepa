#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include "sound.h"

void print_time(char* msg, double time){
    int hours, minutes, seconds, milliseconds;
    double time_in_seconds = time;
    hours = (int)time_in_seconds / 3600;
    time_in_seconds -= hours * 3600;
    minutes = (int)time_in_seconds / 60;
    time_in_seconds -= minutes * 60;
    seconds = (int)time_in_seconds;
    milliseconds = (time_in_seconds - seconds) * 1000;

    if(hours > 0)
        printf("%s %dh, %dmin, %ds and %dms\n", msg, hours, minutes, seconds, milliseconds);
    else if(minutes > 0)
        printf("%s %dmin, %ds and %dms\n", msg, minutes, seconds, milliseconds);
    else if(seconds > 0)
        printf("%s %ds and %dms\n", msg, seconds, milliseconds);
    else
        printf("%s %dms\n", msg, milliseconds);
}

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


    // Nombre de samples total max
    unsigned int number_of_samples = 0;
    for(int j = 0; j < number_of_channels; j++)
        if(s[j] -> n_samples > number_of_samples)
            number_of_samples = s[j] -> n_samples;


    write_header(f, number_of_samples, number_of_channels);

    for(int i = 0; i<number_of_samples; i++){
        for(int j = 0; j < number_of_channels; j++){
            if(i < s[j]->n_samples)
                write_int(f, (s[j]->samples)[i], 2);
            else
                write_int(f, 0, 2);
        }
    }

    int tot_samples = 0;
    for(int j = 0; j < number_of_channels; j++){
        tot_samples += s[j] -> n_samples;
        free_sound(s[j]);
    }
    free(s);
    
    printf("Fichier '%s' généré.\nTaille du fichier: %f Mo\n", filename, (float)(tot_samples)*2/1000000);
    print_time("Durée de l'audio:", (number_of_samples)*1/44100);
    fclose(f);
}

void read_int(FILE* f, int16_t* a, int size){
    char buffer;
    for(int i = 0; i<size; i++){
        fscanf(f, "%c", &buffer);
        *a += buffer<<(8*i);
    }
}

void read_header(FILE* f, int* N, int* f_ech, int* L, int* number_of_channels){
    char useless;
    unsigned char buffer;

    // RIFF
    fscanf(f, "%c", &useless);
    fscanf(f, "%c", &useless);
    fscanf(f, "%c", &useless);
    fscanf(f, "%c", &useless);

    // 36+L*n/8 = 36 + 2*n*(number_of_channels)
    fscanf(f, "%c", &useless);
    fscanf(f, "%c", &useless);
    fscanf(f, "%c", &useless);
    fscanf(f, "%c", &useless);

    // "WAVEfmt "
    fscanf(f, "%c", &useless);
    fscanf(f, "%c", &useless);
    fscanf(f, "%c", &useless);
    fscanf(f, "%c", &useless);
    fscanf(f, "%c", &useless);
    fscanf(f, "%c", &useless);
    fscanf(f, "%c", &useless);
    fscanf(f, "%c", &useless);

    // 16
    fscanf(f, "%c", &useless);
    fscanf(f, "%c", &useless);
    fscanf(f, "%c", &useless);
    fscanf(f, "%c", &useless);

    // 1
    fscanf(f, "%c", &useless);
    fscanf(f, "%c", &useless);
    
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
    *f_ech += buffer << 16;
    fscanf(f, "%c", &buffer);
    *f_ech += buffer << 24;

    // f*(number_of_channels)*L/8 = 88200 * (number_of_channels)
    fscanf(f, "%c", &useless);
    fscanf(f, "%c", &useless);
    fscanf(f, "%c", &useless);
    fscanf(f, "%c", &useless);;

    // (number_of_channels)*L/8 = 2 * (number_of_channels)
    fscanf(f, "%c", &useless);
    fscanf(f, "%c", &useless);

    // L = 16
    fscanf(f, "%c", &buffer);
    *L = buffer;
    fscanf(f, "%c", &buffer);
    *L += buffer << 8;

    // "data"
    fscanf(f, "%c", &useless);
    fscanf(f, "%c", &useless);
    fscanf(f, "%c", &useless);
    fscanf(f, "%c", &useless);

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

    /*
    printf("%d\n", *number_of_channels);
    printf("%d\n", *N);
    */

    assert(*L==16);
    assert(*f_ech == 44100);
}

sound_t** read_wav(char* filename, int* number_of_channels){
    FILE* f = fopen(filename, "r");
    printf("%s\n", filename);
    assert(f!=NULL);

    int N;
    int f_ech;
    int L;
    read_header(f, &N, &f_ech, &L, number_of_channels);
    
    sound_t** s_tab = malloc(sizeof(sound_t*));
    for(int i = 0; i < (*number_of_channels); i++){
        s_tab[i] = malloc(sizeof(sound_t*));
        s_tab[i]->n_samples = N/(*number_of_channels);
        s_tab[i]->samples = malloc(s_tab[i]->n_samples * sizeof(int16_t));
    }

    for(int i = 0; i<N/(*number_of_channels); i++){
        for(int j = 0; j < *number_of_channels; j++){
            int16_t buffer = 0;
            read_int(f, &buffer, 2);
            (s_tab[j]->samples)[i] = buffer;
        }
    }
    return s_tab;

}