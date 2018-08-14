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
        int count;
    };
    HoughLines(cv::Mat& img, int threshold, float rho=1, float theta=float(1./180.*CV_PI),
               float min_theta=0, float max_theta=float(CV_PI));
    vector<PolarLine> getLines(int topNum=1);

private:
    struct hough_cmp_gt {
        hough_cmp_gt(const int* _aux) : aux(_aux) {}
        inline bool operator()(int l1, int l2) const {
            return aux[l1] > aux[l2] || (aux[l1] == aux[l2] && l1 < l2);
        }
        const int* aux;
    };

    const cv::Mat img_;
    int threshold_;
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
    vector<int> sortBuf_;

    void createTrigTable();
    void initAccumTable();
    void findLocalMax();
};
#endif //UNTITLED_HOUGH_HPP

