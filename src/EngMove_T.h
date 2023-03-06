#ifndef ENGMOVE_T
#define ENGMOVE_T
#include <vector>

class EngMove_T
{
  std::vector<int*> start_ptr;  
  std::vector<int*> speed_ptr;
  public:
    EngMove_T();
    ~EngMove_T();
    size_t register_to_process(int *st_ptr, int *sp_ptr);
    void clear();
    // void unregister(size_t nr);
    
    void move();
        
};

#endif //ENGMOVE_T
