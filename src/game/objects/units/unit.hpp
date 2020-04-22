#ifndef UNITS_HPP
#define UNITS_HPP

#include "game/objects/hexObject.hpp"
#include "game/objects/weapon.hpp"

class Unit : public HexObject {
    public:
        Unit();
        ~Unit();

        Weapon * getWeapon() { return mWeapon; }
    protected:
        Weapon * mWeapon;
};

#endif