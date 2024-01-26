#include "liste.h"
/* Implémentation par liste à sentinelle
La liste contient toujours deux maillons, un
à la tête et un à la queue, appelés les
sentinelles. Ces maillons sont invisibles du
point de vue de l'utilisateur. */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

typedef struct liste {
   struct maillon* tete;
   struct maillon* queue;
   int taille;
} liste_t;

typedef struct maillon {
   T val;
   struct maillon* suiv;
   struct maillon* prec;
   struct liste* mere;
} maillon_t;


liste_t* liste_vide(){
   liste_t* l = malloc(sizeof(liste_t));
   l->taille = 0;
   l->tete = malloc(sizeof(maillon_t));
   l->queue = malloc(sizeof(maillon_t));

   l->tete->mere = l;
   l->queue->mere = l;

   // TETE <-> QUEUE
   l->tete->suiv = l->queue;
   l->tete->prec = NULL;
   l->queue->prec = l->tete;
   l->queue->suiv = NULL;

   return l;
}


void print_liste(liste_t* l){
   // itérer sur les vrais maillons, i.e. en partant après la sentinelle de tête
   maillon_t* m = l->tete->suiv; 
   //jusqu'à atteindre la sentinelle de queue
   while (m->suiv != NULL){
      printf("%d", m->val);
      // mettre une double flèche s'il reste un vrai maillon à afficher
      if (m->suiv->suiv != NULL){
         printf(" <-> ");
      }
      m = m->suiv;
   }
   printf("\n");
}


void free_liste(liste_t* l){
   maillon_t* m = l->tete;
   while (m != NULL){
      maillon_t* prochain = m->suiv;
      free(m);
      m = prochain;
   }
   free(l);
}

bool est_sentinelle(maillon_t* m){
   return (m->prec == NULL || m->suiv == NULL);
}

void ajout_tete(liste_t* l, T x){
   ajouter_m(l->tete, x);
}

void ajout_queue(liste_t* l, T x){
   ajouter_m(l->queue->prec, x);
}

T get_val(maillon_t* m){
   return m->val;
}

maillon_t* get_tete(liste_t* l){
   if(est_sentinelle(l->tete->suiv))
      return NULL;
   return l->tete->suiv;
}

maillon_t* get_queue(liste_t* l){
   if(est_sentinelle(l->queue->prec))
      return NULL;
   return l->queue->prec;
}

maillon_t* maillon_suiv(maillon_t* m){
   if(est_sentinelle(m->suiv))
      return NULL;
   return m->suiv;
}

maillon_t* maillon_prec(maillon_t* m){
   if(est_sentinelle(m->prec))
      return NULL;
   return m->prec;
}

void ajouter_m(maillon_t* m, T x){
   maillon_t* nv_m = malloc(sizeof(maillon_t));
   nv_m->val = x;
   nv_m->mere = m->mere;

   nv_m->prec = m;
   nv_m->suiv = m->suiv;
   
   m->suiv->prec = nv_m;
   m->suiv = nv_m;

   m->mere->taille += 1;
}

void supprimer_m(maillon_t* m){
   m->prec->suiv = m->suiv;
   m->suiv->prec = m->prec;

   m->mere->taille -= 1;

   free(m);
}

void modifier_m(maillon_t* m, T x){
   m->val = x;
}

int taille(liste_t* l){
   return l->taille;
}

bool in(liste_t* l, T x){
   maillon_t* m = l->tete->suiv;
   while (m != NULL){
      maillon_t* prochain = m->suiv;
      if(m->val == x)
         return true;
      m = prochain;
   }
   return false;
}

void tri_insertion(liste_t* l){
   maillon_t* maillon_actuel = l->tete->suiv;
   int len_l = taille(l);
   for(int i = 0; i<len_l-1; i++){
      maillon_t* m = maillon_actuel->prec;
      maillon_t* nv_maillon_actuel = maillon_actuel->suiv;

      while(!(est_sentinelle(m)) && m->val > maillon_actuel->val){
         m = m->prec;
      }
      maillon_actuel->suiv->prec = maillon_actuel->prec;
      maillon_actuel->prec->suiv = maillon_actuel->suiv;

      maillon_actuel->suiv = m->suiv;
      m->suiv->prec = maillon_actuel;
      
      m->suiv = maillon_actuel;
      maillon_actuel->prec = m;

      maillon_actuel = nv_maillon_actuel;
   }
}