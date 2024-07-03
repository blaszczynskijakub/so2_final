//
// Created by vboxuser on 4/29/24.
//

#include "Coordinates.h"

int Coordinates::getX() const {
    return x;
}

void Coordinates::setX(int x) {
    Coordinates::x = x;
}

int Coordinates::getY() const {
    return y;
}

void Coordinates::setY(int y) {
    Coordinates::y = y;
}

Coordinates::Coordinates(int x, int y) : x(x), y(y) {}
