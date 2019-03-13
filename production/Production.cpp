#include <stdio.h>
#include <unistd.h>
#include <chrono>
#include <ctime>
#include <vector>
#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;
Mat colour, src_gray;
 int thresh = 100;
 int max_thresh = 255;
 RNG rng(12345);

void thresh_callback(int, void* );

int main(int, char**)
{
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    auto start = std::chrono::system_clock::now();

    namedWindow("Control", 1);

    int iLowH = 0, iHighH = 179, iLowS = 0, iHighS = 255, iLowV = 0, iHighV = 255;
    // Create trackbars in "Control" window
    createTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
    createTrackbar("HighH", "Control", &iHighH, 179);

    createTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
    createTrackbar("HighS", "Control", &iHighS, 255);

    createTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
    createTrackbar("HighV", "Control", &iHighV, 255);

    for(;;)
    {
        Mat frame0, frame, imgHSV;
        cap >> frame0; // get a new frame from camera
        imshow("CameraFeed", frame0);

        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        // if(elapsed_seconds.count()>1){
            resize(frame0, frame, Size(frame0.cols *0.8, frame0.rows * 0.8));
            pyrMeanShiftFiltering(frame, frame, 5, 5);
            resize(frame, frame, Size(frame.cols * 1.25, frame.rows * 1.25));

            imshow("filtered", frame);

            cvtColor(frame, imgHSV, COLOR_BGR2HSV);
            inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), colour);
            // inRange(imgHSV, Scalar(19, 24, 83), Scalar(86, 142, 255), colour);
            imshow("EdgeFeed", colour);

            thresh_callback(0, 0);
        // }

        int c = waitKey(30);
        if(c == 27) break;            //Escape key
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
/** @function thresh_callback */
void thresh_callback(int, void* ){
    Mat src_copy = colour.clone();
    Mat threshold_output;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    /// Detect edges using Threshold
    threshold( src_copy, threshold_output, thresh, 255, THRESH_BINARY );

  
    /// Find contours
    findContours( threshold_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) );
    // find moments of the image

    //found the moments for each contour differently and considered only those with area >100
    vector<vector<Point>> hull( contours.size() );
    Mat drawing = Mat::zeros( threshold_output.size(), CV_8UC3 );
    for(int i=0; i< contours.size(); i++){
        Moments m = moments(contours[i], true);
        if(m.m00<100) continue;
        // Point p(m.m10/m.m00, m.m01/m.m00);

        // show the image with a point mark at the centroid
        // circle(moms, p, 5, Scalar(255, 255, 255), -1);


        convexHull( Mat(contours[i]), hull[i], false );

        Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
        drawContours( drawing, hull, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
    }

    imshow( "Hull demo", drawing );
}