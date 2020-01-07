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
  scale(GVector(4,4));
  centerX = 200;
  centerY = 200;
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
  for(auto & hex : hexs) {
    hex.second->draw();
  }
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
        Hex * newHex = new Hex();
        HexTexture newHexTexture("forest10.png", 54, 73, 22);
        newHex->setLocation(CubeCoord(q, r));
//        newHex->setTexture(newHexTexture);
        addHex(CubeCoord(newHex->getX(), newHex->getZ()), newHex);
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
  for(auto & hex : hexs) {
    for (size_t i = North; i <= NorthWest; i++)
    {      
      CubeCoord neighborLocation = hex.first + getCubeCoord(Direction(i));
      std::map<CubeCoord, Hex *>::iterator it;
      it = this->hexs.find(neighborLocation);
      if(it != hexs.end()) {
        hex.second->addNeighbor(it->second, Direction(i));
      } 
    }
  }
}

void Map::addHex(CubeCoord location, Hex * hex)
{
  if(this->hexs[location] != nullptr) {
    this->hexs[location] = hex;
    hex->parent(this);
  } else {
    delete this->hexs[location];
    this->hexs[location] = hex;
    hex->parent(this);
  }
}



void Map::loadMap(std::vector<std::vector<int>> map, std::vector<Hex> mapBindings)
{
  for(int i = 0; i < map.size(); i++) {
    for(int j = 0; j < map[i].size(); j++) {
      if (map[i][j] == -1) {
        continue;
      }
      Hex * newHex = new Hex();
      *newHex = mapBindings.at(map[i][j]);
      CubeCoord location = axialToCube(i, j);
      newHex->setLocation(location);
      addHex(location, newHex);
    }
  }
  initMapNeighbors();
}

#endif