#include "Paddle.hpp"

void Paddle::init(SDL_Renderer* r, int winW, int winH) {
    renderer = r;
    windowWidth = winW;
    rect = { winW / 2 - 50, winH - 40, 100, 20 };
    speed = 7;
}

void Paddle::handleInput(const Uint8* keys) {
    if (keys[SDL_SCANCODE_LEFT]) rect.x -= speed;
    if (keys[SDL_SCANCODE_RIGHT]) rect.x += speed;
    if (rect.x < 0) rect.x = 0;
    if (rect.x + rect.w > windowWidth) rect.x = windowWidth - rect.w;
}

void Paddle::update() {}

void Paddle::render() {
    SDL_SetRenderDrawColor(renderer, 200, 200, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
}

SDL_Rect Paddle::getRect() const {
    return rect;
}

void Paddle::resize(int delta) {
    rect.w += delta;
    if (rect.w < 30) rect.w = 30;
}

void Paddle::reset() {
    rect.x = windowWidth / 2 - rect.w / 2;
}
