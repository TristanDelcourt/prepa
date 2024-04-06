#include "tas.h"
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

bool est_tas(int* t , int n){
    for(int i = 1; i<n; i++){
        if(t[i] < t[(i-1)/2])
            return false;
    }
    return true;
}

int* tableau_aleatoire(int n, int a, int b){
    srand(time(NULL));

    int* t = malloc(n * sizeof(int));
    for(int i = 0; i<n; i++)
        t[i] = rand() % (b-a+1) + a;
    return t;
}

void print_tab(int* t, int n){
    printf("[");
    for(int i = 0; i < n - 1; i++){
        printf("%d,", t[i]);
    }

    printf("%d]\n", t[n-1]);
}

void print_heap(HEAP* h){
    print_tab(h->tab, h->taille_actuelle);
}

bool est_trie(int* t, int n){
    for(int i = 0; i<n-1; i++){
        if (t[i] < t[i+1])
            return false;
    }
    return true;
}

int main(){
    /*
    int* t1 = tableau_aleatoire(10, 10, 20);
    int* t2 = malloc(3*sizeof(int));
    t2[0] = 1;
    t2[1] = 2;
    t2[2] = 3;
    
    int* t3 = malloc(3*sizeof(int));
    t3[0] = 2;
    t3[1] = 1;
    t3[2] = 3;

    assert(est_tas(t2, 3));
    assert(!est_tas(t3, 3));

    print_tab(t1, 10);
    */

    HEAP* h = tas_vide(20);
    ajouter(h, 5);
    ajouter(h, 1);
    ajouter(h, 3);
    ajouter(h, 10);
    ajouter(h, 6);
    ajouter(h, 2);
    ajouter(h, 7);
    ajouter(h, 11);
    ajouter(h, 9);

    print_heap(h);

    T min = extraire_min(h);
    printf("%d\n", min);

    print_heap(h);

    assert(est_tas(h->tab, h->taille_actuelle));


    return 0;
}