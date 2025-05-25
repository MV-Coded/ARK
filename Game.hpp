#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include "Paddle.hpp"
#include "Ball.hpp"
#include "Block.hpp"
#include "Bonus.hpp"

class Game {
public:
    Game();
    ~Game();
    bool init(const char* title, int width, int height);
    void run();
    void cleanup();

private:
    void handleEvents();
    void update();
    void render();
    void resetBall();

    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isRunning;

    Paddle paddle;
    Ball ball;
    std::vector<Block*> blocks;
    std::vector<Bonus> bonuses;
    bool floorActive;
    SDL_Rect floorRect;

    int score;
    int lives;
};
