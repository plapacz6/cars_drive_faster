#include <catch2/catch_all.hpp>
#include "../game_obj_category_T.h"
#include "../check_collisions_en_T.h"
#include "../game_collidable_obj_T.h"
#include "../board_T.h"

#include <iostream>

class print_msg_T {
    public:
        print_msg_T(std::string msg) {
            std::cerr << msg << std::endl;
        }
};

void action_BEFOREIN(game_collidable_obj_T* o1, game_collidable_obj_T* o2){
    print_msg_T("action_BEFOREIN:" + 
     #ifdef DEBUG
    o1->get_obj_category_name() +
    collision_type_to_string(collision_type_T::IN) + 
    o2->get_obj_category_name() + 
    #endif //DEBUG
    "");   
}
void action_ONIN(game_collidable_obj_T* o1, game_collidable_obj_T* o2){
    print_msg_T("action_ONIN:" + 
     #ifdef DEBUG
    o1->get_obj_category_name() +
    collision_type_to_string(collision_type_T::IN) + 
    o2->get_obj_category_name() + 
    #endif //DEBUG
    "");   
}
void action_ONIN_OR_IN(game_collidable_obj_T* o1, game_collidable_obj_T* o2){
    print_msg_T("action_ONIN_OR_IN: " + 
    #ifdef DEBUG
    o1->get_obj_category_name() +
    collision_type_to_string(collision_type_T::ONIN_OR_IN) + 
    o2->get_obj_category_name() + 
    #endif //DEBUG
    ""); 
}
void action_IN(game_collidable_obj_T* o1, game_collidable_obj_T* o2){
    print_msg_T("action_IN:" + 
     #ifdef DEBUG
    o1->get_obj_category_name() +
    collision_type_to_string(collision_type_T::IN) + 
    o2->get_obj_category_name() + 
    #endif //DEBUG
    "");         
}
void action_IN_OR_ONOUT(game_collidable_obj_T* o1, game_collidable_obj_T* o2){
    print_msg_T("action_IN_OR_ONOUT:" + 
     #ifdef DEBUG
    o1->get_obj_category_name() +
    collision_type_to_string(collision_type_T::IN) + 
    o2->get_obj_category_name() + 
    #endif //DEBUG
    "");   
}
void action_ONOUT(game_collidable_obj_T* o1, game_collidable_obj_T* o2){
    print_msg_T("action_ONOUT: " + 
    #ifdef DEBUG
    o1->get_obj_category_name() +
    collision_type_to_string(collision_type_T::ONOUT) + 
    o2->get_obj_category_name() + 
    #endif //DEBUG
    "");
}
void action_ONOUT_OR_OUT(game_collidable_obj_T* o1, game_collidable_obj_T* o2){
    print_msg_T("action_ONOUT_OR_OUT:" + 
     #ifdef DEBUG
    o1->get_obj_category_name() +
    collision_type_to_string(collision_type_T::IN) + 
    o2->get_obj_category_name() + 
    #endif //DEBUG
    "");   
}
void action_OUT(game_collidable_obj_T* o1, game_collidable_obj_T* o2){
    print_msg_T("action_OUT:" + 
     #ifdef DEBUG
    o1->get_obj_category_name() +
    collision_type_to_string(collision_type_T::IN) + 
    o2->get_obj_category_name() + 
    #endif //DEBUG
    "");   
}
/*
    //BEFOREIN
    //ONIN,   //!<< on obj's border 1 (according to movement direction)
    //ONIN_OR_IN,
    //IN,     //!<< past the border 1, in the area of obj    
    //IN_OR_ONOUT,
    //ONOUT,  //!<< on obj's border 2 (according to movement direction)
    //ONOUT_OR_OUT
    //OUT    
*/

TEST_CASE("Creating check_collisions_en_T") {
    check_collisions_en_T chco1;
};

TEST_CASE("Registering object") {
    board_T board;
    check_collisions_en_T chco1;
    game_collidable_obj_T co1(nullptr, nullptr, board, game_obj_category_T::CAR, chco1);
    game_collidable_obj_T co2(nullptr, nullptr, board, game_obj_category_T::HOLE, chco1);
    #ifdef DEBUG
    REQUIRE(chco1.get_registered_obj(0) == &co1);
    REQUIRE(chco1.get_registered_obj(1) == &co2);
    #endif //DEBUG
};

TEST_CASE("Registering collisons") {
    board_T board;
    check_collisions_en_T chco1;
 
    chco1.signup_collision_to_check(
        game_obj_category_T::CAR,
        game_obj_category_T::HOLE,
        collision_type_T::ONOUT,
        action_ONOUT
    );
        chco1.signup_collision_to_check(
        game_obj_category_T::CAR,
        game_obj_category_T::CAR,
        collision_type_T::ONIN_OR_IN,
        action_ONIN_OR_IN
    );
        chco1.signup_collision_to_check(
        game_obj_category_T::CAR,
        game_obj_category_T::BUSH,
        collision_type_T::IN,
        action_IN
    );
    REQUIRE(chco1.get_registered_action(0).action == action_ONOUT);
    REQUIRE(chco1.get_registered_action(1).action == action_ONIN_OR_IN);
    REQUIRE(chco1.get_registered_action(2).action == action_IN);
    REQUIRE(chco1.get_registered_action(0).collision_type == collision_type_T::ONOUT);
    REQUIRE(chco1.get_registered_action(1).collision_type == collision_type_T::ONIN_OR_IN);
    REQUIRE(chco1.get_registered_action(2).collision_type == collision_type_T::IN);
    REQUIRE(chco1.get_registered_action(0).so == game_obj_category_T::CAR);
    REQUIRE(chco1.get_registered_action(1).so == game_obj_category_T::CAR);
    REQUIRE(chco1.get_registered_action(2).so == game_obj_category_T::CAR);
    REQUIRE(chco1.get_registered_action(0).ho == game_obj_category_T::HOLE);
    REQUIRE(chco1.get_registered_action(1).ho == game_obj_category_T::CAR);
    REQUIRE(chco1.get_registered_action(2).ho == game_obj_category_T::BUSH);        
};

TEST_CASE("Checking collisions") {
    board_T board;
    check_collisions_en_T chco1;
    game_collidable_obj_T car1(nullptr, nullptr, board, game_obj_category_T::CAR, chco1);    
    game_collidable_obj_T hole1(nullptr, nullptr, board, game_obj_category_T::HOLE, chco1);
    game_collidable_obj_T car2(nullptr, nullptr, board, game_obj_category_T::CAR, chco1);
    game_collidable_obj_T bush1(nullptr, nullptr, board, game_obj_category_T::BUSH, chco1);

    chco1.signup_collision_to_check(
        game_obj_category_T::CAR,
        game_obj_category_T::HOLE,
        collision_type_T::BEFOREIN,
        action_BEFOREIN
    );
    chco1.signup_collision_to_check(
        game_obj_category_T::CAR,
        game_obj_category_T::CAR,
        collision_type_T::ONIN,
        action_ONIN
    );
    chco1.signup_collision_to_check(
        game_obj_category_T::CAR,
        game_obj_category_T::BUSH,
        collision_type_T::ONIN_OR_IN,
        action_ONIN_OR_IN
    );
    chco1.signup_collision_to_check(
        game_obj_category_T::CAR,
        game_obj_category_T::HOLE,
        collision_type_T::IN,
        action_IN
    );
    chco1.signup_collision_to_check(
        game_obj_category_T::CAR,
        game_obj_category_T::CAR,
        collision_type_T::IN_OR_ONOUT,
        action_IN_OR_ONOUT
    );
    chco1.signup_collision_to_check(
        game_obj_category_T::CAR,
        game_obj_category_T::BUSH,
        collision_type_T::ONOUT,
        action_ONOUT
    );
    chco1.signup_collision_to_check(
        game_obj_category_T::CAR,
        game_obj_category_T::BUSH,
        collision_type_T::ONOUT_OR_OUT,
        action_ONOUT_OR_OUT
    );
    chco1.signup_collision_to_check(
        game_obj_category_T::CAR,
        game_obj_category_T::BUSH,
        collision_type_T::OUT,
        action_OUT
    );    
    // #ifdef DEBUG
    // REQUIRE(chco1.get_registered_obj(0) == &co1);
    // REQUIRE(chco1.get_registered_obj(1) == &co2);
    // #endif //DEBUG
};