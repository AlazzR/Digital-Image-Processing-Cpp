#ifndef _SECTION_5_8_H_
#define _SECTION_5_8_H_
#include "Section_5_7_H_.h"
void wiener_filtering(const cv::Mat& img, std::string type, float k = 0.0025F, float a = 0.1F, float b = 0.1F, float T = 1.0F, std::string imageName = "Book", float K = 1.0F);

#endif _SECTION_5_8_H_