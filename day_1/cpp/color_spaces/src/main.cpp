/**
 * @file main.cpp
 * @brief Main entry point for color space conversion operations
 * @author opencv_daily
 * Contact: opencvdaily@gmail.com
 */

#include "color_space_converter.h"

#include <string>

using cv::imshow;
using cv::waitKey;

int main(int argc, char** argv)
{
  if (argc == 1)
  {
    std::cout << "\033[91mEnter File Name and Run Again.\033[m" << std::endl;
  }
  else
  {
    std::string file_name = argv[1];
    cv::Mat input_img = cv::imread(file_name, 1);
    cv::Mat input_img_canvas = input_img.clone();

    std::printf("\033[93m Dimensions of Input Image (wxh): {%d, %d} \033[m \n",  
                input_img.cols, input_img.rows);
    putText(input_img_canvas, "BGR", cv::Point(200,50), 
            cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(255,255,255), 2);
    putText(input_img_canvas, "@opencv_daily", cv::Point(300,200), 
            cv::FONT_HERSHEY_SIMPLEX, 0.75, cv::Scalar(255,255,255), 2);
    imshow("Input Image", input_img_canvas);
    waitKey(0);

    ColorSpaceConverter color_space_converter;
    color_space_converter.Convert(input_img);
  }
  return 0;
}