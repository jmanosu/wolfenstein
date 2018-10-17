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

class Player{
  public:
    Player();
    ~Player();
    void init(int = 0, int = 0, double = 2.0, double = 60, double = 180);
    void twoDRender(SDL_Renderer *);
    int get_xpos();
    int get_ypos();
    double get_fov();
    double get_los();
    void moveForward();
    void moveBackward();
    void moveLeft();
    void moveRight();
  private:
    //x and y position variables
    int xpos;
    int ypos;
    //speed of walking of the player
    double speed;
    //fov = feild of vision and los = line of sight
    double fov;
    double los;
};

#endif
