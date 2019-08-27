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
#include <vector>
#include <tuple>
#include "hex.hpp"
#include "player.hpp"
#include "constants.hpp"
#include "utl.cpp"

class Map{
  public:
    Map();
    ~Map();
    void init();
    void render(SDL_Renderer *);
    void generateGridMap(int, int, int);
    void generateCubeMap(int, double);
    void setCenterXY(int, int);
    void handleClick(SDL_Event event);
  private:
    int centerX, centerY;
    int boundX, boundY;
    eventTracker eTracker;
    std::vector<Hex> hexs;
};

#endif
