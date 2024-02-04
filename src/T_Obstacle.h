#ifndef OBSTACLE_H
#define OBSTACLE_H
#include "T_Rect.h"
#include "TBoardSector.h"

namespace csfgame {

class T_Obstacle {
public:
    explicit T_Obstacle();
    explicit T_Obstacle(const  T_Obstacle&) = default;
    virtual ~T_Obstacle() = default;
    T_Obstacle& operator=(const T_Obstacle&) = default;

    T_Rect coord;         //< current coordinates
    virtual void reset() = 0;
    virtual void action() = 0;
    bool processed;
protected:
private:
};

} //namespace csfgame
#endif //OBSTACLE_H
