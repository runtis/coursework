#pragma once
#include "GameObject.h"
#include <vector>

class Food : public GameObject {
public:
    Food();
    void update() override;
    void respawn(int maxX, int maxY, const std::vector<Position>& snakeBody);
    bool isValidPosition(const Position& pos, const std::vector<Position>& snakeBody, int maxX, int maxY) const;

    // ƒќЅј¬Ћя≈ћ метод дл€ установки позиции
    void setPosition(int x, int y) { position.x = x; position.y = y; }
};