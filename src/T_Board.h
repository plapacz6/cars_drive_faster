#ifndef T_BOARD_H
#define T_BOARD_H

#include <string>
#include "T_Rect.h"
#include "TBoardSector.h"


namespace csfgame {

struct board_def_t {
    int roadside_width;
    int lane_width;
    int road_hight;  //length of the visible part of road
    const std::string& wndName;
    long time_period_ns;
    time_t time_period_s;
    long time_speed_up_ns;
    time_t time_speed_up_s;
    //double begining_speed_car1;
    double step_speed_up;
    //double max_speed;

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
};

//-----------------------------------------

/**
 * @brief game board
 *
 */
class T_Board {
public:
    T_Board();
    T_Board(const  T_Board&) = delete;
    virtual ~T_Board() = default;
    T_Board& operator=(const T_Board&) = delete;

    //setters and getters:
    //void set_(TTT);
    //TTT get_() const;

    void show();
    void load_images();

    cv::Mat b;

protected:
private:
};

extern board_def_t b_df;
extern T_Board board;

} //namespace csfgame
#endif //T_BOARD_H
