#include "dico_hash.h"
#include "dico_chaine.h"
#include "keyval.h"

/* TABLES DE HACHAGE AVEC CHAINAGE 
Dictionnaires implémentés par des tables de hachage.
Chaque alvéole de la table contient une liste chaînée
stockant les différentes clés hashés vers cette alvéole.

*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#define MIN_SIZE 4 // nombre minimale d'alvéoles 

// ALPHA_LOW et ALPHA_HIGH sont les bornes sur le taux de remplissage
// Lorsque le taux de remplissage est hors des bornes, on redimensionne
// la taille en posant m (nombre d'alvéoles) = RESIZE_FACTOR * n (nombre de clés).
// ceci assure que l'on a n/m = 1/RESIZE_FACTOR = (ALPHA_LOW + ALPHA_HIGH)/2,
// i.e. le taux de remplissage reste entre les deux bornes
#define ALPHA_LOW 0.1
#define ALPHA_HIGH 0.5
#define RESIZE_FACTOR 2.0/(ALPHA_LOW+ALPHA_HIGH)

struct hashtable{
	int m; // nombre d'alvéoles
	int n; // nombre d'entrées
	chain_t** t; // table de hachage: chaque case i contient la liste
	             // des clés hachées à la valeur i
};


/* Remplace *d par une nouvelle table contenant les mêmes éléments, de façon 
   à ce que le taux de remplissage reste entre ALPHA_LOW et ALPHA_HIGH, sans 
   que le nombre d'alvéoles passe en dessous de MIN_SIZE */
void resize(hashtable_t* d){
	// Si le taux de remplissage est déjà correct, ne rien faire
	if (ALPHA_LOW * d->m <= d->n && d->n <= ALPHA_HIGH * d->m){
		return;
	}

	// calculer le nouveau nombre d'alvéoles, et ne continuer que s'il
	// est supérieur à MIN_SIZE
	int new_m = d->n * RESIZE_FACTOR;
	if (new_m < MIN_SIZE){
		return ;
	}

	// nouvelle table
	chain_t** new_table = malloc(sizeof(chain_t*)*new_m);
	for (int i = 0; i < new_m; ++i)
	{
		new_table[i] = chain_create();
	}

	// réarranger les maillons de l'ancienne table pour les mettre
	// dans la nouvelle
	for (int i = 0; i < d->m; ++i)
	{
		chain_t* c = d->t[i];
		maillon_t* m = c->head; // maillon pour parcourir l'alvéole i
		while (m != NULL){
			KEY k = m->key;
			maillon_t* s = m->next; // maillon suivant de m, permet de parcourir la chaine tout en enlevant les maillons

			// calcul de l'alvéole de la nouvelle table pour la clé k
			chain_t* new_c = new_table[hash(k)%new_m];
			// insertion du maillon m dans cette alvéole
			m->next = new_c->head;
			m->prev = NULL;
			if (new_c->head != NULL){
				new_c->head->prev = m;
			}
			new_c->head = m;

			// passer au maillon suivant
			m = s;
		}
		free(c);
	}
	free(d->t);
	d->t = new_table;
	d->m = new_m;
}



void hash_print(hashtable_t* d){
	for (int i = 0; i < d->m; ++i)
	{
		chain_print(d->t[i]);
	}
}

void hash_debug(hashtable_t* d){
	for (int i = 0; i < d->m; ++i)
	{
		printf("Alvéole %d (taille %d):\n", i, d->t[i]->n);
		chain_print(d->t[i]);
	}
	printf("===================\n");
}

hashtable_t* hash_create(){
	struct hashtable* ht = malloc(sizeof(struct hashtable));
	ht->m = MIN_SIZE;
	ht->n = 0;
	ht->t = malloc(sizeof(chain_t*));
	for(int i = 0; i<MIN_SIZE; i++)
		ht->t[i] = chain_create();
	return ht;
}

void hash_set(hashtable_t* d, KEY k, VAL v){
	unsigned h = hash(k)%d->m;
	chain_set(d->t[h], k, v);
	d->n++;

	if(d->n/d->m > ALPHA_HIGH)
		resize(d);
}

bool hash_get(hashtable_t* d, KEY k, VAL* v){
	unsigned h = hash(k)%d->m;
	return chain_get(d->t[h], k, v);
}

bool hash_delete(hashtable_t* d, KEY k){
	unsigned h = hash(k)%d->m;
	bool success =  chain_delete(d->t[h], k);
	if(success){
		d->n --;
		if(d->n/d->m < ALPHA_LOW)
			resize(d);
	}
	return success;
}