#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include "events.h"
#include <string>

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
private:
    EventHandler* _eh;
    //Window to render to
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Surface* surface;
};

#endif // WINDOW_H