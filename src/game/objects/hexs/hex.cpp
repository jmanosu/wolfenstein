/*
File: Hex.cpp
Author: Jared Tence
Last Edit: 10/13/2018

Description: Hex Object functions and methods
*/

#include <iostream>
#include "hex.hpp"


Hex::Hex() : mLocation(0,0), mNeighbors(int(NorthWest) + 1, 0), mHexTexture(nullptr), mHexSkirtTexture(nullptr), mHighlighted(false), mWidth(0), mHeight(0), mPeakHeight(0)
{
  for (size_t i = North; i < NorthWest; i++) {
    mNeighbors.at(i) = nullptr;
  }
  hexTextureHighlight = nullptr;
}

Hex::Hex(const Hex &obj) : Hex()
{
  setHexDimensions(obj.mWidth, obj.mHeight, obj.mPeakHeight);

  if(obj.mHexTexture != nullptr) {
    setHexTexture(*(obj.mHexTexture));
  }

  if(obj.mHexSkirtTexture != nullptr) {
    setHexSkirtTexture(*(obj.mHexSkirtTexture));
  }

  setLocation(obj.mLocation);
}


//Hex destructor
Hex::~Hex(){
  delete mHexTexture;
  delete mHexSkirtTexture;
  delete hexTextureHighlight;
}

void Hex::setLocation(CubeCoord location, int height)
{
  mLocation = location;

  GVector newPos;

  newPos.x = (mWidth - 1) * mLocation.getX() + mWidth / 2 * mLocation.getZ();
  newPos.y = (mHeight - mPeakHeight - 1)  * mLocation.getZ() + height * scale(world).y;

  pos(newPos);
}

void Hex::setHexDimensions(int width, int height, int peakHeight)
{
  mWidth = width;
  mHeight = height;
  mPeakHeight = peakHeight;
}


void Hex::setHexTexture(Texture hex)
{
  if (this->mHexTexture == nullptr) {
    this->mHexTexture = new Texture();
  }

  *(this->mHexTexture) = hex;

  this->mHexTexture->parent(this);
}

void Hex::setHexSkirtTexture(Texture skirt)
{
  if (this->mHexSkirtTexture == nullptr) {
    this->mHexSkirtTexture = new Texture();
  }

  *(this->mHexSkirtTexture) = skirt;

  this->mHexSkirtTexture->parent(this);
}

void Hex::draw()
{
  if (mHexTexture != nullptr) {
    mHexTexture->render();
  }
  
  if (mHexSkirtTexture != nullptr) {
    mHexSkirtTexture->render();
  }

  if (mHighlighted && hexTextureHighlight != nullptr) {
    hexTextureHighlight->render();
  }

}

bool Hex::checkCollision(int px, int py)
{
  bool collision = false;
  return collision;
}

void Hex::addNeighbor(Hex * neighbor, Direction direction)
{
  mNeighbors.at(int(direction)) = neighbor;
}

void Hex::update()
{
  if (InputManager::instance()->getCurrentEvent().type == SDL_MOUSEBUTTONDOWN) {
    GVector mousePos = InputManager::instance()->getCurrentMousePos();
    GVector myPos = pos(world);

    if (mousePos.x < myPos.x + 20 && mousePos.x > myPos.x - 20 && mousePos.y < myPos.y + 20 && mousePos.y > myPos.y - 20) {
      mHighlighted = true;
      for (size_t i = North; i <= NorthWest; i++) {
        Hex * neighbor = mNeighbors.at(i);
        if (neighbor) {
          neighbor->setHighlighted(true);
        }
      }
    }
  }
}

void Hex::setHighlighted(bool highlighted) {
  this->mHighlighted = highlighted;
}

Hex & Hex::operator = (Hex const &obj)
{
  setHexDimensions(obj.mWidth, obj.mHeight, obj.mPeakHeight);

  if(obj.mHexTexture != nullptr) {
    setHexTexture(*(obj.mHexTexture));
  }

  if(obj.mHexSkirtTexture != nullptr) {
    setHexSkirtTexture(*(obj.mHexSkirtTexture));
  }

  setLocation(obj.mLocation);
}