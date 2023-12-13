#include "pile.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct maillon{
    int elem;
    struct maillon* suivant;
} maillon_t;

struct pile{
    maillon_t* sommet;
};

pile_t* pile_vide(){
    pile_t* p = malloc(sizeof(pile_t));
    p->sommet = NULL;
}

bool est_vide(pile_t* p){
    return (p->sommet == NULL);
}

void empiler(pile_t* p, int x){
    maillon_t* m = malloc(sizeof(maillon_t));
    m->elem = x;
    m->suivant = p->sommet;
    p->sommet = m;
}

int depiler(pile_t* p){
    assert(p->sommet != NULL);
    
    int x = p->sommet->elem;
    maillon_t* nv_sommet = p->sommet->suivant;
    free(p->sommet);
    p->sommet = nv_sommet;
    return x;
}

void print_pile(pile_t* p){
    maillon_t* s = p->sommet;
    printf("----------\n");
    for(maillon_t* i = s; i!=NULL; i = i->suivant)
        printf("%d\n", i->elem);
    printf("----------\n");
}

void free_pile(pile_t* p){
    maillon_t* prev = p->sommet;

    while(prev != NULL){
        maillon_t* next = prev->suivant;
        free(prev);
        prev = next;
    }
    
    free(p);
}