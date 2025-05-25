#pragma once
#include <SDL2/SDL.h>
#include "Paddle.hpp"
#include "Ball.hpp"

enum BonusType {
    PAD_SIZE,
    BALL_SPEED,
    BALL_STICKY,
    FLOOR_ONCE,
    BALL_RANDOM
};

class Bonus {
public:
    Bonus(SDL_Renderer* renderer, int x, int y);
    void update();
    void render();
    bool checkCollision(const SDL_Rect& rect);
    void applyEffect(Paddle& paddle, Ball& ball);
    void deactivate();
    bool isActive() const;

private:
    SDL_Renderer* renderer;
    SDL_Rect rect;
    BonusType type;
    bool active;
};
