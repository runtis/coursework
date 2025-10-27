#pragma once
#include "Snake.h"
#include "Food.h"
#include <vector>
#include <memory>

class Game {
private:
    Snake snake;
    Food food;
    bool isRunning;
    int score;
    int width, height;

    static Game* instance;
    Game();

public:
    static Game* getInstance();

    void initialize();
    void run();
    void processInput();
    void update();
    void render();
    void checkCollisions();
    void gameOver();
    bool getIsRunning() const;

    int getWidth() const { return width; }
    int getHeight() const { return height; }
};