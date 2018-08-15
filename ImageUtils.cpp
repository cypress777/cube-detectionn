#include "opencv2/opencv.hpp"

using namespace std;

cv::Mat rotateImage(const cv::Mat& img, float degree) {
    int cols = img.cols;
    int rows = img.rows;

    cv::Point2f center(cols/2, rows/2);
    cv::Mat rotateMatrix = cv::getRotationMatrix2D(center, degree, 1);
    cv::Mat rotatedImg{cv::Size(img.size().height, img.size().width), img.type()};

    cv::warpAffine(img, rotatedImg, rotateMatrix, image.size());
    return rotatedImg;
}