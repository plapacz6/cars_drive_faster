#include <cassert>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "T_Board.h"

using namespace std;
using namespace cv;
namespace csfgame {

// int roadside_width;
// int lane_width;
// int road_hight;  //length of the visible part of road
// const string& wndName;
// long time_period_ns;
// time_t time_period_s;
// long time_speed_up_ns;
// time_t time_speed_up_s;
// double begining_speed_car1;
// double step_speed_up;
// double max_speed;
board_def_t b_df = {
    .roadside_width = 200,
    .lane_width = 75,
    .road_hight = 500,
    .wndName = "cars - higher speed",
    .time_period_ns = 33000000,  //ms
    .time_period_s = 0,
    .time_speed_up_ns = 1000000000,
    .time_speed_up_s = 0,
    //.begining_speed_car1= 0.1,    //now in T_Car class
    .step_speed_up = 0.4,
    //.max_speed = 35.0             //now in T_Car class
};

T_Rect board_def_t::calc_begin_rect_lane(Mat &img, TBoardSector place) {
    assert(static_cast<size_t>(place) < 3);
    int lane;
    if(place == TBoardSector::LANE_L) {        
        lane = 0;
    }
    else
    if(place == TBoardSector::LANE_R) {        
        lane = 2;
    }    
    else {
        lane = 1;
    }
    return T_Rect(
               roadside_width + lane_width * lane +
               (lane_width - img.cols) / 2,
               0,
               img.cols,
               img.rows
           );
}

T_Rect board_def_t::calc_begin_rect_roadside(Mat &img, TBoardSector place) {
    assert(static_cast<size_t>(place) > 2 && static_cast<size_t>(place) < 5);
    int roadside;
    int lane;
    if(place == TBoardSector::ROADSIDE_L) {
        roadside = 0;
        lane = 0;
    }
    if(place == TBoardSector::ROADSIDE_R) {
        roadside = 1;
        lane = 3;
    }
    return T_Rect(
               roadside_width * roadside + lane_width * lane +
               (roadside_width - img.cols) / 2,
               0,
               img.cols,
               img.rows
           );
}

//-----------------------------------------

T_Board board;

T_Board::T_Board() {
    b = cv::Mat(
            b_df.road_hight,
            b_df.roadside_width * 2 + b_df.lane_width * 3,
            CV_8UC3
        );
}

//T_Board::~T_Board() override { }

//setters and getters:
//void T_Board::set_(TTT) { }
//TTT T_Board::get_() const { }

void T_Board:: show() {
    cv::imshow(b_df.wndName, b);
}

} //namespace csfgame
