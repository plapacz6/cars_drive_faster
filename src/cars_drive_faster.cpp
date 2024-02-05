/*
author: plapacz6@gmail.com
data: 2022-07-22
ver: 0.1.0
*/
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
#include <unistd.h>
#include <thread>

// #include <mutex>

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
#include "T_Board.h"
#include "T_VShiftUnit.h"
#include "T_CollisionChecker.h"

namespace csfgame {
/* ----------------------------------------- */
T_TimeController game_clock;
bool game_break = false;
T_Road *ptr_road = nullptr;
T_Car1 *ptr_car1 = nullptr;

/* ----------------------------------------- */
enum key_nr_t {
    KEY_ESC = 1048603,
    KEY_ESC_CAPSLOCK = 1179675,
    KEY_LARROW = 1113937,
    KEY_RARROR = 1113939
};
/* ----------------------------------------- */
} //namespace csfgame



using namespace csfgame;

void game_control(bool *ptr_game_break) {

    T_CLI cli{TUserLanguage::PL};
    key_nr_t key;

    T_Road& road = *ptr_road;
    T_Car1 my_car(road, TBoardSector::LANE_M, 0.0);
    ptr_car1 = &my_car;
    T_CollisionChecker collision_car1 {&my_car};

    cli.print_message(TCLIMessages::basic_control);

    my_car.action();
    /* EXAMPLE */

    T_Car2 car2;
    T_RoadHole hole2;

    /* EXAMPLE */

    while(key != KEY_ESC && key != KEY_ESC_CAPSLOCK) {

        //PDEBUG_(key);
        key = static_cast<key_nr_t>(pollKey());
        /* key = pollKey() == waitKeyEx(0) != waitKey(0) */

        for(size_t i = 0; i < road.road_objects.size(); i++) {
            road.road_objects[i].action();
        }
        road.draw();
        if(key == KEY_LARROW) {
            if(my_car.ptr_coord == &road.car1_M) /* order is important: checking M before R */
                my_car.ptr_coord = &road.car1_L;
            if(my_car.ptr_coord == &road.car1_R)
                my_car.ptr_coord = &road.car1_M;
        }
        else if(key == KEY_RARROR) {
            if(my_car.ptr_coord == &road.car1_M)
                my_car.ptr_coord = &road.car1_R;
            if(my_car.ptr_coord == &road.car1_L)
                my_car.ptr_coord = &road.car1_M;
        }

        /* EXAMPLE */
        hole2.action();
        car2.action();
        /* EXAMPLE */

        my_car.action();

        board.show();

        if(collision_car1.with_hole(&hole2)) {
            double speed_car_1_prev = my_car.get_speed();
            my_car.set_speed(
                (speed_car_1_prev - 0.2) < 1
                ? 1
                : speed_car_1_prev - 0.2);
            ptr_road->calculate_shift(my_car.get_speed());
        }
        else {
            if(collision_car1.with_car2(&car2)) {
                double speed_car_1_prev = my_car.get_speed();
                my_car.set_speed(speed_car_1_prev * 0.9);
                car2.coord.y -= 10;
                car2.speed += 0.2;
                ptr_road->calculate_shift(my_car.get_speed());
            }
        }

        if(!hole2.processed) {
            hole2.draw_new();
        }
        if(!car2.processed) {
            car2.draw_new();
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

    double speed_car1_get;

    while(!*ptr_game_break) {

        game_clock.sleep(b_df.time_speed_up_ns);

        speed_car1_get = ptr_car1->get_speed();
        if(speed_car1_get < ptr_car1->max_speed +  b_df.step_speed_up) {
            ptr_car1->set_speed( (speed_car1_get + b_df.step_speed_up) );
            ptr_road->calculate_shift(ptr_car1->get_speed());
        }

        PDEBUG_(ptr_car1->get_speed());
        //waitKey(0);
    }
}


int main() {
    init_mutex();
    srand(time(NULL));

    //cout << _POSIX_C_SOURCE << endl;
    namedWindow(b_df.wndName);
    T_Road road;
    ptr_road = &road;
    std::thread th_game_control(game_control, &game_break);
    sleep(1);  //time for laoding textures
    std::thread th_speed_up(speed_up, &game_break);

    th_game_control.join();
    th_speed_up.join();

    destroy_mutex();
    return EXIT_SUCCESS;
}



