#include <opencv2/opencv.hpp>

using namespace cv;

class ColorDetectionModule {
    int thresh = 100;
    int max_thresh = 255;
    RNG& rng;
    Mat& colour;

    public:
        ColorDetectionModule(int a, int b, RNG& c, Mat& d): thresh(a), max_thresh(b), rng(c), colour(d) {}

        void thresh_callback();
};
