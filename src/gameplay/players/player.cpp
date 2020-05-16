/*
File: player.cpp
Author: Jared Tence
Last Edit: 10/13/2018

Description: Player object that holds the values and functions of the player
*/

#include "player.hpp"

//constructor for player
Player::Player(){}

//destructor for player
Player::~Player(){}


void Player::addUnit(Unit * unit)
{
  if (mUnits[unit->id()] != nullptr) {
    mUnits[unit->id()] = unit;
  } else {
    mUnits[unit->id()] = unit;
  }
}

Unit * Player::getUnit(unsigned int id)
{
  std::map<unsigned int, Unit *>::iterator it;
  it = mUnits.find(id);

  if (it != mUnits.end()) {
    return it->second;
  } else {
    std::cout << "returning null" << std::endl;
    return nullptr;
  }
}