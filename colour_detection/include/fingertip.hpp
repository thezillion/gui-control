#ifndef FINGERTIP
#define FINGERTIP

#include <opencv2/opencv.hpp>

#define NONE 0
#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4

class Fingertip : public cv::Point {
    public:
        Fingertip(): cv::Point() {};
        Fingertip(int a, int b): cv::Point(a,b) {};
};

class Hand : public cv::Point {
    public:
        Hand(): cv::Point(), fingers(0) {};
        Hand(Fingertip fingers[], int number);
        Hand(int a, int b) : cv::Point(a, b) {};
        int fingers;
        void distanceAndDirectionFrom(Hand& a, int& distance, int& direction);
};

class Gesture{

    public:
        int fingers, direction;
        Gesture(): fingers(0), direction(0) {};
        Gesture(int a, int b): fingers(a), direction(b) {};
        friend bool operator<(const Gesture& l, const Gesture& r ){
            if (l.fingers != r.fingers)
                return l.fingers < r.fingers;
            else
                return l.direction < r.direction;
        }
};

#endif