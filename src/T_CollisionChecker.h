#ifndef T_COLLISIONCHECKER_H
#define T_COLLISIONCHECKER_H

#include "T_Car1.h"
#include "T_Obstacle.h"
#include "T_Car2.h"
#include "T_RoadHole.h"
#include "T_SteppeBush.h"

namespace csfgame {

class T_CollisionChecker {
public:
    T_CollisionChecker(T_Car1 * ptr_car1);
    T_CollisionChecker(const  T_CollisionChecker&) = delete;
    virtual ~T_CollisionChecker() = default;
    T_CollisionChecker& operator=(const T_CollisionChecker&) = delete;

    //setters and getters:
    //void set_(TTT);
    //TTT get_() const;

    bool with_hole(T_Obstacle *ptr_obj);
    bool with_car2(T_Obstacle *ptr_obj);

    T_Car1 * ptr_car1;

protected:
private:
};

} //namespace csfgame
#endif //T_COLLISIONCHECKER_H
