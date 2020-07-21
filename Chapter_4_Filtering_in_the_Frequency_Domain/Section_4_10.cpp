#include "Section_4_10_H_.h"
coordinate::coordinate(int x, int y)
{
	this->x = (x >= 0) ? x : 0;
	this->y = (y >= 0) ? y : 0;
}

int coordinate::getX() const
{
	return this->x;
}

int coordinate::getY() const
{
	return this->y;
}

bool customCompare::operator()(const coordinate& lhs, const coordinate& rhs) const
{
	if ((lhs.getX() == rhs.getX()) && (lhs.getY() == rhs.getY()))
	{
		return true;
	}
	else
		return false;
}

size_t customHashing::operator()(const coordinate& obj)const
{
	return std::hash<int>()(obj.getX()) ^ std::hash<int>()(obj.getY());//The hash value of x XORed with hash value of y to be stored in the bucket
}

std::unordered_set<coordinate, customHashing, customCompare>  find_loc_to_suppress(cv::Mat & img, int width)
{
	//Padding the image will increase the significant strength of along the vertical and horizontal axes of the spectrum, hence, if you don't want to pad you need to play around with the accepted intensity values.
	//When image is padded in it will darken the transformed image. See problem 4.42
	cv::Mat pad = cv::Mat(img.rows * 2, img.cols * 2, CV_32FC1, cv::Scalar(0.0F));
	std::unordered_set<coordinate, customHashing, customCompare>  locationLocation;

	for (int i = 0; i < img.rows; i++)
		for (int j = 0; j < img.cols; j++)
			pad.at<float>(i, j) = img.at<uchar>(i, j);

	cv::Mat temp(pad.clone());
	centering_image(temp, CV_32FC1);
	cv::Mat complex[2] = { temp, cv::Mat::zeros(pad.rows, pad.cols, CV_32FC1) };
	cv::Mat dftImage;
	cv::merge(complex, 2, dftImage);
	cv::dft(dftImage, dftImage);

	img = dftImage.clone(); //In order to get the transformed image

	cv::split(dftImage, complex);

	cv::Mat mag = cv::Mat::zeros(complex[0].size(), CV_32FC1);
	cv::magnitude(complex[0], complex[1], mag);
	//Enhancing the figure
	float* ptr;
	for (int i = 0; i < mag.rows; i++)
	{
		ptr = mag.ptr<float>(i);
		for (int j = 0; j < mag.cols; j++)
			ptr[j] = std::log10(ptr[j] + 1);
	}

	std::cout << "Image size for the " << "Notch reject Filter: " << img.size() << std::endl;
	cv::normalize(mag, mag, 0.0F, 255.0F, CV_MINMAX);
	//std::cout << mag.at<float>(mag.rows / 2, mag.cols / 2) << std::endl;
	mag.convertTo(mag, CV_8UC1);
	//std::cout << mag << std::endl;
	//Finding the location of these peak frequencies

	cv::Mat colored[3] = { mag, mag, mag };
	cv::Mat complete;
	cv::merge(colored, 3, complete);
	cv::Mat interest_points = cv::Mat::zeros(mag.rows, mag.cols, CV_8UC1);

	uchar* ptrComplete;
	uchar* ptrRed;
	cv::Mat magTemp = mag.clone();

	for (int i = 0; i < mag.rows; i++)
	{
		ptrComplete = magTemp.ptr<uchar>(i);
		ptrRed = interest_points.ptr<uchar>(i);

		for (int j = 0; j < mag.cols; j++)
			if ((ptrComplete[j] >= 160) && (ptrComplete[j] <= 255))
			{
				ptrRed[j] = 255;
				if ((i == (mag.rows / 2)) || (j == (mag.cols / 2)) || ((i >= (mag.rows / 2 - 50)) && (i <= (mag.rows / 2 + 50))) || ((j >= (mag.cols / 2 - 50)) && (j <= (mag.cols / 2 + 50))))
				{
					ptrComplete[j] = 0;
				}//suppress uninteresting points
				else
				{
						int posX = 0;
						int posY = 0;
						int count = 0;
						
						cv::Mat temp = cv::Mat(magTemp, cv::Rect((int)(j - width), (int)(i - width), 2 * width, 2 * width));
						for(int t1 =0; t1 < 2 * width; t1++)
							for (int t2 = 0; t2 < 2 * width; t2++)
							{
								if ((temp.at<uchar>(t1, t2)>= 160) && (temp.at<uchar>(t1, t2) <= 255))
								{
									posX += i - width + t1;
									posY += j - width + t2;
									count += 1;
								}
							}
						posX = (int)(posX / count);
						posY = (int)(posY / count);
						std::vector<int> positions;
						locationLocation.insert(coordinate(posY, posX));
						cv::Point p(posY, posX);
						cv::circle(complete, p, 2.5, cv::Scalar(0, 0, 255));
				}
			}
	}
	/*
	for (std::vector<std::vector<int>>::iterator itr = locationLocation.begin(); itr != locationLocation.end(); itr++)
	{
		for (std::vector<int>::iterator itr2 = itr->begin(); itr2 != itr->end(); itr2++)
			std::cout << *itr2 << "\t";
		std::cout << std::endl;
	}
	*/
	//cv::add(colored[0], interest_points, colored[0]);
	for (std::unordered_set<coordinate, customHashing, customCompare>::iterator itr = locationLocation.begin(); itr != locationLocation.end(); itr++)
		std::cout << "Coordinate of interest point: " <<itr->getX() << ":" << itr->getY() << std::endl;

	cv::imshow("Colored Image", complete);
	cv::waitKey(1000);
	cv::destroyAllWindows();
	cv::imwrite("../bin/Section_4_10/Magnitude_car_Moire.jpg", mag);
	cv::imwrite("../bin/Section_4_10/Magnitude_car_Moire_with_circles.jpg", complete);
	
	return locationLocation;
}
cv::Mat creating_notch(int P, int Q, float D0, int uk, int vk, int n)
{
	cv::Mat notch = cv::Mat::zeros(P, Q, CV_32FC1);
	float* ptrNotch;
	for (int i = 0; i < notch.rows; i++)
	{
		ptrNotch = notch.ptr<float>(i);
		for (int j = 0; j < notch.cols; j++)
		{
			float t1 = std::sqrt(std::pow(i - P/2- uk, 2) + std::pow(j - Q/2 - vk, 2));
			ptrNotch[j] = 1.0F / (1.0F + std::pow(D0 / t1, n));
		}
	}

	return notch;
}

void filtering_by_notch(const cv::Mat& img, float D0, int n)
{
	cv::Mat tempPad= img.clone();
	std::unordered_set<coordinate, customHashing, customCompare> location = find_loc_to_suppress(tempPad, 40);//passed by reference, tempPad will be the DFT version of the image
	int P = tempPad.rows;
	int Q = tempPad.cols;
	std::cout << "Padded Image size: " << tempPad.size() << std::endl;
	cv::Mat notchFilter = cv::Mat::ones(tempPad.size(), CV_32FC1);

	for (std::unordered_set<coordinate, customHashing, customCompare>::iterator itr1 = location.begin(); itr1 != location.end(); itr1++)
	{
		cv::multiply(creating_notch(P, Q, D0, itr1->getY()  + P/2, itr1->getX() + Q/2, n), notchFilter, notchFilter);
		cv::multiply(creating_notch(P, Q, D0, -1 * itr1->getY() + P/2, -1 * itr1->getX() + Q/2, n), notchFilter, notchFilter);
	}
	cv::Mat complex[2];
	cv::split(tempPad, complex);
	cv::multiply(complex[0], notchFilter, complex[0]);
	cv::multiply(complex[1], notchFilter, complex[1]);
	cv::Mat mag;
	cv::magnitude(complex[0], complex[1], mag);
	float* ptr;
	for (int i = 0; i < mag.rows; i++)
	{
		ptr = mag.ptr<float>(i);
		for (int j = 0; j < mag.cols; j++)
			ptr[j] = std::log10(ptr[j] + 1);
	}
	cv::normalize(mag, mag, 0.0F, 255.0F, CV_MINMAX);
	mag.convertTo(mag, CV_8UC1);
	cv::normalize(notchFilter, notchFilter, 0.0F, 255.0F, CV_MINMAX);
	notchFilter.convertTo(notchFilter, CV_8UC1);

	cv::imwrite("../bin/Section_4_10/Magnitude_car_Moire_After_notch_filter.jpg", mag);
	cv::imwrite("../bin/Section_4_10/notch_" + std::to_string(n) + ".jpg", notchFilter);

	cv::Mat dftImage;
	cv::merge(complex, 2, dftImage);
	cv::dft(dftImage, dftImage, cv::DFT_INVERSE | cv::DFT_SCALE | cv::DFT_REAL_OUTPUT);
	rescaling_intensities(dftImage);
	cv::Mat finalImage(dftImage, cv::Rect(0, 0, img.cols, img.rows));
	rescaling_intensities(finalImage);
	finalImage.convertTo(finalImage, CV_8UC1);
	cv::imwrite("../bin/Section_4_10/Car_Moire_After_notch_filtering_" + std::to_string(n) +".jpg", finalImage);

}
