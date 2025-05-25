#pragma once
#include <SDL2/SDL.h>
#include "Paddle.hpp"

class Ball {
public:
    void init(SDL_Renderer* renderer, int winW, int winH);
    void update();
    void render();
    bool checkCollision(const SDL_Rect& other);
    void reflectFromPaddle(const Paddle& paddle);
    bool isOutOfBounds() const;
    void reset();
    void reflectVertical();

    void increaseSpeed();
    void randomizeTrajectory();

private:
    SDL_Renderer* renderer;
    SDL_Rect rect;
    float dx, dy;
    int windowWidth, windowHeight;
};
