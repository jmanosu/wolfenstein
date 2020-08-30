#include "battleMap.hpp"

BattleMap::BattleMap() :
  HexMap()
{
}

BattleMap::~BattleMap()
{
}

void BattleMap::render()
{
  HexMap::render();
}


void BattleMap::addUnit(CubeCoord location, Unit * unit)
{
  if (unit == nullptr) {
    return;
  }

  this->mHexUnits[unit->id()] = unit;

  getHexTile(location)->setHexObject(unit);
}

void BattleMap::setHexObject(CubeCoord location, HexObject * hexObject)
{
  BattleTile * tile = getHexTile(location);
  tile->releaseHexObject();
  tile->setHexObject(hexObject);
}

void BattleMap::setHexObject(CubeCoord location, Unit * unit)
{
  BattleTile * tile = getHexTile(location);
  tile->releaseHexObject();
  tile->setHexObject(unit);
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
  
}

template<typename Valid, typename Modify> void BattleMap::modifyHexCoordRange(int range, CubeCoord location, Valid valid, Modify modify)
{
  for (int q = -range; q <= range; q++) {
    for (int r = std::max(-range, -q - range); r <= std::min(range, -q + range); r++) {
      CubeCoord newLocation = CubeCoord(q + location.getQ(), r + location.getR());
      BattleTile * tile = getHexTile(newLocation);
      if (tile != nullptr && valid(tile, std::abs(q))) {
        modify(tile, std::abs(q));
      }
    }
  }
}

template<typename Valid, typename Modify> void BattleMap::modifyHexReachable(int range, CubeCoord location, Valid valid, Modify modify)
{
  range += 1;

  modifyHexCoordRange(range, location,
    [&](BattleTile *, int distance) {
      return true;
    },
    [&](BattleTile * tile, int distance) {
      tile->setVisited(false);
    }
  );

  std::vector<std::vector<BattleTile *>> fringes(2);

  BattleTile * startTile = getHexTile(location);

  if (startTile == nullptr) {
    return;
  }

  startTile->setVisited(true);
  fringes.at(0).push_back(startTile);

  for (int i = 0; i < range; i++) {
    while (fringes.at(i % 2).size() > 0) {
      BattleTile * tile = fringes.at(i % 2).back();
      modify(tile, i);

      if (i+1 < range) {
        for (HexSide j = 0; j < 6; j++) {
          BattleTile * neighbor = tile->getNeighbor(j);

          if (neighbor == nullptr) {
            continue;
          }

          if (!neighbor->getVisted() && valid(tile, neighbor)) {
            fringes.at((i+1) % 2).push_back(neighbor);
            neighbor->setVisited(true);
          }
        }
      }
      fringes.at(i % 2).pop_back();
    }
  }

  modifyHexCoordRange(range, location,
    [&](BattleTile *, int distance) {
      return true;
    },
    [&](BattleTile * tile, int distance) {
      tile->setVisited(false);
    }
  );
}

HexCollection BattleMap::getHexRangeCollection(int range, CubeCoord location)
{
  HexCollection hexCollection;

  hexCollection.setCenter(location);

  modifyHexCoordRange(range, location,
    [&](BattleTile *, int distance) {
      return true;
    },
    [&](BattleTile * battleTile, int distance){
      HexCollectionEntry hexCollectionEntry(battleTile, distance);
      hexCollection.addTile(battleTile->getLocation(), hexCollectionEntry);
    }
  );

  return hexCollection;
}

HexCollection BattleMap::getHexReachableCollection(int range, CubeCoord location)
{
  HexCollection hexCollection;

  hexCollection.setCenter(location);

  modifyHexReachable(range, location,
    [&](BattleTile * tile, BattleTile * neighbor){
      return tile->getDepth() == neighbor->getDepth();
    },
    [&](BattleTile * battleTile, int distance){
      HexCollectionEntry hexCollectionEntry(battleTile, distance);
      hexCollection.addTile(battleTile->getLocation(), hexCollectionEntry);
    }
  );

  return hexCollection;
}

bool BattleMap::moveHexObject(CubeCoord location, CubeCoord destination)
{
  BattleTile * tile = getHexTile(location);

  BattleTile * destinationTile = getHexTile(destination);

  if (destinationTile->getHexObject() == nullptr) {

    switch (tile->getHexObjectType())
    {
      case BattleTile::HexObjectType::hexObject:
        {
          HexObject * hexObject = tile->getHexObject();

          tile->releaseHexObject();
          destinationTile->setHexObject(hexObject);
          break;
        }
      case BattleTile::HexObjectType::unit:
        {
          Unit * unit = tile->getUnit();

          tile->releaseHexObject();
          destinationTile->setHexObject(unit);

          break;
        }
      default:
        break;
    }

    return true;
  } else {
    return false;
  }
}