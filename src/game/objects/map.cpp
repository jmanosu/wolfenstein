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

#include "map.hpp"
#include "game/objects/hexObject.hpp"

// constructor for Map object
Map::Map() : GameEntity(200, 200)
{
  scale(GVector(3,3));

  mSelectedHex = nullptr;
  mClickedHex = nullptr;
  mHoveredHex = nullptr;
}

//simple destructor, delets all dynamically allocated variables
Map::~Map()
{
  for(auto & hex : mHexs) {
    delete hex.second;
  }
}

void Map::init()
{
}

void Map::render()
{
  for(auto & hex : mHexs) {
    hex.second->renderBackground();\
    hex.second->renderMidground();
    hex.second->renderForground();
  }
}

void Map::update()
{
  if (InputManager::instance()->getCurrentEvent().type == SDL_MOUSEMOTION) {
    GVector updatedPos = pos();
    updatedPos.x += InputManager::instance()->getMouseDrag().x;
    updatedPos.y += InputManager::instance()->getMouseDrag().y;
//    pos(updatedPos);
  }

  bool clicked = 0;

  for(auto & hex : mHexs) {
    hex.second->update();
    if (hex.second->getClicked()) {
      clicked = 1;

      mSelectedHex = hex.second;
      mClickedHex = hex.second;
    }
    if (hex.second->getHovered()) {
      mHoveredHex = hex.second;
    }
  }

  if (!clicked) {
    mClickedHex = nullptr;
  }
}

void Map::handleClick(SDL_Event event)
{
}

void Map::initMapNeighbors()
{
  for(auto & hex : mHexs) {
    for (size_t i = North; i <= NorthWest; i++)
    {      
      CubeCoord neighborLocation = hex.first + getCubeCoord(Direction(i));
      std::map<CubeCoord, Hex *>::iterator it;
      it = this->mHexs.find(neighborLocation);
      if(it != mHexs.end()) {
        hex.second->addNeighbor(it->second, Direction(i));
      } 
    }
  }
}


void Map::loadMap(std::vector<std::vector<int>> map, std::vector<Hex *> mapBindings)
{
  for(int i = 0; i < map.size(); i++) {
    for(int j = 0; j < map[i].size(); j++) {
      if (map[i][j] == -1) {
        continue;
      }
      Hex * newHex = mapBindings.at(map[i][j])->clone();
      CubeCoord location = axialToCubeOddVertical(i, j);
      newHex->setLocation(location);
      addHex(location, newHex);
    }
  }
  initMapNeighbors();
}

void Map::addHex(CubeCoord location, Hex * hex)
{
  if(this->mHexs[location] != nullptr) {
    this->mHexs[location] = hex;
    hex->parent(this);
  } else {
    delete this->mHexs[location];
    this->mHexs[location] = hex;
    hex->parent(this);
  }
}

Hex * Map::getHex(CubeCoord location)
{
  std::map<CubeCoord, Hex *>::iterator it;
  it = mHexs.find(location);

  if (it != mHexs.end()) {
    return it->second;
  } else {
    return nullptr;
  }
}

void Map::addHexObject(CubeCoord location, HexObject * hexObject)
{
  Hex * hex = getHex(location);

  if (hex != nullptr && hexObject != nullptr) {
    this->mHexObjects[hexObject->id()] = hexObject;
    hex->releaseHexObject();
    hex->setHexObject(hexObject);
  }
}

HexObject * Map::getHexObject(CubeCoord location)
{
  std::map<CubeCoord, Hex *>::iterator it;
  it = mHexs.find(location);

  if (it != mHexs.end()) {
    return it->second->getHexObject();
  } else {
    return nullptr;
  }
}

HexObject * Map::getHexObject(ID id)
{
  std::map<ID, HexObject *>::iterator it;
  it = mHexObjects.find(id);

  if (it != mHexObjects.end()) {
    return it->second;
  } else {
    return nullptr;
  }
}

void Map::moveHexObject(CubeCoord location, ID id)
{
  Hex * hex = getHex(location);
  HexObject * hexObject = getHexObject(id);

  if (hex != nullptr && hexObject != nullptr) {
    CubeCoord oldLocation = hexObject->getLocation();
    Hex * oldHex = getHex(oldLocation);

    if (oldHex != nullptr) {
      oldHex->releaseHexObject();
    }

    hex->releaseHexObject();
    hex->setHexObject(hexObject);
  }

}

Hex * Map::getSelectedHex()
{
  return mSelectedHex;
}

Hex * Map::getClickedHex()
{
  return mClickedHex;
}

Hex * Map::getHoveredHex()
{
  return mHoveredHex;
}

void Map::applyWeapon(Weapon * weapon, CubeCoord origin, CubeCoord target)
{
  switch (weapon->getType()) {
    case beam:
      break;
    case projectile:
      break;
    case mortor:
      {
        Hex * originHex = getHex(origin);
        Hex * targetHex = getHex(target);
        std::cout  << "targetHex " << targetHex << std::endl;
        targetHex->applyWeapon(weapon);
      }
      break;
    default:
      break;
    }
}

#endif