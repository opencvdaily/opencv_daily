/**
 * @file music_notes.cpp
 * @brief Illustrates Extraction and Removal of Horizontal Lines using Morphological Operations: Erosion and Dilation in OpenCV
 * @author opencv_daily
 * Contact: opencvdaily@gmail.com
 */


#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

void show_wait_destroy(const char* winname, cv::Mat img);

using namespace std;
using namespace cv;

// Tutorial Available at:
// https://docs.opencv.org/3.4/dd/dd7/tutorial_morph_lines_detection.html

int main(int argc, char** argv)
{
  CommandLineParser parser(argc, argv, "{@input | notes.png | input image}");
  Mat src = imread( parser.get<String>("@input"), IMREAD_COLOR);
  if (src.empty())
  {
    cout << "Could not open or find the image!\n" << endl;
    cout << "Usage: " << argv[0] << " <Input image>" << endl;
    return -1;
  }

  // Show source image
  imshow("src", src);

  // Transform source image to gray if it is not already
  Mat gray;
  if (src.channels() == 3)
  {
    cvtColor(src, gray, COLOR_BGR2GRAY);
  }
  else
  {
    gray = src;
  }
  // Show gray image
  imshow("gray", src);
  // waitKey(0);
  // show_wait_destroy("gray", gray);

  // Apply adaptiveThreshold at the bitwise_not of gray, notice the ~ symbol
  Mat bw;
  adaptiveThreshold(~gray, bw, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 15, -2);

  Mat bw2;
  cv::threshold(gray, bw2, 15, 255, THRESH_BINARY);
  imshow("Binary", bw);
  imshow("Binary2", bw2);
  imshow("Binary3", ~bw2);
  // waitKey(0);

  bw = ~bw2;

  // Show binary image
  // show_wait_destroy("binary", bw);

  // Create the images that will use to extract the horizontal and vertical lines
  Mat horizontal = bw.clone();
  Mat vertical = bw.clone();

  // Specify size on horizontal axis
  int horizontal_size = horizontal.cols / 100;

  // Create structure element for extracting horizontal lines through morphology operations
  Mat horizontalStructure = getStructuringElement(MORPH_RECT, Size(horizontal_size, 1));

  // Apply morphology operations
  erode(horizontal, horizontal, horizontalStructure, Point(-1, -1));
  dilate(horizontal, horizontal, horizontalStructure, Point(-1, -1));

  // Show extracted horizontal lines
  imshow("horizontal", horizontal);
  // show_wait_destroy("horizontal", horizontal);

  // Specify size on vertical axis
  int vertical_size = vertical.rows / 100;

  cout << "vertical.rows: " << vertical.rows << endl;
  cout << "vertical_size: " << vertical_size << endl;

  // Create structure element for extracting vertical lines through morphology operations
  Mat verticalStructure = getStructuringElement(MORPH_RECT, Size(1, vertical_size));

  // Apply morphology operations
  erode(vertical, vertical, verticalStructure, Point(-1, -1));
  dilate(vertical, vertical, verticalStructure, Point(-1, -1));

  // Show extracted vertical lines
  imshow("vertical", vertical);
  // show_wait_destroy("vertical", vertical);

  // Inverse vertical image
  bitwise_not(vertical, vertical);
  // show_wait_destroy("vertical_bit", vertical);
  imshow("vertical_bit", vertical);
  waitKey(0);

  // Extract edges and smooth image according to the logic
  // 1. extract edges
  // 2. dilate(edges)
  // 3. src.copyTo(smooth)
  // 4. blur smooth img
  // 5. smooth.copyTo(src, edges)

  // Step 1
  Mat edges;
  adaptiveThreshold(vertical, edges, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 3, -2);
  imshow("edges", edges);
  // show_wait_destroy("edges", edges);

  // Step 2
  Mat kernel = Mat::ones(2, 2, CV_8UC1);
  dilate(edges, edges, kernel);
  // show_wait_destroy("dilate", edges);
  imshow("dilate", edges);

  // Step 3
  Mat smooth;
  vertical.copyTo(smooth);

  // Step 4
  blur(smooth, smooth, Size(2, 2));

  // Step 5
  smooth.copyTo(vertical, edges);

  // Show final result
  // show_wait_destroy("smooth - final", vertical);
  imshow("smooth - final", vertical);


  Mat final_img = vertical.clone();
  // Mat dst_roi = final_img(Rect(0, 510, gray.cols, 400));
  // gray.copyTo(dst_roi);

  // gray(Rect(0, 510, gray.cols, 400)).copyTo(final_img);  // Copy ROI and replaces Final Image with ROI - Unintended result
  gray(Rect(0, 510, gray.cols, 400)).copyTo(final_img(Rect(0, 510, gray.cols, 400)));
  imshow("Final Ouput", final_img);

  waitKey(0);
  return 0;
}

void show_wait_destroy(const char* winname, cv::Mat img) {
  imshow(winname, img);
  moveWindow(winname, 500, 0);
  waitKey(0);
  destroyWindow(winname);
}