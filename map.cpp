/*
File: map.cpp
Author: Jared Tence
Last Edit: 9/27/2018

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
Map::Map()
{
  //nfloors repesents the number of levels the map has
  nfloors = 0;
  //width is the width of the map
  width = 0;
  //length is the length of the map
  length = 0;
  //bsize repesents a single side length of the square walls
  bsize = 0;
  //floors stores all the wall objects
  floors = NULL;
}

//simple destructor, delets all dynamically allocated variables
Map::~Map()
{
  for(int i = 0; i < nfloors; i++){
    for(int j = 0; j < length; j++){
      delete[] floors[i][j];
    }
    delete[] floors[i];
  }
}

//basic initalizer method with default parameters (see map.hpp)
void Map::init(Wall *** floors, int width, int length, int bsize, int nfloors)
{
  this->floors = floors;
  this->width = width;
  this->length = length;
  this->bsize = bsize;
  this->nfloors = nfloors;
}

//generates a default map with a single floor for tests
void Map::defaultMap(int width, int length){
  //construction of floors pointer so it points to an area in the heap
  floors = new Wall**[1];
  floors[0] = new Wall*[length];

  //temparary wall that will be loaded into wall location on each floor
  Wall temp;
  for(int i = 0; i < length; i++){
    floors[0][i] = new Wall[width];
    for(int j = 0; j < width; j++){
      //initalizes the wall object to have a cascading color
      temp.init(j*i, j*i, j*i);
      //sets floors pointer to wall temp
      floors[0][i][j] = temp;
    }
  }

  //changes other variables to refelct new floors compostion
  this->width = width;
  this->length = length;
  this->bsize = 20;
  this->nfloors = 1;
}

void Map::twoDRender(SDL_Renderer * renderer, int startx, int starty, int dsize){
  for(int i = 0; i < length; i++){
    for(int j = 0; j < width; j++){
      Wall tempw = floors[0][i][j];
      SDL_Rect temp;
      temp.x = startx + j * dsize;
      temp.y = starty + i * dsize;
      temp.w = dsize;
      temp.h = dsize;
      SDL_SetRenderDrawColor(renderer, tempw.get_color().r, tempw.get_color().g, tempw.get_color().b, 0);
      SDL_RenderFillRect(renderer, &temp);
    }
  }
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
}

void Map::threeDRender(SDL_Renderer * renderer, Player * player, int startx, int starty, int rwidth, int rheight)
{
  int separation = 1;
  double dfov = player->get_fov();
  double dlos = player->get_los();
  int sstep = ceil(rwidth / dfov * separation);
  double dstep = separation;
  double currentX = 0;
  double dcurrent = dlos - dfov / 2;
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  while(dlos + dfov / 2 > dcurrent){
    std::tuple<double, double, Wall> hit = calcWDistance(player->get_xpos(), player->get_ypos(), dcurrent,  renderer);
    double hitx = std::get<0>(hit);
    double hity = std::get<1>(hit);
    double distance = sqrt(pow(hitx, 2.0)+ pow(hity, 2.0)) * cos((dlos - dcurrent) * M_PI / 180);
    double angle =  atan(3/distance);
    double heightw = tan(angle) / (M_PI/4) * rheight;

    SDL_Rect temp;
    temp.x = currentX;
    temp.y = (rheight / 2) - heightw;
    temp.w = sstep;
    temp.h = heightw * 2;
    SDL_SetRenderDrawColor(renderer, 100, 0, 0, 100 * distance / 20);
    SDL_RenderFillRect(renderer, &temp);
    currentX += sstep;
    dcurrent += dstep;
  }
}

std::tuple<double, double, Wall> Map::calcWDistance(int x, int y, double degree, SDL_Renderer * renderer)
{
  degree = ceil(degree);
  bool end = false;
  double radian = (degree * M_PI) / 180.00;

  double c = cos(radian);
  double currentX = -(x % bsize);
  double xadjust = -1;
  if(c > 0){
    currentX = bsize - (x % bsize);
    xadjust = 0;
  }

  double s = sin(radian);
  double currentY = -(y % bsize);
  double yadjust = -1;
  if(s > 0){
    currentY = bsize - (y % bsize);
    yadjust = 0;
  }

  double closestX = 1000000;
  double closestY = 1000000;

  currentX = round(currentX);
  currentY = round(currentY);

  double foundY = bsize * length;
  double foundX = bsize * width;
  //while(!end){
    if((currentX + x) < (width * bsize) && (currentX + x) > 0){
      foundY = currentX * tan(radian);
      if(foundY + y > 0 && foundY + y < length * bsize){
        Wall temp = floors[0][(int)((y + foundY) / bsize)][(int)((x + currentX) / bsize + xadjust)];
        if(sqrt(pow(closestX,2.0) + pow(closestY,2.0)) > sqrt(pow(currentX,2.0) + pow(foundY,2.0))){
          closestX = currentX;
          closestY = foundY;
        }
      }else{
      }
    }

    if((currentY + y) < (length * bsize) && (currentY + y) > 0){
      foundX = currentY / tan(radian);
      if(foundX + x > 0 && foundX + x < width * bsize){
        Wall temp = floors[0][(int)((y + currentY) / bsize + yadjust)][(int)((x + foundX) / bsize)];
        if(sqrt(pow(closestX,2.0) + pow(closestY,2.0)) > sqrt(pow(foundX,2.0) + pow(currentY,2.0))){
          closestX = foundX;
          closestY = currentY;
        }
      }else{
      }
    }
    currentX += bsize;
    currentY += bsize;
    Wall temp;
    std::tuple<double, double, Wall> foo (closestX, closestY, temp);
    return foo;
}

#endif
