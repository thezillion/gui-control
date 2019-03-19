#ifndef FINGERTIP_DETECTION
#define FINGERTIP_DETECTION

#include <opencv2/opencv.hpp>
#include "fingertip.hpp"
using namespace cv;

class FingertipDetectionModule {
    int thresh = 100;
    int max_thresh = 255;
    RNG rng;
    Mat& colour;
    Hand current;

    public:
        FingertipDetectionModule(Mat& a): thresh(100), max_thresh(255), rng(12345), colour(a),current() {}

        void thresh_callback();
};

#endif