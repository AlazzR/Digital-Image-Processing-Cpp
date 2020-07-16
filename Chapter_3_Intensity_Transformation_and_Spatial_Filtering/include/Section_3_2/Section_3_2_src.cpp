#include "Section_3_2.h"

template<typename T>
float calculating_mean(const cv::Mat& img)
{
	float mean = 0;
	//calculating the mean
	T* ptr;
	for (int i = 0; i < img.rows; i++)
	{
		ptr = img.ptr<T>(i);
		for (int j = 0; j < img.cols; j++)
			mean += ptr[j];
	}
	mean = mean / (img.cols * img.rows);
	return mean;
}

void image_negative(const cv::Mat& img)
{
	cv::Mat tempImg = cv::Mat::zeros(img.rows, img.cols, CV_32FC(1));
	img.convertTo(tempImg, CV_32FC(1));
	float* ptr;
	// Changing the image to become the negative of it self.
	for (int row = 0; row < tempImg.rows; row++)
	{
		ptr = tempImg.ptr<float>(row);
		for (int col = 0; col < tempImg.cols; col++)
			ptr[col] = 255 - ptr[col];//s = L -1 -r
	}

	cv::imshow("Digital Mammogram", img);
	cv::Mat finalImage = cv::Mat(tempImg.rows, tempImg.cols, CV_8UC(1));
	tempImg.convertTo(finalImage, CV_8UC(1));
	cv::imshow("Transformed Digital Mammogram", finalImage);
	cv::namedWindow("Transformed Digital Mammogram");
	cv::moveWindow("Transformed Digital Mammogram", 500, 500);
	//cv::waitKey(1000);
	cv::destroyAllWindows();
	cv::imwrite("../bin/Section_3_2/original_mammogram_img.jpg", img);
	cv::imwrite("../bin/Section_3_2/negative_mammogram_img.jpg", tempImg);
	/*
	//std::cout << "Negative image function for: " << Section_3_2 << std::endl;
	//cv::Mat t1 = cv::Mat::eye(4, 4, CV_8UC1);
	//std::cout << t1 << std::endl;
	cv::Mat t1 = cv::Mat::eye(4, 4, CV_32FC1);
	std::cout << t1 << std::endl;
	std::cout << t1.rows << std::endl;
	float* ptr;
	for (int i = 0; i < t1.rows; ++i)
	{
		ptr = t1.ptr<float>(i);
		for (int j = 0; j < t1.cols; ++j)
			ptr[j] = (1000.0F * ptr[j]) / 255.0F;
	}
	std::cout << t1 << std::endl;

	cv::Mat t2 = cv::Mat::zeros(4, 4, CV_8UC1);
	t1.convertTo(t2, CV_8UC1);
	std::cout << t2 << std::endl;
	cv::Mat img = cv::imread("../digital_mammogram.tif");
	cv::imshow("Digital Mammogram", img);
	cv::waitKey(1000);
	cv::destroyWindow("Digital Mammogram");
	*/
}

void image_power_law(const cv::Mat& img, float c, float gamma)
{
	cv::Mat temp = cv::Mat(img.rows, img.cols, CV_32FC(1));
	img.convertTo(temp, CV_32FC(1));

	//cv::Mat temp2;
	//img.copyTo(temp2);
	float* ptr;

	for (int row = 0; row < temp.rows; row++)
	{
		ptr = temp.ptr<float>(row);
		for (int col = 0; col < temp.cols; col++)
			ptr[col] = (float)( (c * pow(ptr[col]/255.0F, gamma)) * 255.0F);//We map it to range [0, 1] to ensure it wouldn't go over 255, then we multiply it by 255 to get it back to be in the range of [0, 255]

	}
	std::cout << "Image size:  " << img.size() << std::endl;
	//std::cout << cv::format(temp, 6) << std::endl;

	cv::imshow("Original Image", img);
	cv::Mat finalImage = cv::Mat(temp.rows, temp.cols, CV_8UC(1));

	temp.convertTo(finalImage, CV_8UC(1));

	cv::imshow("Transformed image by power law", finalImage);
	cv::namedWindow("Transformed image by power law");
	cv::moveWindow("Transformed image by power law", 100, 100);
	//cv::waitKey(1000);
	cv::destroyAllWindows();

	cv::imwrite("../bin/Section_3_2/original_aerial_img.jpg", img);
	cv::imwrite("../bin/Section_3_2/transformed_power_law_aerial_img.jpg", finalImage);

}

void image_contrast_stretching(const cv::Mat& img, char type, uchar s1, uchar s2, uchar r1, uchar r2)
{
	//c-contrast in which it the slope wouldn't be infinity
	//t-just a threshold, in which we either assign a zero or 255 based on its mean
	if (type == 'c')
	{
		float slope;
		if (r1 == r2)
		{
			cv::Mat finalImage = cv::Mat(img.rows, img.cols, CV_8UC(1));
			const uchar* ptr;
			for (int i = 0; i < img.rows; i++)
			{
				ptr = img.ptr<uchar>(i);
				for (int j = 0; j < img.cols; j++)
				{
					if (ptr[j] < r1)
						finalImage.at<uchar>(i, j) = s1;
					else
						finalImage.at<uchar>(i, j) = s2;

				}
			}
			cv::imshow("Original Image", img);
			cv::imshow("Contrasted image", finalImage);
			//cv::waitKey(1000);
			cv::destroyAllWindows();
			cv::imwrite("../bin/Section_3_2/Original_pollen_image.jpg", img);
			cv::imwrite("../bin/Section_3_2/Contrast_slope_infinity_pollen_image.jpg", finalImage);
		}
		else
		{
			//slope isn't infinity
			slope = ((s2 - s1) / (r2 - r1));
			//std::cout << "Slope: " << slope << std::endl;
			cv::Mat finalImage = cv::Mat(img.rows, img.cols, CV_8UC(1));
			const uchar* ptr;
			for (int i = 0; i < img.rows; i++)
			{
				ptr = img.ptr<uchar>(i);
				for (int j = 0; j < img.cols; j++)
				{
					if (ptr[j] <= r1)
						finalImage.at<uchar>(i, j) = ptr[j];
					else if(ptr[j] >= r2)
						finalImage.at<uchar>(i, j) = ptr[j];
					else
						finalImage.at<uchar>(i, j) = (uchar)(slope * (float) (ptr[j]  - r1));
				}
			}
			cv::imshow("Original Image", img);
			cv::imshow("Contrasted image", finalImage);
			//cv::waitKey(1000);
			cv::destroyAllWindows();
			cv::imwrite("../bin/Section_3_2/Original_pollen_image.jpg", img);
			cv::imwrite("../bin/Section_3_2/Contrast_slope_notInfinity_pollen_image.jpg", finalImage);
		}
	}
	else
	{

		float mean = calculating_mean<const uchar>(img);
		cv::Mat finalImage = cv::Mat(img.rows, img.cols, CV_8UC(1));
		const uchar* ptr;
		//Thresholding phase to obtain final image
		for (int i = 0; i < img.rows; i++)
		{
			ptr = img.ptr<uchar>(i);
			for (int j = 0; j < img.cols; j++)
			{
				if (ptr[j] < mean)
					finalImage.at<uchar>(i, j) = 0;
				else
					finalImage.at<uchar>(i, j) = 255;
			}
		}


		cv::imshow("Original Image", img);
		cv::imshow("Threshold image", finalImage);
		//cv::waitKey(1000);
		cv::destroyAllWindows();
		cv::imwrite("../bin/Section_3_2/Original_pollen_image.jpg", img);
		cv::imwrite("../bin/Section_3_2/Threshold_pollen_image.jpg", finalImage);


	}

}