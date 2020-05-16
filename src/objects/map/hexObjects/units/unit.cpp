#include "unit.hpp"

Unit::Unit()
{
    mWeapon = nullptr;
}

Unit::~Unit()
{
    delete mWeapon;
}

void Unit::setWeapon(Weapon * weapon)
{
    mWeapon = weapon;
}

Weapon * Unit::getWeapon()
{
    return mWeapon;
}