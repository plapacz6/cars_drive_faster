#ifndef GAME_VMOVABLE_OBJ_T
#define GAME_VMOVABLE_OBJ_T
#include "game_obj_T.h"
#include "EngMove_T.h"

extern EngMove_T glob_em_y;

class game_Vmovable_obj_T : public game_obj_T
{  
    EngMove_T em_y;
  public:
    int vspeed;

    game_Vmovable_obj_T(EngMove_T& em_y_ = glob_em_y);
    ~game_Vmovable_obj_T();    
};

#endif //GAME_VMOVABLE_OBJ_T
