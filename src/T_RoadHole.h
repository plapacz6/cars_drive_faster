#ifndef ROADHOLE_H
#define ROADHOLE_H

#include "T_Obstacle.h"

namespace csfgame {

class T_RoadHole : public T_Obstacle {
public:
    explicit T_RoadHole();
    explicit T_RoadHole(const  T_RoadHole&) = delete;
    virtual ~T_RoadHole() = default;
    T_RoadHole& operator=(const T_RoadHole&) = delete;

    void draw_new();
    void action();
    void reset();

    /**
     * @brief Set the beg position object
     *
     * @param pos TBoardSector::ANY, LANE_L, LANE_M, LANE_R
     */
    void set_beg_position(TBoardSector pos = TBoardSector::ANY);

    TBoardSector beg_pos; /*!< beginning sector of board for RoadHole obj*/
    //Rect coord;         /*< inherited current coordinates */

protected:
private:
};

} //namespace csfgame
#endif //ROADHOLE_H
