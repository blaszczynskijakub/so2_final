//
// Created by vboxuser on 4/28/24.
//

#include <random>
#include <mutex>
#include <memory>
#include <iostream>
#include "Client.h"
#include "Station.h"

extern int destStation;
extern Station stations[];
extern std::vector<std::shared_ptr<Client *>> clients;
extern Coordinates client_coor;
extern Coordinates director_coor;
extern std::mutex threadProtect;


std::thread Client::moveClient() {
    while (runningThread) {
        if (!reachedDirector && start.getX() + 3 == dest.getX()) {

            std::unique_lock<std::mutex> lockDir(threadProtect);

            conditionVariableDirector.wait(lockDir, [&]() {

                return occuppiedStations[destStation] <= maxClientsOnBranch;
            });
            start.setX(start.getX() + 3);
            occuppiedStations[destStation] += 1;


            reachedDirector = true;
            dest = stations[destStation].getPos();


        }

        if (reachedDirector && start.getX() + 3 == dest.getX()) {
            std::unique_lock<std::mutex> lock(threadProtect);


            if (dest.getY() < 15) {
                conditionVariable.wait(lock, [&]() { return !station3; });

                start.setX(start.getX() + 3);
                station3 = true;
                lock.unlock();
                std::this_thread::sleep_for(std::chrono::seconds(3));
                arrived = true;
                occuppiedStations[2] -= 1;
                conditionVariableDirector.notify_all();
                runningThread = false;
                station3 = false;


                conditionVariable.notify_all();






            }

            if (dest.getY() == 15) {
                conditionVariable.wait(lock, [&]() { return !station2; });


                start.setX(start.getX() + 3);
                station2 = true;
                lock.unlock();
                std::this_thread::sleep_for(std::chrono::seconds(3));
                arrived = true;
                occuppiedStations[1] -= 1;
                conditionVariableDirector.notify_all();
                runningThread = false;
                station2 = false;


                conditionVariable.notify_all();


            }
            if (dest.getY() > 15) {
                conditionVariable.wait(lock, [&]() { return !station1; });

                start.setX(start.getX() + 3);
                station1 = true;
                lock.unlock();
                std::this_thread::sleep_for(std::chrono::seconds(3));
                arrived = true;
                occuppiedStations[0] -= 1;
                conditionVariableDirector.notify_all();
                runningThread = false;
                station1 = false;


                conditionVariable.notify_all();


            }


        } else if (start.getY() < dest.getY()) {

            start.setY(start.getY() + 1);

        } else if (start.getY() > dest.getY()) {

            start.setY(start.getY() - 1);
        } else if (start.getX() < dest.getX()) {


            start.setX(start.getX() + 1);


        }


        std::this_thread::sleep_for(std::chrono::milliseconds(500 / (speed + 1)));

    }
}


char Client::getLetter() {
    return letter;
}

Client::Client(int speed, bool running, Coordinates start, Coordinates dest,
               char input_letter) {
    this->runningThread = running;
    this->start = start;
    this->dest = dest;
    this->move = std::thread(&Client::moveClient, this);
    this->letter = input_letter;
    this->speed = speed;

}

void Client::stopTread() {
    runningThread = false;
    move.join();
}


const Coordinates &Client::getStart() const {
    return start;
}

bool Client::isArrived() {
    return arrived;
}

void Client::setDest(const Coordinates &dest) {
    Client::dest = dest;
}



