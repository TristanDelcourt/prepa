#include "pile.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#define Nmax 1000

struct pile{
    int nb_elem;
    int tab[Nmax];
};

pile_t* pile_vide(){
    pile_t* p = malloc(sizeof(pile_t));
    p->nb_elem = 0;
    return p;
}

bool est_vide(pile_t* p){
    return p->nb_elem == 0;
}

void empiler(pile_t* p, int x){
    assert(p->nb_elem<Nmax);
    p->tab[p->nb_elem] = x;
    p->nb_elem++;
}

int depiler(pile_t* p){
    assert(p->nb_elem !=0);
    p->nb_elem--;
    int x = p->tab[p->nb_elem];
    return x;
}

void free_pile(pile_t* p){
    free(p);
}

void print_pile(pile_t* p){
    printf("----------\n");
    for(int i = 0; i<p->nb_elem; i++){
        printf("%d\n", p->tab[i]);
    }
    printf("----------\n");
}