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
  scale(GVector(3,2));
  generateCubeMap(3, 50);
  initMapNeighbors();
  centerX = 200;
  centerY = 200;
  mATexture = new AnimatedTexture("animatedDot.png", 0, 0, 19, 19, 10, 1000.0f, AnimatedTexture::ANIM_DIR::horizontal);
  mATexture->pos(GVector(200,200));
  mATexture->WrapMode(AnimatedTexture::WRAP_MODE::loop);
}

//simple destructor, delets all dynamically allocated variables
Map::~Map()
{
  for(auto & hex : hexs) {
    delete hex.second;
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
      this->hexs[CubeCoord(-q - r, q)]->draw();
      r--;
    }
  }
  const SDL_version *link_version=TTF_Linked_Version();
  Texture temp("HELLO DAD!", "Roboto-Black.ttf", 180, {.r = 255, .g = 255, .b = 0, .a = 0});
  temp.parent(this);
  temp.render(200, 200, 300, 300);
  mATexture->render();
}

void Map::update()
{
  if (InputManager::instance()->getCurrentEvent().type == SDL_MOUSEMOTION) {
    GVector updatedPos = pos();
    updatedPos.x += InputManager::instance()->getMouseDrag().x;
    updatedPos.y += InputManager::instance()->getMouseDrag().y;
    pos(updatedPos);
  }
  for (auto it = hexs.begin(); it != hexs.end(); it++ ) {
    Hex * hex = it->second;
    hex->update();
  }
  mATexture->update();
}

void Map::generateCubeMap(int radius, double size)
{
  int hexWidth  = 2 * cos(30*PI/180)*size;
  int hexHeight = (6* size)/4;

  this->boundX = hexWidth * (radius / 3);
  this->boundY = hexHeight * (radius / 3);

  this->radius = radius;

  for(int q = -radius; q <= radius; q++){
    int r = std::min(radius, radius - q);
    for(int i = 0; i < 2 * radius + 1 - std::abs(q); i++){
        HexTexture * newHexTexture = new HexTexture("desertHex9.png", 54, 73, 22);
        Hex * newHex = new Hex(q, r, newHexTexture);
        newHex->parent(this);
        this->hexs[CubeCoord(newHex->getX(), newHex->getZ())] = newHex;

        r--;
    }
  }
}

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

}

void Map::initMapNeighbors()
{
  for(int q = -this->radius; q <= this->radius; q++)
  {
    int r = std::min(this->radius, this->radius - q);
    for(int i = 0; i < 2 * this->radius + 1 - std::abs(q); i++)
    {
      for (size_t i = North; i <= NorthWest; i++)
      {
        std::map<CubeCoord, Hex *>::iterator it;
        CubeCoord temp = CubeCoord(q, r) + getCubeCoord(Direction(i));
        it = this->hexs.find(CubeCoord(q, r) + getCubeCoord(Direction(i)));
        Hex * hex = this->hexs.find(CubeCoord(q, r))->second;
        if(it != hexs.end()) {
          hex->addNeighbor(it->second, Direction(i));
        } 
      }
      
      r--;
    }
  }
}

#endif