#include "Section_3_5.h"
cv::Mat creating_box_filter(int size)
{
	cv::Mat kernal = cv::Mat::zeros(size, size, CV_32FC(1));
	try 
	{
		if (size % 2 == 0)
			throw "This isn't an odd size kernal";
		else
		{
			std::cout << "Kernal size is eligible" << std::endl;
			float* ptr;
			for (int row = 0; row < kernal.rows; row++)
			{
				ptr = kernal.ptr<float>(row);
				for (int col = 0; col < kernal.cols; col++)
					ptr[col] = (1.0F / ((float)(kernal.rows * kernal.cols)));
			}
			return kernal;
		}
	}
	catch(char* c)
	{
		std::cout << c << std::endl;
		return kernal;
	}
}

cv::Mat creating_gaussian_filter(float K, float std)
{
	int size = std::ceil(6 * std);
	//std::cout << size << std::endl;

	if (size % 2 == 0)
	{
		//throw "This isn't an odd size kernal and I will updated to become an odd";
		std::cout << "This isn't an odd size kernal and I will updated to become an odd" << std::endl;
		size = size - 1;
	}
	else
		std::cout << "Already an odd kernal" << std::endl;

	//int size = std::ceil(6 * std);//need to ensure to pass a value for std such that ceil(6*std) will result in an odd kernel.
	cv::Mat kernal = cv::Mat::zeros(size, size, CV_32FC(1));
	std::unique_ptr<int[]> vector(new int[size]);
	int count = 0;
	//std::cout << -(int)size / 2 << std::endl;
	for (int i = -(int)size / 2; i <= (int)size/2; i++)
	{
		vector[count] = i;
			count++;

	}
	//for (int i = 0; i < size; i++)
		//std::cout << vector[i] << "\t";
			
	//std::cout << std::endl;
	std::cout << "Kernal size is eligible" << std::endl;
	float* ptr;
	float sum=0;
	//like meshgrid in python
	for (int row = 0; row < kernal.rows; row++)
	{
		ptr = kernal.ptr<float>(row);
		//std::cout << std::pow(vector[row], 2) << std::endl;
		for (int col = 0; col < kernal.cols; col++)
		{
			float t1 = -1.0F * (std::pow(vector[row], 2) + std::pow(vector[col], 2));
			//std::cout << t1 << std::endl;
			float t2 = 2.0F * std::pow(std, 2);
			ptr[col] = (float)(K * std::exp(t1 /t2));
			sum += ptr[col];
		}
	}
	//Normalizing the kernel
	for (int row = 0; row < kernal.rows; row++)
	{
		ptr = kernal.ptr<float>(row);
		for (int col = 0; col < kernal.cols; col++)
		{
			ptr[col] = ptr[col]/sum;
		}
	}

	cv::Mat temp = cv::Mat::zeros(kernal.rows, kernal.cols, CV_8UC1);
	kernal.convertTo(temp, CV_8UC1);
	//std::cout << cv::format(temp, 4) << std::endl;
	//std::cout << "Kernel shape\n" <<cv::format(kernal, 4) << std::endl;
	std::cout << "Kernel size: " << kernal.size() << std::endl;
	//cv::imwrite("../bin/Section_3_5/Gaussian" + std::to_string(std) + "_" + std::to_string(std) + ".jpg", temp);
	return kernal;
		
	
	/*
	catch (char* c)
	{
		std::cout << c << std::endl;
		cv::Mat kernal = cv::Mat::zeros(size, size, CV_32FC(1));
		return kernal;
	}*/
}

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

//I will assume that the kernal already rotated twice to proceed with the convolution in the same manner as the correlation.
cv::Mat convolution_kernal_rotated(const cv::Mat& img, const cv::Mat& kernal,int padX, int padY, int sizeX, int sizeY)
{
	//Assume that the image is a square matrix
	cv::Mat paddedImage = cv::Mat::zeros(img.rows + 2 * padX, img.cols + 2 * padY, CV_32FC1);
	//copying the orignal image into the padded image
	float* ptrPad;
	const uchar* ptrImg;
	for (int i = 0; i < img.rows; i++)
	{
		ptrPad = paddedImage.ptr<float>(i + padX);
		ptrImg = img.ptr<uchar>(i);
		for (int j = 0; j < img.cols; j++)
			ptrPad[j + padY] = (float)ptrImg[j];
	}
	cv::Mat tempImage = cv::Mat::zeros(paddedImage.rows, paddedImage.cols, CV_32FC1);

	for (int row = padX; row < paddedImage.rows - padX; row++)
	{
		for (int col = padY; col < paddedImage.cols - padY; col++)
		{
			cv::Mat temp = cv::Mat(paddedImage, cv::Rect(row - padX, col - padY, sizeX, sizeY));
			const float* ptrPad;
			const float* ptrKernal;
			float* ptrTemp;
			for (int i = 0; i < temp.rows; i++)
			{
				ptrPad = temp.ptr<float>(i);
				ptrKernal = kernal.ptr<float>(i);
				ptrTemp = tempImage.ptr<float>(row);
				for (int j = 0; j < temp.cols; j++)
				{
					ptrTemp[col] += ptrPad[j] * ptrKernal[j];
				}
			}
		}
	}
	tempImage = tempImage.t();
	rescaling_intensities(tempImage);
	cv::Mat temp = cv::Mat(tempImage.rows, tempImage.cols, CV_8UC1);
	tempImage.convertTo(temp, CV_8UC1);
	cv::Mat finalImage(temp, cv::Rect(padX, padY, img.rows, img.cols));
	return finalImage;
}

void convolving_by_box_filter(const cv::Mat& img, int size, std::string type)
{
	cv::Mat filter(creating_box_filter(size));
	//std::cout << filter << std::endl;
	int padX = (int)((size - 1) / 2);
	int padY = (int)((size - 1) / 2);
	//No need to rotate the box fileter because it is a circular symmetric filter
	cv::Mat finalImage(convolution_kernal_rotated(img, filter, padX, padY, size, size));
	cv::imshow("Original Image", img);
	cv::imshow("Blurred Image by box filter", finalImage);
	cv::waitKey(1000);
	cv::imwrite("../bin/Section_3_5/Original_test_pattern_image.jpg", img);
	cv::imwrite("../bin/Section_3_5/Blurred" + type +"_by_box_filter_test_pattern_image.jpg", finalImage);

}

void convolving_by_gaussian_filter(const cv::Mat& img, float K, float std, std::string type)
{
	cv::Mat filter(creating_gaussian_filter(K, std));
	//std::cout << filter << std::endl;
	int padX = (int)((std::ceil(6 * std) - 1.0F) / 2);
	int padY = (int)((std::ceil(6 * std) - 1.0F) / 2);
	//No need to rotate the box fileter because it is a circular symmetric filter
	cv::Mat finalImage(convolution_kernal_rotated(img, filter, padX, padY, ceil(6 * std), ceil(6 * std)));
	cv::imshow("Original Image", img);
	cv::imshow("Blurred Image by Gaussian filter", finalImage);
	cv::waitKey(1000);
	cv::imwrite("../bin/Section_3_5/Original_test_pattern_image.jpg", img);
	cv::imwrite("../bin/Section_3_5/Blurred" + type + "_by_Gaussian_filter_test_pattern_image.jpg", finalImage);
	cv::destroyAllWindows();
}

uchar finding_median(const cv::Mat& kernal)
{
	std::vector<uchar> flattend;
	const uchar* ptr;
	for (int i = 0; i < kernal.rows; i++)
	{
		ptr = kernal.ptr<uchar>(i);
		for (int j = 0; j < kernal.cols; j++)
		{
			flattend.push_back(ptr[j]);
		}
	}
	//ordering the flattened vector in ascending manner
	sort(flattend.begin(), flattend.end());
	/*
	std::cout << (kernal.rows * kernal.cols) / 2.0F << std::endl;
	std::cout << std::floor((kernal.rows * kernal.cols) / 2.0F) << " : " << std::ceil((kernal.rows * kernal.cols) / 2.0F) << std::endl;
	std::cout << "Mode =0:  " << (int)flattend.at((kernal.rows * kernal.cols) / 2.0F) << std::endl;
	std::cout << "Mode !=0:  " << (int)(flattend.at(std::floor((kernal.rows * kernal.cols) / 2.0F)) + flattend.at(std::ceil((kernal.rows * kernal.cols) / 2.0F)))/ 2.0F << std::endl;
	*/
	//if size was odd then the median is found in size/2 where is index start from zero
	if (((kernal.rows * kernal.cols) % 2) != 0)
	{
		//std::cout << "The kernel flattend size was odd" << std::endl;
		return (int)flattend.at(std::floor((kernal.rows * kernal.cols) / 2.0F));
	}
	return (int)(flattend.at(std::floor((kernal.rows * kernal.cols) / 2.0F)) + flattend.at(std::ceil((kernal.rows * kernal.cols) / 2.0F))) / 2.0F;
}

void convolving_by_saltPepper_filter(const cv::Mat& img, int size)
{
	try
	{
		if (size % 2 == 0)
			throw "This isn't an odd kernal";
		else
		{
			std::cout << "Kernal size is eligible" << std::endl;
			int pad = (int)((size - 1) / 2);
			//Need to appended with more pads because its rows != cols
			//std::cout << img.cols << " : " << img.rows << std::endl;
			int temp = img.cols + 2 * pad;
			//std::cout << temp << std::endl;
			cv::Mat paddedImage = cv::Mat::zeros(temp, temp, CV_8UC1);
			//std::cout << paddedImage.size() << std::endl;

			//copying the orignal image into the padded image
			uchar* ptrPad;
			const uchar* ptrImg;
			for (int i = 0; i < img.rows; i++)
			{
				ptrPad = paddedImage.ptr<uchar>(i + pad);
				ptrImg = img.ptr<uchar>(i);
				for (int j = 0; j < img.cols; j++)
					ptrPad[j + pad] = ptrImg[j];
			}
			//cv::imshow("Temp", paddedImage);
			//cv::waitKey(2000);
			cv::Mat tempImage = cv::Mat::zeros(paddedImage.rows, paddedImage.cols, CV_8UC1);
			uchar* ptrTemp;
			//std::cout << tempImage.size() << std::endl;
			//std::cout << tempImage.rows << std::endl;
			//std::cout << tempImage.cols<< std::endl;
			//std::cout << paddedImage.size() << std::endl;
			//std::cout << paddedImage.rows << std::endl;
			//std::cout << paddedImage.cols << std::endl;
			for (int i = pad; i < paddedImage.rows - pad; i++)
			{
				ptrTemp = tempImage.ptr<uchar>(i);
				//std::cout << paddedImage.rows << std::endl;
				for (int j = pad; j < paddedImage.cols - pad; j++)
				{
					
					//std::cout << j << " a" << std::endl;
					cv::Mat kernal = cv::Mat(paddedImage, cv::Rect(i - pad, j - pad, size, size));
					//std::cout << 'b' << std::endl;
					//std::cout << i << " : " << j << std::endl;
					ptrTemp[j] = finding_median(kernal);
				}
			}
			tempImage = tempImage.t();
			cv::Mat finalImage(tempImage, cv::Rect(pad, pad, img.cols, img.rows));
			cv::imshow("Original Image", img);
			cv::imshow("Image after removing salt and pepper noise", finalImage);
			cv::waitKey(1000);
			cv::destroyAllWindows();
			cv::imwrite("../bin/Section_3_5/Original_slat_peppered_image.jpg", img);
			cv::imwrite("../bin/Section_3_5/Final_slat_peppered_image.jpg", finalImage);

		}
	}

	catch (char* c)
	{
		std::cout << c << std::endl;
	}
}

