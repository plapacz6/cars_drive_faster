#ifndef T_BOARD_H
#define T_BOARD_H

#include <string>
#include "T_Rect.h"
#include "TBoardSector.h"

namespace csfgame {

/**
 * @brief game board
 *
 */
class T_Board {
public:
    T_Board();
    T_Board(const  T_Board&) = delete;
    virtual ~T_Board() = default;
    T_Board& operator=(const T_Board&) = delete;

    /**
     * @brief Shows boad in the game window.
     * 
     */
    void show();
    void load_images();

    cv::Mat b;

protected:
private:
};

extern T_Board board;

} //namespace csfgame
#endif //T_BOARD_H
