#ifndef _MAIN_HEADER_H_
#define _MAIN_HEADER_H_
#include <iostream>
#include "opencv2//opencv.hpp"
#include "Eigen/Dense"
#include <cmath>
#include <string>
#define PI 	3.14159265358979323846F
template <typename T> 
inline
cv::Mat translation(const cv::Mat&, int, int);
void rescaling_intensities(cv::Mat&);
void showing_frequency_spectrum(const cv::Mat&, std::string, int);
void translational_simulation(const cv::Mat&, std::string, int, int, int);
void rotationa_simulation(const cv::Mat&, std::string, float, int);
cv::Mat creating_ideal_LPF(int P, int Q, float D0);
cv::Mat creating_Gaussian(int P, int Q, float D0, float K);
cv::Mat creating_Butterworth_LPF(int P, int Q, float D0, int n);
void centering_image(cv::Mat& img, int dataType);
template<typename T>
void image_smoothing(const cv::Mat& img, std::string type = "", int sect = 0, float D0 = 0.0F, float K = 1.0F, float n = 0.0F, std::string name ="")
{
	union floatOruchar {
		float* ptrPadf;
		uchar* ptrPadu;
	};
	int P = img.rows * 2;
	int Q = img.cols * 2;
	int dataType;
	cv::Mat pad;
	cv::Mat kernel;
	cv::Mat temp;
	//Using typedef from https://docs.opencv.org/3.4/d1/d1b/group__core__hal__interface.html
	auto padding = [](const cv::Mat& img, int P, int Q, int dataType)->cv::Mat
	{
		cv::Mat pad = cv::Mat::zeros(P, Q, dataType);
		const uchar* ptrImg;
		//union is like struct of C

		floatOruchar type;
		for (int i = 0; i < img.rows; i++)
		{
			ptrImg = img.ptr<uchar>(i);
			if (dataType == CV_MAKETYPE(CV_32F, 1))
				type.ptrPadf = pad.ptr<float>(i);
			else
				type.ptrPadu = pad.ptr<uchar>(i);
			for (int j = 0; j < img.cols; j++)
			{
				if (dataType == CV_MAKETYPE(CV_32F, 1))
					type.ptrPadf[j] = (float)ptrImg[j];
				else
					type.ptrPadu[j] = ptrImg[j];
			}
		}
		//std::cout << pad << std::endl;
		return pad;
	};

	if (type == "Gaussian")
	{
		dataType = CV_32FC1;
		pad = padding(img, P, Q, dataType);
		kernel = creating_Gaussian(P, Q, D0, K);//Both pad and kernel are CV_32FC1
		temp = pad.clone();
		centering_image(temp, dataType);
	}
	else if(type == "Ideal")
	{
		dataType = CV_32FC1;
		pad = padding(img, P, Q, dataType);
		kernel = creating_ideal_LPF(P, Q, D0);//Both pad and kernel are CV_8UC1
		kernel.convertTo(kernel, dataType);
		temp = pad.clone();
		centering_image(temp, dataType);

	}
	else
	{
		dataType = CV_32FC1;
		pad = padding(img, P, Q, dataType);
		kernel = creating_Butterworth_LPF(P, Q, D0, n);//Both pad and kernel are CV_32FC1
		temp = pad.clone();
		centering_image(temp, dataType);

	}
	cv::Mat complexPad[2] = { temp, cv::Mat::zeros(temp.size(), dataType) };
	cv::Mat dftPad = cv::Mat::zeros(temp.size(), dataType);
	cv::merge(complexPad, 2, dftPad);
	cv::dft(dftPad, dftPad);
	cv::split(dftPad, complexPad);

	cv::multiply(complexPad[0], kernel, complexPad[0]);
	cv::multiply(complexPad[1], kernel, complexPad[1]);
	cv::Mat resultedImage = cv::Mat(complexPad[0].rows, complexPad[0].cols, dataType);
	cv::merge(complexPad, 2, dftPad);
	cv::dft(dftPad, resultedImage, cv::DFT_INVERSE | cv::DFT_REAL_OUTPUT| cv::DFT_SCALE);
	//std::cout << resultedImage << std::endl;
	centering_image(resultedImage, dataType);//This will de-centeralize the transformed image
	cv::Mat finalImage(resultedImage, cv::Rect(0, 0, img.cols, img.rows));
	//rescaling_intensities(finalImage);
	//std::cout << finalImage << std::endl;

	finalImage.convertTo(finalImage, CV_8UC1);//The following function will deal with uchar data
	showing_frequency_spectrum(img, name + " Image_Before_Transformation_" + type + "_", sect);
	showing_frequency_spectrum(finalImage, name +" Image_After_Transformation_" + type + "_", sect);


	pad.convertTo(pad, CV_8UC1);
	//cv::imshow(name + " Padded Image by zero", pad);
	//cv::imshow(name + " Tranformed Image by kernel type= " + type, pad);;
	//cv::waitKey(2000);
	//cv::destroyAllWindows();
	cv::imwrite("../bin/Section_4_" + std::to_string(sect) + "/Padded_" + name + type + ".jpg", pad);
}

//////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
cv::Mat translation(const cv::Mat& img, int tx, int ty)
{
	int rows = img.rows;
	int cols = img.cols;
	cv::Mat temp = img.clone();

	//img.copyTo(temp);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (tx != 0)
			{
				if (tx > 0)
				{
					if ((j + tx) < cols)
						temp.at<T>(i, j + tx) = img.at<T>(i, j);
					else
						temp.at<T>(i, std::abs(j - ((cols - 2 * tx) + tx))) = img.at<T>(i, j);

				}
				else
				{
					if (((j + tx) >= 0))
						temp.at<T>(i, j + tx) = img.at<T>(i, j);
					else
						temp.at<T>(i, std::abs(j + cols + tx)) = img.at<T>(i, j);

				}
			}
		}
	}
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (ty != 0)
			{
				if (ty > 0)
				{
					if ((i + ty) < rows)
						temp.at<T>(i + ty, j) = img.at<T>(i, j);
					else
						temp.at<T>(std::abs(i - ((rows - 2 * ty) + ty)), j) = img.at<T>(i, j);

				}
				else
				{
					if (((i + ty) >= 0))
						temp.at<T>(i + ty, j) = img.at<T>(i, j);
					else
						temp.at<T>(std::abs(i + rows + ty), j) = img.at<T>(i, j);

				}
			}
		}
	}

	return temp;
}

#endif _MAIN_HEADER_H_