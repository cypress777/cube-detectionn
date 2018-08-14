//
// Created by yiping.chen on 2018/8/14.
//

#include "hough.hpp"
#include <iostream>

using namespace std;

int main() {
    cv::Mat img = cv::imread("../1.jpg", 0);
    cout << img.rows << ' ' << img.cols << endl;
    cout << img.step << endl;

    HoughLines Houghdetector(img, 20, 1, 1/180*CV_PI);
    Houghlines::PolarLine lines = HoughLines.getLines(5);

    for (int i = 0; i < 5; i++) {
        cout << 'deteted lines: ' << endl;
        cout << lines[i].rho << ' ' << lines[0].theta << ' ' << lines[i].cout << endl;
    }
}
