#include "file.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

typedef struct maillon_t{
    int elem;
    struct maillon_t* suivant;
} maillon_t;

struct file{
    maillon_t* tete;
    maillon_t* queue;
};

file_t* file_vide(){
    file_t* f = malloc(sizeof(file_t));
    f->queue = NULL;
    f->tete = NULL;
    return f;
}

bool est_file_vide(file_t* f){
    return (f->tete == NULL);
}

void enfiler(file_t* f, int x){
    maillon_t* m = malloc(sizeof(maillon_t));
    m->elem = x;

    if(est_file_vide(f)){
        m->suivant = NULL;
        f->tete = m;
        f->queue = m;
    }

    else{
        f->queue->suivant = m;
        m->suivant = NULL;
    }
}

void affiche_file(file_t* f){
    maillon_t* t = f->tete;    
    for(maillon_t* i = t; i!=NULL; i = i->suivant)
        printf("%d<-", i->elem);
    printf("\n");
}

int defiler(file_t* f){
    assert(f->tete != NULL);

    int x = f->tete->elem;

    maillon_t* nv_tete = f->tete->suivant;
    free(f->tete);
    f->tete = nv_tete;

    return x;
}

void free_file(file_t* f){
    maillon_t* prev = f->tete;

    while(prev != NULL){
        maillon_t* next = prev->suivant;
        free(prev);
        prev = next;
    }
    
    free(f);
}