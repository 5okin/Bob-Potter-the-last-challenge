#include "Moving.h"


Moving::Moving()
{
    this->curry = 0;
    this->currx = 0;
}


void Moving::setCoordinates(int y, int x){
    this->curry = y;
    this->currx = x;
}
