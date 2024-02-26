#ifndef ROADLINE_H
#define ROADLINE_H

#include "T_Rect.h"
#include "TBoardSector.h"

namespace csfgame {

enum road_line_type_t {
    LINE_DOTTED
};

class T_RoadLine {
public:
    /**
    * @brief Construct a new road line T_RoadLine object
    *
    * @param lane_on_left //< (LANE_L, LANE_M)
    */
    explicit T_RoadLine(TBoardSector lane_on_left, road_line_type_t type_);
    T_RoadLine(const  T_RoadLine&) = delete;
    virtual ~T_RoadLine() = default;
    T_RoadLine& operator=(const T_RoadLine&) = delete;

    //setters and getters:
    //void set_(TTT);
    //TTT get_() const;

    void set_img(road_line_type_t type_);

    T_Rect coord; //< absolute lane position on road
    cv::Mat* ptr_img = NULL; //< line image depending on line type

    road_line_type_t type;

protected:
private:
};

} //namespace csfgame
#endif //ROADLINE_H
