#include "opencv2/opencv.hpp"

void rotateImage(cv::Mat& img, float degree);

void translateImage(cv::Mat& img, int offsetX, int offsetY);

void addRandomNoise(cv::Mat& img, int strength);