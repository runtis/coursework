#include "Food.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

Food::Food() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

void Food::update() {
}

void Food::respawn(int maxX, int maxY, const std::vector<Position>& snakeBody) {
    int attempts = 0;
    const int maxAttempts = 50;

    do {
        setPosition(1 + rand() % (maxX - 2), 1 + rand() % (maxY - 2));
        attempts++;

        if (attempts >= maxAttempts) {
            setPosition(rand() % maxX, rand() % maxY);
            break;
        }

    } while (!isValidPosition(position, snakeBody, maxX, maxY));
}

bool Food::isValidPosition(const Position& pos, const std::vector<Position>& snakeBody, int maxX, int maxY) const {
    bool isInCorner = (pos.x <= 0 || pos.x >= maxX - 1) &&
        (pos.y <= 0 || pos.y >= maxY - 1);

    if (isInCorner) {
        return false;
    }

    for (const auto& bodyPart : snakeBody) {
        if (pos == bodyPart) {
            return false;
        }
    }

    return true;
}