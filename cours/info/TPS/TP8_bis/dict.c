#include "dict.h"
#include "liste.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

struct dict {
	liste_t* chaine;
};
typedef struct dict dict_t;

dict_t* dico_vide(){
	dict_t* d = malloc(sizeof(dict_t));
	d->chaine = liste_vide();
	return d;
}

bool in(dict_t* d, char* k){
	maillon_t* m = get_tete(d->chaine);
	while(m != NULL){
		cv_t* c = get_val(m);
		if (strcmp(c->cle, k) == 0){
			return true;
		}
		m = maillon_suiv(m);
	}
	return false;
}

char* get(dict_t* d, char* k){
	maillon_t* m = get_tete(d->chaine);
	while(m != NULL){
		cv_t* c = get_val(m);
		if (strcmp(c->cle, k) == 0){
			return c->valeur;
		}
		m = maillon_suiv(m);
	}
	return NULL;
}

void set(dict_t* d, char* k, char* v){
	if(!in(d, k)){
		cv_t* truc = malloc(sizeof(cv_t));
		truc->cle = k;
		truc->valeur = v;
		ajout_tete(d->chaine, truc);
	}

	else{
		bool done = false; // pour eviter le break
		maillon_t* m = get_tete(d->chaine);
		while(m != NULL && !done){
			cv_t* c = get_val(m);
			if (strcmp(c->cle, k) == 0){
				c->valeur = v;
				bool done = true;
			}
			m = maillon_suiv(m);
		}
	}
}