/*
File: game.cpp
Author: Jared Tence
Last Edit: 10/13/2018

Description: The Game class allows for the creation of a Game object that can
  render, run, and update both the graphic display and game objects. SDL2 is
  used as the graphics package

  SDL2: https://www.libsdl.org/index.php

*/

#ifndef game_cpp
#define game_cpp

#include "game.hpp"

//Game constructor
Game::Game(){}

//Game deconstructor
Game::~Game(){
  delete map;
  delete player;
  mGraphics->release();
  mAssetManager->release();
  mTimer->release();
  mInputManager->release();
}

//initalizer initalizes the SDL graphic display and objects like the Map and Player
void Game::init(const char * title, int xpos, int ypos, int width, int height, bool fullscreen)
{
  mGraphics = Graphics::instance();
  mAssetManager = assetManager::instance();
  map = new Map();
  isRunning = Graphics::initalized();
  mTimer = Timer::instance();
  mInputManager = InputManager::instance();
}

//handleEvents checks for any input and if so executes their specific operation
void Game::handleEvents(){
  mInputManager->update();
  if (mInputManager->didQuit())
  {
    isRunning = false;
  }
}

//updates game objects
void Game::update(){
  mTimer->update();
  map->update();
}

//clears renderer and renderers the map
void Game::render(){
  if(mTimer->deltaTime() >= (1.0f / FRAME_RATE))
  {
    SDL_SetRenderDrawColor(mGraphics->getRenderer(), 255, 0, 0, 255);
    mGraphics->clear();
    map->render();
    mGraphics->render();
    mTimer->reset();
  }
}

//destroys graphic window when game when game is terminating
void Game::clean(){
}


#endif
