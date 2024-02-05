#ifndef ROAD_H
#define ROAD_H

#include <vector>
#include "T_Rect.h"
#include "T_RoadLine.h"
#include "T_Obstacle.h"

namespace csfgame {

class T_Road {
public:
    T_Road();
    T_Road(const  T_Road&) = delete;
    virtual ~T_Road() = default;
    T_Road& operator=(const T_Road&) = delete;

    //setters and getters:
    //void set_(TTT);
    //TTT get_() const;

    void calculate_shift(double curr_speed);
    void draw();

    int v_shift_total; //total shift

    T_RoadLine line1;
    T_RoadLine line2;

    T_Rect roadside_L;
    T_Rect lane_L;
    T_Rect lane_M;
    T_Rect lane_R;
    T_Rect roadside_R;

    T_Rect car1_L;
    T_Rect car1_M;
    T_Rect car1_R;

    cv::Mat empty_road;
    cv::Mat img_roadside;

    std::vector<T_Obstacle> road_objects;

protected:
private:
};

} //namespace csfgame
#endif //ROAD_H
