#ifndef T_CAR_H
#define T_CAR_H

namespace csfgame {

class T_Car {
public:
    explicit T_Car();
    explicit T_Car(const T_Car&) = default;
    virtual ~T_Car() = default;
    T_Car& operator=(const T_Car&) = default;

    //setters and getters:
    //void set_(TTT);
    //TTT get_() const;

    static double constexpr max_speed {35.0};       /*< max speed of each car*/
    static double constexpr beginnig_speed {0.1};   /*< beginnig speed of each car*/

protected:
private:
};

} //namespace csfgame
#endif //T_CAR_H
