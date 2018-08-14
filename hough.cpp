//
// Created by yiping.chen on 2018/8/14.
//
using namespace std;

#include "hough.hpp"

HoughLines::HoughLines(cv::Mat& img, int threshold, float rho, float theta, float minTheta, float maxTheta) {
    threshold_ = threshold;
    thetaStep_ = theta;
    rhoStep_ = rho;
    minTheta_ = minTheta;
    maxTheta_ = maxTheta;
    numTheta_ = cvRound((maxTheta_ - minTheta_) / thetaStep_);
    maxRho_ = img.rows + img.cols;
    minRho_ = -1 * maxRho_;
    numRho_ = cvRound((maxRho_ - minRho_ + 1) / rhoStep_);
    accumTable_ = cv::Mat::zeros(numTheta_ + 2, numRho_ + 2, CV_32SC1);  // 

    createTrigTable();
    initAccumTable(img);

    findLocalMax();

    const int *accum = accumTable_.ptr<int>();
    sort(sortBuf_.begin(), sortBuf_.end(), hough_cmp_gt(accum));
}

void HoughLines::initAccumTable(cv::Mat& img) {
    const uchar *image = img.ptr();
    int *accum = accumTable_.ptr<int>();
    int step = (int)img.step;
    int width = img.cols;
    int height = img.rows;

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

void HoughLines::findLocalMax() {
    const int *accum = accumTable_.ptr<int>();
    for (int r = 0; r < numRho_; r++) {
        for (int n = 0; n < numTheta_; n++) {
            int base = (n+1) * (numRho_+2) + r + 1;
            if( accum[base] > threshold_ &&
                accum[base] > accum[base - 1] && accum[base] >= accum[base + 1] &&
                accum[base] > accum[base - numRho_ - 2] && accum[base] >= accum[base + numRho_ + 2] )
                sortBuf_.push_back(base);
        }
    }
}


vector<HoughLines::PolarLine> HoughLines::getLines(int topNum) {
    vector<HoughLines::PolarLine> lines;
    const int *accum = accumTable_.ptr<int>();

    topNum = min(topNum, (int)sortBuf_.size());
    float scale = 1./(numRho_ + 2);

    for (int i = 0; i < topNum; i++) {
        PolarLine line;
        int idx = sortBuf_[i];
        int n = cvFloor(idx*scale) - 1;
        int r = idx - (n+1)*(numRho_+2) - 1;
        line.rho = (r - (numRho_ - 1)*0.5f) * rhoStep_;
        line.theta = minTheta_ + n*thetaStep_;
        line.count = accum[idx];
        lines.push_back(line);
    }
    return lines;
}