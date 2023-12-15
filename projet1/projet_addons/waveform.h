#pragma once

#include "sound.h"

// Créer un sound qui contient des samples choisit aléatoirement
sound_t* white(float duree, int f_ech);

// Créer un sound avec des samples qui correspondent a un son sinoisidal de fréquence freq
sound_t* sine(float freq, int amplitude, float duree, int f_ech);

// Créer un sound avec des samples qui correspondent a un son square de fréquence freq
sound_t* square(int freq, int amplitude, float duree, int f_ech);

// Créer un sound avec des samples qui correspondent a un son sawtooth de fréquence freq
sound_t* sawtooth(float freq, int amplitude, float duree, int f_ech);

// Créer un sound avec des samples qui correspondent a un son triangle de fréquence freq
sound_t* triangle(float freq, int amplitude, float duree, int f_ech);
