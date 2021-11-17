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

*/

#include "seglib.hpp"

using namespace cv;

void fsiv_segm_by_dif(const cv::Mat & prevFrame, const cv::Mat & curFrame, cv::Mat & difimg, int thr, int r)
{
   // WRITE ME
   
   // We apply the morphological operations (Opening + Closing)
   if (r > 0){
      //Creation of the kernel
      Mat morphologicalKernel(r, r, CV_32FC1);
      morphologicalKernel = Mat::ones(r, r, CV_32FC1);
      cout << "test" <<endl;          
      //We change from RGB to gray scale (0 to 255)
      cvtColor(curFrame, curFrame, COLOR_BGR2GRAY);
      cvtColor(prevFrame, prevFrame, COLOR_BGR2GRAY);
     
      // Opening
      erode(curFrame, curFrame, morphologicalKernel, Point(-1,-1));
      dilate(curFrame, curFrame, morphologicalKernel, Point(-1,-1));
      
      erode(prevFrame, prevFrame, morphologicalKernel, Point(-1,-1));
      dilate(prevFrame, prevFrame, morphologicalKernel, Point(-1,-1));

      // Closing
      dilate(curFrame, curFrame, morphologicalKernel, Point(-1,-1));
      erode(curFrame, curFrame, morphologicalKernel, Point(-1,-1));

      dilate(prevFrame, prevFrame, morphologicalKernel, Point(-1,-1));
      erode(prevFrame, prevFrame, morphologicalKernel, Point(-1,-1));
   }


   
}

void fsiv_apply_mask(const cv::Mat & frame, const cv::Mat & mask, cv::Mat & outframe)
{
   // WRITE ME
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
