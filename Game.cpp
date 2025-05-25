#include "Game.hpp"
#include <cstdlib>

Game::Game() : window(nullptr), renderer(nullptr), isRunning(false), score(0), lives(3) {}

Game::~Game() {
    for (auto block : blocks) delete block;
}

bool Game::init(const char* title, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) return false;

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    paddle.init(renderer, width, height);
    ball.init(renderer, width, height);

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 5; ++j) {
            BlockType type = static_cast<BlockType>(rand() % 4);
            blocks.push_back(new Block(renderer, 100 * i, 40 * j, type));
        }
    }

    floorActive = false;
    floorRect = { 0, 580, 800, 10 }; 

    isRunning = true;
    return true;
}

void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) isRunning = false;
    }

    const Uint8* keystates = SDL_GetKeyboardState(nullptr);
    paddle.handleInput(keystates);
}

bool floorOnceFlag = false;

void Game::update() {
    paddle.update();
    ball.update();

    if (ball.checkCollision(paddle.getRect())) {
        ball.reflectFromPaddle(paddle);
    }

    for (auto it = blocks.begin(); it != blocks.end();) {
        if (ball.checkCollision((*it)->getRect())) {
            bool destroyed = (*it)->onHit(score, bonuses, ball);
            if (destroyed) {
                delete* it;
                it = blocks.erase(it);
            }
            else {
                ++it;
            }
        }
        else {
            ++it;
        }
    }

    for (auto& bonus : bonuses) {
        bonus.update();
        if (bonus.checkCollision(paddle.getRect())) {
            bonus.applyEffect(paddle, ball);
            bonus.deactivate();
        }
    }

    if (ball.isOutOfBounds()) {
        lives--;
        if (lives <= 0) isRunning = false;
        resetBall();
    }

    extern bool floorOnceFlag;
    if (floorOnceFlag) {
        floorActive = true;
        floorOnceFlag = false;
        if (floorActive && ball.checkCollision(floorRect)) {
            ball.reflectVertical();
            floorActive = false;
        }
    }
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    paddle.render();
    ball.render();
    for (auto& b : blocks) b->render();
    for (auto& bonus : bonuses) bonus.render();

    SDL_RenderPresent(renderer);

    if (floorActive) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 100);
        SDL_RenderFillRect(renderer, &floorRect);
    }
}

void Game::resetBall() {
    ball.reset();
    paddle.reset();
}

void Game::run() {
    while (isRunning) {
        handleEvents();
        update();
        render();
        SDL_Delay(16);
    }
}

void Game::cleanup() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
