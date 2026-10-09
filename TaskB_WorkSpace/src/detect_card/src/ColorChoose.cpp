#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    // string path = "/home/adh-a-a/Task/TaskB_WorkSpace/Resource/TaskB3.jpg";
    // Mat img = imread(path);
    VideoCapture cap(2);
    Mat img,mask,imgHSV;

    int hmin = 162, smin = 68, vmin = 18;
    int hmax = 179, smax = 231, vmax = 128;  

    const string trackbarWin = "Trackbars";
    namedWindow(trackbarWin, WINDOW_AUTOSIZE);

    createTrackbar("Hue Min", trackbarWin, &hmin, 179);
    createTrackbar("Sat Min", trackbarWin, &smin, 255);
    createTrackbar("Val Min", trackbarWin, &vmin, 255);
    createTrackbar("Hue Max", trackbarWin, &hmax, 179);
    createTrackbar("Sat Max", trackbarWin, &smax, 255);
    createTrackbar("Val Max", trackbarWin, &vmax, 255);

    namedWindow("image", WINDOW_FREERATIO);
    namedWindow("mask", WINDOW_FREERATIO);

    while (true) {
        cap.read(img);

        cvtColor(img, imgHSV, COLOR_BGR2HSV);

        Scalar lower(hmin, smin, vmin);
        Scalar upper(hmax, smax, vmax);

        inRange(imgHSV, lower, upper, mask);

        imshow("image", img);
        imshow("mask", mask);

        cout << "H: " << hmin << "-" << hmax << "  S: " << smin << "-" << smax << "  V: " << vmin << "-" << vmax << "\r" << flush;

        char key = (char)waitKey(1);
        if (key == 'q' || key == 27) break; 
    }

    return 0;
}

//colcon build --cmake-args -DPython3_EXECUTABLE=/usr/bin/python3
//H: 162-179  S: 68-231  V: 18-128
//H: 139-179  S: 68-231  V: 18-128