#include <opencv2/opencv.hpp>

class ColorDetectionModule {
    int thresh = 100;
    int max_thresh = 255;
    cv::RNG& rng;
    cv::Mat& colour;

    public:
        ColorDetectionModule(int a, int b, cv::RNG& c, cv::Mat& d): thresh(a), max_thresh(b), rng(c), colour(d) {}

        void thresh_callback();
};
