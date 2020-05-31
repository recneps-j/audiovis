#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include "events.h"

bool InitSDL(void);

class Window : public Observer {
public:
    Window(EventHandler* eh){ this->_eh = eh; };
    void CatchEvent(EventType e);
    void RunLoop(void);
    bool init(void);
    void draw(void);
    void update(void);
    bool close(void);
private:
    EventHandler* _eh;
    //Window to render to
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Surface* surface;
};

#endif // WINDOW_H