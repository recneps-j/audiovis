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

    // Create event handler object to be passed throughout the program
    EventHandler event_handler;

    // Create the main window and initialise it
    Window window = Window(&event_handler);
    window.Init();
    // window.DrawBackground();

    // Create an audiohelper object to manage Portaudio streams
    AudioHelper ah(&event_handler);

    //OscilloscopeEffect oe(&ah.input_stream_data);
    CircleEffect ce(&ah.input_stream_data);
    window.SetCurrentEffect(&ce);

    // Specify connections between event triggers and Obeserver (receiver) objects
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

    // Separate thread to check for used input in the console non-blocking. This closes down the program
    std::thread t(&GetUserInputNB, std::ref(event_handler));
    t.detach();

    // Run the main loop
    return exec(event_handler, window, ah);
}
