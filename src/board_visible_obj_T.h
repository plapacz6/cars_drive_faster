
#ifndef BOARD_VISIBLE_OBJ_T_H
#define BOARD_VISIBLE_OBJ_T_H

/**
 * class board_visible_obj_T
 * class board_visible_obj_T
 * class board_visible_obj_T
 *
 */

class board_visible_obj_T
{
public:
    /* Constructors/Destructors     */

    /**
     * Empty Constructor
     */
    board_visible_obj_T();

    /**
     * Empty Destructor
     */
    virtual ~board_visible_obj_T();

    /* Public attributes     */

    undef img;
    Rect_T pos;

    /**
     */
    void draw();

private:
    /**
     */
    void initAttributes();

    void initAttributes();

};

#endif // BOARD_VISIBLE_OBJ_T_H
