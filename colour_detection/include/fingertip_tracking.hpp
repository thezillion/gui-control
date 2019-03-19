#ifndef FINGERTIP_TRACKING
#define FINGERTIP_TRACKING

#include <opencv2/opencv.hpp>
#include <deque>

using namespace cv;

class FingertipTrackingModule {
    int movement_thresh = 100;
    dequeu motion;
    int
    direction = 
    public:
        void thresh_callback();
};

#endif