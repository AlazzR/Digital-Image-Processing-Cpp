#include "main_header.h"

int main(int argc, char** argv)
{
	/*
	###########SECTION 5.2###########
	*/
	cv::Mat test = cv::imread("../test_pattern.tif", cv::IMREAD_GRAYSCALE);
	displaying_histogram(test, "Original");
	displaying_histogram(cv::imread("../test_pattern_gaussian.tif", cv::IMREAD_GRAYSCALE), "Gaussian_Noise");
	displaying_histogram(cv::imread("../test_pattern_rayleigh_noise.tif", cv::IMREAD_GRAYSCALE), "Rayleigh_Noise");
	displaying_histogram(cv::imread("../test_pattern_gamma_noise.tif", cv::IMREAD_GRAYSCALE), "Gamma_Noise");
	displaying_histogram(cv::imread("../test_pattern_neg-exp-noise.tif", cv::IMREAD_GRAYSCALE), "Exponential_Noise");
	displaying_histogram(cv::imread("../test_pattern_uniform-noise.tif", cv::IMREAD_GRAYSCALE), "Uniform_Noise");
	displaying_histogram(cv::imread("../test_pattern_salt-pepper-noise.tif", cv::IMREAD_GRAYSCALE), "Salt_and_pepper_Noise");

	/*
	###########SECTION 5.3###########
	*/
	cv::Mat circuit = cv::imread("../ckt-board_with_Gaussian_Noise.tif", cv::IMREAD_GRAYSCALE);
	arithmatic_mean(circuit, 3, 3);
	geometric_mean(circuit, 3, 3);
	harmonic_mean(circuit, 3, 3);
	
	cv::Mat circuitPepper = cv::imread("../circuit-board-pepper-prob-pt1.tif", cv::IMREAD_GRAYSCALE);
	cv::Mat circuitSalt = cv::imread("../circuit-board-salt-prob-pt1.tif", cv::IMREAD_GRAYSCALE);
	contraharmonic_mean(circuitPepper, 3, 3, 1.5, "Pepper");
	contraharmonic_mean(circuitSalt, 3, 3, -1.5, "Salt");
	cv::Mat cktSaltAndPepper = cv::imread("../ckt-board-saltpep-prob_pt05.tif", cv::IMREAD_GRAYSCALE);
	cv::Mat passes;
	passes = cktSaltAndPepper.clone();
	for(int i=1; i <= 3; i++)
		passes = median_filter(passes, 3, 3, std::to_string(i));
	
	max_filter(circuitPepper, 3, 3);
	min_filter(circuitSalt, 3, 3);
	midway_filter(circuit, 3, 3);
	adaptive_local_noise_reduction(circuit, 7, 7, 1000);
	cv::Mat HighSaltPepper = cv::imread("../ckt_saltpep_prob_pt25.tif", cv::IMREAD_GRAYSCALE);
	std::cout << "Adaptive Median Filter performance on highly corrupted image by salt and pepper noise" << std::endl;
	adaptive_median_filter(HighSaltPepper, 3, 7);
	std::cout << "Standard Median Filter performance on highly corrupted image by salt and pepper noise" << std::endl;
	cv::Mat _ = median_filter(HighSaltPepper, 7, 7, std::to_string(0));
	
	/*
	###########SECTION 5.7###########
	*/
	cv::Mat blurred_city = cv::imread("../aerial_view_turb_c_0pt0025_severe.tif", cv::IMREAD_GRAYSCALE);
	inverse_filtering(blurred_city, "Atmospheric", 70.0F, 10, 0.0025F, 0.1F, 0.1F, 1.0F, "AerialSeverelyDamaged");
	/*

	###########SECTION 5.8###########
	*/
	wiener_filtering(blurred_city, "Atmospheric",  0.0025F, 0.1F, 0.1F, 1.0F, "AerialSeverelyDamaged" + std::to_string(0), 0.3333F);
	cv::Mat moving_book = cv::imread("../least_noise_var_10minus37.tif", cv::IMREAD_GRAYSCALE);


	//Its not working, I think I am not using the corresct PSF to model the degrading function
	//inverse_filtering(moving_book, "Motion", 688.0F, 10, 0.0025F, 0.1F, 0.1F, 1.0F, "MotionImageWithLeastAmountOfNoise");
	//wiener_filtering(moving_book, "Motion", 0.0025F, 0.1F, 0.1F, 1.0F, "MotionImageWithLeastAmountOfNoise", 1);
	
	/*
	###########SECTION 5.9###########
	*/
	//cv::Mat testing = cv::Mat::zeros(10, 10, CV_8UC1);
	constrained_LS_filtering(blurred_city, 1e-5F, 0.25F, 1e-6F, "Atmospheric", 0, 1e-5F, 0.0025F, 0.1F, 0.1F, 1.0F);

	return 0;
}