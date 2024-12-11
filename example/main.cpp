#include <iostream>
#include "../Audeal.h"

int main() {
    Audio audio = Audio();

    // Sound instance
    Sound sound = Sound(&audio.engine, "example/music.wav");

    // Play the sound
    sound.play();

    // Just get the enter key to stop the program
    std::cout<<"enter"<<std::endl;
    std::cin.ignore();

    return 0;


}