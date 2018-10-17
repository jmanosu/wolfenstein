/*
File: wall.hp
Author: Jared Tence
Last Edit: 10/13/2018

Description: header function for wallc
*/
#ifndef wall_hpp
#define wall_hpp

#include <iostream>

struct Color{
  int r;
  int g;
  int b;
};

class Wall{
  public:
    Wall();
    ~Wall();
    void init(Color, bool=true);
    void init(int, int, int, bool=true);
    Color get_color();
    bool get_isFloor();
  private:
    Color wallc;
    bool isFloor;
};

#endif
