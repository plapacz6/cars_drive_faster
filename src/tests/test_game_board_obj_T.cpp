#include <catch2/catch_all.hpp>
#include "../debug_utils.h"
#include "../dimension.h"
#include "../game_board_obj_T.h"
#include "../game_obj_T.h"
//#include "../move_en_T.h"
#include "../board_T.h"

// #include <iostream>
#include <vector>

using namespace std;

/**
 * @brief mocking class for move_en_T
 * difference is that vectors gbobj i step are public
 * letting access to it in tests
 */
class move_en_T {
public:
    vector<game_board_obj_T*> gbobj;
    vector<int (*)[board_dim]> step;
    void signup(game_board_obj_T* o, int (*speed)[board_dim]);
};
void move_en_T::signup(game_board_obj_T* o, int (*speed)[board_dim]) {
    gbobj.push_back(o);
    step.push_back(speed);
}

// class board_T {
/*
For some reason this mocking class don't work as original.
player_speed addres changes during passing it to signup
function of move_en_T.
Original obiekct work well.
*/
//     public:
//     int player_speed[board_dim];
//     board_T(){
//         for(size_t i = 0; i < board_dim; i++){
//             player_speed[i] = i * 10;
//         }
//         PDEBUG("board_T_constructor: player_speed" << &player_speed);
//     }
//     ~board_T(){
//     }
// };

TEST_CASE("creating and signuping game_board_obj_T object in move_en_T") {

    board_T board;
    move_en_T mv_en_01;

    game_board_obj_T o1(&mv_en_01, nullptr, board);
    REQUIRE(mv_en_01.gbobj[0] == &o1);
    REQUIRE(mv_en_01.step[0] == &board.player_speed);
    REQUIRE(mv_en_01.gbobj.size() == 1);
    REQUIRE(mv_en_01.step.size() == 1);

    game_board_obj_T o2(&mv_en_01, &mv_en_01, board);
    REQUIRE(mv_en_01.gbobj[1] == &o2);
    REQUIRE(mv_en_01.step[1] == &board.player_speed);
    REQUIRE(mv_en_01.gbobj[2] == &o2);
    REQUIRE(mv_en_01.step[2] == &o2.speed);
    REQUIRE(mv_en_01.gbobj.size() == 3);
    REQUIRE(mv_en_01.step.size() == 3);

    game_board_obj_T o3(nullptr, &mv_en_01, board);
    REQUIRE(mv_en_01.gbobj[3] == &o3);
    REQUIRE(mv_en_01.step[3] == &o3.speed);
    REQUIRE(mv_en_01.gbobj.size() == 4);
    REQUIRE(mv_en_01.step.size() == 4);

};