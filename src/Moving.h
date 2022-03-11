#ifndef moving_h
#define moving_h

#include <iostream>
#include <string>
#include <vector>

class Moving
{
protected:
    char            appearance;
    int             currx ;
    int             curry ;


public:
    Moving();
    virtual void Move(int=0, int=0)=0;

    /** Function for finding a move gets everything thats required (potters location and map) for deciding next
        move. Potter, Gnome and Troll have there own findMove(), goal was for all of them to move on there own, 
        differently (not same rules)
    **/
    virtual void findMove(std::vector<std::vector<char>> &, int potterY, int potterX)=0;

    /** Move for monsters is "smart" in the sense that they have "some" logic to keep them from getting stuck.
        If they do, they find another direction (randomly) and continue moving in that direction.
    **/

    void setCoordinates(int, int);

    int currX() {return currx;}
    int currY() {return curry;}

    char style() {return appearance;}
};

#endif
