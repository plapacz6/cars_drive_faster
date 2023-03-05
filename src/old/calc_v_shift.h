#ifndef CALC_V_SHIFT_H
#define CALC_V_SHIFT_H
#include <array>>
#include <iterator>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <cstdlib>
#include <cstddef>
#include "game_visible_obj_T.h"




constexpr size_t GAME_MOVING_OBJ_NUMBER = 10;
constexpr size_t GAME_ANIMATED_OBJ_NUBMER = 10;


class coordTable_T {
  public:
    std::vector<int> x;
    std::vector<int> w;
    std::vector<int> vspeed;
    std::vector<int> y;
    std::vector<int> h;
    std::vector<int> hspeed;
    size_t size;
    coordTable_T(size_t size_){
      size = 0;
    }
};
class coordMovingObj_T : public coordTable_T{    
  public:
    void subsribe(GameMovableObj_T &gvo) {
      x.push_back(gvo.co.x);
      w.push_back(gvo.co.width);
      vspeed.push_back(gvo.vspeed);
      y.push_back(gvo.co.y);
      h.push_back(gvo.co.height);
      hspeed.push_back(gvo.hspeed);
      size++;
    }
};
class coordVAnimatedObj_T : public coordTable_T{
  public:
    void subsribe(GameVAnimatedObj_T &gao);
};
#endif // CALC_V_SHIFT_H



std::mutex v_caclulate_region;
std::condition_variable calc_v_move;
bool v_ready;

void calculate_v_moves(coordMovingObj_T &cmo){
  std::unique_lock lk(v_caclulate_region);
  calc_v_move.wait(lk, [](){return true;} );
  for(int i = 0; i < cmo.size; i++){
    cmo.x[i] += cmo.vspeed[i];
    cmo.w[i] += cmo.vspeed[i];
  }
  lk.unlock();
}

std::mutex h_caclulate_region;
std::condition_variable calc_h_move;
bool h_ready;

void calculate_h_moves(coordMovingObj_T &cmo){
  std::unique_lock lk(h_caclulate_region);
  calc_h_move.wait(lk, [](){return true;} );
  for(int i = 0; i < cmo.size; i++){
    cmo.y[i] += cmo.hspeed[i];
    cmo.h[i] += cmo.hspeed[i];
  }
  lk.unlock();
}

int main(){
  bool game_end = false;
  std::unique_lock lkv(v_caclulate_region);
  std::unique_lock lkh(h_caclulate_region);
  std::thread calc_move_v(calculate_v_moves);
  std::thread calc_move_h(calculate_h_moves);
  while(!game_end){
    calc_v_move.notify_one();
    lkv.release();
    calc_h_move.notify_one();
    lkh.release();
    lkv.lock();
    lkh.lock();
    //calcualte new speeds
    
  }
  calc_move_v.join();
  calc_move_h.join();
}