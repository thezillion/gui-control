#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "../include/init.hpp"
#include "../include/color_detection.hpp"

using namespace cv;
using namespace std;

Mat colour, src_gray;
int thresh = 100;
int max_thresh = 255;
RNG rng(12345);

void InitModule::showTrackbars() {
    // namedWindow("CameraFeed",1);
    // namedWindow("EdgeFeed",1);
    namedWindow("Control", 1);
    // namedWindow( "Hull demo", 1);

    //Create trackbars in "Control" window
    createTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
    createTrackbar("HighH", "Control", &iHighH, 179);

    createTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
    createTrackbar("HighS", "Control", &iHighS, 255);

    createTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
    createTrackbar("HighV", "Control", &iHighV, 255);
}

void InitModule::loop(VideoCapture &cap) {
    ColorDetectionModule c(thresh, max_thresh, rng, colour);

    for(;;) {
        Mat frame0, frame, imgHSV;
        cap >> frame; // get a new frame from camera
        imshow("CameraFeed", frame);
        // fastNlMeansDenoisingColoredMulti(frame0, frame, 10);
        GaussianBlur(frame, frame, Size(7,7), 0, 0);
        // imshow("Blur1", frame);

        GaussianBlur(frame, frame, Size(7,7), 0, 0);
        // imshow("Blur2", frame);

        cvtColor(frame, imgHSV, COLOR_BGR2HSV);
        inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), colour);
        // inRange(imgHSV, Scalar(19, 24, 83), Scalar(86, 142, 255), colour);
        imshow("EdgeFeed", colour);

        c.thresh_callback();

        int c = waitKey(30);
        if(c == 27) break;            //Escape key
    }
}

void InitModule::init(VideoCapture &cap) {
    loop(cap);
}