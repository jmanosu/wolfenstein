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

#include "graphics/assetManager.hpp"
#include "gameplay/input/inputManager.hpp"
#include "gameplay/screens/screenManager.hpp"

#include "gameplay/timer/timer.hpp"

#include "graphics/textureCache.hpp"


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
    TextureCache * mTextureCache;
    
    Timer * mTimer;

    InputManager * mInputManager;
    ScreenManager * mScreenManager;
    assetManager * mAssetManager;

    bool isRunning;

    const int FRAME_RATE = 60;

};


#endif
