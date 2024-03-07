#include <cassert>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "T_Board.h"
#include "T_GameDefs.h"

using namespace std;
using namespace cv;
namespace csfgame {

T_Board board;

T_Board::T_Board() {
    b = cv::Mat(
            b_df.road_hight,
            b_df.board_width,
            CV_8UC3
        );
}

void T_Board:: show() {
    cv::imshow(b_df.wndName, b);
}

} //namespace csfgame
