#ifndef TRACK_H
#define TRACK_H

#include "car.h"

    class Track {
protected:
    int width;
    int height;
    char obstacleSymbol = 'X';

public:
    Track(int w, int h) : width(w), height(h) {}

    int getWidth() const {
        return width;
    }

    int getHeight() const {
        return height;
    }

    bool iswithinbounds(int r, int c) {
        return (r >= 0 && r < height && c > 0 && c < width - 1);
    }

    void display(const vector<Car*>& cars) {
        vector<vector<string>> grid(height, vector<string>(width, " "));

        // Side boundaries
        for (int i = 0; i < height; i++) {
            grid[i][0] = "|";
            grid[i][width - 1] = "|";
        }

        // Obstacles
        if (height > 2 && width > 3) grid[2][1] = "X";
        if (height > 5 && width > 7) grid[5][5] = "X";
        if (height > 3 && width > 12) grid[3][12] = "X";

        // Place cars
        for (int i = 0; i < cars.size(); i++) {
            int r = cars[i]->getRow();
            int c = cars[i]->getCol();

            if (r >= 0 && r < height && c > 0 && c < width - 1) {
                grid[r][c] = cars[i]->getSymbol();
            }
        }
 

        // Print grid
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                cout << grid[i][j];
            }
            cout << endl;
        }
    }
bool isObstacle(int r, int c) {
    if ((r == 2 && c == 1) ||
        (r == 5 && c == 5) ||
        (r == 3 && c == 12)) {
        return true;
    }
    return false;
}
};

#endif