#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <vector>
#include <cmath>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {

    int down_range[3] = { 0,90,150 }, up_range[3] = { 90,255,255 };

    VideoCapture camera(0);

    while (waitKey(1) != 27 || waitKey(1) == 'q') {

        Mat frame;
        Mat frameMaskOne, frameMaskTwo;
        Mat frameWithMask;

        camera >> frame;

        flip(frame, frame, 1);

        cvtColor(frame, frameMaskOne, COLOR_BGR2HSV);
        inRange(frameMaskOne, Scalar(down_range[0], down_range[1], down_range[2]),
            Scalar(up_range[0], up_range[1], up_range[2]), frameMaskTwo);

        vector<vector<Point>>  contours;
        findContours(frameMaskTwo, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

        //sortowanie konturów po wielkości
        sort(contours.begin(), contours.end(),
            [](auto& a, auto& b) {
                return contourArea(a, false) > contourArea(b, false);
            });


        Point center[2] = {

        };

        int changableLine = 10;
        if (contours.size() >= 2 && contourArea(contours[0]) != 0 && contourArea(contours[1]) != 0) {
        for (int i = 0; i < min(2, (int)contours.size()); i++)
        {
            approxPolyDP(contours.at(i), contours.at(i), 10, true);
            drawContours(frame, contours, i, { 0,0,255,255 });
            Rect rect = boundingRect(contours.at(i));
            //cout << (int(abs(contourArea(contours[0])/100))) << endl;
            center[i].x = rect.width / 2 + rect.x;
            center[i].y = rect.height / 2 + rect.y;
        }
        
        if (abs((center[0].y - center[1].y <= 30))) {
            line(frame, center[0], center[1], Scalar(200, 0, 0), (int(abs(contourArea(contours[0]) / 100))));
        }
    }
        imshow("contours", frame);

        if (waitKey(1) == 'q')
            break;
    }
    return 0;
}
