/*
File: map.hpp
Author: Jared Tence
Last Edit: 10/13/2018

Description: header file for map. Map has a 3 dimensional array of wall objects
  called floors. This allows for multipule levels.

*/
#ifndef BATTLE_MAP
#define BATTLE_MAP

#include "objects/map/map.hpp"
#include "objects/map/hexObjects/units/unit.hpp"

class BattleMap : public Map{
  public:
    BattleMap();
    ~BattleMap();

    void addUnit(CubeCoord, Unit *);
    Unit * getUnit(ID);

    void applyWeapon(Weapon *, CubeCoord, CubeCoord);

  private:

  std::map<ID, Unit *> mHexUnits;
};

#endif