#include "game_colidable_obj_T.h"
#include "debug_utils.h"

/* Constructors/Destructors */

game_colidable_obj_T::game_colidable_obj_T(
    move_en_T* mv_player_en,
    move_en_T* mv_obj_en,
    board_T& board,
    game_obj_category_T category_
) :
    game_board_obj_T(
        move_en_T* mv_player_en,
        move_en_T* mv_obj_en,
        board_T board
    ),
    category {category_}
{
    PDEBUG("game_colidable_obj_T: destructor");
}

game_colidable_obj_T::~game_colidable_obj_T(
{
    PDEBUG("game_colidable_obj_T: destructor");
}

/* Methods */

/* Accessor methods */

/* Other methods */
