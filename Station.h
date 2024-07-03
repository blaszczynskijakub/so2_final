//
// Created by vboxuser on 4/28/24.
//

#ifndef SO2_QUEUE_PROJECT1_STATION_H
#define SO2_QUEUE_PROJECT1_STATION_H


#include "Coordinates.h"

class Station {
    Coordinates pos;
public:
    const Coordinates &getPos() const;


public:
    explicit Station(const Coordinates &pos);
};


#endif //SO2_QUEUE_PROJECT1_STATION_H
