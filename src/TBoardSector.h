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

// public:
//     static size_t get_uint(TBoardSector v);
//     static TBoardSector get_BoardSector(size_t i);
//     static TBoardSector get_BoardLine(size_t i);
//     static size_t size();
//     static size_t lines_number();
//     static size_t get_LineIdx(TBoardSector l);
};

// static size_t TBoardSector::get_uint(TBoardSector v);
// static TBoardSector TBoardSector::get_BoardSector(size_t i);
// static TBoardSector TBoardSector::get_BoardLine(size_t i);
// static size_t TBoardSector::size();
// static size_t TBoardSector::lines_number();
// static size_t TBoardSector::get_LineIdx(TBoardSector l);

} //namespace csfgame
#endif //TBOARDSECTOR_H
