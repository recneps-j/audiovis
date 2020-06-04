#include "audiovis.h"
#include <iostream>
#include "audio_helper.h"
#include "window.h"
#include "events.h"
#include "visual.h"
#include <future>
#include <SDL.h>

int exec(EventHandler& event_handler, Window& w, AudioHelper& ah) {
    while (!event_handler.ShouldQuit()) {
        event_handler.ProcessEvents();
        ah.CheckDataReady();
        w.Update();
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
    window.Init();
    window.DrawBackground();

    AudioHelper ah(&event_handler);

    OscilloscopeEffect oe(&ah.input_stream_data);
    window.SetCurrentEffect(&oe);

    event_handler.Connect(EventType::EVENT_QUIT, ah);
    event_handler.Connect(EventType::EVENT_QUIT, window);
    event_handler.Connect(EventType::EVENT_AUDIO_DATA_READY, window);

    if (!AudioHelper::InitPortAudio()) {
        std::cout << "Error initialising portaudio. Exiting...\n";
        return 1;
    }

    std::cout << "Initialised portaudio successfully\n";

    std::cout << "Starting test stream\n";
    ah.StartReadingAudio();
    
    std::thread t(&GetUserInputNB, std::ref(event_handler));
    t.detach();

    return exec(event_handler, window, ah);
}
