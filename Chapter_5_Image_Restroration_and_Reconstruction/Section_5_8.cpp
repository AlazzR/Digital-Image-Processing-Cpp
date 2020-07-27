#include "Section_5_8_H_.h"

void wiener_filtering(const cv::Mat& img, std::string type, float k, float a , float b, float T, std::string imageName, float K)
{
	cv::Mat kernel;
	if (type == "Atmospheric")
		kernel = creating_H_atmospheric(k, img.rows, img.cols);
	else
		kernel = creating_H_motion(a, b, T, img.rows, img.cols);

	cv::Mat ker[2] = { cv::Mat::zeros(img.rows, img.cols, CV_32FC1), cv::Mat::zeros(img.rows, img.cols, CV_32FC1) };
	cv::split(kernel, ker);
	
	cv::Mat mag;
	cv::Mat temp;
	cv::magnitude(ker[0], ker[1], mag);
	cv::multiply(mag, mag, mag);
	cv::add(mag, cv::Scalar::all(K), temp);
	cv::divide(mag, temp, mag);

	cv::Mat imgcentered = img.clone();
	imgcentered.convertTo(imgcentered, CV_32FC1);
	centering_image(imgcentered);
	cv::Mat complex[2] = { imgcentered, cv::Mat::zeros(img.rows, img.cols, CV_32FC1) };
	cv::Mat dftimg;
	cv::merge(complex, 2, dftimg);
	cv::dft(dftimg, dftimg);
	cv::split(dftimg, complex);
	cv::multiply(complex[0], mag, complex[0]);
	cv::multiply(complex[1], mag, complex[1]);
	std::cout << "*******************************" << std::endl;
	//(a+jb)/ (c + jd) = mag(a,b)/mag(c,d) < atan(b/a) - atan(d/c) 
	cv::Mat magTemp[2] = { complex[0].clone(), complex[1].clone() };
	cv::Mat phaseTemp = complex[0].clone();
	cv::magnitude(complex[0], complex[1], magTemp[0]);
	cv::magnitude(ker[0], ker[1], magTemp[1]);
	cv::divide(magTemp[0], magTemp[1], magTemp[0]);



	float* ptrMag1;
	float* ptrMag2;
	float* ptrPhase;
	const float* ptrC1;
	const float* ptrC2;
	const float* ptrK1;
	const float* ptrK2;
	for (int row = 0; row < img.rows; row++)
	{
		ptrPhase = phaseTemp.ptr<float>(row);
		ptrC1 = complex[0].ptr<float>(row);
		ptrC2 = complex[1].ptr<float>(row);
		ptrK1 = ker[0].ptr<float>(row);
		ptrK2 = ker[1].ptr<float>(row);
		for (int col = 0; col < img.cols; col++)
		{
			ptrPhase[col] = std::atan2f(ptrC2[col], ptrC1[col]) - std::atan2f(ptrK2[col], ptrK1[col]);
		}
	}
	magTemp[1] = magTemp[0].clone();//To equate them and this will mitigate the issue of creating another Mat object
	for (int row = 0; row < img.rows; row++)
	{
		ptrMag1 = magTemp[0].ptr<float>(row);
		ptrMag2 = magTemp[1].ptr<float>(row);
		ptrPhase = phaseTemp.ptr<float>(row);
		for (int col = 0; col < img.cols; col++)
		{
			ptrMag1[col] = ptrMag1[col] * std::cos(ptrPhase[col]);//real
			ptrMag2[col] = ptrMag2[col] * std::sin(ptrPhase[col]);//imaginary

		}
	}

	complex[0] = magTemp[0].clone();
	complex[1] = magTemp[1].clone();



	cv::merge(complex, 2, dftimg);
	cv::dft(dftimg, dftimg, cv::DFT_INVERSE | cv::DFT_REAL_OUTPUT | cv::DFT_SCALE);
	cv::Mat finalImg;
	finalImg = dftimg.clone();
	centering_image(finalImg);
	//rescaling_intensities(finalImg);
	finalImg.convertTo(finalImg, CV_8UC1);
	cv::imwrite("../bin/Section_5_8/Origina_WienerFiltering_" + imageName + "_noiseType_BY_" + type + ".jpg", img);
	cv::imwrite("../bin/Section_5_8/Image__After_WienerFiltering_" + imageName + "_noiseType_BY_" + type + ".jpg", finalImg);

}