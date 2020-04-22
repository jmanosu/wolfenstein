#include "mech.hpp"

Mech::Mech()
{
    mHexObjectTexture = new Texture("hexObjects/Mech2.png");
    mHexObjectTexture->parent(this);
    this->pos(GVector(3,-7));
}

Mech::~Mech()
{

}

void Mech::applyWeapon(Weapon * weapon)
{
    std::cout << weapon->getName() << std::endl;
}