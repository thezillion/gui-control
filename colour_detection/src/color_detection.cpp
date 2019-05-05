#include <vector>
#include "../include/color_detection.hpp"

#define H_RANGE 30
#define S_RANGE 70
#define V_RANGE 30

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
    int morph_size=2;
    Mat kernel = getStructuringElement( MORPH_ELLIPSE, Size( 2*morph_size + 1, 2*morph_size+1 ), Point( morph_size, morph_size ) );
    // Creating kernel matrix
    //   Mat kernel = Mat.ones(5,5, CV_32F);
    // Apply the specified morphology operation
    Mat colourCopy=color.clone();
    morphologyEx( colourCopy, color, MORPH_OPEN, kernel);
                colourCopy=color.clone();

    morphologyEx( colourCopy ,color, MORPH_CLOSE, kernel);
    imshow("EdgeFeed", color);

    ftdm.thresh_callback();
}

void ColorDetectionModule::setHSVColors(Mat image){
    int rectsize=30;
    Rect Rec(image.rows/2 - rectsize, image.cols/2 - rectsize, rectsize *2, rectsize*2);
    Mat roi=image(Rec);
    cvtColor(roi, image, COLOR_BGR2HSV);
    std::vector<Mat> channels;
    double minval,maxval;
    Point minidx, maxidx;
    split(image, channels);
    // minMaxLoc( channels[0], &minval, &maxval, &minidx, &maxidx);
    
    Scalar temp= mean(channels[0]);
    minval=maxval=temp[0];

    
    iLowH=std::max((int)minval-H_RANGE,0);
    iLowH = 0;
    std::cout<<minval-H_RANGE<<" ";
    iHighH=std::min((int)maxval+H_RANGE,179);
    iHighH = 83;
    std::cout<<iHighH<<std::endl;
    // minMaxLoc( channels[1], &minval, &maxval, &minidx, &maxidx);
    temp= mean(channels[1]);
    minval=maxval=temp[0];
    iLowS=std::max((int)minval-S_RANGE,0);
    iLowS = 62;
    iHighS=std::min((int)maxval+S_RANGE,255);
    iHighS = 180;
    // minMaxLoc( channels[2], &minval, &maxval, &minidx, &maxidx);
    
    temp= mean(channels[2]);
    minval=maxval=temp[0];
    iLowV=std::max(0,(int)minval-V_RANGE);
    iHighV=std::min(255,(int)maxval+V_RANGE);
    iLowV = 150;
    iHighV = 255;

    color_set=true;
    showTrackbars();
    destroyWindow("Select Color");
}

void ColorDetectionModule::colorSelect(Mat image){
    int rectsize=30;
    Rect Rec(image.rows/2 - rectsize, image.cols/2 - rectsize, rectsize *2, rectsize*2);
    rectangle(image, Rec, Scalar(255), 1, 8, 0);
    imshow("Select Color", image);
}