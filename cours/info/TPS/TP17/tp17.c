#include <math.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct graphe {
    int n;
    float** mat;
} graphe_t;

float** init_mat(int n){
    float** m = malloc(n*sizeof(float*));
    for(int i = 0; i<n; i++){
        m[i] = malloc(n*sizeof(float));
    }
    return m;
}

void print_mat(float** m, int n){
    for(int i = 0; i<n; i++){
        for(int j = 0; j<n; j++){
            printf("%f   ", m[i][j]);
        }
        printf("\n");
    }
}

void free_mat(float** m, int n){
    for(int i = 0; i<n; i++){
        free(m[i]);
    }
    free(m);
}

float** floyd_warshall(graphe_t* g){
    float*** T = malloc((g->n+1)*sizeof(float**));
    for(int k = 1; k < g->n+1; k++){
        T[k] = init_mat(g->n);
    }
    T[0] = g->mat;

    for(int k = 0; k<g->n; k++){
        for(int i = 0; i< g->n; i++){
            for(int j = 0; j<g->n; j++){
                T[k+1][i][j] = fmin(T[k][i][j], T[k][i][k] + T[k][k][j]);
            }
        }
    }
    float** out = T[g->n];

    for(int k = 1; k< g->n; k++){
        free_mat(T[k], g->n);
    }
    free(T);

    return out;
}

int main(){
    graphe_t* g = malloc(sizeof(graphe_t));
    g->n = 5;
    g->mat = malloc(5*sizeof(float*));

    float l1[5] = {0, 2, INFINITY, -1, INFINITY};
    g->mat[0] = l1;

    float l2[5] = {INFINITY, 0, 2, INFINITY, INFINITY};
    g->mat[1] = l2;

    
    float l3[5] = {INFINITY, INFINITY, 0, -1, INFINITY};
    g->mat[2] = l3;

    
    float l4[5] = {2, INFINITY, INFINITY, 0, 2};
    g->mat[3] = l4;

    float l5[5] = {INFINITY, INFINITY, 1, INFINITY, 0};
    g->mat[4] = l5;

    float** t = floyd_warshall(g);
    print_mat(t, g->n);

    free_mat(t, g->n);
    free(g->mat);
    free(g);

    return 0;
}