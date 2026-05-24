#ifndef AICAR_H
#define AICAR_H

#include "car.h"
#include <random>
#include <cstdlib>

class AICar : public Car {
public:
    AICar(float s, int r, int c, string sym) : Car(s, r, c, sym) {}
    void move() override {
        // Always move forward
        row++;

        // Optional: random lateral movement
        int choice = rand() % 3;
        if(choice == 0) col--;   // move left
        else if(choice == 1) col++; // move right
        // choice == 2 → stay in lane
    }
};


#endif