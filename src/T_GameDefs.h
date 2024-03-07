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
    int horizontal_step;  /**< distances tarveled horizontaly by bush in one unit time*/

    std::string wndName;

    long time_period_ns;
    time_t time_period_s;
    long time_speed_up_ns;
    time_t time_speed_up_s;
                    
    double const car1_step_speed_up;
    double const car_max_speed;        /**< max speed of each car*/
    double const car_beginnig_speed;   /**< beginnig speed of each car*/

    //TODO  - calculate in compile time : //ARYTMINT
    /* //TODO: Internal unit of speed:   mm/sec  ???   mm/one_frame_period ?
    shirt speed to mm allow perhaps to move to int aritmetic for speed
    and perhaps bitshifting by <<6 may be similiar to *1000 and further back to px >>6
    */
    // double const Icar_max_speed;       /**< car_max_speed in game Interal units*/
    // double const Icar_beginnig_speed;  /**< car_beginnig_speed in game Internal units*/

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
