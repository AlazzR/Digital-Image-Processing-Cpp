#include "Section_5_3_H_.h"

void arithmatic_mean(const cv::Mat& img, int m, int n)
{
	std::cout << "Image size: " << img.size() << std::endl;
	if (m % 2 == 0)
		m = std::ceil(m);
	if (n % 2 == 0)
		n = std::ceil(n);
	int padX = std::floor((m) / 2);
	int padY = std::floor((n) / 2);
	int square;
	
	if (img.rows != img.cols)
	{
		if (img.rows > img.cols)
			square = img.rows;
		else
			square = img.cols;
	}

	cv::Mat kernel = cv::Mat(m, n, CV_32FC1, cv::Scalar::all((float)(1.0F / (m * n))));
	//std::cout << kernel << std::endl;
	cv::Mat pad = cv::Mat::zeros(square + 2*padX, square + 2*padY, CV_8UC1);

	const uchar* ptrImg;
	uchar* ptrPad;
	for (int row = 0; row < img.rows; row++)
	{
		ptrImg = img.ptr<uchar>(row);
		ptrPad = pad.ptr<uchar>(row + padX);
		for(int col=0; col <img.cols; col++)
		{ 
			ptrPad[col + padY] = ptrImg[col];
		}
	}
	cv::Mat tempPad;
	pad.copyTo(tempPad);
	for (int row = padX; row < tempPad.rows - padX; row++)
	{
		ptrPad = tempPad.ptr<uchar>(row);
		for (int col = padY; col < tempPad.cols - padY; col++)
		{
			cv::Mat temp = cv::Mat(pad, cv::Rect(col - padY, row - padX, n, m));
			temp.convertTo(temp, CV_32FC1);
			cv::multiply(temp, kernel, temp);
			ptrPad[col] = std::ceil(cv::sum(temp)[0]);
		}
	}
	cv::Mat finalImage(cv::Mat(tempPad, cv::Rect(padX, padY, img.cols, img.rows)));
	cv::imshow("Original Image", img);
	cv::imshow("Padded Image After Arithmetic mean Filter", finalImage);
	//cv::waitKey(1000);
	cv::destroyAllWindows();
	cv::imwrite("../bin/Section_5_3/Original_Image_Gaussian_Noise_with_Arihmetic_mean.jpg", img);
	pad.convertTo(pad, CV_8UC1);
	cv::imwrite("../bin/Section_5_3/Padded_Image_Gaussian_Noise_with_Arihmetic_mean.jpg", pad);
	cv::imwrite("../bin/Section_5_3/Image_Gaussian_Noise_After_Arihmetic_mean_filter.jpg", finalImage);
}

void geometric_mean(const cv::Mat& img, int m, int n)
{
	std::cout << "Image size: " << img.size() << std::endl;
	if (m % 2 == 0)
		m = std::ceil(m);
	if (n % 2 == 0)
		n = std::ceil(n);
	int padX = std::floor((m) / 2);
	int padY = std::floor((n) / 2);
	int square;

	if (img.rows != img.cols)
	{
		if (img.rows > img.cols)
			square = img.rows;
		else
			square = img.cols;
	}

	cv::Mat pad = cv::Mat::zeros(square + 2 * padX, square + 2 * padY, CV_8UC1);

	const uchar* ptrImg;
	uchar* ptrPad;
	for (int row = 0; row < img.rows; row++)
	{
		ptrImg = img.ptr<uchar>(row);
		ptrPad = pad.ptr<uchar>(row + padX);
		for (int col = 0; col < img.cols; col++)
		{
			ptrPad[col + padY] = ptrImg[col];
		}
	}
	cv::Mat tempPad;
	pad.copyTo(tempPad);
	for (int row = padX; row < tempPad.rows - padX; row++)
	{
		ptrPad = tempPad.ptr<uchar>(row);
		for (int col = padY; col < tempPad.cols - padY; col++)
		{
			cv::Mat temp = cv::Mat(pad, cv::Rect(col - padY, row - padX, n, m));
			temp.convertTo(temp, CV_32FC1);
			float tempValue = 1.0F;
			for (int i = 0; i < temp.rows; i++)
				for (int j = 0; j < temp.cols; j++)
				{
					tempValue = tempValue * temp.at<float>(i, j);
					//std::cout << tempValue << std::endl;
				}
			//std::cout << temp << ":" << std::ceil(std::pow(tempValue, (int)(1 / (m * n)))) << std::endl;
			ptrPad[col] = std::ceil( std::pow(tempValue, (1.0F/(m * n))));
		}
	}
	//std::cout << tempPad << std::endl;
	cv::Mat finalImage(cv::Mat(tempPad, cv::Rect(padX, padY, img.cols, img.rows)));

	cv::imshow("Original Image", img);
	cv::imshow("Padded Image After Geometric mean Filter", finalImage);
	//cv::waitKey(1000);
	cv::destroyAllWindows();
	cv::imwrite("../bin/Section_5_3/Image_Gaussian_Noise_After_Geometric_mean_filter.jpg", finalImage);
}

void harmonic_mean(const cv::Mat& img, int m, int n)
{
	std::cout << "Image size: " << img.size() << std::endl;
	if (m % 2 == 0)
		m = std::ceil(m);
	if (n % 2 == 0)
		n = std::ceil(n);
	int padX = std::floor((m) / 2);
	int padY = std::floor((n) / 2);
	int square;

	if (img.rows != img.cols)
	{
		if (img.rows > img.cols)
			square = img.rows;
		else
			square = img.cols;
	}

	cv::Mat pad = cv::Mat::zeros(square + 2 * padX, square + 2 * padY, CV_8UC1);

	const uchar* ptrImg;
	uchar* ptrPad;
	for (int row = 0; row < img.rows; row++)
	{
		ptrImg = img.ptr<uchar>(row);
		ptrPad = pad.ptr<uchar>(row + padX);
		for (int col = 0; col < img.cols; col++)
		{
			ptrPad[col + padY] = ptrImg[col];
		}
	}
	cv::Mat tempPad;
	pad.copyTo(tempPad);
	for (int row = padX; row < tempPad.rows - padX; row++)
	{
		ptrPad = tempPad.ptr<uchar>(row);
		for (int col = padY; col < tempPad.cols - padY; col++)
		{
			cv::Mat temp = cv::Mat(pad, cv::Rect(col - padY, row - padX, n, m));
			temp.convertTo(temp, CV_32FC1);
			float tempValue = 0;
			for (int i = 0; i < temp.rows; i++)
				for (int j = 0; j < temp.cols; j++)
				{
					tempValue = tempValue + 1.0F/temp.at<float>(i, j);
					//std::cout << tempValue << std::endl;
				}
			//std::cout << temp << ":" << std::ceil(std::pow(tempValue, (int)(1 / (m * n)))) << std::endl;
			ptrPad[col] = (float)(m*n)/tempValue;
		}
	}
	//std::cout << tempPad << std::endl;
	cv::Mat finalImage(cv::Mat(tempPad, cv::Rect(padX, padY, img.cols, img.rows)));

	cv::imshow("Original Image", img);
	cv::imshow("Padded Image After Harmonic mean Filter", finalImage);
	//cv::waitKey(1000);
	cv::destroyAllWindows();
	cv::imwrite("../bin/Section_5_3/Image_Gaussian_Noise_After_Harmonic_mean_filter.jpg", finalImage);
}

void contraharmonic_mean(const cv::Mat& img, int m, int n, float Q, std::string saltOrPepper)
{
	std::cout << "Image size: " << img.size() << std::endl;
	if (m % 2 == 0)
		m = std::ceil(m);
	if (n % 2 == 0)
		n = std::ceil(n);
	int padX = std::floor((m) / 2);
	int padY = std::floor((n) / 2);
	int square;

	if (img.rows != img.cols)
	{
		if (img.rows > img.cols)
			square = img.rows;
		else
			square = img.cols;
	}

	cv::Mat pad = cv::Mat::zeros(square + 2 * padX, square + 2 * padY, CV_8UC1);

	const uchar* ptrImg;
	uchar* ptrPad;
	for (int row = 0; row < img.rows; row++)
	{
		ptrImg = img.ptr<uchar>(row);
		ptrPad = pad.ptr<uchar>(row + padX);
		for (int col = 0; col < img.cols; col++)
		{
			ptrPad[col + padY] = ptrImg[col];
		}
	}
	cv::Mat tempPad;
	pad.copyTo(tempPad);
	for (int row = padX; row < tempPad.rows - padX; row++)
	{
		ptrPad = tempPad.ptr<uchar>(row);
		for (int col = padY; col < tempPad.cols - padY; col++)
		{
			cv::Mat temp = cv::Mat(pad, cv::Rect(col - padY, row - padX, n, m));
			temp.convertTo(temp, CV_32FC1);
			float tempValue1 = 0;
			float tempValue2 = 0;

			for (int i = 0; i < temp.rows; i++)
				for (int j = 0; j < temp.cols; j++)
				{
					tempValue1 = tempValue1 + std::pow( temp.at<float>(i, j), Q + 1);
					tempValue2 = tempValue2 + std::pow(temp.at<float>(i, j), Q);

					//std::cout << tempValue << std::endl;
				}
			//std::cout << temp << ":" << std::ceil(std::pow(tempValue, (int)(1 / (m * n)))) << std::endl;
			ptrPad[col] = tempValue1/tempValue2;
		}
	}
	//std::cout << tempPad << std::endl;
	cv::Mat finalImage(cv::Mat(tempPad, cv::Rect(padX, padY, img.cols, img.rows)));

	cv::imshow("Original Image", img);
	cv::imshow("Padded Image After ContraHarmonic mean Filter", finalImage);
	//cv::waitKey(1000);
	cv::destroyAllWindows();
	cv::imwrite("../bin/Section_5_3/Original_SaltOrPepper_Noise_ContraHarmonic_mean_filter" + saltOrPepper + std::to_string(Q) + ".jpg", img);
	cv::imwrite("../bin/Section_5_3/Image_SaltOrPepper_Noise_After_ContraHarmonic_mean_filter" + saltOrPepper + "_" + std::to_string(Q) + ".jpg", finalImage);
}

std::vector<int> uniqueHistogram(const cv::Mat& kernel)
{
	int* hist;
	const uchar* ptrKernel;
	hist = new int[256];
	for (int i = 0; i < 256; i++)
		hist[i] = 0;

	for (int i = 0; i < 256; i++)
	{
		for (int row = 0; row < kernel.rows; row++)
		{
			ptrKernel = kernel.ptr<uchar>(row);
			for (int col = 0; col < kernel.cols; col++)
			{
				if (ptrKernel[col] == (uchar)i)
					hist[i] += 1;
			}
		}
	}
	
	std::vector<int> unique;
	for (int i = 0; i < 256; i++)
		if (hist[i] != 0)
			unique.push_back(i);
	//By default this will be already ordered
	delete[] hist;
	return unique;
}

cv::Mat median_filter(const cv::Mat& img, int m, int n, std::string pass)
{
	std::cout << "Image size: " << img.size() << std::endl;
	if (m % 2 == 0)
		m = std::ceil(m);
	if (n % 2 == 0)
		n = std::ceil(n);
	int padX = std::floor((m) / 2);
	int padY = std::floor((n) / 2);
	int square;

	if (img.rows != img.cols)
	{
		if (img.rows > img.cols)
			square = img.rows;
		else
			square = img.cols;
	}

	cv::Mat pad = cv::Mat::zeros(img.rows + 2 * padX, img.cols + 2 * padY, CV_8UC1);

	const uchar* ptrImg;
	uchar* ptrPad;
	for (int row = 0; row < img.rows; row++)
	{
		ptrImg = img.ptr<uchar>(row);
		ptrPad = pad.ptr<uchar>(row + padX);
		for (int col = 0; col < img.cols; col++)
		{
			ptrPad[col + padY] = ptrImg[col];
		}
	}
	cv::Mat tempPad;
	pad.copyTo(tempPad);
	for (int row = padX; row < tempPad.rows - padX; row++)
	{
		ptrPad = tempPad.ptr<uchar>(row);
		for (int col = padY; col < tempPad.cols - padY; col++)
		{
			cv::Mat temp = cv::Mat(pad, cv::Rect(col - padY, row - padX, n, m));
			std::vector<int> unique = uniqueHistogram(temp);
			int med;
			if (unique.size() % 2 == 0)
				med = (int)((unique.size() / 2)) - 1;
			else
				med = std::floor(unique.size()/2);
			
			ptrPad[col] = unique.at(med);
		}
	}
	//std::cout << tempPad << std::endl;
	cv::Mat finalImage(cv::Mat(tempPad, cv::Rect(padX, padY, img.cols, img.rows)));

	cv::imshow("Original Image", img);
	cv::imshow("Padded Image After Median Filter", finalImage);
	//cv::waitKey(1000);
	cv::destroyAllWindows();
	cv::imwrite("../bin/Section_5_3/Original_SaltAndPepper_Noise_Median_filter_pass" + pass + "_" + std::to_string(m) + "x" + std::to_string(n) + ".jpg", img);
	cv::imwrite("../bin/Section_5_3/Image_SaltAndPepper_Noise_After_Median_filter_pass"+ pass + "_"  + std::to_string(m) + "x" + std::to_string(n) + ".jpg", finalImage);
	return finalImage;
}

void max_filter(const cv::Mat& img, int m, int n)
{
	std::cout << "Image size: " << img.size() << std::endl;
	if (m % 2 == 0)
		m = std::ceil(m);
	if (n % 2 == 0)
		n = std::ceil(n);
	int padX = std::floor((m) / 2);
	int padY = std::floor((n) / 2);
	int square;

	if (img.rows != img.cols)
	{
		if (img.rows > img.cols)
			square = img.rows;
		else
			square = img.cols;
	}

	cv::Mat pad = cv::Mat::zeros(img.rows + 2 * padX, img.cols + 2 * padY, CV_8UC1);

	const uchar* ptrImg;
	uchar* ptrPad;
	for (int row = 0; row < img.rows; row++)
	{
		ptrImg = img.ptr<uchar>(row);
		ptrPad = pad.ptr<uchar>(row + padX);
		for (int col = 0; col < img.cols; col++)
		{
			ptrPad[col + padY] = ptrImg[col];
		}
	}
	cv::Mat tempPad;
	pad.copyTo(tempPad);
	for (int row = padX; row < tempPad.rows - padX; row++)
	{
		ptrPad = tempPad.ptr<uchar>(row);
		for (int col = padY; col < tempPad.cols - padY; col++)
		{
			cv::Mat temp = cv::Mat(pad, cv::Rect(col - padY, row - padX, n, m));
			std::vector<int> unique = uniqueHistogram(temp);
			if(!unique.empty())
				ptrPad[col] = unique.back();
		}
	}
	//std::cout << tempPad << std::endl;
	cv::Mat finalImage(cv::Mat(tempPad, cv::Rect(padX, padY, img.cols, img.rows)));

	cv::imshow("Original Image", img);
	cv::imshow("Padded Image After Maximum Filter", finalImage);
	//cv::waitKey(1000);
	cv::destroyAllWindows();
	cv::imwrite("../bin/Section_5_3/Original_Pepper_Noise_Maximum_filter_" + std::to_string(m) + "x" + std::to_string(n) + ".jpg", img);
	cv::imwrite("../bin/Section_5_3/Image_Pepper_Noise_After_Maximum_filter_" + std::to_string(m) + "x" + std::to_string(n) + ".jpg", finalImage);
}

void min_filter(const cv::Mat& img, int m, int n)
{
	std::cout << "Image size: " << img.size() << std::endl;
	if (m % 2 == 0)
		m = std::ceil(m);
	if (n % 2 == 0)
		n = std::ceil(n);
	int padX = std::floor((m) / 2);
	int padY = std::floor((n) / 2);
	int square;

	if (img.rows != img.cols)
	{
		if (img.rows > img.cols)
			square = img.rows;
		else
			square = img.cols;
	}

	cv::Mat pad = cv::Mat::zeros(img.rows + 2 * padX, img.cols + 2 * padY, CV_8UC1);

	const uchar* ptrImg;
	uchar* ptrPad;
	for (int row = 0; row < img.rows; row++)
	{
		ptrImg = img.ptr<uchar>(row);
		ptrPad = pad.ptr<uchar>(row + padX);
		for (int col = 0; col < img.cols; col++)
		{
			ptrPad[col + padY] = ptrImg[col];
		}
	}
	cv::Mat tempPad;
	pad.copyTo(tempPad);
	for (int row = padX; row < tempPad.rows - padX; row++)
	{
		ptrPad = tempPad.ptr<uchar>(row);
		for (int col = padY; col < tempPad.cols - padY; col++)
		{
			cv::Mat temp = cv::Mat(pad, cv::Rect(col - padY, row - padX, n, m));
			std::vector<int> unique = uniqueHistogram(temp);
			ptrPad[col] = *(unique.begin());
		}
	}
	//std::cout << tempPad << std::endl;
	cv::Mat finalImage(cv::Mat(tempPad, cv::Rect(padX, padY, img.cols, img.rows)));

	cv::imshow("Original Image", img);
	cv::imshow("Padded Image After Minimum Filter", finalImage);
	//cv::waitKey(1000);
	cv::destroyAllWindows();
	cv::imwrite("../bin/Section_5_3/Original_Salt_Noise_Minimum_filter_" + std::to_string(m) + "x" + std::to_string(n) + ".jpg", img);
	cv::imwrite("../bin/Section_5_3/Image_Salt_Noise_After_Minimum_filter_" + std::to_string(m) + "x" + std::to_string(n) + ".jpg", finalImage);
}
void midway_filter(const cv::Mat& img, int m, int n)
{
	std::cout << "Image size: " << img.size() << std::endl;
	if (m % 2 == 0)
		m = std::ceil(m);
	if (n % 2 == 0)
		n = std::ceil(n);
	int padX = std::floor((m) / 2);
	int padY = std::floor((n) / 2);
	int square;

	if (img.rows != img.cols)
	{
		if (img.rows > img.cols)
			square = img.rows;
		else
			square = img.cols;
	}

	cv::Mat pad = cv::Mat::zeros(img.rows + 2 * padX, img.cols + 2 * padY, CV_8UC1);

	const uchar* ptrImg;
	uchar* ptrPad;
	for (int row = 0; row < img.rows; row++)
	{
		ptrImg = img.ptr<uchar>(row);
		ptrPad = pad.ptr<uchar>(row + padX);
		for (int col = 0; col < img.cols; col++)
		{
			ptrPad[col + padY] = ptrImg[col];
		}
	}
	cv::Mat tempPad;
	pad.copyTo(tempPad);
	for (int row = padX; row < tempPad.rows - padX; row++)
	{
		ptrPad = tempPad.ptr<uchar>(row);
		for (int col = padY; col < tempPad.cols - padY; col++)
		{
			cv::Mat temp = cv::Mat(pad, cv::Rect(col - padY, row - padX, n, m));
			std::vector<int> unique = uniqueHistogram(temp);
			if (!unique.empty())
				ptrPad[col] = (int) ((unique.back() + *(unique.begin()))/2);
		}
	}
	//std::cout << tempPad << std::endl;
	cv::Mat finalImage(cv::Mat(tempPad, cv::Rect(padX, padY, img.cols, img.rows)));

	cv::imshow("Original Image", img);
	cv::imshow("Padded Image After MidWay Filter", finalImage);
	//cv::waitKey(1000);
	cv::destroyAllWindows();
	cv::imwrite("../bin/Section_5_3/Original_Gaussian_MidWay_filter_" + std::to_string(m) + "x" + std::to_string(n) + ".jpg", img);
	cv::imwrite("../bin/Section_5_3/Image_Gaussian_Noise_After_MidWay_filter_" + std::to_string(m) + "x" + std::to_string(n) + ".jpg", finalImage);
}

float variance_neighborhood(const cv::Mat& img, float& mean)
{
	mean = 0.0F;
	int* hist;
	hist = new int[256];
	for (int i = 0; i < 256; i++)
		hist[i] = 0;
	const uchar* ptr;
	for (int i = 0; i < 256; i++)
	{
		for (int row = 0; row < img.rows; row++)
		{
			ptr = img.ptr<uchar>(row);
			for (int col = 0; col < img.cols; col++)
				if (ptr[col] == i)
					hist[i]++;
		}
	}
	std::vector<int> spread;
	std::vector<float> prob;

	for (int i = 0; i < 256; i++)
	{
		if (hist[i] != 0)
		{
			spread.push_back(i); 
			prob.push_back(((float)hist[i]) / (img.rows * img.cols));

		}
	}
	int count = 0;
	for (std::vector<int>::iterator itr = spread.begin(); itr != spread.end(); itr++)
	{
		mean += (*itr) * prob[count];
		count++;
	}
	float variance = 0.0F;
	count = 0;
	for (std::vector<int>::iterator itr = spread.begin(); itr != spread.end(); itr++)
	{
		variance += std::pow((*itr) - mean, 2) * prob[count];
		count++;
	}
	delete[] hist;
	return variance;
}

void adaptive_local_noise_reduction(const cv::Mat& img, int m, int n, float varNoise)
{
	std::cout << "Image size: " << img.size() << std::endl;
	if (m % 2 == 0)
		m = std::ceil(m);
	if (n % 2 == 0)
		n = std::ceil(n);
	int padX = std::floor((m) / 2);
	int padY = std::floor((n) / 2);
	int square;

	if (img.rows != img.cols)
	{
		if (img.rows > img.cols)
			square = img.rows;
		else
			square = img.cols;
	}

	cv::Mat pad = cv::Mat::zeros(img.rows + 2 * padX, img.cols + 2 * padY, CV_8UC1);

	const uchar* ptrImg;
	uchar* ptrPad;
	for (int row = 0; row < img.rows; row++)
	{
		ptrImg = img.ptr<uchar>(row);
		ptrPad = pad.ptr<uchar>(row + padX);
		for (int col = 0; col < img.cols; col++)
		{
			ptrPad[col + padY] = ptrImg[col];
		}
	}
	cv::Mat tempPad;
	pad.copyTo(tempPad);
	const uchar* ptrPadded;
	for (int row = padX; row < tempPad.rows - padX; row++)
	{
		ptrPad = tempPad.ptr<uchar>(row);
		ptrPadded = pad.ptr<uchar>(row);

		for (int col = padY; col < tempPad.cols - padY; col++)
		{
			cv::Mat temp = cv::Mat(pad, cv::Rect(col - padY, row - padX, n, m));
			float mean = 0.0F;
			float variance;
			variance = variance_neighborhood(temp, mean);
			if(varNoise <= variance)
				ptrPad[col] = ptrPadded[col] - (float)(varNoise/variance)*(ptrPadded[col] - mean);
			else
				ptrPad[col] = ptrPadded[col] - 1.0F * (ptrPadded[col] - mean);
		}
	}
	//std::cout << tempPad << std::endl;
	cv::Mat finalImage(cv::Mat(tempPad, cv::Rect(padX, padY, img.cols, img.rows)));

	cv::imshow("Original Image", img);
	cv::imshow("Padded Image After adaptive local noise reduction Filter", finalImage);
	//cv::waitKey(1000);
	cv::destroyAllWindows();
	cv::imwrite("../bin/Section_5_3/Original_Gaussian_AdaptiveLocalNoiseReduction_filter_" + std::to_string(m) + "x" + std::to_string(n) + ".jpg", img);
	cv::imwrite("../bin/Section_5_3/Image_Gaussian_Noise_After_AdaptiveLocalNoiseReduction_filter_" + std::to_string(m) + "x" + std::to_string(n) + ".jpg", finalImage);
}
cv::Mat padding_image(const cv::Mat& img, int size)
{
	cv::Mat pad = cv::Mat::zeros(img.rows + 2 * std::floor(size / 2.0F), img.cols + 2 * std::floor(size / 2.0F), CV_8UC1);
	const uchar* ptrImg;
	uchar* ptrPad;
	for (int i = 0; i < img.rows; i++)
	{
		ptrImg = img.ptr<uchar>(i);
		ptrPad = pad.ptr<uchar>(i + std::floor(size / 2));
		for (int j = 0; j < img.cols; j++)
			ptrPad[j + (int)std::floor(size / 2)] = ptrImg[j];
	}
	return pad;
}

void adaptive_median_filter(const cv::Mat& img, int size, int maximum_size)
{
	int m = size; int n = size;

	std::cout << "Image size: " << img.size() << std::endl;
	if (m % 2 == 0)
		m = std::ceil(m);
	if (n % 2 == 0)
		n = std::ceil(n);
	int padX = std::floor((m) / 2);
	int padY = std::floor((n) / 2);
	int square;

	if (img.rows != img.cols)
	{
		if (img.rows > img.cols)
			square = img.rows;
		else
			square = img.cols;
	}

	cv::Mat pad = cv::Mat::zeros(img.rows + 2 * padX, img.cols + 2 * padY, CV_8UC1);

	const uchar* ptrImg;
	uchar* ptrPad;
	for (int row = 0; row < img.rows; row++)
	{
		ptrImg = img.ptr<uchar>(row);
		ptrPad = pad.ptr<uchar>(row + padX);
		for (int col = 0; col < img.cols; col++)
		{
			ptrPad[col + padY] = ptrImg[col];
		}
	}
	cv::Mat tempPad;
	pad.copyTo(tempPad);
	std::function<uchar(const cv::Mat&, const std::vector<cv::Mat>, const int, const int, bool&, int&, const int, int&, int&, int&, int)> levelA;
	levelA = [&levelA](const cv::Mat& img, const std::vector<cv::Mat>const padded_opitions, int col, const int row, bool& flag, int& size, const int maxSize, int& zmin, int& zmax, int& medValue, int level)->uchar
	{
		//std::cout << "Level A, size: " << size << "x" << size << std::endl;
		
		cv::Mat kernel = cv::Mat(padded_opitions[level], cv::Rect(col , row , size, size));//row, and col will be alreadyu centered
		flag = false;
		std::vector<int> unique = uniqueHistogram(kernel);
		if (!unique.empty())
			zmax = unique.back();
		zmin = *(unique.begin());
		int med;
		if (unique.size() % 2 == 0)
			med = (int)((unique.size() / 2)) - 1;
		else
			med = std::floor(unique.size() / 2);

		medValue = unique.at(med);

		if ((medValue > zmin) && (medValue < zmax))
		{
			flag = true;
			return 0;//Don't care
		}
		else
		{
			level++;
			if ((size + 1) % 2 == 0)
				size += 2;//To ensure that the kernel of odd size
			else
				size = size + 1;

		}

		if (size <= maxSize)
		{
			//std::cout << "Repeat Level A" << std::endl;
			return levelA(img, padded_opitions, col, row, flag, size, maxSize, zmin, zmax, medValue, level);
		}
		else
		{
			flag = false;
			//std::cout << "Pixel at this coordinate is one of the bipolar impulses" << std::endl;
			return medValue;
		}
			
	};

	std::function<uchar(int, int, int, int)> levelB;
	levelB = [](int padValue, int zmin, int zmax, int med)->uchar
	{
		if ((zmin < padValue) && (padValue < zmax))
			return padValue;
		return med;
	};

	std::vector<cv::Mat> padding_options;
	int sizeT = size;
	int c = 0;
	while (sizeT <= maximum_size)
	{
		std::cout << "Padding Image, level: " << c << std::endl;
		padding_options.push_back(padding_image(img, sizeT));
		if ((sizeT + 1) % 2 == 0)
			sizeT += 2;//To ensure that the kernel of odd size
		else
			sizeT = sizeT + 1;
		c++;
	}

	for (int row = padX; row < tempPad.rows - padX; row++)
	{
		ptrPad = tempPad.ptr<uchar>(row);
		for (int col = padY; col < tempPad.cols - padY; col++)
		{
			bool flag = false;
			int sizeT = size;
			int zmin, zmax, med;
			int VALUE;
			zmin = 0; zmax = 0; med = 0;
			VALUE = levelA(img, padding_options, col - padY, row - padX, flag, sizeT, maximum_size, zmin, zmax, med, 0);
			if (flag == true)
				VALUE = levelB(pad.at<uchar>(row, col), zmin, zmax, med);

			ptrPad[col] = VALUE;
		}
	}
	//std::cout << tempPad << std::endl;
	cv::Mat finalImage(cv::Mat(tempPad, cv::Rect(padX, padY, img.cols, img.rows)));

	cv::imshow("Original Image", img);
	cv::imshow("Padded Image After Adaptive Median Filter", finalImage);
	//cv::waitKey(1000);
	cv::destroyAllWindows();
	cv::imwrite("../bin/Section_5_3/Original_HighSaltAndPepper_Noise_AdaptiveMedian_filter_maxSize" + std::to_string(maximum_size) + "_" + std::to_string(m) + "x" + std::to_string(n) + ".jpg", img);
	cv::imwrite("../bin/Section_5_3/Image_HighSaltAndPepper_Noise_After_AdaptiveMedian_filter_maxSize" + std::to_string(maximum_size) + "_"  + std::to_string(m) + "x" + std::to_string(n) + ".jpg", finalImage);
}