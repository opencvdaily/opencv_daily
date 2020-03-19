/**
 * @file brightness_and_contrast.cpp
 * @brief Illustrates Brightness and Contrast Adjustments for Images using OpenCV
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

// Optimized
// Alpha - Adjusts Contrast
// Beta - Adjusts Brightness
// https://docs.opencv.org/2.4/doc/tutorials/core/basic_linear_transform/basic_linear_transform.html

// Brightness Factor: -100 (Dark) to 100 (Bright)
void AdjustBrightness(const cv::Mat& img, double brighten_factor, cv::Mat& bightened_img)
{
  double alpha = 1.0;
  double beta = brighten_factor;

  img.convertTo(bightened_img, -1, alpha, beta);  
  imshow("Brightened Image", bightened_img);
  waitKey(10);
}

// Contrast: 1.0 - 3.0
void AdjustContrast(const cv::Mat& img, double contrast_factor, cv::Mat& contrasted_img)
{
  double alpha = contrast_factor;
  double beta = -100;

  img.convertTo(contrasted_img, -1, alpha, beta);  
  imshow("Contrasted Image", contrasted_img);
  waitKey(0);
}

int main(int argc, char** argv)
{
  if (argc <= 3)
  {
    std::cout << "\033[91mEnter File Path for Image, Brightness Factor and Contrast Factor then Run Again.\033[m" << std::endl;
  }
  else
  {
    std::string file_name = argv[1];

    cv::Mat img = cv::imread(file_name, 1);

    if (img.empty())
    {
      std::cout << "\033[91mCannot read the image: " << file_name << "\033[m" << std::endl;
      return -1;
    }

    imshow("Input Image", img);
    waitKey(10);

    // TODO Input Checking
    double brighten_factor = std::stod(argv[2]);
    double contrast_factor = std::stod(argv[3]);

    std::cout << "\033[92mbrighten_factor: " << brighten_factor << "\033[m" << std::endl;
    std::cout << "\033[93mcontrast_factor: " << contrast_factor << "\033[m" << std::endl;

    cv::Mat bightened_img, contrasted_img;
    AdjustBrightness(img, brighten_factor, bightened_img);
    AdjustContrast(img, contrast_factor, contrasted_img);
  }
  return 0;
}