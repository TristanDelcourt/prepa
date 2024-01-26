#pragma once
/* Structure de données abstraite: Liste chaînée */

#include <stdbool.h>
#include "dict.h"

struct cle_valeur {
	char* cle;
	char* valeur;
};
typedef struct cle_valeur cv_t;

#define T cv_t*

typedef struct liste liste_t;
typedef struct maillon maillon_t;

/* Crée une liste vide */
liste_t* liste_vide();

/* Libère toute la mémoire allouée à l */
void free_liste(liste_t* l);

/* Affiche la liste de l'avant à l'arrière */
void print_liste(liste_t* l);

/* Renvoie si le mayon en question est un sentinelle*/
bool est_sentinelle(maillon_t* m);

void ajout_tete(liste_t* l, T x);

void ajout_queue(liste_t* l, T x);

T get_val(maillon_t* m);

maillon_t* get_tete(liste_t* l);

maillon_t* get_queue(liste_t* l);

maillon_t* maillon_suiv(maillon_t* m);

maillon_t* maillon_prec(maillon_t* m);

void ajouter_m(maillon_t* m, T x);

void supprimer_m(maillon_t* m);

void modifier_m(maillon_t* m, T x);

int taille(liste_t* l);

bool in_liste(liste_t* l, T x);

void tri_insertion(liste_t* l);