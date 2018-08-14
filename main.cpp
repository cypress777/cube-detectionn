//
// Created by yiping.chen on 2018/8/14.
//

#include "hough.hpp"
#include <iostream>

using namespace std;

int main() {
    cv::Mat img = cv::imread("1.jpg", 0);
    cout << img.rows << ' ' << img.cols << endl;
    cout << img.step << endl;
}
