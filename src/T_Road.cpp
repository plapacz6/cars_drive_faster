#include <thread>

#include "T_Road.h"
#include "T_Board.h"
#include "T_VShiftUnit.h"
#include "T_GameMutexes.h"
#include "T_GameImages.h"
#include "PasteImgFunctions.h"


#include "pdebug.h"

using namespace std;
namespace csfgame {

T_Road::T_Road()
    : 
    line1(TBoardSector::LANE_L, LINE_DOTTED), 
    line2(TBoardSector::LANE_R, LINE_DOTTED)
{
    empty_road = cv::Mat::zeros(
                     cv::Size(
                         b_df.roadside_width * 2 + b_df.lane_width * 3,
                         b_df.road_hight),
                     CV_8UC3
                 );

    roadside_L = T_Rect(
                     0,
                     0,
                     b_df.roadside_width,
                     b_df.road_hight);
    lane_L = T_Rect(
                 b_df.roadside_width + b_df.lane_width * 0,
                 0,
                 b_df.roadside_width + b_df.lane_width * 1,
                 b_df.road_hight);
    lane_M = T_Rect(
                 b_df.roadside_width + b_df.lane_width * 1,
                 0,
                 b_df.roadside_width + b_df.lane_width * 2,
                 b_df.road_hight);
    lane_R = T_Rect(
                 b_df.roadside_width + b_df.lane_width * 2,
                 0,
                 b_df.roadside_width + b_df.lane_width * 3,
                 b_df.road_hight);
    roadside_R = T_Rect(
                     b_df.roadside_width + b_df.lane_width * 3,
                     0,
                     b_df.roadside_width * 2 + b_df.lane_width * 3,
                     b_df.road_hight);

    if(game_images.img_car1.empty()) {
        throw;  //game_images.load_images() must be call before
    }
    car1_L = T_Rect {
        b_df.roadside_width + b_df.lane_width * 0 +
        (b_df.lane_width - game_images.img_car1.cols) / 2,
        b_df.road_hight - game_images.img_car1.rows,
        game_images.img_car1.cols,
        game_images.img_car1.rows};

    car1_M = T_Rect {
        b_df.roadside_width + b_df.lane_width * 1 +
        (b_df.lane_width - game_images.img_car1.cols) / 2,
        b_df.road_hight - game_images.img_car1.rows,
        game_images.img_car1.cols,
        game_images.img_car1.rows};

    car1_R = T_Rect {
        b_df.roadside_width + b_df.lane_width * 2 +
        (b_df.lane_width - game_images.img_car1.cols) / 2,
        b_df.road_hight - game_images.img_car1.rows,
        game_images.img_car1.cols,
        game_images.img_car1.rows};

    paste_img(game_images.img_roadside, roadside_L, empty_road);
    paste_img(game_images.img_lane, lane_L, empty_road);
    paste_img(game_images.img_lane, lane_M, empty_road);
    paste_img(game_images.img_lane, lane_R, empty_road);
    paste_img(game_images.img_roadside, roadside_R, empty_road);
}

void T_Road::calculate_shift(double curr_speed) {
    PMDEBUG("calc_shift() ");
    v_shift_unit.set( static_cast<int>(       
                          (curr_speed)
                          * (b_df.time_period_ns) 
                          / 26500000) //== curr_speed * (1,245283019)
                    );   
    /*  TODO:
    
        speed * time = length
        50px == 2cm = 0,02m ->   0.01m == 25px == 1m real
        10 == 4km/h == 1.1m/s
        33000000ns == 0,033s
        --------------------------  
        0.033s -> 0.3m/s -> 25px/3 = 8.33 px
    */
    //PDEBUG_(v_shift_unit.get());
}

void T_Road:: draw() {
    int v_shift_unit_get = v_shift_unit.get();
    pthread_mutex_lock(&mtx.lock_speed_car1);
    board.b = empty_road.clone();

    v_shift_total += v_shift_unit_get;
    if(v_shift_total >  b_df.road_hight) {
        v_shift_total = v_shift_total - b_df.road_hight;
    }

    paste_img_vert_wrap(*(line1.ptr_img), line1.coord, v_shift_total,  board.b);
    paste_img_vert_wrap(*(line2.ptr_img), line2.coord, v_shift_total,  board.b);

    pthread_mutex_unlock(&mtx.lock_speed_car1);
    // PDEBUG_( game_images.img_car1.size() );
    // PDEBUG_( car1_L );
    // PDEBUG_( board.b.size() );
}

} //namespace csfgame
