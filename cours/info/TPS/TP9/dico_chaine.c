#include "dico_chaine.h"
#include "keyval.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

chain_t* chain_create(){
	chain_t* d = malloc(sizeof(chain_t));
	d->head = NULL;
	d->n = 0;
	return d;
}

bool chain_get(chain_t* d, KEY k, VAL* v){
	maillon_t* m = d->head;
	while(m != NULL && !equal(m->key, k)){
		m = m->next;
	}
	// en sortie de boucle: soit m est NULL, auquel cas aucun maillon ne contient k
	// soit m est tel que m->key et k sont égales
	if (m != NULL){
		*v = m->val;
		return true;  // ERREUR
	}
	return false;
}

void chain_set(chain_t* d, KEY k, VAL v){
	maillon_t* m = d->head;
	while(m != NULL && !equal(m->key, k)){
		m = m->next;
	}
	// en sortie de boucle: si m est NULL la clé k n'est
	// pas dans d, il faut créer un nouveau maillon. Sinon,
	// le maillon m contient la clé k, il suffit de modifier
	// sa valeur
	if (m == NULL){
		d->n++;
		// nouveau maillon_t
		m = malloc(sizeof(maillon_t));
		m->key = k; // ERREUR
		m->val = v;		
		
		// ajout de m en tête de liste: deux liens à créer
		// entre m et la tête actuelle (qui peut être NULL)
		m->prev = NULL;
		m->next = d->head;
		if (d->head != NULL){
			d->head->prev = m;
		} 
		d->head = m;

	} else {
		val_free(m->val);
		m->val = v;
	}
}

bool chain_delete(chain_t* d, KEY k){
	maillon_t* m = d->head;
	while(m != NULL && !equal(m->key, k)){
		m = m->next;
	}

	if (m == NULL){
		return false;
	}
	
	maillon_t* prev = m->prev;
	maillon_t* next = m->next;

	if (prev != NULL){
		prev->next = next;
	} else {
		d->head = next;
	}
	if (next != NULL){
		next->prev = prev;
	}
	key_free(m->key);
	val_free(m->val);
	free(m);

	d->n --;
	return true;
}



void chain_print(chain_t* d){
	maillon_t* m = d->head;
	if (m == NULL){
		printf("(liste vide)\n");
	}
	while (m != NULL){
		key_print(m->key);
		printf(" -> ");
		val_print(m->val);
		printf("\n");
		m = m->next;
	}
}


void free_maillon(maillon_t* m){
	if (m != NULL){
		free_maillon(m->next);
		key_free(m->key);
		val_free(m->val);
		free(m);
	}
}

void chain_free(chain_t* d){
	free_maillon(d->head);
	free(d);
}