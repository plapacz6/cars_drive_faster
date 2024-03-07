#include "T_SteppeBush.h"
#include "T_GameDefs.h"
#include "T_Board.h"
#include "T_GameImages.h"
#include "T_VShiftUnit.h"
#include "PasteImgFunctions.h"

using namespace std;
namespace csfgame {

T_SteppeBush::T_SteppeBush() {
    set_beg_distance();
    set_beg_sector();
    set_end_position();
    set_if_check_end_position();
    reset();
}
// T_SteppeBush::~T_SteppeBush() {
// }

void T_SteppeBush::draw_a_new_one() {
    set_beg_distance();
    set_beg_sector();
    set_end_position();
    set_if_check_end_position();
    reset();
}
void T_SteppeBush::action() {
    coord.y += v_shift_unit.get();
    if(check_end_position) {
        if(abs(coord.x - coord_targed.x) > horizontal_step) {
            coord.x += horizontal_step;
        }
    }
    else {
        coord.x += horizontal_step;
        if( coord.x <= 0
                || coord.x > b_df.steppebush_max_distance )
        {
            processed = false;
        }
    }
    paste_img_vert_partialy(game_images.img_bush, coord, board.b);
    if(coord.y > b_df.road_hight) {
        processed = false;
    }
}

void T_SteppeBush::reset() {
    coord = b_df.calc_begin_rect_roadside(
                game_images.img_bush, beg_pos);

    coord_targed = b_df.calc_begin_rect_lane(
                       game_images.img_bush, end_pos);

    coord.y = static_cast<int>(
                  (b_df.road_hight / 6) * (distance / 100.0));

    calculate_horizontal_step();
    processed = true;
}

void T_SteppeBush::set_beg_sector(TBoardSector pos) {
    if(
        pos != TBoardSector::ANY
    ) {
        beg_pos = pos;
    }
    else {
        size_t beg_pos_idx =
            (rand() % TBoardSecor_roadside_number) + TBoardSecor_lines_number;
        assert(beg_pos_idx > 2 && beg_pos_idx < 5);
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

void T_SteppeBush::calculate_horizontal_step() {
    if(coord.x < coord_targed.x) {
        horizontal_step = b_df.horizontal_step;
    }
    else {
        horizontal_step = -b_df.horizontal_step;
    }
}

void T_SteppeBush::set_if_check_end_position(TOption opt) {
    if(opt == TOption::RANDOM) {
        check_end_position = static_cast<bool>(rand()%2);
    }
    else if(opt == TOption::YES) {
        check_end_position =  true;
    }
    else {
        check_end_position = false;
    }
}

} //namespace csfgame
