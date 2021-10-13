/****************************************
 * Autor: Francisco Javier Perez Castillo
 * Universidad de Córdoba (Spain)
 * 
 * High Boost Filter:
 *  Create a program that reads and image and a value for the High Boost 
 *  filter and saves the corresponding image with the HighBoost Filter applied.
 * 
 * **************************************/

/*
 * Documentation:
    - ones() : https://docs.opencv.org/4.5.3/d3/d63/classcv_1_1Mat.html#a69ae0402d116fc9c71908d8508dc2f09
    - converTo() : https://docs.opencv.org/4.5.3/d3/d63/classcv_1_1Mat.html#adf88c60c5b4980e05bb556080916978b
    - normalize(): https://docs.opencv.org/4.5.3/d2/de8/group__core__array.html#ga87eef7ee3970f86906d69a92cbf064bd
*/

/*
    NOTE: I assume that we have to calculate first the High frecuency image from the original image and then calculate the 
    high boost image by adding the High frecuency image (with the kernel applyed) to the original image:
        High frecuency = Original image - Low frecuency image
        High boost image = Original image + (c · High frecuency image)

    I will use a box filter to calculate the Low frecuency image.
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
    Mat user_image = imread(argv[1], IMREAD_GRAYSCALE);
   
    if(user_image.rows == 0){
        cerr << "Error, your image is empty or you wrote image's name wrongly" << endl;
        return 0;
    }

    //Now the user's image is converted to CV_32FC1
    Mat original_image;
    user_image.convertTo(original_image, CV_32FC1);

    float c;
    cout << "Introduce the value for 'c': ";
    cin >> c;

    Mat LowPass_image = original_image.clone();
    Mat HighPass_image = original_image.clone();
    Mat HighPass_c_result_image = original_image.clone();
    Mat HighBoost_image = original_image.clone();

    //We create the matrix that will have the values of our kernels
    //This kernel will be use to calculate the Low pass image
  /*  float box_matrix[] = { 1/9, 1/9, 1/9,
                           1/9, 1/9, 1/9,       
                           1/9, 1/9, 1/9 };*/

    //This kernel will be use to calculate the High boost image
    float boost_matrix[] = { -c, -c, -c,
                             -c, 8*c+1, -c,       
                            -c, -c, -c  };

    //Creation of the kernels    
    Mat box_kernel(3, 3, CV_32FC1);
    box_kernel=Mat::ones(3, 3, CV_32FC1)/(9);
    Mat boost_kernel(3, 3, CV_32FC1, boost_matrix);


    //Now we apply the box kernel to the original image to calculate the Low pass image
    applyKernel(original_image, LowPass_image, box_kernel);

    //We calculate the High pass image:
    HighPass_image = original_image - LowPass_image;

    //After this, we apply the boost_kernel to the High pass image
    applyKernel(HighPass_image, HighPass_c_result_image, boost_kernel);

    //Now we calculate the high boost image
    HighBoost_image = original_image + HighPass_c_result_image;

    //Finally, the image is normalized
    Mat normalized_highBoost_image = HighBoost_image.clone();
    normalize(HighBoost_image, normalized_highBoost_image, 150, NORM_MINMAX);

    //Images are shown
    namedWindow("User image");
    imshow("User image", user_image);

    namedWindow("Result");
    imshow("Result", normalized_highBoost_image);

    waitKey(0);
} catch (exception &ex) {
    cout<<ex.what()<<endl;
}

}