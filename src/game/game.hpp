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
#include "graphics/graphics.hpp"
#include "managers/assetManager.hpp"
#include "managers/inputManager.hpp"
#include "managers/screenManager.hpp"
#include "game/objects/map.hpp"
#include "game/player/player.hpp"
#include "misc/timer.hpp"



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
    Player * player;
    Timer * mTimer;
    InputManager * mInputManager;
    ScreenManager * mScreenManager;
    bool isRunning;

    const int FRAME_RATE = 60;

};


#endif
