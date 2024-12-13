#include <stdio.h>

#include "../../Audeal.h"

int main() {
    adlAudio audio;

    if(adlInitAudio(&audio) != ADL_SUCCESS) {
        return adlGetError(audio.error);
    }

    adlSound sound;

    // something here causes ADL_UNKNOWN_ERROR...
    if(adlCreateSound(&sound, &audio.engine, "music.wav", true) != ADL_SUCCESS) {
        return adlGetError(sound.error);
    }


    adlUninitSound(&sound);
    adlUninitAudio(&audio);

    return 0;
}