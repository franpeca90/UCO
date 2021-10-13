/****************************************
 * Autor: Francisco Javier Perez Castillo
 * Universidad de Córdoba (Spain)
 * 
 * Image equalization:
 *   - User introduce a black and white image
 *     and the program will show two windows,
 *     one will be the original image
 *     and the other one will be the equalizated
 *     image of the original. 
 * 
 * **************************************/

/*
 * Documentation:
 *   clone() : https://docs.opencv.org/4.5.3/d3/d63/classcv_1_1Mat.html#adff2ea98da45eae0833e73582dd4a660
 *   Histogram equalization : https://docs.opencv.org/3.4.15/d4/d1b/tutorial_histogram_equalization.html
*/

#include <opencv2/core/core.hpp> //core routines
#include <opencv2/highgui/highgui.hpp>//imread,imshow,namedWindow,waitKey
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc,char **argv){
try {

    //256 elements with value 0 
    //h(i) can be from [0,255], where 'i' is the pixel and h() the histogram function
    vector<int> histogram(256,0);
    vector<double> accumulative_histogram(256,0); 
    vector<double> factors(256,0);
    //We check that user introduce only one image
    if(argc!=2){
        cerr<<"Error, you have to insert an image as an argument"<<endl;
        return 0;
    }

    //We save the image in a variable in grey scale
    Mat user_image=imread(argv[1], IMREAD_GRAYSCALE);

    if(user_image.rows == 0){
        cerr << "Error, your image is empty or you wrote image's name wrongly" << endl;
        return 0;
    }

    //We create a copy of the original image
    Mat aux_image=user_image.clone();

    //Now we create the histogram of the user's image
    //We go around the rows and cols
    for(int x=0 ; x<user_image.rows ; x++){
        for(int y=0 ; y<user_image.cols ; y++){
            //We need to know the value of a pixel, onece we know it
            //we have to had 1 in the position of the histogram vector with
            //the same value of the pixel of the original image

            //We access to gre-scale pixel, with only one value
            int val = user_image.at<uchar>(x,y);
            histogram[val] = histogram[val] + 1;
        }
    }

    //We create the accumulative histogram
    //This is done by adding the value of the actual 'i' position of
    //the histogram plus the value of the 'i-1' position of our accum. vector
    accumulative_histogram[0] = histogram[0];
    for(int i = 1 ; i<accumulative_histogram.size() ; i++){
        accumulative_histogram[i] = histogram[i] + accumulative_histogram[i-1];
    }

    //To calibrate our image we must change the value of the pixels 
    //based of the results of the accumulative histogram, but first we need to multiply by a 
    //factor to scale this values to [0,255] range

    //To do this, we calculate the factor dividing 255 by the size of our image
    double factor = (double)255/(double)(user_image.rows*user_image.cols);
    
    //Now we create an array of factors where 'i' position stores the factor that
    //will be use to create our balanced image
    for(int i=0 ; i<accumulative_histogram.size(); i++){
        factors[i] = accumulative_histogram[i] * factor;
    }

    //We create the balanced image using these factors and with the original image
    for(int x=0 ; x<aux_image.rows ; x++){
        for(int y=0 ; y<aux_image.cols ; y++){
            aux_image.at<uchar>(x,y) = factors[aux_image.at<uchar>(x,y)];
        }
    }

    //Finally, we show both images
    imshow("Normal image", user_image);
    imshow("Equalized image", aux_image);

    
    waitKey(0);
} catch (exception &ex) {
    cout<<ex.what()<<endl;
}

}