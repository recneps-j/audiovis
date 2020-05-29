#include "audiovis.h"
#include <iostream>
#include "audio_helper.h"
#include "window.h"
#include "events.h"
#include <future>

int exec(EventHandler& event_handler) {
    while (!event_handler.ShouldQuit()) {
        event_handler.ProcessEvents();
    }
    return 0;
}

int main(int argc, char const *argv[])
{   
    if (!InitSDL()) {
        std::cout << "Error initialising SDL. Exiting...\n";
        return 1;
    }
    std::cout << "Initialised SDL successfully\n";

    Window window = Window();
    window.init();

    AudioHelper ah;
    if (!AudioHelper::InitPortAudio()) {
        std::cout << "Error initialising portaudio. Exiting...\n";
        return 1;
    }

    std::cout << "Initialised portaudio successfully\n";

    std::cout << "Starting test stream\n";
    ah.StartReadingAudio();

    EventHandler event_handler;

    return exec(event_handler);
}
