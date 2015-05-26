#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace cv;

int main(int argc, char** argv) {
  Mat src, src_gray, edges;

  // Read the image
  src = imread(argv[1], 1);

  if (!src.data) {
    return -1;
  }

  // Convert it to gray
  cvtColor(src, src_gray, CV_BGR2GRAY);

  // Reduce the noise so we avoid false circle detection
  GaussianBlur(src_gray, src_gray, Size(9, 9), 2, 2);

  // Canny Edge Detector
  Canny(src_gray, edges, 0, 30, 3);

  vector<Vec3f> circles;

  /*
  // Apply the Hough Transform to find the circles
  HoughCircles(edges, circles, CV_HOUGH_GRADIENT, 1, edges.rows/8, 200, 100, 0, 0);

  // Draw the circles detected
  for (size_t i=0; i < circles.size(); i++) {
    Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
    int radius = cvRound(circles[i][2]);
    // circle center
    circle(src, center, 3, Scalar(0, 255, 0), -1, 8, 0);
    // circle outline
    circle(src, center, radius, Scalar(0, 0, 255), 20, 8, 0);
  }

  if (circles.size() <= 0) {
    std::cout << "No circles detected.\n";
  }

  */

  // Show your results
  namedWindow("Hough Circle Transform Demo", CV_WINDOW_AUTOSIZE);
  imshow("Hough Circle Transform Demo", src);

  waitKey(0);
  return 0;
}
