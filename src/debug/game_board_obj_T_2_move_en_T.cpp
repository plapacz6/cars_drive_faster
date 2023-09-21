#include "../debug_utils.h"
#include "../dimension.h"
#include "../game_board_obj_T.h"
#include "../game_obj_T.h"
#include "../move_en_T.h"
#include "../board_T.h"

using namespace std;

board_T board;
move_en_T mv_en;

int main() {
    PDEBUG("---------------------o1");
    game_board_obj_T o1(nullptr, nullptr, board);
    PDEBUG("---------------------o2");
    game_board_obj_T o2(&mv_en, nullptr, board);
    PDEBUG("---------------------o3");
    game_board_obj_T o3(nullptr, &mv_en, board);
    PDEBUG("---------------------o4");
    game_board_obj_T o4(&mv_en, &mv_en, board);
    PDEBUG("---------------------");

    return 0;
}
