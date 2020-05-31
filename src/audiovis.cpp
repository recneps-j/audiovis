#include "audiovis.h"
#include <iostream>
#include "audio_helper.h"
#include "window.h"
#include "events.h"
#include <future>

int exec(EventHandler& event_handler, Window& w) {
    while (!event_handler.ShouldQuit()) {
        event_handler.ProcessEvents();
        w.update();
    }
    return 0;
}

void GetUserInputNB(EventHandler& ev) {
    std::cin.get();
    ev.TriggerEvent(EventType::EVENT_QUIT);
}

int main(int argc, char const *argv[])
{   
    if (!InitSDL()) {
        std::cout << "Error initialising SDL. Exiting...\n";
        return 1;
    }
    std::cout << "Initialised SDL successfully\n";

    EventHandler event_handler;

    Window window = Window(&event_handler);
    window.init();

    AudioHelper ah;

    event_handler.Connect(EventType::EVENT_QUIT, ah);
    event_handler.Connect(EventType::EVENT_QUIT, window);

    if (!AudioHelper::InitPortAudio()) {
        std::cout << "Error initialising portaudio. Exiting...\n";
        return 1;
    }

    std::cout << "Initialised portaudio successfully\n";

    std::cout << "Starting test stream\n";
    ah.StartReadingAudio();
    
    std::thread t(&GetUserInputNB, std::ref(event_handler));
    t.detach();

    return exec(event_handler, window);
}
