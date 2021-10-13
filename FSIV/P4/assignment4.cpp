/****************************************
 * Autor: Francisco Javier Perez Castillo
 * Universidad de Córdoba (Spain)
 * 
 * Magnitude of Derivative:
 *  Write a prgram that reads an image from file, converts it to gray scale and computes the 
 *  magnitude of the derivative using the Sobel filter. You have to use your own implementation 
 *  of applyKernel, based on the one you did for the previous assigment.
 *  
 *  In order to avoid overflow problems, you will convert the input grey scale image into a 
 *  floating point image and will do the convolution. In this case, both the image and the 
 *  kernel will be floating point pixels.
 *  
 *  The resulting magnitude image, will need to be transformed into a grey scale image. 
 *  You will have to scale the magnitude into a [0,255] uchar image. 
 *
 *  You can use the following opencv functions:
 *
 *  cv::Mat::convertTo, cv::minMaxLoc,cv::normalize
 * 
 * **************************************/

/*
 * Documentation:
    - converTo() : https://docs.opencv.org/4.5.3/d3/d63/classcv_1_1Mat.html#adf88c60c5b4980e05bb556080916978b
    - normalize(): https://docs.opencv.org/4.5.3/d2/de8/group__core__array.html#ga87eef7ee3970f86906d69a92cbf064bd
*/


#include <opencv2/core/core.hpp> //core routines
#include <opencv2/highgui/highgui.hpp>//imread,imshow,namedWindow,waitKey
#include <iostream>

using namespace std;
using namespace cv;


void magnitude(const cv::Mat &derivativeX, const cv::Mat &derivativeY, cv::Mat &magnitude) {

    //We go around the image
    for(int x=0 ; x<magnitude.rows; x++){
        for(int y=0 ; y<magnitude.cols; y++){
            //We take both value of the derivatives at the same X,Y coords
            int valX = derivativeX.at<float>(x,y);
            int valY = derivativeY.at<float>(x,y); 
            //The value of the ecuation will be the value of our magnitude image
            magnitude.at<float>(x,y) = sqrt(pow(valX, 2)+pow(valY, 2));
        }
    }

}


void applyKernel(const Mat &in, Mat &out, const Mat &kernel){
    //We check if the kernel is kernel is correct in terms of size
    
    if(kernel.cols <=1){
        cout << "Error, your kernel size is wrong" << endl;
        return;
    }

    //We calculate the radius of the kernel
    int size = kernel.cols;
    int kernel_radio = kernel.cols/2;

    for(int x=0 ; x<in.rows ; x++){ //Where x and y are the position of the image's pixels
        for(int y=0 ; y<in.cols ; y++){
            //Now we are on the pixel where we apply the kernel           
            float sum_val= 0.0;
            //We go around the kernel
            for(int kx=((size*(-1))+(size/2))+1; kx<size-(size/2); kx++) {
                for(int ky=((size*(-1))+(size/2))+1; ky<size-(size/2); ky++){	
                    if((kx+x < 0) || (ky+y < 0) || (kx+x >= in.rows) || (ky+y >= in.cols)){
                        sum_val = sum_val + 0;
                    } else {
                        sum_val = sum_val + (in.at<float>(x+kx, y+ky) * kernel.at<float>(kx+kernel_radio,ky+kernel_radio));
                    }
                }
            }
            //Once we have the "mean" of the value around the pixel, we can change the value in our aux image
            out.at<float>(x,y) = sum_val;
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
    Mat img = imread(argv[1], IMREAD_GRAYSCALE);
   
    if(img.rows == 0){
        cerr << "Error, your image is empty or you wrote image's name wrongly" << endl;
        return 0;
    }

    Mat user_image;
    img.convertTo(user_image, CV_32FC1);

    //We create different images to calculate the derivatives and the magnitude.
    Mat kernelX_result = user_image.clone();
    Mat kernelY_result = user_image.clone();
    Mat magnitude_image = user_image.clone();


    //We create the matrix that will have the values of our kernels
    float sobel_x[] = { -1, 0, 1,
                        -2, 0, 2,       
                        -1, 0, 1  };

    float sobel_y[] = {  1,  2,  1,
                         0,  0,  0,       
                        -1, -2, -1  };
    //Creation of the kernels
    Mat sobel_kernelX(3, 3, CV_32FC1, sobel_x);
    Mat sobel_kernelY(3, 3, CV_32FC1, sobel_y);

    //We apply this kernels to our image with the applyKernel method
    applyKernel(user_image, kernelX_result, sobel_kernelX);
    applyKernel(user_image, kernelY_result, sobel_kernelY);

    //We calculate the magnitude values for our final image
    magnitude(kernelX_result, kernelY_result, magnitude_image);

    //We have to normalize the value of the image
    Mat normalized_image = magnitude_image.clone();
    normalize(magnitude_image, normalized_image, 100, NORM_MINMAX);


    //We show the original image and the result
    namedWindow("Original image");
    imshow("Original image", img);

    namedWindow("Modified image");
    imshow("Modified image", normalized_image);
    
    waitKey(0);

} catch (exception &ex) {
    cout<<ex.what()<<endl;
}

}