#include "window.h"
#include <SDL.h>
#include <iostream>
#include <thread>
#include <SDL_image.h>
#include <string>

void Window::CatchEvent(EventType e) {
    switch (e) {
        case EventType::EVENT_QUIT:
            this->Close();
            break;
        case EventType::EVENT_AUDIO_DATA_READY:
            SDL_RenderClear(this->renderer);
            // SDL_RenderCopy(this->renderer, this->bg_tex, NULL, NULL);
            this->current_effect->DoProcessing(this->renderer);
            SDL_RenderPresent(this->renderer);
            SDL_Delay(100);
            break;
        default:
            break;
    }
}

void Window::DrawBackground(void) {   
    std::string p = "/Users/joespencer/Projects/audiovis/audiovis/img/bg.png";
    SDL_Surface* bg = LoadPNGSurface(p, this->surface);
    //Apply the image
    this->bg_tex = SDL_CreateTextureFromSurface(this->renderer, bg);
    SDL_FreeSurface(bg);
    SDL_RenderCopy(this->renderer, this->bg_tex, NULL, NULL);
    SDL_RenderPresent(this->renderer);
}

void Window::RunLoop(void) {
    while(true) {
        this->Update();
        SDL_Delay(50);
    }
}

SDL_Surface* LoadPNGSurface(std::string path, SDL_Surface* surface) {
    //The final optimized image
    SDL_Surface* optimized_surface = NULL;

    //Load image at specified path
    SDL_Surface* loaded_surface = IMG_Load(path.c_str());

    std::cout << "Loaded image OK" << std::endl;
    return loaded_surface;
}

bool InitSDL(void) {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
       std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << "\n";
       return false;
    }
    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if(!(IMG_Init(imgFlags) & imgFlags))
    {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }

    return true;
}

bool Window::Init(void) {
    //Create window
    this->window = SDL_CreateWindow( "SDL HelloWorld", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if(this->window == NULL)
    {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        return false;
    } else {
        this->renderer = SDL_CreateRenderer(this->window, -1, 0);
        this->surface = SDL_GetWindowSurface(this->window);
    }
    return true;
}

void Window::Update(void) {
    SDL_Event e;                                            
    //SDL_PollEvent takes an event from the event queue   
    while (SDL_PollEvent(&e) != 0) {                         
        if (e.type == SDL_QUIT) {    
            this->_eh->TriggerEvent(EventType::EVENT_QUIT);                
            return;                                
        }                                   
    }
    // SDL_RenderClear(this->renderer);
    // SDL_RenderCopy(this->renderer, this->bg_tex, NULL, NULL);
    // this->current_effect->DoProcessingDummy(this->renderer);
    // SDL_RenderPresent(this->renderer);
    // SDL_Delay(100);
    // Not needed as updated on an event basis
    // if (this->current_effect) {
    //     this->current_effect->DoProcessing(this->effect_renderer);
    // }
}

bool Window::Close(void) {
    //Destroy window
    SDL_DestroyTexture(this->bg_tex);
    SDL_DestroyRenderer(this->renderer);
    SDL_FreeSurface(this->surface);
    SDL_DestroyWindow(this->window);
    //Quit SDL subsystems
    SDL_Quit();
    return true;
}

bool Window::SetCurrentEffect(VisualEffectProcessor* effect) {
    this->current_effect = effect;
    return true;
}