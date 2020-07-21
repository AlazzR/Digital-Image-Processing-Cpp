#include "Section_4_9_H_.h"

cv::Mat creating_ideal_HPF(int P, int Q, float D0)
{
	cv::Mat ideal = cv::Mat::zeros(P, Q, CV_32FC1);
	std::cout << "Filter size:\t" << ideal.size() << std::endl;

	float t1;
	float t2;
	float D;
	float* ptr;
	for (int i = 0; i < P; i++)
	{
		ptr = ideal.ptr<float>(i);
		for (int j = 0; j < Q; j++)
		{
			t1 = std::pow(i - P / 2.0F, 2);
			t2 = std::pow(j - Q / 2.0F, 2);
			D = std::sqrt(t1 + t2);
			if (D <= D0)
				ptr[j] = 0.0F;
			else
				ptr[j] = 1.0F;
		}
	}
	return ideal;
}
cv::Mat creating_Gaussian_HPF(int P, int Q, float D0, float K)
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
			ptr[j] = 1.0F - K * std::exp(-1.0F * (std::pow(D, 2) / (2.0F * std::pow(D0, 2))));
		}
	}
	return gaussian;
}

cv::Mat creating_Butterworth_HPF(int P, int Q, float D0, int n)
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
			ptr[j] = 1.0F / (1.0F + std::pow(D0 / D, 2 * n));
		}
	}
	return butter;
}
void image_sharpening(const cv::Mat& img, std::string type, int sect, float D0, float K, float n, std::string name)
{
	int P = img.rows * 2;
	int Q = img.cols * 2;
	cv::Mat temp = cv::Mat(P, Q, CV_32FC1);
	cv::Mat kernel = cv::Mat::zeros(P, Q, CV_32FC1);
	cv::Mat pad = cv::Mat(P, Q, CV_32FC1, cv::Scalar(0.0F));
	const uchar* ptrImg;
	float* ptrPad;
	for (int i = 0; i < img.rows; i++)
	{
		ptrImg = img.ptr<uchar>(i);
		ptrPad = pad.ptr<float>(i);
		for (int j = 0; j < img.cols; j++)
			ptrPad[j] = (float)ptrImg[j];
	}
	if (type == "Gaussian")
	{
		kernel = creating_Gaussian_HPF(P, Q, D0, K);//Both pad and kernel are CV_32FC1
		temp = pad.clone();
		centering_image(temp, CV_32FC1);
	}
	else if (type == "Ideal")
	{
		kernel = creating_ideal_HPF(P, Q, D0);//Both pad and kernel are CV_8UC1
		temp = pad.clone();
		centering_image(temp, CV_32FC1);

	}
	else
	{
		kernel = creating_Butterworth_HPF(P, Q, D0, n);//Both pad and kernel are CV_32FC1
		temp = pad.clone();
		centering_image(temp, CV_32FC1);
	}
	cv::Mat complex[2] = { temp, cv::Mat::zeros(P, Q, CV_32FC1) };
	cv::Mat dftImage;
	cv::merge(complex, 2, dftImage);
	cv::dft(dftImage, dftImage);
	cv::split(dftImage, complex);
	cv::multiply(complex[0], kernel, complex[0]);
	cv::multiply(complex[1], kernel, complex[1]);
	cv::merge(complex, 2, dftImage);
	cv::dft(dftImage, dftImage, cv::DFT_INVERSE | cv::DFT_SCALE | cv::DFT_REAL_OUTPUT);
	centering_image(dftImage, CV_32FC1);//To decenteralize the transformed image
	cv::Mat finalImage(dftImage, cv::Rect(0, 0, img.cols, img.rows));
	finalImage.convertTo(finalImage, CV_8UC1);//The following function will deal with uchar data
	showing_frequency_spectrum(img, name + " Image_Before_Transformation_" + type + "_", sect);
	showing_frequency_spectrum(finalImage, name + " Image_After_Transformation_" + type + "_", sect);
	pad.convertTo(pad, CV_8UC1);
	cv::imwrite("../bin/Section_4_" + std::to_string(sect) + "/Padded_" + name + type + ".jpg", pad);

}
cv::Mat creating_Laplacian(int P, int Q)
{
	cv::Mat laplacian = cv::Mat::zeros(P, Q, CV_32FC1);
	std::cout << "Filter size: " << laplacian.size() << std::endl;
	float* ptr;
	for (int i = 0; i < P; i++)
	{
		ptr = laplacian.ptr<float>(i);
		for(int j = 0; j < Q; j++)
		{
			float t1 = std::pow((float)i - P / 2.0F, 2) + std::pow((float)j - Q / 2.0F, 2);
			ptr[j] = -4.0F * std::pow(PI, 2) * t1;
		}
	}
	cv::Mat temp = laplacian.clone();
	cv::normalize(temp, temp, 0.0F, 255.0F, cv::NORM_MINMAX);
	temp.convertTo(temp, CV_8UC1);
	showing_frequency_spectrum(temp, "Laplacian_Filter", 9);
	return laplacian;

}
void sharpening_by_laplacian_filter(const cv::Mat& img, std::string name, int sect)
{
	int P = img.rows * 2;
	int Q = img.cols * 2;
	cv::Mat temp = cv::Mat(P, Q, CV_32FC1);
	cv::Mat kernel = creating_Laplacian(P, Q);
	cv::Mat pad = cv::Mat(P, Q, CV_32FC1, cv::Scalar(0.0F));
	const uchar* ptrImg;
	float* ptrPad;
	for (int i = 0; i < img.rows; i++)
	{
		ptrImg = img.ptr<uchar>(i);
		ptrPad = pad.ptr<float>(i);
		for (int j = 0; j < img.cols; j++)
			ptrPad[j] = (float)ptrImg[j];
	}
	temp = pad.clone();
	cv::normalize(temp, temp, 0.0F, 1.0F, cv::NORM_MINMAX);
	cv::Mat obj = temp.clone();
	centering_image(temp, CV_32FC1);
	cv::Mat complex[2] = { temp, cv::Mat::zeros(P, Q, CV_32FC1) };
	cv::Mat dftImage;
	cv::merge(complex, 2, dftImage);
	cv::dft(dftImage, dftImage);
	cv::split(dftImage, complex);
	cv::multiply(complex[0], kernel, complex[0]);
	cv::multiply(complex[1], kernel, complex[1]);
	cv::merge(complex, 2, dftImage);
	cv::dft(dftImage, dftImage, cv::DFT_INVERSE | cv::DFT_SCALE | cv::DFT_REAL_OUTPUT);
	double min, max;
	cv::minMaxIdx(dftImage, &min, &max);
	//std::cout << "min: " << min << " max: " << max << std::endl;
	cv::divide(dftImage, cv::Scalar::all(-1.0F * max), dftImage);
	//cv::minMaxIdx(dftImage, &min, &max);
	//std::cout << "min: " << min << " max: " << max << std::endl;
	centering_image(dftImage, CV_32FC1);
	cv::Mat finalImage = cv::Mat(dftImage, cv::Rect(0, 0, img.cols, img.rows));
	cv::Mat f = cv::Mat(obj, cv::Rect(0, 0, img.cols, img.rows));
	cv::add(f, finalImage, finalImage);
	//cv::normalize(finalImage, finalImage, 0.0F, 255.0F, cv::NORM_MINMAX);
	rescaling_intensities(finalImage);//To get it back to [0, 255]
	showing_frequency_spectrum(img, name + " Image_Before_Transformation_laplacian" + "_", sect);
	showing_frequency_spectrum(finalImage, name + " Image_After_Transformation_laplacian" + "_", sect);
	pad.convertTo(pad, CV_8UC1);
	cv::imwrite("../bin/Section_4_" + std::to_string(sect) + "/Padded_" + name + "_laplacian" + ".jpg", pad);

}
