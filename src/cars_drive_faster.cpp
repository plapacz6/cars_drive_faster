/*
author: plapacz6@gmail.com
data: 2022-07-22
ver: 0.1.0
*/
#define DEBUG_MSG

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
#include <unistd.h>
#include <thread>

#include "PasteImgFunctions.h"

using namespace std;
using namespace cv;

/* ----------------------------------------- */
#include "pdebug.h"
#include "T_CLI.h"
#include "T_TimeController.h"
#include "T_GameMutexes.h"
#include "T_GameImages.h"

#include "T_Obstacle.h"
#include "T_Car2.h"
#include "T_RoadHole.h"
#include "T_SteppeBush.h"
#include "T_RoadLine.h"
#include "T_Road.h"
#include "T_Car1.h"
#include "T_GameDefs.h"
#include "T_Board.h"
#include "T_VShiftUnit.h"
#include "T_CollisionChecker.h"

namespace csfgame {
/* ----------------------------------------- */
T_TimeController game_clock;
bool game_break = false;
T_Road *ptr_road = nullptr;
T_Car1 *ptr_car1 = nullptr;  /*< used by two threads */

/* ----------------------------------------- */
enum key_nr_t {
    KEY_ESC = 1048603,
    KEY_ESC_CAPSLOCK = 1179675,
    KEY_LARROW = 1113937,
    KEY_RARROR = 1113939,

    COMMAND_end = KEY_ESC,
    COMMAND_END = KEY_ESC_CAPSLOCK,
    COMMAND_LEFT = KEY_LARROW,
    COMMAND_RIGHT = KEY_RARROR
};
/* ----------------------------------------- */
} //namespace csfgame



using namespace csfgame;

void game_control(bool *ptr_game_break) {

    T_CLI cli{TUserLanguage::PL};
    key_nr_t command;

    T_Road& road = *ptr_road;
    T_Car1 my_car(road, TBoardSector::LANE_M, 0.0);
    ptr_car1 = &my_car;
    T_CollisionChecker collision_car1 {my_car};

    cli.print_message(TCLIMessages::basic_control);

    my_car.action();
    /* EXAMPLE */

    T_Car2 car2;
    T_RoadHole hole2;
    T_SteppeBush bush;

    /* EXAMPLE */

    while(command != KEY_ESC && command != KEY_ESC_CAPSLOCK) {

        //PDEBUG_(command);
        command = static_cast<key_nr_t>(pollKey());
        /* command = pollKey() == waitKeyEx(0) != waitKey(0) */

        road.draw();

        if(command == COMMAND_LEFT) {
            my_car.to_left();
        }
        else if(command == COMMAND_RIGHT) {
            my_car.to_right();
        }

        /* not working currently */
        // for(size_t i = 0; i < road.road_objects.size(); i++) {
        //     road.road_objects[i].action();
        // }
        /* EXAMPLE */
        hole2.action();
        car2.action();
        bush.action();
        /* EXAMPLE */

        my_car.action();

        board.show();

        if(collision_car1.with(hole2)) {
            ptr_road->calculate_shift(my_car.get_speed());
        }
        else if(collision_car1.with(car2)) {
            ptr_road->calculate_shift(my_car.get_speed());
        }
        if(collision_car1.with(bush)) {
            ptr_road->calculate_shift(my_car.get_speed());
        }

        if(!hole2.processed) {
            hole2.draw_a_new_one();
        }
        if(!car2.processed) {
            car2.draw_a_new_one();
        }
        if(!bush.processed) {
            bush.draw_a_new_one();
        }
        game_clock.sleep(b_df.time_period_ns);
    }
    *ptr_game_break = true;
}


/**
 * @brief thread increasing car1 speed
 *
 * @param ptr_game_break
 */
void speed_up(bool *ptr_game_break) {

    double car1_speed_curr;

    while(!*ptr_game_break) {

        game_clock.sleep(b_df.time_speed_up_ns);
        
        static double const car1_almost_max_speed = ptr_car1->max_speed - b_df.car1_step_speed_up;
        car1_speed_curr = ptr_car1->get_speed();

        if(car1_speed_curr <= car1_almost_max_speed){ 
            ptr_car1->set_speed( (car1_speed_curr + b_df.car1_step_speed_up) );
            ptr_road->calculate_shift(car1_speed_curr);
        }

        PDEBUG_(ptr_car1->get_speed());
        //waitKey(0);
    }
}


int main() {
    
    srand(time(NULL));

    //cout << _POSIX_C_SOURCE << endl;
    namedWindow(b_df.wndName);
    T_Road road;
    ptr_road = &road;
    std::thread th_game_control(game_control, &game_break);
    sleep(2);  //time for laoding textures
    std::thread th_speed_up(speed_up, &game_break);

    th_game_control.join();
    th_speed_up.join();
    
    return EXIT_SUCCESS;
}



