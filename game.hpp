#ifndef game_hpp
#define game_hpp

#include <SDL2/SDL.h>
#include <iostream>
#include "map.hpp"
#include "player.hpp"

class Game{
  public:
    Game();
    ~Game();
    void init(const char *, int, int, int, int, bool);
    void render();
    void update();
    void clean();
    void handleEvents();
    bool running(){ return isRunning; }
  private:
    bool isRunning;
    SDL_Window * window;
    SDL_Renderer * renderer;
    Map * map;
    Player * player;

};


#endif
