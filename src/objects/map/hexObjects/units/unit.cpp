#include "unit.hpp"

Unit::Unit() : HexObject()
{
    _defaultGameStats = {
        ._health = 0,
        ._moveRange = 0,
        ._moveCount = 0
    };

    _hex = nullptr;

    reset();

    _weaponId = -1;
}

Unit::~Unit()
{
}

void Unit::setWeaponId(int weaponId)
{
    _weaponId = weaponId;
}

int Unit::getWeaponId()
{
    return _weaponId;
}


void Unit::reset()
{
    _currentGameStats = _defaultGameStats;
}

void Unit::setHealth(int health)
{
    _currentGameStats._health = health;
}

int Unit::getHealth()
{
    return _currentGameStats._health;
}

void Unit::setMoveRange(int range)
{
    _currentGameStats._moveRange = range;
}

int Unit::getMoveRange()
{
    return _currentGameStats._moveRange;
}

void Unit::setMoveCount(int count)
{
    _currentGameStats._moveCount = count;
}

int Unit::getMoveCount()
{
    return _currentGameStats._moveCount;
}

bool Unit::isMovable()
{
    return _currentGameStats._moveCount > 0;
}