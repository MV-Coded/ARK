#pragma once
#include <SDL2/SDL.h>

class Paddle {
public:
    void init(SDL_Renderer* renderer, int winW, int winH);
    void handleInput(const Uint8* keystates);
    void update();
    void render();
    SDL_Rect getRect() const;
    void resize(int delta);
    void reset();

private:
    SDL_Renderer* renderer;
    SDL_Rect rect;
    int windowWidth;
    int speed;
};
