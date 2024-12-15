#include <stdio.h>

#include "../../Audeal.h"

int main() {
    adlAudio audio;

    if(adlInitAudio(&audio) != ADL_SUCCESS) {
        return adlGetError(audio.error);
    }

    adlSound sound;

    if(adlCreateSound(&sound, &audio.engine, "music.wav", true) != ADL_SUCCESS) {
        return adlGetError(sound.error);
    }

    adlPlaySound(&sound);

    char prev = 0;
    while(true) {
        char c = getchar();
        prev = c;
        if(c == '\n' && prev == c) {
            break;
        }
        
    }


    adlUninitSound(&sound);
    adlUninitAudio(&audio);

    return adlGetError(ADL_SUCCESS);
}