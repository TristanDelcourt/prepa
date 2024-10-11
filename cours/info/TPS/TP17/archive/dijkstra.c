#include "graphe.h"
#include "stoi.h"

float get_weight(graphe_t* g, char* u, char* v){
	assert(stoi_mem(g->indice, u));
	assert(stoi_mem(g->indice, v));

	int i = stoi_get(g->indice, u);
	int j = stoi_get(g->indice, v);

	adj_t* maillon = g->voisins[i];
	while (maillon->dest != j){
		maillon = maillon->suiv;
	}
	return maillon->poids;
}

float longueur(graphe_t* g, char** chemin, int n){
    float cost = 0;
    for(int i = 0; i<n-1; i++){
        assert(est_arete(g, chemin[i], chemin[i+1]));
        cost += get_weight(g, chemin[i], chemin[i+1]);
    }
    return cost;
}

int extraire_min(float* d, bool* q, int n){
    int min = 0;
    bool found = false;
    for(int i = 0; i<n; i++){
        if(q[i]){
            bool found = true;
            if(d[i]<d[min])
                min = i;
        }
    }
    if(!found){
        return -1;
    }
    else{
        q[min] = 0;
        return min;
    }
}