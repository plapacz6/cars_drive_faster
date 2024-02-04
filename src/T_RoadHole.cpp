#include "T_RoadHole.h"
#include "T_Board.h"
#include "T_GameImages.h"
#include "T_VShiftUnit.h"
#include "PasteImgFunctions.h"

using namespace std;
namespace csfgame {

T_RoadHole::T_RoadHole() {
    set_beg_position();
    reset();
}

// T_RoadHole::~T_RoadHole() {
// }

void T_RoadHole::reset() {
    coord = b_df.calc_begin_rect_lane(game_images.img_hole, beg_pos);
    coord.y -= game_images.img_hole.rows;
    processed = true;
}

void T_RoadHole::action() {
    coord.y += v_shift_unit.get();
    paste_img_vert_partialy(game_images.img_hole, coord, board.b);
    if(coord.y > b_df.road_hight) {
        processed = false;
    }
}

void T_RoadHole::set_beg_position(TBoardSector pos) {
    if(
        pos == TBoardSector::LANE_L ||
        pos == TBoardSector::LANE_M||
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

} //namespace csfgame
