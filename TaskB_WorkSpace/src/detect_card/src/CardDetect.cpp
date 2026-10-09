#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

//H: 0-179  S: 112-200  V: 34-96

Mat process(Mat img)
{
    Mat imgHSV,mask;

    int hsvmin[3] = {0, 112, 34};
    int hsvmax[3] = {179, 200, 96};
    Scalar lower(hsvmin[0], hsvmin[1], hsvmin[2]);
    Scalar upper(hsvmax[0], hsvmax[1], hsvmax[2]);
    cvtColor(img,imgHSV,COLOR_BGR2HSV);
    inRange(imgHSV,lower,upper,mask);

    Mat kernel = getStructuringElement(MORPH_RECT, Size(7, 7));
    morphologyEx(mask, mask, MORPH_CLOSE, kernel);
    morphologyEx(mask, mask, MORPH_OPEN, kernel);

    vector<vector<Point>>contours;
    findContours(mask, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    double maxArea = 0;
    int index = -1;
    for (int i = 0; i < (int)contours.size(); i++) {
        double a = contourArea(contours[i]);
        if (a > maxArea) { maxArea = a; index = i; }
    }

    Mat result = img.clone();
    if (index >= 0 && maxArea > 1000) {  
        RotatedRect rect = minAreaRect(contours[index]);
        Point2f pts[4];
        rect.points(pts);
        //挑选顺眼的角落
        float sum = 1145141919;
        int Index = -1;
        for (int i = 0; i < 4; ++i)
        {
            line(result, pts[i], pts[(i + 1) % 4], Scalar(0, 255, 0), 3);
            if(pts[i].x+pts[i].y < sum){sum = pts[i].x+pts[i].y ; Index = i;};
        }
        Point2f ppp(pts[Index].x,pts[Index].y);
        putText(result,"ID card",ppp,FONT_HERSHEY_DUPLEX,2,Scalar(200,100,255),2);
    } 

    return result;
}

int main()
{
    // string path = "/home/adh-a-a/Task/TaskB_WorkSpace/Resource/TaskB3.jpg";
    // Mat img = imread(path);
    // Mat result = process(img);
    VideoCapture cap(2);
    Mat img,result;
    namedWindow("image",WINDOW_FREERATIO);
    namedWindow("result",WINDOW_FREERATIO);

    while(1){
        cap.read(img);
        result = process(img);
        imshow("image", img);
        imshow("result", result);
        char key = (char)waitKey(1);
        if (key == 'q' || key == 27) break;
    }

    return 0;
}