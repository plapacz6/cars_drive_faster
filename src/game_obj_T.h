
#ifndef GAME_OBJ_T_H
#define GAME_OBJ_T_H

#include "dimension.h"
#include "Rect_T.h"

/**
 * class game_obj_T
 */

class game_obj_T
{
public:
    /* Constructors/Destructors     */
    game_obj_T();
    virtual ~game_obj_T();

    /* Public attributes     */
    //Rect_T pos;
    int pos[board_dim * 2];

private:
};

#endif // GAME_OBJ_T_H
