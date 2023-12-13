#include "file.h"
#include <stdlib.h>
#include <assert.h>

#define Nmax 1000

struct file{
    int queue;
    int nb_elem;
    int tab[Nmax];
};

file_t* file_vide(){
    file_t* f = malloc(sizeof(file_t));
    f->nb_elem = 0;
    f->queue = 0;
    return f;
};

bool est_file_vide(file_t* f){
    return (f->nb_elem == 0);
}

void enfiler(file_t* f, int x){
    assert(f->nb_elem < Nmax);

    f->tab[f->queue%Nmax] = x;
    f->nb_elem++;
    f->queue++;
}

int defiler(file_t* f){
    assert(f->nb_elem != 0);

    int tete = (f->nb_elem + f->queue)%Nmax;
    f->nb_elem--;
    return f->tab[tete];
}

void free_file(file_t* f){
    return;
}

void affiche_file(file_t* f){
    printf("----------\n");
    int tete = (f->nb_elem + f->queue)%Nmax;
    for(int i = tete ; i<f->nb_elem + tete; i++)
        printf("%d\n", f->tab[i]);
    printf("----------\n");
}