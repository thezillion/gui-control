#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"

#include "../include/color_detection.hpp"

using namespace cv;

void ColorDetectionModule::thresh_callback() {
    
    /** @function thresh_callback */
    Mat src_copy = colour.clone();
    Mat threshold_output;
    Mat moms = Mat::zeros( src_copy.size(), CV_8UC3 );
    std::vector<std::vector<Point> > contours;
    std::vector<std::vector<Point> > contours1;
    std::vector<Vec4i> hierarchy;

    /// Detect edges using Threshold
    threshold( src_copy, threshold_output, thresh, 255, THRESH_BINARY );


    /// Find contours
    findContours( threshold_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) );
    // find moments of the image

    //found the moments for each contour differently and considered only those with area >100
    std::vector<std::vector<Point>> hull( contours.size() );
    Mat drawing = Mat::zeros( threshold_output.size(), CV_8UC3 );
    Mat drawing2 = Mat::zeros( threshold_output.size(), CV_8UC3 );
    for(int i=0; i< contours.size(); i++){
        Moments m = moments(contours[i], true);
        if(m.m00<100) continue;
        Point p(m.m10/m.m00, m.m01/m.m00);
        
        // show the image with a Point mark at the centroid
        circle(moms, p, 5, Scalar(255, 255, 255), -1);


        convexHull( Mat(contours[i]), hull[i], false );

        Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
        drawContours( drawing, hull, i, color, 1, 8, std::vector<Vec4i>(), 0, Point() );
        fillConvexPoly( drawing2, contours[i], 255);
    }

    imshow( "Hull demo", drawing );
    imshow( "Points", moms);
    imshow( "Polygons", drawing2);

    findContours( threshold_output, contours1, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) );
    std::vector<std::vector<Point>> hull1( contours1.size() );
    Mat drawing3 = Mat::zeros( threshold_output.size(), CV_8UC3 );
    for(int i=0; i< contours1.size(); i++){
        Moments m = moments(contours1[i], true);
        
        if(m.m00 < 100) continue;
        
        Point p(m.m10/m.m00, m.m01/m.m00);
        
        // show the image with a Point mark at the centroid
        circle(drawing3, p, 5, Scalar(255, 255, 255), -1);
    }
    imshow( "New Points", drawing3);
}