//
// Created by yiping.chen on 2018/8/14.
//
#include <iostream>
#include "Hough.hpp"

using namespace std;

int main() {
    cv::Mat img = cv::imread("../1.jpg", 0);
    cout << img.cols << ' ' << img.size().height << endl;
    cout << img.rows << ' ' << img.size().width << endl;

    cout << "Start detecting..." << endl;
    HoughLines HoughDetector(img, 20, 1, 1./180.*CV_PI);
    cout << "Getting lines" << endl;
    vector<HoughLines::PolarLine> lines = HoughDetector.getLines(5);

    for (int i = 0; i < 5; i++) {
        cout << "Deteted lines: " << endl;
        cout << lines[i].rho << ' ' << lines[0].theta << ' ' << lines[i].count << endl;
    }
}

