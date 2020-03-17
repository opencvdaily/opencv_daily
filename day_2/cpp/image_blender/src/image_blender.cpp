/**
 * @file image_blender.cpp
 * @brief Illustrates OpenCV functionality for blending images
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


void BlendImages(const cv::Mat& img1, const cv::Mat& img2)
{
  cv::Mat blended_img;
  double alpha = 0.5;
  double beta = (1.0 - alpha);

  cv::addWeighted(img1, alpha, img2, beta, 0.0, blended_img);

  // blended_img = img1 + img2;  // (when alpha = beta = 1.0)
  
  imshow("Blended Image", blended_img);
  waitKey(0);
}

int main(int argc, char** argv)
{
  if (argc <= 2)
  {
    std::cout << "\033[91mEnter File Path for 2 Images and Run Again.\033[m" << std::endl;
  }
  else
  {
    std::string file_name1 = argv[1];
    std::string file_name2 = argv[2];

    cv::Mat img1 = cv::imread(file_name1, 1);
    cv::Mat img2 = cv::imread(file_name2, 1);

    imshow("Image 1", img1);
    imshow("Image 2", img2);
    waitKey(0);

    BlendImages(img1, img2);
  }
  return 0;
}