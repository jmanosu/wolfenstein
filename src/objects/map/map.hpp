/*
File: map.hpp
Author: Jared Tence
Last Edit: 10/13/2018

Description: header file for map. Map has a 3 dimensional array of wall objects
  called floors. This allows for multipule levels.

*/
#ifndef Map_hpp
#define Map_hpp

#include <iostream>
#include <SDL2/SDL.h>
#include <cmath>
#include <vector>
#include <list>
#include <tuple>

#include "objects/gameEntity.hpp"
#include "objects/map/hexGrid.hpp"
#include "objects/map/hexs/hex.hpp"
#include "objects/map/hexObjects/hexObject.hpp"
#include "objects/map/weapons/weapon.hpp"

#include "geometry/cubeCoord.hpp"

#include "utils/constants.hpp"

#include "gameplay/input/inputManager.hpp"

#include "graphics/textures/animatedTexture.hpp"

template <typename Hex> class Map : public GameEntity{
  public:
    Map();
    ~Map();

    void init();

    void render();
    void update();

    void initMapNeighbors();

    void addHex(CubeCoord, Hex *);
    Hex * getHex(CubeCoord);

    void addHexObject(CubeCoord, HexObject *);
    HexObject * getHexObject(CubeCoord);
    HexObject * getHexObject(ID);

    void moveHexObject(CubeCoord, ID);

    Hex * getSelectedHex();
    Hex * getHoveredHex();
    Hex * getClickedHex();

  protected:
    int boundX, boundY;
    int radius;

    std::map<ID, HexObject *> mHexObjects;

    Hex * mSelectedHex;
    Hex * mHoveredHex;
    Hex * mClickedHex;

    HexGrid<Hex *> mHexGrid;
};

// constructor for Map object
template <class Hex> Map<Hex>::Map() : GameEntity(200, 200)
{
  scale(GVector(3,3));

  mSelectedHex = nullptr;
  mClickedHex = nullptr;
  mHoveredHex = nullptr;
}

//simple destructor, delets all dynamically allocated variables
template <class Hex> Map<Hex>::~Map()
{

}

template <class Hex> void Map<Hex>::init()
{
}

template <class Hex> void Map<Hex>::render()
{
  for(auto & hex : mHexGrid) {
    hex.second->render();
  }
}

template <class Hex> void Map<Hex>::update()
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

template <class Hex> void Map<Hex>::initMapNeighbors()
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

template <class Hex> void Map<Hex>::addHex(CubeCoord location, Hex * hex)
{
  if (hex != nullptr) {
    hex->parent(this);
    hex->setLocation(location);
    mHexGrid.add(location, hex);
  }
}

template <class Hex> Hex * Map<Hex>::getHex(CubeCoord location)
{
  return mHexGrid.get(location);
}

template <class Hex> void Map<Hex>::addHexObject(CubeCoord location, HexObject * hexObject)
{
  Hex * hex = getHex(location);

  if (hex != nullptr && hexObject != nullptr) {
    this->mHexObjects[hexObject->id()] = hexObject;
    hex->releaseHexObject();
    hex->setHexObject(hexObject);
  }
}

template <class Hex> HexObject * Map<Hex>::getHexObject(CubeCoord location)
{
  Hex * hex = getHex(location);

  if (hex != nullptr) {
    return hex->getHexObject();
  } else {
    return nullptr;
  }
}

template <class Hex> HexObject * Map<Hex>::getHexObject(ID id)
{
  std::map<ID, HexObject *>::iterator it;
  it = mHexObjects.find(id);

  if (it != mHexObjects.end()) {
    return it->second;
  } else {
    return nullptr;
  }
}

template <class Hex> void Map<Hex>::moveHexObject(CubeCoord location, ID id)
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

template <class Hex> Hex * Map<Hex>::getSelectedHex()
{
  return mSelectedHex;
}

template <class Hex> Hex * Map<Hex>::getClickedHex()
{
  return mClickedHex;
}

template <class Hex> Hex * Map<Hex>::getHoveredHex()
{
  return mHoveredHex;
}

#endif