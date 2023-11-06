#include <cstdbool>
#include <iostream>
#include <catch2/catch_all.hpp>

#include "../board_T.h"
#include "../game_board_obj_T.h"
#include "../move_en_T.h"

using namespace std;

board_T board;
move_en_T move_en1;
TEST_CASE("Create obj move_en_T") {
    move_en_T move_en2;
    move_en_T* pmove_en3 = new move_en_T;

    game_board_obj_T o1(&move_en1, &move_en2, board);
    game_board_obj_T o2(&move_en1, pmove_en3, board);

    if(pmove_en3) {
        delete pmove_en3;
    }
    //REQUIRE(==)
};
TEST_CASE("Calculate coordinates registerd game_board_obj") {

    struct tested_data_obj_definition_T {
        game_board_obj_T* o;
        bool player_move_en;
        bool obj_move_en;
        int obj_size_initial;
        int obj_size_step;
        int obj_pos_initial;
        int obj_pos_step;
        int obj_speed_initial;
        int obj_speed_step;
        int obj_size_random_step;
        int obj_pos_random_step;
        int obj_speed_random_step;
    } test_definition[] = {
        {   //obj nr 1
            nullptr,
            true,   //player move en present
            false,  //obj move en prestnt
            10, 0, //obj size,  step (10 == random)
            10, 1, //obj pos,   step (10 == random)
            1, 1,  //obj speed, step (10 == random)
            0,0,0
        },
        {   //obj nr 2
            nullptr,
            true,   //player move en present
            true,  //obj move en prestnt
            10, 0, //obj size,  step (10 == random)
            20, 1, //obj pos,   step (10 == random)
            1, 1,  //obj speed, step (10 == random)
            0,0,0
        },
        {   //obj nr 3
            nullptr,
            true,   //player move en present
            true,  //obj move en prestnt
            10, 0, //obj size,  step (10 == random)
            30, 1, //obj pos,   step (10 == random)
            -1, -1,  //obj speed, step (10 == random)
            0,0,0
        },
        {   //obj nr 4
            nullptr,
            true,   //player move en present
            true,  //obj move en prestnt
            10, 0, //obj size,  step (10 == random)
            40, 1, //obj pos,   step (10 == random)
            1, 1,  //obj speed, step (10 == random)
            0,0,0
        },                        
    };

    //checking correctenss of test definition
    size_t test_def_count = sizeof(test_definition) / sizeof(tested_data_obj_definition_T);
    REQUIRE(test_def_count == 4);

    class variable_print_T {
        public:
            variable_print_T(int t, int k, int i, int j) {
                cout << "t: " << t << ", k: " << k << ", i: " << i << ", j: " << j << endl;
            };            
    };

    move_en_T player_move_en;
    move_en_T obj_move_en;
    for(size_t i = 0; i < board_dim; i++) {
        board.player_speed[i] = 11;
    }
    
    //creating game_board_objects
    for(size_t t = 0; t < test_def_count; t++) {
        test_definition[t].o = new game_board_obj_T(
            test_definition[t].player_move_en ? &player_move_en : nullptr,
            test_definition[t].obj_move_en ? &obj_move_en : nullptr,
            board
        );
        REQUIRE(test_definition[t].o != nullptr);
        if(!test_definition[t].o) {
            std::cerr << "lack of memory int test: Calculate coordinates registerd game_board_obj" << endl;
            exit(1);
        }
    }
    //setting up parameters for game_board_objetes
    for(size_t t = 0; t < test_def_count; t++) {
        for(size_t i = 0; i < board_dim; i++){
            test_definition[t].o->pos[i] = 
                test_definition[t].obj_pos_initial + (test_definition[t].obj_pos_step * i);
            test_definition[t].o->pos[i + board_dim] = 
                test_definition[t].obj_size_initial + (test_definition[t].obj_size_step * i);
            test_definition[t].o->speed[i] = 
                test_definition[t].obj_speed_initial + (test_definition[t].obj_speed_step * i);                
        }
    }


    //TESTING
    for(int k = 0; k < 3; k++) {

        //CHECKING game_board_objects PARAMETERS
        for(size_t t = 0; t < test_def_count; t++) {            

            //during move speed doesn't change
            for(size_t j = 0; j < board_dim; j++){
                REQUIRE(test_definition[t].o->speed[j] == 
                    test_definition[t].obj_speed_initial + (test_definition[t].obj_speed_step * (int)j)
                );
            }

            //during move pos does change
            for(size_t i = 0; i < board_dim; i++){
                variable_print_T* v = new variable_print_T(t, k, i, 0);
                REQUIRE(test_definition[t].o->pos[i] == 
                    test_definition[t].obj_pos_initial + (test_definition[t].obj_pos_step * (int)i) + 
                    (
                        ( test_definition[t].obj_move_en 
                            ? k * (
                                test_definition[t].obj_speed_initial + 
                                (test_definition[t].obj_speed_step * (int)i)
                            ) 
                            : 0 
                        )
                        + 
                        ( test_definition[t].player_move_en 
                            ? k * (board.player_speed[i])
                            : 0
                        )
                    )
                );                  
                if(v) {
                    delete v;
                }

                //during move obj size doesn't change
                REQUIRE(test_definition[t].o->pos[i + board_dim] == 
                    test_definition[t].obj_size_initial + (test_definition[t].obj_size_step * (int)i)
                );
            }  

        }

        player_move_en.calculate();
        obj_move_en.calculate();
    }


    //deleting game_board_objects
    for(size_t t = 0; t < test_def_count; t++) {
        if(test_definition[t].o) {
            delete test_definition[t].o;
        }
    }
};

TEST_CASE("Calculate coordinates registerd game_board_obj ver1") {
    move_en_T player_move_en;
    move_en_T obj_move_en;
    for(size_t i = 0; i < board_dim; i++) {
        board.player_speed[i] = 11;
    }

    
    game_board_obj_T o1(&player_move_en, nullptr, board);
    game_board_obj_T o2(&player_move_en, &obj_move_en, board);
    game_board_obj_T o3(&player_move_en, &obj_move_en, board);
    game_board_obj_T o4(nullptr, &obj_move_en, board);

    for(size_t i = 0; i < board_dim; i++){
        o1.pos[i] = i + 10;
        o1.pos[i + board_dim] = 10;                
    }
    for(size_t j = 0; j < board_dim; j++){
        o1.speed[j] = 0; //0, 0, 0
    }    

    for(size_t i = 0; i < board_dim; i++){
        o2.pos[i] = i + 20;
        o2.pos[i + board_dim] = 10;        
    }
    for(size_t j = 0; j < board_dim; j++){
        o2.speed[j] = j + 1;    //x:1, y:2, 3
    }

    for(size_t i = 0; i < board_dim; i++){
        o3.pos[i] = i + 30;
        o3.pos[i + board_dim] = 10;        
    }
    for(size_t j = 0; j < board_dim; j++){
        o3.speed[j] = -1 * (j + 1); //x:-1, y:-2, -3
    }

    for(size_t i = 0; i < board_dim; i++){
        o4.pos[i] = i + 40;
        o4.pos[i + board_dim] = 10;        
    }
    for(size_t j = 0; j < board_dim; j++){
        o4.speed[j] = j + 1; //x:1, y:2, 3
    }    

    
    for(int k = 0; k < 3; k++) {

        //--------------------------------------------------
        //CHECK game_board_obj_T PARAMETERS

        for(size_t j = 0; j < board_dim; j++){
            REQUIRE(o1.speed[j] == 0);
        }
        for(size_t i = 0; i < board_dim; i++){
            REQUIRE(o1.pos[i] == (int)i + 10 + (board.player_speed[i] * k));
            REQUIRE(o1.pos[i + board_dim] == 10);                
        }

        for(size_t j = 0; j < board_dim; j++){
            REQUIRE(o2.speed[j] == (int)j + 1) ; //x:1, y:2, 3
        }
        for(size_t i = 0; i < board_dim; i++){
            REQUIRE(o2.pos[i] == (int)i + 20 + (board.player_speed[i] * k) + (o2.speed[i] * k));
            REQUIRE(o2.pos[i + board_dim] == 10);                
        }    

        for(size_t j = 0; j < board_dim; j++){
            REQUIRE(o3.speed[j] == -1 *((int)j + 1) ) ; //x:-1, y:-2, -3
        }
        for(size_t i = 0; i < board_dim; i++){
            REQUIRE(o3.pos[i] == (int)i + 30 + (board.player_speed[i] * k) + (o3.speed[i] * k));
            REQUIRE(o3.pos[i + board_dim] == 10);                
        }    

        for(size_t j = 0; j < board_dim; j++){
            REQUIRE(o4.speed[j] == (int)j + 1) ; //x:1, y:2, 3
        }
        for(size_t i = 0; i < board_dim; i++){
            REQUIRE(o4.pos[i] == (int)i + 40 + (o4.speed[i] * k));
            REQUIRE(o4.pos[i + board_dim] == 10);                
        }    
        //--------------------------------------------------

        player_move_en.calculate();
        obj_move_en.calculate();

    } //for(k...)

};