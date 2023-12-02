#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "sound.h"
#include "wav.h"
#include "waveform.h"
#include "melody.h"

int main(int argc, char** argv){
    //assert(argc==3);
    srand(time(NULL));

    sound_t* s = read_wav("test2.wav");

    /*
    int stereo_flag;
    mix_t** m_lr = load_mix("test2.txt", &stereo_flag);
    sound_t** s = reduce_mix(m_lr, stereo_flag);
    save_sound("test2.wav", s, stereo_flag);
    */

    return 0;
}