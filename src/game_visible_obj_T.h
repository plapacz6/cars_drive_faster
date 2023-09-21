
#ifndef GAME_VISIBLE_OBJ_T_H
#define GAME_VISIBLE_OBJ_T_H

#include "game_board_obj_T.h"
#include "game_board_obj_T.h"
#include "game_board_obj_T.h"
#include "game_board_obj_T.h"
#include "game_board_obj_T.h"
#include "game_obj_T.h"

/**
 * class game_visible_obj_T
 * class game_visible_obj_T
 * class game_visible_obj_T
 *
 */

class game_visible_obj_T : public game_board_obj_T, public game_board_obj_T, public game_board_obj_T, public game_board_obj_T, public game_board_obj_T, public game_obj_T
{
public:
    /* Constructors/Destructors     */

    /**
     * Empty Constructor
     */
    game_visible_obj_T();

    /**
     * Empty Destructor
     */
    virtual ~game_visible_obj_T();

    /**
     * draw object on the board
     */
    void draw();

private:
    /* Private attributes     */

    undef img;

    /**
     */
    void initAttributes();

    void initAttributes();

};

#endif // GAME_VISIBLE_OBJ_T_H
