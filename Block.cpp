#include "Block.hpp"

Block::Block(SDL_Renderer* r, int x, int y, BlockType t) : renderer(r), type(t), health(1) {
    rect = { x, y, 90, 30 };
    if (t == HEALTHY) health = 3;
}

void Block::render() {
    SDL_Color color;
    switch (type) {
    case INDESTRUCTIBLE: color = { 100, 100, 100, 255 }; break;
    case BONUS_HIDDEN: color = { 0, 255, 0, 255 }; break;
    case SPEED_UP: color = { 255, 0, 0, 255 }; break;
    case HEALTHY: color = { 255, 255, 0, 255 }; break;
    }
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
}

bool Block::onHit(int& score, std::vector<Bonus>& bonuses, Ball& ball) {
    switch (type) {
    case INDESTRUCTIBLE:
        ball.reflectVertical();
        return false;
    case BONUS_HIDDEN:
        bonuses.push_back(Bonus(renderer, rect.x + rect.w / 2, rect.y + rect.h));
        break;
    case SPEED_UP:
        ball.increaseSpeed();
        break;
    case HEALTHY:
        health--;
        score++;
        return health <= 0;
    }
    score++;
    return true;
}

SDL_Rect Block::getRect() const {
    return rect;
}
