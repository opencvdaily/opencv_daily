/**
 * @file thresholding.cpp
 * @brief Illustrates Segmentation of an image using Simple Thresholding in OpenCV
 * @author opencv_daily
 * Contact: opencvdaily@gmail.com
 */

// C++ Includes
#include <cstdio>
#include <iostream>
#include <string>

// OpenCV Includes
#include <opencv2/core/core.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"


using cv::imshow;
using cv::waitKey;

int threshold_value = 0;
int threshold_type = 3;
int const max_value = 255;
int const max_type = 4;
int const max_binary_value = 255;

cv::Mat img, img_gray, input_img, segmented_img_mask;

cv::String window_name = "Segment Ball";


static void TrackbarThresholdingCallback(int, void*)
{
  /* 
   0: Binary
   1: Binary Inverted
   2: Threshold Truncated
   3: Threshold to Zero
   4: Threshold to Zero Inverted
  */

  int threshold_type = 0;
  cv::threshold(input_img, segmented_img_mask, threshold_value, max_binary_value, threshold_type);
  imshow(window_name, segmented_img_mask);

  cv::Mat output_img, output_img2;  
	img.copyTo(output_img, segmented_img_mask);
	img.copyTo(output_img2, ~segmented_img_mask);

	// Image with Just Ball
	imshow("Output Image", output_img);

	// Image with everything but Ball
	imshow("Output Image2", output_img2);
}


int main(int argc, char** argv)
{
  if (argc == 1)
  {
    std::cout << "\033[91mEnter File Path for Image and Run Again.\033[m" << std::endl;
  }
  else
  {
    std::string file_name = argv[1];

    img = cv::imread(file_name, 1);

    if (img.empty())
    {
      std::cout << "\033[91mCannot read the image: " << file_name << "\033[m" << std::endl;
      return -1;
    }

    imshow("Input Image", img);
    waitKey(10);

    // Convert the image from BGR to Grayscale
    // cvtColor(img, img_gray, cv::COLOR_BGR2GRAY); 

    cv::Mat hsv_img;
    cvtColor(img, hsv_img, cv::COLOR_BGR2HSV); 

    // Array to Store HSV channels
    cv::Mat hsv[3]; 

    // Split hsv img
		cv::split(hsv_img, hsv);

		input_img = hsv[0];

		imshow("Hue", hsv[0]);
		imshow("Saturation", hsv[1]);
		imshow("Value", hsv[2]);
		imshow("HSV Image", hsv_img);
    waitKey(0);


    // Must call namedWindow for Trackbar to appear
    cv::namedWindow(window_name, cv::WINDOW_AUTOSIZE); // Create a window to display results

    // Create a Trackbar to choose Threshold value
    cv::String trackbar_name = "Threshold Value";
    int max_position_of_slider = 255;
    cv::createTrackbar(trackbar_name,
                       window_name, &threshold_value,
                       max_position_of_slider, TrackbarThresholdingCallback); 

    // Call the function to initialize
    TrackbarThresholdingCallback(0, 0); 
    cv::waitKey(0);

  }
  return 0;
}