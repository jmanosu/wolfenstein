#ifndef player_hpp
#define player_hpp

#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>

class Player{
  public:
    Player();
    ~Player();
    void init(int = 0, int = 0, double = 2.0, double = 60, double = 180);
    void twoDRender(SDL_Renderer *);
    int get_xpos();
    int get_ypos();
    double get_fov();
    double get_los();
    void moveForward();
    void moveBackward();
    void moveLeft();
    void moveRight();
  private:
    int xpos;
    int ypos;
    double speed;
    double fov;
    double los;
};

#endif
