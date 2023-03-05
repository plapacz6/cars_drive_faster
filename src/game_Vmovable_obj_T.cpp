#include "game_Vmovable_obj_T.h"

game_Vmovable_obj_T::game_Vmovable_obj_T(EngMove_T& em_y_) 
  : em_y(em_y_){
  em_y.register_start(&pos.y);  
  em_y.register_speed(&vspeed);
}

game_Vmovable_obj_T::~game_Vmovable_obj_T(){
}

