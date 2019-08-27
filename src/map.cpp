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

void drawHexagon(SDL_Renderer *, double, double, double);
void drawHexagonGrid(SDL_Renderer *, double, double, double, double, double);
void drawHexagonGrid2(SDL_Renderer *, double, double, int, double);
// constructor for Map object
Map::Map()
{
//  generateGridMap(5,5,20);
  generateCubeMap(3, 50);
  centerX = 200;
  centerY = 200;
}

//simple destructor, delets all dynamically allocated variables
Map::~Map()
{
}

void Map::init()
{
}

void Map::render(SDL_Renderer * renderer)
{
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
  for(int i = 0; i < this->hexs.size(); i++){
    this->hexs[i].draw(renderer, centerX, centerY, 50);
  }
  SDL_SetRenderDrawColor(renderer, 250, 0, 0, 1);
}

void Map::generateCubeMap(int radius, double size)
{
  int hexWidth  = 2 * cos(30*PI/180)*size;
  int hexHeight = (6* size)/4;
  for(int q = -radius; q <= radius; q++){
    int r = std::min(radius, radius - q);
    for(int i = 0; i < 2 * radius + 1 - std::abs(q); i++){
        Hex temp;
        temp.init(q, -q - r ,r , 30, 0, 0, 0, 1, .5);
        this->hexs.push_back(temp);
        r--;
    }
  }
  this->boundX = hexWidth * (radius / 3);
  this->boundY = hexHeight * (radius / 3);
}

void Map::generateGridMap(int rows, int colms, int size)
{
  int hexWidth  = 2 * cos(30*PI/180)*size;
  int hexHeight = (6* size)/4;
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < colms; j++){
      if(j % 2){
        Hex temp;
        temp.init(hexWidth / 2 + hexWidth * i, hexHeight * j, size, 30, 0, 0, 0, 1, .5);
        this->hexs.push_back(temp);
        //drawHexagon(renderer, startx + hexWidth / 2 + hexWidth * i, starty + hexHeight * j, size);
      } else {
        Hex temp;
        temp.init(hexWidth * i, hexHeight * j, size, 30, 0, 0, 0, 1, .5);
        this->hexs.push_back(temp);
        //drawHexagon(renderer, startx + hexWidth * i, starty + hexHeight * j, size);
      }
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
  std::cout << "centerX: " << this->centerX << " boundX: " << boundX << std::endl;
  std::cout << "centerY: " << this->centerY << " boundY: " << boundY << std::endl;
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
        eTracker.oldX  = this->centerX;
        eTracker.oldY  = this->centerY;
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
        std::cout << "x: " << x << " y: " << y << std::endl;
        for(int i = 0; i < this->hexs.size(); i++){
          this->hexs[i].checkCollision(x, y);
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
        setCenterXY(eTracker.oldX + differenceX, eTracker.oldY + differenceY);
      }
      break;
    default:
      break;
  }
}

#endif

/*
void drawHexagonGrid(SDL_Renderer * renderer, double startx, double starty, double rows, double colms, double size)
{  
  int hexWidth  = 2 * cos(30*PI/180)*size;
  int hexHeight = (6* size)/4;
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < colms; j++){
      if(j % 2){
        
        //drawHexagon(renderer, startx + hexWidth / 2 + hexWidth * i, starty + hexHeight * j, size);
      } else {
        //drawHexagon(renderer, startx + hexWidth * i, starty + hexHeight * j, size);
      }
    }
  }
}

void drawHexagonGrid2(SDL_Renderer * renderer, double startx, double starty, int radius, double size)
{  
  int hexWidth  = 2 * cos(30*PI/180)*size;
  int hexHeight = (6* size)/4;
  for(int q = -radius; q <= radius; q++){
    int r = std::min(radius, radius - q);
    for(int i = 0; i < 2 * radius + 1 - std::abs(q); i++){
        drawHexagon(renderer, startx + hexWidth * q + hexWidth / 2 * r, starty + hexHeight * r, size);
      r--;
    }
  }
}


void drawHexagon(SDL_Renderer * renderer, double centerX, double centerY, double size)
{  
  SDL_RenderDrawPoint(renderer, centerX, centerY);
  int degree = 30;
  double currentX = cos(degree*PI/180)*size + centerX;
  double currentY = sin(degree*PI/180)*size + centerY;
  for(int i = 0; i < 6; i++){
    degree = degree + 60;
    double nextX = cos(degree*PI/180)*size + centerX;
    double nextY = sin(degree*PI/180)*size + centerY;
    SDL_RenderDrawLine(renderer, currentX, currentY, nextX, nextY);
    currentX = nextX;
    currentY = nextY;
  }
}
*/