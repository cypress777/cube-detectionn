//
// Created by yiping.chen on 2018/8/14.
//
#ifndef UNTITLED_HOUGH_HPP
#define UNTITLED_HOUGH_HPP

#include <vector>
#include "opencv2/opencv.hpp"
using namespace std;

class HoughLines {
public:
    struct PolarLine {
        float rho;
        float theta;
        int accum;
    };
    HoughLines(cv::Mat& img, float rho, float theta=float(1./180.*CV_PI), float min_theta=0, float max_theta=float(CV_PI));

private:
    cv::Mat img_;
    float thetaStep_;
    float rhoStep_;
    float minTheta_;
    float maxTheta_;
    int minRho_;
    int maxRho_;
    int numTheta_;
    int numRho_;
    cv::Mat accumTable_;
    vector<float> sinTab_;
    vector<float> cosTab_;

    void createTrigTable();
    void initAccumTable();
};
#endif //UNTITLED_HOUGH_HPP

