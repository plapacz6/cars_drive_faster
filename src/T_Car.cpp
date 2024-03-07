#include "T_Car.h"
#include "T_GameDefs.h"

using namespace std;
namespace csfgame {

T_Car::T_Car() {
}

double const& T_Car::max_speed {b_df.car_max_speed};             /*< max speed of each car*/
double const& T_Car::beginnig_speed {b_df.car_beginnig_speed};   /*< beginnig speed of each car*/

} //namespace csfgame
