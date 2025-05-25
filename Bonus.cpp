#include "Bonus.hpp"
#include <cstdlib>

Bonus::Bonus(SDL_Renderer* r, int x, int y)
    : renderer(r), rect{ x, y, 20, 20 }, active(true) {
    type = static_cast<BonusType>(rand() % 5);
}

void Bonus::update() {
    rect.y += 3;
}

void Bonus::render() {
    if (!active) return;
    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
}

bool Bonus::checkCollision(const SDL_Rect& r) {
    return SDL_HasIntersection(&rect, &r);
}

extern bool floorOnceFlag;

void Bonus::applyEffect(Paddle& paddle, Ball& ball) {
    switch (type) {
    case PAD_SIZE: paddle.resize(30); break;
    case BALL_SPEED: ball.increaseSpeed(); break;
    case BALL_RANDOM: ball.randomizeTrajectory(); break;
    case FLOOR_ONCE:
        extern bool floorOnceFlag;
        floorOnceFlag = true;
        break;
    default: break;
    }
}

void Bonus::deactivate() {
    active = false;
}

bool Bonus::isActive() const {
    return active;
}
