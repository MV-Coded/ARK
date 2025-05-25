#include "Ball.hpp"
#include <cstdlib>

void Ball::init(SDL_Renderer* r, int winW, int winH) {
    renderer = r;
    windowWidth = winW;
    windowHeight = winH;
    reset();
}

void Ball::update() {
    rect.x += dx;
    rect.y += dy;

    if (rect.x <= 0 || rect.x + rect.w >= windowWidth) dx = -dx;
    if (rect.y <= 0) dy = -dy;
}

void Ball::render() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
}

bool Ball::checkCollision(const SDL_Rect& other) {
    return SDL_HasIntersection(&rect, &other);
}

void Ball::reflectFromPaddle(const Paddle& paddle) {
    dy = -dy;
    dx += ((rect.x + rect.w / 2) - (paddle.getRect().x + paddle.getRect().w / 2)) * 0.05f;
}

bool Ball::isOutOfBounds() const {
    return rect.y > windowHeight;
}

void Ball::reset() {
    rect = { windowWidth / 2 - 10, windowHeight / 2, 15, 15 };
    dx = 4;
    dy = -4;
}

void Ball::increaseSpeed() {
    dx *= 1.02f;
    dy *= 1.02f;
}

void Ball::reflectVertical() {
    dy = -dy;
}

void Ball::randomizeTrajectory() {
    float angle = ((rand() % 120) + 30) * 3.14159f / 180.0f;
    float speed = sqrt(dx * dx + dy * dy);
    dx = speed * cos(angle);
    dy = -abs(speed * sin(angle)); 
}
