#pragma once
#include <stdio.h>
#include "sound.h"

// Ecrit le nombre a sur size octets en petit boutiste dans le fichier f
void write_int(FILE* f, int a, int size);

// Ecrit dans le fichier f le header correspondant a n samples
void write_header(FILE* f, int n);

// Prends un sound et l'écrit dans un ficher, avec le header
void save_sound(char* filename, sound_t* s);

// Affiche le temps formaté
void print_time(char* msg, double time);
