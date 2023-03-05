#ifndef GAME_VISIBLE_OBJ_T_H
#define GAME_VISIBLE_OBJ_T_H

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>

#include <time.h>  //clock_nanosleep()
#include <unistd.h>

#include <thread>

#include "paste_img.h"
#include "calc_v_shift.h"




class GameMovableObj_T{
  friend class coordMovingObj_T;
  public:
  
    cv::Rect co;   /**< Coordinates of object*/
    int vspeed; /**< vertical speed */
    int hspeed; /**< horisontal speed*/
};

class GameMovablePrepositionedObj_T : public GameMovableObj_T {
  public:
    std::vector<cv::Rect> dft; /**< set of default positions*/
    void setPos()
};

class GameVisibleObj_T {  
  public:
    cv::Mat img;
    cv::Mat *img_ptr;    
    cv::Rect img_co;    
    virtual void emplace(cv::Mat &dst) = 0;
};

class GameVAnimatedObj_T : public GameVisibleObj_T{
  public:        
    int vspeed;
    int vshift;
    virtual void emplace(cv::Mat& dst){
      paste_img_vert_wrap(*img_ptr, img_co, vshift, dst);
    }
};

class GameHAnimatedObj_T : public GameVisibleObj_T{
  public:        
    int hspeed;
    int hshift;
    virtual void emplace(cv::Mat& dst){
      paste_img_horiz_wrap(*img_ptr, img_co, hshift, dst);
    }
};

class GameHVAnimatedObj_T : public GameVAnimatedObj_T, public GameHAnimatedObj_T{
  friend class coordHVAnimatedObj_T;
  public:    
    virtual void emplace(cv::Mat& dst){     
    }  
};


class GameNoAnimatedObj_T : public GameVisibleObj_T{
  public:
    void emplace(cv::Mat& dst){
      //paste_img(*img_ptr, img_co, dst);
      paste_img_vert_partialy(*img_ptr, img_co, dst);
    }  
};

#endif // GAME_VISIBLE_OBJ_T_H