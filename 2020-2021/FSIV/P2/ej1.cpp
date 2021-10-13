#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace std;


int main(int argc, char** argv){
  try {

    //Auxiliar variables
    float sum=0;
    float auxMax=0;
    float auxB=0, auxG=0, auxR=0;
    float auxScalar=0;
    float brightest[3];

    //We create the image object
    cv::Mat image;
    image=cv::imread(argv[1]);//, cv::IMREAD_GRAYSCALE);

    //We show the original image
    cv::namedWindow("Original");
    cv::imshow("Original",image);

    //With this we know the brightest pixel and the value we have to add
    for(int j=0 ; j<image.rows; j++){
      uchar* ptr=image.ptr<uchar>(j);
      for(int i=0 ; i<image.cols; i++){ //We access to the cols of that row

        sum=(ptr[0]+ptr[1]+ptr[2])/3;

        if(sum>auxMax){
          auxMax=sum; //Value to know the brightest pixel of the image
          //This are the values of the brightest pixel
          brightest[0]=ptr[0];
          brightest[1]=ptr[1];
          brightest[2]=ptr[2];

        }
        ptr+=3; //We go to the next pixel
      }
    }

    //Now we calculate the factor value that we have to multiply to the pixels of the matrix
    if (brightest[0]!=0) {
      auxB = 255 / brightest[0];
    }

    if (brightest[1]!=0) {
      auxG = 255 / brightest[1];
    }

    if (brightest[2]!=0) {
      auxR = 255 / brightest[2];
    }

    //We multiply the factor value to all our image, we change all pixels

    for(int j=0 ; j<image.rows; j++){
      uchar* ptr=image.ptr<uchar>(j);
      for(int i=0 ; i<image.cols; i++){ //We access to the cols of that row
        //We store the value of the pixels multiplied by the factor
        //We use an aux variable to prevent overflow
        auxScalar = ptr[0] * auxB;

        if(auxScalar>255){
          ptr[0]=255;
        } else {
          ptr[0]=auxScalar;
        }

        auxScalar = ptr[1] * auxG;

        if(auxScalar>255){
          ptr[1]=255;
        } else {
          ptr[1]=auxScalar;
        }

        auxScalar = ptr[2] * auxR;

        if(auxScalar>255){
          ptr[2]=255;
        } else {
          ptr[2]=auxScalar;
        }

        ptr+=3; //We go to the next pixel
      }
    }


    //We show the image with new colors
    cv::namedWindow("Retocada");
    cv::imshow("Retocada",image);


    cv::waitKey(0);

  } catch (std::exception &ex){
      cerr<<ex.what()<<endl;
  }


}
