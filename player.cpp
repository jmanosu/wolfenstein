/*
File: player.cpp
Author: Jared Tence
Last Edit: 10/13/2018

Description: Player object that holds the values and functions of the player
*/

#ifndef player_cpp
#define player_cpp

#include "player.hpp"

//constructor for player
Player::Player(){}

//destructor for player
Player::~Player(){}

//initalizer for player
void Player::init(int xpos, int ypos, double speed, double fov, double los)
{
  this->xpos  = xpos;
  this->ypos  = ypos;
  this->speed = speed;
  this->fov   = fov;
  this->los   = los;
}

//accessor for x position
int Player::get_xpos()
{
  return xpos;
}

//accessor for y position
int Player::get_ypos()
{
  return ypos;
}

//accessor for feild of vision
double Player::get_fov()
{
  return fov;
}

//accessor for line of sight
double Player::get_los()
{
  return los;
}

void Player::moveForward()
{

}

void Player::moveBackward(){

}

void Player::moveLeft()
{
  this->los += 8;
  if(this->los > 360){
    this->los -= 360;
  }
}

void Player::moveRight()
{
  this->los -= 8;
  if(this->los < 0){
    this->los += 360;
  }
}

//renders the player with it's feild of vision.
//used for debugging
void Player::twoDRender(SDL_Renderer * renderer)
{
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
  double radian = (los-fov/2) * M_PI / 180;
  double c = cos(radian);
  double s = sin(radian);
  SDL_RenderDrawLine(renderer, xpos, ypos, xpos + (c * 30), ypos + (s * 30));
  radian = (los+fov/2) * M_PI / 180;
  c = cos(radian);
  s = sin(radian);
  SDL_RenderDrawLine(renderer, xpos, ypos, xpos + (c * 30), ypos + (s * 30));
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
  SDL_RenderDrawPoint(renderer, xpos, ypos);
}

#endif
