#include "opencv2/opencv.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include <string>
#include <ctime>

#ifndef CV_HAAR_SCALE_IMAGE 
#define CV_HAAR_SCALE_IMAGE 2
#endif

using namespace cv;
using namespace std;


static void grabHeadShot(vector<Rect>::iterator i, Mat red) {
    try {
        Point topleft(
                i->tl().x - ((i->br().x - i->tl().x) * 0.2), 
                i->tl().y - ((i->br().y - i->tl().y) * 0.4)
        );
        Point bottomright(
                i->br().x + ((i->br().x - i->tl().x) * 0.2), 
                i->br().y + ((i->br().y - i->tl().y) * 0.2)
        );
        rectangle(red, topleft, bottomright, Scalar(0, 0, 0), 3);  
        Mat face_roi = red(Rect(topleft, bottomright));
        time_t currtime = time(0); 
        string timestamp(asctime(localtime(&currtime))), filepath("/tmp/headshots/X.jpg"),
               to_replace("X"); 
        string fullpath = filepath.replace( 
                filepath.find("X"), 
                to_replace.length(), 
                timestamp); 

        imwrite(fullpath, face_roi);
    } catch(cv::Exception e) {
        // ROI was out of view. Just pass, it prevents clipping.
    }
}

vector<std::tuple<Point, std::string>> latest_whereabouts(); 

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
            grabHeadShot(i, red);
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
    namedWindow("headshots",1);
    for(;;)
    {
        cap >> frame; // get a new frame from camera
	red = frame.clone();
	paintfaces(haar_faces, haar_leye, haar_reye, frame, red);
        imshow("headshots", red);
        if(waitKey(30) >= 0) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
