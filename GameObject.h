#pragma once
#include "Position.h"

class GameObject {
public:
    virtual void update() = 0;
    virtual ~GameObject() = default;

    Position getPosition() const { return position; }

protected:
    Position position;
};