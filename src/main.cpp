/*
File: main.cpp
Author: Jared Tence
Last Edit: 10/13/2018

Description: main.cpp creates a game object. Renders it until the isRunning
  bool in game is set to false causing the while loop to end and the game cleaning
  itself
*/

#include <SDL2/SDL.h>
#include <iostream>
#include "game.hpp"
#include "constants.hpp"

Game * game = NULL;

// Main:
int main(int argc, char* argv[]) {

    game = new Game();
    game->init("test", 0, 0, sc_width, sc_height, false);

    while(game->running()){
      game->handleEvents();
      game->update();
      game->render();
    }

    game->clean();

    return 0;
}
