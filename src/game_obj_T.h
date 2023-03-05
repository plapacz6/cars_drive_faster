#ifndef GAME_OBJ_T
#define GAME_OBJ_T
#include "Rect_T.h"

class game_obj_T
{
  public:
    Rect_T pos;
    game_obj_T();
    virtual ~game_obj_T();
};

#endif //GAME_OBJ_T
