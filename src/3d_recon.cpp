#include <iostream>

#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

int main(int, char**)
{
    cv::VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    cv::Mat grey;
    cv::namedWindow("greyscale",1);
    for(;;)
    {
        cv::Mat frame;
        std::vector<cv::Point2f> corners;
        //std::vector<std::vector<cv::Point2f>> objpoints = {{}};
        // std::vector<std::vector<cv::Point2f>> imgpoints;

        cap >> frame; // get a new frame from camera
        cv::cvtColor(frame, grey, cv::COLOR_BGR2GRAY);

        cv::Size columns_x_rows(3, 3);
        bool found = cv::findChessboardCorners(frame, columns_x_rows, corners, cv::CALIB_CB_FAST_CHECK);

        if(found){
            std::cout << "FOUND THE CHESSBOARD!" << std::endl;
            cv::cornerSubPix(frame, corners, cv::Size(11, 11), cv::Size(-1, -1),
                cv::TermCriteria(cv::TermCriteria::COUNT + cv::TermCriteria::EPS, 30, 0.1));

            cv::drawChessboardCorners(frame, columns_x_rows, cv::Mat(corners), found);
            
        } else {
            std::cout << "No chessboard in this image" << std::endl;
        }

        // GaussianBlur(grey, grey, Size(7,7), 1.5, 1.5);
        // Canny(grey, grey, 0, 30, 3);
        
        cv::imshow("grey", grey);
        if(cv::waitKey(30) >= 0) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
