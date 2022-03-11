#ifndef potter_h
#define potter_h

#include <iostream>
#include <string>
#include "Moving.h"


class Potter : public Moving
{


public:
    Potter ();
    void Move(int, int);

    void findMove(std::vector<std::vector<char>> &, int=0, int=0);
};

#endif