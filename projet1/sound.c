#include <stdlib.h>
#include "sound.h"

void free_sound(sound_t* s){
    free(s->samples);
    free(s);
}