#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include "sound.h"
#include "wav.h"
#include "waveform.h"
#include "melody.h"
#include "midi.h"

int main(int argc, char** argv){
    srand(time(NULL));
    assert(argc==3);


    clock_t start, end;
    double cpu_time_used;

    start = clock();
    
    
    /* stereo
    */
    if (argv[1][strlen(argv[1])-1] == 't'){
        int number_of_channels;
        mix_t** m_lr = load_mix(argv[1], &number_of_channels);
        sound_t** s = reduce_mix(m_lr, number_of_channels);
        save_sound(argv[2], s, number_of_channels);
    }

    /* Read wav file
    */
    if (argv[1][strlen(argv[1])-1] == 'v'){
        int number_of_channels;
        sound_t** s = read_wav(argv[1], &number_of_channels);
        save_sound(argv[2], s, number_of_channels);
    }

    /* UNFINISHED
    //Read midi file
    int format, number_of_tracks, division;
    read_midi_file("./tests/simple.mid");
    */

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    print_time("Temps d'éxécution: ", cpu_time_used);

    return 0;
}