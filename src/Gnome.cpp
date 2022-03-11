#include "Gnome.h"


Gnome::Gnome()
{
    goingx = (rand() % 3)-1;
    goingy = 0;
    pastx = pasty = 0;
    currx = curry = 2;
    nextx = nexty = 0;
    appearance = 'G';
}


void Gnome::Move(int y, int x){
    curry += y;
    currx += x;
}


void Gnome::findMove(std::vector<std::vector<char>> & maze, int potterY, int potterX){
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

int Gnome::getPastY(){
    if (pasty != 0)
        return pasty;
    return curry;
}

int Gnome::getPastX(){
    if (pastx != 0)
        return pastx;
    return currx;
}
