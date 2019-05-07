#ifndef FINGERTIP_DETECTION
#define FINGERTIP_DETECTION

#include <opencv2/opencv.hpp>
#include "fingertip.hpp"
#include "fingertip_tracking.hpp"
using namespace cv;

class FingertipDetectionModule {
    int thresh = 100;
    int max_thresh = 255;
    RNG rng;
    Mat& colour;
    Hand current;
    FingertipTrackingModule fttm;

    public:
        FingertipDetectionModule(Mat& a): thresh(100), max_thresh(255), rng(12345), colour(a),current(),fttm(a) {};

        void thresh_callback(int);
};

#endif