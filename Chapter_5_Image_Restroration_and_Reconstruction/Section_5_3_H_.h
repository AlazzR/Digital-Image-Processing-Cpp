#ifndef _SECTION5_5_3_H_
#define _SECTION5_5_3_H_
#include <iostream>
#include <opencv2/opencv.hpp>
#include <cmath>
#include <string>
#include <vector>
void arithmatic_mean(const cv::Mat& img, int m, int n);
void geometric_mean(const cv::Mat& img, int m, int n);
void harmonic_mean(const cv::Mat& img, int m, int n);
void contraharmonic_mean(const cv::Mat& img, int m, int n, float Q, std::string saltOrPepper);
std::vector<int> uniqueHistogram(const cv::Mat& kernel);
cv::Mat median_filter(const cv::Mat& img, int m, int n, std::string pass);
void max_filter(const cv::Mat& img, int m, int n);
void min_filter(const cv::Mat& img, int m, int n);
void midway_filter(const cv::Mat& img, int m, int n);
float variance_neighborhood(const cv::Mat& img, float& mean);
void adaptive_local_noise_reduction(const cv::Mat& img, int m, int n, float varNoise);
cv::Mat padding_image(const cv::Mat& img, int size);
void adaptive_median_filter(const cv::Mat& img, int size, int maximum_size);
#endif _SECTION5_5_3_H_