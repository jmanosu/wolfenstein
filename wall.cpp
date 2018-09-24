#ifndef wall_cpp
#define wall_cpp

#include <iostream>
#include "wall.hpp"

Wall::Wall(){}

Wall::~Wall(){}

void Wall::init(Color wallc)
{
  this->wallc = wallc;
}

void Wall::init(int r, int g, int b)
{
  Color wallc;
  wallc.r = r;
  wallc.g = g;
  wallc.b = b;
  this->wallc = wallc;
}

Color Wall::get_color()
{
  return this->wallc;
}

#endif
