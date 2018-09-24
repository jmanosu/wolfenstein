#ifndef player_cpp
#define player_cpp

#include "player.hpp"

Player::Player(){}

Player::~Player(){}

void Player::init(int xpos, int ypos, double speed, double fov, double los)
{
  this->xpos  = xpos;
  this->ypos  = ypos;
  this->speed = speed;
  this->fov   = fov;
  this->los   = los;
}

int Player::get_xpos()
{
  return xpos;
}

int Player::get_ypos()
{
  return ypos;
}

double Player::get_fov()
{
  return fov;
}

void Player::moveForward()
{

}

void Player::moveBackward(){

}

void Player::moveLeft()
{

}

void Player::moveRight()
{

}

void Player::twoDRender(SDL_Renderer * renderer)
{
  SDL_SetRenderDrawColor(renderer, 250, 100, 100, 0);
  double radian = fov * M_PI / 180;
  double c = cos(radian);
  double s = sin(radian);
  SDL_RenderDrawLine(renderer, xpos, ypos, xpos + (c * 30), ypos + (s * 30));
  radian = 0;
  c = cos(radian);
  s = sin(radian);
  SDL_RenderDrawLine(renderer, xpos, ypos, xpos + (c * 30), ypos + (s * 30));
  SDL_SetRenderDrawColor(renderer, 250, 100, 250, 0);
  SDL_RenderDrawPoint(renderer, xpos, ypos);
}

#endif
