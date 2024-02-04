#include <iostream>

#include "T_GameMutexes.h"

using namespace std;
namespace csfgame {

T_GameMutexes mtx;

T_GameMutexes::T_GameMutexes() {
}

//T_GameMutexes::~T_GameMutexes() override { }

//setters and getters:
//void T_GameMutexes::set_(TTT) { }
//TTT T_GameMutexes::get_() const { }

void init_mutex() {

    int ret;
    ret = pthread_mutex_init(&mtx.lock_speed_car1, &mtx.mutex_attr_speed_car1);
    if(ret) {
        cerr << "mutex init" << endl;
        exit(1);
    }

    ret = pthread_mutex_init(&mtx.lock_get_time, &mtx.mutex_attr_get_time);
    if(ret) {
        cerr << "mutex init" << endl;
        exit(1);
    }

    ret = pthread_mutex_init(&mtx.lock_v_shift_unit, &mtx.mutex_attr_v_shift_unit);
    if(ret) {
        cerr << "mutex init" << endl;
        exit(1);
    }
}

void destroy_mutex() {
    pthread_mutex_destroy(&mtx.lock_speed_car1);
    pthread_mutex_destroy(&mtx.lock_get_time);
    pthread_mutex_destroy(&mtx.lock_v_shift_unit);
}

} //namespace csfgame



