#include "graphe.h"
#include "stoi.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

void afficher(graphe_t* g){
	for (int i = 0; i < g->n; ++i)
	{
		printf("%s -> ", g->sommets[i]);
		adj_t* maillon = g->voisins[i];
		while (maillon != NULL){
			char* nom_voisin = g->sommets[maillon->dest];
			printf("(%s, %f), ", nom_voisin, maillon->poids);
			maillon = maillon->suiv;
		}
		printf("\n");
	}
}

bool est_arete(graphe_t* g, char* u, char* v){
	assert(stoi_mem(g->indice, u));
	assert(stoi_mem(g->indice, v));

	// retrouver les indices des sommets
	int i = stoi_get(g->indice, u);
	int j = stoi_get(g->indice, v);

	// chercher j dans la liste des voisins de i
	adj_t* maillon = g->voisins[i];
	while (maillon != NULL && maillon->dest != j){
		maillon = maillon->suiv;
	}
	// en sortie: soit maillon = NULL soit maillon représente une arête (i, j) 
	return (maillon != NULL);
}

graphe_t* graphe_vide(char** sommets, int n){
	graphe_t* g = malloc(sizeof(graphe_t));
	g->n = n;
	g->sommets = sommets;
	g->voisins = malloc(n*sizeof(adj_t*));
	g->indice = stoi_vide();

	for(int i = 0; i<n; i++){
		g->voisins[i] = NULL;
		stoi_set(g->indice, sommets[i], i);
	}

	return g;
}

void ajouter(graphe_t* g, char* u, char* v, float w){
	assert(stoi_mem(g->indice, u));
	assert(stoi_mem(g->indice, v));

	// retrouver les indices des sommets
	int i = stoi_get(g->indice, u);
	int j = stoi_get(g->indice, v);

	adj_t* maillon = g->voisins[i];
	adj_t* new = malloc(sizeof(adj_t));
	new->dest = j;
	new->poids = w;

	new->suiv = maillon;
	g->voisins[i] = new;
}

void liste_adj_free(adj_t* t){
	adj_t* curr = t;
	while(curr!=NULL){
		adj_t* next = curr->suiv;
		free(curr);
		curr = next;
	}
}

void graphe_free(graphe_t* g){
	stoi_free(g->indice);

	for(int i = 0; i<g->n; i++){
		liste_adj_free(g->voisins[i]);
	}
	free(g->voisins);

	for(int i = 0; i<g->n; i++){
		free(g->sommets[i]);
	}
	free(g->sommets);
	free(g);
}