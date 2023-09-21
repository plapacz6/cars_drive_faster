#include "game_board_obj_T.h"
#include "debug_utils.h"
#include "move_en_T.h"
#include "board_T.h"

/* Constructors/Destructors */

game_board_obj_T::game_board_obj_T(
    move_en_T *mv_player_en,
    move_en_T *mv_obj_en,
    board_T& board
) :  speed {0, 0}, present {true}
{
    PDEBUG("game_board_obj_T: constructor");
    if(mv_player_en) {
        PDEBUG("game_board_obj_T_constructor: player_speed : " << &board.player_speed);
        mv_player_en->signup(this, &board.player_speed);
    }
    if(mv_obj_en) {
        mv_obj_en->signup(this, &speed);
    }
}

game_board_obj_T::~game_board_obj_T()
{
    PDEBUG("game_board_obj_T: destructor");
}

/* Methods */

/* Accessor methods */

/* Other methods */
