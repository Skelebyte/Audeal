#include <iostream>
#include "Audeal.hpp"

int main() {
    Audio audio = Audio();

    // Sound instance
    Sound sound = Sound(&audio.engine, "music.wav");

    // Play the sound
    sound.play();

    // Just get the enter key to stop the program
    std::cout<<"enter"<<std::endl;
    std::cin.ignore();

    sound.pause();

    // Just get the enter key to stop the program
    std::cout<<"enter"<<std::endl;
    std::cin.ignore();

    sound.unpause();

    // Just get the enter key to stop the program
    std::cout<<"enter"<<std::endl;
    std::cin.ignore();



    return 0;


}