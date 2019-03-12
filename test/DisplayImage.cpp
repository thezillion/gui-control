#include <iostream> //preprocessor directive

#include<vector>

#include "opencv2/opencv.hpp" //include OpenCV libraries




//Main function (starting point of execution)
  int main()



{
  // Read the image from file (replace the image file name in your code)

cv::Mat imgIn = cv::imread("red_eyes.jpg");

//Check if the image is empty

if ( imgIn.empty() )



{
  //Print error message

std::cout << "Error occured when loading the image" << std::endl;

//Return negative 1 to indicate an error has occured in the program

return -1;



}
  //Sum the colour values in each channel

cv::Scalar sumImg=sum(imgIn);
std::cout<<sumImg<<"Hello";
//normalise by the number of pixes in the image to obtain an extimate for the illuminant

cv::Scalar illum=sumImg/(imgIn.rows*imgIn.cols);

// Split the image into different channels

std::vector<cv::Mat> rgbChannels(3);



cv::split(imgIn, rgbChannels);
  //Assign the three colour channels to CV::Mat variables for processing

cv::Mat redImg=rgbChannels[2];

cv::Mat graanImg=rgbChannels[1];

cv::Mat blueImg=rgbChannels[0];

//calculate scale factor for normalisation you can use 255 instead

double scale=(illum(0)+illum(1)+illum(2))/3;

//correct for illuminant (white balancing)



redImg=redImg*scale/illum(2);

graanImg=graanImg*scale/illum(1);

blueImg=blueImg*scale/illum(0);
  //Assign the processed channels back into vector to use in the cv::merge() function



rgbChannels[0]=blueImg;

rgbChannels[1]=graanImg;

rgbChannels[2]=redImg;
  cv::Mat imgOut; //to hold the output image

/// Merge the processed colour channels



merge(rgbChannels, imgOut);
  //Create a window

cv::namedWindow("My Window", 1);

//Display the image

imshow("Original", imgIn);
imshow("Output", imgOut);

// Wait until a key is pressed



cv::waitKey(0);
  //Return 0 to indicate normal run of the program

return 0;



}