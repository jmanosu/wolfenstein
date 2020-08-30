#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <iostream>


class Weapon {
    public:
        enum WEAPONTYPE {
            beam = 0,
            projectile,
            mortor
        };

        Weapon(WEAPONTYPE);
        ~Weapon();

        WEAPONTYPE getType();

//        void previewEffect();
//       void executeEffect();
        
    private:
        WEAPONTYPE _type;
};

#endif