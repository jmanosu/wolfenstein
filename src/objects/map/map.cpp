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
/*#ifndef MAP_CPP
#define MAP_CPP

#include "map.hpp"

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
}

void Map::init()
{
}

void Map::render()
{
  for(auto & hex : mHexGrid) {
    hex.second->render();
  }
}

void Map::update()
{
  if (InputManager::instance()->mouseDown(SDL_BUTTON(SDL_BUTTON_LEFT))) {
    GVector updatedPos = pos();
//    updatedPos.x = InputManager::instance()->getMouseX();
//    updatedPos.y = InputManager::instance()->getMouseY();
    pos(updatedPos);
  }

  bool clicked = 0;

  mHoveredHex = nullptr;
  mClickedHex = nullptr;
  for(auto & hex : mHexGrid) {
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
  for(auto & hex : mHexGrid) {
    for (size_t i = North; i <= NorthWest; i++) {      
      CubeCoord neighborLocation = hex.first + getCubeCoord(Direction(i));
      Hex * neighborHex = getHex(neighborLocation);
      if(neighborHex != nullptr) {
        hex.second->addNeighbor(neighborHex, Direction(i));
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
  if (hex != nullptr) {
    hex->parent(this);
    hex->setLocation(location);
    mHexGrid.add(location, hex);
  }
}

Hex * Map::getHex(CubeCoord location)
{
  return mHexGrid.get(location);
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
  Hex * hex = getHex(location);

  if (hex != nullptr) {
    return hex->getHexObject();
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

#endif*/