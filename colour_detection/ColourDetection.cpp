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

class ColorDetectionModule {
    public:
        void thresh_callback();
};

class InitModule {

    std::chrono::system_clock::time_point start;
    int iLowH, iHighH, iLowS, iHighS, iLowV, iHighV;

    public:

    InitModule() : iLowH(0), iHighH(179), iLowS(0),iHighS(255),iLowV(0),iHighV(255) {}

    void showTrackbars() {
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

    void loop(VideoCapture &cap) {
        ColorDetectionModule c;

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

    void init(VideoCapture &cap) {
        loop(cap);
    }
};

void ColorDetectionModule::thresh_callback() {
    /** @function thresh_callback */
    Mat src_copy = colour.clone();
    Mat threshold_output;
    Mat moms = Mat::zeros( src_copy.size(), CV_8UC3 );
    vector<vector<Point> > contours;
    vector<vector<Point> > contours1;
    vector<Vec4i> hierarchy;

    /// Detect edges using Threshold
    threshold( src_copy, threshold_output, thresh, 255, THRESH_BINARY );


    /// Find contours
    findContours( threshold_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) );
    // find moments of the image

    //found the moments for each contour differently and considered only those with area >100
    vector<vector<Point>> hull( contours.size() );
    Mat drawing = Mat::zeros( threshold_output.size(), CV_8UC3 );
    Mat drawing2 = Mat::zeros( threshold_output.size(), CV_8UC3 );
    for(int i=0; i< contours.size(); i++){
        Moments m = moments(contours[i], true);
        if(m.m00<100) continue;
        Point p(m.m10/m.m00, m.m01/m.m00);

        
        // coordinates of centroid
        // cout<< Mat(p)<< endl;
        
        // show the image with a point mark at the centroid
        circle(moms, p, 5, Scalar(255, 255, 255), -1);


        convexHull( Mat(contours[i]), hull[i], false );

        Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
        drawContours( drawing, hull, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
        fillConvexPoly( drawing2, contours[i], 255);
    }

    imshow( "Hull demo", drawing );
    imshow( "Points", moms);
    imshow( "Polygons", drawing2);

    findContours( threshold_output, contours1, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) );
    vector<vector<Point>> hull1( contours1.size() );
    Mat drawing3 = Mat::zeros( threshold_output.size(), CV_8UC3 );
    for(int i=0; i< contours1.size(); i++){
        Moments m = moments(contours1[i], true);
        if(m.m00<100) continue;
        Point p(m.m10/m.m00, m.m01/m.m00);

        
        // coordinates of centroid
        // cout<< Mat(p)<< endl;
        
        // show the image with a point mark at the centroid
        circle(drawing3, p, 5, Scalar(255, 255, 255), -1);
    }
    imshow( "New Points", drawing3);
}

int main(int, char**)
{
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    // for(;;) {
    //     Mat frame0, frame, imgHSV;
    //     cap >> frame; // get a new frame from camera
    //     imshow("CameraFeed", frame);
    //     int c = waitKey(30);
    //     if(c == 27) break;            //Escape key
    // }

    InitModule i;
    i.init(cap);
    return 0;
}

