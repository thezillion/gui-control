#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "../include/init.hpp"
#include "../include/color_detection.hpp"

// using namespace cv;
// using namespace std;

cv::Mat colour, src_gray;
int thresh = 100;
int max_thresh = 255;
cv::RNG rng(12345);

void InitModule::showTrackbars() {
    // cv::namedWindow("CameraFeed",1);
    // cv::namedWindow("EdgeFeed",1);
    cv::namedWindow("Control", 1);
    // cv::namedWindow( "Hull demo", 1);

    //Create trackbars in "Control" window
    cv::createTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
    cv::createTrackbar("HighH", "Control", &iHighH, 179);

    cv::createTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
    cv::createTrackbar("HighS", "Control", &iHighS, 255);

    cv::createTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
    cv::createTrackbar("HighV", "Control", &iHighV, 255);
}

void InitModule::loop(VideoCapture &cap) {
    ColorDetectionModule c(thresh, max_thresh, rng, colour);

    for(;;) {
        cv::Mat frame0, frame, imgHSV;
        cap >> frame; // get a new frame from camera
        cv::imshow("CameraFeed", frame);
        // fastNlMeansDenoisingColoredMulti(frame0, frame, 10);
        cv::GaussianBlur(frame, frame, cv::Size(7,7), 0, 0);
        // imshow("Blur1", frame);

        cv::GaussianBlur(frame, frame, cv::Size(7,7), 0, 0);
        // imshow("Blur2", frame);

        cv::cvtColor(frame, imgHSV, COLOR_BGR2HSV);
        cv::inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), colour);
        // inRange(imgHSV, Scalar(19, 24, 83), Scalar(86, 142, 255), colour);
        cv::imshow("EdgeFeed", colour);

        c.thresh_callback();

        int c = waitKey(30);
        if(c == 27) break;            //Escape key
    }
}

void InitModule::init(VideoCapture &cap) {
    loop(cap);
}