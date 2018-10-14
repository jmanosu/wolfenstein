/*
File: map.hpp
Author: Jared Tence
Last Edit: 10/13/2018

Description: header file for map. Map has a 3 dimensional array of wall objects
  called floors. This allows for multipule levels.

*/
#ifndef Map_hpp
#define Map_hpp

#include <iostream>
#include <SDL2/SDL.h>
#include <cmath>
#include "wall.hpp"
#include "player.hpp"
#include <tuple>

class Map{
  public:
    Map();
    ~Map();
    void init(Wall ***, int, int, int, int);
    void twoDRender(SDL_Renderer *, int, int, int);
    void threeDRender(SDL_Renderer *, Player*, int = 0, int = 0, int = 640, int = 480);
    std::tuple<double, double, Wall> calcWDistance(int, int, double, SDL_Renderer *);
    void defaultMap(int, int);
  private:
    int length, width, bsize, nfloors;
    Wall *** floors;
};

#endif
