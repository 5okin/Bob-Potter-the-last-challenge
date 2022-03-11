#ifndef Gnome_h
#define Gnome_h

#include <iostream>
#include <string>
#include "Moving.h"


class Gnome : public Moving
{
    int     goingx;             // Current moving direction
    int     goingy;
    int     nextx;              // Suggested move
    int     nexty;
    int     pastx;              // previous pos
    int     pasty;

public:
    Gnome();
    void Move(int=0, int=0);

    // Gnome has its own findMove
    void findMove(std::vector<std::vector<char>> &, int, int);

    int getNextX() {return nextx;}
    int getNextY() {return nexty;}

    int getPastY();
    int getPastX();
};

#endif