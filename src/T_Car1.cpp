#include "T_Car1.h"
#include "T_GameMutexes.h"
#include "T_GameImages.h"
#include "T_Board.h"
#include "PasteImgFunctions.h"

using namespace std;
namespace csfgame {

/**
 * @brief Construct a new car1 t::car1 t object
 *
 * @param road_ object road, stroing Rec of car1 position on each lane
 * @param begin_pos_ TBoardSector  beginning lane
 * @param speed_     beginning speed
 */
T_Car1::T_Car1(T_Road& road_, TBoardSector begin_pos_, double speed_)
    : road(road_)
{
    if(begin_pos_ == TBoardSector::LANE_L)
        ptr_coord = &road_.car1_L;    
    else 
    if(begin_pos_ == TBoardSector::LANE_R)
        ptr_coord = &road_.car1_R;
    else //if(begin_pos_ == TBoardSector::LANE_M)  //each other set defaut to middle position
        ptr_coord = &road_.car1_M;        
}

// T_Car1::~T_Car1() {
// }


void T_Car1::action() {
    paste_img(game_images.img_car1, *ptr_coord, board.b);
}


//class speed_car1_t { //TODO
void T_Car1::zeros_speed() {
    pthread_mutex_lock(&mtx.lock_speed_car1);
    speed_car1 = beginnig_speed;
    pthread_mutex_unlock(&mtx.lock_speed_car1);
}
double T_Car1::get_speed() {
    double spped_car1_;
    pthread_mutex_lock(&mtx.lock_speed_car1);
    spped_car1_ = speed_car1;
    pthread_mutex_unlock(&mtx.lock_speed_car1);
    return spped_car1_;
}
void T_Car1::set_speed(double&& speed_car1_) {
    pthread_mutex_lock(&mtx.lock_speed_car1);
    speed_car1 = speed_car1_;
    pthread_mutex_unlock(&mtx.lock_speed_car1);
}

} //namespace csfgame
