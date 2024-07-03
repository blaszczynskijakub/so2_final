#include <iostream>
#include <ncurses.h>
#include <vector>
#include <mutex>
#include <memory>
#include <random>
#include "Station.h"
#include "Coordinates.h"
#include "Client.h"
#include <condition_variable>

Coordinates director_coor = Coordinates(25, 15);
Coordinates client_coor = Coordinates(1, 15);
Station stations[3] = {Station(Coordinates(60, 25)), Station(Coordinates(60, 15)), Station(Coordinates(60, 5))};
int destStation = 0;
std::vector<std::shared_ptr<Client *>> clients;
bool directWork = true;
bool run = true;
int directorX = 25;
int directorY = 15;
bool generate = true;
std::mutex threadProtect;
std::mutex threadProtectDir;
std::mutex threadProtectFalse;
std::vector<int> occuppiedStations(3, 0);
bool station1 = false;
bool station2 = false;
bool station3 = false;
std::condition_variable conditionVariable;
std::condition_variable conditionVariableDirector;


void drawDir() {
    switch (destStation) {
        case 0:
            mvaddch(directorY, directorX, ACS_DARROW);

            break;
        case 1:
            mvaddch(directorY, directorX, ACS_RARROW);
            break;
        case 2:
            mvaddch(directorY, directorX, ACS_UARROW);

            break;
    }
}

void drawShapes() {
    for (int i = 2; i < directorX - 1; ++i) {
        mvaddch(directorY - 2, i, '.');
        mvaddch(directorY + 2, i, '.');
    }

    for (int i = 0; i < 10; ++i) {
        mvaddch(directorY + i + 2, directorX - 2, '.');
        mvaddch(directorY - i - 2, directorX - 2, '.');
    }
    for (int i = 0; i < 6; ++i) {
        mvaddch(directorY - 3 - i, directorX + 2, '.');
        mvaddch(directorY + 3 + i, directorX + 2, '.');
    }


    for (int i = 0; i < stations[0].getPos().getX() - directorX; ++i) {
        mvaddch(directorY - 2, directorX + 2 + i, '.');
        mvaddch(directorY + 2, directorX + 2 + i, '.');
    }

    for (int i = 0; i < stations[0].getPos().getX() - directorX; ++i) {
        mvaddch(directorY - 9, directorX + 2 + i, '.');
    }
    for (int i = 0; i < stations[0].getPos().getX() - directorX + 4; ++i) {
        mvaddch(directorY - 12, directorX + i - 2, '.');
    }


    for (int i = 0; i < stations[0].getPos().getX() - directorX; ++i) {
        mvaddch(directorY + 9, directorX + 2 + i, '.');
    }
    for (int i = 0; i < stations[0].getPos().getX() - directorX + 4; ++i) {
        mvaddch(directorY + 12, directorX + i - 2, '.');
    }


    for (int i = 0; i < 3; ++i) {
        mvaddch(directorY + 10 + i, 1 + directorX + stations[0].getPos().getX() - directorX - 3, '*');
    }
    for (int i = 0; i < 3; ++i) {
        mvaddch(directorY + 10 + i, 5 + directorX + stations[0].getPos().getX() - directorX - 3, '*');
    }


    for (int i = 0; i < 3; ++i) {
        mvaddch(directorY - 9 - i, 1 + directorX + stations[0].getPos().getX() - directorX - 3, '*');
    }
    for (int i = 0; i < 3; ++i) {
        mvaddch(directorY - 9 - i, 5 + directorX + stations[0].getPos().getX() - directorX - 3, '*');
    }


    for (int i = 0; i < 4; ++i) {
        mvaddch(directorY + 2 - i, 1 + directorX + stations[0].getPos().getX() - directorX - 3, '*');
    }
    for (int i = 0; i < 4; ++i) {
        mvaddch(directorY + 2 - i, 5 + directorX + stations[0].getPos().getX() - directorX - 3, '*');
    }


}

void changeDir() {
    while (directWork) {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        if (destStation != 2) {
            destStation += 1;
        } else {
            destStation = 0;
        }
    }
}


void generateClients() {
    int nextLetter = 0;
    char letter;
    int speed;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> random_letter(0, 30);
    std::uniform_int_distribution<> random_sleep(1, 4);
    std::uniform_int_distribution<> random_speed(1, 9);
    while (generate) {
        letter = 'A' + (nextLetter % 30);
        nextLetter++;
        speed = 1 + random_speed(gen);
        auto newClient = std::make_shared<Client *>(
                new Client(speed, true, Coordinates(client_coor.getX(), client_coor.getY()),
                           Coordinates(director_coor.getX(), director_coor.getY()), letter));
        threadProtect.lock();
        clients.emplace_back(newClient);
        threadProtect.unlock();
        std::this_thread::sleep_for(std::chrono::seconds(random_sleep(gen)));


    }

}


int main() {


    initscr();
    curs_set(0);

    nodelay(stdscr, TRUE);
    std::thread clientGeneratorThread(&generateClients);
    std::thread directorThread(&changeDir);
    drawShapes();
    while (run) {

        erase();
        drawDir();
        drawShapes();


        for (auto &client: clients) {
            mvaddch((*client)->getStart().getY(), (*client)->getStart().getX(), (*client)->getLetter());
        }


        for (auto client = clients.begin(); client != clients.end(); client++) {
            if ((**client)->isArrived()) {
                threadProtect.lock();
                client = clients.erase(client);
                threadProtect.unlock();
                break;
            }

        }


        int ch = getch();
        if (ch == ' ') {
            endwin();
            run = false;
            generate = false;
            clientGeneratorThread.join();
            directWork = false;
            directorThread.join();
            for (auto &client: clients) {
                (*client)->stopTread();
            }
            break;
        }
        refresh();

        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }


    return 0;
}
