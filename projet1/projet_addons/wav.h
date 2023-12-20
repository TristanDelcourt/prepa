#pragma once
#include <stdio.h>
#include "sound.h"

// Ecrit le nombre a sur size octets en petit boutiste dans le fichier f
void write_int(FILE* f, int a, int size);

// Ecrit dans le fichier f le header correspondant a n samples
void write_header(FILE* f, int n, int stereo_flag);

// Prends un sound et l'écrit dans un ficher, avec le header
void save_sound(char* filename, sound_t** s, int stereo_flag);

// Lit dans un fichier wav et renvoie un sound correspondant (comme l'implémentation du stéréo a besoin de liste de sound, cette fonction renvoie un liste de taille 1)
sound_t** read_wav(char* filename, int* number_of_channels);

// Affiche le temps formaté
void print_time(char* msg, double time);

// lit le header d'un fichier wav pour obtenir les informations importants qu'il contient
void read_header(FILE* f, int* N, int* f_ech, int* L, int* stereo_flag);

// lit un entier de size octet en betit boutiste dans un fichier
void read_int(FILE* f, int* a, int size);