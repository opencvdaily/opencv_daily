/**
 * @file color_space_converter.cpp
 * @brief Implementation of the Color Space Converter class
 * @author opencv_daily
 * Contact: opencvdaily@gmail.com
 */

#include "color_space_converter.h"

// C++ Includes
#include <array>


using cv::imshow;
using cv::waitKey;


// OpenCV Color Space Conversions: https://docs.opencv.org/master/d8/d01/group__imgproc__color__conversions.html

void ColorSpaceConverter::Convert(const cv::Mat& input_img)
{
  std::array<std::pair<int, std::string>, 9> color_codes = { 
    { {cv::COLOR_BGR2HSV, "HSV"},
      {cv::COLOR_BGR2HLS, "HLS"},
      {cv::COLOR_BGR2YUV, "YUV"},
      {cv::COLOR_BGR2YCrCb, "YCrCb"},
      {cv::COLOR_BGR2Lab, "Lab"},
      {cv::COLOR_BGR2Luv, "Luv"},
      {cv::COLOR_BGR2XYZ, "CIE XYZ"},
      {cv::COLOR_BGR2GRAY, "Grayscale"},
      {cv::COLOR_BGR2BGRA, "BGRA"}
    } };

  cv::Mat output_img;
  for (const auto& code : color_codes)
  {
    cvtColor(input_img, output_img, code.first);
    putText(output_img, code.second, cv::Point(200,50), 
            cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(255,255,255), 2);
    putText(output_img, "@opencv_daily", cv::Point(300,200), 
            cv::FONT_HERSHEY_SIMPLEX, 0.75, cv::Scalar(255,255,255), 2);
    imshow("Output Image", output_img);
    waitKey(0);
  }
}