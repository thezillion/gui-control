#include "../include/fingertip.hpp"
#include <cmath>

Hand::Hand(Fingertip fingertips[], int number):cv::Point(){
    if(number>0){
        int x_cum=0, y_cum=0;
        cv::Point acc(0,0);
        for(int i=0;i<number;i++){
            acc +=fingertips[i];
        }
        x = acc.x/number;
        y = acc.y/number;
    }
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