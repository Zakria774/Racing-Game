#ifndef CAR_H
#define CAR_H

#include <iostream>
#include <string>
using namespace std;
class Car{
    protected:
        float speed;
        int row, col;
        string symbol;

    public:
        Car(float s, int r, int c, string sym){
            speed = s;
            row = r;
            col = c;
            symbol = sym;
        }
        int getRow() const {
            return row;
        }
        int getCol() const {
            return col;
        }
        string getSymbol() const {
            return symbol;
        }
        void setRow(int r) {
            row = r;
        }
        void setCol(int c) {
            col = c;
        }

        virtual void move()=0; // pure virtual function
        void display(){
            cout << "Car"<<symbol<<" at (" << row << ", " << col << ") with speed " << speed << endl;
        }

};
#endif // CAR_H