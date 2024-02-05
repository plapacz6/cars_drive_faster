#ifndef STEPPEBUSH_H
#define STEPPEBUSH_H

#include "T_Obstacle.h"

namespace csfgame {

class T_SteppeBush : T_Obstacle {
public:
    explicit T_SteppeBush();
    T_SteppeBush(const  T_SteppeBush&) = default;
    virtual ~T_SteppeBush() = default;
    T_SteppeBush& operator=(const T_SteppeBush&) = default;

    void draw_new();
    void action();
    void reset();
    T_Rect coord_targed;  /*< target coordinates */
    //Rect coord;       /*< inheritedcurrent coordinates */

    /**
     * @brief Set the beg position of StepperBush
     *
     * @param pos TBoardSector::ANY, ROADSIDE_L, ROADSIDE_R
     */
    void set_beg_sector(TBoardSector pos = TBoardSector::ANY);

    /**
     * @brief Set the beg distance of StepperBush
     *
     * @param distance int 0-100 % of the more distant half of the road
     */
    void set_beg_distance(int distance = 50);

    /**
     * @brief Set the end position of StepperBush
     *
     * @param pos TBoardSector::ANY, LANE_L, LANE_M, LANE_R
     */
    void set_end_position(TBoardSector pos = TBoardSector::ANY);

    TBoardSector beg_pos; /*< beginning sector of board for StepperBush obj*/
    TBoardSector end_pos; /*< ending line sector of board for StepperBush obj*/
    int distance;         /*< beginnig distance of StepperBush obj from player
                            int percent of the more distanct half of the road */
protected:
private:
};

} //namespace csfgame
#endif //STEPPEBUSH_H
