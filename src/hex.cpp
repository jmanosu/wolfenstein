/*
File: Hex.cpp
Author: Jared Tence
Last Edit: 10/13/2018

Description: Hex Object functions and methods
*/

#include <iostream>
#include "hex.hpp"


Hex::Hex(int x, int z, HexTexture * hexTexture) : location(x,z), mNeighbors(int(NorthWest) + 1, 0){
  this->hexTexture = hexTexture;

  hexTexture->parent(this);

  int hexWidth = hexTexture->getHexWidth();
  int hexHeight = hexTexture->getHexHeight();

  GVector newPos;
  newPos.x = hexWidth * location.getX() + hexWidth / 2 * location.getZ();
  newPos.y = (hexHeight - hexTexture->getPeakHeight())  * location.getZ();
  pos(newPos);
}


//Hex destructor
Hex::~Hex(){
  delete hexTexture;
}

void Hex::draw()
{
  hexTexture->render();
}

bool Hex::checkCollision(int px, int py)
{
  bool collision = false;
/*  int radius = cos(30*PI/180) * size * .9;
  if((pow(px-this->centerX, 2) + pow(py-this->centerY, 2)) <= pow(radius+2, 2)){
    std::cout << "collison radius: " << (pow(px-this->centerX, 2) + pow(py-this->centerY, 2)) << std::endl;
    collision = true;
  }
*/
  //if (collision) {
  //  hexColor.r = 250;
  //  hexColor.g = 250;
  //  hexColor.b = 250;
  //}
  return collision;
}

void Hex::addNeighbor(Hex * neighbor, Direction direction)
{
  mNeighbors.at(int(direction)) = neighbor;
}

Space * Hex::getSpace(int i)
{
  return mSpaces.at(i);
}

void Hex::initalizeSpaces()
{
}

void Hex::update()
{
  if (InputManager::instance()->getCurrentEvent().type == SDL_MOUSEBUTTONDOWN) {
    GVector mousePos = InputManager::instance()->getCurrentMousePos();
    GVector myPos = pos(world);

    if (mousePos.x < myPos.x + 20 && mousePos.x > myPos.x - 20 && mousePos.y < myPos.y + 20 && mousePos.y > myPos.y - 20) {
      std::cout << "x: " << this->location.getX() << " z: " << this->location.getZ() << std::endl;
    }
  }
}