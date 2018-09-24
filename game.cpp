#ifndef game_cpp
#define game_cpp

#include "game.hpp"

Game::Game(){}

Game::~Game(){
  delete map;
  delete player;
}

void Game::init(const char * title, int xpos, int ypos, int width, int height, bool fullscreen)
{
  int flags = SDL_WINDOW_SHOWN;
  if(fullscreen){
    flags = SDL_WINDOW_FULLSCREEN;
  }
  if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
    std::cout << "SYSTEM initialized" << std::endl;
    window = SDL_CreateWindow(title,
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              width, height,
                              flags);
    if(window){
      std::cout << "WINDOW created" << std::endl;
    }else{
       std::cout << "WINDOW creation ERROR" << std::endl;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_ClearError();
    if(renderer){
      SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
      std::cout << "RENDERER created" << std::endl;
    }else{
      std::cout << "RENDERER creation ERROR" << std::endl;
    }

    isRunning = true;

    map = new Map();
    map->defaultMap(15,15);

    player = new Player();
    player->init(30,30);
  }else{
    isRunning = false;
    std::cout << "ERROR failed to initalize" << std::endl;
  }
}

void Game::handleEvents(){
  SDL_Event event;
  SDL_PollEvent(&event);
  switch (event.type) {
    case SDL_QUIT:
      isRunning = false;
      break;
    default:
      break;
  }
}

void Game::render(){
  SDL_RenderClear(renderer);
  map->twoDRender(renderer, 0, 0,20);
  map->threeDRender(renderer, player);
  player->twoDRender(renderer);
  SDL_RenderPresent(renderer);
}

void Game::update(){

}

void Game::clean(){
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
  std::cout << "WINDOW, RENDERER, and SUBSYSTEMS terminated" << std::endl;
}



#endif
