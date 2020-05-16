#ifndef UNITS_HPP
#define UNITS_HPP

#include "objects/map/hexObjects/hexObject.hpp"
#include "objects/map/weapons/weapon.hpp"

class Unit : public HexObject {
    public:
        Unit();
        ~Unit();

        void setWeapon(Weapon *);
        Weapon * getWeapon();
        
        void setHealth(int);
        int getHealth(int);
    protected:
        Weapon * mWeapon;

        int mHealth;
};

#endif