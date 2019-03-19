#include <stdio.h>
#include <unistd.h>
#include <opencv2/opencv.hpp>

#include "include/init.hpp"

using namespace cv;
using namespace std;

int main(int, char**)
{
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    InitModule i;
    // i.showTrackbars();
    i.init(cap);
    return 0;
}

