#pragma once
#define HAVE_OPENCV_HIGHGUI
#define HAVE_OPENCV_IMGPROC

#include <opencv2/opencv.hpp>

// Normalizes the given face image to a standard size.
cv::Mat norm_0_255(cv::InputArray _src);

// read a csv
void read_csv(const std::string& file, std::vector<cv::Mat>& o_images, std::vector<int>& labels, char separator = ';');
