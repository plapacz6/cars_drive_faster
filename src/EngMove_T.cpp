#include "EngMove_T.h"
#include <vector>
#include <iterator>

EngMove_T::EngMove_T(){
}

EngMove_T::~EngMove_T(){
}
size_t EngMove_T::register_to_process(int *st_ptr, int *sp_ptr){
  start_ptr.push_back(st_ptr);
  speed_ptr.push_back(sp_ptr);
}

void EngMove_T::clear(){
  start_ptr.clear();
  speed_ptr.clear();
}

// void unregister(size_t nr);

void EngMove_T::move(){
  std::vector<int*>::iterator it_st, it_sp;  
  for(
    it_st = start_ptr.begin(),
    it_sp = speed_ptr.begin();
    it_st != start_ptr.end() && it_sp != speed_ptr.end();
    ++it_st,
    ++it_sp
  ){
    **it_st = *(*it_st) + *(*it_sp);
  }
}


