#ifndef MECH_HPP
#define MECH_HPP

#include "objects/map/hexObjects/units/unit.hpp"

#include "graphics/textures/animatedTexture.hpp"

class Mech : public Unit {
    public:
        Mech();
        ~Mech();

        void update();
        void render();

        void applyWeapon(Weapon *);

        void setIdleTexture(const AnimatedTexture *);
        AnimatedTexture * getIdleTexture();
    private:

        AnimatedTexture * mIdleTexture;
};

#endif