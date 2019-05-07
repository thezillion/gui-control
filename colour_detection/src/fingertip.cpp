#include "../include/fingertip.hpp"
#include <cmath>

Hand::Hand(Fingertip fingertips[], int number):cv::Point(){
    if (number > 0) {
        cv::Point acc(0,0);

        for (int i=0; i<number; i++) {
            acc += fingertips[i];
        }

        x = acc.x/number;
        y = acc.y/number;
    }
    
    fingers = number;
}

void Hand::distanceAndDirectionFrom(Hand& a, int& distance, int& direction_v, int& direction_h){
    int del_x = x - a.x, del_y = y - a.y;
    distance = pow(del_x,2) + pow(del_y,2);
    // if (abs(del_x) > abs(del_y))
        direction_h = (del_x > 0) ? LEFT : RIGHT;
    // else
        direction_v = (del_y > 0) ? UP : DOWN;
}