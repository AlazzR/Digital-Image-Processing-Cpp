#include "Section_5_2_H_.h"


void displaying_histogram(const cv::Mat& img, std::string type)
{
	std::cout << "Section 5-2: Histogram for " << type << std::endl;
	float* hist;
	hist = new float[256];

	for (int i = 0; i < 256; i++)
		hist[i] = 0;
	
	const uchar* ptrImg;
	float sum = 0;
	for (int i = 0; i < 256; i++)
	{
		for (int row = 0; row < img.rows; row++)
		{
			ptrImg = img.ptr<uchar>(row);
			for (int col = 0; col < img.cols; col++)
			{
				if (ptrImg[col] == i)
					hist[i] += 1.0F;
			}
		}
		sum += hist[i];
		//hist[i] = hist[i] / (img.rows * img.cols);
	}

	std::cout << "Value of Sum: " << sum << " ,Number of pixesl: " << img.rows * img.cols << std::endl;
	int pos = 0;
	float tValue = 0.0F;
	for (int i = 0; i < 256; i++)
	{
		//finding Maximum value	
		if (hist[i] > tValue)
		{
			tValue = hist[i];
			pos = hist[i];
		}
	}

	cv::Mat Histogram = cv::Mat(256, 256, CV_8UC3, cv::Scalar::all(0));
	cv::Mat tempMat[3];
	cv::split(Histogram, tempMat);
	uchar* ptrHist;
	uchar* ptrHist2;

	for (int i = 0; i < 256; i++)
	{
		int temp = std::ceil( (hist[i]/tValue) * 256);
		ptrHist = tempMat[1].ptr<uchar>(i);
		ptrHist2 = tempMat[2].ptr<uchar>(i);

		for (int col = 0; col < temp; col++)
		{
			ptrHist[col] = 255;
			ptrHist2[col] = 255;

		}
	}

	cv::merge(tempMat, 3, Histogram);
	//cv::Mat regionOfInterest = cv::Mat(Histogram, cv::Rect(0, 0, Histogram.rows, pos + 10));
	cv::Point center(Histogram.cols / 2, Histogram.rows / 2);
	cv::Mat M = cv::getRotationMatrix2D(center, 90, 1);
	cv::warpAffine(Histogram, Histogram, M, Histogram.size(), CV_INTER_LINEAR, CV_HAL_BORDER_CONSTANT, cv::Scalar(0));
	//cv::resize(regionOfInterest, regionOfInterest, cv::Size(256, 256), cv::INTER_LINEAR);
	cv::imshow("Test Pattern Image", img);
	cv::imshow("Histogram", Histogram);
	//cv::waitKey(1000);
	cv::destroyAllWindows();

	cv::imwrite("../bin/Section_5_2/Original_" + type + "_Image.jpg", img);
	cv::imwrite("../bin/Section_5_2/Histogram_" + type + "_Image.jpg", Histogram);
	delete[] hist;//clearing the heap
}