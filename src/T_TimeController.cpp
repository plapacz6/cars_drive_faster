#include <iostream>
#include <thread>
#include "T_TimeController.h"
#include "T_Board.h"
#include "T_GameMutexes.h"
#include "pdebug.h"

using namespace std;
namespace csfgame {

T_TimeController::T_TimeController() {
}

//T_TimeController::~T_TimeController() override { }

//setters and getters:
//void T_TimeController::set_(TTT) { }
//TTT T_TimeController::get_() const { }

void T_TimeController::sleep(long ns) {
    timespec now;
    get_time(&now, ns);
    int sleep_status = 0;
    do {
        sleep_status =
            clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &now, NULL);
        PDEBUG_(sleep_status);
    } while(sleep_status != 0);
}

void get_time(timespec *ptr_now, long ns) {
    pthread_mutex_lock(&mtx.lock_get_time);
    int ret = clock_gettime(CLOCK_MONOTONIC, ptr_now);
    if(ret) {
        cerr << "game_control(), clock_gettime()" << endl;
        exit(1);
    }
    ptr_now->tv_nsec += ns;
    if(ptr_now->tv_nsec > 1000000000L) {
        ptr_now->tv_nsec -= 1000000000L;
        ptr_now->tv_sec++;
    }
    pthread_mutex_unlock(&mtx.lock_get_time);
}

} //namespace csfgame
