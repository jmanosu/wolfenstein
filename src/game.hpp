/*
File: game.hpp
Author: Jared Tence
Last Edit: 10/13/2018

Description: defenitions for the game class and functions. The Game class contains
  the renderer, window, map, and player object.

*/

#ifndef game_hpp
#define game_hpp

#include <SDL2/SDL.h>
#include <iostream>
#include "graphics.hpp"
#include "assetManager.hpp"
#include "map.hpp"
#include "player.hpp"
#include "timer.hpp"



class Game{
  public:
    Game();
    ~Game();
    void init(const char *, int, int, int, int, bool);
    void update();
    void handleEvents();
    void render();
    void clean();
    bool running(){ return isRunning; }
  private:
    Graphics * mGraphics;
    assetManager * mAssetManager;
    Map * map;
    Player * player;
    Timer * mTimer;
    bool isRunning;

    const int FRAME_RATE = 60;

};


#endif
