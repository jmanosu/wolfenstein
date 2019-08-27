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

//Hex constructor
Hex::Hex(){}

//Hex destructor
Hex::~Hex(){}

//Hex initalizer that takes in a Color struct
void Hex::init(double x, double y, double z, int degree, Color hexColor, double skewX = 1, double skewY = 1)
{
  this->x = x;
  this->y = y;
  this->z = z;
  this->degree = degree;
  this->hexColor = hexColor;
  this->skewX = skewX;
  this->skewY = skewY;
  this->centerX = 0;
  this->centerY = 0;
  this->size;
}

//Hex initalizer that takes three integers which repesents r g b of the color
// of the Hex
void Hex::init(double x, double y, double z, int degree, int r, int g, int b, double skewX = 1, double skewY = 1)
{
  Color hexColor;
  this->x = x;
  this->y = y;
  this->z = z;
  this->degree = degree;
  hexColor.r = r;
  hexColor.g = g;
  hexColor.b = b;
  this->hexColor = hexColor;
  this->skewX = skewX;
  this->skewY = skewY;
  this->centerX = 0;
  this->centerY = 0;
  this->size;
}

void Hex::draw(SDL_Renderer * renderer, double displaceX, double displaceY, double size)
{
  int hexWidth  = 2 * cos(30*PI/180)*size;
  int hexHeight = (6* size)/4;
  
  this->centerX = hexWidth * x + hexWidth / 2 * z + displaceX;
  this->centerY = hexHeight * z + displaceY;
  
  this->size = size;
  
  SDL_SetRenderDrawColor(renderer, this->hexColor.r, this->hexColor.g, this->hexColor.b, 1);
  SDL_RenderDrawPoint(renderer, this->centerX, this->centerY);
  
  int currentDegree = this->degree;
  
  double currentX = cos(currentDegree*PI/180)*size + centerX;
  double currentY = sin(currentDegree*PI/180)*size + centerY;

  for(int i = 0; i < 6; i++)
  {
    //vertices.push_back(std::tuple<int,int>(currentX * this->skewX + displaceX, currentY * this->skewY + displaceY));


    currentDegree = currentDegree + 60;
    
    double nextX = cos(currentDegree*PI/180)*size + centerX;
    double nextY = sin(currentDegree*PI/180)*size + centerY;
    
    SDL_RenderDrawLine(renderer,
      currentX,
      currentY,
      nextX,
      nextY);

      SDL_SetRenderDrawColor(renderer, 250,250,250, 1);
        SDL_RenderDrawPoint(renderer, currentX * this->skewX , currentY * this->skewY);
      SDL_SetRenderDrawColor(renderer, this->hexColor.r, this->hexColor.g, this->hexColor.b, 1);

    currentX = nextX;
    currentY = nextY;
  }
}

bool Hex::checkCollision(int px, int py)
{
  bool collision = false;
  /*for(int i = 0; i < vertices.size(); i++){
    int next = i + 1;
    if(i == vertices.size()){
      next = 0;
    }
    int vcx = std::get<0>(vertices[i]);    // c for "current"
    int vcy = std::get<1>(vertices[i]);    // c for "current"
    int vnx = std::get<0>(vertices[next]);       // n for "next"
    int vny = std::get<1>(vertices[next]);    // n for "next"
    if (((vcy >= py && vny < py) || (vcy < py && vny >= py)) &&
         (px < (vnx-vcx)*(py-vcy) / (vny-vcy)+vcx)) {
            collision = !collision;
    }
  }*/
  int radius = cos(30*PI/180) * size * .9;
  if((pow(px-this->centerX, 2) + pow(py-this->centerY, 2)) <= pow(radius+2, 2)){
    std::cout << "collison radius: " << (pow(px-this->centerX, 2) + pow(py-this->centerY, 2)) << std::endl;
    collision = true;
  }

  if (collision) {
    hexColor.r = 250;
    hexColor.g = 250;
    hexColor.b = 250;
  }
  return collision;
}

//accessor for Hex color
Color Hex::get_color()
{
  return this->hexColor;
}

#endif
