/****************************************
 * Autor: Francisco Javier Perez Castillo
 * Universidad de Córdoba (Spain)
 * 
 * Create a program that reads an input image, threshold the image, and then
 * applies the morphological operations: erode, dilate, open, close, saving the result into a file.
 * 
 * The program must have the following command-line arguments:
 * 
 * ./prog in_image out_image -thres <val> -op <(erode|dilate|open|close)> 
 * 
 * -thres <val> : threhold value. The image will be thresholded using this value. pixels BELOW this value will be set to 255, the others to 0.
 * 
 * -op <string>:  the morphological operation to be applied.
 * 
 * **************************************/

/*
 * Documentation:

    - getopt_long() : https://linux.die.net/man/3/getopt_long
    - struct option : https://linux.die.net/man/3/getopt_long
    - ones() : https://docs.opencv.org/4.5.3/d3/d63/classcv_1_1Mat.html#a69ae0402d116fc9c71908d8508dc2f09

*/
/*

*/

#include <opencv2/core/core.hpp> //core routines
#include <opencv2/highgui/highgui.hpp>//imread,imshow,namedWindow,waitKey
#include <iostream>
#include <string>
#include <getopt.h>

using namespace std;
using namespace cv;

void threhold_operation(const Mat &in, Mat &out, const int threshold){
    for(int x=0 ; x<in.rows ; x++){ //Where x and y are the position of the image's pixels
        for(int y=0 ; y<in.cols ; y++){
            if(in.at<uchar>(x,y) < threshold){ //If the pixel of the original image is BELOW this value...
                out.at<uchar>(x,y) = 255; //... we apply 255 value ...
            } else {
                out.at<uchar>(x,y) = 0; // ... if not we apply 0
            }
        }
    }
}

void erode(const Mat &in, Mat &out, const Mat &kernel){
    
    if(kernel.cols <=1){
        cout << "Error, your kernel size is wrong" << endl;
        return;
    }

    //We calculate the radius of the kernel
    int size = kernel.cols;
    int kernel_radio = kernel.cols/2;
        for(int x=0 ; x<in.rows ; x++){ //Where x and y are the position of the image's pixels
            for(int y=0 ; y<in.cols ; y++){           
               float min_val = 255;
                //We go around the kernel
                for(int kx=((size*(-1))+(size/2))+1; kx<size-(size/2); kx++) {
                    for(int ky=((size*(-1))+(size/2))+1; ky<size-(size/2); ky++){	
                        if((kx+x < 0) || (ky+y < 0) || (kx+x >= in.rows) || (ky+y >= in.cols)){
                            //We dont change the value here
                        } else {
                            if(in.at<uchar>(x+kx, y+ky) < min_val){ //If the pixel has a lower value, this value
                                min_val = in.at<uchar>(x+kx, y+ky); //will be our new lowest value.
                            }
                        }
                    }
                }
                //Once we have the minium value, we apply it to the pixel
                out.at<uchar>(x,y) = min_val;
            }
        }
}

void dilate(const Mat &in, Mat &out, const Mat &kernel){
    
    if(kernel.cols <=1){
        cout << "Error, your kernel size is wrong" << endl;
        return;
    }

    //We calculate the radius of the kernel
    int size = kernel.cols;
    int kernel_radio = kernel.cols/2;
        for(int x=0 ; x<in.rows ; x++){ //Where x and y are the position of the image's pixels
            for(int y=0 ; y<in.cols ; y++){           
               float max_val = 0;
                //We go around the kernel
                for(int kx=((size*(-1))+(size/2))+1; kx<size-(size/2); kx++) {
                    for(int ky=((size*(-1))+(size/2))+1; ky<size-(size/2); ky++){	
                        if((kx+x < 0) || (ky+y < 0) || (kx+x >= in.rows) || (ky+y >= in.cols)){
                            //We dont change the value here
                        } else {
                            if(in.at<uchar>(x+kx, y+ky) > max_val){ //If the pixel has a bigger value, this value
                                max_val = in.at<uchar>(x+kx, y+ky); //will be our new biggest value.
                            }
                        }
                    }
                }
                //Once we have the maximum value, we apply it to the pixel
                out.at<uchar>(x,y) = max_val;
            }
        }
}


int main(int argc,char **argv){
try {

    bool operation_flag = false;

    //We check the arguments of the program
    if(argc!=7){
        cerr<<"Error in command-line arguments"<<endl;
        return 0;
    }

    //Struct for long options
    const struct option long_options[]={
        {"thres", required_argument, 0, 't'},
        {"op", required_argument, 0, 'o'},
        {0,0,0},
    };
    
    //Variables necessary to get the options
    int longindex;
    int c = 0;
    //Variables that storage the threshold and the operation
    string threshold_argument;
    string operation_argument;

    string file_img = argv[1]; //This is the path of the user's image
    string file_save = argv[2];//This is the name of the img that will be export as a file

    while( (c=getopt_long(argc, argv, "t:o:", long_options, &longindex)) != -1){
        switch(c){
            case 't':
                threshold_argument=optarg;
            break;

            case 'o':
                operation_argument=optarg;
            break;
        }
    }

    //Warning, if does not introduce a number, the program will throw an error
    int threshold = stoi(threshold_argument);

    //We read user's image
    Mat user_image = imread(file_img, IMREAD_GRAYSCALE);

    if(user_image.rows == 0){
        cerr << "Error, your image is empty or you wrote image's name wrongly" << endl;
        return 0;
    }

    //Size of the kernel and window
    int n;
    cout << "Introduce the value for 'n': ";
    cin >> n;

    //Creation of the window filled with 1
    //Warning, I use the "kernel" to know which pixel I want to use, I will NOT change the value of the original pixels by
    //multypling or adding by the kernel. This is why sometimes I call this "window" instead of kernel. Window <=> kernel
    Mat kernel(n, n, CV_32FC1);
    kernel = Mat::ones(n, n, CV_32FC1);

    //We create the image that will be the result of the operations
    Mat result_img = user_image.clone();
    //To apply the morphological operations, first we need to apply a thershold to the image.
    Mat threshold_img = user_image.clone();
    //Auxiliar image for Open and Close operations
    Mat aux_img = user_image.clone();

    //We calculate the threshold image
    threhold_operation(user_image, threshold_img, threshold); 
    
    //Now we apply diferent filters in base of the operation that user wants
    //Important to know that Open: erode then dilate, and Close: dilate then erode
    if(operation_argument == "erode"){
        erode(threshold_img, result_img, kernel);
        operation_flag = true;
    }

    if(operation_argument == "dilate"){
        dilate(threshold_img, result_img, kernel);
        operation_flag = true;
    }
    
    if(operation_argument == "open"){
        erode(threshold_img, aux_img, kernel);
        dilate(aux_img, result_img, kernel);
        operation_flag = true;
    }

    if(operation_argument == "close"){
        dilate(threshold_img, aux_img, kernel);
        erode(aux_img, result_img, kernel);
        operation_flag = true;
    }

    if(operation_flag == false){ //This is in case that user introduce an invalid operation
        cout << "Error, incorrect operation" << endl;
        return 0;
    }
    
    //We show the result image
    namedWindow("result image");
    imshow("result image", result_img);
    //We show the threshold image
    namedWindow("threshold image");
    imshow("threshold image", threshold_img);
    //We export the image
    imwrite(file_save, result_img);
    waitKey(0);
    
} catch (exception &ex) {
    cout<< "Error in function: " << ex.what()<<endl;
}

}