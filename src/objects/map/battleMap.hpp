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

#include "objects/map/hexs/battleHex.hpp"
#include "objects/map/hexs/hexCollection.hpp"

class BattleMap : public Map<BattleHex> {
  public:
    BattleMap();
    ~BattleMap();

    void render();

    void addUnit(CubeCoord, Unit *);
    Unit * getUnit(ID);

    void applyWeapon(Weapon *, CubeCoord, CubeCoord);

    template<typename Func> void modifyHexCoordRange(int, CubeCoord, Func);

    template<typename Func> void modifyHexReachable(int, CubeCoord, Func);

    HexCollection getHexRangeCollection(int, CubeCoord);
    HexCollection getHexReachableCollection(int, CubeCoord);

  private:
    std::map<ID, Unit *> mHexUnits;
};

#endif