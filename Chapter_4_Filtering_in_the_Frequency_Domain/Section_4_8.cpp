#include "main_header.h"

cv::Mat creating_ideal_LPF(int P, int Q, float D0)
{
	cv::Mat ideal = cv::Mat::zeros(P, Q, CV_8UC1);
	std::cout << "Filter size:\t" << ideal.size() << std::endl;

	float t1;
	float t2;
	float D;
	uchar* ptr;
	for (int i = 0; i < P; i++)
	{
		ptr = ideal.ptr<uchar>(i);
		for (int j = 0; j < Q; j++)
		{
			t1 = std::pow(i - P / 2.0F, 2);
			t2 = std::pow(j - Q / 2.0F, 2);
			D = std::sqrt(t1 + t2);
			if (D <= D0)
				ptr[j] = 1;
			else
				ptr[j] = 0;
		}
	}
	return ideal;
}
cv::Mat creating_Gaussian(int P, int Q, float D0, float K)
{
	
	cv::Mat gaussian = cv::Mat::zeros(P, Q, CV_32FC1);
	std::cout << "Filter size:\t" << gaussian.size() << std::endl;
	float t1;
	float t2;
	float D;
	float* ptr;
	for (int i = 0; i < P; i++)
	{
		ptr = gaussian.ptr<float>(i);
		for (int j = 0; j < Q; j++)
		{
			t1 = std::pow(i - P / 2.0F, 2);
			t2 = std::pow(j - Q / 2.0F, 2);
			D = std::sqrt(t1 + t2);
			ptr[j] = K * std::exp(-1.0F * (std::pow(D, 2) / (2.0F * std::pow(D0, 2) )));
		}
	}
	return gaussian;
}

cv::Mat creating_Butterworth_LPF(int P, int Q, float D0, int n)
{
	cv::Mat butter = cv::Mat::zeros(P, Q, CV_32FC1);
	std::cout << "Filter size:\t" << butter.size() << std::endl;

	float t1;
	float t2;
	float D;
	float* ptr;
	for (int i = 0; i < P; i++)
	{
		ptr = butter.ptr<float>(i);
		for (int j = 0; j < Q; j++)
		{
			t1 = std::pow(i - P / 2.0F, 2);
			t2 = std::pow(j - Q / 2.0F, 2);
			D = std::sqrt(t1 + t2);
			ptr[j] = 1.0F / (1.0F + std::pow(D / D0, 2 * n));
		}
	}
	return butter;
}
void centering_image(cv::Mat& img, int dataType)
{
	union types
	{
		float* ptrF;
		uchar* ptrU;
	};
	types type;
	for (int i = 0; i < img.rows; i++)
	{
		if (dataType == CV_MAKETYPE(CV_32F, 1))
			type.ptrF = img.ptr<float>(i);
		else
			type.ptrU = img.ptr<uchar>(i);
		for (int j = 0; j < img.cols; j++)
			if (dataType == CV_MAKETYPE(CV_32F, 1))
				type.ptrF[j] = type.ptrF[j] * std::pow(-1, i + j);
			else
				type.ptrU[j] = type.ptrU[j] * std::pow(-1, i + j);//Will shift it by M/2 and N/2
	}
}
