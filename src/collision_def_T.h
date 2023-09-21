
#ifndef COLLISION_DEF_T_H
#define COLLISION_DEF_T_H

#include wektor

/**
 * class collision_def_T
 */

class collision_def_T
{
public:
    /* Constructors/Destructors     */

    /**
     * Empty Constructor
     */
    collision_def_T();

    /**
     * Empty Destructor
     */
    virtual ~collision_def_T();

    /* Public attributes     */

    int edge_o1;
    /* action performed when     */
    int edge_o2;
    undef action;

private:
    /* Private attributes     */

    /* action pefromed when edge_o1 - edge_o2 = direction
     *
     * void action(gama_colidable_obj_T* o1, game_colidable_obj_T* o2);
     *
     * edge_o1 and edge_o2 is filled during registration of action. Then is state     */
    * whitch edge of ocject must be compared, to fullfill relation.
    game_colidable_obj_T* o1;
    game_colidable_obj_T* o2;
    enum_COMPARISON direction;

    void initAttributes();

};

#endif // COLLISION_DEF_T_H
