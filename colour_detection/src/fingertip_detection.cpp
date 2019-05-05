#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "../include/fingertip_detection.hpp"
#include "../include/fingertip.hpp"

using namespace cv;
using namespace std;

void FingertipDetectionModule::thresh_callback() {
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
    Fingertip fingers[4];
    int j=0;
    for(int i=0; i < contours.size(); i++) {
        Moments m = moments(contours[i], true);
        if(m.m00<100) continue;
        Point p(m.m10/m.m00, m.m01/m.m00);

        
        // coordinates of centroid
        // cout<< Mat(p)<< endl;
        
        // show the image with a point mark at the centroid
        circle(moms, p, 5, Scalar(255, 255, 255), -1);
        if(j < 4) {
            fingers[j] = Fingertip(p.x, p.y);
            j++;
        }
        convexHull( Mat(contours[i]), hull[i], false );

        Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
        drawContours( drawing, hull, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
        // fillConvexPoly( drawing2, contours[i], 255);
    }
    Hand h(fingers, j);
    if(!fttm.size_set)
        fttm.set_size(threshold_output.size());
    fttm.track(h);
    // imshow( "Hull demo", drawing );
    imshow( "Points", moms);
}