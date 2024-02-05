#ifndef CAR2_H
#define CAR2_H

#include "T_Obstacle.h"
#include "T_Car.h"

namespace csfgame {

class T_Car2 : public T_Obstacle, public T_Car {
public:
    explicit T_Car2();
    explicit T_Car2(const  T_Car2&) = default;
    virtual ~T_Car2() = default;
    T_Car2& operator=(const T_Car2&) = default;

    void draw_new();
    void reset();
    void action();

    TBoardSector beg_pos;  /*< beginnig position*/
    double speed;          /*< beginning speed (chagnes during collision)*/
    //Rect coord;          /*< inherited current coordinates */

    /**
     * @brief Set the beg position object
     *
     * @param pos TBoardSector::ANY, LANE_L, LANE_M, LANE_R
     */
    void set_beg_position(TBoardSector pos = TBoardSector::ANY);

    /**
     * @brief Set the beg speed object
     *
     * @param speed double  (0 means draw new speed)
     */
    void set_beg_speed(double speed = 0);

protected:
private:
};

} //namespace csfgame
#endif //CAR2_H
