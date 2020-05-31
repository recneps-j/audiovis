#include "window.h"
#include <SDL.h>
#include <iostream>
#include <thread>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void Window::CatchEvent(EventType e) {
    switch (e) {
        case EventType::EVENT_QUIT:
            this->close();
            break;
        default:
            break;
    }
}

void Window::RunLoop(void) {
    while(true) {
        this->update();
        SDL_Delay(50);
    }
}

bool InitSDL(void) {
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
       std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << "\n";
       return false;
    }
    return true;
}

bool Window::init(void) {
    //Create window
    this->window = SDL_CreateWindow( "SDL HelloWorld", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if(this->window == NULL)
    {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        return false;
    } else {
        // gRenderer = SDL_CreateRenderer(gWindow, -1, 0);

        //Update the surface
        SDL_UpdateWindowSurface(this->window);
    }
    return true;
}

void Window::update(void) {
    SDL_Event e;                                            
    //SDL_PollEvent takes an event from the event queue   
    while (SDL_PollEvent(&e) != 0) {                         
        if (e.type == SDL_QUIT) {    
            this->_eh->TriggerEvent(EventType::EVENT_QUIT);                
            return;                                
        }                                   
    } 
}

bool Window::close(void) {
    //Destroy window
    SDL_DestroyWindow( this->window );

    //Quit SDL subsystems
    SDL_Quit();
    return true;
}