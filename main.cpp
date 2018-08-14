//
// Created by yiping.chen on 2018/8/14.
//
#include <iostream>
#include "hough.hpp"

using namespace std;

int main() {
    cv::Mat img = cv::imread("../1.jpg", 0);

    cv::InputArray src_img(img);
    cout << "start detecting" << endl;
    HoughLines HoughDetector(src_img, 20, 1, 1./180.*CV_PI);
    cout << "getting lines" << endl;
    vector<HoughLines::PolarLine> lines = HoughDetector.getLines(5);

    for (int i = 0; i < 5; i++) {
        cout << "deteted lines: " << endl;
        cout << lines[i].rho << ' ' << lines[0].theta << ' ' << lines[i].count << endl;
    }
}
