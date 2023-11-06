
#ifndef GAME_BOARD_OBJ_T_H
#define GAME_BOARD_OBJ_T_H

#include <vector>
#include "debug_view_T.h"

#include "dimension.h"
#include "game_obj_T.h"
//#include "board_T.h"

class move_en_T;
class board_T;

/**
 * class game_board_obj_T
 * object present on the board
 */

class game_board_obj_T
    : public game_obj_T, public debug_view_T
{
public:
    /* Constructors/Destructors     */

    /**
     *
     * @param mv_player_en  Calculates object coordinates based on player movement
     *                      if nullptr object won't be signuped in player move engine
     * @param mv_obj_en  Calculates the coordinates of an object based on the object's own motion
     *                   if nullptr object won't be movable object
     */
    game_board_obj_T(
        move_en_T *mv_player_en,
        move_en_T *mv_obj_en,
        board_T& board
    );

    virtual ~game_board_obj_T();

    /* Public attributes     */

    /* if object is present on the board     */
    bool present;

    /* game object's own speed  [0] - x, [1] - y   */
    int speed[board_dim];
    /* previous pos
     * updated for game_vm_obj_T by move_en_T class
     * purpose: for colision checking function and cross boundary function     */

    /**
     * @brief
     * TODO: co ma aktualizowac to pos_prev ?
     * kiedy to ma sie dziac ?
     * bo jesli camera view jest przeliczane po kolizjach
     * to aktualizacja w camera view (zeby tez dla statycznych obiektow bylo)
     * skasuje poprawki wprowadzone w kolizach.
     *
     */
    //Rect_T pos_prev;
    int pos_prev[board_dim * 2];

private:
    /* Private attributes     */
};

#endif // GAME_BOARD_OBJ_T_H
