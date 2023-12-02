#pragma once

float pitch_to_freq(int n);
track_t* read_track(FILE* f);
mix_t** load_mix(char* filename, int* stereo_flag);