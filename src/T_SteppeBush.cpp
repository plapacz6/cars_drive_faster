#include "T_SteppeBush.h"
#include "T_Board.h"
#include "T_GameImages.h"
#include "PasteImgFunctions.h"

using namespace std;
namespace csfgame {
 
T_SteppeBush::T_SteppeBush() {
    set_beg_distance();
    set_beg_sector();
    set_end_position();    
    reset();
}
// T_SteppeBush::~T_SteppeBush() {
// }

void T_SteppeBush::draw_new() {
    set_beg_distance();
    set_beg_sector();
    set_end_position();    
    reset();
}
void T_SteppeBush::action() {
    //TODO: calcualte coord according to current road speed
    paste_img(game_images.img_bush, coord, board.b);
}

void T_SteppeBush::reset() {
    coord = b_df.calc_begin_rect_roadside(
        game_images.img_bush, beg_pos);

    coord_targed = b_df.calc_begin_rect_lane(
        game_images.img_bush, end_pos);

    coord.y = static_cast<int>(
        (b_df.road_hight / 2) * (distance / 100.0));        
}

void T_SteppeBush::set_beg_sector(TBoardSector pos) {
    if(
        pos != TBoardSector::ANY
    ) {
        beg_pos = pos;
    }
    else {
      size_t beg_pos_idx = rand() % TBoardSecor_sectors_number;
        assert(beg_pos_idx < 5);
        beg_pos = static_cast<TBoardSector>(beg_pos_idx); 
    }
}

void T_SteppeBush::set_beg_distance(int distance) {    
    if(distance < 0 || distance > 100) {
        distance = rand()%100;
    }
    this->distance = distance;
}

void T_SteppeBush::set_end_position(TBoardSector pos) {
    if(
        pos == TBoardSector::LANE_L ||
        pos == TBoardSector::LANE_M||
        pos == TBoardSector::LANE_R
    ) {
        end_pos = pos;
    }
    else {
        size_t beg_pos_idx = rand() % TBoardSecor_lines_number;
        assert(beg_pos_idx < 3);
        end_pos = static_cast<TBoardSector>(beg_pos_idx);            
    }
}

} //namespace csfgame
