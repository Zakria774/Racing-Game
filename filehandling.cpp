#include<fstream>
#include "game2.h"

int main(){
    
    ofstream outFile("gamedata.txt");
    outFile<<"Game initialized with track size "<<track.getWidth()<<"x"<<track.getHeight()<<endl;
    outFile.close();
    return 0;
}