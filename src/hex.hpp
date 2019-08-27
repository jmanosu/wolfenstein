/*
File: hex.hp
Author: Jared Tence
Last Edit: 10/13/2018

Description: header function for Hex
*/
#ifndef hex_hpp
#define hex_hpp

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <tuple>
#include <cmath>
#include "constants.hpp"

struct Color{
  int r;
  int g;
  int b;
};

class Hex{
  public:
    Hex();
    ~Hex();
    void init(double, double, double, int, Color, double, double);
    void init(double, double, double, int, int, int, int, double, double);
    void draw(SDL_Renderer *, double, double, double);
    bool checkCollision(int, int);
    Color get_color();
  private:
    double x, y, z;
    double skewY, skewX;
    int centerX, centerY;
    int degree;
    int size;
    std::vector<std::tuple<int, int>> vertices;
    Color hexColor;
};

#endif
