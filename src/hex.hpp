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

class Hex : public GameEntity{
  public:
    Hex(int, int, int, HexTexture *);
    //Hex(double, double, double, int, int, int, int);
    ~Hex();
    //void draw(SDL_Renderer *, double, double, double);
    void draw(int, int, int);
    bool checkCollision(int, int);
    //Color get_color();
    int getX() { return x; }
    int getY() { return y; }
    int getZ() { return z; }
  private:
    int x, y, z;
    int centerX, centerY;
    //int degree;
    //int size;
    //std::vector<std::tuple<int, int>> vertices;
    //Color hexColor;
    //Texture * tileTexture;
    HexTexture * hexTexture;
};

#endif
