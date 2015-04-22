#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

void difference_filter(Mat frame_motion_blur, Mat frame) {
    Vec3b pixel, pixel_old, pixel_ma;
    for (int i = 0; i < frame.rows; ++i) {
        for (int j = 0; j < frame.cols; ++j) {
            pixel = frame.at<Vec3b>(i, j);
            pixel_old = frame_motion_blur.at<Vec3b>(i,j);
            double R = pixel[0], R_old = pixel_old[0];
            double G = pixel[1], G_old = pixel_old[1];
            double B = pixel[2], B_old = pixel_old[2];
            
            double thresh = 0.8;
            double R_ma = R * (1-thresh) + R_old * thresh;
            double G_ma = G * (1-thresh) + G_old * thresh;
            double B_ma = B * (1-thresh) + B_old * thresh;
            pixel_ma[0] = R_ma;
            pixel_ma[1] = G_ma;
            pixel_ma[2] = B_ma;
            frame_motion_blur.at<Vec3b>(i,j) = pixel_ma;
        }
    }
}

int main(int, char**)
{
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    Mat frame;
    Mat frame_motion_blur;
    cap >> frame; // get a new frame from camera
    frame_motion_blur = frame.clone();
    namedWindow("blurred",1);
    for(;;)
    {
        cap >> frame; // get a new frame from camera
        difference_filter(frame_motion_blur, frame);
        imshow("blurred", frame_motion_blur);
        if(waitKey(30) >= 0) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
