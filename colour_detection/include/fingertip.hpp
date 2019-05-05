#ifndef FINGERTIP
#define FINGERTIP

#define NONE 0
#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4

class Fingertip{
    public:
        int x, y; //Coordinates of fingertip
        Fingertip(): x(0), y(0) {};
        Fingertip(int a, int b): x(a), y(b) {};
};

class Hand{
    public:
        int x, y;
        Hand(): x(0),y(0){};
        Hand(Fingertip fingers[], int number);
        int fingers, motion;
        void distanceAndDirectionFrom(Hand& a, int& distance, int& direction);
};

#endif