#ifndef CAR1_H
#define CAR1_H

#include "T_Rect.h"
#include "TBoardSector.h"
#include "T_Car.h"
#include "T_Road.h"

namespace csfgame {

/**
 * @brief players car
 *
 */
class T_Car1 : public T_Car {
public:
    T_Car1(T_Road& road_, TBoardSector begin_pos_, double speed_ = beginnig_speed);
    T_Car1(const  T_Car1&) = delete;
    virtual ~T_Car1() = default;
    T_Car1& operator=(const T_Car1&) = delete;

    void action();
    T_Road& road;
    double speed;

    T_Rect *ptr_coord;         /*< current coordinates on board (fixed 3 places) */


    //class speed_car1_t { //TODO
    double speed_car1;
    void zeros_speed();
    double get_speed();
    void set_speed(double&& speed_car1_);
    void to_right();
    void to_left();

protected:
private:
};

} //namespace csfgame
#endif //CAR1_H
