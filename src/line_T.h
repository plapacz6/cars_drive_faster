
#ifndef LINE_T_H
#define LINE_T_H

/**
 * class line_T
 * class line_T
 * class line_T
 *
 */

class line_T
{
public:
    /* Constructors/Destructors     */

    /**
     * Empty Constructor
     */
    line_T();

    /**
     * Empty Destructor
     */
    virtual ~line_T();

    /* Public attributes     */

    int x1;
    int y1;
    int x2;
    int y2;

    /**
     * check if point lay on the line
     * @param  p
     * @param  p
     * @param  p
     */
    void is_on(point_T p);

    /**
     * check if point is near the line on the specified side and specified distance
     * @param  p
     * @param  distance length of the perpendicular segment between the line and the
     * point
     *
     * < 0 - left side of line
     * > 0 - right side of line
     * 0 - point lay on the line
     * @param  p
     * @param  distance
     * @param  p
     * @param  distance
     */
    void is_near(point_T p, int distance);

private:
    /**
     */
    void initAttributes();

    void initAttributes();

};

#endif // LINE_T_H
