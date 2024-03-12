#ifndef T_GAMEMUTEXES_H
#define T_GAMEMUTEXES_H

#include <mutex>
#include <thread>

namespace csfgame {

class T_GameMutexes {
public:
    explicit T_GameMutexes();
    T_GameMutexes(const  T_GameMutexes&) = delete;
    virtual ~T_GameMutexes() = default;
    T_GameMutexes& operator=(const T_GameMutexes&) = delete;

    std::mutex get_time;
    std::mutex speed_car1;
    std::mutex v_shift_unit;

protected:
private:
};

extern T_GameMutexes mtx;

} //namespace csfgame
#endif //T_GAMEMUTEXES_H


