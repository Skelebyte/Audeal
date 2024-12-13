/*  ================================================================================
    Audeal
    -------
    A simple addon for Miniaudio (https://github.com/mackron/miniaudio/tree/master),
    to make using it a little easier.

    License
    --------
    This is free and unencumbered software released into the public domain.

    Anyone is free to copy, modify, publish, use, compile, sell, or
    distribute this software, either in source code form or as a compiled
    binary, for any purpose, commercial or non-commercial, and by any
    means.

    In jurisdictions that recognize copyright laws, the author or authors
    of this software dedicate any and all copyright interest in the
    software to the public domain. We make this dedication for the benefit
    of the public at large and to the detriment of our heirs and
    successors. We intend this dedication to be an overt act of
    relinquishment in perpetuity of all present and future rights to this
    software under copyright law.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
    IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
    OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
    ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    OTHER DEALINGS IN THE SOFTWARE.

    or more information, please refer to <https://unlicense.org>

    ================================================================================ */

#ifndef AUDEAL_H
#define AUDEAL_H

#include <stdio.h>
#include <stdbool.h>


#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"


// Audeal error handling
typedef enum adlErrors {
    ADL_UNKNOWN_ERROR = -1,
    ADL_SUCCESS = 0,
    ADL_FAILED_TO_INIT_AUDIO = 1,
    ADL_FAILED_TO_INIT_SOUND = 2,
    ADL_FAILED_TO_PLAY_SOUND = 3,
} adlErrors;

static inline int adlGetError(adlErrors error) {
    switch(error) {
        case ADL_SUCCESS:
        printf("ADL_SUCCESS\n");
        return ADL_SUCCESS;

        case ADL_FAILED_TO_INIT_AUDIO:
        printf("ADL_FAILED_TO_INIT_AUDIO\n");
        return ADL_FAILED_TO_INIT_AUDIO;

        case ADL_FAILED_TO_INIT_SOUND:
        printf("ADL_FAILED_TO_INIT_SOUND\n");
        return ADL_FAILED_TO_INIT_SOUND;

        case ADL_FAILED_TO_PLAY_SOUND:
        printf("ADL_FAILED_TO_PLAY_SOUND\n");
        return ADL_FAILED_TO_PLAY_SOUND;

        default:
        printf("ADL_UNKNOWN_ERROR\n");
        return ADL_UNKNOWN_ERROR;
    }
}

static inline adlErrors adlSetError(adlErrors* error, adlErrors value) {
    error = &value;
    return value;
}

typedef struct adlAudio {
    ma_engine engine;
    ma_result result;

    adlErrors error;
} adlAudio;

typedef struct adlSound {
    const char* path;
    ma_sound sound;

    ma_engine* engine;
    ma_result result;

    adlErrors error;
} adlSound;


// Audeal audio
static inline adlErrors adlInitAudio(adlAudio* audio) {
    audio->result = ma_engine_init(NULL, &audio->engine);
    if(audio->result != MA_SUCCESS) {
        return adlSetError(&audio->error, ADL_FAILED_TO_INIT_AUDIO);
    }

    return adlSetError(&audio->error, ADL_SUCCESS); 
}
static inline adlErrors adlUninitAudio(adlAudio* audio) {
    ma_engine_uninit(&audio->engine);
    
    return adlSetError(&audio->error, ADL_SUCCESS);
}

// Audeal sound
static inline adlErrors adlCreateSound(adlSound* sound, ma_engine* e, const char* p, bool global) {
    sound->path = p;
    sound->engine = e;

    sound->result = ma_sound_init_from_file(sound->engine, sound->path, 0, NULL, NULL, &sound->sound);
    if(sound->result != MA_SUCCESS) {
        printf("%i", sound->result);
        return adlSetError(&sound->error, ADL_FAILED_TO_INIT_SOUND);
    }

    // ma_sound_set_spatialization_enabled(&sound->sound, !global);

    return adlSetError(&sound->error, ADL_SUCCESS);
}
static inline adlErrors adlUninitSound(adlSound* sound) {
    ma_sound_uninit(&sound->sound);

    return adlSetError(&sound->error, ADL_SUCCESS);
}



#endif // AUDEAL_H