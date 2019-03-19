#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "../include/init.hpp"
#include "../include/color_detection.hpp"

using namespace cv;
using namespace std;

void InitModule::loop(VideoCapture &cap) {
    Mat frame0, frame, imgHSV;
    ColorDetectionModule c(frame);
    c.showTrackbars();
    start = std::chrono::system_clock::now();
    for(;;) {
        cap >> frame; // get a new frame from camera
        imshow("CameraFeed", frame);
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        // std::time_t end_time = std::chrono::system_clock::to_time_t(end);
        if(elapsed_seconds.count()>=0.5){
            start = end;
            // fastNlMeansDenoisingColoredMulti(frame0, frame, 10);
            GaussianBlur(frame, frame, Size(7,7), 0, 0);
            // imshow("Blur1", frame);

            GaussianBlur(frame, frame, Size(7,7), 0, 0);
            // imshow("Blur2", frame);

            // c.thresh_callback();
            c.getColor();
        }
        int c = waitKey(30);
        if(c == 27) break;            //Escape key
    }
}

void InitModule::init(VideoCapture &cap) {
    loop(cap);
}