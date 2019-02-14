#include <stdio.h>
#include <unistd.h>
#include <chrono>
#include <ctime>
#include <opencv2/opencv.hpp>
using namespace cv;

int main(int, char**)
{
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    auto start = std::chrono::system_clock::now();

    namedWindow("CameraFeed",1);
    namedWindow("EdgeFeed",1);
    for(;;)
    {
        Mat frame, edges;
        cap >> frame; // get a new frame from camera
        imshow("CameraFeed", frame);

        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        if(elapsed_seconds.count()>0.1){
            cvtColor(frame, edges, COLOR_BGR2GRAY);
            GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
            Canny(edges, edges, 3, 30, 3);
            imshow("EdgeFeed", edges);
            start = end;
        }
        int c = waitKey(30);
        if(c == 27) break;            //Escape key
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}