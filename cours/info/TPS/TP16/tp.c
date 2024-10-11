#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// liste chainée pour stocker les voisins d'un sommet
struct adj{
	unsigned int voisin;
	struct adj* suiv;
};
typedef struct adj adj_t;

struct graphe {
	int n;
	adj_t** lv; // listes des voisins		
};
typedef struct graphe graphe_t;

void print_graphe(graphe_t* g){
    for(int i = 0; i<g->n; i++){
        printf("%d -> ", i);
        adj_t* noeud = g->lv[i];
        while(noeud != NULL){
            printf("%d ", noeud->voisin);
            noeud = noeud -> suiv;
        }
        printf("\n");
    }
}

void free_graphe(graphe_t* g){
    for(int i = 0; i<g->n; i++){
        adj_t* curr = g->lv[i];
        while(curr != NULL){
            adj_t* next = curr->suiv;
            free(curr);
            curr = next;
        }
    }
    free(g->lv);
    free(g);
}

graphe_t* graphe_vide(int n){
    graphe_t* g = malloc(sizeof(graphe_t));
    g->n = n;
    g->lv = malloc(n*sizeof(adj_t));
    for(int i = 0; i<n; i++){
        g->lv[i] = NULL;
    }
    return g;
}

void ajout(graphe_t* g, unsigned int u, unsigned int v){
    adj_t* curr = g->lv[u];
    bool already_exists = false;
    while(curr != NULL){
        if(curr->voisin == v)
            already_exists = true;
        curr = curr->suiv;
    }
    if (!already_exists){
        adj_t* new = malloc(sizeof(adj_t));
        new->voisin = v;
        new->suiv = g->lv[u];
        g->lv[u] = new;
    }
}

void ajouter(graphe_t* g, unsigned int u, unsigned int v, bool oriente){
    ajout(g, u, v);
    if(!oriente)
        ajout(g, v, u);
}

int main(int argc, char const *argv[])
{	
	graphe_t* g = malloc(sizeof(graphe_t));
	g->n = 4;
	g->lv = malloc(4*sizeof(adj_t*));
	
	// successeurs de 0: [1]
	g->lv[0] = malloc(sizeof(adj_t));
	g->lv[0]->voisin = 1;
	g->lv[0]->suiv = NULL;

	// successeurs de 1: [2, 3]
	g->lv[1] = malloc(sizeof(adj_t));
	g->lv[1]->voisin = 2;
	g->lv[1]->suiv = malloc(sizeof(adj_t));
	g->lv[1]->suiv->voisin = 3;
	g->lv[1]->suiv->suiv = NULL;

	//successeurs de 2: [0, 3]
	g->lv[2] = malloc(sizeof(adj_t));
	g->lv[2]->voisin = 0;
	g->lv[2]->suiv = malloc(sizeof(adj_t));
	g->lv[2]->suiv->voisin = 3;
	g->lv[2]->suiv->suiv = NULL;

	// successeurs de 3: []
	g->lv[3] = NULL;

    /* END INIT DE G0  */


    graphe_t* g2 = graphe_vide(5);
    ajouter(g2, 0, 1, false);
    ajouter(g2, 0, 2, false);
    ajouter(g2, 1, 0, false);
    ajouter(g2, 2, 4, false);
    ajouter(g2, 3, 0, false);
    print_graphe(g2);

	// Libérer la mémoire
    free_graphe(g);
    free_graphe(g2);
	return 0;
}