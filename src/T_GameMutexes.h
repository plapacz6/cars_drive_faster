#ifndef T_GAMEMUTEXES_H
#define T_GAMEMUTEXES_H

#include <thread>

namespace csfgame {

class T_GameMutexes {
public:
    explicit T_GameMutexes();
    T_GameMutexes(const  T_GameMutexes&) = delete;
    virtual ~T_GameMutexes() = default;
    T_GameMutexes& operator=(const T_GameMutexes&) = delete;

    //setters and getters:
    //void set_(TTT);
    //TTT get_() const;

    pthread_mutex_t lock_get_time;
    pthread_mutexattr_t mutex_attr_get_time;

    pthread_mutex_t lock_speed_car1;
    pthread_mutexattr_t mutex_attr_speed_car1;

    pthread_mutex_t lock_v_shift_unit;
    pthread_mutexattr_t mutex_attr_v_shift_unit;

protected:
private:
};

extern T_GameMutexes mtx;
void init_mutex();
void destroy_mutex();

} //namespace csfgame
#endif //T_GAMEMUTEXES_H


