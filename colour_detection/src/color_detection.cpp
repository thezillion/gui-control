#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"

#include "../include/color_detection.hpp"

void ColorDetectionModule::thresh_callback() {
    
    /** @function thresh_callback */
    cv::Mat src_copy = colour.clone();
    cv::Mat threshold_output;
    cv::Mat moms = cv::Mat::zeros( src_copy.size(), CV_8UC3 );
    std::vector<std::vector<cv::Point> > contours;
    std::vector<std::vector<cv::Point> > contours1;
    std::vector<cv::Vec4i> hierarchy;

    /// Detect edges using Threshold
    cv::threshold( src_copy, threshold_output, thresh, 255, THRESH_BINARY );


    /// Find contours
    cv::findContours( threshold_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );
    // find moments of the image

    //found the moments for each contour differently and considered only those with area >100
    std::vector<std::vector<cv::Point>> hull( contours.size() );
    cv::Mat drawing = cv::Mat::zeros( threshold_output.size(), CV_8UC3 );
    cv::Mat drawing2 = cv::Mat::zeros( threshold_output.size(), CV_8UC3 );
    for(int i=0; i< contours.size(); i++){
        cv::Moments m = moments(contours[i], true);
        if(m.m00<100) continue;
        cv::Point p(m.m10/m.m00, m.m01/m.m00);
        
        // show the image with a cv::Point mark at the centroid
        cv::circle(moms, p, 5, cv::Scalar(255, 255, 255), -1);


        convexHull( cv::Mat(contours[i]), hull[i], false );

        cv::Scalar color = cv::Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
        cv::drawContours( drawing, hull, i, color, 1, 8, std::vector<cv::Vec4i>(), 0, cv::Point() );
        cv::fillConvexPoly( drawing2, contours[i], 255);
    }

    cv::imshow( "Hull demo", drawing );
    cv::imshow( "Points", moms);
    cv::imshow( "Polygons", drawing2);

    cv::findContours( threshold_output, contours1, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );
    std::vector<std::vector<cv::Point>> hull1( contours1.size() );
    cv::Mat drawing3 = cv::Mat::zeros( threshold_output.size(), CV_8UC3 );
    for(int i=0; i< contours1.size(); i++){
        cv::Moments m = moments(contours1[i], true);
        
        if(m.m00 < 100) continue;
        
        cv::Point p(m.m10/m.m00, m.m01/m.m00);
        
        // show the image with a cv::Point mark at the centroid
        cv::circle(drawing3, p, 5, cv::Scalar(255, 255, 255), -1);
    }
    cv::imshow( "New Points", drawing3);
}