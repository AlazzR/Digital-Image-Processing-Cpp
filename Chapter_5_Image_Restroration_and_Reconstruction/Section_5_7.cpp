#include "Section_5_7_H_.h"
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
	auto f = [](cv::Mat& A, cv::Mat& B) {cv::Mat temp; cv::multiply(A, B, temp); return temp; };
	cv::imwrite("../bin/Section_5_7/Butterworth_radii" + std::to_string(D0) + "_n_" + std::to_string(n) + ".jpg", f(butter, cv::Mat(butter.rows, butter.cols, CV_32FC1, cv::Scalar(255))));
	return butter;
}

void centering_image(cv::Mat& img)
{
	float* ptr;
	for (int i = 0; i < img.rows; i++)
	{
		ptr = img.ptr<float>(i);
		for (int j = 0; j < img.cols; j++)
			ptr[j] = ptr[j] * std::pow(-1, i + j);
	}
}

cv::Mat creating_H_atmospheric(float k, int M, int N)
{
	cv::Mat kernel[2] = { cv::Mat::zeros(M, N, CV_32FC1), cv::Mat::zeros(M, N, CV_32FC1) };
	float* ptr;
	for (int i = 0; i < kernel[0].rows;  i++)
	{
		ptr = kernel[0].ptr<float>(i);
		for (int j = 0; j < kernel[0].cols; j++)
		{
			float t1 = std::pow((float)i - M/2.0F , 2) + std::pow((float)j - N / 2.0F, 2);
			//std::cout << 5 / 6 << std::endl;
			//std::cout << 5.0F/6.0F << std::endl;
			float t2 = std::pow(t1, 0.5F);
			ptr[j] = std::exp(-1.0F * k * t2);
		}
	}
	cv::Mat finalKernel = cv::Mat(M, N, CV_32FC2);
	cv::merge(kernel, 2, finalKernel);
	return finalKernel;
}

cv::Mat creating_H_motion(float a, float b, float T, int M, int N)
{
	cv::Mat kernel[2] = { cv::Mat::zeros(M, N, CV_32FC1), cv::Mat::zeros(M, N, CV_32FC1)};
	float* ptr1;
	float* ptr2;

	for (int i = 0; i < kernel[0].rows; i++)
	{
		ptr1 = kernel[0].ptr<float>(i);
		ptr2 = kernel[1].ptr<float>(i);

		for (int j = 0; j < kernel[0].cols; j++)
		{
			//float u = (float)i - M / 2.0F;
			//float v = (float)j - N / 2.0F;
			float u = (float)i;
			float v = (float)j;
			float t = (a * u + b * v);
			float t1 = std::sin(PI * t);
			float t2 = T / (PI * t);
			float treal  = std::cos(-1.0F * PI * t);
			float timg = std::sin(-1.0F * PI * t);

			ptr1[j] = t2 * t1 * treal;
			ptr2[j] = t2 * t1 * timg;
		}
	}
	cv::Mat finalKernel = cv::Mat(M, N, CV_32FC2);
	cv::merge(kernel, 2, finalKernel);
	return finalKernel;
}

void inverse_filtering(const cv::Mat& img, std::string type, float D0, int n, float k, float a, float b, float T, std::string imageName)
{
	cv::Mat kernel;
	if (type == "Atmospheric")
		kernel = creating_H_atmospheric(k, img.rows, img.cols);
	else
		kernel = creating_H_motion(a, b, T, img.rows, img.cols);

	cv::Mat ker[2] = { cv::Mat::zeros(img.rows, img.cols, CV_32FC1), cv::Mat::zeros(img.rows, img.cols, CV_32FC1) };
	cv::split(kernel, ker);
	cv::Mat imgcentered = img.clone();
	imgcentered.convertTo(imgcentered, CV_32FC1);
	centering_image(imgcentered);
	cv::Mat complex[2] = { imgcentered, cv::Mat::zeros(img.rows, img.cols, CV_32FC1) };
	cv::Mat dftimg;
	cv::merge(complex, 2, dftimg);
	cv::dft(dftimg, dftimg);
	cv::split(dftimg, complex);
	std::cout << "*******************************" << std::endl;
	//(a+jb)/ (c + jd) = mag(a,b)/mag(c,d) < atan(b/a) - atan(d/c) 
	cv::Mat magTemp[2] = { complex[0].clone(), complex[1].clone()};
	cv::Mat phaseTemp = complex[0].clone();
	cv::magnitude(magTemp[0], magTemp[1], magTemp[0]);
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
			ptrPhase[col] =std::atan2(ptrC2[col], ptrC1[col]) - std::atan2(ptrK2[col], ptrK1[col]);
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

	cv::Mat LPF = creating_Butterworth_LPF(img.rows, img.cols, D0, n);
	cv::multiply(complex[0], LPF, complex[0]);
	cv::multiply(complex[1], LPF, complex[1]);
	cv::merge(complex, 2, dftimg);
	cv::dft(dftimg, dftimg, cv::DFT_INVERSE | cv::DFT_REAL_OUTPUT | cv::DFT_SCALE);
	cv::Mat finalImg;
	finalImg = dftimg.clone();
	centering_image(finalImg);
	//rescaling_intensities(finalImg);
	finalImg.convertTo(finalImg, CV_8UC1);
	cv::imwrite("../bin/Section_5_7/Origina_Inverse_Filtering_" + imageName + "_noiseType_BY_" + type + ".jpg", img);
	cv::imwrite("../bin/Section_5_7/Image__After_Inverse_Filtering_" + imageName + "_noiseType_BY_" + type + ".jpg", finalImg);

}