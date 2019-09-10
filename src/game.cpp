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
}

//initalizer initalizes the SDL graphic display and objects like the Map and Player
void Game::init(const char * title, int xpos, int ypos, int width, int height, bool fullscreen)
{
  mGraphics = Graphics::instance();
  mAssetManager = assetManager::instance();
  map = new Map();
  isRunning = Graphics::initalized();
}

//handleEvents checks for any input and if so executes their specific operation
void Game::handleEvents(){
  //creates SDL_Event temp object
  SDL_Event event;
  //polls the event handler and sets event to the top of the event stack
  SDL_PollEvent(&event);
  map->handleClick(event);
  switch (event.type) {
    //if close button is clicked the render is set to terminate
    case SDL_QUIT:
      isRunning = false;
      break;
    case SDL_KEYDOWN:
      switch( event.key.keysym.sym ){
          default:
            break;
        }
        break;
    case SDL_MOUSEBUTTONDOWN:
      switch ( event.button.button ){
      case SDL_BUTTON_LEFT:
        break;
      case SDL_BUTTON_RIGHT:
        break;
      default:
        break;
      }
    default:
      break;
  }
}

//clears renderer and renderers the map
void Game::render(){
  SDL_SetRenderDrawColor(mGraphics->getRenderer(), 255, 0, 0, 255);
  mGraphics->clear();
  map->render(mGraphics->getRenderer());
  mGraphics->render();
}

//updates game objects
void Game::update(){

}

//destroys graphic window when game when game is terminating
void Game::clean(){
}


#endif
