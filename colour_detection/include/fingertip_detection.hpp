#include <opencv2/opencv.hpp>

using namespace cv;

class FingertipDetectionModule {
    int thresh = 100;
    int max_thresh = 255;
    RNG rng;
    Mat& colour;

    public:
        FingertipDetectionModule(Mat& a): thresh(100), max_thresh(255), rng(12345), colour(a) {}

        void thresh_callback();
};
