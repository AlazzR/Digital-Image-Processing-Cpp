#include "Section_5_9_H_.h"

void constrained_LS_filtering(const cv::Mat& img, float gamma, float alpha, float correction_factor, std::string type, float meanN, float varN, float k, float a, float b, float T)
{
	cv::Mat pad = cv::Mat::zeros(img.rows, img.cols, CV_8UC1);;
	auto f = [](const cv::Mat& img, cv::Mat& pad)->void
	{
		const uchar* ptrImg;
		uchar* ptr;
		for (int i = 0; i < pad.rows; i++)
		{
			ptrImg = img.ptr<uchar>(i);
			ptr = pad.ptr<uchar>(i);
			for (int j = 0; j < pad.cols; j++)
				ptr[j] = ptrImg[j];
		}
	};
	//Making the image of even dimension
	if (img.rows % 2 != 0)
	{
		if (img.cols % 2 != 0)
		{
			pad = cv::Mat(img.rows - 1, img.cols - 1, CV_8UC1);
			f(img, pad);
		}
		else
		{
			pad = cv::Mat(img.rows - 1, img.cols, CV_8UC1);
			f(img, pad);
		}
	}
	else
		f(img, pad);

	//std::cout << "pad: \n" << cv::format(pad, 6) << std::endl;

	cv::Mat P = cv::Mat::zeros(4, 4, CV_32FC1);//To keep the even symmetry

	P.at<float>(2, 2) = 4.0F;
	P.at<float>(2, 1) = -1.0F;
	P.at<float>(1, 2) = -1.0F;
	P.at<float>(2, 3) = -1.0F;
	P.at<float>(3, 2) = -1.0F;
	//std::cout << "P: \n" << cv::format(P, 6) << std::endl;
	cv::Mat Ppadded = cv::Mat::zeros(pad.rows, pad.cols, CV_32FC1);
	float* ptrP;
	float* ptrPpadded;
	int posX = 0;
	for (int i = Ppadded.rows/2 - 2 ; i < Ppadded.rows/2 + 2; i++)
	{
		ptrP = P.ptr<float>(posX);
		ptrPpadded = Ppadded.ptr<float>(i);
		int posY = 0;
		for (int j = Ppadded.cols / 2 - 2; j < Ppadded.cols / 2 + 2; j++)
		{
			ptrPpadded[j] = ptrP[posY];
			posY++;
		}
		posX++;
	}
	//std::cout << "Ppadded: \n" << cv::format(Ppadded, 6) << std::endl;

	cv::Mat complexSmoothing[2] = { Ppadded, cv::Mat::zeros(Ppadded.rows, Ppadded.cols, CV_32FC1) };
	cv::Mat dftImg;
	cv::merge(complexSmoothing, 2, dftImg);
	cv::dft(dftImg, dftImg);
	cv::split(dftImg, complexSmoothing);

	cv::Mat kernel;
	if (type == "Atmospheric")
		kernel = creating_H_atmospheric(k, pad.rows, pad.cols);
	else
		kernel = creating_H_motion(a, b, T, pad.rows, pad.cols);
	
	cv::Mat complexKernel[2];
	cv::split(kernel, complexKernel);
	cv::multiply(complexKernel[1], cv::Scalar::all(-1.0F), complexKernel[1]);//Getting the conjugate
	
	cv::Mat magK; cv::Mat magP;
	cv::magnitude(complexKernel[0], complexKernel[1], magK);
	cv::magnitude(complexSmoothing[0], complexSmoothing[1], magP);
	cv::magnitude(magK, magK, magK);
	cv::magnitude(magP, magP, magP);

	cv::Mat padT = pad.clone();
	padT.convertTo(padT, CV_32FC1);
	centering_image(padT);
	cv::Mat complexG[2] = { padT, cv::Mat::zeros(padT.rows, padT.cols, CV_32FC1)};
	cv::Mat complexF[2] = { cv::Mat::zeros(padT.rows, padT.cols, CV_32FC1), cv::Mat::zeros(padT.rows, padT.cols, CV_32FC1) };

	cv::merge(complexG, 2, dftImg);
	cv::dft(dftImg, dftImg);
	cv::split(dftImg, complexG);

	cv::Mat R = cv::Mat::zeros(complexG[0].rows, complexG[0].cols, CV_32FC2);
	cv::Mat temp[2];
	cv::Mat tempH[2];
	bool flag = true;
	cv::Mat complexGT[2] = { complexG[0].clone(), complexG[1].clone() };
	cv::merge(complexGT, 2, dftImg);
	cv::dft(dftImg, dftImg, cv::DFT_REAL_OUTPUT | cv::DFT_INVERSE | cv::DFT_SCALE);
	cv::Mat Ginv = dftImg;
	centering_image(Ginv);
	cv::Mat finalImage = cv::Mat(padT.rows, padT.cols, CV_32FC1);
	int count = 0;
	while (flag)
	{
		cv::multiply(magP, cv::Scalar::all(gamma), temp[0]);
		cv::add(temp[0], magK, temp[1]);
		cv::divide(complexKernel[0], temp[1], tempH[0]);
		cv::divide(complexKernel[1], temp[1], tempH[1]);
		cv::multiply(tempH[0], complexG[0], complexF[0]);
		cv::multiply(tempH[1], complexG[1], complexF[1]);
		cv::Mat r1; 
		cv::Mat r2;
		cv::subtract(complexG[0], complexF[0], r1);
		cv::subtract(complexG[1], complexF[1], r2);

		cv::Mat t[2] = { r1, r2 };
		cv::merge(t, 2, R);

		cv::dft(R, R, cv::DFT_REAL_OUTPUT | cv::DFT_INVERSE | cv::DFT_SCALE);
		centering_image(R);


		cv::Mat r = R.reshape(R.rows * R.cols, 1);
		float norm_r = (float)cv::norm(r, cv::NORM_L2);
		float norm_n = (float)R.rows * (float)R.cols * (varN + std::pow(meanN, 2));

		if (norm_r == norm_n)
		{
			std::cout << "Reached the optimal representation of the de-noised image" << std::endl;
			flag = false;
			break;
		}
		if (norm_r < norm_n - alpha)
			gamma += correction_factor;
		else
			gamma -= correction_factor;
		if (count % 100 == 0)
		{
			std::cout << "Pass number: " << count << " Gamma was updated to " << gamma << " norm_r= " << norm_r << " ,norm_n= " << norm_n << std::endl;
			cv::merge(complexF, 2, dftImg);
			cv::dft(dftImg, dftImg, cv::DFT_REAL_OUTPUT | cv::DFT_INVERSE | cv::DFT_SCALE);
			finalImage = dftImg.clone();
			centering_image(finalImage);
			finalImage.convertTo(finalImage, CV_8UC1);
			cv::imwrite("../bin/Section_5_9/" + std::to_string(count) + "_Image_with_even_coordinate_" + type + "_noise_After_constrained_LS.jpg", finalImage);

		}
		count++;
	}

	cv::merge(complexF, 2, dftImg);
	cv::dft(dftImg, dftImg, cv::DFT_REAL_OUTPUT | cv::DFT_INVERSE | cv::DFT_SCALE);
	finalImage = dftImg.clone();
	centering_image(finalImage);
	finalImage.convertTo(finalImage, CV_8UC1);
	cv::imwrite("../bin/Section_5_9/1_Original_image_with_even_coordinate" + type + "_noise_constrained_LS.jpg", pad);
	cv::imwrite("../bin/Section_5_9/2_FINAL_Image_with_even_coordinate_" + type + "_noise_After_constrained_LS.jpg", finalImage);
}