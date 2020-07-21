#include "main_header.h"
#include "Section_4_9_H_.h"
#include "Section_4_10_H_.h"
int main(int argc, char** argv)
{
	///////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////
	//Section 4.6
	///////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////
	//Showing the effect of DFT
	cv::Mat rect = cv::imread("../Rectangle.tif", cv::IMREAD_GRAYSCALE);
	showing_frequency_spectrum(rect, "Rectangle", 6);
	translational_simulation(rect, "Translational", 6, 10, 50);
	rotationa_simulation(rect, "Rotated", 45.0F, 6);


	/*
	//Testing for translation transformation in which I will keep all of the pixesl
	cv::Mat temp = cv::Mat::zeros(4, 5, CV_8UC1);
	int m = temp.rows;
	int n = temp.cols;
	std::cout << m << "\t" << n << std::endl;
	uchar* ptr1;
	uchar* ptr2;

	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			temp.at<uchar>(i, j) = i * m + j;

	std::cout << temp << std::endl;
	std::cout << translation<uchar>(temp, 0, -2) << std::endl;
	std::cout << "*****************************" << std::endl;
	int shift = -5;
	cv::Mat temp2 = cv::Mat::zeros(temp.size(), CV_8UC1);
	for (int i = 0; i < m; i++)
	{
		ptr1 = temp.ptr<uchar>(i);
		ptr2 = temp2.ptr<uchar>(i);

		for (int j = 0; j < n; j++)
		{
			if ((j + shift) >= 0)
			{
				ptr2[j + shift] = ptr1[j];
			}
			else
			{
				ptr2[std::abs(j + ((n ) + shift))] = ptr1[j];
			}
		}
	}
	std::cout << temp2 << std::endl;
	*/
	///////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////
	/***********************Section 4.8***********************/
	///////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////
	cv::Mat ideal = creating_ideal_LPF(2 * rect.rows, 2 * rect.cols, 500.0F);
	cv::Mat gaussian = creating_Gaussian(2 * rect.rows, 2 * rect.cols, 500.0F, 1.0F);
	int n = 1;
	cv::Mat butter = creating_Butterworth_LPF(2 * rect.rows, 2 * rect.cols, 500.0F, n);
	cv::Mat all255 = cv::Mat(butter.rows, butter.cols, CV_8UC1, cv::Scalar(255));
	
	auto f = [](cv::Mat& A, cv::Mat& B) {cv::Mat temp; cv::multiply(A, B, temp); return temp; };

	cv::imwrite("../bin/Section_4_8/Gaussian_LPF.jpg", f(gaussian, cv::Mat(gaussian.rows, gaussian.cols, CV_32FC1, cv::Scalar(255))));
	cv::imwrite("../bin/Section_4_8/Ideal_LPF.jpg", f(ideal, cv::Mat(ideal.rows, ideal.cols, CV_8UC1, cv::Scalar(255))));
	cv::imwrite("../bin/Section_4_8/Butterworth_" + std::to_string(n) + "_LPF.jpg", f(butter, cv::Mat(butter.rows, butter.cols, CV_32FC1, cv::Scalar(255))));

	cv::Mat test_pattern = cv::imread("../test_pattern.tif", cv::IMREAD_GRAYSCALE);
	image_smoothing<float>(test_pattern, "Ideal", 8, 60.0F, 1.0F, 0.0F, "Test Pattern");
	image_smoothing<float>(test_pattern, "Gaussian", 8, 60.0F, 1.0F, 0.0F, "Test Pattern");
	image_smoothing<float>(test_pattern, "Butterworth", 8, 60.0F, 1.0F, 2.25F, "Test Pattern");
	///////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////
	/***********************Section 4.9***********************/
	///////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////
	cv::Mat ideal_HPF = creating_ideal_HPF(2 * rect.rows, 2 * rect.cols, 500.0F);
	cv::Mat gaussian_HPF = creating_Gaussian_HPF(2 * rect.rows, 2 * rect.cols, 500.0F, 1.0F);
	//int n = 1;
	cv::Mat butter_HPF = creating_Butterworth_HPF(2 * rect.rows, 2 * rect.cols, 500.0F, n);
	cv::imwrite("../bin/Section_4_9/Gaussian_HPF.jpg", f(gaussian_HPF, cv::Mat(gaussian_HPF.rows, gaussian_HPF.cols, CV_32FC1, cv::Scalar(255.0F))));
	cv::imwrite("../bin/Section_4_9/Ideal_HPF.jpg", f(ideal_HPF, cv::Mat(ideal_HPF.rows, ideal_HPF.cols, CV_32FC1, cv::Scalar(255.0F))));
	cv::imwrite("../bin/Section_4_9/Butterworth_" + std::to_string(n) + "_HPF.jpg", f(butter_HPF, cv::Mat(butter_HPF.rows, butter_HPF.cols, CV_32FC1, cv::Scalar(255.0F))));

	image_sharpening(test_pattern, "Ideal", 9, 60.0F, 1.0F, 0.0F, "Test Pattern");
	image_sharpening(test_pattern, "Gaussian", 9, 60.0F, 1.0F, 0.0F, "Test Pattern");
	image_sharpening(test_pattern, "Butter", 9, 60.0F, 1.0F, 2.25F, "Test Pattern");
	cv::Mat moon = cv::imread("../blurry_moon.tif", cv::IMREAD_GRAYSCALE);
	sharpening_by_laplacian_filter(moon, "blurry_moon", 9);
	///////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////
	/***********************Section 4.10***********************/
	///////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////
	cv::Mat car = cv::imread("../car_Moire.tif", cv::IMREAD_GRAYSCALE);
	showing_frequency_spectrum(car, "Identifiying_Frequencies_to_suppress", 10);
	
	//std::unordered_set<coordinate, customHashing, customCompare> t = find_loc_to_suppress(car);
	filtering_by_notch(car, 9.0F, 4);





	/*
	Eigen::MatrixXd m = Eigen::MatrixXd::Random(3, 3);
	std::cout << "M is:\n " << m << std::endl;
	Eigen::MatrixXd c = Eigen::MatrixXd::Constant(3, 3, 1.2);
	std::cout << "C is:\n " << c << std::endl;
	m = (m + c) * 50.0F;
	std::cout << "M is:\n " << m << std::endl;
	Eigen::VectorXd v(3);
	v << 1, 2, 3;
	std::cout << " m * v\n" << m * v << std::endl;
	*/
	return 0;
}



