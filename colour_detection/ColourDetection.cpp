#include <stdio.h>
#include <unistd.h>
#include <chrono>
#include <ctime>
#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

int main(int, char**)
{
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    auto start = std::chrono::system_clock::now();

    namedWindow("CameraFeed",1);
    namedWindow("EdgeFeed",1);
    namedWindow("Control", 1);

    int iLowH = 0, iHighH = 179, iLowS = 0, iHighS = 255, iLowV = 0, iHighV = 255;
    //Create trackbars in "Control" window
    createTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
    createTrackbar("HighH", "Control", &iHighH, 179);

    createTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
    createTrackbar("HighS", "Control", &iHighS, 255);

    createTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
    createTrackbar("HighV", "Control", &iHighV, 255);

    for(;;)
    {
        Mat frame, colour, imgHSV;
        cap >> frame; // get a new frame from camera
        imshow("CameraFeed", frame);

        cvtColor(frame, imgHSV, COLOR_BGR2HSV);
        inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), colour);
        imshow("EdgeFeed", colour);

        int c = waitKey(30);
        if(c == 27) break;            //Escape key
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}