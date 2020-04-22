#ifndef MECH_HPP
#define MECH_HPP

#include "game/objects/units/unit.hpp"

class Mech : public Unit {
    public:
        Mech();
        ~Mech();

        void applyWeapon(Weapon *);
    private:
};

#endif