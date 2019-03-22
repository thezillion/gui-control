#ifndef FINGERTIP_TRACKING
#define FINGERTIP_TRACKING

#include <opencv2/opencv.hpp>
#include <deque>
#include "fingertip.hpp"
#include "gesture_execution.hpp"

#define BUFFER_SIZE 10
#define DISTANCE_THRESHOLD 1

using namespace cv;

class FingertipTrackingModule {
    std::deque<Hand> buffer,jitter;
    int count, direction, pos=0;
    GestureExecutionModule gm;
    Hand current;
    Size size;
    Mat can;

    public:
        bool size_set=false;
        FingertipTrackingModule(Mat& a): buffer(),jitter(),count(0),direction(0),pos(1),can(a),size_set(false),size(),gm(){};
        void set_size(Size a){ size=a; size_set=true; };
        void track(Hand a);
        void flush();
};

#endif