#include <opencv2/opencv.hpp>

using namespace cv;

class InitModule {

    int iLowH, iHighH, iLowS, iHighS, iLowV, iHighV;

    public:

    InitModule() : iLowH(0), iHighH(179), iLowS(0),iHighS(255),iLowV(0),iHighV(255) {}

    void showTrackbars();

    void loop(cv::VideoCapture&);

    void init(cv::VideoCapture&);

};