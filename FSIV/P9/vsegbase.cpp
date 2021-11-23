/* 
   (c) Fundamentos de Sistemas Inteligenties en Vision
   University of Cordoba, Spain  
*/

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctype.h>
#include <cmath>


#include <opencv2/core/utility.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/video.hpp>

#include "seglib.hpp"

using namespace std;
using namespace cv;

#ifndef NDEBUG
int __Debug_Level = 0;
#endif

/*
  Use CMake to compile

  Documentation:

  - copyTo() : https://docs.opencv.org/3.4/d3/d63/classcv_1_1Mat.html#a33fd5d125b4c302b0c9aa86980791a77
  - gaussianBlur() : https://docs.opencv.org/3.4/d4/d86/group__imgproc__filter.html#gaabe8c836e97159a9193fb0b11ac52cf1
  - cvtColor() : https://docs.opencv.org/3.4/d8/d01/group__imgproc__color__conversions.html#ga397ae87e1288a81d2363b61574eb8cab

  NOTE: This functions are same that we created on assignment 7, I will use the functions of OpenCV
  - Morphological Transformations : https://docs.opencv.org/3.4/d9/d61/tutorial_py_morphological_ops.html
  - erode() : https://docs.opencv.org/3.4/d4/d86/group__imgproc__filter.html#gaeb1e0c1033e3f6b891a25d0511362aeb
  - dilate() : https://docs.opencv.org/3.4/d4/d86/group__imgproc__filter.html#ga4ff0f3318642c4f469d0e11f242f3b6c
*/

const cv::String keys =
    "{help h usage ? |      | print this message   }"        
#ifndef NDEBUG
    "{verbose        |0     | Set the verbose level.}"
#endif    
    "{t threshold    |13     | Segmentation threshold.}"
    "{s              |0   | Radius of structural element.}"   
    "{g              |  | Size of Gaussian's Kernel}" //New line for the size
    "{c              |  | Use the camera?}"
    "{@input         |<none>| Path to video/Camera index.}"
    "{@output        |<none>| Path to output video.}"
    ;

int main (int argc, char * const argv[])
{
  /* Default values */
  bool cameraInput=false;
  int threshold;
  const char * filein = 0;
  const char * fileout = 0;
  char opt;
  int radius = 0;
  int sizeGkernel = 0; //New variable that stores the size of the Gaussian's Kernel
  
  cv::CommandLineParser parser(argc, argv, keys);
  parser.about("Background segmentation in video.");
  if (parser.has("help"))
  {
      parser.printMessage();
      return 0;
  }

#ifndef NDEBUG
  __Debug_Level = parser.get<int>("verbose");
#endif
    
  std::string input_path = parser.get<std::string>("@input");
  std::string output_path = parser.get<std::string>("@output");
  threshold = parser.get<int>("threshold");  
  radius = parser.get<int>("s");
  sizeGkernel = parser.get<int>("g"); // We get the size that user wants

  if((sizeGkernel>0) && ((sizeGkernel%2)==0)){ // Checking that size is an odd number
    cerr << "ERROR: The kernel's size must be odd\n";
    abort();
  }

  filein = input_path.c_str();
  fileout = output_path.c_str();

  std::cout << "Input stream: " << filein << endl;
  std::cout << "Output: " << fileout << endl;

  VideoCapture input;
    
  if (parser.has("c"))
  {
    std::cout << "Using camera index" << std::endl;
    input.open(atoi(filein));
  }
  else  
    input.open(filein);
    
  if (!input.isOpened())
  {
    cerr << "Error: the input stream is not opened.\n";
    abort();
  }

  Mat inFrame; 
  bool wasOk = input.read(inFrame);
  if (!wasOk)
  {
    cerr << "Error: could not read any image from stream.\n";
    abort();
  }
  
  double fps=25.0;
  if (!cameraInput)
    fps=input.get(CAP_PROP_FPS); //CV_CAP_PROP_FPS was changed to CAP_PROP_FPS
  std::cout << "FPS: " << fps << std::endl; //I wrote "FPS: " in this cout.
  
  Mat outFrame = Mat::zeros(inFrame.size(), CV_8UC3);
  Mat theMask = Mat::zeros(inFrame.size(), CV_8UC1);
  
  std::cout << "Frame size: " <<inFrame.size() << std::endl; //I wrote "Frame size: " in this cout.
  VideoWriter output;
  
  output.open(fileout, cv::VideoWriter::fourcc('M','J','P','G'), fps, inFrame.size()); //CV_FOURCC was changed to cv::VideoWriter::fourcc
  if (!output.isOpened())
  {
    cerr << "Error: the ouput stream is not opened.\n";
    exit(-1);
  }  

  int frameNumber=0;
  int key = 0;

// WRITE ME 

  cv::namedWindow("Output");

  while(wasOk && key!=27)
  {
    frameNumber++;  
	  // Do your processing
	  // TODO
    
    // Creation of the previus frame
    Mat prevFrame;
    Mat result;
    Mat mask;
    inFrame.copyTo(prevFrame);

    // Now we get the next frame
    wasOk = input.read(inFrame); // Same as: input >> inFrame
    
    if((wasOk) && (inFrame.empty()==false)){

      // We apply the Gaussian's filter to both frames
      if (sizeGkernel > 0){
        GaussianBlur( inFrame, inFrame, Size(sizeGkernel, sizeGkernel), 0);
        GaussianBlur( prevFrame, prevFrame, Size(sizeGkernel, sizeGkernel), 0);
      }
      //We obtain the mask
      fsiv_segm_by_dif(prevFrame, inFrame, mask, threshold, radius);
      
      // TODO Apply the mask to the original frame and show
      //Finally we apply the mask into the original image
      fsiv_apply_mask(inFrame, mask, outFrame);

      namedWindow("Original");
      imshow ("Original", inFrame);  

      namedWindow("Mask");
      imshow ("Mask", mask); 

      namedWindow("Result");
      imshow ("Result", outFrame); 
    } 

    // TODO Add frame to output video
    output.write(outFrame); //Same as: output << inFrame
       
    key=waitKey(1);
  }           
  return 0;
}
