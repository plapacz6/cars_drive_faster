#ifndef T_GAMEDEFS_H
#define T_GAMEDEFS_H

#include <string>
#include "T_Rect.h"
#include "TBoardSector.h"

namespace csfgame {

class T_GameDefs {
    public:
    explicit T_GameDefs();
    T_GameDefs(const  T_GameDefs&) = delete;
    virtual ~T_GameDefs() = default;
    T_GameDefs& operator=(const T_GameDefs&) = delete;

    int roadside_width;
    int lane_width;
    int road_hight;  //length of the visible part of road
    int board_width;  //== ( roadside_width * 2 + lane_width * 3 ),
    int steppebush_max_distance; // = (board_width - lane_width),
    std::string wndName;
    long time_period_ns;
    time_t time_period_s;
    long time_speed_up_ns;
    time_t time_speed_up_s;
    //double begining_speed_car1;    //moved to  T_Car
    double step_speed_up;
    //double max_speed;              //moved to T_Car
    int horizontal_step;  /*< distances tarveled horizontaly by bush in one unit time*/

    /**
     * @brief calculate coordinates of rectangle where object image
     * will be painted based on symbolic name of one of some
     * fixed positions on board (road)
     *
     * @param img image from where width and height will be taken
     * @param lane TBoardSector LANE_L LANE_R LANE_M. Other values cause assert error
     * @return T_Rect
     */
    T_Rect calc_begin_rect_lane(cv::Mat &img, TBoardSector place);

    /**
     * @brief calculates coordinates of rectangle where object image
     * will be painted based on sybolic name of one of BoardSectors
     *
     * @param img image from where width and height will be taken
     * @param place TBoardSector
     * @return T_Rect
     */
    T_Rect calc_begin_rect_roadside(cv::Mat &img, TBoardSector place);

    protected:
    private:
};

extern T_GameDefs b_df;

} //namespace csfgame
#endif //T_GAMEDEFS_H
