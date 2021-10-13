/****************************************
 * Autor: Francisco Javier Perez Castillo
 * Universidad de Córdoba (Spain)
 * 
 * NxN Box filter:
 *  Implement a NxN box filter for an image (where N is odd)
 *  Make a program that reads an image in grey scale, apply a box filter and save the result. 
 *  To make it modular, create a function
 *  
 *  void applyKernel(const cv::Mat &in,cv::Mat &out,const cv::Mat &kernel);
 *  
 *  that applies any kernel NxN to the image.
 *  
 *  The kernel image must be a floating point image with a single channel, e.g., 
 *  cv::Mat kernel(3,3,CV_32FC1);
 * 
 * **************************************/

/*
 * Documentation:
    - ones() : https://docs.opencv.org/4.5.3/d3/d63/classcv_1_1Mat.html#a69ae0402d116fc9c71908d8508dc2f09
*/

#include <opencv2/core/core.hpp> //core routines
#include <opencv2/highgui/highgui.hpp>//imread,imshow,namedWindow,waitKey
#include <iostream>

using namespace std;
using namespace cv;


void applyKernel(const Mat &in, Mat &out, const Mat &kernel){
    //We check if the kernel is kernel is correct in terms of size
    if(kernel.cols <=1){
        cout << "Error, your kernel size is wrong" << endl;
        return;
    }

    //We calculate the radius of the kernel
    int kernel_radius = kernel.cols / 2;  

    for(int x=0 ; x<in.rows ; x++){ //Where x and y are the position of the image's pixels
        for(int y=0 ; y<in.cols ; y++){
            //Now we are on the pixel where we apply the kernel           
            float sum_val= 0.0;
            //We go around the kernel
            for(int i=kernel_radius ; i<kernel.rows+kernel_radius ; i++){ //Where i and j are the position of the kernel's pixels
                for(int j=kernel_radius ; j<kernel.rows+kernel_radius ; j++){
                    //We start at the middle of the kernel
                    //We only do the mean if we take pixels values that are in our image
                   if( (x-i+kernel_radius>=0) && (y-j+kernel_radius>=0) && (x-i+kernel_radius<=in.rows) && (y-j+kernel_radius<=in.cols) ){     
                        sum_val = sum_val + (in.at<uchar>(x+i-kernel_radius,y+j-kernel_radius) * kernel.at<float>(i-kernel_radius,j-kernel_radius));
                   } 
                }
            }
            //Once we have the "mean" of the value around the pixel, we can change the value in our aux image
            out.at<uchar>(x,y) = sum_val;
        }
    }
}

int main(int argc,char **argv){
try {
    //We check that user introduce only one image
    if(argc!=2){
        cerr<<"Error, you have to insert an image as an argument"<<endl;
        return 0;
    }

    //We save the image in a variable in grey scale
    Mat user_image = imread(argv[1], IMREAD_GRAYSCALE);
    Mat aux_image = user_image.clone();

    if(user_image.rows == 0){
        cerr << "Error, your image is empty or you wrote image's name wrongly" << endl;
        return 0;
    }

    int N; //Size of the kernel
    cout << "Introduce the size of the kernel. It must be an odd number: "; 
    cin >> N;

    if(N%2==0){
        cout <<"Error, the size of the kernel must be an odd number" << endl;
        return 0;
    }

    //We create a new "image" that will be the kernel that we will applye
    Mat NxN_kernel(N,N, CV_32FC1); //NxN image with 32 bits float and one channel
    //Now, we modify the kernel and we fill it with 1 values
    NxN_kernel=Mat::ones(N, N, CV_32FC1)/(N*N); //Filled the NxN images with 1 values in every pixel divided by the total number

    //We apply the NxN Kernel to our aux_image
    applyKernel(user_image, aux_image, NxN_kernel);
    
    //We show the original image and the result
    namedWindow("Original image");
    imshow("Original image", user_image);

    namedWindow("Modified image");
    imshow("Modified image", aux_image);
    
    waitKey(0);
} catch (exception &ex) {
    cout<<ex.what()<<endl;
}

}