/**
 * @file edge_detection.cpp
 * @brief Illustrates Edge Detection using the Canny Edge Detector in OpenCV
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


using namespace cv;

int low_threshold_value = 0;
const int max_low_threshold_val = 200;  // Max position of slider
const int ratio = 3;
const int kernel_size = 3;

cv::Mat img, img_gray, edges_img, output_img;

cv::String window_name = "Image Edges";


static void TrackbarCannyThresholdCallback(int, void*)
{
  blur(img_gray, edges_img, Size(3,3));
  Canny(edges_img, edges_img, low_threshold_value, low_threshold_value*ratio, kernel_size);
  output_img = Scalar::all(0);
  img.copyTo(output_img, edges_img);
  imshow("Raw Edges", edges_img);
  imshow(window_name, output_img);
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

    output_img.create(img.size(), img.type());

    // Convert the image from BGR to Grayscale
    cvtColor(img, img_gray, cv::COLOR_BGR2GRAY); 

    // Must call namedWindow for Trackbar to appear
    cv::namedWindow(window_name, cv::WINDOW_AUTOSIZE); // Create a window to display results

    // Create a Trackbar to choose Threshold value
    cv::String trackbar_name = "Threshold Value";
    cv::createTrackbar(trackbar_name,
                       window_name, &low_threshold_value,
                       max_low_threshold_val, TrackbarCannyThresholdCallback); 

    // Call the function to initialize
    TrackbarCannyThresholdCallback(0, 0); 
    cv::waitKey(0);

  }
  return 0;
}