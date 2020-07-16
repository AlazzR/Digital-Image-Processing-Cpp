#ifndef _SECTION_3_3_H_
#define _SECTION_3_3_H_
#include <iostream>
#include <opencv2/opencv.hpp>
#include <memory>
#include <string>
#include<cmath>
template<typename T>std::unique_ptr<float[]> calculating_histogram(const cv::Mat&);
void histogram_equalization(const cv::Mat&, std::string);
void local_histogram_processing(const cv::Mat&, int size=3);
template<typename T> float calculating_mean_neighborhood(const cv::Mat&, const std::unique_ptr<T[]>&);
template<typename T> float calculating_stdDeviation_neighborhood(const cv::Mat&, const std::unique_ptr<T[]>&, float);
void statistical_local_enhancement(const cv::Mat&, float C=30.5F, float  k0=0.0F, float k1=0.1F, float k2=0.0F, float k3=0.1F, int size = 3);
#endif _SECTION_3_3_H_