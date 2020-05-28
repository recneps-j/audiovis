#include "audiovis.h"
#include "audio_helper.h"

int main(int argc, char const *argv[])
{
    std::cout << "Initialising PortAudio\n";
    if (!InitPortAudio()) {
        std::cout << "Error initialising portaudio. Exiting...\n";
        return 1;
    }
    std::cout << "portaudio initialised successfully\n";

    return 0;
}
