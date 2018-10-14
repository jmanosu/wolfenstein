/*
File: main.cpp
Author: Jared Tence
Last Edit: 10/13/2018

Description: main.cpp creates a game object. Renders it until the isRunning
  bool in game is set to false causing the while loop to end and the game cleaning
  itself
*/

#include <SDL2/SDL.h>
#include "game.hpp"
#include <iostream>
//g++ main.cpp game.cpp map.cpp wall.cpp player.cpp -I/home/jmanosu/dev/SDL/x86_64-w64-mingw32/bin/ -l SDL2 -std=c++11

//g++ main.cpp game.cpp map.cpp wall.cpp player.cpp -std=c++11



// Defining screen attributes:
const int sc_width  = 640; // Width
const int sc_height = 480; // Height
const int sc_bpp    = 32;  // Bits per pixel.

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
