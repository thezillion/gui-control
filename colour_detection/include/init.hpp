#ifndef INIT_MODULE
#define INIT_MODULE

#include <opencv2/opencv.hpp>

using namespace cv;

class InitModule {
    std::chrono::system_clock::time_point start;

    public:

    void loop(VideoCapture&);

    void init(VideoCapture&);

};

#endif