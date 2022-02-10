#include <opencv2/core/core.hpp> //core routines
#include <opencv2/highgui/highgui.hpp>//imread,imshow,namedWindow,waitKey
#include <opencv2/imgproc.hpp>

#include <iostream>

using namespace std;

using namespace cv; // Recordar que las funciones tienen su propio espacio de nombres

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



int main(int argc,char **argv){
    
    


}