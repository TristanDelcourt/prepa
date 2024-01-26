#include "liste.h"
#include <stdio.h>

void test(){
    liste_t* l = liste_vide();
    print_liste(l);

    ajout_tete(l, 6);
    ajout_tete(l, 4);
    ajout_tete(l, 2);

    ajout_queue(l, 3);
    ajout_queue(l, 5);
    ajout_queue(l, 1);

    print_liste(l);

    maillon_t* t = get_tete(l);
    maillon_t* q = get_queue(l);
    printf("tete: %d, queue: %d\n", get_val(t), get_val(q));

    
    for(int _ = 0; _<3; _++){
        t = maillon_suiv(t);
    }
    ajouter_m(t, 120);
    print_liste(l);

    ajouter_m(q, 138);

    print_liste(l);

    supprimer_m(t);

    print_liste(l);

    printf("taille: %d\n", taille(l));
    printf("6 in l: %d\n", in(l, 6));

    tri_insertion(l);
    print_liste(l);

    free_liste(l);

    return;
}

int main(){

    test();

    return 0;
}