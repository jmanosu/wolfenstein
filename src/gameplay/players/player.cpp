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
  _units.push_back(unit);
}

Unit * Player::getUnit(unsigned int index)
{
  if (index > _units.size()) {
    return nullptr;
  }

  return _units.at(index);
}

Unit * Player::getUnplacedUnit()
{
  for (int i = 0; i < _units.size(); i++) {
    if (_units.at(i) != nullptr && !_units.at(i)->getPlaced()) {
      return _units.at(i);
    }
  }

  return nullptr;
}

bool Player::setupFinished()
{
  for (int i = 0; i < _units.size(); i++) {
    if (_units.at(i) != nullptr && !_units.at(i)->getPlaced()) {
      return false;
    }
  }

  return true;
}