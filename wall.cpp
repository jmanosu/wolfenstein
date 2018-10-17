/*
File: wall.cpp
Author: Jared Tence
Last Edit: 10/13/2018

Description: Wall Object functions and methods
*/

#ifndef wall_cpp
#define wall_cpp

#include <iostream>
#include "wall.hpp"

//Wall constructor
Wall::Wall(){}

//Wall destructor
Wall::~Wall(){}

//wall initalizer that takes in a Color struct
void Wall::init(Color wallc, bool isFloor)
{
  this->wallc = wallc;
  this->isFloor = isFloor;
}

//wall initalizer that takes three integers which repesents r g b of the color
// of the wall
void Wall::init(int r, int g, int b, bool isFloor)
{
  Color wallc;
  wallc.r = r;
  wallc.g = g;
  wallc.b = b;
  this->wallc = wallc;
  this->isFloor = isFloor;
}

//accessor for wall color
Color Wall::get_color()
{
  return this->wallc;
}

bool Wall::get_isFloor()
{
  return this->isFloor;
}

#endif
