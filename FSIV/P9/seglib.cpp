// ----------------------------------------
// seglib.cpp
// (c) FSIV, University of Cordoba
// ----------------------------------------

/*
  Documentation:
  NOTE: This functions are same that we created on assignment 7, I will use the functions of OpenCV
  - Morphological Transformations : https://docs.opencv.org/3.4/d9/d61/tutorial_py_morphological_ops.html
  - erode() : https://docs.opencv.org/3.4/d4/d86/group__imgproc__filter.html#gaeb1e0c1033e3f6b891a25d0511362aeb
  - dilate() : https://docs.opencv.org/3.4/d4/d86/group__imgproc__filter.html#ga4ff0f3318642c4f469d0e11f242f3b6c

   - bitwise operations : https://docs.opencv.org/3.4/dd/d4d/tutorial_js_image_arithmetics.html

*/

#include "seglib.hpp"

using namespace cv;

void fsiv_segm_by_dif(const cv::Mat & prevFrame, const cv::Mat & curFrame, cv::Mat & difimg, int thr, int r)
{
   // WRITE ME
   Mat aux1, aux2;
   curFrame.copyTo(aux1);
   prevFrame.copyTo(aux2);

   //We change from RGB to gray scale (0 to 255)
   cvtColor(aux1, aux1, COLOR_BGR2GRAY);
   cvtColor(aux2, aux2, COLOR_BGR2GRAY);

   aux1.copyTo(difimg);

   Mat diff;
   absdiff(aux1, aux2, diff);

   // We do the "I_t+1 - I_t > threshold" operation for every pixel
   for(int x=0 ; x<diff.rows ; x++){ //Where x and y are the position of the image's pixels
        for(int y=0 ; y<diff.cols ; y++){        
            if(diff.at<uchar>(x,y) > thr){ 
                difimg.at<uchar>(x,y) = 255;
            } else {
                difimg.at<uchar>(x,y) = 0; 
            }
         }
   }

   if (r > 0){
      //Creation of the kernel
      Mat morphologicalKernel(r, r, CV_32FC1);
      morphologicalKernel = Mat::ones(r, r, CV_32FC1);        

      // Opening
      erode(difimg, difimg, morphologicalKernel, Point(-1,-1));
      dilate(difimg, difimg, morphologicalKernel, Point(-1,-1));

      // Closing
      dilate(difimg, difimg, morphologicalKernel, Point(-1,-1));
      erode(difimg, difimg, morphologicalKernel, Point(-1,-1));
   }

}

void fsiv_apply_mask(const cv::Mat & frame, const cv::Mat & mask, cv::Mat & outframe)
{
   // WRITE ME
   Mat aux1, aux2;
   frame.copyTo(aux1); //The frame is rgb
   mask.copyTo(aux2);  //The mask is one-channel

   cvtColor(mask, aux2, 3); //We change the mask from 1 channel to 3 channel

   //With this, now we can operate the frame and the mask
   for(int x=0 ; x<outframe.rows ; x++){ //Where x and y are the position of the image's pixels
        for(int y=0 ; y<outframe.cols ; y++){
            //We use the operator & to take only those pixels that are "behind the kernel"
            outframe.at<Vec3b>(x,y)[0] = aux1.at<Vec3b>(x,y)[0] & aux2.at<Vec3b>(x,y)[0];
            outframe.at<Vec3b>(x,y)[1] = aux1.at<Vec3b>(x,y)[1] & aux2.at<Vec3b>(x,y)[1];
            outframe.at<Vec3b>(x,y)[2] = aux1.at<Vec3b>(x,y)[2] & aux2.at<Vec3b>(x,y)[2];

         }
   }
   
   //Note for me: Instead of using &, we could have multiply the frame and the kernel and get those points where
   //the pixels are different from zero?. Maybe do this using the only the mask and not multiplying?
   // --> Ask to the teacher

}

// ================= OPTIONAL PART STARTS HERE =======================

void fsiv_learn_model(cv::VideoCapture & input, int maxframes, cv::Mat & MeanI, cv::Mat & I2, cv::Mat & VarI, cv::Mat & StdI)
{
   // WRITE ME

}

void fsiv_acc_model(const cv::Mat & frame, cv::Mat & MeanI, cv::Mat & I2)
{
   // WRITE ME
}

void fsiv_segm_by_model(const cv::Mat & frame, cv::Mat & theMask, const cv::Mat & mean, const cv::Mat & std, float t, int r)
{
   // WRITE ME
}

void fsiv_update_model(const cv::Mat & frame, cv::Mat & mean, cv::Mat & I2, cv::Mat &std,  float alpha, const cv::Mat & theMask)
{
   // WRITE ME
}
