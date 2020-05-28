#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>

bool InitSDL(void);

class Window
{
public:
    Window(){};
    bool init(void);
    void draw(void);
    void update(void);
    bool close(void);
private:
    //Window to render to
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Surface* surface;
};

#endif // WINDOW_H