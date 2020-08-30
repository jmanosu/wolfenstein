#include "weapon.hpp"

Weapon::Weapon(Weapon::WEAPONTYPE type)
{
    _type = type;
}

Weapon::~Weapon()
{
    
}

Weapon::WEAPONTYPE Weapon::getType()
{
    return _type;
}