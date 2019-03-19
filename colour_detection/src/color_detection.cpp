#include "../include/color_detection.hpp"

void ColorDetectionModule::showTrackbars() {
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

void ColorDetectionModule::getColor() {
    Mat imgHSV;
    cvtColor(frame, imgHSV, COLOR_BGR2HSV);
    inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), color);
    // inRange(imgHSV, Scalar(19, 24, 83), Scalar(86, 142, 255), colour);
    imshow("EdgeFeed", color);

    ftdm.thresh_callback();
}