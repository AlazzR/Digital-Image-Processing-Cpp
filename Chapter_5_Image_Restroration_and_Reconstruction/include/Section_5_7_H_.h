#ifndef _SECTION_5_7_H_
#define _SECTION_5_7_H_
#include <iostream>
#include "opencv2/opencv.hpp"
#include <cmath>
#include <string>
#define PI 	3.14159265358979323846F
void rescaling_intensities(cv::Mat& tempImage);
cv::Mat creating_Butterworth_LPF(int P, int Q, float D0, int n);
void centering_image(cv::Mat& img);
cv::Mat creating_H_atmospheric(float k, int M, int N);
cv::Mat creating_H_motion(float a, float b, float T, int M, int N);
void inverse_filtering(const cv::Mat& img, std::string type, float D0, int n, float k = 0.0025F, float a = 0.1F, float b = 0.1F, float T = 1.0F, std::string imageName="Book");

#endif _SECTION_5_7_H_