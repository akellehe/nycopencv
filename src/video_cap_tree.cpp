#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

int main(int, char**)
{
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    Mat edges;
    namedWindow("edges",1);
    for(;;)
    {
        Mat frame;
        cap >> frame; // get a new frame from camera
        cvtColor(frame, edges, COLOR_BGR2GRAY);
        // Gaussian blur uses a Gaussian kernel to blur the picture.
        GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
        
        std::vector<Vec3f> circles;

        Canny(edges, edges, 0, 30, 3);
        
        HoughCircles(edges, circles, CV_HOUGH_GRADIENT, 1, edges.rows/8, 200, 100, 0, 0);

        for (size_t i=0; i < circles.size(); i++) {
          Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
          int radius = cvRound(circles[i][2]);
          circle(frame, center, 3, Scalar(0, 255, 0), -1, 8, 0);
          circle(frame, center, radius, Scalar(0, 0, 255), 3, 8, 0);
        }
    
        imshow("edges", frame);
        if(waitKey(30) >= 0) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
