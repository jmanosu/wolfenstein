/*
File: map.cpp
Author: Jared Tence
Last Edit: 10/13/2018

Description: The Map class contains a three dimensional array of Wall objects
  in a dynamically allocated array. This map can be rendered in a 2-d format
  where the walls are draw as a grid system. The other option is a 3-d render
  where the walls are draw using a technique called ray casting.

  Ray Casting Link: https://en.wikipedia.org/wiki/Ray_casting

*/
#ifndef Map_cpp
#define Map_cpp

#include "map.hpp"

// constructor for Map object
Map::Map() : GameEntity(200, 200)
{
  generateCubeMap(3, 50);
  centerX = 200;
  centerY = 200;
}

//simple destructor, delets all dynamically allocated variables
Map::~Map()
{
  for(auto & outer_map_pair : hexs) {
    for(auto & inner_map_pair : outer_map_pair.second) {
      delete inner_map_pair.second;
    }
  }
}

void Map::init()
{
}

void Map::render()
{
  for(int q = -this->radius; q <= this->radius; q++)
  {
    int r = std::min(this->radius, this->radius - q);
    for(int i = 0; i < 2 * this->radius + 1 - std::abs(q); i++)
    {
      this->hexs[-q - r][q]->draw(centerX, centerY, 3);
      r--;
    }
  }
}

void Map::update()
{

}

void Map::generateCubeMap(int radius, double size)
{
  int hexWidth  = 2 * cos(30*PI/180)*size;
  int hexHeight = (6* size)/4;
  for(int q = -radius; q <= radius; q++){
    int r = std::min(radius, radius - q);
    for(int i = 0; i < 2 * radius + 1 - std::abs(q); i++){
        HexTexture * newHexTexture = new HexTexture("desertHex2.png", 56, 73, 21);
        Hex * newHex = new Hex(q, -q - r, r, newHexTexture);
        newHex->parent(this);
        this->hexs[newHex->getX()][newHex->getZ()] = newHex;
        r--;
    }
  }

  this->boundX = hexWidth * (radius / 3);
  this->boundY = hexHeight * (radius / 3);

  this->radius = radius;
}
/* 
void Map::generateGridMap(int rows, int colms, int size)
{
  int hexWidth  = 2 * cos(30*PI/180)*size;
  int hexHeight = (6* size)/4;
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < colms; j++){
      if(j % 2){
        Hex * temp = new Hex(hexWidth / 2 + hexWidth * i, hexHeight * j, size, 30, 0, 0, 0);
        this->hexs.push_back(temp);
      } else {
        Hex * temp = new Hex(hexWidth * i, hexHeight * j, size, 30, 0, 0, 0);
        this->hexs.push_back(temp);
      }
    }
  }
}
*/
void Map::setCenterXY(int nextX, int nextY)
{
  if (nextX < -boundX) {
    this->centerX = -boundX;
  } else if(nextX > boundX + sc_width){
    this->centerX = boundX + sc_width;
  } else {
    this->centerX = nextX;
  }

  if (nextY < -boundY) {
    this->centerY = -boundY;
  } else if(nextY > boundY + sc_height){
    this->centerY = boundY + sc_height;
  } else {
    this->centerY = nextY;
  }
}

void Map::handleClick(SDL_Event event)
{
  switch (event.type) {
    case SDL_KEYDOWN:
      switch( event.key.keysym.sym ){
          default:
            break;
        }
        break;
    case SDL_MOUSEBUTTONDOWN:
      switch ( event.button.button ){
      case SDL_BUTTON_LEFT:
        break;
      case SDL_BUTTON_RIGHT:
        int x, y;
        SDL_GetMouseState(&x, &y);
        eTracker.dragX = x;
        eTracker.dragY = y;
        eTracker.drag  = true;
        eTracker.oldX  = this->pos(world).x;
        eTracker.oldY  = this->pos(world).y;
        break;
      default:
        break;
      }
      break;
    case SDL_MOUSEBUTTONUP:
      switch ( event.button.button ){
      case SDL_BUTTON_LEFT:
        int x, y;
        SDL_GetMouseState(&x, &y);
        for(auto & outer_map_pair : hexs) {
          for(auto & inner_map_pair : outer_map_pair.second) {
            inner_map_pair.second->checkCollision(x, y);
          }
        }
        break;
      case SDL_BUTTON_RIGHT:
        eTracker.drag = false;
        break;
      default:
        break;
      }
      break;
    case SDL_MOUSEMOTION:
      if(eTracker.drag){
        int x, y, differenceX, differenceY;
        SDL_GetMouseState(&x, &y);
        differenceX = (x - eTracker.dragX) * .9;
        differenceY = (y - eTracker.dragY) * .9;
        GVector::GVector newPos;
        newPos.x = eTracker.oldX + differenceX;
        newPos.y = eTracker.oldY + differenceY;
        pos(newPos);
      }
      break;
    default:
      break;
  }
}

#endif