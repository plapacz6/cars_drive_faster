#include "debug_utils.h"
#include "move_en_T.h"
#include <vector>
#include <iterator>
using namespace std;

/* Constructors/Destructors */

move_en_T::move_en_T()
{
}

move_en_T::~move_en_T()
{
}

/* Methods */

/* Accessor methods */

/* Other methods */

/**
 * calculates new coords all signuped objects
 */
void move_en_T::calculate()
{

    //TODO: split up to seprateate thread for x and y

    vector<game_board_obj_T*>::iterator it_o;
    vector<int (*)[board_dim]>::iterator it_s;

    for(it_o = gbobj.begin(), it_s = step.begin() ;
            it_o != gbobj.end() && it_s != step.end();
            it_o++, it_s++)
    {
        for(size_t i = 0; i < board_dim; i++) {
            (*it_o)->pos_prev[i] = (*it_o)->pos[i];
        }

        for(size_t i = 0; i < board_dim; i++) {
            (*it_o)->pos[i] = (*it_o)->pos[i] + (**it_s)[i];
        }
    }
}

/**
 * signups one coordinate of game object to recalculate in specific period of
 * time
 * @param  o object's current position one coordinate
 * @param  speed speed of ocject in that direction
 */
void move_en_T::signup(game_board_obj_T* o, int (*speed)[board_dim])
{
    PDEBUG("move_en_T_signup: o     : " << o);
    PDEBUG("move_en_T_signup: speed : " << speed);

    //TODO: split up to seprateate thread for x and y

    gbobj.push_back(o);
    step.push_back(speed);
}
