/*
File: player.cpp
Author: Jared Tence
Last Edit: 10/13/2018

Description: Player object header file
*/

#ifndef player_hpp
#define player_hpp

#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>
#include <vector>

#include "objects/map/hexObjects/units/unit.hpp"

class Player{
  public:
    Player();
    ~Player();

    void addUnit(Unit *);
    Unit * getUnit(unsigned int);
    Unit * getUnplacedUnit();

    bool setupFinished();

  private:
    std::vector<Unit *> _units;
};

#endif
