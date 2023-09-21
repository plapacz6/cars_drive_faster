
#ifndef BOARD_T_H
#define BOARD_T_H

#include "dimension.h"
#include "Rect_T.h"

/**
 * class board_T
 */

class board_T
{
public:
    /* Constructors/Destructors     */

    board_T();

    virtual ~board_T();

    /* Public attributes     */

    int player_speed[board_dim];

    Rect_T edges;

private:
};

#endif // BOARD_T_H
