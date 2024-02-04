#include "T_CollisionChecker.h"
#include "pdebug.h"

using namespace std;
namespace csfgame {

T_CollisionChecker::T_CollisionChecker(T_Car1* ptr_car1)
    : ptr_car1{ptr_car1}
{
}

//T_CollisionChecker::~T_CollisionChecker() override { }

//setters and getters:
//void T_CollisionChecker::set_(TTT) { }
//TTT T_CollisionChecker::get_() const { }


bool T_CollisionChecker::with_hole(T_Obstacle *ptr_obj) {
    if(
        std::abs(ptr_obj->coord.x - ptr_car1->ptr_coord->x) < 15 &&
        (ptr_obj->coord.y + ptr_obj->coord.height) >= ptr_car1->ptr_coord->y) {
        // PDEBUG_(ptr_obj->coord.x);
        // PDEBUG_(ptr_car1->ptr_coord->x);
        PDEBUG_((ptr_obj->coord.x - ptr_car1->ptr_coord->x));
        return true;
    }
    return false;
}

bool T_CollisionChecker::with_car2(T_Obstacle *ptr_obj) {
    if(
        std::abs(ptr_obj->coord.x - ptr_car1->ptr_coord->x) < 15 &&
        (ptr_obj->coord.y + ptr_obj->coord.height) >= ptr_car1->ptr_coord->y) {
        // PDEBUG_(ptr_obj->coord.x);
        // PDEBUG_(ptr_car1->ptr_coord->x);
        PDEBUG_((ptr_obj->coord.x - ptr_car1->ptr_coord->x));
        return true;
    }
    return false;
}

} //namespace csfgame
