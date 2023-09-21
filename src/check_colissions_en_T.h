
#ifndef CHECK_COLISSIONS_EN_T_H
#define CHECK_COLISSIONS_EN_T_H

#include <vector>

class game_colidable_obj_T;

/**
 * class check_colissions_en_T

 * rejestruje akcje (funkcje) wywolywana dla zdarzenia kolizji dwoch obiektow
 * game_obj_T
 *
 *
 * metoda check_collisions() jest wywolywana w oddzielnym watku w odpowienim
 * momencie i
 * sprawdza czy zachodzi kolizja pomiedzy ktora kolwiek z par obiektow
 * zarejestwoanych na jego liscie obiektow monitorownych pod wzgledem kolizji,
 * i jesli tak to wywoluje przypisana do tego zdarzenia funkcje, ktora robi
 * odpowiednia akcje
 */

class check_colissions_en_T
{
public:
    /* Constructors/Destructors     */

    /**
     * Empty Constructor
     */
    check_colissions_en_T();

    /**
     * Empty Destructor
     */
    virtual ~check_colissions_en_T();

    /**
     * checking for objects colissions
     * and when collission is detected runnig signupd calback based on colided
     * objects
     * @param  so striking item
     * @param  ho hit object
     */
    void check_collisions_and_execute(game_colidable_obj_T* so, game_colidable_obj_T* ho);

    /**
     * regiters selected collisons to check if occured and action to perform
     * @param  o1
     * @param  o2
     * @param  o1_to_o2_in_out actrion pefromed when o1 enter into area of o2 (IN)
     * or leave (OUT)
     * @param  action void action(&o1, &o2)
     */
    void signup_collision_to_check(game_colidable_obj_T* o1, game_colidable_obj_T* o2, enum_IN_OUT o1_to_o2_in_out, nowa_klasa_1 action);

private:
    /* Private attributes     */

    vector<collison_def_T> collision_def_table;

    void initAttributes();

};

#endif // CHECK_COLISSIONS_EN_T_H
