#pragma once

#include "sound.h"

sound_t* white(float duree, int f_ech);
sound_t* sine(float freq, int amplitude, float duree, int f_ech);
sound_t* square(int freq, int amplitude, float duree, int f_ech);
sound_t* sawtooth(float freq, int amplitude, float duree, int f_ech);
sound_t* triangle(float freq, int amplitude, float duree, int f_ech);
