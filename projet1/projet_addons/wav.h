#pragma once
#include <stdio.h>
#include "sound.h"

void write_int(FILE* f, int a, int size);
void write_header(FILE* f, int n, int stereo_flag);
void save_sound(char* filename, sound_t** s, int stereo_flag);
sound_t* read_wav(char* filename);
void read_header(FILE* f, int* N, int* f_ech, int* L, int* stereo_flag);
void read_int(FILE* f, int* a, int size);