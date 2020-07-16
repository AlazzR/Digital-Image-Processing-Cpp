#include "Section_3_3.h"
template <typename T>
std::unique_ptr<float[]> calculating_histogram(const cv::Mat& img)
{
	const T* ptrImg;
	std::unique_ptr<float[]> ptr(new float[256]);
	for (int i = 0; i < 256; i++)
		ptr[i] = 0.0F;

	for (int row = 0; row < img.rows; row++)
	{
		ptrImg = img.ptr<T>(row);
		for (int col = 0; col < img.cols; col++)
		{
			for(uchar count = 0; count < 256; count++)
			{
				if (count == ptrImg[col])
				{
					ptr[count] += 1.0F;
					break;
				}
			}
		}
	}

	for (int i = 0; i < 256; i++)
		ptr[i] = ptr[i]/(img.rows * img.cols);


	return ptr;//Will invoke the move constructor semantics
}

void histogram_equalization(const cv::Mat& img, std::string type)
{

	std::unique_ptr<float[]> ptr(calculating_histogram<uchar>(img));

	//for (int i = 0; i < 256; i++)
		//std::cout << "Value at " << i << " : " << ptr[i] << std::endl;
	
	//Make sure that the p(r_k) is a legitimate PMF
	float sum = 0;
	for (int i = 0; i < 256; i++)
		sum += ptr[i];
	std::cout << "Value of Sum: " << sum << std::endl;

	//formual s_k= T(r_k) = (L-1) /sum_{i=0}^{k}P_r(r_k); k=0,...,L-1
	cv::Mat tempImg = cv::Mat::zeros(img.rows, img.cols, CV_32FC(1));
	
	for (int row = 0; row < img.rows; row++)
	{
		const uchar* ptrImg = img.ptr<uchar>(row);
		float* ptrTemp = tempImg.ptr<float>(row);
		for (int col = 0; col < img.cols ; col++)
		{
			for (int k = 0; k < (int) ptrImg[col]; k++)
			{
				ptrTemp[col] += (256 - 1) * ptr[k];
			}
		}
	}

	cv::Mat finalImage = cv::Mat(img.rows, img.cols, CV_8UC(1));
	tempImg.convertTo(finalImage, CV_8UC(1));
	cv::imshow("Original Image", img);
	cv::imshow("Equalized Image", finalImage);
	//cv::waitKey(1000);
	cv::destroyAllWindows();
	//std::cout << "../bin/Section_3_2/Original" + type + "_pollen_image.jpg" << std::endl;
	cv::imwrite("../bin/Section_3_3/Original" + type + "_image.jpg", img);
	cv::imwrite("../bin/Section_3_3/Equalized" + type + "_image.jpg", finalImage);


}

void local_histogram_processing(const cv::Mat& img, int size)
{
	try
	{
		if (size % 2 == 0)
			throw "Kernal size is even";
		else
		{
			std::cout << "Kernal size is eligible" << std::endl;
			int sizeX, sizeY;
			sizeX = (int)((size - 1) / 2);
			sizeY = (int)((size - 1) / 2);
			//std::cout << "sizeX: " << sizeX << " sizeY: " << sizeY << std::endl;
			cv::Mat paddedImage = cv::Mat::ones(2*sizeX + img.rows, 2*sizeY + img.cols, CV_8UC(1)) *255;
			uchar* ptrPad;
			const uchar* ptrImg;
			//Coping image into padded Image
			for (int i = 0; i < img.rows ; i++)
			{
				ptrPad = paddedImage.ptr<uchar>(i + sizeX);
				ptrImg = img.ptr<uchar>(i);
				for (int j = 0; j < img.cols; j++)
				{
					ptrPad[j + sizeY] = ptrImg[j];
				}
			}
			//Doing global histogram equalization
			histogram_equalization(paddedImage, "_padded_blocks_with_hidden_values");
			//Doint Local histogram Eqalization
			cv::Mat tempImg = cv::Mat::zeros(paddedImage.rows, paddedImage.cols, CV_32FC(1));
			for (int i = sizeX; i < tempImg.rows - sizeX; i++)
			{
				for (int j = sizeY; j < tempImg.cols - sizeY; j++)
				{
					cv::Mat kernal(paddedImage, cv::Rect(i - sizeX, j - sizeY, size, size));//kernal type is CV_8UC1
					//our cener is ixj
					//std::cout << "Kernal size: " << kernal.size() << std::endl;
					std::unique_ptr<float[]> ptr(calculating_histogram<uchar>(kernal));

					//float sum = 0;
					//for (int i = 0; i < 256; i++)
					//	sum += ptr[i];
					//std::cout << "Value of Sum: " << sum << std::endl;

					uchar* ptrKernal;
					float* ptrTempImg;
					for (int row = 0; row < kernal.rows; row++)
					{
						ptrKernal = kernal.ptr<uchar>(row);
						ptrTempImg = tempImg.ptr<float>(i);
						for (int col = 0; col < kernal.cols; col++)
						{
							for (int k = 0; k < (int)ptrKernal[col]; k++)
							{
								ptrTempImg[j] += (float)((256 - 1) * ptr[k]);
							}
						}
					}
				}
			}

			//taking the negative of the image
			tempImg = tempImg.t();//We need to transpose it because the computed pixels would be flipped, and I am not sure why this is happening.
			for (int i = 0; i < tempImg.rows; i++)
			{
				float* ptr = tempImg.ptr<float>(i);
				for (int j = 0; j < tempImg.cols; j++)
				{
					ptr[j] = 255 - ptr[j];
				}
			}
			cv::Mat tempUnPadded(tempImg, cv::Rect(sizeX, sizeY, tempImg.rows - 2*sizeX, tempImg.cols - 2*sizeY));
			cv::Mat finalImage = cv::Mat(tempUnPadded.rows, tempUnPadded.cols, CV_8UC(1));
			tempUnPadded.convertTo(finalImage, CV_8UC(1));
			//cv::imshow("Temp image", temp);
			cv::imshow("Local Equalized Image", finalImage);
			cv::waitKey(2000);

			//cv::Mat temp = cv::Mat(img, cv::Rect(0, 0, 100, 100));
			//cv::imshow("Temp image", temp);
			cv::imshow("Original Image", img);
			cv::waitKey(1000);
			cv::destroyAllWindows();
			cv::imwrite("../bin/Section_3_3/Original_block_with_hidden_pixels.jpg", img);
			cv::imwrite("../bin/Section_3_3/local_equalized_block_with_hidden_pixels.jpg", finalImage);
		}
	}
	catch (char* c)
	{
		std::cout << c << std::endl;
	}

}

template<typename T> 
float calculating_mean_neighborhood(const cv::Mat& img, const std::unique_ptr<T[]>& hist)
{
	float mean = 0.0F;
	for (int i = 0; i < 256; i++)
	{
		mean += ((float)i * hist[i]);
	}

	return mean;
}

template<typename T>
float calculating_stdDeviation_neighborhood(const cv::Mat& img, const std::unique_ptr<T[]>& hist, float mean)
{
	float std = 0.0F;
	for (int i = 0; i < 256; i++)
	{
		std += std::pow((float)i - mean, 2) * hist[i];
	}
	std = std::sqrt(std);
	return std;
}

void statistical_local_enhancement(const cv::Mat& img, float C, float  k0, float k1, float k2, float k3, int size)
{
	try
	{
		if (size % 2 == 0)
			throw "Kernal size is even";
		else
		{
			std::cout << "Kernal size is eligible" << std::endl;
			int sizeX, sizeY;
			sizeX = (int)((size - 1) / 2);
			sizeY = (int)((size - 1) / 2);
			std::unique_ptr<float[]> ptrHist(calculating_histogram<uchar>(img));
			float m_g = calculating_mean_neighborhood<float>(img, ptrHist);
			float std_g = calculating_stdDeviation_neighborhood<float>(img, ptrHist, m_g);
			std::cout << "Global Mean: " << m_g << " Global Standard Deviation: " << std_g << std::endl;
			cv::Mat paddedImage = cv::Mat(2 * sizeX + img.rows, 2 * sizeY + img.cols, CV_8UC(1));
			const uchar* ptrImg;
			uchar* ptrPadd;
			for (int i = 0; i < img.rows; i++)
			{
				ptrImg = img.ptr<uchar>(i);
				ptrPadd = paddedImage.ptr<uchar>(i + sizeX);
				for (int j = 0; j < img.cols; j++)
				{
					ptrPadd[j + sizeY] = ptrImg[j];
				}
			}
			cv::Mat tempImage = cv::Mat::zeros(paddedImage.rows, paddedImage.cols, CV_32FC(1));
			for (int i = sizeX; i < paddedImage.rows - sizeX; i++)
			{
				const uchar* ptrPadded = paddedImage.ptr<uchar>(i);
				float* ptrTempImg = tempImage.ptr<float>(i);
				for (int j = sizeY; j < paddedImage.cols - sizeY; j++)
				{
					cv::Mat kernal(paddedImage, cv::Rect(i - sizeX, j - sizeY, size, size));
					std::unique_ptr<float[]> ptrkernalHist(calculating_histogram<uchar>(kernal));
					float m_neigh = calculating_mean_neighborhood<float>(kernal, ptrkernalHist);
					float std_neigh = calculating_stdDeviation_neighborhood<float>(kernal, ptrkernalHist, m_neigh);

					if (((k0 * m_g <= m_neigh) && (m_neigh <= k1 * m_g)) && ((k2 * std_g <= std_neigh) && (std_neigh <= k3 * std_g)))
						ptrTempImg[j] = C * (float) ptrPadded[j];
					else
						ptrTempImg[j] = (float)ptrPadded[j];
				}
			}

			cv::Mat tempUnPadded(tempImage, cv::Rect(sizeX, sizeY, tempImage.rows - 2*sizeX, tempImage.cols - 2*sizeY));
			cv::Mat finalImage = cv::Mat(tempUnPadded.rows, tempUnPadded.cols, CV_8UC(1));
			tempUnPadded.convertTo(finalImage, CV_8UC(1));
			
			cv::imshow("Padded Image", paddedImage);
			//cv::waitKey(1000);

			cv::imshow("Original Image", img);
			//cv::waitKey(1000);
			cv::imshow("Statistically Enhanced Image", finalImage);
			//cv::waitKey(1000);
			cv::destroyAllWindows();
			cv::imwrite("../bin/Section_3_3/Original_block_with_hidden_pixels.jpg", img);
			cv::imwrite("../bin/Section_3_3/Statistically_enhanced_image_block_with_hidden_pixels.jpg", finalImage);

		}
	}
	catch (char* c)
	{
		std::cout << c << std::endl;
	}

}