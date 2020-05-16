/*
File: map.cpp
Author: Jared Tence
Last Edit: 10/13/2018

Description: The Map class contains a three dimensional array of Wall objects
  in a dynamically allocated array. This map can be rendered in a 2-d format
  where the walls are draw as a grid system. The other option is a 3-d render
  where the walls are draw using a technique called ray casting.

  Ray Casting Link: https://en.wikipedia.org/wiki/Ray_casting

*/
#ifndef Map_cpp
#define Map_cpp

#include "battleMap.hpp"

// constructor for Map object
BattleMap::BattleMap()
{
  scale(GVector(3,3));

  mSelectedHex = nullptr;
  mClickedHex = nullptr;
  mHoveredHex = nullptr;
}

//simple destructor, delets all dynamically allocated variables
BattleMap::~BattleMap()
{
}

void BattleMap::addUnit(CubeCoord location, Unit * unit)
{
  this->mHexUnits[unit->id()] = unit;
  addHexObject(location, unit);
}

Unit * BattleMap::getUnit(ID id)
{
  std::map<ID, Unit *>::iterator it = mHexUnits.find(id);

  if (it != mHexUnits.end()) {
    return it->second;
  } else {
    return nullptr;
  }

}

void BattleMap::applyWeapon(Weapon * weapon, CubeCoord origin, CubeCoord target)
{
  switch (weapon->getType()) {
    case beam:
      break;
    case projectile:
      break;
    case mortor:
      {
        Hex * targetHex = getHex(target);
        if (targetHex != nullptr) {
          targetHex->applyWeapon(weapon);
        } 
      }
      break;
    default:
      break;
    }
}

#endif