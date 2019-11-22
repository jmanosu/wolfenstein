/*
File: hex.hpp
Author: Jared Tence
Last Edit: 10/13/2018

Description: header function for Hex
*/

#ifndef hex_hpp
#define hex_hpp

#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <tuple>
#include <cmath>
#include "constants.hpp"
#include "texture.hpp"
#include "hexTexture.hpp"
#include "helpfulStructs.hpp"
#include "gameEntity.hpp"
#include "cubeCoord.hpp"
#include "space.hpp"
#include "inputManager.hpp"

class Hex : public GameEntity{
  public:
    Hex(int, int, HexTexture *);
    ~Hex();
    void draw();
    bool checkCollision(int, int);
    int getX() { return location.getX(); }
    int getY() { return location.getY(); }
    int getZ() { return location.getZ(); }
    void addNeighbor(Hex *, Direction);
    HexTexture * getHexTexture() { return hexTexture; }
    void initalizeSpaces();
    Space * getSpace(int);
    void update();
  private:
    CubeCoord location;
    int centerX, centerY;
    HexTexture * hexTexture;
    std::vector<Hex *> mNeighbors;
    std::vector<Space *> mSpaces;
};

#endif
