#include "main_header.h"

void rescaling_intensities(cv::Mat& tempImage)
{
	//Rescalling the values of the image to be non-negative
	cv::Mat gm = cv::Mat::zeros(tempImage.rows, tempImage.cols, CV_32FC1);
	cv::Mat gs = cv::Mat::zeros(tempImage.rows, tempImage.cols, CV_32FC1);

	std::vector<float> min_vector;
	auto f = [](const cv::Mat& a, std::vector<float>& vector)->void
	{
		const float* ptrM;
		for (int i = 0; i < a.rows; i++)
		{
			ptrM = a.ptr<float>(i);
			for (int j = 0; j < a.cols; j++)
				vector.push_back(ptrM[i]);
		}
	};
	f(tempImage, min_vector);
	float min = *std::min_element(min_vector.begin(), min_vector.end());
	const float* ptrTempT;
	float* ptrTempT1;
	for (int i = 0; i < gm.rows; i++)
	{
		ptrTempT = tempImage.ptr<float>(i);
		ptrTempT1 = gm.ptr<float>(i);
		for (int j = 0; j < gm.cols; j++)
			ptrTempT1[j] = ptrTempT[j] - min;
	}
	std::vector<float> max_vector;
	f(gm, max_vector);
	float max = *std::max_element(max_vector.begin(), max_vector.end());
	for (int i = 0; i < gm.rows; i++)
	{
		ptrTempT = gm.ptr<float>(i);
		ptrTempT1 = gs.ptr<float>(i);
		for (int j = 0; j < gm.cols; j++)
			ptrTempT1[j] = 255.0F * (ptrTempT[j] / max);
	}
	gs.copyTo(tempImage);

}


void showing_frequency_spectrum(const cv::Mat& img, std::string type, int sect)
{
	cv::Mat pad = cv::Mat::zeros(img.rows * 2, img.cols * 2, CV_32FC1);
	const uchar* ptrImg;
	float* ptrPad;
	//To lose the wraperror
	for (int i = 0; i < img.rows; i++)
	{
		ptrImg = img.ptr<uchar>(i);
		ptrPad = pad.ptr<float>(i);
		for (int j = 0; j < img.cols; j++)
			//ptrPad[j] = ptrImg[j] / 255.0F;
			ptrPad[j] = ptrImg[j];
	}
	//Need to center the frequency respnse
	for (int i = 0; i < pad.rows; i++)
	{
		ptrPad = pad.ptr<float>(i);
		for (int j = 0; j < pad.cols; j++)
			ptrPad[j] = ptrPad[j] * std::pow(-1, i + j);//Will shift it by M/2 and N/2
	}
	//cv::imshow("Padded Image", pad);
	cv::Mat complex[2] = { pad, cv::Mat::zeros(pad.size(), CV_32FC1) };

	cv::Mat dft_frequency;
	cv::merge(complex, 2, dft_frequency);
	cv::dft(dft_frequency, dft_frequency);
	cv::split(dft_frequency, complex);

	cv::Mat mag = cv::Mat(pad.size(), CV_32FC1);
	cv::Mat phase = cv::Mat(pad.size(), CV_32FC1);

	cv::magnitude(complex[0], complex[1], mag);
	//mag = mag + cv::Scalar::all(1);
	//std::cout << mag;
	float* ptrMag;
	float* ptrPhase;
	float* ptr1;
	float* ptr2;
	for (int i = 0; i < mag.rows; i++)
	{
		ptrMag = mag.ptr<float>(i);
		ptrPhase = phase.ptr<float>(i);
		ptr1 = complex[0].ptr<float>(i);
		ptr2 = complex[1].ptr<float>(i);
		for (int j = 0; j < mag.cols; j++)
		{
			ptrMag[j] = std::log10(std::log10(ptrMag[j] + 1) + 1);
			ptrPhase[j] = std::atan(ptr2[j] / ptr1[j]);
		}

	}
	//std::cout << mag << std::endl;
	//cv::normalize(mag, mag, 0, 255, CV_MINMAX);
	//mag.convertTo(mag , CV_8UC1);
	
	//cv::imshow("Rectangle", img);
	//cv::imshow("Magnitude", mag);
	//cv::imshow("Phase", phase);

	std::cout << "Image size " << type + ": " << img.size() << std::endl;
	//rescaling_intensities(mag);
	//std::cout << mag << std::endl;
	cv::normalize(mag, mag, 0, 255, CV_MINMAX);
	cv::normalize(phase, phase, 0, 255, CV_MINMAX);
	mag.convertTo(mag, CV_8UC1);
	phase.convertTo(phase, CV_8UC1);

	//cv::waitKey(1000);
	//cv::destroyAllWindows();
	
	cv::imwrite("../bin/Section_4_" + std::to_string(sect) + "/Original_" + type +".jpg", img);
	cv::imwrite("../bin/Section_4_" + std::to_string(sect) + "/Magnitude_" + type + ".jpg", mag);
	cv::imwrite("../bin/Section_4_" + std::to_string(sect) + "/Phase_" + type + ".jpg", phase);

}

void translational_simulation(const cv::Mat& img, std::string type, int sect, int tx, int ty)
{
	cv::Mat translated = translation<uchar>(img, tx, ty);
	showing_frequency_spectrum(translated, type, sect);

}

void rotationa_simulation(const cv::Mat& img, std::string type, float angle, int sect)
{
	cv::Point center(img.cols / 2, img.rows / 2);
	cv::Mat rotated = cv::Mat(img.size(), CV_8UC1);
	cv::Mat M = cv::getRotationMatrix2D(center, angle, 1);
	cv::warpAffine(img, rotated, M, img.size(), CV_INTER_LINEAR, CV_HAL_BORDER_CONSTANT, cv::Scalar(0));
	showing_frequency_spectrum(rotated, type, sect);


}
