#include "game_Vmovable_obj_T.h"

game_Vmovable_obj_T::game_Vmovable_obj_T(EngMove_T& em_y_) 
  : em_y{em_y_}{
  em_y.register_to_process(&pos.y, &vspeed);    
}

game_Vmovable_obj_T::~game_Vmovable_obj_T(){
}

