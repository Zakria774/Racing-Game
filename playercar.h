#ifndef PLAYERCAR_H
#define PLAYERCAR_H
#include "car.h"
#include <sstream>

class PlayerCar : public Car {
    public:
        PlayerCar(float s, int r, int c, string sym) : Car(s, r, c, sym) {}
        void move() override {
            // the movement logic for the player's car
            string line;
            cout << "Enter command (w/a/s/d to move): ";

            cout<<">>";
            getline(cin, line);

            stringstream ss(line);
            string command;
            ss >> command;

            if(command == "w") {
                row++;
            } else if(command == "s") {
                row--;
            } else if(command == "a") {
                col--;
            } else if(command == "d") {
                col++;
            } else {
                cout << "Invalid command! Use w/a/s/d to move.\n";
            }

        }

        };
#endif