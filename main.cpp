//
// Created by yiping.chen on 2018/8/14.
//
#include <iostream>
#include "Hough.hpp"
#include "ImageUtils.hpp"

using namespace std;

int main(int argc, char* argv[]) {
//    cv::Mat img = cv::imread(argv[1], 0);

    int degree = rand()%361;
    cv::Mat img = initSquare(512, 120, degree);

    cout << "Start detecting..." << endl;
    HoughLines HoughDetector(img, 20, 1, 1./180.*CV_PI);
    cout << "Getting lines" << endl;
    vector<HoughLines::PolarLine> lines = HoughDetector.getLines(5);

    for (int i = 0; i < 5; i++) {
        cout << "Deteted lines: " << endl;
        cout << lines[i].rho << ' ' << lines[0].theta << ' ' << lines[i].count << endl;
    }
}

cv::Mat initSquare(int imgSize, int objSize, int degree) {
    cv::Mat img = cv::Mat::zeros(imgSize, imgSize, CV_32SC1);
    cv::Mat_ cimg = img;

    for (int i = (imgSize/2 - objSize/2); i < (imgSize/2 + objSize/2); i++) {
        for (int j = (imgSize/2 - objSize/2); j < (imgSize/2 + objSize/2); j++) {
            cimg(i, j) = 255;
        }
    }

    rotateImage(img, degree);

    int offX = int(rand()%61 - objSize*0.2);
    int offY = int(rand()%61 - objSize*0.2);
    translateImage(img, offX, offY);

    return img;
}