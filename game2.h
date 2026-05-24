#ifndef GAME2_H
#define GAME2_H

#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "AIcar.h"
#include "playercar.h"
#include "track.h"

using namespace std;

class Game {
private:
vector<Car*> cars;
bool gameRunning;

public:
    Track track;
    Game(int trackWidth, int trackHeight)
        : track(trackWidth, trackHeight), gameRunning(true) {
        srand(time(0));
    }

    ~Game() {
        for (int i = 0; i < cars.size(); i++) {
            delete cars[i];
        }
    }

    void initializeGame() {
        cars.push_back(new PlayerCar(1.0, 0, 1, "P"));
        cars.push_back(new AICar(1.0, 0, 5, "A"));

        
    ofstream outFile("gamedata.txt");
    outFile<<"Game initialized with track size "<<track.getWidth()<<"x"<<track.getHeight()<<endl;
    outFile<<"Player car starts at (0, 1) with speed 1.0\n";
    outFile<<"AI car starts at (0, 5) with speed 1.0\n";
    outFile.close();

    }

    void displayGame() {
        cout << "\n===== TRACK =====\n";
        track.display(cars);
        cout << endl;
    }
bool checkCollision(int currentIndex) {
    for (int j = 0; j < cars.size(); j++) {
        if (j != currentIndex) {
            if (cars[currentIndex]->getRow() == cars[j]->getRow() &&
                cars[currentIndex]->getCol() == cars[j]->getCol()) {
                return true;
            }
        }
    }
    return false;
}


    void updateGame() {

    // Player moves first
    int oldRow = cars[0]->getRow();
    int oldCol = cars[0]->getCol();

    cars[0]->move();

    // Cancel if out of bounds
    if (!track.iswithinbounds(cars[0]->getRow(), cars[0]->getCol())) {
        cars[0]->setRow(oldRow);
        cars[0]->setCol(oldCol);
        cout << "Player hit boundary! Move cancelled.\n";
    }
    // Cancel if obstacle hit
    else if (track.isObstacle(cars[0]->getRow(), cars[0]->getCol())) {
        cars[0]->setRow(oldRow);
        cars[0]->setCol(oldCol);
        cout << "Player hit obstacle! Move cancelled.\n";
    }
    // Cancel if car collision
    else if (checkCollision(0)) {
        cars[0]->setRow(oldRow);
        cars[0]->setCol(oldCol);
        cout << "Player hit another car! Move cancelled.\n";
    }

    // AI cars move
    for (int i = 1; i < cars.size(); i++) {
        int prevRow = cars[i]->getRow();
        int prevCol = cars[i]->getCol();

        cars[i]->move();

        if (!track.iswithinbounds(cars[i]->getRow(), cars[i]->getCol()) ||
            track.isObstacle(cars[i]->getRow(), cars[i]->getCol()) ||
            checkCollision(i)) {
            cars[i]->setRow(prevRow);
            cars[i]->setCol(prevCol);
        }
    }
}

    void checkBoundaries() {
        for (int i = 0; i < cars.size(); i++) {
            if (!track.iswithinbounds(cars[i]->getRow(), cars[i]->getCol())) {
                if (cars[i]->getRow() < 0) {
                    cars[i]->setRow(0);
                }
                if (cars[i]->getRow() >= track.getHeight()) {
                    cars[i]->setRow(track.getHeight() - 1);
                }
                if (cars[i]->getCol() <= 0) {
                    cars[i]->setCol(1);
                }
                if (cars[i]->getCol() >= track.getWidth() - 1) {
                    cars[i]->setCol(track.getWidth() - 2);
                }
            }
        }
    }

    void checkWinner() {
        for (int i = 0; i < cars.size(); i++) {
            if (cars[i]->getRow() == track.getHeight() - 1) {
                cout << cars[i]->getSymbol() << " wins the race!" << endl;
                gameRunning = false;
            }
        }

    }

    void startGame() {
        initializeGame();

        while (gameRunning) {
            displayGame();
            updateGame();
            checkBoundaries();
            checkWinner();
        }

        ofstream outFile("gamedata.txt", ios::app);
        for (int i = 0; i < cars.size(); i++) {
            if (cars[i]->getRow() == track.getHeight() - 1) {
                outFile << "Winner of the game is " << cars[i]->getSymbol() << "\n";
            }
        }
        outFile.close();

        cout << "Game Over!" << endl;
    }
};


#endif