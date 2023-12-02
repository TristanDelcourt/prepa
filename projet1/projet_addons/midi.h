#pragma once
#include <stdio.h>

void read_midi_header(FILE* f, int* format, int* number_of_tracks, int* division);
void read_midi_file(char* filename);
void read_midi_track(FILE*f, int* track_length);
void get_delta_time(FILE* f, int32_t* dt);