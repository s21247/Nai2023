#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {

    bool currentSide = false;
    bool checkingSide = true;
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        cerr << "error while opening" << endl;
        return -1;
    }
    
    do {
        Mat frame;
        Mat dst = frame;
        char m = waitKey(1);
        if (m == 'r') currentSide = !currentSide;

        if (cap.read(frame)) {

            if (currentSide) {
                flip(frame, dst, 1);
                imshow("Not-yet smart window", dst);
            }
            else
                imshow("Not-yet smart window", frame);
        }
        else {
            checkingSide = false;
        }
        if (m == 'q') {
            checkingSide = false;
        }
    } while (checkingSide);
    return 0;
}
