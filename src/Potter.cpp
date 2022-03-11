#include "Potter.h"


Potter::Potter()
{
    appearance = 'B';
}

void Potter::Move(int y, int x){
    curry += y;
    currx += x;
}

void Potter::findMove(std::vector<std::vector<char>> & maze, int a, int b){
    /*
    Class should contain Bob Potter logic for moving, getting jems and avoiding monsters on his own
    for the game to be able to play "demo" mode.
    */
}
