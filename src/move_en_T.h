
#ifndef MOVE_EN_T_H
#define MOVE_EN_T_H

#include <vector>
#include "game_board_obj_T.h"

/**
 * class move_en_T
 */

class move_en_T
{
public:
    /* Constructors/Destructors     */

    /**
     * Empty Constructor
     */
    move_en_T();

    /**
     * Empty Destructor
     */
    virtual ~move_en_T();

    /**
     * calculates new coords all registered objects
     */
    void calculate();

    /**
     * signups one coordinate of game object to recalculate in specific period of
     * time
     * @param  o object to be registered
     * @param  speed speed of ocject in that direction
     */
    void signup(game_board_obj_T* o, int (*speed)[board_dim]);

private:
    /* Private attributes     */

    /* vector of one coordinate of each registered objects     */
    std::vector<game_board_obj_T*> gbobj;

    /* vector value of the distance that each of the registered objects jumps in one
    *  time unit
    */
    std::vector<int (*)[board_dim]> step;
};

#endif // MOVE_EN_T_H
