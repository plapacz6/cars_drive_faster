#ifndef ENGMOVE_T
#define ENGMOVE_T
#include <vector>

class EngMove_T
{
  std::vector<int*> start_ptr;  
  std::vector<int*> speed_ptr;
  public:
    EngMove_T(){}
    ~EngMove_T(){}
    void register_start(int *st_ptr);    
    void register_speed(int *sp_ptr);
    void move();
};

#endif //ENGMOVE_T
