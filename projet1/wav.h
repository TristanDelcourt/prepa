#pragma once
#include <stdio.h>
#include "sound.h"

void write_int(FILE* f, int a, int size);
void write_header(FILE* f, int n);
void save_sound(char* filename, sound_t* s);