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

void BattleMap::render()
{
  for(auto & hex : mHexGrid) {
    hex.second->renderBackground();
    hex.second->renderMidground();
    hex.second->renderForground();
  }
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
        BattleHex * targetHex = getHex(target);
        if (targetHex != nullptr) {
          targetHex->applyWeapon(weapon);
        } 
      }
      break;
    default:
      break;
    }
}

template<typename Func> void BattleMap::modifyHexCoordRange(int range, CubeCoord location, Func function)
{
  for (int q = -range; q <= range; q++) {
    for (int r = std::max(-range, -q - range); r <= std::min(range, -q + range); r++) {
      BattleHex * hex = getHex(CubeCoord(q + location.getQ(), r + location.getR()));
      if (hex != nullptr) {
        function(hex, std::abs(q));
      }
    }
  }
}

template<typename Func> void BattleMap::modifyHexReachable(int range, CubeCoord location, Func function)
{
  range += 1;

  modifyHexCoordRange(range, location, 
    [&](BattleHex * hex, int distance) {
      hex->setVisited(false);
    }
  );

  std::vector<std::vector<BattleHex *>> fringes(2);

  BattleHex * startHex = getHex(location);
  startHex->setVisited(true);

  if (startHex == nullptr) {
    return;
  }

  fringes.at(0).push_back(startHex);

  for (int i = 0; i < range; i++) {
    while (fringes.at(i % 2).size() > 0) {
      BattleHex * hex = fringes.at(i % 2).back();
      function(hex, i);

      if (i+1 < range) {
        for (size_t d = North; d <= NorthWest; d++) {
          BattleHex * neighbor = hex->getNeighbor((Direction)d);

          if (neighbor == nullptr) {
            continue;
          }

          if (!neighbor->getVisted() && neighbor->getLevel() == hex->getLevel()) {
            fringes.at((i+1) % 2).push_back(neighbor);
            neighbor->setVisited(true);
          }
        }
      }
      fringes.at(i % 2).pop_back();
    }
  }

  modifyHexCoordRange(range, location, 
    [&](BattleHex * hex, int distance) {
      hex->setVisited(false);
    }
  );
}

HexCollection BattleMap::getHexRangeCollection(int range, CubeCoord location)
{
  HexCollection hexCollection;

  modifyHexCoordRange(range, location,
    [&](BattleHex * battleHex, int distance){
      HexCollectionEntry hexCollectionEntry(battleHex, distance);
      hexCollection.addHex(location, hexCollectionEntry);
    }
  );

  return hexCollection;
}

HexCollection BattleMap::getHexReachableCollection(int range, CubeCoord location)
{
  HexCollection hexCollection;

  hexCollection.setCenter(location);

  modifyHexReachable(range, location,
    [&](BattleHex * battleHex, int distance){
      HexCollectionEntry hexCollectionEntry(battleHex, distance);
      hexCollection.addHex(battleHex->getLocation(), hexCollectionEntry);
    }
  );

  return hexCollection;
}