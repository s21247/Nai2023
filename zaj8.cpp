#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <vector>
#include <cmath>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {

    int lower_range[3] = { 0,100,120 }, higher_range[3] = { 45,190,185 };

    VideoCapture cap(0);

    do {

        Mat frame;
        Mat frameMask, frameMask2;
        Mat frameWithMask;

        cap >> frame;

        flip(frame, frame, 1);

        cvtColor(frame, frameMask, COLOR_BGR2HSV);
        inRange(frameMask, Scalar(lower_range[0], lower_range[1], lower_range[2]),
            Scalar(higher_range[0], higher_range[1], higher_range[2]), frameMask2);

        vector<vector<Point>>  contours;
        findContours(frameMask2, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

        sort(contours.begin(), contours.end(),
            [](auto& a, auto& b) {
                return contourArea(a, false) > contourArea(b, false);
            });


        Point middle[2] = {};
        Point middle2[2] = {};
        Point middle3[2]= {};



        for (int i = 0; i < min(2, (int)contours.size()); i++)
        {
            approxPolyDP(contours.at(i), contours.at(i), 10, true);
            drawContours(frame, contours, i, { 0,0,255,255 });
            Rect rect = boundingRect(contours.at(i));
            middle[i].x = rect.width / 2 + rect.x;
            middle[i].y = rect.height / 2 + rect.y;
        }

        for (int i = 0; i < min(2, (int)contours.size()); i++)
        {
            approxPolyDP(contours.at(i), contours.at(i), 10, true);
            drawContours(frame, contours, i, { 0,0,255,255 });
            Rect rect = boundingRect(contours.at(i));
            middle2[i].y = rect.height + 2 / 2 + rect.y;
            middle2[i].x = rect.width / 2 + rect.x;
            middle3[i].y = rect.height - 2 / 2 + rect.y;
            middle3[i].x = rect.width / 2 + rect.x;
        }

        if (abs((middle[0].y - middle[1].y < 30))) {

            if (contours.size() % 2 != 0) {
                line(frame, middle[0], middle[1], Scalar(200, 0, 0), 10);
                line(frame, middle2[0], middle2[1], Scalar(200, 0, 0), 8);
                line(frame, middle3[0], middle3[1], Scalar(200, 0, 0), 8);
            }
            else {
                line(frame, middle[0], middle[1], Scalar(200, 0, 0), 10);
                line(frame, middle2[0], middle2[1], Scalar(200, 0, 0), 8);

            }
            
        }
        imshow("contours", frame);

    } while (waitKey(1) != 27);
    return 0;
}
