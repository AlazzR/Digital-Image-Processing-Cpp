#include "Section_3_6.h"


cv::Mat creating_simple_laplacian_1()
{
	int x[9] = { 0, 1, 0, 1, -4, 1, 0, 1, 0 };
	cv::Mat kernal = cv::Mat(3, 3, CV_32FC(1));
	float* ptr;
	for (int i = 0; i < kernal.rows; i++)
	{
		ptr = kernal.ptr<float>(i);
		for (int j = 0; j < kernal.cols; j++)
			ptr[j] = x[i * kernal.rows + j];
	}
	//std::cout << "Laplacian kernal: \n" << cv::format(kernal, 4) << std::endl;

	return kernal;
}

cv::Mat creating_simple_laplacian_2()
{
	int x[9] = { 1, 1, 1, 1, -8, 1, 1, 1, 1 };
	cv::Mat kernal = cv::Mat(3, 3, CV_32FC(1));
	float* ptr;
	for (int i = 0; i < kernal.rows; i++)
	{
		ptr = kernal.ptr<float>(i);
		for (int j = 0; j < kernal.cols; j++)
			ptr[j] = x[i * kernal.rows + j];
	}
	std::cout << "Laplacian kernal: \n" << cv::format(kernal, 4) << std::endl;

	return kernal;
}
void convolving_with_simple_laplacian(cv::Mat& img, bool flag)
{
	if (flag == true)
	{
		std::cout << img.size() << std::endl;
		auto f = [](int a, int b)->int {if (a > b) return a; else return b; };
		cv::Mat tempImg = cv::Mat::zeros(f(img.rows, img.cols), f(img.rows, img.cols), CV_8UC1);
		const uchar* ptrImg;
		uchar* ptrTemp;
		//Padding the image to make it a square matrix
		for (int i = 0; i < img.rows; i++)
		{
			ptrImg = img.ptr<uchar>(i);
			ptrTemp = tempImg.ptr<uchar>(i);
			for (int j = 0; j < img.cols; j++)
				ptrTemp[j] = ptrImg[j];
		}
		//cv::imshow("Temporary Image", tempImg);
		//cv::waitKey(2000);
		//cv::destroyAllWindows();

		int pad = 1, size = 3;
		cv::Mat laplacianImage = cv::Mat(tempImg.rows, tempImg.cols, CV_8UC1);
		cv::Mat kernal(creating_simple_laplacian_1());
		laplacianImage = convolution_kernal_rotated(tempImg, kernal, pad, pad, size, size);
		std::cout << laplacianImage.size() << std::endl;
		//std::cout << laplacianImage << std::endl;

		cv::Mat finalImage = cv::Mat::zeros(laplacianImage.rows, laplacianImage.cols, CV_8UC1);
		const uchar* ptrLaplace;
		uchar* ptrFinal;
		for (int row = 0; row < laplacianImage.rows; row++)
		{
			ptrLaplace = laplacianImage.ptr<uchar>(row);
			ptrFinal = finalImage.ptr<uchar>(row);
			ptrImg = tempImg.ptr<uchar>(row);
			for (int col = 0; col < laplacianImage.cols; col++)
				ptrFinal[col] = ptrImg[col] - ptrLaplace[col];
		}

		//Opencv will deal with the negative value conversion by using gm = g - min(g)-> gs=K((gm/max(gm))
		cv::Mat laplacianImageFinal(laplacianImage, cv::Rect(0, 0, img.cols, img.rows));
		cv::Mat finalFinalImage(finalImage, cv::Rect(0, 0, img.cols, img.rows));
		cv::imwrite("../bin/Section_3_6/Original_blurry_moon_image.jpg", img);
		cv::imwrite("../bin/Section_3_6/Simple_laplacian_type_" + std::to_string((int)flag) + "_blurry_moon_image.jpg", laplacianImageFinal);

		cv::imwrite("../bin/Section_3_6/Simple_laplacian_type_" + std::to_string((int)flag) + "_applied_on_blurry_moon_image.jpg", finalFinalImage);
		cv::imshow("Image after applying laplacian", laplacianImageFinal);
		cv::imshow("Image after subtracting the laplacian", finalFinalImage);
		//cv::waitKey(2000);
		cv::destroyAllWindows();

	}
	else
	
	{
		std::cout << img.size() << std::endl;
		auto f = [](int a, int b)->int {if (a > b) return a; else return b; };
		cv::Mat tempImg = cv::Mat::zeros(f(img.rows, img.cols), f(img.rows, img.cols), CV_8UC1);
		const uchar* ptrImg;
		uchar* ptrTemp;
		//Padding the image to make it a square matrix
		for (int i = 0; i < img.rows; i++)
		{
			ptrImg = img.ptr<uchar>(i);
			ptrTemp = tempImg.ptr<uchar>(i);
			for (int j = 0; j < img.cols; j++)
				ptrTemp[j] = ptrImg[j];
		}
		//cv::imshow("Temporary Image", tempImg);
		//cv::waitKey(2000);
		//cv::destroyAllWindows();

		int pad = 1, size = 3;
		cv::Mat laplacianImage = cv::Mat(tempImg.rows, tempImg.cols, CV_8UC1);
		cv::Mat kernal(creating_simple_laplacian_2());
		laplacianImage = convolution_kernal_rotated(tempImg, kernal, pad, pad, size, size);
		std::cout << laplacianImage.size() << std::endl;
		//std::cout << laplacianImage << std::endl;

		cv::Mat finalImage = cv::Mat::zeros(laplacianImage.rows, laplacianImage.cols, CV_8UC1);
		const uchar* ptrLaplace;
		uchar* ptrFinal;
		for (int row = 0; row < laplacianImage.rows; row++)
		{
			ptrLaplace = laplacianImage.ptr<uchar>(row);
			ptrFinal = finalImage.ptr<uchar>(row);
			ptrImg = tempImg.ptr<uchar>(row);
			for (int col = 0; col < laplacianImage.cols; col++)
				ptrFinal[col] = ptrImg[col] - ptrLaplace[col];
		}

		//Opencv will deal with the negative value conversion by using gm = g - min(g)-> gs=K((gm/max(gm))
		cv::Mat laplacianImageFinal(laplacianImage, cv::Rect(0, 0, img.cols, img.rows));
		cv::Mat finalFinalImage(finalImage, cv::Rect(0, 0, img.cols, img.rows));
		cv::imwrite("../bin/Section_3_6/Original_blurry_moon_image.jpg", img);
		cv::imwrite("../bin/Section_3_6/Simple_laplacian_type_" + std::to_string((int)flag) + "_blurry_moon_image.jpg", laplacianImageFinal);

		cv::imwrite("../bin/Section_3_6/Simple_laplacian_type_" + std::to_string((int)flag) + "_applied_on_blurry_moon_image.jpg", finalFinalImage);
		cv::imshow("Image after applying laplacian", laplacianImageFinal);
		cv::imshow("Image after subtracting the laplacian", finalFinalImage);
		//cv::waitKey(2000);
		cv::destroyAllWindows();
	}
	
}

void differnce_of_gaussian(const cv::Mat& img, float std, float k1, float k2)
{
	auto f = [](int a, int b)->int {if (a > b) return a; else return b; };
	cv::Mat tempImg = cv::Mat::zeros(f(img.rows, img.cols), f(img.rows, img.cols), CV_8UC1);
	const uchar* ptrImg;
	uchar* ptrTemp;
	//Padding the image to make it a square matrix
	for (int i = 0; i < img.rows; i++)
	{
		ptrImg = img.ptr<uchar>(i);
		ptrTemp = tempImg.ptr<uchar>(i);
		for (int j = 0; j < img.cols; j++)
			ptrTemp[j] = ptrImg[j];
	}
	//cv::imshow("Lena", tempImg);
	//cv::waitKey(1000);
	cv::Mat kernal1 = creating_gaussian_filter(1.0F / (std::sqrt(2.0F * M_PI) * (float)(k1 * std)), (float)(k1 * std));
	cv::Mat kernal2 = creating_gaussian_filter(1.0F / (std::sqrt(2.0F * M_PI) * (float)(k2 * std)), (float)(k2 * std));
	std::cout << kernal1.size() << std::endl;
	std::cout << kernal2.size() << std::endl;
	//std::cout << kernal1 << std::endl;
	//std::cout << kernal2 << std::endl;

	cv::Mat g1 = convolution_kernal_rotated(tempImg, kernal1, (int)((kernal1.rows - 1) / 2.0F), (int)((kernal1.cols - 1) / 2.0F), kernal1.rows, kernal1.cols);
	cv::Mat g2 = convolution_kernal_rotated(tempImg, kernal2, (int)((kernal2.rows - 1) / 2.0F), (int)((kernal2.cols - 1) / 2.0F), kernal2.rows, kernal2.cols);
	cv::imshow("Lena", g2);
	//cv::waitKey(1000);

	cv::Mat tempTImage = cv::Mat::zeros(tempImg.rows, tempImg.cols, CV_32SC1);//signend int
	const uchar* ptrG1;
	const uchar* ptrG2;
	signed int* ptrTempT;

	for (int i = 0; i < tempTImage.rows; i++)
	{
		ptrG1 = g1.ptr<uchar>(i);
		ptrG2 = g2.ptr<uchar>(i);
		ptrTempT = tempTImage.ptr<signed int>(i);
		for (int j = 0; j < tempTImage.cols; j++)
			ptrTempT[j] = ptrG1[j] - ptrG2[j];
	}
	cv::Mat tImage = cv::Mat(tempTImage, cv::Rect(0, 0, img.cols, img.rows));
	rescaling_intensities(tImage);
	cv::Mat finalImage = cv::Mat(tImage.rows, tImage.cols, CV_8UC1);
	tImage.convertTo(finalImage, CV_8UC1);
	cv::imshow("Origina Image", img);
	cv::imshow("DoG appplied on Image", finalImage);
	//cv::waitKey(2000);
	cv::destroyAllWindows();
	cv::imwrite("../bin/Section_3_6/Original_lena.jpg", img);
	cv::imwrite("../bin/Section_3_6/DoG_applied_on_lena.jpg", finalImage);


}

cv::Mat creating_laplacian(float std)
{
	//This will be the normalized laplacian in order to make it scale invarient
	int size = std::ceil(6 * std);
	if (size % 2 == 0)
	{
		//std::cout << "This isn't an odd size kernal and I will updated to become an odd" << std::endl;
		size = size - 1;
	}
	else
	{
		//std::cout << "Already an odd kernal" << std::endl;
	}
	cv::Mat kernal = cv::Mat::zeros(size, size, CV_32FC(1));
	//std::cout << kernal.size() << std::endl;
	std::unique_ptr<int[]> vector(new int[size]);
	int count = 0;
	//std::cout << -(int)size / 2 << std::endl;
	for (int i = -(int)size / 2; i <= (int)size / 2; i++)
	{
		vector[count] = i;
		count++;

	}
	//for (int i = 0; i < size; i++)
		//std::cout << vector[i] << "\t";

	//std::cout << std::endl;
	//std::cout << "Kernal size is eligible" << std::endl;
	//Using the equation from here http://fourier.eng.hmc.edu/e161/lectures/gradient/node8.html
	float* ptr;
	float sum = 0;
	//like meshgrid in python
	for (int row = 0; row < kernal.rows; row++)
	{
		ptr = kernal.ptr<float>(row);
		//std::cout << std::pow(vector[row], 2) << std::endl;
		for (int col = 0; col < kernal.cols; col++)
		{

			float t1 = (std::pow(vector[row], 2) + std::pow(vector[col], 2));
			float t2 = t1 - 2.0F * std::pow(std, 2);
			float t3 = std::pow(std, 4);
			float t4 = 2.0F * std::pow(std, 2);
			ptr[col] = (float)((float)(t2/t3) * std::exp((-1.0F * t1) / t4));
			sum += ptr[col];
		}
	}
	//std::cout << sum << std::endl;
	//Normalizing the kernel
	for (int row = 0; row < kernal.rows; row++)
	{
		ptr = kernal.ptr<float>(row);
		for (int col = 0; col < kernal.cols; col++)
		{
			ptr[col] = ptr[col] / sum;
		}
	}

	cv::Mat temp = cv::Mat::zeros(kernal.rows, kernal.cols, CV_8UC1);
	kernal.convertTo(temp, CV_8UC1);
	//std::cout << cv::format(temp, 4) << std::endl;
	std::cout << "Kernel size: " << kernal.size() << std::endl;
	//std::cout << "Kernel shape\n" << cv::format(kernal, 4) << std::endl;

	//cv::imwrite("../bin/Section_3_5/Gaussian" + std::to_string(std) + "_" + std::to_string(std) + ".jpg", temp);
	return kernal;

	/*catch (char* c)
	{
		std::cout << c << std::endl;
		exit(0);
	}*/


}
cv::Mat non_maximum_suppression(const std::vector<cv::Mat>& pyramid, const float* sigmas, float threshold, int size, int depth)
{
	for(int i=0; i < depth; i++)
		std::cout << "Size of image at pyramid level: " << i << " : "<<  pyramid[i].size() << " With sigma: "<< sigmas[i]<< std::endl;
	//cv::waitKey(10000);
	cv::Mat finalImage = cv::Mat::zeros(pyramid[0].rows, pyramid[0].cols, CV_32FC(1));
	float* ptr;
	int pad = std::floor( size / 2);
	//non-overlapping windows
	for (int row = pad; row < pyramid[0].rows - pad; row+=size)
	{
		for (int col = pad; col < pyramid[0].cols - pad; col+=size)
		{
			std::vector<cv::Mat> windows;
			for (int d = 0; d < depth; d++)
			{
				//cv::Mat temp = pyramid[d], cv::Rect(row, col, size, size));
				//std::cout << temp << std::endl;
				windows.push_back(cv::Mat(pyramid[d], cv::Rect(row - pad, col - pad, size, size)));
			}
			int posDepth=0;
			int posX=0;
			int posY=0;
			uchar value= (windows[posDepth].ptr<uchar>(posX))[posY];
			//std::cout << value << std::endl;
			//std::cout << row << " : " << col << std::endl;
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					for (int dd = 0; dd < depth; dd++)
					{
						const cv::Mat init = windows[dd];
						if (value <= (init.ptr<uchar>(i))[j])
						{
							value = (init.ptr<uchar>(i))[j];
							posX = i;
							posY = j;
							posDepth = dd;
						}
					}
				}
			}
			if (value >= threshold)
			{
				ptr = finalImage.ptr<float>(row + posX - pad);//This will be the position of the interest points
				ptr[posY + col - pad] = std::sqrt(2.0F) * sigmas[posDepth];//Radius of the circle
			}
		}
	}
	return finalImage;
}
void blob_detection(cv::Mat& img, float std, float increment, int depth, float threshold, int winSize, std::string name)
{
	std::cout << "Size of Image: " << img.size() << std::endl;
	auto f = [](int a, int b)->int {if (a > b) return a; else return b; };
	cv::Mat paddedImage = cv::Mat::zeros(f(img.rows, img.cols), f(img.rows, img.cols), CV_8UC1);
	const uchar* ptrImg;
	uchar* ptrPad;
	//Padding the image to make it a square matrix
	for (int i = 0; i < img.rows; i++)
	{
		ptrImg = img.ptr<uchar>(i);
		ptrPad = paddedImage.ptr<uchar>(i);
		for (int j = 0; j < img.cols; j++)
			ptrPad[j] = ptrImg[j];
	}
	std::vector<cv::Mat> pyramid;
	std::vector<cv::Mat> pyramidT;
	pyramid.reserve(depth);
	pyramidT.reserve(depth);
	float* sigmas;
	sigmas = new float[depth];
	for (int i = 0; i < depth; i++)
	{
		if (pyramid.capacity() - pyramid.size() == 0)
		{
			std::cout << "We reached the vertex of the pyramid: " << i << std::endl;
			break;
		}
		sigmas[i] = std::pow(increment, i) * (std);
		cv::Mat kernal = creating_laplacian(sigmas[i]);//i*increment*std
		cv::Mat convolvedImage = convolution_kernal_rotated(paddedImage, kernal, (int)((kernal.rows - 1) / 2.0F), (int)((kernal.cols - 1) / 2.0F), kernal.rows, kernal.cols);
		//convolvedImage = convolvedImage.t();
		cv::Mat pad = cv::Mat::zeros(convolvedImage.rows + 2*std::floor(winSize / 2), convolvedImage.cols + 2*std::floor(winSize / 2), CV_8UC1);
		const uchar* ptr1;
		uchar* ptr2;
		for (int i = 0; i < convolvedImage.rows; i++)
		{
			ptr1 = convolvedImage.ptr<uchar>(i);
			ptr2 = pad.ptr<uchar>(i + std::floor(winSize / 2));
			for (int j = 0; j < convolvedImage.cols; j++)
				ptr2[j +(int)std::floor(winSize / 2)] = ptr1[j];
		}


		pyramid.push_back(pad);
		cv::Mat finalImage(convolvedImage, cv::Rect(0, 0, img.cols, img.rows));
		pyramidT.push_back(finalImage);

	}
	int count = 0;
	for (std::vector<cv::Mat>::iterator itr = pyramidT.begin(); itr != pyramidT.end(); itr++)
	{
		cv::imshow("Applied Laplacian of Gaussian on Image", *itr);
		//cv::waitKey(2000);
		cv::imwrite("../bin/Section_3_6/temp/LoG_applied_on_" + name + "_" + std::to_string(count) + ".jpg", *itr);
		count++;
	}
	cv::Mat interestPoints = cv::Mat((non_maximum_suppression(pyramid, sigmas, threshold, winSize, depth)).t(), cv::Rect(std::floor(winSize / 2), std::floor(winSize / 2), paddedImage.cols, paddedImage.rows));
	cv::Mat finalImage = cv::Mat::zeros(interestPoints.rows, interestPoints.cols, CV_8UC1);
	uchar* ptrFinal;
	const float* ptrInt;
	for (int i = 0; i < finalImage.rows; i++)
	{
		ptrFinal = finalImage.ptr<uchar>(i);
		ptrInt = interestPoints.ptr<float>(i);

		for (int j = 0; j < finalImage.cols; j++)
		{
			if (ptrInt[j] != 0.0F)
				ptrFinal[j] = (uchar)255;
		}
	}
	cv::imshow("Origina Image", img);
	cv::imwrite("../bin/Section_3_6/Original_" + name + "_.jpg", img);
	cv::imshow("Interest Points Image", cv::Mat(finalImage, cv::Rect(0, 0, img.cols, img.rows)));
	cv::imwrite("../bin/Section_3_6/Interest_points_" + name + "_" + ".jpg", cv::Mat(finalImage, cv::Rect(0, 0, img.cols, img.rows)));
	//cv::waitKey(1000);
	cv::destroyAllWindows();
	delete[] sigmas;

	cv::Mat imageWithCircles = cv::Mat::zeros(paddedImage.rows, paddedImage.cols, CV_8UC3);

	cv::cvtColor(paddedImage, imageWithCircles, CV_GRAY2BGR);
	
	const float* ptrIntrest;
	for (int i = 0; i < interestPoints.rows; i++)
	{
		ptrIntrest = interestPoints.ptr<float>(i);
		for (int j = 0; j < interestPoints.cols; j++)
		{
			if (ptrIntrest[j] != 0.0F)
			{
				cv::Point p(j, i);
				//std::cout << ptrIntrest[j] << std::endl;
				cv::circle(imageWithCircles, p, ptrIntrest[j], cv::Scalar(0, 0, 255));
			}

		}
	}
	cv::imshow("3 Channel Image", cv::Mat(imageWithCircles, cv::Rect(0, 0, img.cols, img.rows)));
	cv::imwrite("../bin/Section_3_6/"+name + "_" + "_with_blob_detection.jpg", cv::Mat(imageWithCircles, cv::Rect(0, 0, img.cols, img.rows)));
	//cv::waitKey(1000);
	cv::destroyAllWindows();
	{
		const cv::Mat img = cv::imread("../lena512color.tiff", cv::IMREAD_GRAYSCALE);
		auto f = [](int a, int b)->int {if (a > b) return a; else return b; };
		cv::Mat paddedImage = cv::Mat::zeros(f(img.rows, img.cols), f(img.rows, img.cols), CV_8UC1);
		const uchar* ptrImg;
		uchar* ptrPad;
		//Padding the image to make it a square matrix
		for (int i = 0; i < img.rows; i++)
		{
			ptrImg = img.ptr<uchar>(i);
			ptrPad = paddedImage.ptr<uchar>(i);
			for (int j = 0; j < img.cols; j++)
				ptrPad[j] = ptrImg[j];
		}
		cv::Mat kernal = creating_laplacian(std);
		cv::Mat convolvedImage = convolution_kernal_rotated(paddedImage, kernal, (int)((kernal.rows - 1) / 2.0F), (int)((kernal.cols - 1) / 2.0F), kernal.rows, kernal.cols);
		cv::Mat lenaTemp = cv::Mat::zeros(convolvedImage.rows, convolvedImage.cols, CV_32FC1);
		const uchar* ptrConv;
		float* ptrLena;
		const float* ptrKernal;
		ptrKernal = kernal.ptr<float>((int)(kernal.rows / 2));
		float value = ptrKernal[(int)(kernal.cols / 2)];
		std::cout << value << std::endl;
		auto f1 = [](float a) {if (a > 0) return 1; else return -1; };
		for (int i = 0; i < paddedImage.rows; i++)
		{
			ptrImg = paddedImage.ptr<uchar>(i);
			ptrConv = convolvedImage.ptr<uchar>(i);
			ptrLena = lenaTemp.ptr<float>(i);
			for (int j = 0; j < paddedImage.cols; j++)
				ptrLena[j] = ptrImg[j] + f1(value) * ptrConv[j];
		}
		cv::Mat tImage = cv::Mat(lenaTemp, cv::Rect(0, 0, img.cols, img.rows));
		rescaling_intensities(tImage);
		cv::Mat finalImage = cv::Mat(tImage.rows, tImage.cols, CV_8UC1);
		tImage.convertTo(finalImage, CV_8UC1);
		cv::imwrite("../bin/Section_3_6/LoG_substracted_from_lena.jpg", finalImage);
	}
}
