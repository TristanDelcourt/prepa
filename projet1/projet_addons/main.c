#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "sound.h"
#include "wav.h"
#include "waveform.h"
#include "melody.h"
#include "midi.h"

int main(int argc, char** argv){
    //assert(argc==3);
    srand(time(NULL));
    
    /* stereo
    int number_of_channels;
    mix_t** m_lr = load_mix("test.txt", &number_of_channels);
    sound_t** s = reduce_mix(m_lr, number_of_channels);
    save_sound("test.wav", s, number_of_channels);
    */

    /* Read wav file
    int number_of_channels;
    sound_t** s = read_wav("test2.wav", &number_of_channels);
    save_sound("plswork.wav", s, number_of_channels);
    */

    //Read midi file
    int format, number_of_tracks, division;
    read_midi_file("hb.mid");

    return 0;
}