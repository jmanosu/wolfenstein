/*
File: Hex.cpp
Author: Jared Tence
Last Edit: 10/13/2018

Description: Hex Object functions and methods
*/

#ifndef Hex_cpp
#define Hex_cpp

#include <iostream>
#include "hex.hpp"


Hex::Hex(int x, int y, int z, HexTexture * hexTexture) {
  this->x = x;
  this->y = y;
  this->z = z;
  this->hexTexture = hexTexture;

  hexTexture->parent(this);

  int hexWidth = hexTexture->getHexWidth();
  int hexHeight = hexTexture->getHexHeight();

  GVector::GVector newPos;
  newPos.x = hexWidth * x + hexWidth / 2 * z;
  newPos.y = (hexHeight - hexTexture->getPeakHeight())  * z;
  pos(newPos);
}


//Hex destructor
Hex::~Hex(){
  delete hexTexture;
}

void Hex::draw(int drawX, int drawY, int scall)
{
  Graphics::instance()->setColor(250,250,250,1);
  Graphics::instance()->drawPoint(pos(world).x, pos(world).y);
  Graphics::instance()->drawPoint(pos(world).x+1, pos(world).y+1);
  Graphics::instance()->drawPoint(pos(world).x+1, pos(world).y);
  Graphics::instance()->drawPoint(pos(world).x, pos(world).y+1);
  Graphics::instance()->drawPoint(pos(world).x-1, pos(world).y-1);
  Graphics::instance()->drawPoint(pos(world).x, pos(world).y-1);
  Graphics::instance()->drawPoint(pos(world).x-1, pos(world).y);
  Graphics::instance()->drawPoint(pos(world).x+1, pos(world).y-1);
  Graphics::instance()->drawPoint(pos(world).x-1, pos(world).y+1);
  
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

#endif
