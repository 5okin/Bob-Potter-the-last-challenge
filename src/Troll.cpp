#include "Troll.h"


Troll::Troll()
{
    goingx = (rand() % 3)-1;
    goingy = 0;
    pastx = pasty = 0;
    currx = curry = 0;
    nextx = nexty = 0;
    appearance = 'T';
}


void Troll::Move(int y, int x){
    curry += y;
    currx += x;
}


void Troll::findMove(std::vector<std::vector<char>> &maze, int potterY, int potterX){
    if (currx == pastx && curry == pasty){                      // Find out if youre stuck
        int newDirection = (rand() % 3)-1;                      // Calculate new direction

        if (rand()%2 == 0){                                     // Randomly choose where to add it
            goingx = newDirection;
            goingy = 0;
        }
        else{
            goingx = 0;
            goingy = newDirection;
        }
    }
    nexty = goingy;
    nextx = goingx;

    pasty = curry;
    pastx = currx;
}

int Troll::getPastY(){
    if (pasty != 0)
        return pasty;
    return curry;
}

int Troll::getPastX(){
    if (pastx != 0)
        return pastx;
    return currx;
}
