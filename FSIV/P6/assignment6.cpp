/****************************************
 * Autor: Francisco Javier Perez Castillo
 * Universidad de Córdoba (Spain)
 * 
 * Create a program that compares the result of the median filter and the box filter for the input image given.
 * You will have to create a function implementing the median filter (not using the existing one):
 * 
 * void medianFilter(const cv::Mat &in,cv::Mat &out, int size);
 * 
 * Then, use also your previous applyKernel function to apply a box filter to the same image and see the results. 
 * Which obtains better results?
 * There are two possible versions of this tasks:
 * 
 *  a) gray scale (up to 6 points)
 *  b) color image (up to 10 points)
 * 
 * You can use the OpenCV functions cv::split,cv::merge
 * 
 * **************************************/

/*
 * Documentation:

    - channels() : https://docs.opencv.org/4.5.4/d3/d63/classcv_1_1Mat.html#aa11336b9ac538e0475d840657ce164be
    - converTo() : https://docs.opencv.org/4.5.3/d3/d63/classcv_1_1Mat.html#adf88c60c5b4980e05bb556080916978b
*/
/*

*/

#include <opencv2/core/core.hpp> //core routines
#include <opencv2/highgui/highgui.hpp>//imread,imshow,namedWindow,waitKey
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

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

    if(in.channels()==1){
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
                            sum_val = sum_val + (in.at<uchar>(x+kx, y+ky) * kernel.at<float>(kx+kernel_radio,ky+kernel_radio));
                        }
                    }
                }
                //Once we have the "mean" of the value around the pixel, we can change the value in our aux image
                out.at<uchar>(x,y) = sum_val;
            }
        }
    } else if (in.channels()==3){
        for(int x=0 ; x<in.rows ; x++){ //Where x and y are the position of the image's pixels
            for(int y=0 ; y<in.cols ; y++){
                //Now we are on the pixel where we apply the kernel           
                float sum_val1 = 0.0;
                float sum_val2 = 0.0;
                float sum_val3 = 0.0;
                //We go around the kernel
                for(int kx=((size*(-1))+(size/2))+1; kx<size-(size/2); kx++) {
                    for(int ky=((size*(-1))+(size/2))+1; ky<size-(size/2); ky++){	
                        if((kx+x < 0) || (ky+y < 0) || (kx+x >= in.rows) || (ky+y >= in.cols)){
                            sum_val1 = sum_val1 + 0;
                            sum_val2 = sum_val2 + 0;
                            sum_val3 = sum_val3 + 0;
                        } else {
                            sum_val1 = sum_val1 + (in.at<Vec3b>(x+kx, y+ky)[0] * kernel.at<float>(kx+kernel_radio,ky+kernel_radio));
                            sum_val2 = sum_val2 + (in.at<Vec3b>(x+kx, y+ky)[1] * kernel.at<float>(kx+kernel_radio,ky+kernel_radio));
                            sum_val3 = sum_val3 + (in.at<Vec3b>(x+kx, y+ky)[2] * kernel.at<float>(kx+kernel_radio,ky+kernel_radio));
                        }
                    }
                }
                //Once we have the "mean" of the value around the pixel, we can change the value in our aux image
                out.at<Vec3b>(x,y)[0] = sum_val1;
                out.at<Vec3b>(x,y)[1] = sum_val2;
                out.at<Vec3b>(x,y)[2] = sum_val3;
            }
        }
    }
}


void medianFilter(const cv::Mat &in,cv::Mat &out, int size){
    if(size <=1){
        cout << "Error, your window size is wrong" << endl;
        return;
    }
    
    int window_radio = size/2;
    //The idea of this 4 for bucles is the same as kernel, we go across the window that is on top of our image and we take that
    //values and we insert them into an array, which will be sort
    if(in.channels()==1){ //Black and white image case
        vector<uchar> val;
        
        for(int x=0 ; x<in.rows ; x++){ //Where x and y are the position of the image's pixels
            for(int y=0 ; y<in.cols ; y++){
                //We go around the window
                for(int kx=((size*(-1))+(size/2))+1; kx<size-(size/2); kx++) {
                    for(int ky=((size*(-1))+(size/2))+1; ky<size-(size/2); ky++){	
                        if((kx+x < 0) || (ky+y < 0) || (kx+x >= in.rows) || (ky+y >= in.cols)){
                            val.push_back(0);
                        } else {
                            val.push_back(in.at<uchar>(x+kx, y+ky));
                        }
                    }
                }

                sort(val.begin(), val.end());
                //Once the array is sorted, we take the middle value of the array, the median value
                out.at<uchar>(x,y) = val[ (val.size()/2) ];
                //Very important to reset our array
                val.clear(); 
            }
        }
    } else if (in.channels()==3){ //Color image case
        vector<uchar> val1;
        vector<uchar> val2;
        vector<uchar> val3;
        //In this case we use 3 vector to store all the values of each channel
        for(int x=0 ; x<in.rows ; x++){ //Where x and y are the position of the image's pixels
            for(int y=0 ; y<in.cols ; y++){

                //We go around the window
                for(int kx=((size*(-1))+(size/2))+1; kx<size-(size/2); kx++) {
                    for(int ky=((size*(-1))+(size/2))+1; ky<size-(size/2); ky++){	
                        if((kx+x < 0) || (ky+y < 0) || (kx+x >= in.rows) || (ky+y >= in.cols)){
                            val1.push_back(0);
                            val2.push_back(0);
                            val3.push_back(0);
                        } else {
                            val1.push_back(in.at<Vec3b>(x+kx, y+ky)[0]);
                            val2.push_back(in.at<Vec3b>(x+kx, y+ky)[1]);
                            val3.push_back(in.at<Vec3b>(x+kx, y+ky)[2]);
                        }
                    }
                }

                sort(val1.begin(), val1.end());
                sort(val2.begin(), val2.end());
                sort(val3.begin(), val3.end());
                //Once the array is sorted, we take the middle value of the array, the median value
                out.at<Vec3b>(x,y)[0] = val1[ (val1.size()/2) ];
                out.at<Vec3b>(x,y)[1] = val2[ (val2.size()/2) ];
                out.at<Vec3b>(x,y)[2] = val3[ (val3.size()/2) ];
                //Very important to reset our array
                val1.clear();
                val2.clear();
                val3.clear(); 
            }
        }       
    }
}


int main(int argc,char **argv){
try {
    bool flag_error = false;

    //We check that user introduce only one image
    if(argc!=2){
        cerr<<"Error, you have to insert an image as an argument"<<endl;
        return 0;
    }

    //We ask for the type of image
    int option;
    cout <<"Introduce '1' for a black and white image, '2' for color image: ";
    cin >> option;

    //Case where we use black and white images
    //We save the image in a variable in grey scale
    Mat user_image;

    //We read the image baseed of the type of image that user wants
    if (option==1){
        user_image = imread(argv[1], IMREAD_GRAYSCALE);
    } else if (option==2){
            user_image = imread(argv[1], CV_32FC1);
            cout << "color" << endl;
    }

    if(user_image.rows == 0){
        cerr << "Error, your image is empty or you wrote image's name wrongly" << endl;
        return 0;
    }

    //Size of the kernel and window
    int n;
    cout << "Introduce the value for 'n': ";
    cin >> n;
    int size = n*n;

    if(size <=1){
        cout << "Error, your window size is wrong" << endl;
        return 0;
    }

    Mat result_image = user_image.clone();
    Mat box_image = user_image.clone();
    
    //We apply the median filter
    medianFilter(user_image, result_image, size);

    //Creation of the kernel    
    Mat box_kernel(n, n, CV_32FC1);
    box_kernel=Mat::ones(n, n, CV_32FC1)/(n*n);

    //We apply the box filter
    applyKernel(user_image, box_image, box_kernel);

    //Images are shown
    namedWindow("User image");
    imshow("User image", user_image);

    namedWindow("Result");
    imshow("Result", result_image);

    namedWindow("Box image");
    imshow("Box image", box_image);


    waitKey(0);
} catch (exception &ex) {
    cout<<ex.what()<<endl;
}

}