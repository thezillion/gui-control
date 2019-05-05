#include "../include/fingertip.hpp"
#include <cmath>

Hand::Hand(Fingertip fingertips[], int number){
    int x_cum=0, y_cum=0;
    for(int i=0;i<number;i++){
        x_cum += fingertips[i].x;
        y_cum += fingertips[i].y;
    }
    x = x_cum/number;
    y = y_cum/number;
    fingers = number;
}

void Hand::distanceAndDirectionFrom(Hand& a, int& distance, int& direction){
    int del_x = a.x - x, del_y = a.y - y;
    distance = pow(del_x,2) + pow(del_y,2);
    if( abs(del_x) > abs(del_y) )
        direction = (del_x>0) ? LEFT : RIGHT;
    else
        direction = (del_y>0) ? DOWN : UP;
}