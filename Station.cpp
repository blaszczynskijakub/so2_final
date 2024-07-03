//
// Created by vboxuser on 4/28/24.
//

#include "Station.h"

Station::Station(const Coordinates &pos) : pos(pos) {}

const Coordinates &Station::getPos() const {
    return pos;
}


