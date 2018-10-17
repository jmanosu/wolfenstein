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
}

//initalizer initalizes the SDL graphic display and objects like the Map and Player
void Game::init(const char * title, int xpos, int ypos, int width, int height, bool fullscreen)
{
  int flags = SDL_WINDOW_SHOWN;

  if(fullscreen){
    flags = SDL_WINDOW_FULLSCREEN;
  }

  //SDL_Init initalizes everything and creates window if init returns no error
  if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
    std::cout << "SYSTEM initialized" << std::endl;
    //creates window at the center of the screen using width and height args
    window = SDL_CreateWindow(title,
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              width, height,
                              flags);

    //error catching if window is created succesfully or not
    if(window){
      std::cout << "WINDOW created" << std::endl;
    }else{
       std::cout << "WINDOW creation ERROR" << std::endl;
    }

    //creates renderer
    renderer = SDL_CreateRenderer(window, -1, 0);
    //clears errors
    SDL_ClearError();

    //if renderer is created succesfully sets color of render else error catch
    if(renderer){
      SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
      std::cout << "RENDERER created" << std::endl;
    }else{
      std::cout << "RENDERER creation ERROR" << std::endl;
    }

    //sets is Running variable to true which is used to tell if user wants to exit
    isRunning = true;

    //creates map and Player variables
    map = new Map();
    map->defaultMap(15,15);

    player = new Player();
    player->init(30,30);
  }else{
    isRunning = false;
    std::cout << "ERROR failed to initalize" << std::endl;
  }
}

//handleEvents checks for any input and if so executes their specific operation
void Game::handleEvents(){
  //creates SDL_Event temp object
  SDL_Event event;
  //polls the event handler and sets event to the top of the event stack
  SDL_PollEvent(&event);
  switch (event.type) {
    //if close button is clicked the render is set to terminate
    case SDL_QUIT:
      isRunning = false;
      break;
    case SDL_KEYDOWN:
      switch( event.key.keysym.sym ){
                        case SDLK_LEFT:
                            player->moveLeft();
                            break;
                        case SDLK_RIGHT:
                            player->moveRight();
                            break;
                        case SDLK_UP:
                            player->moveForward();
                            break;
                        case SDLK_DOWN:
                            player->moveBackward();
                            break;
                        default:
                            break;
                    }
        break;
    default:
      break;
  }
}

//clears renderer and renderers the map
void Game::render(){
  SDL_RenderClear(renderer);
  map->twoDRender(renderer, 0, 0,20);
  map->threeDRender(renderer, player);
  player->twoDRender(renderer);
  SDL_RenderPresent(renderer);
}

//updates game objects
void Game::update(){

}

//destroys graphic window when game when game is terminating
void Game::clean(){
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
  std::cout << "WINDOW, RENDERER, and SUBSYSTEMS terminated" << std::endl;
}



#endif
