/**
 * @file color_space_converter.h
 * @brief Interface for the Color Space Converter class
 * @author opencv_daily
 * Contact: opencvdaily@gmail.com
 */


#ifndef COLOR_SPACES_COLOR_SPACE_CONVERTER_H
#define COLOR_SPACES_COLOR_SPACE_CONVERTER_H

// C++ Includes
#include <cstdio>
#include <iostream>

// OpenCV Includes
#include <opencv2/core/core.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"



class ColorSpaceConverter
{
public:
  ColorSpaceConverter() {};
  void Convert(const cv::Mat& input_img);
};


#endif // COLOR_SPACES_COLOR_SPACE_CONVERTER_H