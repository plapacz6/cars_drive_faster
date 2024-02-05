#ifndef T_TIMECONTROLLER_H
#define T_TIMECONTROLLER_H

#include <ctime>  //nanosleep
// #include <chrono>

namespace csfgame {

class T_TimeController {
public:
    T_TimeController();
    T_TimeController(const  T_TimeController&) = delete;
    virtual ~T_TimeController() = default;
    T_TimeController& operator=(const T_TimeController&) = delete;

    //setters and getters:
    //void set_(TTT);
    //TTT get_() const;

    void sleep(long ns);

protected:
private:
};

void get_time(timespec *ptr_now, long ns);

} //namespace csfgame
#endif //T_TIMECONTROLLER_H
