/*
File: Hex.cpp
Author: Jared Tence
Last Edit: 10/13/2018

Description: Hex Object functions and methods
*/

#include <iostream>
#include "hex.hpp"


Hex::Hex() :
  mLocation(0,0),
  mOrientation(horizontal),

  mNeighbors(int(NorthWest) + 1, nullptr),

  mWidth(0),
  mHeight(0),
  mPeakHeight(0),
  mLevel(0),

  mHighlighted(false),

  mHexObject(nullptr)
{
  for (size_t i = North; i <= NorthWest; i++) {
    mNeighbors.at(i) = nullptr;
  }
}

Hex::Hex(const Hex &obj) : Hex()
{
  setDimensions(obj.mOrientation, obj.mWidth, obj.mHeight, obj.mPeakHeight, obj.mLevel);

  setLocation(obj.mLocation);

  mLevel = obj.mLevel;
  mOrientation = obj.mOrientation;
}


//Hex destructor
Hex::~Hex(){
}


Hex & Hex::operator = (Hex const &obj)
{
  setDimensions(obj.mOrientation, obj.mWidth, obj.mHeight, obj.mPeakHeight, obj.mLevel);

  setLocation(obj.mLocation);

  mLevel = obj.mLevel;
  mOrientation = obj.mOrientation;
}

Hex * Hex::clone()
{
  Hex * newHex = new Hex(*(this));
  return newHex;
}

void Hex::setDimensions(Orientation orientation, int width, int height, int peakHeight, int level)
{
  mOrientation = orientation;
  mWidth = width;
  mHeight = height;
  mPeakHeight = peakHeight;
  mLevel = level;
}


void Hex::setLocation(CubeCoord location)
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


bool Hex::checkCollision(int x, int y)
{
  GVector mPos = pos(world);

  double difference = pow((mPos.x - x), 2) + pow((mPos.y - y), 2);

  if (difference < pow(((mHeight - 2) * scale(world).y / 2), 2)) {
    return true;
  }

  return false;
}

void Hex::addNeighbor(Hex * neighbor, Direction direction)
{
  mNeighbors.at(int(direction)) = neighbor;
}

void Hex::update()
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

void Hex::setHighlighted(bool highlighted) {
  this->mHighlighted = highlighted;
}

void Hex::setHexObject(HexObject * hexObject)
{
  mHexObject = hexObject;
  mHexObject->parent(this);
  mHexObject->setLocation(mLocation);
}

void Hex::releaseHexObject()
{
  mHexObject = nullptr;
}

HexObject * Hex::getHexObject()
{
  return mHexObject;
}

void Hex::applyWeapon(Weapon * weapon)
{
  if (mHexObject != nullptr) {
    mHexObject->applyWeapon(weapon);
  }
}