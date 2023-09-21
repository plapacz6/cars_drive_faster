
#ifndef RECT_T_H
#define RECT_T_H

/**
 * class Rect_T
 */

class Rect_T
{
public:
    /* Constructors/Destructors     */

    /**
     * Empty Constructor
     */
    Rect_T();

    /**
     * Empty Destructor
     */
    virtual ~Rect_T();

    int x;
    int y;
    int w;
    int h;
};

#endif // RECT_T_H
