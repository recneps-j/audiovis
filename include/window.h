#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include "events.h"
#include <string>
#include "visual.h"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool InitSDL(void);
SDL_Surface* LoadPNGSurface(std::string path, SDL_Surface* surface);

class Window : public Observer {
public:
    Window(EventHandler* eh){ this->_eh = eh; };
    void CatchEvent(EventType e);
    void RunLoop(void);
    bool Init(void);
    void Draw(void);
    void Update(void);
    void DrawBackground(void);
    bool Close(void);
    bool SetCurrentEffect(VisualEffectProcessor* effect);
private:
    VisualEffectProcessor* current_effect = 0;
    EventHandler* _eh;
    //Window to render to
    SDL_Texture* bg_tex;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Surface* surface;
};

#endif // WINDOW_H