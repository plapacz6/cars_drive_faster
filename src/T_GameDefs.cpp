#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "T_GameDefs.h"

using namespace std;
using namespace cv;
namespace csfgame {

T_GameDefs b_df;

T_GameDefs::T_GameDefs()
    : wndName {"cars - higher speed"}
{
    roadside_width = 200;
    lane_width = 75;
    road_hight = 500;
    board_width = ( roadside_width * 2 + lane_width * 3 );
    steppebush_max_distance = (board_width - lane_width);
    time_period_ns = 33000000;  //ms
    time_period_s = 0;
    time_speed_up_ns = 1000000000;
    time_speed_up_s = 0;
    step_speed_up = 20; //0.4,      //ARYTMINT
    horizontal_step = 20;  /*< distances tarveled horizontaly by bush in one unit time*/
}

T_Rect T_GameDefs::calc_begin_rect_lane(Mat &img, TBoardSector place) {
    assert(static_cast<size_t>(place) < 3);
    int lane;
    if(place == TBoardSector::LANE_L) {
        lane = 0;
    }
    else if(place == TBoardSector::LANE_R) {
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

T_Rect T_GameDefs::calc_begin_rect_roadside(Mat &img, TBoardSector place) {
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

} //namespace csfgame
