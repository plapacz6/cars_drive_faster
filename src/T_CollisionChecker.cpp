#include "T_CollisionChecker.h"
#include "pdebug.h"

using namespace std;
namespace csfgame {

T_CollisionChecker::T_CollisionChecker(T_Car1& car1)
    : car1{car1}
{
}

//T_CollisionChecker::~T_CollisionChecker() override { }

//setters and getters:
//void T_CollisionChecker::set_(TTT) { }
//TTT T_CollisionChecker::get_() const { }


bool T_CollisionChecker::with(T_RoadHole& road_hole) {
    if(
        std::abs(road_hole.coord.x - car1.ptr_coord->x) < 15 &&
        (road_hole.coord.y + road_hole.coord.height) >= car1.ptr_coord->y)
    {
        // PDEBUG_(obj->coord.x);
        // PDEBUG_(car1.coord->x);
        PDEBUG_((road_hole.coord.x - car1.ptr_coord->x));

        /*callback performing phisics of collision*/
        constexpr double braking_on_hole = 3; //0.2; //ARYTMINT
        constexpr double min_speed_on_hole = 4; //1.0; //ARYTMINT

        double speed_car_1_prev = car1.get_speed();
        if(speed_car_1_prev > min_speed_on_hole) {
            car1.set_speed(
                (speed_car_1_prev - braking_on_hole) < min_speed_on_hole
                ? min_speed_on_hole
                : speed_car_1_prev - braking_on_hole);
        }
        return true;
    }
    return false;
}

bool T_CollisionChecker::with(T_Car2& car2) {
    if(
        std::abs(car2.coord.x - car1.ptr_coord->x) < 15 &&
        (car2.coord.y + car2.coord.height) >= car1.ptr_coord->y) {

        // PDEBUG_(ptr_obj->coord.x);
        // PDEBUG_(car1.ptr_coord->x);
        PDEBUG_((car2.coord.x - car1.ptr_coord->x));

        /*callback performing phisics of collision*/
        constexpr double speeding_up_car2 = 2; //0.2; //ARYTMINT
        constexpr int shifting_up_car2 = 10;
        constexpr double percent_braking_car1 = 0.9;

        double speed_car_1_prev = car1.get_speed();
        car1.set_speed(speed_car_1_prev * percent_braking_car1);
        car2.coord.y -= shifting_up_car2;
        car2.speed += speeding_up_car2;

        return true;
    }
    return false;
}

bool T_CollisionChecker::with(T_SteppeBush& bush) {
    if(
        std::abs(bush.coord.x - car1.ptr_coord->x) < 15 &&
        (bush.coord.y + bush.coord.height) >= car1.ptr_coord->y)
    {
        // PDEBUG_(obj->coord.x);
        // PDEBUG_(car1.coord->x);
        PDEBUG_((bush.coord.x - car1.ptr_coord->x));

        /*callback performing phisics of collision*/
        constexpr double braking_on_bush = 2; //0.2; //ARYTMINT
        constexpr double min_speed_on_bush = 10; //1.0; //ARYTMINT

        double speed_car_1_prev = car1.get_speed();
        if(speed_car_1_prev > min_speed_on_bush) {
            car1.set_speed(
                (speed_car_1_prev - braking_on_bush) < min_speed_on_bush
                ? min_speed_on_bush
                : speed_car_1_prev - braking_on_bush);
        }
        bush.processed = false;
        return true;
    }
    return false;
}

} //namespace csfgame
