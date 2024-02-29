#ifndef T_CAR_H
#define T_CAR_H

namespace csfgame {

class T_Car {
public:
    explicit T_Car();
    explicit T_Car(const T_Car&) = default;
    virtual ~T_Car() = default;
    T_Car& operator=(const T_Car&) = default;

    //reference to T_GameDefs
    static double const& max_speed;        /*< max speed of each car*/
    static double const& beginnig_speed;   /*< beginnig speed of each car*/

protected:
private:
};

} //namespace csfgame
#endif //T_CAR_H
