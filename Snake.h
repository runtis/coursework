#pragma once
#include "GameObject.h"
#include "Direction.h"
#include <vector>

class Snake : public GameObject {
private:
    std::vector<Position> body;
    Direction direction;
    bool growNextMove;

public:
    Snake();
    void update() override;
    void changeDirection(Direction newDirection);
    bool checkSelfCollision() const;
    void grow();
    const std::vector<Position>& getBody() const;


    void setHeadPosition(int x, int y) {
        if (!body.empty()) {
            body[0].x = x;
            body[0].y = y;
        }
    }
};