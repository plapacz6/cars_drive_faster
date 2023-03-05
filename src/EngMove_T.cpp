#include "EngMove_T.h"
#include <vector>
#include <iterator>

EngMove_T::EngMove_T(){
}

EngMove_T::~EngMove_T(){
}

void EngMove_T::register_start(int* st_ptr){
  start_ptr.push_back(st_ptr);
}

void EngMove_T::register_speed(int *sp_ptr){
  speed_ptr.push_back(sp_ptr)
}

void EngMove_T::move(){
  std::vector<int*>::iterator it_st, it_sp;  
  for(
    it_st = start_ptr.begin(),
    it_sp = speed_ptr.begin();
    it_st != start_ptr.end() && it_sp != speed_ptr.end();
    ++it_st,
    ++it_sp
  ){
    *it_st = (*it_st) + (*it_sp);
  }
}


