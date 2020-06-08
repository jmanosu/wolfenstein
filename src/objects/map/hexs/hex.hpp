/*
File: hex.hpp
Author: Jared Tence
Last Edit: 10/13/2018

Description: header function for Hex
*/

#ifndef HEX_HPP
#define HEX_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <tuple>
#include <cmath>

#include "utils/constants.hpp"

#include "graphics/textures/texture.hpp"

#include "objects/interactableEntity.hpp"
#include "objects/map/hexObjects/hexObject.hpp"
#include "objects/map/weapons/weapon.hpp"

#include "geometry/cubeCoord.hpp"

#include "gameplay/input/inputManager.hpp"

enum Orientation {
  vertical = 0,
  horizontal = 1
};

template <typename _Hex> class Hex : public InteractableEntity {
  public:

    Hex();
    Hex(const Hex &hexR);
    ~Hex();

    Hex & operator = (Hex const &obj);

    _Hex * clone();

    void setDimensions(Orientation orientation, int width, int height, int peakHeight, int level);
    void setLocation(CubeCoord location);

    bool checkCollision(int, int);
    
    void addNeighbor(_Hex *, Direction);
    _Hex * getNeighbor(Direction);

    void update();

    void setLevel(int level) { mLevel = level; }

    HexObject * getHexObject();
    void setHexObject(HexObject * hexObject);
    void releaseHexObject();

    Orientation getOrientation() { return mOrientation; }

    CubeCoord getLocation() { return mLocation; }

    int getWidth()      { return mWidth;  }
    int getHeight()     { return mHeight; }
    int getPeakHeight() { return mPeakHeight; }
    int getLevel()      { return mLevel;  }

    void setVisited(bool);
    bool getVisted();

  protected:

    Orientation mOrientation;

    CubeCoord mLocation;

    std::vector<_Hex *> mNeighbors;

    int mHeight, mWidth, mPeakHeight, mLevel;

    HexObject * mHexObject;

    bool mVisited;
};



template <class _Hex> Hex<_Hex>::Hex() :
  mLocation(0,0),
  mOrientation(horizontal),

  mNeighbors(int(NorthWest) + 1, nullptr),

  mWidth(0),
  mHeight(0),
  mPeakHeight(0),
  mLevel(0),

  mHexObject(nullptr),

  mVisited(false)
{
  for (size_t i = North; i <= NorthWest; i++) {
    mNeighbors.at(i) = nullptr;
  }
}

template <class _Hex> Hex<_Hex>::Hex(const Hex &obj) : Hex()
{
  setDimensions(obj.mOrientation, obj.mWidth, obj.mHeight, obj.mPeakHeight, obj.mLevel);

  setLocation(obj.mLocation);

  mLevel = obj.mLevel;
  mOrientation = obj.mOrientation;
}


//Hex destructor
template <class _Hex> Hex<_Hex>::~Hex(){
}

template <class _Hex> Hex<_Hex> & Hex<_Hex>::operator = (const Hex<_Hex> &obj)
{
  setDimensions(obj.mOrientation, obj.mWidth, obj.mHeight, obj.mPeakHeight, obj.mLevel);

  setLocation(obj.mLocation);

  mLevel = obj.mLevel;
  mOrientation = obj.mOrientation;
}

template <class _Hex> _Hex * Hex<_Hex>::clone() {
  return nullptr;
}

template <class _Hex> void  Hex<_Hex>::setDimensions(Orientation orientation, int width, int height, int peakHeight, int level)
{
  mOrientation = orientation;
  mWidth = width;
  mHeight = height;
  mPeakHeight = peakHeight;
  mLevel = level;
}


template <class _Hex> void Hex<_Hex>::setLocation(CubeCoord location)
{
  if (mOrientation == vertical) {
    mLocation = location;

    GVector newPos;

    newPos.x = (mWidth - 1) * mLocation.getX() + mWidth / 2 * mLocation.getZ();
    newPos.y = (mHeight - mPeakHeight - 1)  * mLocation.getZ() - mLevel * scale(world).y;

    pos(newPos);
  } else {
    mLocation = location;

    GVector newPos;

    newPos.x = (mWidth - mPeakHeight - 1)  * mLocation.getX();
    newPos.y = (mLocation.getZ() + (mLocation.getX() - (mLocation.getX()&1)) / 2 - 1) * (mHeight - 1) + (mHeight / 2) * (mLocation.getX() % 2)  - mLevel * scale(world).y;
    pos(newPos);
  }
}


template <class _Hex> bool Hex<_Hex>::checkCollision(int x, int y)
{
  GVector mPos = pos(world);

  double difference = pow((mPos.x - x), 2) + pow((mPos.y - y), 2);

  if (difference < pow(((mHeight - 2) * scale(world).y / 2), 2)) {
    return true;
  }

  return false;
}

template <class _Hex> void Hex<_Hex>::addNeighbor(_Hex * neighbor, Direction direction)
{
  mNeighbors.at(int(direction)) = neighbor;
}

template <class _Hex> _Hex * Hex<_Hex>::getNeighbor(Direction direction)
{
  return mNeighbors.at(int(direction));
}

template <class _Hex> void Hex<_Hex>::update()
{
  InputManager * inputmanager = InputManager::instance();
  GVector mousePos = GVector(inputmanager->getMouseX(), inputmanager->getMouseY());

  setClicked(false);
  setHovered(false);

  bool collision = checkCollision(mousePos.x, mousePos.y);
  if (InputManager::instance()->mouseRelease(SDL_BUTTON(SDL_BUTTON_LEFT))) {
    if (collision) {
      setClicked(true);
    }
  } else {
    if (collision) {
      setHovered(true);
    }
  }

  if (mHexObject != nullptr) {
    mHexObject->update();
  }
}

template <class _Hex> void Hex<_Hex>::setHexObject(HexObject * hexObject)
{
  mHexObject = hexObject;
  mHexObject->parent(this);
  mHexObject->setLocation(mLocation);
}

template <class _Hex> void Hex<_Hex>::releaseHexObject()
{
  mHexObject = nullptr;
}

template <class _Hex> HexObject * Hex<_Hex>::getHexObject()
{
  return mHexObject;
}

template <class _Hex> void Hex<_Hex>::setVisited(bool visited)
{
  mVisited = visited;
}

template <class _Hex> bool Hex<_Hex>::getVisted()
{
  return mVisited;
}

#endif
