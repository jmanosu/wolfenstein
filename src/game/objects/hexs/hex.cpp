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

  mHexTexture(nullptr),
  mSkirtTexture(nullptr),
  mOutlineTexture(nullptr),
  mHighlightTexture(nullptr),

  mNeighbors(int(NorthWest) + 1, 0),

  mWidth(0),
  mHeight(0),
  mPeakHeight(0),
  mLevel(0),

  mHighlighted(false),

  mHexObject(nullptr)
{
  for (size_t i = North; i < NorthWest; i++) {
    mNeighbors.at(i) = nullptr;
  }
}

Hex::Hex(const Hex &obj) : Hex()
{
  setDimensions(obj.mOrientation, obj.mWidth, obj.mHeight, obj.mPeakHeight, obj.mLevel);

  _setHexTexture(obj.mHexTexture);
  _setSkirtTexture(obj.mSkirtTexture);
  _setOutlineTexture(obj.mOutlineTexture);
  _setHighlighTexture(obj.mHighlightTexture);

  setLocation(obj.mLocation);

  mLevel = obj.mLevel;
  mOrientation = obj.mOrientation;
}


//Hex destructor
Hex::~Hex(){
  delete mHexTexture;
  delete mSkirtTexture;
  delete mOutlineTexture;
  delete mHighlightTexture;
}


Hex & Hex::operator = (Hex const &obj)
{
  setDimensions(obj.mOrientation, obj.mWidth, obj.mHeight, obj.mPeakHeight, obj.mLevel);

  _setHexTexture(obj.mHexTexture);
  _setSkirtTexture(obj.mSkirtTexture);
  _setOutlineTexture(obj.mOutlineTexture);
  _setHighlighTexture(obj.mHighlightTexture);

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

void Hex::_setHexTexture(const Texture * hexTexture) {

  if (hexTexture == nullptr) {
    return;
  }

  if (mHexTexture == nullptr) {
    mHexTexture = new Texture();
  }

  *(mHexTexture) = *(hexTexture);
  mHexTexture->parent(this);
}

void Hex::_setSkirtTexture(const Texture * skirtTexture) {

  if (skirtTexture == nullptr) {
    return;
  }

  if (mSkirtTexture == nullptr) {
    mSkirtTexture = new Texture();
  }

  *(mSkirtTexture) = *(skirtTexture);
  mSkirtTexture->parent(this);
}

void Hex::_setOutlineTexture(const Texture * outlineTexture) {

  if (outlineTexture == nullptr) {
    return;
  }

  if (mOutlineTexture == nullptr) {
    mOutlineTexture = new Texture();
  }

  *(mOutlineTexture) = *(outlineTexture);
  mOutlineTexture->parent(this);
}

void Hex::_setHighlighTexture(const Texture * highlightTexture) {

  if (highlightTexture == nullptr) {
    return;
  }

  if (mHighlightTexture == nullptr) {
    mHighlightTexture = new Texture();
  }

  *(mHighlightTexture) = *(highlightTexture);
  mHighlightTexture->parent(this);
}

void Hex::renderBackground()
{
  if (mHexTexture != nullptr) {
    mHexTexture->render();
  }

  if (mSkirtTexture != nullptr) {
    mSkirtTexture->render();
  }
}

void Hex::renderMidground()
{
  if (mOutlineTexture != nullptr) {
    mOutlineTexture->render();
  }

  if (mHighlightTexture != nullptr) {
    mHighlightTexture->render();
  }

  if (mHexObject != nullptr) {
    mHexObject->render();
  }
}

void Hex::renderForground()
{

}

void Hex::render()
{
  renderBackground();
  renderMidground();
  renderForground();
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
  if (InputManager::instance()->getCurrentEvent().type == SDL_MOUSEBUTTONDOWN) {
    GVector mousePos = InputManager::instance()->getCurrentMousePos();
    GVector mPos = pos(world);

    if (checkCollision(mousePos.x, mousePos.y)) {
      mHighlighted = true;
    };
  }
}

void Hex::setHighlighted(bool highlighted) {
  this->mHighlighted = highlighted;
}

void Hex::setHexObject(HexObject * hexObject)
{
  mHexObject = hexObject;
  mHexObject->parent(this);
}

void Hex::releaseHexObject()
{
  mHexObject = nullptr;
}