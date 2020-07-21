#ifndef _Section_4_9_H_
#define _Section_4_9_H_
#include "main_header.h"
cv::Mat creating_ideal_HPF(int P, int Q, float D0);
cv::Mat creating_Gaussian_HPF(int P, int Q, float D0, float K);
cv::Mat creating_Butterworth_HPF(int P, int Q, float D0, int n);
void image_sharpening(const cv::Mat& img, std::string type = "", int sect = 0, float D0 = 0.0F, float K = 1.0F, float n = 0.0F, std::string name = "");
cv::Mat creating_Laplacian(int P, int Q);
void sharpening_by_laplacian_filter(const cv::Mat& img, std::string name, int sect);

#endif _Section_4_9_H_