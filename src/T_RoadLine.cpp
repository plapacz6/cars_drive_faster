#include "T_RoadLine.h"
#include "T_Board.h"
#include "T_GameImages.h"
#include "PasteImgFunctions.h"


using namespace std;
namespace csfgame {

T_RoadLine::T_RoadLine(TBoardSector lane_on_left, road_line_type_t type_) {
    CV_Assert(
        static_cast<size_t>(lane_on_left) < 3 &&
        static_cast<size_t>(lane_on_left) >= 0);

    int line_half_width;
    type = type_;
    set_img(type_);
    line_half_width = ptr_img->cols / 2;

    coord = T_Rect(
                b_df.roadside_width + (
                    lane_on_left == TBoardSector::LANE_L
                    ? b_df.lane_width * 1 //static_cast<int>(lane_on_left) -
                    : b_df.lane_width * 2 //static_cast<int>(lane_on_left) -
                ) - line_half_width,
                0,  //y, row0
                ptr_img->cols, //width
                ptr_img->rows  //hight
            );
}
// T_RoadLine::~T_RoadLine() override { }

//setters and getters:
// void T_RoadLine::set_(TTT) {}
// TTT T_RoadLine::get_() const {}

void T_RoadLine::set_img(road_line_type_t type_) {
    type = type_;
    //if(type == LINE_DOTTED)
    ptr_img = &game_images.img_lane_dotted;
}

} //namespace csfgame
