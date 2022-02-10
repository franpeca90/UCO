#include <opencv2/core/core.hpp> //core routines
#include <opencv2/highgui/highgui.hpp>//imread,imshow,namedWindow,waitKey
#include <opencv2/imgproc.hpp>

#include <iostream>

using namespace std;

using namespace cv; // Recordar que las funciones tienen su propio espacio de nombres

// Funcion propia de aplicar un kernel
void applyKernel(cv::Mat& in, cv::Mat& filter, cv::Mat& out){
    
    int amplitud = filter.cols/2; // Tomo el radio del kernel

    for(int i=amplitud ; i<in.rows-amplitud ; i++){ // Voy a traves de la imagen (filas y columnas) pero empezando por la amplitud y restando
        for(int j=amplitud ; j<in.cols-amplitud ; j++){
            float sum=0.0;                          // Inicializo suma antes del kernel
            for(int x=0 ; x<filter.rows ; x++){
                for(int y=0 ; y<filter.cols ; y++){ // Voy a traves del kernel de forma normal
                    // Sumo lo anterior mas el valor del pixel mas la posicion del kernel menos la amplitud por el kernel en esa posicion
                    sum = sum + in.at<uchar>(i+x-amplitud, j+y-amplitud) * filter.at<float>(x,y); 
                }
            }
            out.at<float>(i,j)=sum;
        }
    }
}

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


void medianFilter(const cv::Mat &in,cv::Mat &out, int size){

    int window_radio = size/2;
    //The idea of this 4 for bucles is the same as kernel, we go across the window that is on top of our image and we take that
    //values and we insert them into an array, which will be sort
    //Black and white image case
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
}

int main(int argc,char **argv){
    Mat img = imread(argv[1], IMREAD_GRAYSCALE);
    
    img.convertTo(img, CV_32FC1);

    namedWindow("Original");
    imshow("Original", img);
    
    Mat out;
    img.copyTo(out); // Creo una imagen igual
    
    // Creacion de diferentes tipos de filtros

    // -- Box filter --
    Mat box_filter = Mat::ones(3, 3, CV_32FC1); // Filtro con todo llenos de unos (Tamaño 3x3)





    // -- Derivative (Sobel filter) --
    // Matrices que tienen los valores de los kernels
    // Hay dos por cada eje, x e y.
    float sobel_x[] = { -1, 0, 1,
                        -2, 0, 2,       
                        -1, 0, 1  };

    float sobel_y[] = {  1,  2,  1,
                         0,  0,  0,       
                        -1, -2, -1  };
    
    //Creaciones de los kernels
    Mat sobel_kernelX(3, 3, CV_32FC1, sobel_x);
    Mat sobel_kernelY(3, 3, CV_32FC1, sobel_y);
/*
    Mat kernelX_result = user_image.clone();
    Mat kernelY_result = user_image.clone();
    Mat magnitude_image = user_image.clone();

    //We apply this kernels to our image with the applyKernel method
    applyKernel(user_image, kernelX_result, sobel_kernelX);
    applyKernel(user_image, kernelY_result, sobel_kernelY);

    //We calculate the magnitude values for our final image
    magnitude(kernelX_result, kernelY_result, magnitude_image);

    //We have to normalize the value of the image
    normalize(magnitude_image, normalized_image, 100, NORM_MINMAX);
*/




    // -- Highboost filter --

    // Kernel que se aplicara para calcular la low-pass image
    Mat low_pass = Mat::ones(3, 3, CV_32FC1)/float(9);

    // Kernel que se aplicara para calcular la high-pass image
    float c=2;
    
    float high_pass_c[] = { -c, -c, -c,
                             -c, 8*c+1, -c,       
                             -c, -c, -c  };
/*
    // Proceso de highboost
    Mat LowPass_image = original_image.clone();
    Mat HighPass_image = original_image.clone();
    Mat HighPass_c_result_image = original_image.clone();
    Mat HighBoost_image = original_image.clone();
    Mat normalized_highBoost_image = HighBoost_image.clone();

    //Now we apply the box kernel to the original image to calculate the Low pass image
    applyKernel(original_image, LowPass_image, box_kernel);

    //We calculate the High pass image:
    HighPass_image = original_image - LowPass_image;

    //After this, we apply the boost_kernel to the High pass image
    applyKernel(HighPass_image, HighPass_c_result_image, boost_kernel);

    //Now we calculate the high boost image
    HighBoost_image = original_image + HighPass_c_result_image;

    //Finally, the image is normalized
    normalize(HighBoost_image, normalized_highBoost_image, 150, NORM_MINMAX);
*/


    // Aplicar filtro con funcion propia
//   applyKernel(img, box_filter, out);



    // Aplicar un filtro usando una funcion de OpenCV
//   filter2D(img, out, -1 , box_filter);
    

    // -- Median filter --

    int size = 3;

    medianFilter(img, out, size);

    namedWindow("Filtro");
    imshow("Filtro", out);
    waitKey(0);
}