#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <iostream>

enum WEAPONTYPE {
    beam = 0,
    projectile,
    mortor
};

class Weapon {
    public:
        Weapon();
        ~Weapon();

        WEAPONTYPE getType() { return mType; }
        std::string getName() { return mName; }
    private:
        WEAPONTYPE mType;
        std::string mName;

};

#endif