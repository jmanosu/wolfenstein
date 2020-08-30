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

#include "objects/map/battleLocation.hpp"

class BattleMap : public HexMap<BattleTile> {
  public:
    BattleMap();
    ~BattleMap();

    void render();

    void addUnit(CubeCoord, Unit *);
    void setHexObject(CubeCoord, HexObject *);
    void setHexObject(CubeCoord, Unit *);

    Unit * getUnit(ID);

    void applyWeapon(Weapon *, CubeCoord, CubeCoord);

    template<typename Valid, typename Modify> void modifyHexCoordRange(int, CubeCoord, Valid, Modify);
    template<typename Valid, typename Modify> void modifyHexReachable(int, CubeCoord, Valid, Modify);

    HexCollection getHexRangeCollection(int, CubeCoord);
    HexCollection getHexReachableCollection(int, CubeCoord);

    HexObject * getHexObject(CubeCoord) { return nullptr; }
    bool moveHexObject(CubeCoord, CubeCoord);

  private:
    std::map<ID, Unit *> mHexUnits;
};

#endif