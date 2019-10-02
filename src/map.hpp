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
#include "gameEntity.hpp"
#include "inputManager.hpp"

class Map : public GameEntity{
  public:
    Map();
    ~Map();
    void init();
    void render();
    void update();
    //void generateGridMap(int, int, int);
    void generateCubeMap(int, double);
    void setCenterXY(int, int);
    void handleClick(SDL_Event event);
  private:
    int centerX, centerY;
    int boundX, boundY;
    eventTracker eTracker;
    //std::vector<Hex *> hexs;
    //std::map<int, std::map<int, std::map<int, Hex *>>> hexs;
    std::map<int, std::map<int, Hex *>> hexs;
    int radius;
};

#endif
