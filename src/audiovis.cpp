#include "audiovis.h"
#include <iostream>
#include "audio_helper.h"
#include "window.h"

int main(int argc, char const *argv[])
{   
    if (!InitSDL()) {
        std::cout << "Error initialising SDL. Exiting...\n";
        return 1;
    }
    std::cout << "Initialised SDL successfully\n";

    Window window = Window();
    window.init();
    //Update window (this should be called repetetively from another thread)
    window.update();

    AudioHelper ah;
    if (!AudioHelper::InitPortAudio()) {
        std::cout << "Error initialising portaudio. Exiting...\n";
        return 1;
    }
    std::cout << "Initialised portaudio successfully\n";

    std::cout << "Starting test stream\n";
    ah.StartReadingAudio();
    // Wait for user to stop stream
    std::cin.get();
    std::cout << "Stopping test stream\n";

    return 0;
}
