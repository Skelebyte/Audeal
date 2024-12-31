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

#ifndef AUDEAL_HPP
#define AUDEAL_HPP

#include <iostream>

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"


class Error {
    public:
    static inline std::string getError(int code) {
        switch(code) {
            case MA_SUCCESS:
            return "MA_SUCCESS";

            default:
            return "UNKNOWN";
        };
        return "";
    }
};

class Audio {
    public:
    ma_engine engine;
    ma_result result;


    public:
    // Initialize Miniaudio Engine
    Audio() {
        result = ma_engine_init(NULL, &engine);

        if (result != MA_SUCCESS) {
            throw std::runtime_error("Failed to initialize ma_engine!");
        }
    }
    // Destructor, uninitialize the miniaudio engine.
    ~Audio() {
        ma_engine_uninit(&engine);
    }
};

class Sound {
    public:
    const char* path;
    bool playing;

    protected:
    ma_sound sound;
    ma_uint64 frame;

    private:
    ma_engine* engine;
    ma_result result;

    public:
    /**
     * Initializes the ma_sound
     * @param e A pointer to the Audio class ma_engine.
     * @param p C-Style string to the directory of the sound file, relative to the executable.
     * @param global Should the sound be heard everywhere, or in 3D space.
     * @throws std::runtime_error If failed to initialize the sound (File or internal error).
     */
    Sound(ma_engine* e, const char* p, bool global = false) : engine(e) {

        path = p;
        
        result = ma_sound_init_from_file(engine, path, 0, NULL, NULL, &sound);
        if (result != MA_SUCCESS) {
            throw std::runtime_error("Failed to initialize sound: " + std::string(path));
        }

        ma_sound_set_spatialization_enabled(&sound, !global);

    }
    // Uninitialize the ma_sound
    ~Sound() {
        ma_sound_uninit(&sound);
    }
    // when using as spatial, i think it needs to be position of sound - player position
    void spatialUpdate(float x, float y, float z) {
        ma_sound_set_position(&sound, x, y, z);
    }
    int play() {
        if(playing) {
            return MA_SUCCESS;
        }
        ma_result result = ma_sound_start(&sound);
        if(result != MA_SUCCESS) {
            throw std::runtime_error("Failed to initialize sound: " + std::string(path));
            return result;
        }
        playing = true;
        return MA_SUCCESS;
    }
    
    int stop() {
        ma_result result = ma_sound_stop(&sound);
        if(result != MA_SUCCESS) {
            throw std::runtime_error("Failed to stop sound.");
            return result;
        }
        playing = false;
        return MA_SUCCESS;
    }
    int pause() {
        frame = ma_sound_get_time_in_milliseconds(&sound);
        ma_result result = (ma_result)stop();
        if(result != MA_SUCCESS) {
            throw std::runtime_error("Failed to pause sound.");
            return result;
        }
        playing = false;
        return MA_SUCCESS;
    }
    void unpause() {
        ma_sound_set_start_time_in_milliseconds(&sound, frame);
        play();
    }
    void setVolume(float value) {
        ma_sound_set_volume(&sound, value);
    } 
    void setPan(float value) {
        ma_sound_set_pan(&sound, value);
    }
};

#endif // AUDEAL_HPP