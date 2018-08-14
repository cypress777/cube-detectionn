//
// Created by yiping.chen on 2018/8/14.
//
using namespace std;

#include "hough.hpp"

HoughLines::HoughLines(cv::Mat& img, float rho, float theta, float minTheta, float maxTheta) {
    img_ = img;
    thetaStep_ = theta;
    rhoStep_ = rho;
    minTheta_ = minTheta;
    maxTheta_ = maxTheta;
    numTheta_ = cvRound((maxTheta_ - minTheta_) / thetaStep_);
    maxRho_ = img_.rows + img_.cols;
    minRho_ = -1 * maxRho_;
    numRho_ = cvRound((maxRho_ - minRho_ + 1) / rhoStep_);
    accumTable_ = cv::Mat::zeros(numTheta_ + 2, numRho_ + 2, CV_32SC1);

    createTrigTable();
    initAccumTable();
}

void HoughLines::initAccumTable() {
    const uchar *image = img_.ptr();
    int *accum = accumTable_.ptr<int>();
    int step = (int)img_.step;
    int width = img_.cols;
    int height = img_.rows;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (image[i*step + j] != 0) {
                for (int n = 0; n < numTheta_; n++) {
                    int r = cvRound(j * cosTab_[n] + i * sinTab_[n]);
                    r += (numRho_ - 1)/2;
                    accum[(n+1) * (numRho_+2) + r+1]++;
                }
            }
        }
    }
}

void HoughLines::createTrigTable() {
    float ang = minTheta_;
    for (int n = 0; n < numTheta_; ang += thetaStep_, n++) {
        sinTab_[n] = sin(ang)/rhoStep_;
        cosTab_[n] = cos(ang)/rhoStep_;
    }
}

