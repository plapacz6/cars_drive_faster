#ifndef DIMENTION_H
#define DIMENTION_H
#include <cstdlib>
enum class DIMENTION : long unsigned int {
    /*
    0 -> x  (horisontal, left to right)
    1 -> y  (vertical, bottom to up)
    */
    DIM = 2
};
constexpr long unsigned int board_dim = 2;
constexpr size_t dim_x = 0;
constexpr size_t dim_y = 1;
constexpr size_t dim_z = 2;
#endif // DIMENTION_H