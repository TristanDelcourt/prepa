/* SDA: dictionnaire */
#pragma once
#include <stdbool.h>

typedef struct dict dict_t;

dict_t* dico_vide();

/* Renvoie un booléen indiquant si k est une clé de d */
bool in(dict_t* d, char* k);

/* Renvoie la valeur associée à k dans d, ou bien NULL
   si k n'est pas dans d */
char* get(dict_t* d, char* k);

/* Modifie la valeur associée à k dans d en v,
   et ajoute le couple (k, v) si k n'est pas déjà dans d */
void set(dict_t* d, char* k, char* v);