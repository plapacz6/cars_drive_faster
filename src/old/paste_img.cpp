#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "paste_img.h"
using namespace cv;
/* ----------------------------------------- */


void paste_img(const Mat& src, const Rect& coord, Mat& dst){
  for(int w = 0; w < src.rows && w < coord.height; ++w){
    for(int c = 0; c < src.cols && c < coord.width; ++c){
      dst.at<Vec3b>(coord.y + w, coord.x + c) = src.at<Vec3b>(w, c);
    }
  }
}

/**
 * @brief pasting a part of the image that may protrude vertically
 * beyond the dimensions of the dst
 * 
 * @param src 
 * @param coord 
 * @param dst 
 */
void paste_img_vert_partialy(const Mat& src, const Rect& coord, Mat& dst){
  for(int w = 0; 
      w < src.rows && w < coord.height;
      ++w){
    for(int c = 0; c < src.cols && c < coord.width; ++c){
      if(coord.y + w < dst.rows && coord.y + w > 0){
        dst.at<Vec3b>(coord.y + w, coord.x + c) = src.at<Vec3b>(w, c);
      }
    }
  }
}

/**
 * @brief paste img to borad in vertical wrap mode
 * 
 */
void paste_img_vert_wrap(const Mat& src, const Rect& coord, int vert_shift, Mat& dst){
  
  //PDEBUG_(vert_shift);
  // while(vert_shift >= 500) {
  //   vert_shift -= 500;
  while(vert_shift >= coord.height) {
    vert_shift -= coord.height;    
  }
  int w1 = 0; 
  for(int w2 = vert_shift;
      w1 < src.rows - vert_shift && w2 < coord.height; 
      ++w1, ++w2)
    {
    for(int c = 0; c < src.cols && c < coord.width; ++c){
      dst.at<Vec3b>(coord.y + w2, coord.x + c) = src.at<Vec3b>(w1, c);
    }
  }  
  for(int w2 = 0; 
      w1 < src.rows && w2 < vert_shift;
      ++w1, ++w2)
    {        
    for(int c = 0; c < src.cols && c < coord.width; ++c){
      dst.at<Vec3b>(coord.y + w2, coord.x + c) = src.at<Vec3b>(w1, c);
    }
  }
}


void paste_img_horiz_wrap(const Mat& src, const Rect& coord, int horiz_shift, Mat& dst){
  while(horiz_shift >= coord.width){
    horiz_shift -= coord.width;
  }
  int c1 = 0;
  for(int w = 0; w < src.rows && w < dst.rows; ++w){
    c1 = 0;
    for(int c2 = horiz_shift;
        c1 < src.cols - horiz_shift && c2 < coord.width;
        ++c1, ++c2)
    {
      dst.at<Vec3b>(coord.y + w, coord.x + c2) = src.at<Vec3b>(w, c1);
    }    
    for(int c2 = 0;
        c1 < src.cols - horiz_shift && c2 < coord.width;
        ++c1, ++c2)        
    {
      dst.at<Vec3b>(coord.y + w, coord.x + c2) = src.at<Vec3b>(w, c1);
    }
  }
}
