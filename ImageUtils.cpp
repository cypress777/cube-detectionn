#include "ImageUtils.hpp"

using namespace std;

void rotateImage(cv::Mat& img, float degree) {
    cv::Point2f center(cols/2, rows/2);
    cv::Mat rotateMatrix = cv::getRotationMatrix2D(center, degree, 1);

    cv::warpAffine(img, img, rotateMatrix, image.size());
}

void translateImage(cv::Mat& img, int offsetX, int offsetY) {
    cv::Mat transMatrix = (cv::Mat_<float>(2,3) << 1, 0, offsetX, 0, 1, offsetY);

    cv::warpAffine(img, img, transMatrix, img.size());
}

void addRandomNoise(cv::Mat& img, int strength) {
    int cols = img.cols;
    int rows = img.rows;
    cv::Mat_ cimg = img;

    for (int i = 0; i < strength; i++) {
        int col = rand() % cols;
        int row = rand() % rows;
        int noise = rand() % 61 - 30;
        float value = cimg(col, row) + noise;
        value = min(value, 255);
        value = max(0, value);
        cimg(col, row) = value;
    }
}