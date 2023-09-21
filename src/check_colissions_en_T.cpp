#include "check_colissions_en_T.h"

/* Constructors/Destructors */

check_colissions_en_T::check_colissions_en_T()
{
    initAttributes();
}

check_colissions_en_T::~check_colissions_en_T()
{
}

/* Methods */

/* Accessor methods */

/* Other methods */

/**
 * checking for objects colissions
 * and when collission is detected runnig signupd calback based on colided
 * objects
 * @param  so striking item
 * @param  ho hit object
 */
void check_colissions_en_T::check_collisions_and_execute(game_colidable_obj_T* so, game_colidable_obj_T* ho)
{
}

/**
 * regiters selected collisons to check if occured and action to perform
 * @param  o1
 * @param  o2
 * @param  o1_to_o2_in_out actrion pefromed when o1 enter into area of o2 (IN)
 * or leave (OUT)
 * @param  action void action(&o1, &o2)
 */
void check_colissions_en_T::signup_collision_to_check(game_colidable_obj_T* o1, game_colidable_obj_T* o2, enum_IN_OUT o1_to_o2_in_out, nowa_klasa_1 action)
{
}

void check_colissions_en_T::initAttributes()
{
}
