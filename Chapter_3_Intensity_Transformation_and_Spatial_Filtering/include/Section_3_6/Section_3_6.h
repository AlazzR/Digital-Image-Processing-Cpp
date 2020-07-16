#ifndef _SECTION_3_6_H_
#define _SECTION_3_6_H_
#include "Section_3_5.h"
#define M_PI 3.14159265358979323846F
cv::Mat creating_simple_laplacian_1();
cv::Mat creating_simple_laplacian_2();
void convolving_with_simple_laplacian(cv::Mat&, bool);
void differnce_of_gaussian(const cv::Mat&, float, float, float);
cv::Mat creating_laplacian(float);
void blob_detection(cv::Mat&, float, float , int , float, int, std::string);
cv::Mat non_maximum_suppression(const std::vector<cv::Mat>&, const float*, float, int, int);
#endif _SECTION_3_6_H_