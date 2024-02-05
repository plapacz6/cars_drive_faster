#ifndef TBOARDSECTOR_H
#define TBOARDSECTOR_H

#include <cstdlib>

namespace csfgame {


enum lane_t {   //for road_t::def_rect()
    IDX_LANE_L = 0,
    IDX_LANE_M = 1,
    IDX_LANE_R = 2
};

// enum pos_t {
//     LANE_L = 0,
//     LANE_M = 1,
//     LANE_R = 2,
//     ROADSIDE_L = 3,
//     ROADSIDE_R = 4,
//     POS_NOT_EXISTING = 5
// };

constexpr size_t TBoardSecor_lines_number = 3;
constexpr size_t TBoardSecor_sectors_number = 5;

enum class TBoardSector : size_t {
    LANE_L = 0,
    LANE_M = 1,
    LANE_R = 2,
    ROADSIDE_L = 3,
    ROADSIDE_R = 4,
    ANY = 5
};

} //namespace csfgame
#endif //TBOARDSECTOR_H
