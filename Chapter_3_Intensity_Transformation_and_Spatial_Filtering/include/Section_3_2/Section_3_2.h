#ifndef _Section_3_2_H
#define _Section_3_2_H
#include<iostream>
#include<opencv2/opencv.hpp>
#include<cmath>
template<typename T> float calculating_mean(const cv::Mat&);
void image_negative(const cv::Mat&);
void image_power_law(const cv::Mat&, float c=1.0F, float gamma=1.0F);
void image_contrast_stretching(const cv::Mat&, char type = 't', uchar s1 = 0, uchar s2 = 255, uchar r1=0, uchar r2=255);
#endif _Section_3_2_H