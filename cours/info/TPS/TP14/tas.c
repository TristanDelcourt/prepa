#include "tas.h"
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

/* Échange les noeuds i et j de t */
void swap(HEAP*t, int i, int j){
	assert (0 <= i && 0 <= j && i < t->taille_max && j < t->taille_max);
	T tmp = t->tab[i];
	t->tab[i] = t->tab[j];
	t->tab[j] = tmp;
}

// parent du noeud i
int parent(int i){
	return (i-1)/2;
}

// enfant gauche du noeud i
int gauche(int i){
	return 2*i+1;
}

// enfant droit du noeud i
int droite(int i){
	return 2*i+2;
}

HEAP* tas_vide(int taille){
    HEAP* h = malloc(sizeof(HEAP));
    h->tab = malloc(taille*sizeof(T));
    h->taille_actuelle = 0;
    h->taille_max = taille;
}

void tasser(HEAP* h, int i){
    while(h->tab[i] <= h->tab[parent(i)] && i != 0){
        swap(h, i, parent(i));
        i  = parent(i);
    }
}

void ajouter(HEAP* h, T x){
    assert(h->taille_actuelle < h->taille_max);

    h->tab[h->taille_actuelle] = x;
    tasser(h, h->taille_actuelle);
    h->taille_actuelle++;
}

void tamiser(HEAP* h, int i){
    while(i<=h->taille_actuelle && 
                (h->tab[i] > h->tab[gauche(i) && droite(i) < h->taille_actuelle]
                    || (h->tab[i] > h->tab[droite(i)] && droite(i) < h->taille_actuelle ))){
        
        if (h->tab[droite(i)] < h->tab[gauche(i) && droite(i) < h->taille_actuelle]){
            swap(h, i, droite(i));
            i = droite(i);
        }
        else{
            swap(h, i, gauche(i));
            i = gauche(i);
        }
    }
}

T extraire_min(HEAP* h){
    T e = h->tab[0];
    swap(h, 0, h->taille_actuelle-1);
    tamiser(h, 0);
    h->taille_actuelle -= 1;

    return e;
}

void tri_par_tas(int* t, int n){
    printf("Not implemented yet\n");
    assert(false);
}