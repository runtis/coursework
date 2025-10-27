#include "Snake.h"
#include <iostream>

Snake::Snake() : direction(Direction::RIGHT), growNextMove(false) {
    body.push_back(Position(15, 7));
    body.push_back(Position(14, 7)); 
    body.push_back(Position(13, 7));
}

void Snake::update() {
    if (body.empty()) return;

    Position newHead = body[0];

    switch (direction) {
    case Direction::UP: newHead.y--; break;
    case Direction::DOWN: newHead.y++; break;
    case Direction::LEFT: newHead.x--; break;
    case Direction::RIGHT: newHead.x++; break;
    }

    body.insert(body.begin(), newHead);

    if (!growNextMove) {
        body.pop_back();
    }
    else {
        growNextMove = false;
    }
}


void Snake::changeDirection(Direction newDirection) {
    // «апрещаем противоположные направлени€
    if ((direction == Direction::UP && newDirection == Direction::DOWN) ||
        (direction == Direction::DOWN && newDirection == Direction::UP) ||
        (direction == Direction::LEFT && newDirection == Direction::RIGHT) ||
        (direction == Direction::RIGHT && newDirection == Direction::LEFT)) {
        return;
    }
    direction = newDirection;
}

bool Snake::checkSelfCollision() const {
    if (body.empty()) return false;

    const Position& head = body[0];
    for (size_t i = 1; i < body.size(); i++) {
        if (head == body[i]) {
            return true;
        }
    }
    return false;
}

void Snake::grow() {
    growNextMove = true;
}

const std::vector<Position>& Snake::getBody() const {
    return body;
}