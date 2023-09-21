
#ifndef GAME_COLIDABLE_OBJ_T_H
#define GAME_COLIDABLE_OBJ_T_H

#include "game_board_obj_T.h"
#include "game_obj_T.h"
#include "game_obj_category_T.h"

/**
 * class game_colidable_obj_T
 */

class game_colidable_obj_T : public game_board_obj_T
{
public:
    /* Constructors/Destructors     */

    game_colidable_obj_T(
        move_en_T* mv_player_en,
        move_en_T* mv_obj_en,
        board_T& board,
        game_obj_category_T category_
    );

    virtual ~game_colidable_obj_T();

    /* Public attributes     */

    /* car, hole, bush, line, sidewalk, ...     */
    game_obj_category_T category;

private:
    /* Private attributes     */
};

#endif // GAME_COLIDABLE_OBJ_T_H
