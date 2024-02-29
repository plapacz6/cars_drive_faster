#include "T_Car2.h"
#include "T_GameDefs.h"
#include "T_Board.h"
#include "T_GameImages.h"
#include "T_VShiftUnit.h"
#include "PasteImgFunctions.h"
#include "pdebug.h"

using namespace std;
namespace csfgame {

T_Car2::T_Car2() {
    set_beg_position();
    set_beg_speed();
    reset();
}

void T_Car2::reset() {
    coord = b_df.calc_begin_rect_lane(game_images.img_car2, beg_pos);
    coord.y -= game_images.img_car2.rows;
    processed = true;
}

void T_Car2::draw_a_new_one() {
    set_beg_position();
    set_beg_speed();
    reset();
}

void T_Car2::action() {
    coord.y += v_shift_unit.get();
    coord.y -= speed * ((b_df.time_period_ns ) / 26500000);  //ARYTMINT
    paste_img_vert_partialy(game_images.img_car2, coord, board.b);
    if(coord.y > b_df.road_hight) {
        processed = false;
    }
}
void T_Car2::set_beg_position(TBoardSector pos) {
    if(
        pos == TBoardSector::LANE_L ||
        pos == TBoardSector::LANE_M ||
        pos == TBoardSector::LANE_R
    ) {
        beg_pos = pos;
    }
    else {
        size_t beg_pos_idx = rand() % TBoardSecor_lines_number;
        assert(beg_pos_idx < 3);
        beg_pos = static_cast<TBoardSector>(beg_pos_idx);
    }
}

void T_Car2::set_beg_speed(double speed) {
    if(speed != 0) {
        this->speed = speed;
    }
    else {
        /*
        T_Car2 is initially on a visible part of the road,
        so if its speed will be much greater than the speed of T_Car1
        it will never be visible because T_Car1 will never catch up with it
        */
        this->speed = (rand()%(static_cast<int>(max_speed/10) * 100))/100.0;
        //ARYTMINT
    }
}

} //namespace csfgame
