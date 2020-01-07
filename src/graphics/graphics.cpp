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

    if(TTF_Init() == -1) {
      std::cout << "ERROR initalizing font" << std::endl;
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

SDL_Texture * Graphics::createTextTexture(TTF_Font * font, std::string text, SDL_Color color)
{
  SDL_Surface * surface = TTF_RenderText_Solid(font, text.c_str(), color);

  if (surface == nullptr) {
    std::cout << "ERROR failed to generate surface for text texture" << std::endl;
    return nullptr;
  }

  SDL_Texture * texture = SDL_CreateTextureFromSurface(mRenderer, surface);

  if (texture == nullptr) {
    std::cout << "ERROR failed to generate texture for text texture" << std::endl;
    return nullptr;
  }

  SDL_FreeSurface(surface);

  return texture;
}

void Graphics::drawTexture(SDL_Texture * texture, SDL_Rect * clipRect, SDL_Rect * renderRect)
{
  SDL_RenderCopy(mRenderer, texture, clipRect, renderRect);
}

void Graphics::drawLine(int x1, int y1, int x2, int y2)
{
  SDL_RenderDrawLine(mRenderer, x1, y1, x2, y2);
}

void Graphics::drawPoint(int x, int y)
{
  SDL_RenderDrawPoint(mRenderer, x, y);
}

void Graphics::drawPoint(GVector vector)
{
  SDL_RenderDrawPoint(mRenderer, vector.x, vector.y);
}

void Graphics::setColor(int r, int g, int b, double a)
{
  SDL_SetRenderDrawColor(mRenderer, r, g, b, a);
}