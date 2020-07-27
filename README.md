# Digital-Image-Processing-Cpp

**Disclaimer:** This project doesn't truly reflect my English capabilities nor my programming capabilities. I have tried to finish these mini-projects as fast as possible, because I wanted to add the Digital Image processing folder to my resume as fast as possible in the hopes of enhancing the chances of finding job opportunities in Canada. Hence, you willn't see the best variables names and you will see some repetitions in my code, in which you might think it is possible to assign these repetitions to a function. 

This repository have my implementation of fundamental Digital Image processing (DIP) algorithms from scratch, as you can see in the folders that is provided with this repository. Unfortunately, I didn’t put great emphasis on the readability, verification and efficiency of my code, because I really wanted to finish as much as I could of these algorithms in a short time. I will try to keep implementing different algorithms relating to DIP and computer vision (CV), and these implementation will be added to this repository when I finish with them. This repository will deal only with C++11 codes due to the capabilities of C++ in dealing with computational issues that is encountered in the field of DIP and CV.

In the future, I am planning to add more projects that corresponds to different books that is related to DIP and CV to this repository. But currently this repository only include my projects of fundamental DIP algorithm that depended mainly on the DIP book. I hope you enjoy what you see in this repository and I sure hope that this repository would benefit you and uncover some of the beauty and intricateness of coding using C++. And I really enjoyed the process of creating those mini-projects and I learned a lot while implementing these mini-projects and I really advice you to implement them by yourself instead of relying on built-in libraries and the theory side, because implementing these DIP algorithm will truly create a strong foundation for the theory to rest on. Best of luck for anyone that sees this repository and I really wish to hear from you, and if you want to connect with me here is my LinkedIn account [LinkedIn Account](https://www.linkedin.com/in/rashidalazzoni/).

In this repository, I tried to dedicate a single project for each chapter in the DIP book. These projects can be found in the folders of this repository, in which the names of these folders will have the same name as the chapter of the DIP book.

--------------------------------------------------------------------------------------------------------
## Digital Image Processing By Rafael Gonzalez and Richard Woods

   * **Chapter 3: Intensity Transformation and Spatial Filtering**
       * (***Section 3.2***)Some Basic Intensity Transformation Functions
         * Image Negatives              
         * Power-Law (Gamma) Transformation
         * Piecewise Linear Transformation Functions
           * Contrast Stretching
       * (***Section 3.3***)Histogram Processing
         * Histogram Equalization
         * Local Histogram Processing
         * Using Histogram Statistics For Image Enhancement
       * (***Section 3.5***)Smoothing (Low Pass) Spatial Filters
          * Box Filter Kernels
          * Low Pass Gaussian Filter Kernels
          * Order Statistic (Non-Linear) Filters
            * Median Filter
       * (***Section 3.6***)Sharpening (High-Pass) Spatial Filters
         * Using the Second Derivative For Image Processing- The Laplacian
         * Difference of Gaussian approximation for Laplacian of Gaussian
         * Blob Detection using Laplacian of Gaussian and Non-maximum Suppression
  * **Chapter 4: Filtering in the Frequency Domain**
      * (***Section 4.6***)Some Properties of the 2 DFT and IDFT
        * Frequency Spectrum
          * Effect of Translating the Image
          * Effect of Rotating the Image
        * Phase Spectrum
          * Effect of Translating the Image
          * Effect of Rotating the Image
     * (***Section 4.8***)Image Smoothing Using Low-Pass Frequency Domain Filters
       * Ideal Low Pass Filter
       * Gaussian Low Pass Filter
       * Butterworth Low-Pass Filter
     * (***Section 4.9***)Image Sharpening Using High-Pass Filters
       * Ideal High Pass Filter
        * Gaussian High Pass Filter
        * Butterworth High-Pass Filter
        * The Laplacian in the Frequency Domain
     * (***Section 4.10***)Selective Filtering
       * Butterworth Notch Reject Filter Using Automatic Localization of Interest Points to Suppress

   * **Chapter 5: Image Restoration and Reconstruction**
     * (***Section 5.2***)Noise Models
        * Gaussian Noise 
        * Rayleigh Noise
        * Erlang (Gamma) Noise
        * Exponential Noise
        * Uniform Noise
        * Salt and Pepper Noise
     * (***Section 5.3***)Restoration in the Presence of Noise Only-Spatial Filtering
       * Arithmetic Mean Filter
       * Geometric Mean Filter
       * Harmonic Mean Filter
       * Contraharmoinc Mean Filter
       * Standard Median Filter
       * Max Filter 
       * Min Filter
       * Midpoint Filter
       * Adaptive, Local Noise Reduction Filter
       * Adaptive Median Filter
     * (***Section 5.7***)Inverse Filtering
       * Atmoshpheric point spread function
       * Mothion point spread function
     * (***Section 5.8***)Minimum Mean Square Error (Wiener) Filtering
     * (***Section 5.9***)Constrined Mean Squares Filtering
--------------------------------------------------------------------------------------------------------
**Libraries used for this Repository**
  * ***C++11***:
    * OpenCV 3.4.10
    * Eigen 3.3
  * ***CMake 3.18.0-rc1***:


