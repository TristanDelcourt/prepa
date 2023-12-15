#pragma once


// Convertie un certaine hauteur en la fréqience corresondante
float pitch_to_freq(int n);

// Renvoie le track contenu dans un fichier
track_t* read_track(FILE* f);

// Renvoie le mix contenu dans fichier
mix_t* load_mix(char* filename);