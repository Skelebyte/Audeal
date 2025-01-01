#include <iostream>
#include "Audeal.hpp"

int main() {
    adl::Audio audio = adl::Audio();

    // Sound instance
    adl::Sound sound = adl::Sound(&audio.engine, "music.wav");

    // Play the sound
    sound.play();

    // Just get the enter key to pause the sound
    std::cout<<"enter to pause"<<std::endl;
    std::cin.ignore();

    sound.pause();

    // Just get the enter key to unpause to sound
    std::cout<<"enter to unpause"<<std::endl;
    std::cin.ignore();

    sound.unpause();

    // Just get the enter key to stop the program
    std::cout<<"enter to quit"<<std::endl;
    std::cin.ignore();

    sound.stop();

    return 0;


}