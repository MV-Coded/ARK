#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include "Bonus.hpp"
#include "Ball.hpp"

enum BlockType {
    INDESTRUCTIBLE,
    BONUS_HIDDEN,
    SPEED_UP,
    HEALTHY
};

class Block {
public:
    Block(SDL_Renderer* r, int x, int y, BlockType type);
    void render();
    bool onHit(int& score, std::vector<Bonus>& bonuses, Ball& ball);
    SDL_Rect getRect() const;

private:
    SDL_Renderer* renderer;
    SDL_Rect rect;
    BlockType type;
    int health;
};
