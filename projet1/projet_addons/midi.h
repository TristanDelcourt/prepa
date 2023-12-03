#pragma once
#include <stdio.h>
#include <stdint.h>
#include "sound.h"

typedef struct channel_status{
    int note;
    int velocity;
    int time_since_last_change;
} channel_status_t;

void read_midi_header(FILE* f, int* format, int* number_of_tracks, int* division);
void read_midi_file(char* filename);
mix_t* read_midi_track(FILE*f, int division);
void get_delta_time(FILE* f, int32_t* dt);