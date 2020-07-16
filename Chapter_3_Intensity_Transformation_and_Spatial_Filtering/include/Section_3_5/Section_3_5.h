#ifndef _SECTION_3_5_H_
#define _SECTION_3_5_H_
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <memory>
#include <string>
#include <cmath>
cv::Mat creating_box_filter(int);
cv::Mat creating_gaussian_filter(float, float);//I will only care about the spread of the filter
/*
I called it convolution because I am used to deal with convolution from courses in signal processing, but my implementation for the filtering algorithim is done by correlation. In which the uncircular symmetric filters need to be rotated twice, then the correlation is done. After doing the correlation, I need to take the transpose of the resulted image from the correlation process.
*/
cv::Mat convolution_kernal_rotated(const cv::Mat&, const cv::Mat&, int, int, int, int);
void convolving_by_box_filter(const cv::Mat&, int size=3, std::string type="_temp");
void convolving_by_gaussian_filter(const cv::Mat& img, float K, float std, std::string type);
uchar finding_median(const cv::Mat&);
void convolving_by_saltPepper_filter(const cv::Mat&, int);
void rescaling_intensities(cv::Mat&);
#endif _SECTION_3_5_H_