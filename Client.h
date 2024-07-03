//
// Created by vboxuser on 4/28/24.
//

#ifndef SO2_QUEUE_PROJECT1_CLIENT_H
#define SO2_QUEUE_PROJECT1_CLIENT_H


#include <thread>
#include <ncurses.h>
#include "Coordinates.h"
#include <condition_variable>
extern  std::condition_variable conditionVariable;
extern  std::condition_variable conditionVariableDirector;
extern  std::mutex threadProtect;
extern  std::vector<int> occuppiedStations;
extern bool station1;
extern bool station2;
extern bool station3;
class Client {

private:
    bool runningThread;
    char letter;
    int maxClientsOnBranch=1;

    std::thread move;

    //mocked values
    Coordinates start = Coordinates(0, 0);
    Coordinates dest = Coordinates(0, 0);
public:
    void setDest(const Coordinates &dest);

private:
    int speed;
    bool arrived = false;
    bool reachedDirector = false;

    std::thread moveClient();



public:

    void stopTread();

    bool isArrived();


public:
    Client(int speed, bool running, Coordinates start, Coordinates dest, char input_letter);

    const Coordinates &getStart() const;


    char getLetter() ;

};


#endif //SO2_QUEUE_PROJECT1_CLIENT_H
