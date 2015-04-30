#include "opencv2/opencv.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

static void redify(const Mat frame, Mat red) {
	Vec3b pixel;
	for (int i = 0; i < frame.rows; ++i) {
		for (int j = 0; j < frame.cols; ++j) {
			pixel = frame.at<Vec3b>(i,j);
			pixel[0] = 0; // set Blue and Green to 0.
			pixel[1] = 0;
			red.at<Vec3b>(i,j) = pixel;
		}
	}
}

static void paintfaces(CascadeClassifier& haar_faces, CascadeClassifier& haar_leyes, CascadeClassifier& haar_reyes, const Mat frame, Mat red) {
	vector<Rect> faces;
	vector<Rect> leyes;
	vector<Rect> reyes;
	haar_faces.detectMultiScale(frame, faces, 1.1, 3, CV_HAAR_SCALE_IMAGE, Size(30,30));
	for (vector<Rect>::iterator i = faces.begin(); i != faces.end(); ++i) {
		Mat roi(frame, (*i));
		int left_eye_found = 0;
		int right_eye_found = 0;
		Rect left_eye, right_eye;
		haar_leyes.detectMultiScale(roi, leyes, 1.1, 2, CV_HAAR_SCALE_IMAGE, Size(5,5));
		haar_reyes.detectMultiScale(roi, reyes, 1.1, 2, CV_HAAR_SCALE_IMAGE, Size(5,5));
		for (vector<Rect>::iterator j = leyes.begin(); j != leyes.end(); ++j) {
			left_eye = (*j) + (*i).tl();
			left_eye_found = 1;
		}
		for (vector<Rect>::iterator j = reyes.begin(); j != reyes.end(); ++j) {
			right_eye = (*j) + (*i).tl();
			right_eye_found = 1;
		}
		if (left_eye_found && right_eye_found) {
			int center_x = (left_eye.tl().x + right_eye.br().x) / 2.0;
			int center_y = (left_eye.tl().y + right_eye.br().y) / 2.0;
			Point center(center_x, center_y);
			circle(red, center, 5, Scalar(0,0,255), -1);
/*
			rectangle(red, (*i), Scalar(0,0,255));
			rectangle(red, left_eye, Scalar(0,0,255));
			rectangle(red, right_eye, Scalar(0,0,255));
 */
		}
	}
}

int main(int, char**)
{
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    CascadeClassifier haar_faces, haar_leye, haar_reye;
    haar_faces.load("/opt/nycopencv/build/INSTALL/share/OpenCV/haarcascades/haarcascade_frontalface_alt2.xml");
    haar_leye.load("/opt/nycopencv/build/INSTALL/share/OpenCV/haarcascades/haarcascade_lefteye_2splits.xml");
    haar_reye.load("/opt/nycopencv/build/INSTALL/share/OpenCV/haarcascades/haarcascade_righteye_2splits.xml");
    Mat frame;
    Mat red;
    namedWindow("terminator",1);
    for(;;)
    {
        cap >> frame; // get a new frame from camera
	red = frame.clone();
	redify(frame, red);
	paintfaces(haar_faces, haar_leye, haar_reye, frame, red);
        imshow("terminator", red);
        if(waitKey(30) >= 0) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
