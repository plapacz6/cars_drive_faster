#ifndef T_VSHIFTUNIT_H
#define T_VSHIFTUNIT_H

#include <thread>
#include "T_GameMutexes.h"

namespace csfgame {

/**
 * @brief Stores size of one step in movement objects on board
 * calcuates in other place according to current speed of player.
 * Because this variable is accessed by more than one thread
 * it is wrapped int that class co synchronize access.
 */
class T_VShiftUnit {
public:
    T_VShiftUnit() {
        pthread_mutex_lock(&mtx.lock_speed_car1);
        pthread_mutex_lock(&mtx.lock_v_shift_unit);
        v_shift_unit = 0;
        pthread_mutex_unlock(&mtx.lock_v_shift_unit);
        pthread_mutex_unlock(&mtx.lock_speed_car1);
    };
    T_VShiftUnit(const  T_VShiftUnit&) = delete;
    virtual ~T_VShiftUnit() = default;
    T_VShiftUnit& operator=(const T_VShiftUnit&) = delete;

    int v_shift_unit;  /*< unit shift calculated based on car1 speed, and prev coord_shift */

    //setters and getters:

    inline int get() {
        int v_shift_unit_;
        //cout << "v_shift_u.get() " << endl;
        pthread_mutex_lock(&mtx.lock_speed_car1);
        pthread_mutex_lock(&mtx.lock_v_shift_unit);
        v_shift_unit_ =  v_shift_unit;
        pthread_mutex_unlock(&mtx.lock_v_shift_unit);
        pthread_mutex_unlock(&mtx.lock_speed_car1);
        return v_shift_unit_;
    }

    inline void set(int v_shift_unit_) {
        //cout << "v_shift_u.set() " << endl;
        pthread_mutex_lock(&mtx.lock_speed_car1);
        pthread_mutex_lock(&mtx.lock_v_shift_unit);
        v_shift_unit = v_shift_unit_;
        pthread_mutex_unlock(&mtx.lock_v_shift_unit);
        pthread_mutex_unlock(&mtx.lock_speed_car1);
    }

protected:
private:
};

extern T_VShiftUnit v_shift_unit;

} //namespace csfgame
#endif //T_VSHIFTUNIT_H
