#define T int

typedef struct tas_ {
	T* tab;
	int taille_max;
	int taille_actuelle;
} HEAP;


/* Crée et renvoie un tas vide de taille `taille`. */
HEAP* tas_vide(int taille);

/* Ajoute x dans t. t ne doit pas être plein. */
void ajouter(HEAP* h, T x);

/* Renvoie la valeur minimale de t. t doit être non vide. */
T extraire_min(HEAP* h);


/* Trie en place le tableau t de taille n en utilisant
   un tas. */
void tri_par_tas(int* t, int n);