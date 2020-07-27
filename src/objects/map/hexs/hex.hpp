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
#include "objects/map/weapons/weapon.hpp"

#include "geometry/cubeCoord.hpp"

#include "gameplay/input/inputManager.hpp"

typedef uint8_t HexSide;

template <typename _Hex> class Hex : public InteractableEntity {
  public:

    Hex();
    Hex(const Hex &hexR);
    ~Hex();

    Hex & operator = (Hex const &obj);

    _Hex * clone();

    void setDimensions(int width, int height, int peakHeight);
    void setLocation(CubeCoord location, int depth = 0);

    bool checkCollision(int, int);
    
    void addNeighbor(_Hex *, Direction);
    _Hex * getNeighbor(Direction);

    void update();

    void setDepth(int depth) { _depth = depth; }

    CubeCoord getLocation() { return mLocation; }

    int getWidth()      { return mWidth;  }
    int getHeight()     { return mHeight; }
    int getPeakHeight() { return mPeakHeight; }
    int getDepth()      { return _depth;  }

  protected:

    CubeCoord mLocation;

    std::vector<_Hex *> mNeighbors;

    int mHeight, mWidth, mPeakHeight, _depth;
};



template <class _Hex> Hex<_Hex>::Hex() :
  mLocation(0,0),

  mNeighbors(int(NorthWest) + 1, nullptr),

  mWidth(0),
  mHeight(0),
  mPeakHeight(0),
  _depth(0)
{
  for (size_t i = North; i <= NorthWest; i++) {
    mNeighbors.at(i) = nullptr;
  }
}

template <class _Hex> Hex<_Hex>::Hex(const Hex &obj) : Hex()
{
  setDimensions(obj.mWidth, obj.mHeight, obj.mPeakHeight);

  setLocation(obj.mLocation, obj._depth);

  _depth = obj._depth;
}


//Hex destructor
template <class _Hex> Hex<_Hex>::~Hex(){
}

template <class _Hex> Hex<_Hex> & Hex<_Hex>::operator = (const Hex<_Hex> &obj)
{
  setDimensions(obj.mWidth, obj.mHeight, obj.mPeakHeight);

  setLocation(obj.mLocation, obj._depth);

  _depth = obj._depth;
}

template <class _Hex> _Hex * Hex<_Hex>::clone() {
  return nullptr;
}

template <class _Hex> void  Hex<_Hex>::setDimensions(int width, int height, int peakHeight)
{
  mWidth = width;
  mHeight = height;
  mPeakHeight = peakHeight;
}


template <class _Hex> void Hex<_Hex>::setLocation(CubeCoord location, int depth)
{
  mLocation = location;
  _depth = depth;
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
}

#endif
