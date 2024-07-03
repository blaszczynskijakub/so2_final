//
// Created by vboxuser on 4/29/24.
//

#ifndef SO2_QUEUE_PROJECT1_COORDINATES_H
#define SO2_QUEUE_PROJECT1_COORDINATES_H


class Coordinates {
private:
    int x;
    int y;
public:
    Coordinates(int x, int y);

public:
    int getX() const;

    void setX(int x);

    int getY() const;

    void setY(int y);
};


#endif //SO2_QUEUE_PROJECT1_COORDINATES_H
