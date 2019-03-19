#ifndef COLOR_DETECTION
#define COLOR_DETECTION

#include <opencv2/opencv.hpp>
#include "../include/fingertip_detection.hpp"

using namespace cv;

class ColorDetectionModule {

    int iLowH, iHighH, iLowS, iHighS, iLowV, iHighV;
    Mat& frame;
    Mat color;
    FingertipDetectionModule ftdm;

    int thresh = 100;
    int max_thresh = 255;
    RNG rng = RNG(12345);

    public:

    ColorDetectionModule(Mat &a) : iLowH(0), iHighH(179), iLowS(0),iHighS(255),iLowV(0),iHighV(255),frame(a),color(),ftdm(color) {}

    void showTrackbars();
    void getColor();
};

#endif