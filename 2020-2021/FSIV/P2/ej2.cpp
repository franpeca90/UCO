#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace std;
class CmdLineParser{

    int argc;
    char **argv;

public:
    CmdLineParser(int _argc,char **_argv):argc(_argc),argv(_argv){}

    bool operator[] ( string param ) {
        int idx=-1;
        for ( int i=0; i<argc && idx==-1; i++ )
            if ( string ( argv[i] ) == param )
                idx=i;
        return ( idx!=-1 ) ;
    }

    string operator()(string param,string defvalue="-1") {
        int idx=-1;
        for ( int i=0; i<argc && idx==-1; i++ )
            if ( string ( argv[i] ) == param )
                idx=i;
        if ( idx==-1 )
            return defvalue;
        else
            return ( argv[idx+1] );
    }
};


void waitPatch(){


  
}


int main(int argc, char** argv){
  try {

    CmdLineParser cml(argc,argv);
    //check if a command is present
    if (cml["-p"]){
        cout<<"-p option is in the command line" << endl;
        float f= stof(cml("-p")); //convert to float
        int i= stoi(cml("-p")); //convert to int

    }

    //used with default values
    float f= stof(cml("-p","1")); //if -p is not, then, return 1

    float p=stof(cml("-p")); //We store the option in a float variable

    cout << "El valor de -p es: " << p <<endl;
    cout << "El valor de -p -1 es: " << 1-p <<endl;

    //Variables
    int histogram[256];
    //At te begenning, histogram has value 0
    for (int i = 0; i < 256; i++) {
      histogram[i]=0;
    }
    int limit=0, pixelsTaken=0, sumHistogram=0;
    float sumB=0, sumG=0, sumR=0, nElem=0;
    float meanG=0, meanB=0, meanR=0;
    float factorB=0, factorG=0, factorR=0;

    //We create the image object
    cv::Mat image;
    image=cv::imread(argv[1]);
    //We open the image in black and white to get the histogram
    cv::Mat imageBW;
    imageBW=cv::imread(argv[1], cv::IMREAD_GRAYSCALE);

    //We show the original image
    cv::namedWindow("Original");
    cv::imshow("Original",image);

    //We calculate the histogram of our image
    for(int j=0 ; j<imageBW.rows; j++){
      for(int i=0 ; i<imageBW.cols; i++){
        //We store the value of the pixel
        auto val = imageBW.at<uchar>(j,i);
        //and we store that value in a vector
        //With this vector we know how many pixels have an specific value
        //This is, the histogram of our image
        histogram[val]=histogram[val]+1;
      }
    }

    //We calculate the ammount of pixels we are going to take
    pixelsTaken = imageBW.cols * imageBW.rows * p;

    for(limit=255 ; limit>=0 ; limit--){
      //We add until we reach the maximum pixels
      if(sumHistogram > pixelsTaken){
        break;
      }
      sumHistogram+=histogram[limit];
    }

    //Once we end the loop, we know the limit
    for(int j=0 ; j<image.rows; j++){
      uchar* ptr=image.ptr<uchar>(j);
      for(int i=0 ; i<image.cols; i++){
        //A pixel will be in our mean if the brightness of that pixel
        //is bigger than the limit we calculated in the histogram
        //So we have to calculate the brighness of the pixel and check if it is
        //bigger or not
        //We can use lightness, avarage or luminosity conversion. In this case
        //we are going to use luminosity method
        float auxBrightness = ptr[0]*0.07+ptr[1]*0.72+ptr[2]*0.21;

        if(auxBrightness>=limit){
//        std::cout << "Entro" << '\n';
          sumB+=ptr[0];
          sumG+=ptr[1];
          sumR+=ptr[2];
          nElem++;
        }

        ptr+=3; //We go to the next pixel
      }
    }

    //We get the factors with the means
    meanB = sumB/nElem;
    meanG = sumG/nElem;
    meanR = sumR/nElem;

    factorB = 255 / meanB;
    factorG = 255 / meanG;
    factorR = 255 / meanR;

    //Finally we change the color of the image
    for(int j=0 ; j<image.rows; j++){
      uchar* ptr=image.ptr<uchar>(j);
      for(int i=0 ; i<image.cols; i++){

        if(ptr[0]*factorB>255){
          ptr[0]=255;
        } else {
          ptr[0]=ptr[0]*factorB;
        }

        if(ptr[1]*factorG>255){
          ptr[1]=255;
        } else {
          ptr[1]=ptr[1]*factorG;
        }

        if(ptr[2]*factorR>255){
          ptr[2]=255;
        } else {
          ptr[2]=ptr[2]*factorR;
        }


        ptr+=3; //We go to the next pixel
      }
    }



    //We show the image with new colors
    cv::namedWindow("Retocada");
    cv::imshow("Retocada",image);

    cv::waitKey(0) & 0xff;

  } catch (std::exception &ex){
      cerr<<ex.what()<<endl;
  }


}
