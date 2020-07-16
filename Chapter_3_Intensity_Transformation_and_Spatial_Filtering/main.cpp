#include "main_header.h"

int main(int argc, char* argv[])
{
	/*
		All of the images that were used in this project and the outputs that I got from applying some of the DIP algorithms can be found in the ../bin folder. In which each section in that folder will have the images and methods of DIP that corresponds to the sections in the Digital Image Processing, 4th edition, by Rafael Gonzalez and Richard Woods.  
	*/
	
	std::cout << "Chapter 3: Intenstiy Transformation and Spatial Filtering" << std::endl;
	////////////////////////////////////////////////////S
	//Negative of an image
	////////////////////////////////////////////////////
	cv::Mat digital_mammogram = cv::imread("../digital_mammogram.tif", CV_8UC(1));
	image_negative(digital_mammogram);
	////////////////////////////////////////////////////
	//Power law
	////////////////////////////////////////////////////
	cv::Mat washedImg = cv::imread("../washed_out_aerial_image.tif", CV_8UC(1));
	image_power_law(washedImg, 1.0F, 5.0F);
	////////////////////////////////////////////////////
	////////////////////////////////////////////////////
	//1-Thresholding
	cv::Mat washedPollen = cv::imread("../washed_out_pollen_image.tif", CV_8UC(1));
	image_contrast_stretching(washedPollen, 't', 0, 255, 0, 255);//using threshold method
	//2-Contrasting by r1=r2
	uchar mean = (uchar)calculating_mean<const uchar>(washedPollen);
	image_contrast_stretching(washedPollen, 'c', 0, 255, mean, mean);//using contrast method when slope is infinity
	//3-Contrasting by r1!=r2
	double minValue, maxValue;
	cv::minMaxLoc(washedPollen, &minValue, &maxValue);
	std::cout << "Min: " << minValue << " and Max: " << maxValue << std::endl;
	image_contrast_stretching(washedPollen, 'c', 0, 255, minValue, maxValue);//using contrast method when slope is not infinity
	////////////////////////////////////////////////////
	////////////////////////////////////////////////////

	////////////////////////////////////////////////////
	//Histogram Equalization
	////////////////////////////////////////////////////
	//Darkest image
	cv::Mat darkest_pollen = cv::imread("../darkest_values_intensity_pollen.tif", CV_8UC(1));
	cv::Mat dark_values = cv::imread("../dark_values_intensity_pollen.tif", CV_8UC(1));
	cv::Mat high_values = cv::imread("../high_values_intensity_pollen.tif", CV_8UC(1));
	cv::Mat high_contrast = cv::imread("../high_contrast_intensity_pollen.tif", CV_8UC(1));

	histogram_equalization(darkest_pollen, "_darkest_pollen");
	histogram_equalization(dark_values, "_dark_pollen");
	histogram_equalization(high_values, "_high_values_pollen");
	histogram_equalization(high_contrast, "_high_contrast_pollen");
	////////////////////////////////////////////////////
	//Local Histogram processing
	////////////////////////////////////////////////////
	cv::Mat blocks_with_hidden_pixels = cv::imread("../image_enhancement_original.tif", CV_8UC(1));
	local_histogram_processing(blocks_with_hidden_pixels, 3);
	////////////////////////////////////////////////////
	//Statistical Enhancement by utilizing both local and global statistics
	////////////////////////////////////////////////////
	statistical_local_enhancement(blocks_with_hidden_pixels);
	////////////////////////////////////////////////////
	//Low pass filter
	////////////////////////////////////////////////////
	//I will not try to check the rank of the kernal nor I will try to implement separable kernal
	cv::Mat patternImg = cv::imread("../test_pattern.tif", CV_8UC(1));
	//std::cout << creating_box_filter(3) << std::endl;
	convolving_by_box_filter(patternImg, 3, "_3x3");
	convolving_by_box_filter(patternImg, 11, "_11x11");
	convolving_by_box_filter(patternImg, 21, "_21x21");

	cv::Mat _ = creating_gaussian_filter(2.0, 0.5F);
	//std::cout << std::ceil(7.000000001F * 6) << std::endl;
	convolving_by_gaussian_filter(patternImg, 2.0F, 0.5F, "_3x3");
	convolving_by_gaussian_filter(patternImg, 2.0F, 3.5F, "_21x21");
	convolving_by_gaussian_filter(patternImg, 2.0F, 7.0001F, "_43x43");
	/*
	int x[10] = { 4, 5, 6, 7, 8, -1, -2, 0, 10, 0 };	
	int n = sizeof(x) / sizeof(x[0]);
	std::vector<int> tx;
	for (int i = 0; i < n; i++)
		tx.push_back(x[i]);

	for (std::vector<int>::iterator itr = tx.begin(); itr != tx.end(); itr++)
		std::cout << *itr << std::endl;

	for (int i=0; i < n; i++)
		std::cout << tx.at(i) << std::endl;

	std::sort(tx.begin(), tx.end());
	for (int i=0; i < n; i++)
		std::cout << tx.at(i) << std::endl;

	std::sort(x, x + n);
	for(int i=0; i<n; i++)
		std::cout << x[i] << std::endl;
	*/
	////////////////////////////////////////////////////
	//Salt and pepper noise filter
	////////////////////////////////////////////////////
	cv::Mat ker = cv::Mat::zeros(3, 3, CV_8UC1);
	uchar x[10] = { 1, 0, 255, 7, 5, 101, 47, 240, 117, 102 };
	uchar* ptr;
	for (int i = 0; i < 3; i++)
	{
		ptr = ker.ptr<uchar>(i);
		for (int j = 0; j < 3; j++)
			ptr[j] = x[3 * i + j];

	}
	//std::cout << ker << std::endl;
	//std::cout << "Median value: " << (int)finding_median(ker) << std::endl;
	cv::Mat salty = cv::imread("../board_salt_and_pepper_noise.tif", CV_8UC1);
	convolving_by_saltPepper_filter(salty, 7);

	////////////////////////////////////////////////////
	//Image Sharpening 
	////////////////////////////////////////////////////
	//By the approximated 3x3 laplacian with -4 in its center 
	cv::Mat moon = cv::imread("../blurry_moon.tif", CV_8UC1);
	//cv::imshow("Blurry moon", moon);
	//cv::waitKey(1000);
	//cv::destroyAllWindows();
	//creating_simple_laplacian_1();
	//creating_simple_laplacian_2();
	convolving_with_simple_laplacian(moon, true);
	convolving_with_simple_laplacian(moon, false);

	////////////////////////////////////////////////////
	//Difference of Gaussian
	////////////////////////////////////////////////////
	cv::Mat lena = cv::imread("../lena512color.tiff", cv::IMREAD_GRAYSCALE);
	//cv::imshow("Lena", lena);
	//cv::waitKey(1000);
	//cv::destroyAllWindows();
	differnce_of_gaussian(lena, 0.5F, 1 / std::sqrt(2), std::sqrt(2));

	////////////////////////////////////////////////////
	//Laplacian applying direction on Gaussian filter
	////////////////////////////////////////////////////
	//creating_laplacian(0.5F);
	cv::Mat butterfly = cv::imread("../butterfly.jpg", cv::IMREAD_GRAYSCALE);
	//cv::imshow("Butterfly", butterfly);
	//cv::waitKey(1000);
	//cv::destroyAllWindows();
	blob_detection(butterfly, 1.5F, 1.414F, 6, 240.0F, 3, "butterfly");
	cv::Mat cleaning = cv::imread("../cleaning.jpg", cv::IMREAD_GRAYSCALE);
	blob_detection(cleaning, 1.4F, 1.414F, 6, 250.0F, 7, "cleaning");


	/* 
	//Oh how much I love dealing with vectors, screw you arrays. ;)
	std::vector<int> t;
	t.push_back(10);
	t.push_back(20)

	std::vector < std::vector<int> > t2;
	t2.push_back(t);
	for (std::vector<std::vector<int>>::iterator itr = t2.begin(); itr != t2.end(); itr++)
		for(std::vector<int>::iterator itr2 = (*itr).begin(); itr2 != (*itr).end(); itr2++)
			std::cout << *itr2 << std::endl;
	*/
	return 0;
}