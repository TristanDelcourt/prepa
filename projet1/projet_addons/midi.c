#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "midi.h"
#include "sound.h"
#include "waveform.h"
#include "wav.h"

void read_midi_header(FILE* f, int* format, int* number_of_tracks, int* division){
    unsigned char buffer[4];
    fscanf(f, "%c%c%c%c", &buffer[0], &buffer[1], &buffer[2], &buffer[3]);

    if(buffer[0] != 'M' || buffer[1] != 'T' || buffer[2] != 'h' || buffer[3] != 'd'){
        printf("Error: invalid midi file\n");
        exit(1);
    }
    
    fscanf(f, "%c%c%c%c", &buffer[0], &buffer[1], &buffer[2], &buffer[3]);
    if(buffer[0] != 0 || buffer[1] != 0 || buffer[2] != 0 || buffer[3] != 6){
        printf("Error: invalid midi file\n");
        exit(1);
    }

    
    fscanf(f, "%c%c", &buffer[0], &buffer[1]);
    *format = buffer[0] * 256 + buffer[1];
    fscanf(f, "%c%c", &buffer[0], &buffer[1]);
    *number_of_tracks = buffer[0] * 256 + buffer[1];
    fscanf(f, "%c%c", &buffer[0], &buffer[1]);
    *division = buffer[0] * 256 + buffer[1];    

    printf("format: %d\n", *format);
    printf("number_of_tracks: %d\n", *number_of_tracks);
    printf("division: %d\n", *division);
    printf("----------------------\n");
}

void get_delta_time(FILE* f, int32_t* dt){
    unsigned char buffer = 128;
    int i = 0;
    while (buffer >= 128 && i < 4)
    {
        fscanf(f, "%c", &buffer);
        *dt = (*dt) * 256 + (buffer % 256);
        i++;
    }
}

void printf_channel_status(channel_status_t* channels){
    for(int i = 0; i < 16; i++){
        if(channels[i].note != -1){
            printf("(%d, %d, %d) ", channels[i].note, channels[i].velocity, channels[i].time_since_last_change);
        }
    }
    printf("\n");
}

void update_channels_times(channel_status_t* channels, int32_t dt){
    for(int i = 0; i < 16; i++){
        if(channels[i].velocity != 0){
            channels[i].time_since_last_change += dt;
        }
    }
}

mix_t* read_midi_track(FILE*f, int division){
    unsigned char buffer[10];

    fscanf(f, "%c%c%c%c", &buffer[0], &buffer[1], &buffer[2], &buffer[3]);
    assert(buffer[0] == 'M' && buffer[1] == 'T' && buffer[2] == 'r' && buffer[3] == 'k');

    fscanf(f, "%c%c%c%c", &buffer[0], &buffer[1], &buffer[2], &buffer[3]);
    int track_length = buffer[0] * 256 * 256 * 256 + buffer[1] * 256 * 256 + buffer[2] * 256 + buffer[3];
    printf("track_length: %d\n", track_length);

    channel_status_t* channels = malloc(16 * sizeof(channel_status_t));

    float time_coef;

    mix_t* m = malloc(sizeof(mix_t));
    m->n_tracks = 16;
    m->vols = malloc(16 * sizeof(float));
    for(int i = 0; i < 16; i++){
        m->vols[i] = 1;
    }
    m->tracks = malloc(16 * sizeof(track_t*));
    for(int i = 0; i < 16; i++){
        m->tracks[i] = malloc(sizeof(track_t));
        m->tracks[i]->n_sounds = 0;
        m->tracks[i]->sounds = malloc(sizeof(sound_t*));
    }


    while(1){  // :(

        int32_t dt = 0;
        get_delta_time(f, &dt);
        //printf("--\n(dt: %d) ", dt);

        update_channels_times(channels, dt);

        //printf_channel_status(channels);


        fscanf(f, "%c", &buffer[1]);
        //printf("status: %d\n", buffer[1]);
        // meta event
        if(buffer[1] == 255){
            fscanf(f, "%c", &buffer[2]);

            // End of Track
            if(buffer[2] == 47){
                fscanf(f, "%c", &buffer[0]);
                printf("End of Track\n");
                printf("----------------------\n");
                return m;
            }

            // Sequence Number
            else if(buffer[2] == 0){
                fscanf(f, "%c%c", &buffer[0], &buffer[1]);
                int32_t length = buffer[0] * 256 + buffer[1];
                printf("Sequence Number: %d\n", length);
            }

            // Text Event
            else if(buffer[2] == 1){
                fscanf(f, "%c", &buffer[0]);
                int32_t length = buffer[0];
                for(int i = 0; i < length; i++){
                    fscanf(f, "%c", &buffer[3]);
                    printf("%c", buffer[3]);
                }
                printf("\n");
            }

            // Copyrigth Notice
            else if(buffer[2] == 2){
                printf("Copyrigth Notice: ");
                fscanf(f, "%c", &buffer[0]);
                int32_t length = buffer[0];
                for(int i = 0; i < length; i++){
                    fscanf(f, "%c", &buffer[3]);
                    printf("%c", buffer[3]);
                }
                printf("\n");
            }

            // Sequence/Track Name
            else if(buffer[2] == 3){
                printf("Sequence/Track Name: ");
                fscanf(f, "%c", &buffer[0]);
                int32_t length = buffer[0];
                for(int i = 0; i < length; i++){
                    fscanf(f, "%c", &buffer[3]);
                    printf("%c", buffer[3]);
                }
                printf("\n");
            }

            // Instrument Name
            else if(buffer[2] == 4){
                printf("Instrument Name: ");
                fscanf(f, "%c", &buffer[0]);
                int32_t length = buffer[0];
                for(int i = 0; i < length; i++){
                    fscanf(f, "%c", &buffer[3]);
                    printf("%c", buffer[3]);
                }
                printf("\n");
            }
            
            // Lyric
            else if(buffer[2] == 5){
                printf("Lyric: ");
                fscanf(f, "%c", &buffer[0]);
                int32_t length = buffer[0];
                for(int i = 0; i < length; i++){
                    fscanf(f, "%c", &buffer[3]);
                    printf("%c", buffer[3]);
                }
                printf("\n");
            }

            // Marker
            else if(buffer[2] == 6){
                printf("Marker: ");
                fscanf(f, "%c", &buffer[0]);
                int32_t length = buffer[0];
                for(int i = 0; i < length; i++){
                    fscanf(f, "%c", &buffer[3]);
                    printf("%c", buffer[3]);
                }
                printf("\n");
            }

            // Cue Point
            else if(buffer[2] == 7){
                printf("Cue Point: ");
                fscanf(f, "%c", &buffer[0]);
                int32_t length = buffer[0];
                for(int i = 0; i < length; i++){
                    fscanf(f, "%c", &buffer[3]);
                    printf("%c", buffer[3]);
                }
                printf("\n");
            }

            // MIDI Channel Prefix
            else if(buffer[2] == 32){
                fscanf(f, "%c%c", &buffer[0], &buffer[1]);
                int8_t  channel_prefix = buffer[1];
                printf("MIDI Channel Prefix: %d\n", channel_prefix);
            }

            // MIDI Port
            else if(buffer[2] == 33){
                fscanf(f, "%c%c", &buffer[0], &buffer[1]);
                int8_t  port = buffer[1];
                printf("MIDI Port: %d\n", port);
            }

            // Tempo
            else if(buffer[2] == 81){
                fscanf(f, "%c", &buffer[0]); // 03
                fscanf(f, "%c%c%c", &buffer[0], &buffer[1], &buffer[3]);
                int32_t tempo = buffer[0] * 256 * 256 + buffer[1] * 256 + buffer[3];
                printf("Tempo: %d\n", tempo);

                float bpm = (float)60000000/tempo;
                time_coef = (float)division/(bpm*44100);
                printf("time_coef: %f\n", time_coef);

            }

            // SMPTE Offset
            else if(buffer[2] == 84){
                fscanf(f, "%c%c%c%c%c", &buffer[0], &buffer[1], &buffer[3], &buffer[4], &buffer[5]);
                int8_t hour = buffer[0];
                int8_t minute = buffer[1];
                int8_t second = buffer[3];
                int8_t frame = buffer[4];
                int8_t subframe = buffer[5];
                printf("SMPTE Offset: %d:%d:%d:%d:%d\n", hour, minute, second, frame, subframe);
            }

            // Time Signature
            else if(buffer[2] == 88){
                fscanf(f, "%c%c%c%c%c", &buffer[0], &buffer[1], &buffer[3], &buffer[4], &buffer[5]);
                int8_t numerator = buffer[0];
                int8_t denominator = buffer[1];
                int8_t clocks_per_click = buffer[3];
                int8_t number_of_notated_32nd_notes_per_beat = buffer[4];
                printf("Time Signature: %d/%d, %d, %d\n", numerator, denominator, clocks_per_click, number_of_notated_32nd_notes_per_beat);
            }

            else if(buffer[2] == 89){
                fscanf(f, "%c%c%c", &buffer[0], &buffer[1], &buffer[3]);
                int8_t sf = buffer[1];
                int8_t mi = buffer[3];
                printf("Key Signature: %d, %d\n", sf, mi);
            }

            else if(buffer[2] == 127){
                fscanf(f, "%c", &buffer[0]);
                int32_t length = buffer[0];
                printf("Sequencer-Specific Meta-event: ");
                for(int i = 0; i < length; i++){
                    fscanf(f, "%c", &buffer[3]);
                    printf("%c", buffer[3]);
                }
                printf("\n");
            }

            else{
                printf("unknown meta event: %d\n", buffer[2]);
            }
            

        }

        else if((buffer[1]>>4) == 8){
            int channel_nbr = buffer[1] % 16;
            fscanf(f, "%c%c", &buffer[0], &buffer[1]);
            int8_t note = buffer[0];
            int8_t velocity = buffer[1];
            printf("Note Off: %d, %d, %d\n", channel_nbr, note, velocity);

            m->tracks[channel_nbr]->n_sounds++;
            m->tracks[channel_nbr]->sounds = realloc(m->tracks[channel_nbr]->sounds, m->tracks[channel_nbr]->n_sounds * sizeof(sound_t*));
            m->tracks[channel_nbr]->sounds[m->tracks[channel_nbr]->n_sounds -1] = sine(channels[channel_nbr].note + 120, channels[channel_nbr].velocity*128, channels[channel_nbr].time_since_last_change * time_coef, 44100);

            channels[channel_nbr].note = note;
            channels[channel_nbr].velocity = velocity;
            channels[channel_nbr].time_since_last_change = 0;
        }

        else if((buffer[1]>>4) == 9){
            int channel_nbr = buffer[1] % 16;
            fscanf(f, "%c%c", &buffer[0], &buffer[1]);
            int8_t note = buffer[0];
            int8_t velocity = buffer[1];
            printf("Note On: %d, %d, %d\n", channel_nbr, note, velocity);
            channels[channel_nbr].note = note;
            channels[channel_nbr].velocity = velocity;
        }

        else if((buffer[1]>>4) == 10){
            int channel_nbr = buffer[1] % 16;
            fscanf(f, "%c%c", &buffer[0], &buffer[1]);
            int8_t note = buffer[0];
            int8_t velocity = buffer[1];
            printf("Polyphonic Key Pressure: %d, %d, %d\n", channel_nbr, note, velocity);
        }

        else if((buffer[1]>>4) == 11){
            int channel_nbr = buffer[1] % 16;
            fscanf(f, "%c%c", &buffer[0], &buffer[1]);
            int8_t controller_nbr = buffer[0];
            int8_t value = buffer[1];
            printf("Control Change: %d, %d, %d\n", channel_nbr, controller_nbr, value);
        }

        else if((buffer[1]>>4) == 12){
            int channel_nbr = buffer[1] % 16;
            fscanf(f, "%c", &buffer[0]);
            int8_t program_nbr = buffer[0];
            printf("Program Change: %d, %d\n", channel_nbr, program_nbr);
        }

        else if((buffer[1]>>4) == 13){
            int channel_nbr = buffer[1] % 16;
            fscanf(f, "%c", &buffer[0]);
            int8_t pressure = buffer[0];
            printf("Channel Pressure: %d, %d\n", channel_nbr, pressure);
        }

        else if((buffer[1]>>4) == 14){
            int channel_nbr = buffer[1] % 16;
            fscanf(f, "%c%c", &buffer[0], &buffer[1]);
            int8_t value = buffer[0] * 256 + buffer[1];
            printf("Pitch Wheel Change: %d, %d\n", channel_nbr, value);
        }

        else if((buffer[1]>>4) == 15){
            if(buffer[1]%16 == 0){
                printf("Sysex: %d\n", buffer[2]);
                fscanf(f, "%c", &buffer[0]);
                while (buffer[0] != 247)
                {
                    printf("Sysex: %d\n", buffer[0]);
                    fscanf(f, "%c", &buffer[0]);
                }
            }


            else if(buffer[1]%16 == 2){
                fscanf(f, "%c", &buffer[0]);
                printf("Song Position Pointer: %d\n", buffer[2] * 256 + buffer[0]);
            }
            else if(buffer[1]%16 == 3){
                printf("Song Select: %d\n", buffer[2]);
            }
            else if(buffer[1]%16 == 6){
                printf("Tune Request\n");
            }
            else if(buffer[1]%16 == 7){
                printf("End of Exclusive\n");
            }
            else
            {
                printf("unknown event: %d\n", buffer[1]);
            }
            
        }

    }

    return m;
}

uint32_t get_total_dt_tempo(FILE* f, uint32_t* tempo){
    unsigned char buffer[10];

    fscanf(f, "%c%c%c%c", &buffer[0], &buffer[1], &buffer[2], &buffer[3]);
    assert(buffer[0] == 'M' && buffer[1] == 'T' && buffer[2] == 'r' && buffer[3] == 'k');

    fscanf(f, "%c%c%c%c", &buffer[0], &buffer[1], &buffer[2], &buffer[3]);
    int track_length = buffer[0] * 256 * 256 * 256 + buffer[1] * 256 * 256 + buffer[2] * 256 + buffer[3];
    printf("track_length: %d\n", track_length);

    int i = 0;
    int32_t total_dt = 0;
    while(i < track_length){

        int32_t dt = 0;
        get_delta_time(f, &dt);
        total_dt += dt;

        fscanf(f, "%c", &buffer[0]);
        if(buffer[0] = 255){
            fscanf(f, "%c", &buffer[2]);

            if(buffer[2] == 47 || buffer[2] == 0){
                fscanf(f, "%c", &buffer[0]);
                i += 1;
            }

            else if(buffer[2] == 32 || buffer[2] == 33){
                fscanf(f, "%c%c", &buffer[0], &buffer[1]);
                i += 2;
            }

            else if(buffer[2] == 89){
                fscanf(f, "%c%c%c", &buffer[0], &buffer[1], &buffer[3]);
                i += 3;
            }

            else if(buffer[2] == 84 || buffer[2] == 88){
                fscanf(f, "%c%c%c%c%c", &buffer[0], &buffer[1], &buffer[3], &buffer[4], &buffer[5]);
                i += 5;
            }

            else if(buffer[2] == 1 || buffer[2] == 2 || buffer[2] == 3 || buffer[2] == 4 || buffer[2] == 5 || buffer[2] == 6 || buffer[2] == 7 || buffer[2] == 127){
                fscanf(f, "%c", &buffer[0]);
                int32_t length = buffer[0];
                for(int i = 0; i < length; i++){
                    fscanf(f, "%c", &buffer[3]);
                    i += 1;
                }
                i += 1;
            }


            // Tempo
            else if(buffer[2] == 81){
                fscanf(f, "%c", &buffer[0]); // 03
                fscanf(f, "%c%c%c", &buffer[0], &buffer[1], &buffer[3]);
                *tempo = buffer[0] * 256 * 256 + buffer[1] * 256 + buffer[3];
                printf("Tempo: %u\n", *tempo);
                i += 4;

            }

            else{
                printf("unknown meta event: %d\n", buffer[2]);
            }

        }

        else if((buffer[1]>>4) == 9 || (buffer[1]>>4) == 8 || (buffer[1]>>4) == 10 || (buffer[1]>>4) == 11 || (buffer[1]>>4) == 14) {
            fscanf(f, "%c%c", &buffer[0], &buffer[1]);
            i += 2;
        }

        else if((buffer[1]>>4) == 12 || (buffer[1]>>4) == 13){
            fscanf(f, "%c", &buffer[0]);
            i += 1;
        }

        else if((buffer[1]>>4) == 15){
            if(buffer[1]%16 == 0){
                fscanf(f, "%c", &buffer[0]);
                while (buffer[0] != 247)
                    i += 1;
                i += 1;
            }


            else if(buffer[1]%16 == 2 || buffer[1]%16 == 3 || buffer[1]%16 == 6 || buffer[1]%16 == 7){
                fscanf(f, "%c", &buffer[0]);
                i += 1;
            }
            else
                printf("unknown event: %d\n", buffer[1]);
        }
    }

    return total_dt;
}

void read_midi_file(char* filename){
    FILE* f = fopen(filename, "r");
    assert(f != NULL);

    int format, number_of_tracks, division;
    read_midi_header(f, &format, &number_of_tracks, &division);

    uint32_t tempo = 0;
    uint32_t total_dt = get_total_dt_tempo(f, &tempo);
    float tick_duration = (float)tempo/division;
    uint32_t duration = total_dt * tick_duration;
    uint64_t n_samples = duration * 44100;

    printf("samples: %ld\n", n_samples);

    fclose(f);
}