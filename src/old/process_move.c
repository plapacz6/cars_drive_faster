#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <condition_variable>

using namespace std;

condition_variable cv1;
mutex cv1_mtx;
condition_variable cv2;
mutex cv2_mtx;
int work_end = 0;


class Rect {
  public:
    int x;
    int y;
    int w;
    int y;
};

class movableV_obj_T {
  friend class process_Vmove_T;
  public:
    Rect pos;
    int vspeed;  
    movableV_obj_T(){
    }
    movableV_obj_T(int x, int y, int w, int h, int vs){
      pos.x = x;
      pos.y = y;
      pos.w = w;
      pos.h = h;
      vspeed = vs;
    }
    ~movablev_obj_T(){};
};

class process_Vmove_T {
  public:
    vector<int*> y;
    vector<int*> h;
    vector<int*> vspeed;    

    void move() {      
      while(!work_end){
        unique_lock<mutex> lk(cv1_mtx);
        lk.lock();
        for(size_t i = 0; i < x.size(); i++){
          *(y[i]) = *(y[i]) + *(vspeed[i]);              
          *(h[i]) = *(h[i]) + *(vspeed[i]);
        }          
        cv2.notify_one();
        cv1.wait(lk, []{return i == 1});
      }
    }
    void subsribe(movableV_obj_T& o_ptr){
      y.pushback(&o.pos->y);
      h.pushback(&o.pos->h);
      vspeed.pushback(&o.vspeed);
    }
};



int main(){
  srand(time(NULL));

  

  vector<movableV_obj_T> mo;
  process_Vmove_T pmo;

  for(size_t i = 0; i < 10; i++){
    mo.pushback(new movableV_obj_T(
      randint(100),
      randint(100),
      10,
      10,
      randint(10);
    ))
  }
  for(size_t i = 0; i < 10; i++){
    pmo.subscribe(mo[i]);
  }
  thread process_v(pmo.move);
  sleep(5);
  process_v.join();
  return 0;
}


