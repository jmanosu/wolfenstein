#include "graphics.hpp"

Graphics * Graphics::sInstance = nullptr;
bool Graphics::sInitalized = false;

//public
Graphics * Graphics::instance()
{
    if(sInstance == nullptr)
    {
        sInstance = new Graphics();
    }
    return sInstance;
}

void Graphics::release()
{
  delete sInstance;
  sInstance = nullptr;

  sInitalized = false;
}

bool Graphics::initalized()
{
    if(sInstance == nullptr)
    {
        return false;
    }
    return sInitalized;
}

void Graphics::render()
{
  SDL_RenderPresent(mRenderer);
}

void Graphics::clear()
{
  SDL_RenderClear(mRenderer);
}

void Graphics::drawTexture(SDL_Texture * texture)
{
  SDL_Rect texr; texr.x = 100; texr.y = 100; texr.w = 200; texr.h = 200; 
  SDL_RenderCopy(mRenderer, texture, NULL, &texr);
}

//private
Graphics::Graphics()
{
  sInitalized = init();
}

Graphics::~Graphics()
{
  SDL_DestroyWindow(mWindow);
  SDL_DestroyRenderer(mRenderer);
  SDL_Quit();
  std::cout << "WINDOW, RENDERER, and SUBSYSTEMS terminated" << std::endl;
}

bool Graphics::init()
{
  int flags = SDL_WINDOW_SHOWN;

  if(/*fullScreen*/ false){
    flags = SDL_WINDOW_FULLSCREEN;
  }

  //SDL_Init initalizes everything and creates window if init returns no error
  if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
    std::cout << "SYSTEM initialized" << std::endl;
    //creates window at the center of the screen using width and height args
    mWindow = SDL_CreateWindow("title",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              screenWidth,
                              screenHeight,
                              flags);

    //error catching if window is created succesfully or not
    if(mWindow){
      std::cout << "WINDOW created" << std::endl;
    }else{
      printError();
      return false;
    }

    //creates renderer
    mRenderer = SDL_CreateRenderer(mWindow, -1, 0);
    //clears errors
    SDL_ClearError();

    //if renderer is created succesfully sets color of render else error catch
    if(mRenderer){
      SDL_SetRenderDrawColor(mRenderer, 255, 0, 255, 255);
      std::cout << "RENDERER created" << std::endl;
    }else{
      printError();
      return false;
    }

    //sets is Running variable to true which is used to tell if user wants to exit
    return true;

  }else{
    printError();
    return false;
  }
}

void Graphics::printError()
{
    std::cout << SDL_GetError() << std::endl;
}

SDL_Renderer * Graphics::getRenderer()
{
  return mRenderer;
}

SDL_Texture * Graphics::loadTexture(std::string imgPath)
{
  return IMG_LoadTexture(mRenderer, imgPath.c_str());
}